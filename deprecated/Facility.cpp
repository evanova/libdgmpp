//
//  Facility.cpp
//  dgmpp
//
//  Created by Артем Шиманский on 13.01.16.
//
//

#include "Facility.h"
#include <cmath>
#include "Planet.h"
#include "Route.h"
#include <sstream>

using namespace dgmpp;

bool dgmpp::operator == (const std::list<std::shared_ptr<const Commodity>>& left, const std::list<std::shared_ptr<const Commodity>>& right) {
	if (left.size() == right.size()) {
		if (left.size() > 0) {
			bool e = false;
			for (const auto& a: left) {
				for (const auto& b: right) {
					if (*a == *b) {
						e = true;
						break;
					}
				}
				if (!e)
					return false;
			}
			return true;
		}
		else
			return true;
	}
	else
		return false;
}

bool dgmpp::operator != (const std::list<std::shared_ptr<const Commodity>>& left, const std::list<std::shared_ptr<const Commodity>>& right) {
	return !(left == right);
}

Facility::Facility(TypeID typeID, const std::string& typeName, double capacity, std::shared_ptr<Planet> const& owner, int64_t identifier): typeID_(typeID), typeName_(typeName), capacity_(capacity), owner_(owner), identifier_(identifier) {
}

void Facility::addInput(const std::shared_ptr<const Route>& route) {
	inputs_.push_back(route);
}

void Facility::addOutput(const std::shared_ptr<const Route>& route) {
	outputs_.push_back(route);
}

void Facility::removeInput(const std::shared_ptr<const Route>& route) {
	inputs_.remove(route);
}

void Facility::removeOutput(const std::shared_ptr<const Route>& route) {
	outputs_.remove(route);
}


double Facility::getNextUpdateTime() const {
	return std::numeric_limits<double>::infinity();
}


void Facility::addCommodity(const Commodity& commodity) {
	auto i = commodities_.find(commodity.getTypeID());
	if (i != commodities_.end())
		i->second->add(commodity.getQuantity());
	else
		commodities_[commodity.getTypeID()] = std::make_shared<Commodity>(commodity);
	
	auto j = incomming_.find(commodity.getTypeID());
	if (j != incomming_.end())
		j->second->add(commodity.getQuantity());
	else
		incomming_[commodity.getTypeID()] = std::make_shared<Commodity>(commodity);
}

void Facility::addCommodity(TypeID typeID, uint32_t quantity) {
	addCommodity(Commodity(getOwner()->getEngine(), typeID, quantity));
}

void Facility::extractCommodity(const Commodity& commodity) {
	auto i = commodities_.find(commodity.getTypeID());
	if (i != commodities_.end())
		i->second->extract(commodity.getQuantity());
	else
		throw Commodity::NotEnoughCommodities(std::to_string(-commodity.getQuantity()));
}

const Commodity& Facility::getCommodity(const Commodity& commodity) const {
	auto i = commodities_.find(commodity.getTypeID());
	if (i != commodities_.end())
		return *i->second;
	else {
		auto c = std::make_shared<Commodity>(commodity, 0);
		commodities_[commodity.getTypeID()] = c;
		return *c;
	}
}

const Commodity& Facility::getIncomming(const Commodity& commodity) const {
	auto i = incomming_.find(commodity.getTypeID());
	if (i != incomming_.end())
		return *i->second;
	else {
		auto c = std::make_shared<Commodity>(commodity, 0);
		incomming_[commodity.getTypeID()] = c;
		return *c;
	}
}

std::list<const Commodity> Facility::getCommodities() const {
	std::list<const Commodity> list;
	for (const auto& commodity: commodities_) {
		if (commodity.second->getQuantity() > 0)
			list.push_back(*commodity.second);
	}
	return list;
}

void Facility::clear() {
	commodities_.clear();
}

uint32_t Facility::getFreeStorage(const Commodity& commodity) const {
	double itemVolume = commodity.getItemVolume();
	if (itemVolume > 0) {
		double free = getFreeVolume();
		return std::trunc(free / itemVolume);
	}
	else
		return std::numeric_limits<int32_t>::max();
}

double Facility::getFreeVolume() const {
	return getCapacity() - getVolume();
}

double Facility::getVolume() const {
	double volume = 0;
	for (auto commodity: commodities_)
		volume += commodity.second->getVolume();
	return volume;
}


std::shared_ptr<const State> Facility::getState(double timestamp) const {
	std::shared_ptr<const State> lastState;
	for (const auto& state: states_) {
		if (state->getTimestamp() > timestamp)
			return lastState;
		lastState = state;
	}
	return nullptr;
}

void Facility::update(double time) {
	for (const auto& output: getOutputs())
		output->update(time);
}

std::string Facility::getFacilityName() const {
	if (identifier_ > 0 && facilityName_.length() == 0) {
		std::string baseStr = "123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		int len = static_cast<int>(baseStr.length()) - 1;
		std::string pinName;

		for (int i = 0; i < 5; i++) {
			int at = static_cast<int64_t>((identifier_ / pow(len, i))) % len;
			if (i == 2)
				pinName += '-';
			pinName += baseStr.at(at);
		}
		facilityName_ = pinName;
	}
	else if (identifier_ == 0)
		return typeName_;
	
	return facilityName_;
}


std::string Facility::toJSONString() const {
	std::stringstream os;
	os << "\"typeName\":\"" << getTypeName() << "\",";
	if (getCapacity() > 0)
		os << "\"free\":" << getFreeVolume() << ",";
	os << "\"commodities\":[";
	bool isFirst = true;
	for (const auto& commodity: commodities_) {
		if (commodity.second->getQuantity() > 0) {
			if (isFirst)
				isFirst = false;
			else
				os << "," << std::endl;;
			os << *commodity.second;
		}
	}
	os << "],";
	os << "\"states\":[";
	isFirst = true;
	for (const auto& state: states_) {
		if (isFirst)
			isFirst = false;
		else
			os << "," << std::endl;;
		os << *state;
	}
	
	os << "]" << std::endl;
	return os.str();
}

std::ostream& dgmpp::operator<<(std::ostream& os, const Facility& facility) {
	return os << "{" << facility.toJSONString() << "}" << std::endl;
}
