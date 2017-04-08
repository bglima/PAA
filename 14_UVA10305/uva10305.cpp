#include<bits/stdc++.h>

using namespace std;

int n, m;

vector < vector < int > > adj_list;
vector < bool > visited;
vector < int > order;
vector < int > in_degree;

void init( int size ) {
	adj_list.clear();
	in_degree.clear();
    visited.clear();
	order.clear();
	
	adj_list.resize( size + 1 );
	in_degree.resize( size + 1 );
    visited.resize( size + 1 );

    for( int i = 0; i <= m; ++i ) {
        visited[i] = false;
        in_degree[i] = 0;
    }
}

void add_edge(int from, int to ) {
	adj_list[from].push_back( to );
	++in_degree[to];
}

void dfs( int current ) { 
	if ( visited[current] == true )
		return;
	
    visited[ current ] = true;
		
    for( int i = 0; i < adj_list[current].size(); ++i ) {
        int adjacent = adj_list[current][i];

        if ( !visited[adjacent] )
            dfs( adjacent );
    }
	order.push_back( current );	
	
}

int main() {
	int from, to;
	while ( true ) {
		cin >> m >> n;
		if (  m == 0 && n == 0 )
			break;
		init ( m );
		for ( int i = 0; i < n; ++i ) {
			cin >> from >> to;
			add_edge( from, to );
		}   
		
		for( int i = 1; i <= m; ++i)
			if ( in_degree[i] == 0 ) dfs(i);
		
		while( !order.empty() ) {
			cout << order.back() << " ";	
			order.pop_back();
		}
		cout << endl;
	}
	return 0;
}
