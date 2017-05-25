#include<bits/stdc++.h>

#define ii pair <int, int> 
#define vi vector < int> 
#define vvi vector < vi > 
#define MAX 5005

using namespace std;

struct road {
	int u;
	int v;
	int c;
	int d;
} ;

int dijkstra(vector< vector<road> > &adj_list, int s, int to);
int send(int s, int t, int minn);

int G[MAX][MAX], F[MAX][MAX];
bool V[MAX];

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

	memset(G, 0, sizeof(G));
	memset(F, 0, sizeof(F));
	memset(V, 0, sizeof(V));
	
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
	
	// Reading source and destination
	cin >> u >> v;
	
	cout << dijkstra(adj_list, u, v) << endl;
	
	// Calculating maximum flow
	int total_flow = 0;
	while( int sent = send(u, v, INT_MAX) ) {
		total_flow += sent;
		memset(V, 0, sizeof(V));
	}
	
	cout << total_flow << endl;

	return 0;
}

int send(int s, int t, int minn) {
	V[s] = true;
	
	if (s == t) return minn;
	
	for(int i=0; i<n; i++) {
		int capacity = G[s][i]-F[s][i];
		if (!V[i] && G[s][i]-F[s][i] > 0) {
			if (int sent = send(i, t, min(minn, capacity))) {
				F[s][i] += sent;
				F[i][s] -= sent;
				return sent;
			}
		}
	}
    
    return 0;
}

int dijkstra(vector< vector<road> > &adj_list, int s, int to) {
	int total_cost = 0;
	
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
	// cout << "Shortest path" << endl;
	int v = to;
	total_cost = dist[v];
	do {
		// Uncomment to print locations used
		// cout << v << " " ;
		
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
					// Add to new adjacency list
					new_list[u].push_back(r);
					
					// Add capacity to adjacency matrix
					G[u][v] = G[v][u] += r.c;
				}
		}
	}
	
	adj_list.clear();
	adj_list = new_list;
	
	return total_cost;
}


