/*
 *  cubicSpline.h
 *  Bond
 *
 *  Created by Philip Beadling on 29/07/2007.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef CUBICSPLINE_H
#define CUBICSPLINE_H

#include "../matrix/matrix.h"
#include "interpolationBase.h"

#include <vector>

class CubicSpline : public InterpolationBase
{
	public:
		CubicSpline( const dSetCartesian2D& coordinates );
		virtual double getInterpolatedRate( double x ) const;
	
	private:
		std::vector<double> h;
		std::vector<double> twoTimesAdjacentH;
		std::vector<double> d;
		std::vector<double> u;
		std::vector<double> m;
		Matrix augmentedLinearEquations;
		
};

#endif
