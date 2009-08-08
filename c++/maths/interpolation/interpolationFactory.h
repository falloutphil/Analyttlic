/*
 *  factoryTemplate.h
 *  Bond
 *
 *  Created by Philip Beadling on 09/08/2007.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef INTERPOLATIONFACTORY_H
#define INTERPOLATIONFACTORY_H

#include "interpolationBase.h"
#include "../../maths/basic/cartesian.h"


// Is it not possible just to have an un-classed
// createInstance style template function which returns
// the correct child?
// It is but note that the coordinates are passed in
// to a function call used outside of the curve class
// this leads to curve.method( curve.data ) - which sucks.
// By passing a factory in we can create the object actually
// inside the curve object itself.  Think of the factory
// as a trojan horse - delaying instantiation, but predetermining
// it's nature.
template< class INTERPOLATION_CHILD_T >
InterpolationBase* interpolationFactory( const dSetCartesian2D& coordinates )
{
	return new INTERPOLATION_CHILD_T( coordinates );
}

// Do we have to have the parent/child class
// - I think so as this means we can pass
// in the non-templated parent as a function
// argument.  Can you pass templated class referances
// as parameters in non-template classes.... probably not.
// Perhaps we can tho - now that bootstrap is not virtual -
// just stick a template member function in the base curve class.
// boostrap< CubicSpline >()
// -- WE CAN - see curve base class!


class InterpolationFactoryBase
{
   public:
      InterpolationFactoryBase() {}
      virtual ~InterpolationFactoryBase() {}
      virtual InterpolationBase* createInstance( const dSetCartesian2D& coordinates ) const = 0;
};

template < class INTERPOLATION_CHILD_T >
class InterpolationFactory : public InterpolationFactoryBase
{
   public:
      InterpolationFactory() {}
      virtual ~InterpolationFactory() {}
      virtual InterpolationBase* createInstance(  const dSetCartesian2D& coordinates ) const
	  { 
		return new INTERPOLATION_CHILD_T( coordinates );
	  }
};

#endif

