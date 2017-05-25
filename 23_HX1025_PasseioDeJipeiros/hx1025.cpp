#include<bits/stdc++.h>

#define ii pair <int, int> 
#define vi vector < int> 
#define vvi vector < vi > 

using namespace std;


struct road {
	int u;
	int v;
	int c;
	int d;
} ;

void dijkstra(vector< vector<road> > &adj_list, int s, int to);

int n,  // Total of all locations
	k,  // Total of cities
	m;  // Total of roads

vector <int> cityOf;
	
int main() {
	int u, v, c, d;
	int i;
	string line;
	
	// Read number of places followed by number of cities
	cin >> n >> k;
	
	cityOf.clear();
	cityOf.resize(n);

	
	cin.clear();
	cin.ignore(1000,'\n');
	for( i = 0; i < k; ++i ) {		
		getline(std::cin,line);
		istringstream  is( line );
		
		// Reading each location per city
		// u is the location
		// i is the city index, for the location		
		while( is >> u ) {
			cityOf[u] = i;		
		}
	}
	
	// Read number of roads
	cin >> m;
	// One adjacency list for the highways, and one for all roads
	vector<road> roads(m);
	vector< vector<road> > adj_list(n);
	
	for( i = 0; i < m; ++i ) {
		// From, To, Capacity, Length
		cin >> u >> v >> c >> d;
		road r = {u, v, c, d};
		roads[i] = r;		
		
		adj_list[u].push_back(r);
	}
	
	cout << endl << endl;
	for( u = 0; u < n; ++u ) {
		for( int j = 0; j < adj_list[u].size(); ++j ) {
			road r = adj_list[u][j];
			cout << r.u << " " << r.v << " " << r.c << " " << r.d << endl;
		}
	}
	
	dijkstra(adj_list, 0, 21);
	
	cout << endl << endl;
	for( u = 0; u < n; ++u ) {
		for( int j = 0; j < adj_list[u].size(); ++j ) {
			road r = adj_list[u][j];
			cout << r.u << " " << r.v << " " << r.c << " " << r.d << endl;
		}
	}

	return 0;
}

void dijkstra(vector< vector<road> > &adj_list, int s, int to) {
	priority_queue< ii, vector<ii>, less<ii> > queue;
	
	vector<int> dist(n, INT_MAX); // dist, parent
	vector<int> visited(n, false);
	vector<int> prev(n, -1);
	
	dist[s] = 0;
	queue.push( make_pair(dist[s],s) );
	
	// Finding shortest path from 's' to all vertices
	while( !queue.empty() )
	{
		int u = queue.top().second;
		queue.pop();
		
		if(visited[u]) continue;
		
		visited[u] = true;
		
		for (int j=0; j < adj_list[u].size(); ++j) {
			int v = adj_list[u][j].v;
			int d = adj_list[u][j].d;
			
			if ( dist[u] + d < dist[v] )
			{
				dist[v] = dist[u] + d;
				queue.push(make_pair(dist[v], v));
				prev[v] = u;
			}
		}
	}
	
	// We need the list of used cities
	map<int, bool> cities_used;
	
	// Now, we have the shortest path...
	cout << "Shortest path" << endl;
	int v = to;
	do {
		cout << v << " " ;
		int city = cityOf[v] ;
		
		// Storing all used cities in a map
		if ( cities_used.find( city ) == cities_used.end() ) {
			cities_used[city] = true;
		}
			
	} while( (v = prev[v]) != -1 );
	
	// Creating a new adjacency list, where all locations are from visited cities
	vector< vector<road> > new_list(n);
	for(int u = 0; u < adj_list.size(); ++u ) {
		for( int j = 0; j < adj_list[u].size(); ++j) {
			road r = adj_list[u][j];
			int v = r.v;
			
			// Add at new adjacency list only those roads who connects visited cities
			if( cities_used.find( cityOf[u] ) != cities_used.end() &&
				cities_used.find( cityOf[v] ) != cities_used.end() ) {
					new_list[u].push_back(r);
				}
		}
	}
	
	adj_list.clear();
	adj_list = new_list;

}
