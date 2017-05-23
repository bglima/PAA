#include <bits/stdc++.h>
using namespace std;

struct city  {
    string name ;
};

struct link  {
    int from, to;
    int cost ;
};

struct compareCon {
    bool operator()(link const & link1, link const & link2) { 
    //   check if "e1" has smaller cost than "e2"
    return link1.cost > link2.cost;
    }
};

map<string, int> cities;
vector<string> cityNames;
vector<int> sets;

int cases, m, n;
int cityCount;

void init(int n);
int set_find( int vector );
bool set_union( int vector1, int vector2 );
void insertCity(string cityName);

int main() {
	string st1, st2;
	int cost;
	
	cin >> cases;
	
	while (cases--) {
		cityCount = 0;
		
		cin >> m;	// Cities w/ network connections
		cin >> n;	// Links btw cities
		
		init(m);
		
		// Reading cities and links
		priority_queue<city, vector<link>, compareCon> pq;
		for( int i = 0; i < n; ++i ) {
			cin >> st1 >> st2 >> cost;
			insertCity(st1); 
			insertCity(st2);
			link l = { cities[st1], cities[st2], cost };
			pq.push(l);	
		}
		
		// Set up union-find environment
		for( int i = 0; i < m; ++i)
			sets[i]=i;
		
		// For each edge, if not a cycle, add it
		int current_edges = 0;
		int total_cost = 0;
		while( !pq.empty() ) {
			link l = pq.top(); pq.pop();
			if( set_union(l.from, l.to) ) {
				++current_edges;
				total_cost += l.cost;
			}
		}
		
		cout << total_cost << endl;
		if( cases != 0 )
			cout << endl;
	}
}

void insertCity(string cityName) {
	if( cities.find(cityName) == cities.end() ) {
		// city does not exists yet
		cities[cityName] = cityCount;
		cityNames[cityCount] = cityName;
		++cityCount;
	}	
}

void init( int n ) {
	cityCount = 0;
	
	sets.clear();
	cities.clear();
	cityNames.clear();
	
	cityNames.resize(n);
	sets.resize(n);
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