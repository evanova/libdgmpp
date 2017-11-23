//
//  Drone.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 16.11.2017.
//

#include "Drone.hpp"

namespace dgmpp2 {
	
	const Drone::SquadronTag Drone::anySquadronTag = -1;
	
	Drone::Drone (TypeID typeID): Type(typeID) {
		
		if ((*this)[AttributeID::fighterSquadronIsHeavy])
			squadron_ = Squadron::heavy;
		else if ((*this)[AttributeID::fighterSquadronIsLight])
			squadron_ = Squadron::light;
		else if ((*this)[AttributeID::fighterSquadronIsSupport])
			squadron_ = Squadron::support;
		else
			squadron_ = Squadron::none;

		const auto& effects = this->effects();

		flags_.isAssistance = std::any_of(effects.begin(), effects.end(), [](const auto& i) {
			return i->metaInfo().category == MetaInfo::Effect::Category::target && i->metaInfo().isAssistance;
		});
		
		flags_.isOffensive = std::any_of(effects.begin(), effects.end(), [](const auto& i) {
			return i->metaInfo().category == MetaInfo::Effect::Category::target && i->metaInfo().isOffensive;
		});

		auto damageAttributes = {AttributeID::emDamage,
			AttributeID::explosiveDamage,
			AttributeID::kineticDamage,
			AttributeID::thermalDamage,
			AttributeID::fighterAbilityMissilesDamageMultiplier,
			AttributeID::fighterAbilityAttackMissileDamageMultiplier,
			AttributeID::fighterAbilityAttackTurretDamageMultiplier};
		
		flags_.dealsDamage = std::any_of(damageAttributes.begin(), damageAttributes.end(), [&](auto i) {
			return static_cast<bool>((*this)[i]);
		});
		
		flags_.active = true;
		
		if (auto attribute = (*this)[AttributeID::entityMissileTypeID]) {
			auto typeID = static_cast<TypeID>(static_cast<int>(attribute->value()));
			charge_ = Charge::Create(typeID);
			charge_->parent(this);
			
			flags_.isAssistance = flags_.isAssistance || charge_->isAssistance();
			flags_.isOffensive = flags_.isOffensive || charge_->isOffensive();
			flags_.dealsDamage = flags_.dealsDamage || charge_->dealsDamage();
		}
		


		
	}
	
	void Drone::active(bool active) {
		if (flags_.active == active || !isEnabled())
			return;
		
		if (active) {
			activateEffects(MetaInfo::Effect::Category::generic);
			activateEffects(MetaInfo::Effect::Category::target);
			if (charge_ != nullptr)
				charge_->setEnabled(true);
		}
		else {
			deactivateEffects(MetaInfo::Effect::Category::target);
			deactivateEffects(MetaInfo::Effect::Category::generic);
			if (charge_ != nullptr)
				charge_->setEnabled(false);
		}
	}
	
	void Drone::setEnabled (bool enabled) {
		if (isEnabled() == enabled)
			return Type::setEnabled(enabled);
		else
			Type::setEnabled(enabled);
		

		if (enabled && active()) {
			activateEffects(MetaInfo::Effect::Category::generic);
			activateEffects(MetaInfo::Effect::Category::target);
			if (charge_ != nullptr)
				charge_->setEnabled(enabled);
		}
		else {
			deactivateEffects(MetaInfo::Effect::Category::target);
			deactivateEffects(MetaInfo::Effect::Category::generic);
			if (charge_ != nullptr)
				charge_->setEnabled(enabled);
		}
	}
	
	Type* Drone::domain (MetaInfo::Modifier::Domain domain) {
		switch (domain) {
			case MetaInfo::Modifier::Domain::target :
				return nullptr;
			default:
				return Type::domain(domain);
		}
	}
	
	size_t Drone::squadronSize() {
		if (squadron_ == Squadron::none)
			return 5;
		else {
			auto size = static_cast<size_t>((*this)[AttributeID::fighterSquadronMaxSize]->value());
			return size > 0 ? size : 5;
		}
	}
	
	//Calculations
	
	std::chrono::milliseconds Drone::cycleTime() {
		if (auto attribute = (*this)[AttributeID::speed])
			return std::chrono::milliseconds(static_cast<std::chrono::milliseconds::rep>(attribute->value()));
		else if (auto attribute = (*this)[AttributeID::duration])
			return std::chrono::milliseconds(static_cast<std::chrono::milliseconds::rep>(attribute->value()));
		else
			return std::chrono::milliseconds::zero();
	}
	
	DamageVector<HP> Drone::volley() {
		if (active()) {
			auto volley = droneVolley();

			if (auto attribute = (*this)[AttributeID::fighterAbilityAttackMissileDuration]; attribute && attribute->value() > 0)
				volley += fighterAttackMissileVolley();
			if (auto attribute = (*this)[AttributeID::fighterAbilityMissilesDuration]; attribute && attribute->value() > 0)
				volley += fighterMissileVolley();
			if (auto attribute = (*this)[AttributeID::fighterAbilityAttackTurretDuration]; attribute && attribute->value() > 0)
				volley += fighterAttackTurretVolley();
			
			return volley;
		}
		else
			return {0};
	}
	
	DamageVector<HP> Drone::droneVolley() {
		auto volley = DamageVector<HP>(0);
		auto& item = charge_ ? *static_cast<Type*> (charge_.get()) : *static_cast<Type*>(this);
		
		if (auto attribute = item[AttributeID::emDamage])
			volley.emAmount += attribute->value();
		if (auto attribute = item[AttributeID::kineticDamage])
			volley.kineticAmount += attribute->value();
		if (auto attribute = item[AttributeID::thermalDamage])
			volley.thermalAmount += attribute->value();
		if (auto attribute = item[AttributeID::explosiveDamage])
			volley.explosiveAmount += attribute->value();
		if (auto attribute = (*this)[AttributeID::damageMultiplier])
			volley *= attribute->value();

		return volley;
	}
	
	DamageVector<HP> Drone::fighterAttackMissileVolley() {
		auto volley = DamageVector<HP>(0);
		
		if (auto attribute = (*this)[AttributeID::fighterAbilityAttackMissileDamageEM])
			volley.emAmount += attribute->value();
		if (auto attribute = (*this)[AttributeID::fighterAbilityAttackMissileDamageKin])
			volley.kineticAmount += attribute->value();
		if (auto attribute = (*this)[AttributeID::fighterAbilityAttackMissileDamageTherm])
			volley.thermalAmount += attribute->value();
		if (auto attribute = (*this)[AttributeID::fighterAbilityAttackMissileDamageExp])
			volley.explosiveAmount += attribute->value();
		if (auto attribute = (*this)[AttributeID::fighterAbilityAttackMissileDamageMultiplier])
			volley *= attribute->value();

		return volley;
	}
	
	DamageVector<HP> Drone::fighterAttackTurretVolley() {
		auto volley = DamageVector<HP>(0);
		
		if (auto attribute = (*this)[AttributeID::fighterAbilityAttackTurretDamageEM])
			volley.emAmount += attribute->value();
		if (auto attribute = (*this)[AttributeID::fighterAbilityAttackTurretDamageKin])
			volley.kineticAmount += attribute->value();
		if (auto attribute = (*this)[AttributeID::fighterAbilityAttackTurretDamageTherm])
			volley.thermalAmount += attribute->value();
		if (auto attribute = (*this)[AttributeID::fighterAbilityAttackTurretDamageExp])
			volley.explosiveAmount += attribute->value();
		if (auto attribute = (*this)[AttributeID::fighterAbilityAttackTurretDamageMultiplier])
			volley *= attribute->value();
		
		return volley;
	}
	
	DamageVector<HP> Drone::fighterMissileVolley() {
		auto volley = DamageVector<HP>(0);
		
		if (auto attribute = (*this)[AttributeID::fighterAbilityMissilesDamageEM])
			volley.emAmount += attribute->value();
		if (auto attribute = (*this)[AttributeID::fighterAbilityMissilesDamageKin])
			volley.kineticAmount += attribute->value();
		if (auto attribute = (*this)[AttributeID::fighterAbilityMissilesDamageTherm])
			volley.thermalAmount += attribute->value();
		if (auto attribute = (*this)[AttributeID::fighterAbilityMissilesDamageExp])
			volley.explosiveAmount += attribute->value();
		if (auto attribute = (*this)[AttributeID::fighterAbilityMissilesDamageMultiplier])
			volley *= attribute->value();
		
		return volley;
	}

	
	DamagePerSecond Drone::dps(const HostileTarget& target) {
		using namespace std::chrono_literals;
		
		if (active()) {
			auto dps = make_rate(droneVolley(), cycleTime());
			
			if (auto attribute = (*this)[AttributeID::fighterAbilityAttackMissileDuration]; attribute && attribute->value() > 0)
				dps += make_rate(fighterAttackMissileVolley(), std::chrono::milliseconds(static_cast<std::chrono::milliseconds::rep>(attribute->value())));
			if (auto attribute = (*this)[AttributeID::fighterAbilityMissilesDuration]; attribute && attribute->value() > 0)
				dps += make_rate(fighterMissileVolley(), std::chrono::milliseconds(static_cast<std::chrono::milliseconds::rep>(attribute->value())));
			if (auto attribute = (*this)[AttributeID::fighterAbilityAttackTurretDuration]; attribute && attribute->value() > 0)
				dps += make_rate(fighterAttackTurretVolley(), std::chrono::milliseconds(static_cast<std::chrono::milliseconds::rep>(attribute->value())));
			
			
			if (target.signature > 0) {
				auto range = Meter(0);
				if (auto attribute = (*this)[AttributeID::entityFlyRange]; attribute && attribute->value() > 0)
					range = attribute->value();
				else if (auto attribute = (*this)[AttributeID::fighterSquadronOrbitRange]; attribute && attribute->value() > 0)
					range = attribute->value();
				
				auto orbitVelocity = MetersPerSecond(0);
				if (auto attribute = (*this)[AttributeID::entityCruiseSpeed]; attribute && attribute->value() > 0)
					orbitVelocity = make_rate(attribute->value(), 1s);
				else if (auto attribute = (*this)[AttributeID::maxVelocity]; attribute && attribute->value() > 0)
					orbitVelocity = make_rate(attribute->value(), 1s);

				if (target.velocity.count() > 0) {
					auto velocity = this->velocity();
					if (velocity < target.velocity)
						return DamagePerSecond(0);
					
					decltype(velocity) v {std::sqrt(velocity.count() * velocity.count() - target.velocity.count() * target.velocity.count())};
					orbitVelocity = std::min(orbitVelocity, v);
				}
				
				RadiansPerSecond angularVelocity = range > 0 ? make_rate(orbitVelocity * 1s / range, 1s) : RadiansPerSecond(0);
				
				Float a = 0;
				if (angularVelocity.count() > 0) {
					if (auto accuracyScore = this->accuracyScore(); accuracyScore > 0)
						a = angularVelocity * 1s / accuracyScore;
				}

				if (auto signatureResolution = (*this)[AttributeID::optimalSigRadius]; signatureResolution && signatureResolution->value() > 0)
					a = signatureResolution->value() / target.signature;

				Float b = 0;
				if (target.range > 0) {
					auto optimal = this->optimal();
					auto falloff = this->falloff();
					b = falloff > 0 ? std::max(0.0, (range - optimal) / falloff) : 0;
				}

				auto blob = a * a + b * b;
				auto hitChance = std::pow(0.5, blob);
				auto relativeDPS = hitChance > 0.01
					? (hitChance - 0.01) * (0.5 + (hitChance + 0.49)) / 2 + 0.01 * 3
					: hitChance * 3;
				return dps * relativeDPS;
			}
			else
				return dps;
		}
		else
			return DamagePerSecond(0);
	}
	
	Meter Drone::optimal() {
		auto attributes = {
			AttributeID::shieldTransferRange,
			AttributeID::powerTransferRange,
			AttributeID::energyNeutralizerRangeOptimal,
			AttributeID::empFieldRange,
			AttributeID::ecmBurstRange,
			AttributeID::maxRange,
			AttributeID::fighterAbilityAttackMissileRangeOptimal,
			AttributeID::fighterAbilityAttackTurretRangeOptimal,
			AttributeID::fighterAbilityECMRangeOptimal,
			AttributeID::fighterAbilityEnergyNeutralizerOptimalRange,
			AttributeID::fighterAbilityStasisWebifierOptimalRange,
			AttributeID::fighterAbilityWarpDisruptionRange};
		
		for (auto attributeID: attributes) {
			if (auto attribute = (*this)[attributeID])
				return attribute->value();
		}
		
		if (auto charge = this->charge()) {
			auto maxVelocity = (*charge)[AttributeID::maxVelocity];
			auto explosionDelay = (*charge)[AttributeID::explosionDelay];
			
			if (maxVelocity && explosionDelay) {
				rate<Meter, std::chrono::milliseconds> mv = MetersPerSecond(maxVelocity->value());
				auto flightTime = std::chrono::milliseconds(static_cast<std::chrono::milliseconds::rep> (explosionDelay->value()));
				return mv * flightTime;
			}
		}
		return 0;
	}
	
	Meter Drone::falloff() {
		auto attributes = {
			AttributeID::falloff,
			AttributeID::fighterAbilityAttackMissileRangeFalloff,
			AttributeID::fighterAbilityAttackTurretRangeFalloff,
			AttributeID::fighterAbilityECMRangeFalloff,
			AttributeID::fighterAbilityEnergyNeutralizerFalloffRange,
			AttributeID::fighterAbilityStasisWebifierFalloffRange};

		for (auto attributeID: attributes) {
			if (auto attribute = (*this)[attributeID])
				return attribute->value();
		}
		return 0;
	}
	
	Points Drone::accuracyScore() {
		if (auto attribute = (*this)[AttributeID::trackingSpeed])
			return attribute->value();
		else
			return 0;
	}
	
	CubicMeterPerSecond Drone::miningYield() {
		if (active()) {
			CubicMeter volley = 0;
			if (auto attribute = (*this)[AttributeID::specialtyMiningAmount])
				volley += attribute->value();
			if (auto attribute = (*this)[AttributeID::miningAmount])
				volley += attribute->value();
			return make_rate(volley, cycleTime());
		}
		else
			return CubicMeterPerSecond(0.0);
	}
	
	MetersPerSecond Drone::velocity() {
		using namespace std::chrono_literals;
		return make_rate((*this)[AttributeID::maxVelocity]->value(), 1s);
	}

}
