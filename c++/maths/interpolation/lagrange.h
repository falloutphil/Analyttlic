/*
 *  lagrange.h
 *  Bond
 *
 *  Created by Philip Beadling on 22/07/2007.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef LAGRANGE_H
#define LAGRANGE_H

#include "interpolationBase.h"

#include <vector>

class Lagrange : public InterpolationBase
{
	public:
		Lagrange( const dSetCartesian2D& coordinates );
		virtual double getInterpolatedRate( double x ) const;
};

#endif

