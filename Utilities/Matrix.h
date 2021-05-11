#ifndef MATRIX_H
#define MATRIX_H


// this file contains the declaration of the class Matrix
// Matrix is a 4 x 4 square matrix that is used to represent affine transformations
// we don't need a general m x n matrix

//----------------------------------------- class Matrix

class Matrix {
	
	public:
	
		double	m[4][4];								// elements
		
		Matrix(void);									// default constructor

		Matrix(const Matrix& mat);						// copy constructor
		
		~Matrix (void);									// destructor
			
		Matrix& operator= (const Matrix& rhs);			// assignment operator
		 	
			
		 											// multiplication of two matrices
		Matrix operator* (const Matrix& mat) const;

		Matrix 	operator/ (const double d);										// divsion by a double
		

		void set_identity(void);										// set to the identity matrix
			
};

#endif