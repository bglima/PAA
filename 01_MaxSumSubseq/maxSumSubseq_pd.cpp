#include<bits/stdc++.h>
#define MAX 1000000

using namespace std;

int a[MAX];

struct subseq {
	int sum;
	int l;
	int r;
};

subseq dinamicProgram(int n)
{
	subseq largerSeq;
	int sum = 0, first = 0;
	largerSeq.sum = largerSeq.l = largerSeq.r = 0;
	for(int last = 0; last < n; ++last) {
		sum += a[last];
		if (sum > largerSeq.sum)
		{
			largerSeq.sum = sum;
			largerSeq.l = first;
			largerSeq.r = last;
		}
		else if (sum < 0)
		{
			first = last+1;
			sum = 0;
		}
	}
	
	return largerSeq;
}

int main() {
	int n;
	
	while( cin >> n )
	{
		for(int i = 0; i < n; i++)
			cin >> a[i];
		
		subseq largerSubSeq = dinamicProgram(n);
		cout << largerSubSeq.sum << " " << largerSubSeq.l << " " << largerSubSeq.r << " " << endl;
	}
}