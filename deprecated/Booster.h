#pragma once
#include "types.h"
#include "Item.h"

namespace dgmpp {
	
	class Booster : public Item
	{
	public:
		Booster(std::shared_ptr<Engine> const& engine, TypeID typeID, std::shared_ptr<Character> const& owner);
		virtual ~Booster(void);
		std::shared_ptr<Booster> shared_from_this() {
			return std::static_pointer_cast<Booster>(Item::shared_from_this());
		}
		int getSlot();
		
		virtual Item* character();
		virtual Item* ship();
	protected:
		virtual void lazyLoad();

	private:
		int slot_;
		
	};
	
}