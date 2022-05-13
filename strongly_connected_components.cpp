// Kosaraju's Algorithm to find the Strongly Connected Components(SCC):

// used for topological sort Algorithm:
void dfs(int node, stack<int> &st, vector<int> &vis, vector<int> adj[]) {
    vis[node] = 1; 
    for(auto it: adj[node]) {
        if(!vis[it]) {
            dfs(it, st, vis, adj); 
        }
    }
    
    st.push(node); 
}

// used to find strongly connected components using the transpose Graph:
void revDfs(int node, vector<int> &vis, vector<int> transpose[]) {
    cout << node << " "; // printing the SCC components.
    vis[node] = 1; 
    for(auto it: transpose[node]) {
        if(!vis[it]) {
            revDfs(it, vis, transpose); 
        }
    }
}

void kosaraju_algorithm(int V, vector<int> adj[]){
    // Find Topological ordering of the vertices of Graph:
    stack<int> st;
    vector<int> vis(n, 0); 
    for(int i = 0; i < n; i++) {
        if(!vis[i]) {
            dfs(i, st, vis, adj); 
        }
    } 
    
    // creating the Transpose of the Graph:
    vector<int> transpose[n]; 
    for(int i = 0; i < n; i++) {
        vis[i] = 0; 
        for(auto it: adj[i]) {
            transpose[it].push_back(i); 
        }
    }
    
    // calling DFS algorithm for vectices in order of their finish time -> topological order:
    while(!st.empty()) {
        int node = st.top();
        st.pop(); 
        if(!vis[node]) {
            cout << "SCC: "; 
            revDfs(node, vis, transpose); 
            cout << endl; 
        }
    }
}
