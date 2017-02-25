#include<bits/stdc++.h>

using namespace std;

int shorter, taller;

int n, q;
int luchuHeight;

// Iterative binary search. Ends when left > right.
// Initalize shorter and taller as -1, suposing that they does not exist.
void divideAndConquer(int chimpHeight[], int left, int right) {
	shorter = taller = -1;
  	while (left <= right) {			   // If luchuHeight exists in array, we need to find a shorter and a greater element.
            int mid = (left + right) / 2;          // Take the middle from sorted array
            if (chimpHeight[mid] == luchuHeight) { // If there is an equal element
		shorter = taller = mid;	           // Start from it
		while ( chimpHeight[--shorter] == luchuHeight ); // And goes back until we find an element that is shorter
		if( shorter < 0 ) shorter = -1;    // If there isn't one, put -1 back


		while ( chimpHeight[++taller] == luchuHeight ); //  Do the same to find an element that is greater
		if( taller > n-1) taller = -1;	   // It there isn't one, put -1 back
		return;
	    }
	    else if (chimpHeight[mid] > luchuHeight) { // Otherwise, compare to middle. If middle element is greater...
		taller = mid;
                right = mid - 1;
	    }
            else {					// If middle element is shorter...
		shorter = mid;
                left = mid + 1;
	    }
      }
}

// Formatting output
void showResults(int chimpHeight[]) {
     if ( shorter == -1 ) cout << "X "; else cout << chimpHeight[shorter] << " ";
     if ( taller == -1) cout << "X" << endl; else cout << chimpHeight[taller] << endl;
}


int main() {

	cin >> n;
	int chimpHeight[n];
	for( int i = 0; i < n; ++i ) {
		cin >> chimpHeight[i];
	}
	cin >> q;
	for( int i = 0; i < q; ++i ) {
		cin >> luchuHeight;
		divideAndConquer(chimpHeight, 0, n-1); // Divide and conquer
		showResults(chimpHeight);	       // Show results
	}
}
