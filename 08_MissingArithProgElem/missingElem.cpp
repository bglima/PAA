#include <bits/stdc++.h>

using namespace std;

int n, t;
int a[10];
int ratio;

int searchMissing() {
	int left = 0, right = n - 1, mid;

	while ( left < right ) {
		mid = ( left + right ) / 2;

		if ( a[mid] == a[0] + mid*ratio ) {	// Mid is in right place
			if ( a[mid+1] != a[0] + (mid+1)*ratio )	// Check next
				return a[mid+1] - ratio;
			left = mid+1;
		} else {				// Mid is wrong
			if ( a[mid-1] == a[0] + (mid-1)*ratio )  // Check prev
				return a[mid] - ratio;
			right = mid - 1;
		}
	}
}

int main() {
	cin >> t;
	for( int i = 0 ; i < t ; ++i ) {
		cin >> n;
		for( int j = 0 ; j < n ; ++j ) 
			cin >> a[j];
		ratio = (a[n-1] - a[0]) / n;
		cout << searchMissing() << endl;
	}
}
