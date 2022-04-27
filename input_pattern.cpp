#include <bits/stdc++.h>
using namespace std;

// adjacency matrix representation -> undirected graph:
int main() {
	int n, m;
	cin >> n >> m; 
	
	// declare the adjacent matrix 
	int adj[n+1][n+1]; 
	
	// take edges as input 
	for(int i = 0; i < m; i++) {
	    int u, v; 
	    cin >> u >> v;
	    adj[u][v] = 1; 
	    adj[v][u] = 1; 
	}
	return 0;
}


// adjacency matrix representation -> directed graph:
int main() {
	int n, m;
	cin >> n >> m; 
	
	// declare the adjacent matrix 
	int adj[n+1][n+1]; 
	
	// take edges as input 
	for(int i = 0; i < m; i++) {
	    int u, v; 
	    cin >> u >> v;
	    adj[u][v] = 1; 
	}
	return 0;
}


// adjacency list representation -> undirected graph:
int main() {
	int n, m;
	cin >> n >> m; 
	
	// declare the adjacent matrix 
	vector<int> adj[n+1]; 
	
	// take edges as input 
	for(int i = 0; i < m; i++) {
	    int u, v; 
	    cin >> u >> v;
	    adj[u].push_back(v); 
	    adj[v].push_back(u); 
	}
	return 0;
}

// adjacency list representation -> directed graph:
int main() {
	int n, m;
	cin >> n >> m; 
	
	// declare the adjacent matrix 
	vector<int> adj[n+1]; 
	
	// take edges as input 
	for(int i = 0; i < m; i++) {
	    int u, v; 
	    cin >> u >> v;
	    adj[u].push_back(v); 
	}
	return 0;
}

// adjacency list representation -> undirected graph with weights:
int main() {
	int n, m;
	cin >> n >> m; 
	
	// declare the adjacent matrix 
	vector<pair<int, int>> adj[n+1]; 
	
	// take edges as input 
	for(int i = 0; i < m; i++) {
	    int u, v, wt; 
	    cin >> u >> v >> wt;
	    adj[u].push_back({v, wt}); 
	    adj[v].push_back({u, wt}); 
	}
	return 0;
}

// adjacency list representation -> undirected graph with weights:
int main() {
	int n, m;
	cin >> n >> m; 
	
	// declare the adjacent matrix 
	vector<pair<int, int>> adj[n+1]; 
	
	// take edges as input 
	for(int i = 0; i < m; i++) {
	    int u, v, wt; 
	    cin >> u >> v >> wt;
	    adj[u].push_back({v, wt}); 
	}
	return 0;
}

