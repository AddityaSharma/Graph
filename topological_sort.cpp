// dfs solution:

/*
intution : we are calling dfs for u which further calls dfs for its adjacent nodes v;
now first dfs call for v will get completed and we put node v in stack and then, 
the dfs call for node u will get over, and we will put that in our stack. -> so we are
actually dfs in suck a fashion that for an edge from u to v, first node v goes into the
stack then node u goes into to stack and hence our required linear ordering of the 
nodes take place.
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
