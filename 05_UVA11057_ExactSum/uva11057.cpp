#include <bits/stdc++.h>

using namespace std;

int i, j;
int n, m;
int books[10000];
int priceOne, priceTwo;

void calcPrices() {
	i = 0;
	j = n - 1;
	while ( i < j ) {
		if( books[i] + books[j] < m ) 		// If there is money left
			++i;
		else if ( books[i] + books [j] > m )	// If there is money lack
			--j;
		else {					// If the sum is exact
			priceOne = books[i];
			priceTwo = books[j];
			--j;
			++i;
		}
	}
}

void showResults() {
	cout << "Peter should buy books whose prices are " << priceOne << " and " << priceTwo << "." << endl << endl;
}

int main(){
	while ( cin >> n ) {	// Number of avaliable books
		for(i = 0; i < n; ++i)
			cin >> books[i];	// Price of each book
		
		sort(books, books + n);	// Sorting the books

		cin >> m;	// Money Peter has
		calcPrices();
		showResults();
	}
}
