#include<bits/stdc++.h>
using namespace std;

struct edge {
    int from, to;
    int cost;
};

struct compareEdge {
    bool operator()(edge const & e1, edge const & e2) {
        // check if "e1" has smaller dist than "e2"
        return e1.cost > e2.cost;
    }
};

vector<int> sets;

int n, // Number of computer sites (vertex)
    t, // (n-1) previous chosen high-speed lines (previous MST)
    k, // New aditional high-speed lines (new edges)
    m; // Originally avaliable high-speed lines (old edges)

int prev_cost, // Total cost of previous MST
    new_cost;  // Total cost of new MST

int i, from, to, cost;

void init( int n );
int set_find( int vector );
bool set_union( int vector1, int vecto2);

int main() {
    bool first = true;
    while ( cin >> n ) {
        if( !first )
        cout <<  endl;

        // Initialize variables
        init(n);

        // Computing cost of high-speed lines in previous MST
        for( i = 0; i < n-1; ++i) {
            cin >> from >> to >> cost;
            prev_cost += cost;
        }

        // Aditional high-speed lines
        cin >> k;
        priority_queue<edge, vector<edge>, compareEdge> pq;
        for( i = 0; i < k; ++i) {
            cin >> from >> to >> cost;
            edge e = {from, to, cost};
            pq.push(e);
        }

        // Originally avaliable high-speed lines
        cin >> m;
        for( i = 0; i < m; ++i ) {
            cin >> from >> to >> cost;
            edge e = {from, to, cost};
            pq.push(e);
        }

        // Kruskal algorithm
        int current_edges = 0;
        new_cost = 0;
        while ( current_edges < n - 1 ) {
            edge e = pq.top(); pq.pop();
            if ( set_union(e.from, e.to) ) {
                ++current_edges;
                new_cost += e.cost;
            } 
        }

        // Output
        cout << prev_cost << endl << new_cost << endl;
        first = false;
    }
}

void init(int n) {
    prev_cost = 0;
    new_cost = 0;

    sets.clear();
    sets.resize(n+1);  // Sites starts from 1 to n    

    for(int i = 0; i < n+1; ++i)
        sets[i] = i;
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

    // Preserve larger set. Those with smaller index are the largest, siince they didn't change index yet.
    if( sets[set1] < sets[set2] ) 
        sets[set2] = sets[set1];
    else
        sets[set1] = sets[set2];

    return true;
}

