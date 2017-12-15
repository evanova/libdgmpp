#pragma once
#include "types.h"
#include <vector>

namespace dgmpp {
	
	class CapacitorSimulator
	{
	public:
		
		struct State {
			int tNow;
			int duration;
			Float capNeed;
			int reloadTime;
			int reactivationTime;
			int shot;
			int clipSize;
		};

		
		CapacitorSimulator(std::shared_ptr<Ship> const& ship, bool reload, int maxTime);
		virtual ~CapacitorSimulator(void);
		
		void reset();
		
		void setReload(bool reload);
		void setMaxTime(int maxTime);
		
		bool getReload();
		int getMaxTime();
		int getIterations();
		bool isCapStable();
		Float getCapLastsTime();
		Float getCapStableLevel();
		Float getCapUsed();
		Float getCapRecharge();
		
		
	private:
		typedef std::vector<std::shared_ptr<State>> StatesVector;
		
		std::weak_ptr<Ship> ship_;
		
		StatesVector states_;
		
		bool isCalculated_;
		bool reload_;

		int period_;
		int maxTime_;
		Float capacitorRecharge_;
		Float capacitorCapacity_;
		Float capRecharge_;
		Float capUsed_;
		int iterations_;
		int time_;
		Float capStableEVE_;
		Float capStableLow_;
		Float capStableHigh_;
		
		void internalReset();
		void run();
        
        int gcd(int a, int b);
        int lcm(int a, int b);
	};
	
}
