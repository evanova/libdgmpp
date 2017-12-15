#pragma once
#include "types.h"
#include <stdexcept>
#if !_M_CEE
#include <mutex>
#endif
#include "SqlConnector.h"
#include "EffectPrototype.h"
#include "AttributePrototype.h"

//#define FACTOR_RELOAD

namespace dgmpp {
	class Engine : public std::enable_shared_from_this<Engine>
	{
	public:
#if !_M_CEE

		class ScopedLock : public std::lock_guard<std::recursive_mutex> {
		public:
			ScopedLock(std::shared_ptr<Engine> const& engine): std::lock_guard<std::recursive_mutex>(engine->mutex_) {
			};
		};
#endif
		
		//struct SqliteException : virtual boost::exception {};
        typedef std::runtime_error SqliteException;

		Engine(std::shared_ptr<SqlConnector> const& sqlConnector);
		virtual ~Engine(void);
		std::shared_ptr<SqlConnector> getSqlConnector() const;
		std::shared_ptr<Area> setArea(TypeID typeID);
		std::shared_ptr<ControlTower> setControlTower(TypeID typeID);
		void clearArea();
		std::shared_ptr<Gang> getGang();
		std::shared_ptr<Area> getArea();
		std::shared_ptr<ControlTower> getControlTower();
		
		std::shared_ptr<Planet> setPlanet(TypeID typeID);
		std::shared_ptr<Planet> getPlanet();
		
		void reset();
		void beginUpdates();
		void commitUpdates();
		
		friend std::ostream& operator<<(std::ostream& os, Engine& engine);
		
		std::map<EffectID, std::shared_ptr<EffectPrototype> >& getReusableEffectPrototypes() {
			return reusableEffectPrototypes_;
		}
		std::map<ModifierID, std::shared_ptr<EffectPrototype::ModifierPrototype> >& getReusableModifierPrototypes() {
			return reusableModifierPrototypes_;
		}
		std::map<AttributeID, std::shared_ptr<AttributePrototype> >& getReusableAttributePrototypes() {
			return reusableAttributePrototypes_;
		}
		
		uint32_t getGeneration() const {
			return generation_;
		}
		
		Float decayFactor() const;
		Float noiseFactor() const;
		
		const std::map<TypeID, CommodityTier>& getCommodityTiers() const;
		
	private:
		std::shared_ptr<SqlConnector> sqlConnector_;
		std::shared_ptr<Gang> gang_;
		std::shared_ptr<Area> area_;
		std::shared_ptr<ControlTower> controlTower_;
		std::shared_ptr<Planet> planet_;
#if !_M_CEE
		std::recursive_mutex mutex_;
#endif		
		std::map<EffectID, std::shared_ptr<EffectPrototype> > reusableEffectPrototypes_;
		std::map<ModifierID, std::shared_ptr<EffectPrototype::ModifierPrototype> > reusableModifierPrototypes_;
		std::map<AttributeID, std::shared_ptr<AttributePrototype> > reusableAttributePrototypes_;
		uint32_t generation_;
		int32_t updatesCounter_;
		mutable Float decayFactor_;
		mutable Float noiseFactor_;
		mutable std::map<TypeID, CommodityTier> commodityTiers_;

	};

}
