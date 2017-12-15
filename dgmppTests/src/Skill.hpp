//
//  Skill.hpp
//  dgmpp
//
//  Created by Artem Shimanski on 16.11.2017.
//

#pragma once
#include "Type.hpp"

namespace dgmpp {
	
	class Skill: public Type {
	public:
		int level() { return static_cast<int>((*this)[AttributeID::skillLevel]->value()); }
		void level (int level) { *(*this)[AttributeID::skillLevel] = static_cast<Float>(level); }
	protected:
	private:
		friend class Character;
		static std::unique_ptr<Skill> Create (const MetaInfo::Type& metaInfo) { return std::unique_ptr<Skill>(new Skill(metaInfo)); }
		Skill (const MetaInfo::Type& metaInfo) : Type(metaInfo) {};
	};
}
