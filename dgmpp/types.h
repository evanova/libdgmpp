#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <memory>
#include <string>
#include <map>
#include <list>
#include <iterator>
#include <set>
#include <memory>
#include <cassert>
#include <vector>
#include "AttributeID.hpp"
#include "CategoryID.hpp"
#include "GroupID.hpp"
#include "TypeID.hpp"
#include "EffectID.hpp"

namespace dgmpp {
//	typedef int TypeID;
	
	enum class RaceID: int {
		none = 0,
		caldari = 1,
		minmatar = 2,
		amarr = 4,
		gallente = 8
		};
		
	typedef int ModifierID;
	typedef int SchematicID;

	typedef double Float;

	class Item;
	class Attribute;
	class Effect;
	class EffectPrototype;
	class Ship;
	class Module;
	class Gang;
	class Engine;
	class Character;
	class Area;
	class Skill;
	class Implant;
	class Booster;
	class Modifier;
	class LocationGroupModifier;
	class LocationRequiredSkillModifier;
	class Charge;
	class Drone;
	class EffectInterpreter;
	class ControlTower;
	class StarbaseStructure;
	class Environment;
	
	class Planet;
	class Facility;
	class CommandCenter;
	class Route;
	class Commodity;
	
	class Structure;
	class Cargo;
	
	class GangBoost;
	
	typedef std::map<AttributeID, std::shared_ptr<Attribute>> AttributesMap;
	typedef std::list<std::shared_ptr<Effect> > EffectsList;
	typedef std::vector<std::shared_ptr<Module>> ModulesList;
	typedef std::list<std::shared_ptr<Drone>> DronesList;
	typedef std::list<std::shared_ptr<Character>> CharactersList;
	typedef std::map<TypeID, std::shared_ptr<Skill>> SkillsMap;
	typedef std::list<std::shared_ptr<Implant>> ImplantsList;
	typedef std::list<std::shared_ptr<Booster>> BoostersList;
	typedef std::list<std::shared_ptr<Modifier>> ModifiersList;
	typedef std::list<std::shared_ptr<StarbaseStructure>> StarbaseStructuresList;
	typedef std::list<std::shared_ptr<Cargo>> CargoList;
	
//	typedef TypeID GroupID;
//	typedef TypeID SkillID;

	typedef std::map<AttributeID, ModifiersList> ItemModifiers;
	typedef ItemModifiers LocationModifiers;
	typedef std::map<TypeID, ItemModifiers> LocationRequiredSkillModifiers;
	typedef std::map<GroupID, ItemModifiers> LocationGroupModifiers;
	
	typedef std::list<std::shared_ptr<Facility>> FacilitiesList;
	typedef std::list<std::shared_ptr<const Route>> RoutesList;

	struct Tank
	{
		union {
			struct {
				Float passiveShield;
				Float shieldRepair;
				Float armorRepair;
				Float hullRepair;
			};
			Float layers[4];
		};
	};
	
	struct HitPoints
	{
		union {
			struct {
				Float shield;
				Float armor;
				Float hull;
			};
			Float layers[3];
		};
	};

	struct ResistancesLayer
	{
		union {
			struct {
				Float em;
				Float thermal;
				Float kinetic;
				Float explosive;
			};
			Float resistances[4];
		};
	};
	
	struct Resistances
	{
		union {
			struct {
				ResistancesLayer shield, armor, hull;
			};
			ResistancesLayer layers[3];
		};
	};
	
	enum CommodityTier {
		TIER_UNKNOWN = -1,
		TIER_RAW,
		TIER1,
		TIER2,
		TIER3,
		TIER4
	};
}

namespace dgmpp2 {
	using Float = double;
	using TypeID = dgmpp::TypeID;
	using GroupID = dgmpp::GroupID;
	using CategoryID = dgmpp::CategoryID;
	using AttributeID = dgmpp::AttributeID;
	using EffectID = dgmpp::EffectID;
	using ModifierID = dgmpp::ModifierID;
	using SchematicID = dgmpp::SchematicID;
	
	template <typename T> struct optional {
		optional(T* ptr) : value_(ptr) {}
		optional(const T& value) : value_(new T(value)) {}
		optional(optional&& other) = default;
		optional(const optional& other) = delete;
		optional& operator=(optional&& other) = default;
		optional& operator=(const optional& other) = delete;
		
		optional& operator=(const T& value) {
			value_ = std::unique_ptr<T>(new T(value));
			return *this;
		}
		
		optional& operator=(std::nullptr_t) {
			value_.reset(nullptr);
			return *this;
		}

		operator bool() const {return value_ != nullptr;}
		
		T& value() {
			if (value_ == nullptr) {
				throw std::runtime_error("Dereferencing empty optional");
			}
			return *value_;
		}
		
		T& operator*() {
			return value();
		}
		
		T& operator->() {
			return value();
		}
		
		const T& value() const {
			if (value_ == nullptr) {
				throw std::runtime_error("Dereferencing empty optional");
			}
			return *value_;
		}
		
		const T& operator*() const {
			return value();
		}
		
		const T& operator->() const {
			return value();
		}


	private:
		std::unique_ptr<T> value_;
	};
	
	static auto nullopt = nullptr;
	
	template <typename T> optional<T> make_optional(T&& t) {
		return optional<T>(std::forward<T>(t));
	}

	template <typename T> class ref {
	public:
		constexpr ref(T& ref) : ref_(ref) {}
		
		constexpr operator T&() const noexcept {
			return ref_;
		}
		
		constexpr T& get() const noexcept {
			return ref_;
		}
	private:
		T& ref_;
	};
	
	class Type;
	
}
