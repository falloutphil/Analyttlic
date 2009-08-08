/*
 *  irSwap.h
 *  Bond
 *
 *  Created by Philip Beadling on 13/08/2007.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef IRSWAP_H
#define IRSWAP_H

#include "../../curve/forwardrate.h"

#include "../bond/bond.h"

class IrSwap
{
	public:
		IrSwap( double start, double end, double tenor );
		void createdFixedLegFromBonds( ForwardRateCurve& forwardRates );
		double fixedLegPv( ForwardRateCurve& forwardRates );
		double floatingLegPv();
		double pv();
		double setFixedRateAtPar();
		
	//private:
		double fixedRate;
		double start;
		double end;
		double tenor;
		std::vector<double> schedule;
		std::vector<Bond> fixedLeg;
	
		
};




#endif

