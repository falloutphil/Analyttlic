/*
 *  newtonraphson.h
 *  bootsrapper
 *
 *  Created by Philip Beadling on 05/07/2007.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */
 
#ifndef NEWTONRAPHSON_H
#define NEWTONRAPHSON_H

 class NewtonRaphson
 {
	protected:
		NewtonRaphson( double error, double maxIter );
		virtual ~NewtonRaphson();
		double solve( double guess ) const;
	
		virtual double function( const double x ) const = 0;
		virtual double dervOfFunction( const double x ) const = 0;
	
	private:
		const double error;
		const double maxIter;
 };
 
#endif
