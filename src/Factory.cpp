//
//  Factory.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 29.11.2017.
//

#include "Factory.hpp"
#include "SDE.hpp"
#include "Planet.hpp"

namespace dgmpp {
	
	bool Factory::configured() const {
		if (auto product = output()) {
			auto isOutputRouted = std::any_of(outputs_.begin(), outputs_.end(), [typeID = product->metaInfo().typeID](const auto& i) {
				return i.commodity.metaInfo().typeID == typeID;
			});
			if (isOutputRouted) {
				auto required = schematicValue_->inputs();
				return std::all_of(required.begin(), required.end(), [&](const auto& i) {
					return std::any_of(inputs_.begin(), inputs_.end(), [typeID = i.first->typeID](const auto& j) {
						return j.commodity.metaInfo().typeID == typeID;
					});
				});
			}
		}
		return false;
	}
	
	std::optional<Commodity> Factory::output() const {
		if (schematicValue_)
			return {Commodity(*schematicValue_->output.first, schematicValue_->output.second)};
		else
			return std::nullopt;
	}
	
	Commodity Factory::free(const Commodity& key) noexcept {
		if (!schematicValue_) {
			auto output = key;
			output = 0;
			return output;
		}
		
		auto inputs = schematicValue_->inputs();
		auto i = std::find_if(inputs.begin(), inputs.end(), [typeID = key.metaInfo().typeID](const auto& i) {
			return i.first->typeID == typeID;
		});
		
		auto output = key;
		if (i == inputs.end()) {
			output = 0;
		}
		else {
			output = std::max(i->second - (*this)[key].quantity(), std::size_t(0));
		}
		return output;
	}
	
	void Factory::schematic(SchematicID schematicID) {
		schematicValue_ = &SDE::get(schematicID);
	}
	
	int Factory::priority_() const noexcept {
		return schematicValue_ ? static_cast<int>(schematicValue_->output.first->tier) : 0;
	}
	
	std::optional<std::chrono::seconds> Factory::cycleTime() const {
		if (schematicValue_)
			return schematicValue_->cycleTime;
		else
			return std::nullopt;
	}
	
	std::optional<std::chrono::seconds> Factory::nextUpdateTime_() const noexcept {
		if (production_)
			return production_->end();
		else if (states_.empty()) {
			if ((launchTime_ + *cycleTime()) < planet().lastUpdate())
				return planet().lastUpdate();
			else
				return launchTime_;
		}
		else
			return std::nullopt;
	}
	
	void Factory::update_(std::chrono::seconds time) {
		if (updating_ || !configured())
			return;
		updating_ = true;
		
		/*
		 Измнение состояния:
		 	- Новый цикл производства
		 	- Поступление материалов
		 */
		
		auto isStateChanged = states_.empty();

		//Завершение текущего цикла производства
		if (production_) {
			const auto isCycleFinished = production_->end() == time;
			if (isCycleFinished) {
				finishCycle_(*production_, time);
				production_ = nullptr;
				isStateChanged = true;
			}
		}
		
		//Старт нового цикла производства
		if (!production_) {
			if (auto cycle = startCycle_(time)) {
				production_ = cycle;
				isStateChanged = true;
			}
		}
		
		auto materials = commodities();

		//Поступление новых материалов
		if (!isStateChanged) {
			auto last = *states_.back();
			if (last.timestamp < time && last.commodities != materials)
				isStateChanged = true;
		}
		
		if (isStateChanged)
			states_.emplace_back(new ProductionState(time, production_, 0));
		
		states_.back()->efficiency = percentage(productionTime_, (time - startTime_));
		states_.back()->commodities = std::move(materials);
		
		updating_ = false;
	}
	
	void Factory::finishCycle_(ProductionCycle& cycle, std::chrono::seconds time) {
		auto product = *output();
		
		add(product);
		Facility::update_(time);
		auto left = (*this)[product];
		cycle.yield = product - left;
		cycle.waste = left;
		if (left.quantity() > 0)
			extract(left);

		productionTime_ += cycle.duration;
//		launchTime_ = std::nullopt;
		
		
//		states_.emplace_back(new ProductionState(time, std::nullopt, productionTime_ / (time - *startTime_)));
	}
	
	ProductionCycle* Factory::startCycle_(std::chrono::seconds time) {
		if (states_.empty()) {
			if (launchTime_ + *cycleTime() < planet().lastUpdate()) {
				if (time != planet().lastUpdate())
					return nullptr;
			}
			else if (time != launchTime_)
				return nullptr;
			
			if (launchTime_.count() < 0) {
				auto product = *output();
				return cycles_.emplace_back(new ProductionCycle{time, *cycleTime(), product, product}).get();
			}
		}
		
		auto required = schematicValue_->inputs();
		auto available = commodities();
		
		auto equal = required.size() == available.size() && std::equal(required.begin(), required.end(), available.begin(), [](const auto& a, const auto& b) {
			return a.first->typeID == b.metaInfo().typeID && a.second == b.quantity();
		});
		
		if (equal) {
			if (cycles_.empty())
				startTime_ = time;

			auto product = *output();
			commodities_.clear();
			
			//Забрать материалы со склада
			for (const auto& i: inputs_)
				i.from->update_(time);
			return cycles_.emplace_back(new ProductionCycle{time, *cycleTime(), product, product}).get();
		}
		else
			return nullptr;

	}

}
