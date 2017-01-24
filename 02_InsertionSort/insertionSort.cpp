#include<bits/stdc++.h>
#define MAX 100000

using namespace std;

int a[MAX], n;

int insertionSort() {
	int i, key;
	for (i = 1; i < n; ++i)
	{
		key = a[i];
		int j = i-1;
		
		while( j >= 0 && a[j] > key )
		{
			a[j+1] = a[j];
			--j;
		}
		a[j+1] = key;
	}
}

int main()
{
	int i;
	while( cin >> n )
	{
		for(i = 0; i < n; ++i)
			cin  >> a[i];
		
		insertionSort();
		
		for(i = 0; i < n; ++i)
			cout << "[" << a[i] << "]";
		cout << endl;
		
	}
}