/*
 *  bond.h
 *  bootsrapper
 *
 *  Created by Philip Beadling on 01/07/2007.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef BOND_H
#define BOND_H

#include <vector>
#include <utility>

//#include "../../../basic/pythonInterface/pyVectorConduit.h"

#include "../../../maths/iteration/newtonraphson.h"
#include "../../../basic/array/quicksort.h"
#include "coupon.h"



class Bond : private NewtonRaphson, private QuickSort< Coupon >, public IQuickSortable< double >
{
	public:
		Bond( const double marketPrice, const std::vector<Coupon>& _coupons );
		//Bond( const double marketPrice, const Coupons& _coupons );
				
		Bond( const Bond& other );
		Bond& operator=(const Bond& other);
		bool operator==( const Bond& rhs );
		
		double ytm() const;
		double duration( double r ) const;
		int numberOfCoupons() const;
		void sortCouponsByDate();
		void printCoupons() const;
		double maturityIfCouponsAreSorted() const;
		void test();
		
		
		double marketPrice;
		std::vector<Coupon>& coupons;
		double givenYield;
	
	private:
		//double marketPrice;
		// Just a referance to the objects in the base class
		
	
		virtual double function( const double x ) const;
		virtual double dervOfFunction( const double x ) const;
		virtual double getSortItem() const;			
};

/*
class Bonds : public VectorConduit<Bond>
{
	public:
		Bonds();
		virtual void set( boost::python::list list );
		virtual const std::vector<Bond>& getVector() const;
  
	private:
		// Just a ref to the base objects
		std::vector<Bond>& bonds;
};
*/
#endif
