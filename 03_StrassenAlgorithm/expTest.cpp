#include<bits/stdc++.h>

using namespace std;

int exp(int x, int n) {
	if ( n == 0 ) return 1;
	if ( n == 1 ) return x;
	if ( n % 2 == 0 ) return exp ( x * x, n / 2);
	return x * exp ( x * x, (n - 1)/2 );
}

int main() {
	int x, n;
	cin >> x;
	for( n = 0; n < 10; n++)
		cout << exp(x, n) << endl;


}
