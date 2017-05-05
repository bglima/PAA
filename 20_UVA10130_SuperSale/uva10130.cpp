#include<bits/stdc++.h>
#define MAXP 1000 + 2
#define MAXW 30 + 2

using namespace std;

int m[MAXW];

void mwp(int n, int mw, int p[], int w[]);   
void printMatrix();

int main() {
    int t,	// test cases
		n,	// number of objects
		p[MAXP], // price of object
		w[MAXP], // weight of object
		g,		// number of people in the group
		mw,		// maximum weight for each people
		tw;		// maxumum weight the total group can carry
		
    int valueext;
    

    cin >> t;
	
    while(t--) {
		cin >> n;
		
		for(int i = 0; i<n; ++i)
			cin >> p[i] >> w[i];
		
		// Runs MWP for calculating max weight per person
		mwp(n, mw, p, w);
		
		// Initialize total weight for the group
		tw=0;
		// Read number of persons
		cin >> g;
		// For each person, add his max contribution
		while(g--) {
			cin >> mw;
			tw += m[mw];
		}
			
		cout << tw << endl;
		
    }

    return 0;
}
 
// Find the maximum weight one person can carry
// Returns its size
void mwp(int n, int mw, int p[], int w[]) {
  
    memset(m, 0, sizeof(m[0]) * MAXW);
	
	// For each object i in list
	for ( int i = 0; i < n; i++ )
		// Update the max value for determined weight j 
		for ( int j = MAXW; j >= 0; j-- ) {
			// If weight is less than the maxximum possible
			// And we can make the value sum larger, then...
			if (  w[i] <= j   &&   m[j - w[i]] + p[i] > m[j] )
				// Update the new sum
				m[j] = m[j - w[i]] + p[i];
		}

    // printMatrix();
}

// Print matrix from DP
void printMatrix() {
    for( int i = 0; i < MAXW; ++i )
        cout << m[i] << " ";
 
}
