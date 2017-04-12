#include <bits/stdc++.h>
using namespace std;

struct station  {
    string name ;
};

struct connection  {
    int from, to;
    int dist ;
};

struct compareCon {
    bool operator()(connection const & con1, connection const & con2) { 
    //   check if "e1" has smaller dist than "e2"
    return con1.dist > con2.dist;
    }
};

map<string, int> stations;
vector<string> stationNames;

vector<int> sets;

int s, c;

void init(int n);
int set_find( int vector );
bool set_union( int vector1, int vector2 );

int main() {
    string st1, st2;
    int dist, total_dist;

    while ( cin >> s >> c ) {       
        if ( s + c == 0 ) return 0; 
        
        init(s);

        // Reading all stations
        for( int i = 0; i < s; ++i ) {
            cin >> st1;
            stations.insert(pair<string, int>(st1, i));
            stationNames.push_back(st1);
        }
        

        // Reading the edges
        priority_queue<connection, vector<connection>, compareCon> pq;
        for( int i = 0; i < c; ++i ) {
            cin >> st1 >> st2 >> dist;
            connection con = { stations[st1], stations[st2], dist };
            pq.push(con);
        }

		// Starting station
        cin >> st1; 
		
		// Set up union-find environment
		for( int i = 0; i < s; ++i ) {
			sets[i] = i;
		}
		
		// For each edge, if not a cycle, add it
		int current_edges = 0;
		total_dist = 0;
		while( !pq.empty() ) {
			connection con = pq.top(); pq.pop();
			if( set_union(con.from, con.to) ) {
				++current_edges;
				total_dist += con.dist;
			}
		}
		
		if( current_edges == s - 1 )
			cout << total_dist << endl;
		else
			cout << "Impossible" << endl;	
		
        
        /*
        cout << s << " " << c << endl;
        for( int i = 0; i < s; ++i) 
            cout << stationNames[i] << endl;
        while( !pq.empty() ) {
            connection con = pq.top(); pq.pop();
            cout << stationNames[ con.from ] << " " <<  stationNames[ con.to ] << " " << con.dist << endl;
        }
        */
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
    stations.clear();
    stationNames.clear();
    sets.clear();

    sets.resize(n);
}


