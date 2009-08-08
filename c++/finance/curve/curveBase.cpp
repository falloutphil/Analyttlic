/*
 *  curveBase.cpp
 *  Bond
 *
 *  Created by Philip Beadling on 06/08/2007.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#include "curveBase.h"

// Grr grr grr - needed to hide complexity from
// python for now.
#include "../../maths/interpolation/cubicSpline.h"
#include "../../maths/interpolation/dividedDifference.h"


void CurveBase::bootstrap( const InterpolationFactoryBase& interpolationFactory, double first_x, double last_x, double increment )
{
	InterpolationBase* interpolationScheme = interpolationFactory.createInstance( points );
	for( double x = first_x; x < last_x; x += increment )
		interpolatedPoints.push_back( dCartesian2D( x, interpolationScheme->getInterpolatedRate( x ) ) );
	delete interpolationScheme;
}

void CurveBase::bootstrap( const InterpolationFactoryBase& interpolationFactory, double increment )
{
	interpolatedPoints.clear();
	InterpolationBase* interpolationScheme = interpolationFactory.createInstance( points );
	for( double x = points.front().x; x < points.back().x; x += increment )
		interpolatedPoints.push_back( dCartesian2D( x, interpolationScheme->getInterpolatedRate( x ) ) );
	delete interpolationScheme;
}

void CurveBase::bootstrap( InterpolationBase* interpolationScheme, double increment )
{
	interpolatedPoints.clear();
	for( double x = points.front().x; x < points.back().x; x += increment )
		interpolatedPoints.push_back( dCartesian2D( x, interpolationScheme->getInterpolatedRate( x ) ) );

}

void CurveBase::dividedDifferenceBootstrap( double increment )
{
		bootstrap<DividedDifference>( increment );
}

void CurveBase::cubicSplineBootstrap( double increment )
{
		bootstrap<CubicSpline>( increment );
}

void CurveBase::printInterpolatedPoints()
{
	for( dSetCartesian2D::iterator pointIter = interpolatedPoints.begin(); 
		 pointIter != interpolatedPoints.end(); ++pointIter )
	{
		std::cout << "\nx=" << pointIter-> x << " y=" << pointIter->y;
	}
	std::cout << "\n";
}

void CurveBase::printPoints()
{
	for( dSetCartesian2D::iterator pointIter = points.begin(); 
		 pointIter != points.end(); ++pointIter )
	{
		std::cout << "\nx=" << pointIter-> x << " y=" << pointIter->y;
	}
	std::cout << "\n";
}


boost::python::list CurveBase::pyListInterpolatedPoints()
{
	boost::python::list listOfPoints;
	for( dSetCartesian2D::iterator pointIter = interpolatedPoints.begin(); 
			 pointIter != interpolatedPoints.end(); ++pointIter )
		{
			listOfPoints.append< boost::python::tuple >( pointIter->getTuple() );	
			//std::cout << "\nx=" << pointIter-> x << " y=" << pointIter->y;
		}
	
	return listOfPoints;
}


boost::python::list CurveBase::pyListOriginalPoints()
{
	boost::python::list listOfPoints;
	for( dSetCartesian2D::iterator pointIter = points.begin(); 
			 pointIter != points.end(); ++pointIter )
		{
			listOfPoints.append< boost::python::tuple >( pointIter->getTuple() );	
			//std::cout << "\nx=" << pointIter-> x << " y=" << pointIter->y;
		}
	
	return listOfPoints;
}
