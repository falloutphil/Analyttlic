/*
 *  dividedDifference.h
 *  Bond
 *
 *  Created by Philip Beadling on 23/07/2007.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef DIVIDEDDIFFERENCE_H
#define DIVIDEDDIFFERENCE_H

#include "interpolationBase.h"

#include <vector>

class DividedDifference : public InterpolationBase
{
	public:
		DividedDifference( const dSetCartesian2D& coordinates  );
		virtual double getInterpolatedRate( double x ) const;
	
	private:
		// Our divided difference table
		// First vector is f(x_j), f[x_j,x_j+1], ..... , f[x_j, x_j+1, x_j+2, ...., x_j+n-1]
		// Each of the first vectors contains a vector the result for f[] for x_j (our times) 
		std::vector< std::vector< double > > differenceTable;
};

#endif

