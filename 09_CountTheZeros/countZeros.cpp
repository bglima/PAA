#include<bits/stdc++.h>

using namespace std;

int a[30];
int t, n;

int countZeros() {
	if( a[0] == 0 && a[n-1] == 0 ) 
		return n; // If all zeros...
	if( a[0] == 1 && a[n-1] == 1 )
		return 0;

	int left = 0, right = n-1;

	while ( left < right ) {
		int mid = ( left + right ) / 2; // Take element from the middle

		if ( a[mid] == 0 ) {		// If zero...
			if ( a[mid - 1] == 1 )  // Check previous
				return n - mid;
			right = mid - 1;
		} else {			// If one...
			if ( a[mid + 1] == 0 )	// Check next
				return n - mid - 1;
			left = mid + 1;
		}
	}
}

int main() {
	cin >> t;
	for( int i = 0 ; i < t ; ++i ) {
		cin >> n;
		for ( int j = 0 ; j < n; ++j ) 
			cin >> a[j];

		cout << countZeros() << endl;

	}
}
