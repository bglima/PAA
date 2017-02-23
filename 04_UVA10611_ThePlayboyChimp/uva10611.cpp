#include<bits/stdc++.h>

using namespace std;

struct heights{
	int shorter;
	int taller;
};

int n, q;
int luchuHeight;


// Look for a chimp with same height as Luchu. 
// If there exists one, return the previous and the next chimp heights.
// Otherwise, if there is not, there are thre possibilities:
//    1 - Search ends at first position. There is on
//    2 - Search ends at last position
//    3 - Search ends at middle
heights divideAndConquer(int chimpHeight[], int left, int right) {
	heights pretendents;
	if( left == right ) {
		if ( chimpHeight[left] == luchuHeight ) {
			pretendents.shorter = (left == 0) ? (-1) : (--left);
			pretendents.taller = (right == n) ? (-1) : (++right);
			return pretendents;
		} else if ( luchuHeight > chimpHeight[left] ) {
			pretendents.shorter = chimpHeight[left];
			if ( ++right < n && chimpHeight[right] > luchuHeight ) {
				pretendents.taller = chimpHeight[right];
			} else pretendents.taller = -1;	
			return pretendents;
		} else if ( luchuHeight < chimpHeight[left] ) {
			pretendents.taller = chimpHeight[left];
			if ( --left >= 0 && chimpHeight[left] < luchuHeight ) {
				pretendents.shorter = chimpHeight[left];
			} else pretendents.shorter = -1;	
			return pretendents;
		}
	}
	int mid = left + right / 2;
	if ( chimpHeight[mid] > luchuHeight )  
		return divideAndConquer( chimpHeight, left, mid);
	if ( chimpHeight[mid] < luchuHeight )
		return divideAndConquer( chimpHeight, mid, right);

	// Else...
	pretendents.shorter = (mid - 1 >= 0) ? (mid - 1) : (-1);
	pretendents.taller =  (mid + 1 < n) ? (mid + 1) : (-1);
	return pretendents;
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
		heights pretendents;
		cout << pretendents.shorter << " " << pretendents.taller << endl;
	}
}
