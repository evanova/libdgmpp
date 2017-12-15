#include "Character.h"
#include "Ship.h"
#include "Gang.h"
#include "Engine.h"
#include "Area.h"
#include "Skill.h"
#include "Attribute.h"
#include "Modifier.h"
#include "LocationGroupModifier.h"
#include "LocationRequiredSkillModifier.h"
#include "Implant.h"
#include "Booster.h"
#include <algorithm>
#include <limits>
#include "Structure.h"
#include "SDE.hpp"

using namespace dgmpp;

Character::Character(std::shared_ptr<Engine> const& engine, std::shared_ptr<Gang> const& owner, const char* characterName) : Item(engine, TypeID::characterStatic, owner), characterName_(characterName), ship_(nullptr)
{
}

Character::~Character(void)
{
}

std::shared_ptr<Ship> Character::getShip()
{
	return ship_;
}

std::shared_ptr<Ship> Character::setShip(TypeID typeID)
{
	try
	{
		loadIfNeeded();
		auto engine = getEngine();
		if (!engine)
			return nullptr;
		
		std::shared_ptr<Ship> ship = std::make_shared<Ship>(engine, typeID, shared_from_this());
		
		if (ship_)
			removeEffects(Effect::Category::generic);
		ship_ = ship;
		
		if (ship_)
			addEffects(Effect::Category::generic);
		engine->reset();
		return ship;
	}
	catch(Item::UnknownTypeIDException)
	{
		return nullptr;
	}
}


std::shared_ptr<Structure> Character::setStructure(TypeID typeID)
{
	try
	{
		loadIfNeeded();
		auto engine = getEngine();
		if (!engine)
			return nullptr;

		std::shared_ptr<Structure> structure = std::make_shared<Structure>(engine, typeID, shared_from_this());
		if (structure_)
			removeEffects(Effect::Category::generic);
		structure_ = structure;
		if (structure_)
			addEffects(Effect::Category::generic);
		
		engine->reset();
		return structure_;
	}
	catch(Item::UnknownTypeIDException)
	{
		return nullptr;
	}
}

std::shared_ptr<Structure> Character::getStructure()
{
	return structure_;
}

void Character::reset()
{
	Item::reset();
	if (ship_ != nullptr)
		ship_->reset();
	if (structure_ != nullptr)
		structure_->reset();
	
	//for (const std::pair<int, const std::shared_ptr<Skill>&>& i: skills_)
	for (const auto& i: skills_)
		i.second->reset();
	for (const auto& i: implants_)
		i->reset();
	for (const auto& i: boosters_)
		i->reset();
}

std::shared_ptr<Skill> Character::addSkill(TypeID typeID, int skillLevel, bool isLearned)
{
	try
	{
		auto engine = getEngine();
		if (!engine)
			return nullptr;

		std::shared_ptr<Skill> skill = std::make_shared<Skill>(engine, typeID, skillLevel, isLearned, shared_from_this());
		skills_[typeID] = skill;
//	if (getOwner() && ship_ != nullptr)
		if (ship_ || structure_)
			skill->addEffects(Effect::Category::generic);
		return skill;
	}
	catch(Item::UnknownTypeIDException)
	{
		return nullptr;
	}
}

void Character::removeSkill(std::shared_ptr<Skill> const& skill)
{
//	if (getOwner() && ship_ != NULL)
	if (ship_ || structure_)
		skill->removeEffects(Effect::Category::generic);
	skills_.erase(skill->getTypeID());
}

std::shared_ptr<Skill> Character::getSkill(TypeID typeID)
{
	return skills_[typeID];
}

const SkillsMap& Character::getSkills() {
	return skills_;
}

bool Character::emptyImplantSlot(int slot)
{
	return !getImplant(slot);
}

bool Character::emptyBoosterSlot(int slot)
{
	return !getBooster(slot);
}

std::shared_ptr<Implant> Character::getImplant(int slot)
{
	auto i = std::find_if(implants_.begin(), implants_.end(), [=](std::shared_ptr<Implant> implant) {
		return implant->getSlot() == slot;
	});
	return i != implants_.end() ? *i : nullptr;
}

std::shared_ptr<Booster> Character::getBooster(int slot)
{
	auto i = std::find_if(boosters_.begin(), boosters_.end(), [=](std::shared_ptr<Booster> booster) {
		return booster->getSlot() == slot;
	});
	return i != boosters_.end() ? *i : nullptr;
}

std::shared_ptr<Implant> Character::addImplant(TypeID typeID, bool forced)
{
	try
	{
		auto engine = getEngine();
		if (!engine)
			return nullptr;

		std::shared_ptr<Implant> implant = std::make_shared<Implant>(engine, typeID, shared_from_this());
		std::shared_ptr<Implant> currentImplant = getImplant(implant->getSlot());
		if (currentImplant) {
			if (forced)
				removeImplant(currentImplant);
			else
				return currentImplant;
		}
		implants_.push_back(implant);
		if (ship_)
			implant->addEffects(Effect::Category::generic);
		engine->reset();
		return implant;

	}
	catch(Item::UnknownTypeIDException)
	{
		return NULL;
	}
}

std::shared_ptr<Booster> Character::addBooster(TypeID typeID, bool forced)
{
	try
	{
		auto engine = getEngine();
		if (!engine)
			return nullptr;

		std::shared_ptr<Booster> booster = std::make_shared<Booster>(engine, typeID, shared_from_this());
		std::shared_ptr<Booster> currentBooster = getBooster(booster->getSlot());
		if (currentBooster) {
			if (forced)
				removeBooster(currentBooster);
			else
				return currentBooster;
		}
		boosters_.push_back(booster);
		if (ship_)
			booster->addEffects(Effect::Category::generic);
		engine->reset();
		return booster;
	}
	catch(Item::UnknownTypeIDException)
	{
		return NULL;
	}
}

void Character::removeImplant(std::shared_ptr<Implant> const& implant)
{
	if (implant != NULL)
	{
		if (ship_)
			implant->removeEffects(Effect::Category::generic);
		//implants_.remove(implant);
		implants_.erase(std::find(implants_.begin(), implants_.end(), implant));

		auto engine = getEngine();
		if (engine)
			engine->reset();
	}
}

void Character::removeBooster(std::shared_ptr<Booster> const& booster)
{
	if (booster != NULL)
	{
		if (ship_)
			booster->removeEffects(Effect::Category::generic);
		//boosters_.remove(booster);
		boosters_.erase(std::find(boosters_.begin(), boosters_.end(), booster));

		auto engine = getEngine();
		if (engine)
			engine->reset();
	}
}

const ImplantsList& Character::getImplants()
{
	return implants_;
}

const BoostersList& Character::getBoosters()
{
	return boosters_;
}

void Character::addEffects(Effect::Category category)
{
	if (ship_ || structure_)
	{
		Item::addEffects(category);
		if (category == Effect::Category::generic)
		{
			if (ship_)
				ship_->addEffects(Effect::Category::generic);
			if (structure_)
				structure_->addEffects(Effect::Category::generic);

			for (const auto& i: skills_)
				i.second->addEffects(Effect::Category::generic);
			for (const auto& i: implants_)
				i->addEffects(Effect::Category::generic);
			for (const auto& i: boosters_)
				i->addEffects(Effect::Category::generic);
		}
	}
}

void Character::removeEffects(Effect::Category category)
{
	if (ship_ || structure_)
	{
		Item::removeEffects(category);
		if (category == Effect::Category::generic)
		{
			if (ship_)
				ship_->removeEffects(Effect::Category::generic);
			if (structure_)
				structure_->removeEffects(Effect::Category::generic);

			for (const auto& i: skills_)
				i.second->removeEffects(Effect::Category::generic);
			for (const auto& i: implants_)
				i->removeEffects(Effect::Category::generic);
			for (const auto& i: boosters_)
				i->removeEffects(Effect::Category::generic);
		}
	}
}

void Character::setCharacterName(const char* characterName)
{
	characterName_ = characterName ? characterName  : "";
}

const char*  Character::getCharacterName()
{
	return characterName_.c_str();
}

void Character::setSkillLevels(const std::map<TypeID, int>& levels)
{
	loadIfNeeded();
	auto engine = getEngine();
	if (!engine)
		return;
	
	std::map<TypeID, int>::const_iterator j, endj = levels.end();
	
	for (const auto& i: skills_) {
		j = levels.find(i.first);
		if (j != endj)
			i.second->setSkillLevel(j->second);
		else
			i.second->setSkillLevel(0);
	}
	engine->reset();
}

void Character::setAllSkillsLevel(int level)
{
	loadIfNeeded();
	auto engine = getEngine();
	if (!engine)
		return;
	
	for (const auto& i: skills_)
		i.second->setSkillLevel(level);
	engine->reset();
}

Float Character::getDroneControlDistance() {
	return getAttribute(AttributeID::droneControlDistance)->getValue();
}

std::insert_iterator<ModifiersList> Character::getLocationModifiers(Attribute* attribute, std::insert_iterator<ModifiersList> outIterator)
{
	outIterator = Item::getLocationModifiers(attribute, outIterator);
	auto owner = getOwner();
	if (owner)
		outIterator = owner->getLocationModifiers(attribute, outIterator);
	return outIterator;
}

float Character::getDroneControlRange() {
	return getAttribute(dgmpp::DRONE_CONTROL_DISTANCE_ATTRIBUTE_ID)->getValue();
}

void Character::lazyLoad() {
	auto engine = getEngine();
	if (!engine)
		return;

	Item::lazyLoad();
	
	//std::shared_ptr<FetchResult> result = engine->getSqlConnector()->exec("SELECT typeID FROM invTypes, invGroups WHERE invTypes.groupID = invGroups.groupID AND invGroups.categoryID = 16 AND invTypes.published = 1");
	auto stmt = engine->getSqlConnector()->getReusableFetchRequest("SELECT typeID FROM invTypes, invGroups WHERE invTypes.groupID = invGroups.groupID AND invGroups.categoryID = 16 AND invTypes.published = 1");
	std::shared_ptr<FetchResult> result = engine->getSqlConnector()->exec(stmt);
	while (result->next())
	{
		TypeID skillID = static_cast<TypeID>(result->getInt(0));
		addSkill(skillID, 0, false);
	}
}

Item* Character::character() {
	return this;
}

Item* Character::ship() {
	return getShip().get();
}

Item* Character::structure() {
	return getStructure().get();
}

std::ostream& dgmpp::operator<<(std::ostream& os, dgmpp::Character& character)
{
	os << "{\"typeName\":\"Character\",\"ship\":" << *character.ship_ << ", \"attributes\":[";
	
	if (character.attributes_.size() > 0)
	{
		bool isFirst = true;
		for (const auto& i: character.attributes_)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << *i.second;
		}
	}
	
	os << "], \"effects\":[";
	
	if (character.effects_.size() > 0)
	{
		bool isFirst = true;
		for (const auto& i: character.effects_)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << *i;
		}
	}

	
	os << "], \"itemModifiers\":[";
	
	if (character.itemModifiers_.size() > 0)
	{
		bool isFirst = true;
		for (const auto& list: character.itemModifiers_) {
			for (const auto& i: list.second)
			{
				if (isFirst)
					isFirst = false;
				else
					os << ',';
				os << *i;
			}
		}
	}
	
	os << "], \"locationModifiers\":[";
	
	if (character.locationModifiers_.size() > 0)
	{
		bool isFirst = true;
		for (const auto& list: character.locationModifiers_) {
			for (const auto& i: list.second)
			{
				if (isFirst)
					isFirst = false;
				else
					os << ',';
				os << *i;
			}
		}
	}
	
	os << "], \"locationGroupModifiers\":[";
	
	if (character.locationGroupModifiers_.size() > 0)
	{
		bool isFirst = true;
		for (const auto& map: character.locationGroupModifiers_) {
			for (const auto& list: map.second) {
				for (const auto& i: list.second)
				{
					if (isFirst)
						isFirst = false;
					else
						os << ',';
					os << *i;
				}
			}
		}
	}
	
	os << "], \"locationRequiredSkillModifiers\":[";
	
	if (character.locationRequiredSkillModifiers_.size() > 0)
	{
		bool isFirst = true;
		for (const auto& map: character.locationRequiredSkillModifiers_) {
			for (const auto& list: map.second) {
				for (const auto& i: list.second)
				{
					if (isFirst)
						isFirst = false;
					else
						os << ',';
					os << *i;
				}
			}
		}
	}
	
/*	os << "],\"skills\":[";
	
	if (character.skills_.size() > 0)
	{
		SkillsMap::const_iterator i, end = character.skills_.end();
		bool isFirst = true;
		for (i = character.skills_.begin(); i != end; i++)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << *(i->second);
		}
	}*/

	os << "]}";
	return os;
}

