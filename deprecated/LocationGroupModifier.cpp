#include "LocationGroupModifier.h"
#include "Item.h"
#include "Attribute.h"
#include <sstream>

using namespace dgmpp;

LocationGroupModifier::LocationGroupModifier(Domain domain, AttributeID attributeID, Association association, std::shared_ptr<Attribute> const& modifier, GroupID groupID, bool isAssistance, bool isOffensive, Character* character) : Modifier(domain, attributeID, association, modifier, isAssistance, isOffensive, character), groupID_(groupID)
{
	
}

LocationGroupModifier::~LocationGroupModifier()
{
}

bool LocationGroupModifier::isMatch(Item* item) const
{
	return item->getGroupID() == groupID_;
}

std::string LocationGroupModifier::print() {
	std::stringstream s;
	s << "{\"groupID\":\"" << static_cast<int>(groupID_)
	<< "\", \"association\":\"" << getAssociationName()
	<< "\", \"attributeID\":\"" << static_cast<int>(getAttributeID())
	<< "\", \"modifier\":" << *getModifier() << "}";
	return s.str();
}
