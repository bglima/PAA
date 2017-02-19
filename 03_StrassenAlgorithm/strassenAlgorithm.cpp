#include<bits/stdc++.h>

//    Max size of Strassen subsequent divvtsions. After this size, 
//    It's executed the ordinary matrix multiplication before starting
// the recombination.
#define leafSize 2 

using namespace std;

//    Matrix types
typedef vector<int> vt;		// Unidimensional vector type
typedef vector< vt > vvt;	// Bimidmensional vector type

void mSum( vvt &A, vvt &B, vvt &C, int size );
void mSub( vvt &A, vvt &B, vvt &C, int size );
void mMul( vvt &A, vvt &B, vvt &C, int size );
void mMulSt( vvt &A, vvt &B, vvt &C, int size ); 
vvt mExp( vvt &A, int n, int size );
void mPrint( vvt &A, int size );

// Main program
int main() {
	int size, maxPower;
	while ( cin >> size ) {
		vvt m1 (size, vt(size)); // Input matrix
		vvt m2 (size, vt(size)); // Result matrix
		
		cin >> maxPower;	
		
		for(int i = 0; i < size; ++i)
			for(int j=0; j < size; ++j) {
				cin >> m1[i][j];
			}
		
		m2 = mExp( m1, maxPower, size );
		mPrint(m2, size);
	}
}

// Divide and conquer exponential algorithm
vvt mExp( vvt &A, int n, int size ) {
	if ( n == 0 ) {
		vvt result (size, vt(size));
		for( int i = 0; i < size; ++i)
			for( int j = 0; j < size; ++j)
				result[i][j] = 1;
		return result;
	} else if ( n == 1 ) {
		return A;
	} else if ( n % 2 == 0 ) {
		vvt result (size, vt(size));
		mMul(A, A, result, size);
		return mExp(result, n / 2, size);
	} else if ( n % 2 != 0 ) {
		vvt result (size, vt(size));
		vvt partialMultiplication (size, vt(size));
		vvt partialPower (size, vt(size));

		mMul(A, A, partialMultiplication, size);
		partialPower = mExp(partialMultiplication, (n-1)/2, size);
		mMul(A, partialPower, result, size);
		return result;
	}
}

// matrixPrint
void mPrint( vvt &A, int size )
{
	for ( int i = 0; i < size; i++ )
	{
		for ( int j = 0; j < size; j++ )
			cout << A[i][j] << " ";
		cout << endl;
	}
	cout << endl;
}

// matrixSum
void mSum( vvt &A, vvt &B, vvt &C, int size )
{
	for ( int i = 0; i < size; i++ )
		for ( int j = 0; j < size; j++ )
			C[i][j] = A[i][j] + B[i][j];
}

// matrixSubtract
void mSub( vvt &A, vvt &B, vvt &C, int size )
{
	for ( int i = 0; i < size; i++ )
		for ( int j = 0; j < size; j++ )
			C[i][j] = A[i][j] - B[i][j];
}

// ordinary matrixMultiplication
void mMul( vvt &A, vvt &B, vvt &C, int size ) {
	for ( int i = 0; i < size; ++i )
		for ( int k = 0; k < size; ++k ) 
			for ( int j = 0; j < size; ++j )
				C[i][j] += A[i][k] * B[k][j];
}

// Strassen matrixMultiplication
void mMulSt( vvt &A, vvt &B, vvt &C, int size ){
	if ( size <= leafSize ) {
		mMul( A, B, C, size);
		return;		
	} else  {
		int newSize = size/2;
		vvt a11(newSize, vt(newSize)),
		   a12(newSize, vt(newSize)),
		   a21(newSize, vt(newSize)),
		   a22(newSize, vt(newSize)),		   
		   b11(newSize, vt(newSize)),
		   b12(newSize, vt(newSize)),
		   b21(newSize, vt(newSize)),
		   b22(newSize, vt(newSize)),
		   aRes(newSize, vt(newSize)),
		   bRes(newSize, vt(newSize)),
		   c11(newSize, vt(newSize)),
		   c12(newSize, vt(newSize)),
		   c21(newSize, vt(newSize)),
		   c22(newSize, vt(newSize)),
		   p1(newSize, vt(newSize)),
		   p2(newSize, vt(newSize)),
		   p3(newSize, vt(newSize)),
		   p4(newSize, vt(newSize)),
		   p5(newSize, vt(newSize)),
		   p6(newSize, vt(newSize)),
		   p7(newSize, vt(newSize));
		int i, j;

		// Filling the 4 sub-matrices
		for (i = 0; i<newSize; ++i)
			for(j = 0; j<newSize; ++j) {
				a11[i][j] = A[i][j];
				a12[i][j] = A[i][j + newSize];
				a21[i][j] = A[i + newSize][j];
				a22[i][j] = A[i + newSize][j + newSize];

				b11[i][j] = B[i][j];
				b12[i][j] = B[i][j + newSize];
				b21[i][j] = B[i + newSize][j];
				b22[i][j] = B[i + newSize][j + newSize];
			}

		// P1..7 calculations
		mSum(a11, a22, aRes, newSize); // a11 + a22
		mSum(b11, b22, bRes, newSize); // b11 + b22
		mMulSt(aRes, bRes, p1, newSize); //  p1 = (a11+a22) * (b11+b22)

		mSum(a21, a22, aRes, newSize);  // a21 + a22
		mMulSt(aRes, b11, p2, newSize);  // p2 = (a21+a22) * (b11)

		mSub(b12, b22, bRes, newSize); // b12 - b22
		mMulSt(a11, bRes, p3, newSize); // p3 = (a11) * (b12 - b22)

		mSub(b21, b11, bRes, newSize); // b21 - b11
		mMulSt(a22, bRes, p4, newSize); // p4 = (a22) * (b21 - b11)

		mSum(a11, a12, 	aRes, newSize); // a11 + a12
		mMulSt(aRes, b22, p5, newSize); // p5 = (a11 + a12) * (b22)

		mSub(a21, a11, aRes, newSize); // a21 - a11
		mSum(b11, b12, bRes, newSize); // b11 + b12
		mMulSt(aRes, bRes, p6, newSize); // (a21 - a11) * (b11, b12)

		mSub(a12, a22, aRes, newSize); // a12 - a22
		mSum(b21, b22, bRes, newSize); // b21 - b22
		mMulSt(aRes, bRes, p7, newSize); // p7 = (a12 - a22) * (b21 + b22)

		// Calculating c11, c12, c21 and c22
		mSum(p1, p4, aRes, newSize); // p1 + p4
		mSum(aRes, p7, bRes, newSize); // p1 + p4 + p7
		mSub(bRes, p5, c11, newSize); // c11 = p1 + p4 + p7 - p5

		mSum(p3, p5, c12, newSize); // c12 = p1 + p5

		mSum(p2, p4, c21, newSize); // c21 = p2 + p4
		
		mSum(p1, p3, aRes, newSize); // p1 + p3
		mSum(aRes, p6, bRes, newSize); // p1 + p3 + p6
		mSub(bRes, p2, c22, newSize); // c22 = p1 + p3 + p6 = p2

		// Putting the submatrices togheter
		for( i = 0; i<newSize; ++i )
			for( j=0; j < newSize; ++j ) {
				C[i][j] = c11[i][j];
				C[i][j + newSize] = c12[i][j];
				C[i + newSize][j] = c21[i][j];
				C[i + newSize][j + newSize] = c22[i][j];
			}
	}
}
