#include <bits/stdc++.h>

using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> ii;
typedef vector<ii> vii;

vii	critical_links;
vvi server;
vector<int> discovery;
vector<int> low;

int disc_time, number_of_servers;

void dfs(int parent, int u);
void init(int number_of_servers);

int main(){
    int from, to, server_size;
    while(cin >> number_of_servers){
		init(number_of_servers);
		
		// Reading servers
        for(int i = 0; i < number_of_servers; ++i){	
            scanf("%d (%d)",&from,&server_size);  
			
			for (int j = 0; j < server_size; ++j)
            {
                cin >> to;
                server[from].push_back(to);
                // server[to].push_back(from);
				// UVA say it's bidirectinal...
				// But it does not accept this way :/
            }
		}

		
		// Calculating critical links
		for(int i = 0; i < number_of_servers; ++i)
			if ( !discovery[i] ) dfs(i, i);
		
		// Sorting critical links
		sort(critical_links.begin(), critical_links.end());
		
		// Output
		cout << critical_links.size() << " critical links" << endl;
		for (int i = 0; i < critical_links.size(); ++i) {
			 cout << critical_links[i].first << " - "
                 << critical_links[i].second << endl;
		}
		cout << endl;
    }
    return 0;
}

void dfs(int parent, int u) {
	// Starting vertex
	discovery[u] = low[u] = ++disc_time;
	int v;
	
	// For each adjacent vertex
	for(int i=0; i<server[u].size(); ++i) {
		// Take vertex number
		v = server[u][i];
		if (v != parent) {
			// If already visited, it's a back edge
			if(discovery[v]) {
				low[u] = min(low[u], discovery[v]);
			} else {
			// Else, do DFS and compare lows
				dfs(u, v);
				low[u] = min(low[u], low[v]);
				if(low[v] > discovery[u])
					critical_links.push_back(make_pair(min(u, v), max(u, v)));
			}
		}
	}
}

void init(int number_of_servers) {
	disc_time = 0;
	
	server.clear();
	discovery.clear();
	low.clear();
	critical_links.clear();
	
	server.resize(number_of_servers);
	discovery.resize(number_of_servers, 0);
	low.resize(number_of_servers, 0);
}
