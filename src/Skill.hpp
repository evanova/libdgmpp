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
		int level() { LOCK(this); return level_(); }
		void level (int level) { LOCK(this); level_(level); }
	protected:
	private:
		friend class Character;
		static std::unique_ptr<Skill> Create (const MetaInfo::Type& metaInfo) { return std::unique_ptr<Skill>(new Skill(metaInfo)); }
		static std::unique_ptr<Skill> Create (const Skill& other) { return std::unique_ptr<Skill>(new Skill(other)); }
		Skill (const MetaInfo::Type& metaInfo) : Type(metaInfo) {};
		Skill (const Skill& other) : Type(other) {};
		
		int level_() { return static_cast<int>(attribute_(AttributeID::skillLevel)->value_()); }
		void level_ (int level) { *attribute_(AttributeID::skillLevel) = static_cast<Float>(level); }

	};
}
