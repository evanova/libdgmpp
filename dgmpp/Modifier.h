#pragma once
#include "types.h"
#include "MetaInfo.hpp"

namespace dgmpp {
	
	class Modifier
	{
	public:
		
		enum class Domain {
			self,
			character,
			ship,
			gang,
			area,
			target,
			other,
			structure
		};
		
		enum class Association {
			preAssignment,
			modAdd,
			modSub,
			preDiv,
			preMul,
			postPercent,
			postDiv,
			postMul,
			postAssignment,
			skillTime,
			addRate,
			subRate
		};
		
		enum Type {
			item,
			location,
			locationGroup,
			locationRequiredSkill,
			ownerRequiredSkill,
			locationRequiredDomainSkill,
		};
		
		Modifier(Domain domain, AttributeID attributeID, Association association, std::shared_ptr<Attribute> const& modifier, bool isAssistance, bool isOffensive, Character* character = nullptr);
		virtual ~Modifier(void);
		virtual bool isMatch(Item* item) const;
		Domain getDomain();
		AttributeID getAttributeID() const;
		std::shared_ptr<Attribute> getModifier() const;
		Association getAssociation() const;
		Float getValue() const;
		//		bool isStackable() const;
		Character* getCharacter();
		bool isOffensive();
		bool isAssistance();
		
		std::string getAssociationName();
		friend std::ostream& operator<<(std::ostream& os, Modifier& modifier);
		
		virtual std::string print();
		
	private:
		AttributeID attributeID_;
		Domain domain_;
		std::weak_ptr<Attribute> modifier_;
		Association association_;
		Character* character_;
		bool isOffensive_;
		bool isAssistance_;
	};
	
}

namespace dgmpp2 {
	class Type;
	class Attribute;
	class Effect;
	
	class Modifier {
	public:
		Modifier (const MetaInfo::Modifier& metaInfo, Type& owner, const Effect& effect);
		Modifier (const Modifier& other) = delete;
		Modifier (Modifier&& other) = delete;
		Modifier& operator= (const Modifier& other) = delete;
		Modifier& operator= (Modifier&& other) = delete;
		virtual ~Modifier() = default;
		
		const MetaInfo::Modifier& metaInfo() const { return metaInfo_; }
		Type& owner() const { return owner_; }
		Type* domain() const;
		const Effect& effect() const { return effect_; }
		
		bool match(const Type* type) const;
		Float get() const;
		operator Float() const { return get(); }
		bool needsStackingCheck() const { return needsStackingCheck_; }
		
	private:
		friend class Effect;
		
		const MetaInfo::Modifier&	metaInfo_;
		Type&				owner_;
		const Effect&		effect_;
		const Attribute&	modifyingAttribute_;
		bool				needsStackingCheck_;
		
	};	
}

