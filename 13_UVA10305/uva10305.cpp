#include<bits/stdc++.h>

using namespace std;

int n, m;

vector < vector < int > > adj_list;
vector < bool > visited;
vector < int > in_degree;

void init( int size ) {
	adj_list.clear();
	in_degree.clear();
    visited.clear();


	adj_list.resize( size + 1 );
	in_degree.resize( size + 1 );
    visited.resize( size + 1 );

    for( int i = 0; i <= n; ++i ) {
        visited[i] = false;
        in_degree[i] = 0;
    }
}

void add_edge(int from, int to ) {
	adj_list[from].push_back( to );
	++in_degree[to];
}

void dfs( int current ) { 
    visited[ current ] = true;
    cout << "Passed visited check at " << current << endl;
    for( int i = 0; i < adj_list[current].size(); ++i ) {
        int adjacent = adj_list[current][i];
        cout << " Adjacent: " << adjacent<< endl;
        if ( !visited[adjacent] )
            dfs( adjacent );
        }
}

int main() {
	int from, to;
	while ( true ) {
		cin >> m >> n;
		if (  m == 0 && n == 0 )
			break;
		init ( n );
		cout << "Init ok" << endl;
		for ( int i = 0; i < n; ++i ) {
			cin >> from >> to;
			add_edge( from, to );
		}   
		cout << "Edges added" << endl;
		
        dfs(1);
	}
	return 0;
}
