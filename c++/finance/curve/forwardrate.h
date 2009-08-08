/*
 *  forwardrate.h
 *  bootsrapper
 *
 *  Created by Philip Beadling on 01/07/2007.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef FORWARDRATE_H
#define FORWARDRATE_H



#include "curveBase.h"
#include "../instruments/bond/bond.h"

#include <vector>

struct ForwardRate
{
	ForwardRate( const double time, const double rate );
	double time; //x
	double rate; //f(x)
	
};



class ForwardRateCurve : public CurveBase, private QuickSort< Bond >
{
	public:
		ForwardRateCurve( std::vector<Bond>& _bonds );
		//ForwardRateCurve( Bonds& _bonds );
		void sortBondsByMaturity();
	private:
		// Just a referance to the objects in the base class
		std::vector<Bond>& bonds;
};

#endif







