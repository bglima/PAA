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

void dijkstra(vector< vector<road> > &adj_list, int s);

int n,  // Total of all locations
	k,  // Total of cities
	m;  // Total of roads
	
int main() {
	int u, v, c, d;
	int i;
	string line;
	
	
	cin >> n >> k;
	
	vector <int> cityOf(n);
	
	// Read number of places followed by number of cities
	cout << n << " " << k << endl;	
	
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
	
	dijkstra(adj_list, 0);

	return 0;
}

void dijkstra(vector< vector<road> > &adj_list, int s) {
	priority_queue< ii, vector<ii>, less<ii> > queue;
	
	vector<int> dist(n, INT_MAX); // dist, parent
	vector<int> visited(n, false);
	vector<int> prev(n, -1);
	
	dist[s] = 0;
	queue.push( make_pair(dist[s],s) );
	
	// Finding the shortest path from 's' to all vertices
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
	
	for( int i = 0; i < n; ++i ) {		
		cout << "Distance from  0 to " << i << " : " << dist[i] << endl;
	} 
	
	cout << "Shortest path" << endl;
	int i = 21;
	do {
		cout << i << " " ;
	} while( (i = prev[i]) != -1 );
	
}
