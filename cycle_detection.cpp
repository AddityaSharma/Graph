// Detect cycle in undirected graph:

// --> Using Breadth First Search(BFS):
bool checkforcycle(int node, vector<int> &visited, vector<int> adj[]){
    queue<pair<int, int>> q; // <node, parent>
    q.push({node, -1});
    visited[node] = 1;
    
    while(!q.empty()){
        auto front = q.front();
        q.pop();
        int curr_node = front.first;
        int curr_parent = front.second;
        
        for(auto it : adj[curr_node]){
            if(!visited[it]){
                visited[it] = 1;
                q.push({it, curr_node});
            }else if(it != curr_parent) return 1;
        }
    }
    return 0;
}

bool isCycle(int V, vector<int> adj[]){
    vector<int> visited(V+1, 0);
    for(int i = 0; i < V; i++){
        if(!visited[i]){
            if(checkforcycle(i, visited, adj)) return 1;
        }
    }
    return 0;
}

// --> Using Depth First Search(DFS):
bool checkforcycle(int node, int parent, vector<int> &visited, vector<int> adj[]){
    visited[node] = 1;
    
    for(auto it : adj[node]){
        if(!visited[it]) {
            if(checkforcycle(it, node, visited, adj)) return 1;
        } else if(parent != it) return 1;
    }
    
    return 0;
}

bool isCycle(int V, vector<int> adj[]){
    vector<int> visited(V+1, 0);
    for(int i = 0; i < V; i++){
        if(!visited[i]){
            if(checkforcycle(i, -1, visited, adj)) return 1;
        }
    }
    return 0;
}


// Detect cycle in directed graph:

// --> Using Depth First Search(DFS):
bool DFSRec(int node, vector<int> adj[], vector<int> &visited, vector<int> &rec_st){
    visited[node] = 1;
    rec_st[node] = 1;
    
    for(auto it : adj[node]){
        if(!visited[it]){
            if(DFSRec(it, adj, visited, rec_st)) return 1;
        }else if(rec_st[it]) return 1;
    }
    
    rec_st[node] = 0; // backtracking step
    return 0;
}

bool isCyclic(int V, vector<int> adj[]) {
    vector<int> visited(V+1, 0);
    vector<int> rec_st(V+1, 0); // tracks the nodes that are visited by the current DFS call.
    
    for(int i = 0; i < V; i++){
        if(!visited[i]){
            if(DFSRec(i, adj, visited, rec_st)){return 1;}
        }
    }
    
    return 0;
}

// --> Using Breadth First Search(BFS) : kahn's Algorithm
void BFS(vector<int> adj[], int &cnt, queue<int> &q, vector<int> &inDegree){
    while(!q.empty()){
   	    int node = q.front();
   	    q.pop();
   	    cnt++;
   	    
   	    for(int u : adj[node]){
   	        inDegree[u]--;
   	        if(!inDegree[u]) q.push(u); // if indegree of a node becomes zero, push it into the queue.
   	    }
    }
}

bool isCyclic(int V, vector<int> adj[]) {
    vector<int> inDegree(V+1, 0);
    
    // generating indegree of all the nodes.
    for(int i = 0; i < V; i++){
        for(int u : adj[i]) inDegree[u]++;
    }
    
    queue<int> q;
    for(int i = 0; i < V; i++){
        if(!inDegree[i]) q.push(i);
    }
    
    int cnt = 0;
    
    BFS(adj, cnt, q, inDegree);
    return !(cnt == V);
}
