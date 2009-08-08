/*
 *  cartesian.h
 *  Bond
 *
 *  Created by Philip Beadling on 05/08/2007.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef CARTESIAN_H
#define CARTESIAN_H

#include <boost/python.hpp>

#include <vector>

template<class T_NUMBER>
struct Cartesian2D
{
		Cartesian2D( T_NUMBER x, T_NUMBER y ) : x(x), y(y) {};
		
		// Needed by Py++
		bool operator==( const Cartesian2D& rhs )
		{
			return ( (x == rhs.x) && (y == rhs.y) );
		}
				
		boost::python::tuple getTuple() { return boost::python::make_tuple(x,y); };
		T_NUMBER x;
		T_NUMBER y;
		
		
};


typedef Cartesian2D<double> dCartesian2D;

typedef std::vector< dCartesian2D > dSetCartesian2D;

#endif


