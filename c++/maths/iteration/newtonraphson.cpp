/*
 *  newtonraphson.cpp
 *  bootsrapper
 *
 *  Created by Philip Beadling on 05/07/2007.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */


#include <math.h>
#include <iostream>
#include <iomanip>

#include "newtonraphson.h"

using namespace std;

NewtonRaphson::NewtonRaphson( double error, double maxIter ) : error ( error ), maxIter ( maxIter ) 
{
	//cout << "\nNewtonRaphson contructor called";
}

NewtonRaphson::~NewtonRaphson() {}

double NewtonRaphson::solve( double guess ) const
{
	double currentError = 1;
	double iters = 0;
	double nextGuess = 0;
	
	while ( currentError > error && iters < maxIter )
	{
		//std::cout << setprecision(18) << "\nGuess: " << guess;
		nextGuess = guess - ( function( guess )/dervOfFunction( guess ) );
		currentError = fabs( nextGuess - guess );
		guess = nextGuess;
		++iters;
	}
	
	return iters < maxIter ? guess : 0.1234;

}
