#pragma once
#include "Modifier.h"

namespace eufe {
	
	class LocationRequiredSkillModifier : public Modifier
	{
	public:
		LocationRequiredSkillModifier(TypeID attributeID, Association association, std::shared_ptr<Attribute> const& modifier, TypeID skillID, bool isAssistance, bool isOffensive, std::shared_ptr<Character> const& character = nullptr);
		virtual ~LocationRequiredSkillModifier(void);
		virtual bool isMatch(std::shared_ptr<Item> const& item) const;
		TypeID getSkillID() const {return skillID_;}

		friend std::ostream& operator<<(std::ostream& os, LocationRequiredSkillModifier& modifier);

	private:
		TypeID skillID_;
	};
	
}