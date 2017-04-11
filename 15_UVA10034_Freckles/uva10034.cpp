#include <bits/stdc++.h>
using namespace std;

struct freckle {
	double x, y;
};

struct edge {
	int from, to;
	double dist;
};

struct compareEdge {
	bool operator()(edge const & e1, edge const & e2) {
		// check if "e1" has smaller dist than "e2"
		return e1.dist > e2.dist;
	}
};

vector<freckle>	freckles;
vector<int> sets;

int cases, n;
double x, y, dist;
double total_dist;

void init(int n);
int set_find( int vector );
bool set_union( int vector1, int vector2 );

int main() {
	cin >> cases;
	
	while( cases-- ) {
		cin >> n;
		init(n);
		
		// Reading all the vertexes locations
		for( int i = 0; i < n; ++i) {
			freckle f;
			cin >> f.x >> f.y;
			freckles[i] = f;
		}
		
		// Push all possible edges to pq
		priority_queue<edge, vector<edge>, compareEdge> pq;
		for( int from = 0; from < n; ++from)
			for( int to = from + 1; to < n; ++to) {
				double dx = freckles[to].x - freckles[from].x;
				double dy = freckles[to].y - freckles[from].y;
				dist = sqrt( dx*dx + dy*dy );
				edge e = {from, to, dist};
				pq.push(e);		
			}
		
		// Set up union-find environment
		for( int i = 0; i < n; ++i ) {
			sets[i] = i;
		}
		
		// For each edge, if not a cycle, add it
		int current_edges = 0;
		total_dist = 0;
		while( current_edges < n - 1 ) {
			edge e = pq.top(); pq.pop();
			if( set_union(e.from, e.to) ) {
				++current_edges;
				total_dist += e.dist;
			}
		}
		
		cout << setprecision(2) << fixed << total_dist << endl;
		
		if( cases != 0 )
			cout << endl;
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

void init(int n) {
	freckles.clear();
	sets.clear();
	
	freckles.resize(n);
	sets.resize(n);
}


