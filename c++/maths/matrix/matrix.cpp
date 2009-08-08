/*
 *  matrix.cpp
 *  Bond
 *
 *  Created by Philip Beadling on 26/07/2007.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */
#include <iostream>

#include "matrix.h"

using namespace std;

Matrix::Matrix( const dVector2D& array ) : array( array )
{
}

Matrix::Matrix( const unsigned int rows, const unsigned int columns )
{
	array.resize( rows );
	for( unsigned int i=0; i < rows; ++i )
	{
		array[i].assign( columns, 0 );
	}
}

double& Matrix::operator()( const unsigned int row, const unsigned int column )
{
	return array[row][column];
}

double Matrix::operator()( const unsigned int row, const unsigned int column ) const
{
	return array[row][column];
}

// Can't use doEveryElement here as we
// do not have an ElementFunction which
// takes (ostream&,Matrix&) - even if we
// did, << cannot (sensibly) be class member so cannot
// access this->array... Finally this breaks
// sensible design as << does not *do* work
// on every element, it only reads them.
ostream& operator<<(ostream& lhs, const Matrix& rhs)
{
	lhs <<  "\n" << rhs.array.size() << " x " << rhs.array[0].size() << "\n" << "-----\n";
	for( unsigned int i=0; i < rhs.array.size(); ++i)
	{
		for( unsigned int j=0; j < rhs.array[i].size(); ++j)
			lhs << rhs.array[i][j] << "\t\t";
		lhs << "\n";
	}
	return lhs;
}

Matrix Matrix::operator+( const Matrix& rhs )
{
	Matrix copyOfThis( *this );
	copyOfThis += rhs;
	return copyOfThis;	
}

Matrix& Matrix::operator+=( const Matrix& rhs )
{
	doEveryElement( addElement, rhs );
	return *this;
}

Matrix Matrix::operator-( const Matrix& rhs )
{
	Matrix copyOfThis( *this );
	copyOfThis -= rhs;
	return copyOfThis;	
}

Matrix& Matrix::operator-=( const Matrix& rhs )
{
	doEveryElement( subtractElement, rhs );
	return *this;
}

Matrix Matrix::operator*( const Matrix& rhs )
{
	Matrix copyOfThis( *this );
	copyOfThis *= rhs;
	return copyOfThis;	
}

Matrix& Matrix::operator*=( const Matrix& rhs )
{
	if( array[0].size() == rhs.array.size() )
	{
		dVector2D temp;
		//Resize collumns to hold the result
		for ( unsigned int row=0; row < array.size(); ++row )
			array[row].resize( rhs.array[0].size() );
		//cout << *this;
		//Crude - it would be better to initalize temp as an array of zeros.
		temp = array;
		for( unsigned int i=0; i < array.size(); ++i)
		{
			for( unsigned int j=0; j < array[0].size(); ++j)
			{
				temp[i][j] = 0;
				for( unsigned int k=0; k < rhs.array.size(); ++k)
				{
					
					temp[i][j] += array[i][k] * rhs.array[k][j];
				}

			}
		}
	array = temp;
	}
	else
	{
		cout << "Cannot multiply " << array.size() << " x " << array[0].size() << " with "
	         << rhs.array.size() << " x " << rhs.array[0].size() << ".";
		throw MatrixMultiplicationException();
	}
	
	return *this;
}

Matrix& Matrix::operator++()
{
	doEveryElement( incrementElement );
	return *this;
}

const Matrix Matrix::operator++(int)
{
	const Matrix originalMatrix( *this );
	++(*this);
	return originalMatrix;
} 

Matrix& Matrix::operator--()
{
	doEveryElement( decrementElement );
	return *this;
}

const Matrix Matrix::operator--(int)
{
	const Matrix originalMatrix( *this );
	--(*this);
	return originalMatrix;
} 

const dimensions Matrix::getDimensions() const
{
		return ( dimensions( array.size(), array[0].size() ) );
}

void Matrix::gaussElimination()
{
	for ( unsigned int i=0; i < array.size() - 1; ++i )
	{
		double pivot = array[i][i];
		//Push to the bottom if pivot is 0 for next equation
		//cout << "\nInital Pivot (" << i << "," << i << ") : " << pivot;
		while( pivot == 0 )
		{
			//cout << "\nLoop Pivot (" << i << "," << i << ") : " << pivot;
			array.push_back( array[i] );
			//cout << "\nPush back";
			//cout << *this;
			array.erase( array.begin() + i );
			//cout << "\nErase:";
			//cout << *this;
			pivot = array[i][i];
		}
		//cout << "\nFinal Pivot (" << i << "," << i << ") : " << pivot;
		
		// Only eliminate rows below
		for( unsigned int row = i + 1; row < array.size(); ++row )
		{
			double eliminator = array[row][i] / pivot;
			for( unsigned int column = 0; column < array[0].size(); ++column )
			{
				array[row][column] -= eliminator * array[i][column];
			}
		}
		//cout << "\nCompleted parent loop, now pivot with:";
		//cout << *this;
	}
	
}

vector< element > Matrix::backSubstitute()
{
	vector< element > results;
	
	//Check for over specification
	//Remove any rows of zeros
	vector< element > zeroRow;
	for ( unsigned int i=0; i < array[0].size(); ++i )
		zeroRow.push_back(0);
		
	unsigned int row=array.size()-1;
	while ( array[row] == zeroRow )
	{
			array.pop_back();
			--row;
	}	
	
	//cout << *this;
	
	// Woefully crude - tidy it up!
	results.resize( array.size() );
	unsigned int columnCount = 0;
	for ( int i=array.size() - 1; i > -1; --i )
	{
		//Start at the bottom element
		// Last element is the 'answer' to this equation
		double numerator = array[i].back();
		//cout << "\nNumerator:" << numerator;
		// Need to know how many unknowns are now knowns and
		// we can count back over them.
		unsigned int currentColumn = columnCount;
		while( currentColumn > 0 )
		{
			// Numerator is all now knowns taken over
			// and minused off the 'answer'
			//cout << "\nI'm taking over array[" << i << "][" << array[i].size()-1-currentColumn << "] and times it with results[" << array[i].size()-1-currentColumn << "]";
			numerator -= array[i][array[i].size()-1-currentColumn] * results[array[i].size()-1-currentColumn];
			// Drop back to next column
			--currentColumn;
		}
		// Divide whole new 'answer' but new unknown's multiplier
		//cout << "\nFinal Numerator:" << numerator;
		//cout << "\nDenominator array[" << i << "][" << array[i].size()-columnCount-2 << "] :" << array[i][array[i].size()-columnCount-2];
		results[i] = numerator / array[i][array[i].size()-columnCount-2];
		// Next time we will have one more column 
		++columnCount;
	}
	
	// Little test!
	/*
	cout << "\n_____________";
	for( unsigned int i=0; i<results.size();++i)
	{
		cout << "\nresults[" << i << "] = " << results[i];
	}
	*/
	
	// Return a vector where [0] is value for the first unknown and so on...
	return results;

}

void Matrix::doEveryElement( UnaryElementFunction& callMe )
{
	for( unsigned int i=0; i < array.size(); ++i)
		for( unsigned int j=0; j < array[i].size(); ++j)
			callMe( array[i][j] );
}

void Matrix::doEveryElement( BinaryElementFunction& callMe, const Matrix& other )
{
	for( unsigned int i=0; i < array.size(); ++i)
		for( unsigned int j=0; j < array[i].size(); ++j)
			callMe( array[i][j], other.array[i][j] );
}


void Matrix::addElement( element& theElement, const element& theOtherElement )
{
	theElement += theOtherElement;
}

void Matrix::incrementElement( element& theElement )
{
	// Could use addElement( theElement, 1.0 ), but would be slower?
	++theElement;
}

void Matrix::subtractElement( element& theElement, const element& theOtherElement )
{
	theElement -= theOtherElement;
}

void Matrix::decrementElement( element& theElement )
{
	// Could use addElement( theElement, 1.0 ), but would be slower?
	--theElement;
}

void Matrix::test()
{
	// Matrix Tests
	vector< element > row1,row2,row3;
	row1.push_back(1);
	row1.push_back(0);
	row1.push_back(0);
	row2.push_back(0);
	row2.push_back(2);
	row2.push_back(0);
	row3.push_back(0);
	row3.push_back(0);
	row3.push_back(3);
	
	dVector2D array;
	array.push_back( row1 );
	array.push_back( row2 );
	array.push_back( row3 );
	
	Matrix m( array );
	const Matrix m2( array );
	
	cout << "\n_____________\n";
	
	cout << "\n" << m;
	
	m++;
	++m;
	
	cout << "\n" << m;
	
	Matrix p = m + m2;
	
	cout << "\n" << p;
	
	p += m2;
	
	cout << "\n" << p;
		
	Matrix m3(2,2);
	m3(0,0) = 3;
	m3(0,1) = 2;
	m3(1,0) = 7;
	m3(1,1) = 8;
	
	Matrix m4(2,3);
	m4(0,0) = 4;
	m4(0,1) = 0;
	m4(0,2) = 1;
	m4(1,0) = 9;
	m4(1,1) = 2;
	m4(1,2) = 6;
	
	cout << "\nFirst mutiplier:" << m3;
	cout << "\nSecond mutiplier:" << m4;
	
	Matrix m5 = m3 * m4;
	
	cout << "\nResult:" << m5;
	
	m5 *= m;
	
	cout <<"\nAnd *=:" << m5;
	
	cout << "\n_____________\n";
	
	Matrix m6(4,4);
	m6(0,0) = 1;
	m6(0,1) = -1;
	m6(0,2) = 1;
	m6(0,3) = 0;
	m6(1,0) = -1;
	m6(1,1) = 1;
	m6(1,2) = -1;
	m6(1,3) = 0;
	m6(2,0) = 0;
	m6(2,1) = 10;
	m6(2,2) = 25;
	m6(2,3) = 90;
	m6(3,0) = 20;
	m6(3,1) = 10;
	m6(3,2) = 0;
	m6(3,3) = 80;
	
	cout << "\nBefore Gauss:" << m6;
	
	m6.gaussElimination();
	
	cout << "\nAfter Gauss:" << m6;
	
	vector<double> results = m6.backSubstitute();

	Matrix m7(3,5);
	m7(0,0) = 3;
	m7(0,1) = 2;
	m7(0,2) = 2;
	m7(0,3) = -5;
	m7(0,4) = 8;
	m7(1,0) = 0;
	m7(1,1) = 1.1;
	m7(1,2) = 1.1;
	m7(1,3) = -4.4;
	m7(1,4) = 1.1;
	m7(2,0) = 0;
	m7(2,1) = -1.1;
	m7(2,2) = -1.1;
	m7(2,3) = 4.4;
	m7(2,4) = -1.1;
	
	
	cout << "\nBefore Gauss:" << m7;
	
	m7.gaussElimination();
	
	cout << "\nAfter Gauss:" << m7;
	
	cout << "\n_____________\n";
	
	/*
	// THIS SHOULD BE ELSEWHERE - IT'S
	// NOT A PURE MATRIX TEST!
	cout << "\nCubic Spline tests:\n";
	
	
	// Simple CS example - non-financial data
	vector<ForwardRate> testRates;
	testRates.push_back( ForwardRate( 0, 0 ) );
	testRates.push_back( ForwardRate( 1, 0.5 ) );
	testRates.push_back( ForwardRate( 2, 2.0 ) );
	testRates.push_back( ForwardRate( 3, 1.5 ) );
	
	CubicSpline cs( testRates );
	
	for( double i = 0; i<3; i+=0.05 )
	{
		cout << "\n***Cubic Spline at time:\t" << i; 
		double myRate = cs.getInterpolatedRate( i )*100;
		cout << "\n***Rate:\t" << myRate; 
	}
`	*/

}
