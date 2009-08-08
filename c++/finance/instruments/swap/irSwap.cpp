/*
 *  irSwap.cpp
 *  Bond
 *
 *  Created by Philip Beadling on 13/08/2007.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */
 
#include "../bond/coupon.h"

#include "irSwap.h"

#include <iostream>
#include <math.h>

using namespace std;

IrSwap::IrSwap( double start, double end, double tenor ) : start ( start ), end ( end ), tenor( tenor )
{
		//Create a payment schedule
		double i = start;
		for( ; i <= end ; i += tenor )
		{
			cout << "\nPush back swap payment at: " << i;
			schedule.push_back( i );
		}
		// i will have been incremented to end+tenor but the 
		// loop will bail at this point without adding this schedule.
		if ( i - end != tenor )
		{
			// start and end dates do match
			// an integer amount of tenors
			// throw an exception - although be careful you're in a contructor!
			cout << "\nERROR: Payment Schedule is not an integer number of tenors, i=" << i;
			return;
		}
		
}

void IrSwap::createdFixedLegFromBonds( ForwardRateCurve& forwardRates )
{
	for ( vector< double >::iterator scheduleIter = schedule.begin(); scheduleIter != schedule.end(); ++scheduleIter )
	{
		std::vector<Coupon> zcbCoupons;
		zcbCoupons.push_back( Coupon( 1, *scheduleIter ) );
		// Calculate ZCB's market price
		// This scaled to 1 but the forward rate
		// is the correct rate to use at time T.
		dSetCartesian2D::iterator pointIter = forwardRates.interpolatedPoints.begin();
		 
		while( (pointIter != forwardRates.interpolatedPoints.end()) && (*scheduleIter > pointIter->x) )	
		{
			++pointIter;
		}
		if ( pointIter == forwardRates.interpolatedPoints.end() )
		{
			//grrrr - we didn't find an appropriate point
			//on our interpolation curve to use to value our ZCB
			cout << "\nERROR: No point on forward rate curve that matches swap payment at: "  << *scheduleIter;
			return;
		}
		// Back one to get the correct foward rate
		// (rate to use is the nearest point BEFORE our maturity)
		--pointIter;
		
		fixedLeg.push_back( Bond(pointIter->y, zcbCoupons ) );
	}
	
}

