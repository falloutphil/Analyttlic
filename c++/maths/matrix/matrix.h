/*
 *  matrix.h
 *  Bond
 *
 *  Created by Philip Beadling on 26/07/2007.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef MATRIX_H
#define MATRIX_H


#include <vector>
#include <iostream>
#include <exception>


typedef double element;
typedef std::vector< std::vector< element > > dVector2D;
typedef void(UnaryElementFunction)( element& theElement );
typedef void(BinaryElementFunction)( element& theElement, const element& theOtherElement);

struct dimensions
{
	dimensions( const unsigned int m, const unsigned int n ) : m(m), n(n) {};
	const unsigned int m;
	const unsigned int n;
};

class Matrix
{

	public:
		Matrix( const dVector2D& array );
		Matrix( const unsigned int rows, const unsigned int columns );
		
		double& operator()( const unsigned int row, const unsigned int column );
		double operator()( const unsigned int row, const unsigned int column ) const;
		
		// As we don't want to update the ostream class 
		// so make a friend function that correctly takes
		// an ostream as the LHS of the << operator.
		friend std::ostream& operator<<(std::ostream& lhs, const Matrix& rhs);
		// As RHS is also of type Matrix can be member function.
		Matrix operator+( const Matrix& rhs );
		Matrix& operator+=( const Matrix& rhs );
		Matrix operator-( const Matrix& rhs );
		Matrix& operator-=( const Matrix& rhs );
		Matrix operator*( const Matrix& rhs );
		Matrix& operator*=( const Matrix& rhs );
		Matrix& operator++();
		const Matrix operator++(int);
		Matrix& operator--();
		const Matrix operator--(int);
				
		const dimensions getDimensions() const;
		void gaussElimination();
		std::vector< element > backSubstitute();
		
		void test();

	private:
		dVector2D array;
		void doEveryElement( UnaryElementFunction& callMe );
		void doEveryElement( BinaryElementFunction& callMe, const Matrix& other );
		// As built-in types (eg double) are not classes in C++
		// we need to write wrapper functions which can be passed
		// around as referances to double's 'opterators'
		// _______________
		// Effectively double.operator++()
		inline static UnaryElementFunction incrementElement;
		// Effectively double.operator--()
		inline static UnaryElementFunction decrementElement;
		// Effectively double.operator+=( const double& rhs )
		inline static BinaryElementFunction addElement;
		// Effectively double.operator-=( const double& rhs )
		inline static BinaryElementFunction subtractElement;
		
};

class MatrixMultiplicationException : public std::exception
{
	virtual const char* what() const throw()
	{
		return "MatrixMultiplicationException Thrown";
	}
};

#endif

