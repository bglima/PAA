#include<bits/stdc++.h>

using namespace std;

int t;		 // Number of test cases
int n;		 // Number of rungs
int r[100000];  // Heights of the rungs from the ground
int rDiff[100000]; // Difference between two consecutive rungs
int minK;	   // Minnimum value for k

bool testK(int k) {
	int currentK = k;

	for( int i = 0; i < n; ++i ) {
		if( rDiff[i] > currentK ) return false;		// Not enough energy
		else if ( rDiff[i] == currentK ) --currentK;	// Energy loses 1 point
	}

	return true;	// If it gets here, k is valid
}

int main() {
	cin >> t;
	for( int i = 0; i < t; ++i ) {
		cin >> n;
		cin >> r[0]; // First rung height from the ground
		minK = r[0]; // Assumin minK as the first height
		for( int j = 1; j < n; ++j ) {
			cin >> r[j];	// Each consecutive rung
			rDiff[j] = r[j] - r[j-1];
			if ( rDiff[j] > minK ) minK = rDiff[j];	// minK should start at max diff between two consecutive rungs
		}

		while ( ! testK( minK ) )
			++minK;
		
		cout << "Case " << i << ": " << minK << endl; 		
	}
}
