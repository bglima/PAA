#include<bits/stdc++.h>

using namespace std;

int a[500];
int t, n;

int findMin() {
	int left = 0, right = n-1;

	while ( a[left] > a[right] ) {
		int mid = ( left + right ) / 2; // Take element from the middle

		if ( a[mid] > a[right] ) {	// Minimum is at right subarray
			left = mid + 1;
		} else {			// Minimun is at left subarray
			right = mid;
		}
	}
	return a[left];
}

int main() {
	cin >> t;
	for( int i = 0 ; i < t ; ++i ) {
		cin >> n;
		for ( int j = 0 ; j < n; ++j ) 
			cin >> a[j];

		cout << findMin() << endl;

	}
}
