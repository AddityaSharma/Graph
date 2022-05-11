// dfs solution:

/*
intution : we are calling dfs for node u which further calls dfs for its adjacent nodes v; now first dfs call for node v will get completed and we put node v in stack 
and then, the dfs call for node u will get over, and we will put that in our stack. -> so we are actually calling dfs in such a fashion that for an edge from u to v, 
first node v goes into the stack then node u goes into to stack and hence our required linear ordering of the nodes take place.
*/    
void dfs(int node, vector<int> &visited, stack<int> &st, vector<int> adj[]){
    visited[node] = 1;
    
    for(auto it : adj[node]){
        if(!visited[it]) dfs(it, visited, st, adj);
    }
    
    st.push(node);
}
vector<int> topoSort(int V, vector<int> adj[]){
    vector<int> topo_sort;
    vector<int> visited(V+1, 0);
    stack<int> st;
    
    for(int i = 0; i < V; i++){
        if(!visited[i]) dfs(i, visited, st, adj);
    }
    
    while(!st.empty()) {
        topo_sort.push_back(st.top());
        st.pop();
    }
    
    return topo_sort;
}



// BFS solution:

/*
step - 1 : generate an indegree vector having indegree of all the nodes.
step - 2 : push the nodes having value of indegree as 0 into the queue.
step - 3 : now follow the general BFS routine:
         --> take out a node from the queue, and put it in our topo_sort vector.
         --> travel all the adjacent nodes of the node taken our from the queue and decrease their indegree by 1.
         --> constantly check if for any node the value of the indegree becomes zero, push that node in the queue.

intution : we are at first pushing the nodes with no dependency (i.e indegree 0) and then traverse the adjancent of those nodes and reduce the indegree of all their 
adjacent nodes; this way we are one by one reducing their dependency and as soon as their dependency becomes 0 we push them into our queue and hence find the linear
ordering of the nodes.
*/  
    
void BFS(vector<int> adj[], vector<int> &topo_sort, queue<int> &q, vector<int> &inDegree){
    while(!q.empty()){
   	    int node = q.front();
   	    q.pop();
   	    topo_sort.push_back(node);
   	    
   	    for(int u : adj[node]){
   	        inDegree[u]--;
   	        if(!inDegree[u]) q.push(u); // if indegree of a node becomes zero, push it into the queue.
   	    }
    }
}

vector<int> topoSort(int V, vector<int> adj[]){
    vector<int> topo_sort;
    vector<int> inDegree(V+1, 0);
    
    // generating indegree of all the nodes.
    for(int i = 0; i < V; i++){
        for(int u : adj[i]) inDegree[u]++;
    }
    
    queue<int> q;
    for(int i = 0; i < V; i++){
        if(!inDegree[i]) q.push(i);
    }
    
    BFS(adj, topo_sort, q, inDegree);
    return topo_sort;
}
	
