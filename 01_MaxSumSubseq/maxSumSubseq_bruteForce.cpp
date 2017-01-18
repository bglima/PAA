#include<bits/stdc++.h>
#define MAX 100000

using namespace std;

int main() {
	int n, a[MAX];
	int sum, maxSum, left, right;
	
	while( cin >> n ) 
	{
		for(int i = 0; i < n; i++)
			cin >> a[i];
		
		// Inicializa os dados
		maxSum = 0, left = -1, right = -1;
		for(int i = 0; i < n; i++)
		{
			// Cada vez que muda o left, zera a soma.
			sum = 0;
			for(int j = i; j < n; j++)
			{
				// Soma = Soma + novoElemento
				sum = sum + a[j];
				// Atualiza o maior valor e guarda os índices
				if( sum > maxSum )
				{
					maxSum = sum;
					left = i;
					right = j;
				}
			}
		}
			
		cout << "Left=" << left << " Right=" << right << " Sum= " << maxSum << endl;	
	}
}
