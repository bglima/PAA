#include<bits/stdc++.h>
#define MAX 1000000

using namespace std;

int a[MAX];

struct subseq {
	int sum;
	int l;
	int r;
};

subseq divideAndConquer(int left, int right)
{
	// Para quando left = right (1 elem. no interv.)
	if (left == right) {
		// Se o elemento for positivo, retorne o mesmo
		if( a[left] > 0 ) {
			subseq el;
			el.sum = a[left];
			el.l = left;
			el.r = left;
			return el;
		}
		// Caso contrário, o elmento nulo será a soma máxima
		else {
			subseq el;
			el.sum = 0;
			el.l = -1;
			el.r = -1;
			return el;
		}
	} 
	else 
	{
		subseq lSide;
		subseq rSide;
		int sum = 0;
		int mid = (left + right) / 2;
		
		// Procurando o préfixo ótimo
		lSide.sum = 0;
		lSide.r = mid;
		for(int i = mid; i >= left; i--)
		{
			sum = sum + a[i];
			if( sum > lSide.sum ) {
				lSide.sum = sum;
				lSide.l  = i;
			}
		}
		
		// Procurando o sufixo ótimo
		rSide.sum = 0;
		rSide.l = mid+1;
		sum = 0;
		for(int i = mid+1; i <=right; i++)
		{
			sum = sum + a[i];
			if( sum > rSide.sum ) {
				rSide.sum = sum;
				rSide.r = i;
			}
		}
		
		subseq lMaxSubseq = divideAndConquer(left, mid);
		subseq rMaxSubseq = divideAndConquer(mid+1, right);
		subseq mMaxSubseq;
		mMaxSubseq.sum = rSide.sum + lSide.sum;
		mMaxSubseq.r = rSide.r;
		mMaxSubseq.l = lSide.l;
		
		// Subsequência máxima está no lado esquerdo
		if( lMaxSubseq.sum >= rMaxSubseq.sum && lMaxSubseq.sum >= mMaxSubseq.sum) return lMaxSubseq;
		
		// Subsequência máxima está no lado direito
		if( rMaxSubseq.sum >= lMaxSubseq.sum && rMaxSubseq.sum >= mMaxSubseq.sum) return rMaxSubseq;
		
		// Subsequência máxima está cruzando
		return mMaxSubseq;
	}	
}

int main() {
	int n;
	
	while( cin >> n )
	{
		for(int i = 0; i < n; i++)
			cin >> a[i];
		
		subseq largerSubSeq = divideAndConquer(0, n-1);
		cout << largerSubSeq.sum << " " << largerSubSeq.l << " " << largerSubSeq.r << " " << endl;
	}
}