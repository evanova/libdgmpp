#include "Compiler.h"
#include <iostream>
#include <fstream>
#include <ios>
#include <string>
#include <cstdlib>
#include <limits>
#include <sstream>

using namespace eufe;

template<typename T> std::string to_string(const T& t) {
	std::stringstream s;
	s << t;
	return s.str();
};

Compiler::Compiler(const std::string& databasePath, const std::string& outputPath) : databasePath_(databasePath), outputPath_(outputPath)
{
	char c = outputPath_[outputPath_.size() - 1];
	if (c != '/' && c != '\\')
		outputPath_ += '/';
}

Compiler::~Compiler(void)
{
}

void Compiler::compile()
{
	sqlite3* db = NULL;
	try
	{
		if (sqlite3_open(databasePath_.c_str(), &db) == SQLITE_OK)
		{
			char* errmsg = NULL;
			
			std::cout << "Loading effects..." << std::endl;
			if (sqlite3_exec(db, "select * from dgmEffects", callbackEffect, this, &errmsg) != SQLITE_OK)
			{
				SqliteException exc(errmsg);
				sqlite3_free(errmsg);
				throw exc;
			}
			
			std::cout << "Loading operands..." << std::endl;
			if (sqlite3_exec(db, "select * from dgmOperands", callbackOperand, this, &errmsg) != SQLITE_OK)
			{
				SqliteException exc(errmsg);
				sqlite3_free(errmsg);
				throw exc;
			}
			
			std::cout << "Loading expressions..." << std::endl;
			if (sqlite3_exec(db, "select * from dgmExpressions", callbackExpression, this, &errmsg) != SQLITE_OK)
			{
				SqliteException exc(errmsg);
				sqlite3_free(errmsg);
				throw exc;
			}
			
			sqlite3_close(db);
			db = NULL;

			std::cout << "Compiling expressions..." << std::endl;
			
			for (const auto& i: expressions_)
				compiledExpressionsMap_[i.first] = compileExpression(i.second);
			
			std::cout << "Compiling effects..." << std::endl;
			
			std::string path = outputPath_ + "dgmCompiledEffects.sql";
			std::ofstream os(path.c_str());
			os << "DROP TABLE IF EXISTS dgmCompiledEffects;" << std::endl;
			os << "CREATE TABLE \"dgmCompiledEffects\" (\"effectID\" SMALLINT(6) NOT NULL, \"effectName\" TEXT(400), \"effectCategory\" SMALLINT(6) NOT NULL, \"isOffensive\" BOOL NOT NULL, \"isAssistance\" BOOL NOT NULL, \"byteCode\" BLOB, PRIMARY KEY (\"effectID\"));" << std::endl;
			os << "BEGIN TRANSACTION;" << std::endl;

			for (const auto& i: effects_)
			{
				Row& effect = i.second;
				MemoryBlock compiledEffect = compileEffect(effect);

				os	<< "INSERT INTO \"dgmCompiledEffects\" VALUES (" << effect["effectID"]
					<< ",\"" << effect["effectName"]
					<< "\"," << effect["effectCategory"]
					<< "," << effect["isOffensive"]
					<< "," << effect["isAssistance"]
					<< "," << stringRepresentation(compiledEffect) << ");" << std::endl;
			}
			os << "COMMIT TRANSACTION;" << std::endl;
			os.close();
		}
		else {
			SqliteException exc(sqlite3_errmsg(db));
			throw exc;
		}
	}
	catch(SqliteException& exc)
	{
		if (db)
			sqlite3_close(db);
		throw exc;
	}
}

Compiler::MemoryBlock Compiler::compileExpression(Row& expression)
{
  char* end;

	TypeID arg1 = 0;
	TypeID arg2 = 0;
	//TypeID operandID = std::stoi(expression["operandID"]);
	TypeID operandID = std::strtol(expression["operandID"].c_str(), &end, 10);  
	TypeID expressionAttributeID = 0;
	TypeID expressionGroupID = 0;
	TypeID expressionTypeID = 0;
	
	std::string &expressionValueString = expression["expressionValue"];
	int expressionValueInt;
	
	//try {arg1 = std::stoi(expression["arg1"]);}
  try {arg1 = (int) std::strtol(expression["arg1"].c_str(), &end, 10);
  }
	catch (std::invalid_argument) {}

//	try {arg2 = std::stoi(expression["arg2"]);}
  try {
	  arg2 = std::strtol(expression["arg2"].c_str(), &end, 10);
  }
	catch (std::invalid_argument) {}

	try {
		expressionAttributeID = strtol(expression["expressionAttributeID"].c_str(), &end, 10);
	}
	catch (std::invalid_argument) {}

//	try {expressionGroupID = std::stoi(expression["expressionGroupID"]);}
  try {
	  expressionGroupID = std::strtol(expression["expressionGroupID"].c_str(), &end, 10);
  }
	catch (std::invalid_argument) {}

//	try {expressionTypeID = std::stoi(expression["expressionTypeID"]);}
  try {
	  expressionTypeID = std::strtol(expression["expressionTypeID"].c_str(), &end, 10);
  }
	catch (std::invalid_argument) {}

//	try {expressionValueInt = std::stoi(expressionValueString);}
  try {
	  expressionValueInt = std::strtol(expression["expressionValue"].c_str(), &end, 10);
	  if (end[0] != 0)
		  expressionValueInt = std::numeric_limits<int>::min();
  }
	catch(std::invalid_argument) {expressionValueInt = std::numeric_limits<int>::min();}
	
	MemoryBlock compiledExpression;
	compiledExpression.reserve(64);
	
	if (arg1)
	{
		compiledExpression.append(1, static_cast<Byte>(OPCODE_ARGUMENT));
		Byte type = ARGUMENT_TYPE_EXPRESSION;
		compiledExpression.append(reinterpret_cast<Byte*>(&type), sizeof(Byte));
		short len = sizeof(TypeID);
		compiledExpression.append(reinterpret_cast<Byte*>(&len), sizeof(short));
		compiledExpression.append(reinterpret_cast<Byte*>(&arg1), sizeof(TypeID));
	}
	else {
		int value = std::numeric_limits<int>::min();
		if (expressionAttributeID)
			value = expressionAttributeID;
		else if (expressionGroupID)
			value = expressionGroupID;
		else if (expressionTypeID)
			value = expressionTypeID;
		else if (expressionValueInt != std::numeric_limits<int>::min())
			value = expressionValueInt;
		
		if (value != std::numeric_limits<int>::min()) {
			compiledExpression.append(1, static_cast<Byte>(OPCODE_ARGUMENT));
			Byte type = ARGUMENT_TYPE_INT;
			compiledExpression.append(reinterpret_cast<const Byte*>(&type), sizeof(Byte));
			short len = sizeof(int);
			compiledExpression.append(reinterpret_cast<const Byte*>(&len), sizeof(short));
			compiledExpression.append(reinterpret_cast<const Byte*>(&value), sizeof(int));
		}
		else if (expressionValueString.length() > 0)
		{
			compiledExpression.append(1, static_cast<unsigned char>(OPCODE_ARGUMENT));
			Byte type = ARGUMENT_TYPE_STRING;
			compiledExpression.append(reinterpret_cast<const unsigned char*>(&type), sizeof(Byte));
			short len = static_cast<short>(expressionValueString.length()) + 1;
			compiledExpression.append(reinterpret_cast<const unsigned char*>(&len), sizeof(short));
			compiledExpression.append(reinterpret_cast<const unsigned char*>(expressionValueString.c_str()), len);
		}
		else {
			throw (0);
		}
	}

	if (arg2)
	{
		compiledExpression.append(1, static_cast<unsigned char>(OPCODE_ARGUMENT));
		Byte type = ARGUMENT_TYPE_EXPRESSION;
		compiledExpression.append(reinterpret_cast<unsigned char*>(&type), sizeof(Byte));
		short len = sizeof(TypeID);
		compiledExpression.append(reinterpret_cast<unsigned char*>(&len), sizeof(short));
		compiledExpression.append(reinterpret_cast<unsigned char*>(&arg2), sizeof(TypeID));
	}
	
	compiledExpression.append(1, static_cast<unsigned char>(OPCODE_OPERAND));
	compiledExpression.append(reinterpret_cast<unsigned char*>(&operandID), sizeof(TypeID));
	return compiledExpression;
}

Compiler::MemoryBlock Compiler::compileEffect(Row& effect)
{
	CompiledExpressionsMap expressionsMap;
	size_t len = sizeof(int) * 2;
	len += addExpression(expressions_[effect["preExpression"]], expressionsMap);
	len += addExpression(expressions_[effect["postExpression"]], expressionsMap);
	
	MemoryBlock compiledEffect;
	compiledEffect.reserve(len);
	
	std::map<std::string, int> offsets;
	
	int offset = sizeof(int) * 2;

	for (const auto& i: expressionsMap)
	{
		offsets[i.first] = offset;
		offset += i.second.length();
	}
	
	offset = offsets[effect["preExpression"]];
	compiledEffect.append(reinterpret_cast<unsigned char*>(&offset), sizeof(int));
	offset = offsets[effect["postExpression"]];
	compiledEffect.append(reinterpret_cast<unsigned char*>(&offset), sizeof(int));

	for (const auto& i: expressionsMap)
	{
		size_t len = i.second.length();
		Byte* data = new Byte[len];
#ifdef WIN32
		i.second._Copy_s(data, len, len);
#else
		i.second.copy(data, len);
#endif
		Byte* ptr = data;
		while (static_cast<Opcode>(*ptr) == OPCODE_ARGUMENT)
		{
			ptr++;
			ArgumentType type = static_cast<const ArgumentType>(*ptr);
			ptr++;
			short length = *reinterpret_cast<short*>(ptr);
			ptr += sizeof(short);
			if (type == ARGUMENT_TYPE_EXPRESSION)
			{
				TypeID* value = reinterpret_cast<int*>(ptr);
				*value = offsets[to_string(*value)];
			}
			ptr += length;
		}
		compiledEffect.append(data, len);
		delete[] data;
	}

	return compiledEffect;
}

size_t Compiler::addExpression(Row& expression, CompiledExpressionsMap& expressionsMap)
{
	std::string& expressionID = expression["expressionID"];
	if (expressionsMap.find(expressionID) != expressionsMap.end())
		return 0;
	MemoryBlock& compiledExpression = compiledExpressionsMap_[expressionID];
	expressionsMap[expressionID] = compiledExpression;
	
	size_t len = compiledExpression.length();
	
	TypeID arg1 = 0;
	TypeID arg2 = 0;

	char* end;
	//try { arg1 = std::stoi(expression["arg1"]); }
	try{ arg1 = std::strtol(expression["arg1"].c_str(), &end, 10); }
	catch(std::invalid_argument) {};

	//try {arg2 = std::stoi(expression["arg2"]);}
	try{ arg2 = std::strtol(expression["arg2"].c_str(), &end, 10); }
	catch (std::invalid_argument) {};

	if (arg1)
		len += addExpression(expressions_[expression["arg1"]], expressionsMap);
	if (arg2)
		len += addExpression(expressions_[expression["arg2"]], expressionsMap);
	return len;
}


Compiler::Row Compiler::callback(int argc, char** argv, char** azColName)
{
	Row row;
	for (int i = 0; i < argc; i++) {
		if (argv[i] && azColName[i]) {
			row[azColName[i]] = argv[i];
		}
	}
	return row;
}

int Compiler::callbackExpression(void* context, int argc, char** argv, char** azColName)
{
	Compiler* compiler = reinterpret_cast<Compiler*>(context);
	Row row = callback(argc, argv, azColName);
	compiler->expressions_[row["expressionID"]] = row;
	return SQLITE_OK;
}

int Compiler::callbackOperand(void* context, int argc, char** argv, char** azColName)
{
	Compiler* compiler = reinterpret_cast<Compiler*>(context);
	Row row = callback(argc, argv, azColName);
	compiler->operands_[row["operandID"]] = row;
	return SQLITE_OK;
}

int Compiler::callbackEffect(void* context, int argc, char** argv, char** azColName)
{
	Compiler* compiler = reinterpret_cast<Compiler*>(context);
	Row row = callback(argc, argv, azColName);
	compiler->effects_[row["effectID"]] = row;
	return SQLITE_OK;
}


std::string Compiler::stringRepresentation(const MemoryBlock& memoryBlock)
{
	size_t len = 3 + memoryBlock.size() * 2;
	char *buf = new char[len + 1];
	int i = 2;
	const Byte *ptr = memoryBlock.c_str();
	const Byte *end = ptr + memoryBlock.size();
	buf[0] = 'X';
	buf[1] = buf[len - 1] = '\'';
	buf[len] = 0;

	const char *map= "0123456789ABCDEF";

	for (; ptr != end; ptr++)
	{
		Byte l = *ptr & 0xf;
		Byte h = *ptr >> 4;
		buf[i++] = map[h];
		buf[i++] = map[l];
	}
	
	std::string s(buf);
	delete[] buf;
	return s;
}

int main(int argc, char* argv[])
{
	if (argc != 3) {
		std::cout<<"Usage: compiler source_database.sqlite output_dir"<<std::endl;
		return 0;
	}
	Compiler compiler = Compiler(argv[1], argv[2]);
	compiler.compile();
	return 0;
}