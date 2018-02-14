//
//  Route.hpp
//  dgmpp
//
//  Created by Artem Shimanski on 29.11.2017.
//

#pragma once
#include "MetaInfo.hpp"
#include "Commodity.hpp"

namespace dgmpp {
	class Facility;
	
	struct Route {
	public:
		Facility* const from;
		Facility* const to;
		const Commodity commodity;
		
		bool operator== (const Route& other) const noexcept {
			return from == other.from && to == other.to && commodity == other.commodity;
		}
		
		void update(std::chrono::seconds time) const;
	};
}


namespace std {
	template<>
	struct hash<dgmpp::Route> {
		typedef dgmpp::Route argument_type;
		typedef size_t result_type;
		
		result_type operator() (const argument_type& value) const noexcept;
	};
};

