#ifndef MATRIX_H
#define MATRIX_H


/*******************************************************************
 * class - Matrix
 * 
 * A utility class for the usage of Matrices for affine transformations 
 * (Not implemented)
 * A Matrix is a 4X4 square matrix.
 * 
 *******************************************************************/


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