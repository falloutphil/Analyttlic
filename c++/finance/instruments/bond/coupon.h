/*
 *  coupon.h
 *  bootsrapper
 *
 *  Created by Philip Beadling on 15/07/2007.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef COUPON_H
#define COUPON_H



#include "../../../basic/array/quicksort.h"
//#include "../../../basic/pythonInterface/pyVectorConduit.h"

#include <vector>
#include <iostream>


class Coupon : public IQuickSortable< double >
{
	public:
		Coupon( const double value, const double maturity );
		// Needed by Py++
		bool operator==( const Coupon& rhs ) const;
		double pv( const double r ) const;
		double getMaturity() const;
		double getValue() const;
		virtual double getSortItem() const;

	private:	
		double value;
		double maturity;
		
};

/*
class Coupons : public VectorConduit<Coupon>
{
	public:
		Coupons();
		virtual void set( boost::python::list list );
		virtual const std::vector<Coupon>& getVector() const;
  
	private:
		// Just a ref to the base objects
		std::vector<Coupon>& coupons;
};
*/
#endif
