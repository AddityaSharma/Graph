// BFS:
void bfs_traversal(int node, vector<int> adj[], vector<int> &visited, vector<int> &traversal){
    queue<int> q;
    q.push(node);
    visited[node] = 1;
    
    while(!q.empty()){
        int u = q.front();
        q.pop();
        traversal.push_back(u);
        for(auto x : adj[u]){
            if(!visited[x]){
                visited[x] = 1;
                q.push(x);
            }
        }
    }  
}
vector<int> bfs(int V, vector<int> adj[]) {
    vector<int> traversal; // used to store the bfs traversal
    vector<int> visited(V+1, 0);
    
    for(int i = 0; i < V; i++){
        if(!visited[i]){
            bfs_traversal(i, adj, visited, traversal);
        }  
    }
    
    return traversal;
}

// DFS:
void DFSrec(vector<int> adj[], int s, vector<bool> &visited, vector<int> &traversal){
    visited[s] = 1;
    traversal.push_back(s);
    for(auto i : adj[s]){
        if(!visited[i]){
            DFSrec(adj, i, visited, traversal);
        }
    }
}

vector<int> dfs(int V, vector<int> adj[]){
    vector<int> traversal;
    vector<bool> visited(V+1, 0);
    
    // check nodes are 0-based or 1-based indexed.
    for(int i = 1; i <= V; i++){ 
        if(!visited[i]) DFSrec(adj, i, visited, traversal);
    }
    
    return traversal;
}


