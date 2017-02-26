#include<bits/stdc++.h>

using namespace std;

int input1, input3;
string input2, garbage;

int consumption;
int dist, distPrev;
int leak;
double gasUsed, maxGasUsed;

void updateGasUsed() {
	dist = (input1 - distPrev);
	gasUsed += dist * ( (float) consumption / 100.0 + leak );
	distPrev = input1;
}



int main () {
	cout.setf(ios::fixed,ios::floatfield);
    	cout.precision(3);
	while ( cin >> input1 >> input2 ) {
		switch (input2[0]) {
			case 'G':	// d Goal or d Gas station
				if( input2[1] == 'o' ) {		// Goal
					updateGasUsed();
					if ( gasUsed > maxGasUsed ) maxGasUsed = gasUsed;
					cout << maxGasUsed << endl;
				} else {				// Gas station
					cin >> garbage; 		// Take word "Station"
					updateGasUsed();
					if ( gasUsed > maxGasUsed ) maxGasUsed = gasUsed;
					gasUsed = 0;
				}
				break;
			case 'F': 	// d Fuel consumption n
				cin >> garbage;	// Take next word "Consumption" out from buffer
				cin >> input3;	// Take the new consumption
				if ( input1 == 0 ) { 		    // First time entering
					if( input3 == 0 ) return 0; // Stop condition
					distPrev = 0;
					gasUsed = 0;
					maxGasUsed = 0;
					leak = 0;
					consumption = input3;
				} else {
					updateGasUsed();
					consumption = input3;
				}
				break;
			case 'L':	// d Leak
				updateGasUsed();
				++leak;
				break;
			case 'M':	// d Mechanic
				dist = (input1 - distPrev);
				updateGasUsed();
				leak = 0;
				break;
		}
	}
}
