/*
 *  curveBase.h
 *  Bond
 *
 *  Created by Philip Beadling on 06/08/2007.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef CURVEBASE_H
#define CURVEBASE_H

#include "../../maths/basic/cartesian.h"

#include "../../maths/interpolation/interpolationBase.h"
#include "../../maths/interpolation/interpolationFactory.h"

#include <boost/python.hpp>

class CurveBase
{
	public:
		virtual ~CurveBase() {};
		void bootstrap( const InterpolationFactoryBase& interpolationFactory, double first_x, double last_x, double increment );
		void bootstrap( const InterpolationFactoryBase& interpolationFactory, double increment );
		void bootstrap( InterpolationBase* interpolationScheme, double increment );
		
		// This looks like the neatest way
		// no need for a factory using this.
		// The trick was to make bootstrap non-virtual
		// - this way the compiler allows it.
		template< class INTERPOLATION_T > void bootstrap( double increment )
		{
			interpolatedPoints.clear();
			INTERPOLATION_T interpolationScheme = INTERPOLATION_T( points );
			for( double x = points.front().x; x < points.back().x; x += increment )
				interpolatedPoints.push_back( dCartesian2D( x, interpolationScheme.getInterpolatedRate( x ) ) );
		}
		
		// Kinda defeats the object of all my
		// nice templating work - but for now
		// this simple interface hides the complexity 
		// and will keep Python happy.
		// It also means that the curve base
		// must know about the interpolation method via the
		// includes - which is shit.
		void cubicSplineBootstrap( double increment );
		void dividedDifferenceBootstrap( double increment );

		void printInterpolatedPoints();
		void printPoints();
		boost::python::list pyListInterpolatedPoints();
		boost::python::list pyListOriginalPoints();

		dSetCartesian2D points;
		dSetCartesian2D interpolatedPoints;
};

#endif
