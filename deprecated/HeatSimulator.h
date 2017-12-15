#pragma once
#include "types.h"
#include "Module.h"
#include <vector>

namespace dgmpp {
	
	class HeatSimulator
	{
	public:
		struct State {
			int tNow;
			int duration;
			int reloadTime;
			int shot;
			int clipSize;
			int moduleIndex;
			Float heatDamage;
		};

		
		HeatSimulator(std::shared_ptr<Ship> const& ship);
		virtual ~HeatSimulator(void);
		void simulate();
		void reset();
	private:
		std::weak_ptr<Ship> ship_;
		bool isCalculated_;
		typedef std::vector<std::shared_ptr<State>> StatesVector;
		StatesVector states_;

		void simulate(const ModulesList& modules);
		Float heat(Float t, Float heatCapacity, Float heatGeneration);
		Float damageProbability(Float h, int range, int numberOfOnlineModules, int numberOfSlots, Float heatAttenuation);
	};
	
}
