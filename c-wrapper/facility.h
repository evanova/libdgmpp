//
//  facility.h
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

#ifndef facility_h
#define facility_h

#include "utility.h"
#include <stdio.h>

DGMPP_EXTERN void dgmpp_facility_free (dgmpp_facility_ptr facility);

DGMPP_EXTERN dgmpp_type_id		dgmpp_facility_get_type_id		(dgmpp_facility_ptr facility);
DGMPP_EXTERN dgmpp_group_id		dgmpp_facility_get_group_id		(dgmpp_facility_ptr facility);
DGMPP_EXTERN dgmpp_cubic_meter	dgmpp_facility_get_capacity		(dgmpp_facility_ptr facility);
DGMPP_EXTERN dgmpp_cubic_meter	dgmpp_facility_get_free_volume	(dgmpp_facility_ptr facility);
DGMPP_EXTERN dgmpp_cubic_meter	dgmpp_facility_get_used_volume	(dgmpp_facility_ptr facility);

DGMPP_EXTERN dgmpp_commodity	dgmpp_facility_get_free				(dgmpp_facility_ptr facility, dgmpp_type_id commodity_id);
DGMPP_EXTERN void				dgmpp_facility_add_commodity		(dgmpp_facility_ptr facility, dgmpp_commodity commodity);
DGMPP_EXTERN BOOL				dgmpp_facility_extract_commodity	(dgmpp_facility_ptr facility, dgmpp_commodity commodity);

DGMPP_EXTERN dgmpp_commodities_array_ptr	dgmpp_facility_get_commodities	(dgmpp_facility_ptr facility);
DGMPP_EXTERN dgmpp_commodity				dgmpp_facility_get_commodity	(dgmpp_type_id type_id);
DGMPP_EXTERN dgmpp_commodity				dgmpp_facility_get_income		(dgmpp_type_id type_id);

DGMPP_EXTERN BOOL dgmpp_facility_is_configured (dgmpp_type_id type_id);

#endif /* facility_h */
