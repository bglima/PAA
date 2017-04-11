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
int cnt=0;


int main() {
    string st1, st2, from;
    int dist;

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

        cin >> from;

        cout << ++cnt << endl;
    
        
        cout << s << " " << c << endl;
        for( int i = 0; i < s; ++i) 
            cout << stationNames[i] << endl;
        while( !pq.empty() ) {
            connection con = pq.top(); pq.pop();
            cout << stationNames[ con.from ] << " " <<  stationNames[ con.to ] << " " << con.dist << endl;
        }
        
    } 
    return 0;
}

void init(int n) {
    stations.clear();
    stationNames.clear();
    sets.clear();

//    stations.resize(n);
//    stationNames.resize(n);
    sets.resize(n);
}


