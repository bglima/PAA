#include<bits/stdc++.h>

using namespace std;

typedef vector< vector <int> > vi;

void mSum( vi &A, vi &B, vi &C, int size );
void mSub( vi &A, vi &B, vi &C, int size );
void mPrint( vi &A, int size );


int main() {
	int size;
	while ( cin >> size ) {
		vi m1 (size, vector<int>(size));
		vi m2 (size, vector<int>(size));
		vi m3 (size, vector<int>(size));

		for(int i = 0; i < size; ++i)
			for(int j=0; j < size; ++j)
				cin >> m1[i][j];
		
		for(int i = 0; i < size; ++i)
			for(int j=0; j < size; ++j)
				cin >> m2[i][j];

		mSum( m1, m2, m3, size);
		mPrint( m3, size );
		mSub( m1, m2, m3, size);
		mPrint( m3, size );
	}
		
}

void mPrint( vi &A, int size )
{
	for ( int i = 0; i < size; i++ )
	{
		for ( int j = 0; j < size; j++ )
			cout << A[i][j] << " ";
		cout << endl;
	}
	cout << endl;
}

void mSum( vi &A, vi &B, vi &C, int size )
{
	for ( int i = 0; i < size; i++ )
		for ( int j = 0; j < size; j++ )
			C[i][j] = A[i][j] + B[i][j];
}


void mSub( vi &A, vi &B, vi &C, int size )
{
	for ( int i = 0; i < size; i++ )
		for ( int j = 0; j < size; j++ )
			C[i][j] = A[i][j] - B[i][j];
}
