/*
 *  interporlationBase.h
 *  Bond
 *
 *  Created by Philip Beadling on 05/08/2007.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef INTERPOLATIONBASE_H
#define INTERPOLATIONBASE_H

#include "../basic/cartesian.h"

class InterpolationBase
{
	public:
		virtual double getInterpolatedRate( double x ) const =0;
		virtual ~InterpolationBase() {};
	protected:
		InterpolationBase( const dSetCartesian2D& coordinates );
		const dSetCartesian2D& coordinates;

};



#endif

