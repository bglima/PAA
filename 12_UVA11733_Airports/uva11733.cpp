#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<vii> vvii;


vi taken;				// Vertices already processed
priority_queue<ii> pq;	// Vertices in the frontier, where the tree can grow
vvii AdjList;			// Adjacency list of each vertex

void process(int vtx);				// Update priority queue of vertex that are still not visited

int main () {
	int caseNumber, 	// Test case id
		minCost, 		// Minimum cost for the case
		numOfAirports;	// Number of airports for the case
	
	int t,	// Number of test cases
		n,	// Number of locations ( vertexes )
		m,	// Number of roads	( edges )
		a,	// Cost of each airport
		x,	// Location index 1. 1 <= x <= n
		y,	// Location index 2. 1 <= y <= n
		c; 	// Cost of building a road between location 1 and 2
	
	
	cin >> t;
	
	for ( caseNumber = 1; caseNumber <= t; ++caseNumber ) {
		cin >> n >> m >> a;
		
		// Cleaning vectors and initializing variables
		pq = priority_queue<ii>();
		taken.clear();
		AdjList.clear();
		numOfAirports = 0;
		minCost = 0;
		
		// Resizing vectors to correspond to locations number. 
		// Remember: Any vertex index goes from 1 to n. In order to simplificate notations,
		// we'll not use index 0. Thus, we need n+1 places.
		taken.resize(n+1, 0);	// All vertexes initiate as non-processed (taken = 0)
		AdjList.resize(n+1);
		
		// Populating the adjacency list
		for ( int j = 0; j < m; ++j ) {
			cin >> x >> y >> c;
			AdjList[y].push_back( ii(x, c) );
			AdjList[x].push_back( ii(y, c) );
		}
		
		for( int v = 1; v <= n; ++v ) {
			if ( !taken[v] ) {
				// Calculate subtree cost.
				
				// Generating adjacency list for first vertex
				process(v);
				
				// Visiting each vertex and generating the tree
				int subTreeCost = 0;
				
				while( !pq.empty() ) {
					ii front = pq.top(); pq.pop();
					int u = -front.second, w = -front.first;
					if (!taken[u]) {
						// Checking if building an airport is cheaper than building a road
						// If it's the same price, prefer to build a road, in order to connect more cities.
						if ( a <= w ) {
							while(!pq.empty())	// Cleaning adjacency list, as it would be connected via airport
								pq.pop();
							break;
						} else {
							subTreeCost += w;	// Add road cost
						}
						
						process(u);	// Update adjacency list from vertex
					}
				}
				
				minCost += subTreeCost + a;
				numOfAirports++;
			}
		}
		

		cout << "Case #" << caseNumber << ": " << minCost << " " << numOfAirports << endl;	
	}
	
	return 0;
}

// Add adjacent vertex from vtx to adjacenct list
void process(int vtx) {
	taken[vtx] = 1;												// Mark vertex as processed
	for (int j = 0; j < (int)AdjList[vtx].size(); j++){			// For each adjacent vertex...
		ii v = AdjList[vtx][j];
		if (!taken[v.first]) pq.push(ii(-v.second, -v.first));	// Less weight goes first
	}
}

