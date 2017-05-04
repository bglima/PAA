#include<bits/stdc++.h>

using namespace std;

struct road {
	int from, to;
	int cost;
};

struct compareRoad {
	bool operator()(road const & r1, road const & r2) {
		return r1.cost < r2.cost;
	}
};


int set_find( int vector );
bool set_union( int vector1, int vector2 );

vector<int> sets;

int main() {
	int cases;
	int n, m;
	int from, to, cost;
	int total_cost, mst_cost;
	
	cin >> cases;
	
	while(cases--) {
		total_cost = 0;
		mst_cost = 0;

		cin >> n >> m;
		
		// Junctions goes from 1 up to n
		sets.clear(); 
		sets.resize(n+1);
		for(int i = 0; i <= n; ++i) {
			sets[i] = i;
		}
		
		// Priority queue with roads. Larger costs comes first.
		priority_queue<road, vector<road>, compareRoad> pq;
		for(int i = 0; i < m; ++i) {
			cin >> from >> to >> cost;
			road r = {from, to, cost};
			pq.push(r);
			total_cost+=cost;
		}
		
		// Kruskal for the Maximmun Spaning Tree
		int roads_used=0;
		while( roads_used < n - 1 )	{
			road r = pq.top(); pq.pop();
			if( set_union(r.from, r.to) ) {
				++roads_used;
				mst_cost += r.cost;
			}
		}

		// The camera costs will be the cost of all lefting edges.
		cout << total_cost - mst_cost << endl;
	}
	return 0;
}

int set_find( int vector ) {
	if ( sets[vector] == vector )
		return vector;
	
	return set_find(sets[vector]);
}

bool set_union( int vector1, int vector2 ) {
	int set1 = set_find( vector1 );
	int set2 = set_find( vector2 );
	if ( set1 == set2 )
		return false;
	
	// Preserve larger set. Those with smaller index are the largest, since they didn't change index yet.
	if( sets[set1] < sets[set2] ) {
		sets[set2] = sets[set1];
	} else {
		sets[set1] = sets[set2];
	}
	return true;
}

