#include "Attribute.h"
#include "Engine.h"
#include <algorithm>
#include "Item.h"
#include <limits>
#include <cmath>
#include "Ship.h"
#include "Character.h"
#include <sstream>
#include <functional>

#include "SDE.hpp"
#include <numeric>
#include <array>

using namespace dgmpp;

/*const TypeID dgmpp::IS_ONLINE_ATTRIBUTE_ID = 2;
const TypeID dgmpp::MASS_ATTRIBUTE_ID = 4;
const TypeID dgmpp::CAPACITY_ATTRIBUTE_ID = 38;
const TypeID dgmpp::VOLUME_ATTRIBUTE_ID = 161;
const TypeID dgmpp::RADIUS_ATTRIBUTE_ID = 162;
const TypeID dgmpp::REQUIRED_SKILL1_ATTRIBUTE_ID = 182;
const TypeID dgmpp::REQUIRED_SKILL2_ATTRIBUTE_ID = 183;
const TypeID dgmpp::REQUIRED_SKILL3_ATTRIBUTE_ID = 184;
const TypeID dgmpp::REQUIRED_SKILL4_ATTRIBUTE_ID = 1285;
const TypeID dgmpp::REQUIRED_SKILL5_ATTRIBUTE_ID = 1289;
const TypeID dgmpp::REQUIRED_SKILL6_ATTRIBUTE_ID = 1290;
const TypeID dgmpp::RACE_ID_ATTRIBUTE_ID = 195;
const TypeID dgmpp::SKILL_LEVEL_ATTRIBUTE_ID = 280;
const TypeID dgmpp::IMPLANTNESS_ATTRIBUTE_ID = 331;
const TypeID dgmpp::BOOSTERNESS_ATTRIBUTE_ID = 1087;

const TypeID dgmpp::LOW_SLOTS_ATTRIBUTE_ID = 12;
const TypeID dgmpp::MED_SLOTS_ATTRIBUTE_ID = 13;
const TypeID dgmpp::HI_SLOTS_ATTRIBUTE_ID = 14;
const TypeID dgmpp::RIG_SLOTS_ATTRIBUTE_ID = 1137;
const TypeID dgmpp::MAX_SUBSYSTEMS_SLOTS_ATTRIBUTE_ID = 1367;

const TypeID dgmpp::LAUNCHER_SLOTS_LEFT_ATTRIBUTE_ID = 101;
const TypeID dgmpp::TURRET_SLOTS_LEFT_ATTRIBUTE_ID = 102;

const TypeID dgmpp::FITS_TO_SHIP_TYPE_ATTRIBUTE_ID = 1380;
const TypeID dgmpp::CAN_FIT_SHIP_TYPE1_ATTRIBUTE_ID = 1302;
const TypeID dgmpp::CAN_FIT_SHIP_TYPE2_ATTRIBUTE_ID = 1303;
const TypeID dgmpp::CAN_FIT_SHIP_TYPE3_ATTRIBUTE_ID = 1304;
const TypeID dgmpp::CAN_FIT_SHIP_TYPE4_ATTRIBUTE_ID = 1305;
const TypeID dgmpp::CAN_FIT_SHIP_TYPE5_ATTRIBUTE_ID = 1944;
const TypeID dgmpp::CAN_FIT_SHIP_TYPE6_ATTRIBUTE_ID = 2103;

const TypeID dgmpp::CAN_FIT_SHIP_GROUP1_ATTRIBUTE_ID = 1298;
const TypeID dgmpp::CAN_FIT_SHIP_GROUP2_ATTRIBUTE_ID = 1299;
const TypeID dgmpp::CAN_FIT_SHIP_GROUP3_ATTRIBUTE_ID = 1300;
const TypeID dgmpp::CAN_FIT_SHIP_GROUP4_ATTRIBUTE_ID = 1301;
const TypeID dgmpp::CAN_FIT_SHIP_GROUP5_ATTRIBUTE_ID = 1872;
const TypeID dgmpp::CAN_FIT_SHIP_GROUP6_ATTRIBUTE_ID = 1879;
const TypeID dgmpp::CAN_FIT_SHIP_GROUP7_ATTRIBUTE_ID = 1880;
const TypeID dgmpp::CAN_FIT_SHIP_GROUP8_ATTRIBUTE_ID = 1881;
const TypeID dgmpp::CAN_FIT_SHIP_GROUP9_ATTRIBUTE_ID = 2065;

const TypeID dgmpp::SUBSYSTEM_SLOT_ATTRIBUTE_ID = 1366;
const TypeID dgmpp::RIG_SIZE_ATTRIBUTE_ID = 1547;
const TypeID dgmpp::MAX_GROUP_FITTED_ATTRIBUTE_ID = 1544;

const TypeID dgmpp::CHARGE_SIZE_ATTRIBUTE_ID = 128;
const TypeID dgmpp::CHARGE_GROUP1_ATTRIBUTE_ID = 604;
const TypeID dgmpp::CHARGE_GROUP2_ATTRIBUTE_ID = 605;
const TypeID dgmpp::CHARGE_GROUP3_ATTRIBUTE_ID = 606;
const TypeID dgmpp::CHARGE_GROUP4_ATTRIBUTE_ID = 609;
const TypeID dgmpp::CHARGE_GROUP5_ATTRIBUTE_ID = 610;

const TypeID dgmpp::MAX_GROUP_ACTIVE_ATTRIBUTE_ID = 763;

const TypeID dgmpp::SPEED_ATTRIBUTE_ID = 51;
const TypeID dgmpp::DURATION_ATTRIBUTE_ID = 73;
const TypeID dgmpp::MISSILE_LAUNCH_DURATION_ATTRIBUTE_ID = 506;
const TypeID dgmpp::RELOAD_TIME_ATTRIBUTE_ID = 1795;
const TypeID dgmpp::MODULE_REACTIVATION_DELAY_ATTRIBUTE_ID = 669;

const TypeID dgmpp::CHARGE_RATE_ATTRIBUTE_ID = 56;
const TypeID dgmpp::CRYSTALS_GET_DAMAGED_ATTRIBUTE_ID = 786;

const TypeID dgmpp::HP_ATTRIBUTE_ID = 9;
const TypeID dgmpp::CRYSTAL_VOLATILITY_CHANCE_ATTRIBUTE_ID = 783;
const TypeID dgmpp::CRYSTAL_VOLATILITY_DAMAGE_ATTRIBUTE_ID = 784;
const TypeID dgmpp::CAPACITOR_NEED_ATTRIBUTE_ID = 6;
const TypeID dgmpp::CAPACITOR_BONUS_ATTRIBUTE_ID = 67;
const TypeID dgmpp::POWER_TRANSFER_AMOUNT_ATTRIBUTE_ID = 90;
const TypeID dgmpp::ENERGY_DESTABILIZATION_AMOUNT_ATTRIBUTE_ID = 97;

const TypeID dgmpp::CAPACITOR_CAPACITY_ATTRIBUTE_ID = 482;
const TypeID dgmpp::CHARGE_ATTRIBUTE_ID = 18;
const TypeID dgmpp::RECHARGE_RATE_ATTRIBUTE_ID = 55;

const TypeID dgmpp::DISALLOW_ASSISTANCE_ATTRIBUTE_ID = 854;
const TypeID dgmpp::DISALLOW_OFFENSIVE_MODIFIERS_ATTRIBUTE_ID = 872;

const TypeID dgmpp::EM_DAMAGE_ATTRIBUTE_ID = 114;
const TypeID dgmpp::KINETIC_DAMAGE_ATTRIBUTE_ID = 117;
const TypeID dgmpp::EXPLOSIVE_DAMAGE_ATTRIBUTE_ID = 116;
const TypeID dgmpp::THERMAL_DAMAGE_ATTRIBUTE_ID = 118;
const TypeID dgmpp::DAMAGE_MULTIPLIER_ATTRIBUTE_ID = 64;
const TypeID dgmpp::MISSILE_DAMAGE_MULTIPLIER_ATTRIBUTE_ID = 212;

const TypeID dgmpp::MAX_RANGE_ATTRIBUTE_ID = 54;
const TypeID dgmpp::SHIELD_TRANSFER_RANGE_ATTRIBUTE_ID = 87;
const TypeID dgmpp::POWER_TRANSFER_RANGE_ATTRIBUTE_ID = 91;
const TypeID dgmpp::ENERGY_DESTABILIZATION_RANGE_ATTRIBUTE_ID = 98;
const TypeID dgmpp::EMP_FIELD_RANGE_ATTRIBUTE_ID = 99;
const TypeID dgmpp::ECM_BURST_RANGE_ATTRIBUTE_ID = 142;
const TypeID dgmpp::WARP_SCRAMBLE_RANGE_ATTRIBUTE_ID = 103;
const TypeID dgmpp::CARGO_SCAN_RANGE_ATTRIBUTE_ID = 126;
const TypeID dgmpp::SHIP_SCAN_RANGE_ATTRIBUTE_ID = 125;
const TypeID dgmpp::SURVEY_SCAN_RANGE_ATTRIBUTE_ID = 197;
const TypeID dgmpp::FALLOFF_ATTRIBUTE_ID = 158;
const TypeID dgmpp::FALLOFF_EFFECTIVENESS_ATTRIBUTE_ID = 2044;
const TypeID dgmpp::SHIP_SCAN_FALLOFF_ATTRIBUTE_ID = 510;
const TypeID dgmpp::TRACKING_SPEED_ATTRIBUTE_ID = 160;
const TypeID dgmpp::OPTIMAL_SIG_RADIUS_ATTRIBUTE_ID = 620;

const TypeID dgmpp::MAX_VELOCITY_ATTRIBUTE_ID = 37;
const TypeID dgmpp::EXPLOSION_DELAY_ATTRIBUTE_ID = 281;
const TypeID dgmpp::AGILITY_ATTRIBUTE_ID = 70;

const TypeID dgmpp::ARMOR_DAMAGE_ATTRIBUTE_ID = 266;
const TypeID dgmpp::SHIELD_CHARGE_ATTRIBUTE_ID = 264;
const TypeID dgmpp::DAMAGE_ATTRIBUTE_ID = 3;
const TypeID dgmpp::SHIELD_CAPACITY_ATTRIBUTE_ID = 263;
const TypeID dgmpp::ARMOR_HP_ATTRIBUTE_ID =  265;
const TypeID dgmpp::SHIELD_RECHARGE_RATE_ATTRIBUTE_ID = 479;
const TypeID dgmpp::ARMOR_DAMAGE_AMOUNT_ATTRIBUTE_ID = 84;
const TypeID dgmpp::SHIELD_BONUS_ATTRIBUTE_ID = 68;
const TypeID dgmpp::STRUCTURE_DAMAGE_AMOUNT_ATTRIBUTE_ID = 83;

const TypeID dgmpp::KINETIC_DAMAGE_RESONANCE_ATTRIBUTE_ID = 109;
const TypeID dgmpp::THERMAL_DAMAGE_RESONANCE_ATTRIBUTE_ID = 110;
const TypeID dgmpp::EXPLOSIVE_DAMAGE_RESONANCE_ATTRIBUTE_ID = 111;
const TypeID dgmpp::EM_DAMAGE_RESONANCE_ATTRIBUTE_ID = 113;
const TypeID dgmpp::ARMOR_EM_DAMAGE_RESONANCE_ATTRIBUTE_ID = 267;
const TypeID dgmpp::ARMOR_EXPLOSIVE_DAMAGE_RESONANCE_ATTRIBUTE_ID = 268;
const TypeID dgmpp::ARMOR_KINETIC_DAMAGE_RESONANCE_ATTRIBUTE_ID = 269;
const TypeID dgmpp::ARMOR_THERMAL_DAMAGE_RESONANCE_ATTRIBUTE_ID = 270;
const TypeID dgmpp::SHIELD_EM_DAMAGE_RESONANCE_ATTRIBUTE_ID = 271;
const TypeID dgmpp::SHIELD_EXPLOSIVE_DAMAGE_RESONANCE_ATTRIBUTE_ID = 272;
const TypeID dgmpp::SHIELD_KINETIC_DAMAGE_RESONANCE_ATTRIBUTE_ID = 273;
const TypeID dgmpp::SHIELD_THERMAL_DAMAGE_RESONANCE_ATTRIBUTE_ID = 274;

const TypeID dgmpp::ENTITY_MISSILE_TYPE_ID_ATTRIBUTE_ID = 507;
const TypeID dgmpp::ACTIVATION_BLOCKED_ATTRIBUTE_ID = 1349;

const TypeID dgmpp::UPGRADE_COST_ATTRIBUTE_ID = 1153;
const TypeID dgmpp::UPGRADE_CAPACITY_ATTRIBUTE_ID = 1132;
const TypeID dgmpp::CPU_LOAD_ATTRIBUTE_ID = 49;
const TypeID dgmpp::POWER_LOAD_ATTRIBUTE_ID = 15;
const TypeID dgmpp::POWER_OUTPUT_ATTRIBUTE_ID = 11;
const TypeID dgmpp::CPU_OUTPUT_ATTRIBUTE_ID = 48;
const TypeID dgmpp::DRONE_BANDWIDTH_USED_ATTRIBUTE_ID = 1272;
const TypeID dgmpp::DRONE_BANDWIDTH_ATTRIBUTE_ID = 1271;
const TypeID dgmpp::DRONE_CAPACITY_ATTRIBUTE_ID = 283;
const TypeID dgmpp::BASE_WARP_SPEED_ATTRIBUTE_ID = 1281;
const TypeID dgmpp::WARP_SPEED_MULTIPLIER_ATTRIBUTE_ID = 600;
const TypeID dgmpp::SIGNATURE_RADIUS_ATTRIBUTE_ID = 552;
const TypeID dgmpp::WARP_CAPACITOR_NEED_ATTRIBUTE_ID = 153;
const TypeID dgmpp::MAX_LOCKED_TARGETS_ATTRIBUTE_ID = 192;
const TypeID dgmpp::MAX_TARGET_RANGE_ATTRIBUTE_ID = 76;
const TypeID dgmpp::SCAN_RADAR_STRENGTH_ATTRIBUTE_ID = 208;
const TypeID dgmpp::SCAN_LADAR_STRENGTH_ATTRIBUTE_ID = 209;
const TypeID dgmpp::SCAN_MAGNETOMETRIC_STRENGTH_ATTRIBUTE_ID = 210;
const TypeID dgmpp::SCAN_GRAVIMETRIC_STRENGTH_ATTRIBUTE_ID = 211;
const TypeID dgmpp::MAX_ACTIVE_DRONES_ATTRIBUTE_ID = 352;
const TypeID dgmpp::SCAN_RESOLUTION_ATTRIBUTE_ID = 564;
const TypeID dgmpp::SPECIAL_ORE_HOLD_CAPACITY = 1556;

const TypeID dgmpp::HI_SLOT_MODIFIER_ATTRIBUTE_ID = 1374;
const TypeID dgmpp::MED_SLOT_MODIFIER_ATTRIBUTE_ID = 1375;
const TypeID dgmpp::LOW_SLOT_MODIFIER_ATTRIBUTE_ID = 1376;
const TypeID dgmpp::TURRET_HARD_POINT_MODIFIER_ATTRIBUTE_ID = 1368;
const TypeID dgmpp::LAUNCHER_HARD_POINT_MODIFIER_ATTRIBUTE_ID = 1369;

const TypeID dgmpp::HEAT_ATTENUATION_HI_ATTRIBUTE_ID = 1259;
const TypeID dgmpp::HEAT_ATTENUATION_LOW_ATTRIBUTE_ID = 1262;
const TypeID dgmpp::HEAT_ATTENUATION_MED_ATTRIBUTE_ID = 1261;
const TypeID dgmpp::HEAT_CAPACITY_HI_ATTRIBUTE_ID = 1178;
const TypeID dgmpp::HEAT_CAPACITY_LOW_ATTRIBUTE_ID = 1200;
const TypeID dgmpp::HEAT_CAPACITY_MED_ATTRIBUTE_ID = 1199;
const TypeID dgmpp::HEAT_DISSIPATION_RATE_HI_ATTRIBUTE_ID = 1179;
const TypeID dgmpp::HEAT_DISSIPATION_RATE_LOW_ATTRIBUTE_ID = 1198;
const TypeID dgmpp::HEAT_DISSIPATION_RATE_MED_ATTRIBUTE_ID = 1196;
const TypeID dgmpp::HEAT_GENERATION_MULTIPLIER_ATTRIBUTE_ID = 1224;
const TypeID dgmpp::HEAT_ABSORBTION_RATE_MODIFIER_ATTRIBUTE_ID = 1180;
const TypeID dgmpp::HEAT_DAMAGE_ATTRIBUTE_ID = 1211;

const TypeID dgmpp::POWER_ATTRIBUTE_ID = 30;
const TypeID dgmpp::CPU_ATTRIBUTE_ID = 50;

const TypeID dgmpp::HULL_KINETIC_DAMAGE_RESONANCE_ATTRIBUTE_ID = 976;
const TypeID dgmpp::HULL_THERMAL_DAMAGE_RESONANCE_ATTRIBUTE_ID = 977;
const TypeID dgmpp::HULL_EXPLOSIVE_DAMAGE_RESONANCE_ATTRIBUTE_ID = 975;
const TypeID dgmpp::HULL_EM_DAMAGE_RESONANCE_ATTRIBUTE_ID = 974;

const TypeID dgmpp::MISSILE_ENTITY_VELOCITY_MULTIPLIER_ATTRIBUTE_ID = 645;
const TypeID dgmpp::MISSILE_ENTITY_FLIGHT_TIME_MULTIPLIER_ATTRIBUTE_ID = 646;

const TypeID dgmpp::DRONE_CONTROL_DISTANCE_ATTRIBUTE_ID = 458;

const TypeID dgmpp::CHARGE_ARMOR_DAMAGE_MULTIPLIER_ATTRIBUTE_ID = 1886;

const TypeID dgmpp::TACTICAL_MODES_ATTRIBUTE_ID = 10000;

const TypeID dgmpp::AOE_DAMAGE_REDUCTION_FACTOR_ATTRIBUTE_ID = 1353;
const TypeID dgmpp::AOE_DAMAGE_REDUCTION_SENSITIVITY_ATTRIBUTE_ID = 1354;
const TypeID dgmpp::AOE_CLOUD_SIZE_ATTRIBUTE_ID = 654;
const TypeID dgmpp::AOE_VELOCITY_ATTRIBUTE_ID = 653;
const TypeID dgmpp::ENTITY_FLY_RANGE_ATTRIBUTE_ID = 416;
const TypeID dgmpp::ENTITY_CRUISE_SPEED_ATTRIBUTE_ID = 508;
const TypeID dgmpp::WARP_SCRAMBLE_STRENGTH_ATTRIBUTE_ID = 105;
const TypeID dgmpp::WARP_SCRAMBLE_STRENGTH_HIDDEN_ATTRIBUTE_ID = 1318;

const TypeID dgmpp::ECU_DECAY_FACTOR_ATTRIBUTE_ID = 1683;
const TypeID dgmpp::ECU_NOISE_FACTOR_ATTRIBUTE_ID = 1687;

const TypeID dgmpp::SERVICE_SLOT_ATTRIBUTE_ID = 2056;

const TypeID dgmpp::FIGHTER_ABILITY_EVASIVE_MANEUVERS_EM_RESONANCE_ATTRIBUTE_ID = 2118;
const TypeID dgmpp::FIGHTER_ABILITY_EVASIVE_MANEUVERS_THERM_RESONANCE_ATTRIBUTE_ID = 2119;
const TypeID dgmpp::FIGHTER_ABILITY_EVASIVE_MANEUVERS_KIN_RESONANCE_ATTRIBUTE_ID = 2120;
const TypeID dgmpp::FIGHTER_ABILITY_EVASIVE_MANEUVERS_EXP_RESONANCE_ATTRIBUTE_ID = 2121;
const TypeID dgmpp::FIGHTER_ABILITY_EVASIVE_MANEUVERS_DURATION_ATTRIBUTE_ID = 2123;
const TypeID dgmpp::FIGHTER_ABILITY_MISSILES_EXPLOSION_RADIUS_ATTRIBUTE_ID = 2125;
const TypeID dgmpp::FIGHTER_ABILITY_MISSILES_EXPLOSION_VELOCITY_ATTRIBUTE_ID = 2126;
const TypeID dgmpp::FIGHTER_ABILITY_MISSILES_DAMAGE_MULTIPLIER_ATTRIBUTE_ID = 2130;
const TypeID dgmpp::FIGHTER_ABILITY_MISSILES_DAMAGE_EM_ATTRIBUTE_ID = 2131;
const TypeID dgmpp::FIGHTER_ABILITY_MISSILES_DAMAGE_THERM_ATTRIBUTE_ID = 2132;
const TypeID dgmpp::FIGHTER_ABILITY_MISSILES_DAMAGE_KIN_ATTRIBUTE_ID = 2133;
const TypeID dgmpp::FIGHTER_ABILITY_MISSILES_DAMAGE_EXP_ATTRIBUTE_ID = 2134;
const TypeID dgmpp::FIGHTER_ABILITY_MISSILES_RANGE_ATTRIBUTE_ID = 2149;
const TypeID dgmpp::FIGHTER_ABILITY_MISSILES_DURATION_ATTRIBUTE_ID = 2182;
const TypeID dgmpp::FIGHTER_SQUADRON_IS_LIGHT_ATTRIBUTE_ID = 2212;
const TypeID dgmpp::FIGHTER_SQUADRON_IS_SUPPORT_ATTRIBUTE_ID = 2213;
const TypeID dgmpp::FIGHTER_SQUADRON_IS_HEAVY_ATTRIBUTE_ID = 2214;
const TypeID dgmpp::FIGHTER_SQUADRON_MAX_SIZE_ATTRIBUTE_ID = 2215;
const TypeID dgmpp::FIGHTER_ABILITY_ATTACK_MISSILE_DAMAGE_MULTIPLIER_ATTRIBUTE_ID = 2226;
const TypeID dgmpp::FIGHTER_ABILITY_ATTACK_MISSILE_DAMAGE_EM_ATTRIBUTE_ID = 2227;
const TypeID dgmpp::FIGHTER_ABILITY_ATTACK_MISSILE_DAMAGE_THERM_ATTRIBUTE_ID = 2228;
const TypeID dgmpp::FIGHTER_ABILITY_ATTACK_MISSILE_DAMAGE_KIN_ATTRIBUTE_ID = 2229;
const TypeID dgmpp::FIGHTER_ABILITY_ATTACK_MISSILE_DAMAGE_EXP_ATTRIBUTE_ID = 2230;
const TypeID dgmpp::FIGHTER_ABILITY_ATTACK_MISSILE_REDUCTION_FACTOR_ATTRIBUTE_ID = 2231;
const TypeID dgmpp::FIGHTER_ABILITY_ATTACK_MISSILE_REDUCTION_SENSITIVITY_ATTRIBUTE_ID = 2232;
const TypeID dgmpp::FIGHTER_ABILITY_ATTACK_MISSILE_DURATION_ATTRIBUTE_ID = 2233;
const TypeID dgmpp::FIGHTER_ABILITY_ATTACK_MISSILE_EXPLOSION_RADIUS_ATTRIBUTE_ID = 2234;
const TypeID dgmpp::FIGHTER_ABILITY_ATTACK_MISSILE_EXPLOSION_VELOCITY_ATTRIBUTE_ID = 2235;
const TypeID dgmpp::FIGHTER_ABILITY_ATTACK_MISSILE_RANGE_OPTIMAL_ATTRIBUTE_ID = 2236;
const TypeID dgmpp::FIGHTER_ABILITY_ATTACK_MISSILE_RANGE_FALLOFF_ATTRIBUTE_ID = 2237;
const TypeID dgmpp::FIGHTER_ABILITY_ATTACK_TURRET_DAMAGE_EM_ATTRIBUTE_ID = 2171;
const TypeID dgmpp::FIGHTER_ABILITY_ATTACK_TURRET_DAMAGE_EXP_ATTRIBUTE_ID = 2174;
const TypeID dgmpp::FIGHTER_ABILITY_ATTACK_TURRET_DAMAGE_KIN_ATTRIBUTE_ID = 2173;
const TypeID dgmpp::FIGHTER_ABILITY_ATTACK_TURRET_DAMAGE_MULTIPLIER_ATTRIBUTE_ID = 2178;
const TypeID dgmpp::FIGHTER_ABILITY_ATTACK_TURRET_DAMAGE_THERM_ATTRIBUTE_ID = 2172;
const TypeID dgmpp::FIGHTER_ABILITY_ATTACK_TURRET_DURATION_ATTRIBUTE_ID = 2177;
const TypeID dgmpp::FIGHTER_SQUADRON_ORBIT_RANGE_ATTRIBUTE_ID = 2223;

const TypeID dgmpp::FIGHTER_ABILITY_ATTACK_TURRET_RANGE_FALLOFF_ATTRIBUTE_ID = 2176;
const TypeID dgmpp::FIGHTER_ABILITY_ATTACK_TURRET_RANGE_OPTIMAL_ATTRIBUTE_ID = 2175;
const TypeID dgmpp::FIGHTER_ABILITY_ECM_RANGE_FALLOFF_ATTRIBUTE_ID = 2222;
const TypeID dgmpp::FIGHTER_ABILITY_ECM_RANGE_OPTIMAL_ATTRIBUTE_ID = 2221;
const TypeID dgmpp::FIGHTER_ABILITY_ENERGY_NEUTRALIZER_FALLOFF_RANGE_ATTRIBUTE_ID = 2210;
const TypeID dgmpp::FIGHTER_ABILITY_ENERGY_NEUTRALIZER_OPTIMAL_RANGE_ATTRIBUTE_ID = 2209;
const TypeID dgmpp::FIGHTER_ABILITY_STASIS_WEBIFIER_FALLOFF_RANGE_ATTRIBUTE_ID = 2187;
const TypeID dgmpp::FIGHTER_ABILITY_STASIS_WEBIFIER_OPTIMAL_RANGE_ATTRIBUTE_ID = 2186;
const TypeID dgmpp::FIGHTER_ABILITY_WARP_DISRUPTION_RANGE_ATTRIBUTE_ID = 2204;


const TypeID dgmpp::FIGHTER_CAPACITY_ATTRIBUTE_ID = 2055;
const TypeID dgmpp::FIGHTER_SQUADRON_ROLE_ATTRIBUTE_ID = 2270;

const TypeID dgmpp::FIGHTER_HEAVY_SLOTS_ATTRIBUTE_ID = 2219;
const TypeID dgmpp::FIGHTER_LIGHT_SLOTS_ATTRIBUTE_ID = 2217;
const TypeID dgmpp::FIGHTER_SUPPORT_SLOTS_ATTRIBUTE_ID = 2218;
const TypeID dgmpp::FIGHTER_TUBES_ATTRIBUTE_ID = 2216;

const TypeID dgmpp::SERVICE_MODULE_FUEL_AMOUNT_ATTRIBUTE_ID = 2109;
const TypeID dgmpp::SERVICE_MODULE_FUEL_ONLINE_AMOUNT_ATTRIBUTE_ID = 2110;

const TypeID dgmpp::MAX_TYPE_FITTED_ATTRIBUTE_ID = 2431;

const TypeID dgmpp::MINING_AMOUNT_ATTRIBUTE_ID = 77;
const TypeID dgmpp::SPECIALTY_MINING_AMOUNT_ATTRIBUTE_ID = 789;

const TypeID dgmpp::WARFARE_BUFF1_ID_ATTRIBUTE_ID = 2468;
const TypeID dgmpp::WARFARE_BUFF1_VALUE_ATTRIBUTE_ID = 2469;
const TypeID dgmpp::WARFARE_BUFF2_ID_ATTRIBUTE_ID = 2470;
const TypeID dgmpp::WARFARE_BUFF2_VALUE_ATTRIBUTE_ID = 2471;
const TypeID dgmpp::WARFARE_BUFF3_ID_ATTRIBUTE_ID = 2472;
const TypeID dgmpp::WARFARE_BUFF3_VALUE_ATTRIBUTE_ID = 2473;
const TypeID dgmpp::WARFARE_BUFF4_ID_ATTRIBUTE_ID = 2536;
const TypeID dgmpp::WARFARE_BUFF4_VALUE_ATTRIBUTE_ID = 2537;

const TypeID dgmpp::SCAN_GRAVIMETRIC_STRENGTH_BONUS_ATTRIBUTE_ID = 238;
const TypeID dgmpp::SCAN_LADAR_STRENGTH_BONUS_ATTRIBUTE_ID = 239;
const TypeID dgmpp::SCAN_MAGNETOMETRIC_STRENGTH_BONUS_ATTRIBUTE_ID = 240;
const TypeID dgmpp::SCAN_RADAR_STRENGTH_BONUS_ATTRIBUTE_ID = 241;
const TypeID dgmpp::MISSILE_VELOCITY_BONUS_ATTRIBUTE_ID = 547;
const TypeID dgmpp::EXPLOSION_DELAY_BONUS_ATTRIBUTE_ID = 596;
const TypeID dgmpp::AOE_VELOCITY_BONUS_ATTRIBUTE_ID = 847;
const TypeID dgmpp::FALLOFF_BONUS_ATTRIBUTE_ID = 349;
const TypeID dgmpp::MAX_RANGE_BONUS_ATTRIBUTE_ID = 351;
const TypeID dgmpp::AOE_CLOUD_SIZE_BONUS_ATTRIBUTE_ID = 848;
const TypeID dgmpp::TRACKING_SPEED_BONUS_ATTRIBUTE_ID = 767;
const TypeID dgmpp::MAX_TARGET_RANGE_BONUS_ATTRIBUTE_ID = 309;
const TypeID dgmpp::SCAN_RESOLUTION_BONUS_ATTRIBUTE_ID = 566;
const TypeID dgmpp::SIGNATURE_RADIUS_BONUS_ATTRIBUTE_ID = 554;
const TypeID dgmpp::SENSOR_DAMPENER_RESISTANCE_ATTRIBUTE_ID = 2112;
const TypeID dgmpp::WEAPON_DISRUPTION_RESISTANCE_ATTRIBUTE_ID = 2113;
const TypeID dgmpp::SPEED_FACTOR_ATTRIBUTE_ID = 20;*/


template<typename InputIterator, typename Output>
Output multiply(InputIterator first, InputIterator last, Output value, bool stacking)
{
	if (stacking)
	{
		static std::vector<Float> pExp;
		long n = std::distance(first, last);
		for (long i = pExp.size(); i < n; i++) {
			Float j = i;
			pExp.push_back(std::exp(- j * j / 7.1289));
		}
		for (int i = 0; first != last; first++, i++)
			value *= static_cast<Float>(1.0 + (*first - 1.0) * pExp[i]);
	}
	else
	{
		for (; first != last; first++)
			value *= *first;
	}
	return value;
}

std::shared_ptr<Attribute> Attribute::getAttribute(std::shared_ptr<Engine> const& engine, AttributeID attributeID, std::shared_ptr<Item> const& owner, bool isFakeAttribute, Float value) {
	return std::make_shared<Attribute>(engine, AttributePrototype::getAttributePrototype(engine, attributeID), owner, isFakeAttribute, value);
}

Attribute::Attribute(std::shared_ptr<Engine> const& engine, std::shared_ptr<AttributePrototype> const& prototype, std::shared_ptr<Item> const& owner, bool isFakeAttribute, Float value): engine_(engine), prototype_(prototype), owner_(owner), isFakeAttribute_(isFakeAttribute), value_(value), initialValue_(value), calculated_(false), forcedValue_(std::numeric_limits<Float>::quiet_NaN()) {
	if (std::isnan(value))
		initialValue_ = prototype_->getDefaultValue();
	sync = false;
	reset();
}

Attribute::~Attribute(void)
{
}

std::shared_ptr<Item> Attribute::getOwner() const
{
	return owner_.lock();
}

AttributeID Attribute::getAttributeID() const
{
	return prototype_->getAttributeID();
}

bool Attribute::isFakeAttribute() const
{
	return isFakeAttribute_;
}

Float Attribute::getValue()
{
	auto engine = engine_.lock();
	if (!engine)
		return 0;
	uint32_t generation = engine->getGeneration();
	if (generation_ != generation) {
		calculate();
		generation_ = generation;
	}
	return value_;
}

Float Attribute::getInitialValue() const
{
	return initialValue_;
}

bool Attribute::isStackable() const
{
	return prototype_->isStackable();
}

bool Attribute::highIsGood() const
{
	return prototype_->highIsGood();
}

/*Float Attribute::dec(Float value)
{
	if (std::isnan(forcedValue_))
		forcedValue_ = initialValue_;
	isFakeAttribute_ = false;
	return forcedValue_ -= value;
}

Float Attribute::inc(Float value)
{
	if (std::isnan(forcedValue_))
		forcedValue_ = initialValue_;
	isFakeAttribute_ = false;
	return forcedValue_ += value;
}*/

void Attribute::setValue(Float value)
{
	value_ = value;
	forcedValue_ = value;
	isFakeAttribute_ = false;
}

void Attribute::reset()
{
	generation_ = std::numeric_limits<uint32_t>::max();
	calculated_ = false;
	value_ = initialValue_;
	
	sync = false;
}

void Attribute::calculate()
{
	if (!std::isnan(forcedValue_))
		value_ = forcedValue_;
	else
	{
		auto owner = getOwner();
		if (!owner)
			return;
		if (sync)
		{
			std::cout << "Deadlock: " << prototype_->getAttributeName() << std::endl;
		}
		sync = true;
		value_ = initialValue_;
		
		auto environment = owner;
		//std::shared_ptr<Item> currentCharacter = environment.find("Char") != environment.end() ? environment["Char"] : nullptr;
		Item* currentCharacter = environment->character();
		Ship* ship = dynamic_cast<Ship*>(environment->ship());
		
//		std::shared_ptr<Ship> ship = environment.find("Ship") != environment.end() ? std::dynamic_pointer_cast<Ship>(environment["Ship"]) : nullptr;
		auto attributeID = prototype_->getAttributeID();
		auto highIsGood = prototype_->highIsGood();
		auto isStackable = prototype_->isStackable();
		
		bool isDisallowedAssistance = ship && attributeID != AttributeID::disallowAssistance ? ship->isDisallowedAssistance() : false;
		bool isDisallowedOffensiveModifiers = ship && attributeID != AttributeID::disallowOffensiveModifiers ? ship->isDisallowedOffensiveModifiers() : false;
		
		/*std::list<Float>preAssignments;
		std::list<Float>postAssignments;
		std::list<Float>modAdds;
		std::list<Float>preMultipliers;
		std::list<Float>preMultipliersStackable;
		std::list<Float>preDividersStackable;
		std::list<Float>preMultipliersStackableNegative;
		std::list<Float>preDividersStackableNegative;
		std::list<Float>postMultipliers;
		std::list<Float>postMultipliersStackable;
		std::list<Float>postDividersStackable;
		std::list<Float>postPercentsStackable;
		std::list<Float>postMultipliersStackableNegative;
		std::list<Float>postDividersStackableNegative;
		std::list<Float>postPercentsStackableNegative;*/
		
		std::vector<Float>preAssignments;
		std::vector<Float>postAssignments;
		std::vector<Float>modAdds;
		std::vector<Float>preMultipliers;
		std::vector<Float>preMultipliersStackable;
		std::vector<Float>preDividersStackable;
		std::vector<Float>preMultipliersStackableNegative;
		std::vector<Float>preDividersStackableNegative;
		std::vector<Float>postMultipliers;
		std::vector<Float>postMultipliersStackable;
		std::vector<Float>postDividersStackable;
		std::vector<Float>postPercentsStackable;
		std::vector<Float>postMultipliersStackableNegative;
		std::vector<Float>postDividersStackableNegative;
		std::vector<Float>postPercentsStackableNegative;
		
		//ModifiersList modifiers = owner->getModifiers(shared_from_this());
		ModifiersList modifiers;
		owner->getModifiers(this, std::inserter(modifiers, modifiers.end()));


		
//		ModifiersList::iterator i = modifiers.begin(), end = modifiers.end();
//		if (i != end)
//			isFakeAttribute_ = false;
		if (std::distance(modifiers.begin(), modifiers.end()) > 0)
			isFakeAttribute_ = false;
		for (const auto& i: modifiers)
		{
			Item* character = i->getCharacter();
			bool projected = character && currentCharacter && character != currentCharacter;
			if (projected && ((i->isAssistance() && isDisallowedAssistance) || (i->isOffensive() && isDisallowedOffensiveModifiers)))
				continue;
			
			CategoryID categoryID = i->getModifier()->getOwner()->getCategoryID();
			bool needsStackingCheck = categoryID == CategoryID::module || categoryID == CategoryID::charge || categoryID == CategoryID::drone || categoryID == CategoryID::fighter || categoryID == CategoryID::starbase;
			Float value = i->getValue();
			bool isNegative = (highIsGood && value < 1.0) || (!highIsGood && value > 1.0);

			switch (i->getAssociation()) {
				case Modifier::Association::preAssignment:
					preAssignments.push_back(value);
					break;
				case Modifier::Association::postAssignment:
					postAssignments.push_back(value);
					break;
				case Modifier::Association::modAdd:
				case Modifier::Association::addRate:
					modAdds.push_back(value);
					break;
				case Modifier::Association::modSub:
				case Modifier::Association::subRate:
					modAdds.push_back(-value);
					break;
				case Modifier::Association::preMul:
					if (needsStackingCheck && !isStackable)// && !(*i)->isStackable())
					{
						if (isNegative)
							preMultipliersStackableNegative.push_back(value);
						else
							preMultipliersStackable.push_back(value);
					}
					else
						preMultipliers.push_back(value);
					break;
				case Modifier::Association::preDiv:
					if (needsStackingCheck && !isStackable)// && !(*i)->isStackable())
					{
						if (isNegative)
							preDividersStackableNegative.push_back(value);
						else
							preDividersStackable.push_back(value);
					}
					else
						preMultipliers.push_back(value);
					break;
				case Modifier::Association::postMul:
					if (needsStackingCheck && !isStackable)// && !(*i)->isStackable())
					{
						if (isNegative)
							postMultipliersStackableNegative.push_back(value);
						else
							postMultipliersStackable.push_back(value);
					}
					else
						postMultipliers.push_back(value);
					break;
				case Modifier::Association::postDiv:
					if (needsStackingCheck && !isStackable)// && !(*i)->isStackable())
					{
						if (isNegative)
							postDividersStackableNegative.push_back(value);
						else
							postDividersStackable.push_back(value);
					}
					else
						postMultipliers.push_back(value);
					break;
				case Modifier::Association::postPercent:
					if (needsStackingCheck && !isStackable)// && !(*i)->isStackable())
					{
						if (isNegative)
							postPercentsStackableNegative.push_back(value);
						else
							postPercentsStackable.push_back(value);
					}
					else
						postMultipliers.push_back(value);
					break;
				default:
					break;
			}
		}
		
		if (highIsGood)
		{
			/*preMultipliersStackable.sort(std::greater<Float>());
			preDividersStackable.sort(std::greater<Float>());
			postMultipliersStackable.sort(std::greater<Float>());
			postDividersStackable.sort(std::greater<Float>());
			postPercentsStackable.sort(std::greater<Float>());
			
			preMultipliersStackableNegative.sort(std::less<Float>());
			preDividersStackableNegative.sort(std::less<Float>());
			postMultipliersStackableNegative.sort(std::less<Float>());
			postDividersStackableNegative.sort(std::less<Float>());
			postPercentsStackableNegative.sort(std::less<Float>());*/

			std::sort(preMultipliersStackable.begin(), preMultipliersStackable.end(), std::greater<Float>());
			std::sort(preDividersStackable.begin(), preDividersStackable.end(), std::greater<Float>());
			std::sort(postMultipliersStackable.begin(), postMultipliersStackable.end(), std::greater<Float>());
			std::sort(postDividersStackable.begin(), postDividersStackable.end(), std::greater<Float>());
			std::sort(postPercentsStackable.begin(), postPercentsStackable.end(), std::greater<Float>());

			std::sort(preMultipliersStackableNegative.begin(), preMultipliersStackableNegative.end(), std::less<Float>());
			std::sort(preDividersStackableNegative.begin(), preDividersStackableNegative.end(), std::less<Float>());
			std::sort(postMultipliersStackableNegative.begin(), postMultipliersStackableNegative.end(), std::less<Float>());
			std::sort(postDividersStackableNegative.begin(), postDividersStackableNegative.end(), std::less<Float>());
			std::sort(postPercentsStackableNegative.begin(), postPercentsStackableNegative.end(), std::less<Float>());
		}
		else
		{
			/*preMultipliersStackable.sort(std::less<Float>());
			preDividersStackable.sort(std::less<Float>());
			postMultipliersStackable.sort(std::less<Float>());
			postDividersStackable.sort(std::less<Float>());
			postPercentsStackable.sort(std::less<Float>());

			preMultipliersStackableNegative.sort(std::greater<Float>());
			preDividersStackableNegative.sort(std::greater<Float>());
			postMultipliersStackableNegative.sort(std::greater<Float>());
			postDividersStackableNegative.sort(std::greater<Float>());
			postPercentsStackableNegative.sort(std::greater<Float>());*/

			std::sort(preMultipliersStackable.begin(), preMultipliersStackable.end(), std::less<Float>());
			std::sort(preDividersStackable.begin(), preDividersStackable.end(), std::less<Float>());
			std::sort(postMultipliersStackable.begin(), postMultipliersStackable.end(), std::less<Float>());
			std::sort(postDividersStackable.begin(), postDividersStackable.end(), std::less<Float>());
			std::sort(postPercentsStackable.begin(), postPercentsStackable.end(), std::less<Float>());

			std::sort(preMultipliersStackableNegative.begin(), preMultipliersStackableNegative.end(), std::greater<Float>());
			std::sort(preDividersStackableNegative.begin(), preDividersStackableNegative.end(), std::greater<Float>());
			std::sort(postMultipliersStackableNegative.begin(), postMultipliersStackableNegative.end(), std::greater<Float>());
			std::sort(postDividersStackableNegative.begin(), postDividersStackableNegative.end(), std::greater<Float>());
			std::sort(postPercentsStackableNegative.begin(), postPercentsStackableNegative.end(), std::greater<Float>());
		}
		
		if (preAssignments.size() > 0)
			value_ = preAssignments.front();
		
		for (const auto& j: modAdds)
			value_ += j;
		
		value_ = multiply(preMultipliers.begin(), preMultipliers.end(), value_, false);
		value_ = multiply(preMultipliersStackable.begin(), preMultipliersStackable.end(), value_, true);
		value_ = multiply(preDividersStackable.begin(), preDividersStackable.end(), value_, true);
		value_ = multiply(preMultipliersStackableNegative.begin(), preMultipliersStackableNegative.end(), value_, true);
		value_ = multiply(preDividersStackable.begin(), preDividersStackable.end(), value_, true);
		
		if (postAssignments.size() > 0)
			value_ = postAssignments.front();

		value_ = multiply(postMultipliers.begin(), postMultipliers.end(), value_, false);
		value_ = multiply(postMultipliersStackable.begin(), postMultipliersStackable.end(), value_, true);
		value_ = multiply(postDividersStackable.begin(), postDividersStackable.end(), value_, true);
		value_ = multiply(postPercentsStackable.begin(), postPercentsStackable.end(), value_, true);
		value_ = multiply(postMultipliersStackableNegative.begin(), postMultipliersStackableNegative.end(), value_, true);
		value_ = multiply(postDividersStackableNegative.begin(), postDividersStackableNegative.end(), value_, true);
		value_ = multiply(postPercentsStackableNegative.begin(), postPercentsStackableNegative.end(), value_, true);
		
		auto maxAttributeID = prototype_->getMaxAttributeID();
		if (maxAttributeID != AttributeID::none) {
			Float maxValue = owner->getAttribute(maxAttributeID)->getValue();
			value_ = std::min(value_, maxValue);
		}
//		std::cout << static_cast<int>(attributeID) << ": " << value_ << std::endl;
		sync = false;
		
	}

	calculated_ = true;
}

const char* Attribute::getAttributeName() const
{
	return prototype_->getAttributeName();
}

std::ostream& dgmpp::operator<<(std::ostream& os, dgmpp::Attribute& attribute)
{
	os	<< "{\"attributeName\":\"" << attribute.prototype_->getAttributeName()
		<< "\", \"typeName\":\"" << attribute.getOwner()->getTypeName()
		<< "\", \"attributeID\":\"" << static_cast<int>(attribute.prototype_->getAttributeID())
		<< "\", \"value\":\"" << attribute.getValue()
		<< "\", \"initialValue\":\"" << attribute.getInitialValue()
		<< "\", \"stackable\":\"" << attribute.prototype_->isStackable() << "\"}";
	return os;
}


