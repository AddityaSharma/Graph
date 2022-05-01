// Shortest Path in Undirected Graph from a given source with Unit Weights:

void BFS(vector<int> adj[], int N, int src) { 
	int dist[N];
	for(int i = 0;i<N;i++) dist[i] = INT_MAX; 
	queue<int>  q;
	
	dist[src] = 0;
	q.push(src); 

	while(!q.empty()){ 
		int node = q.front(); 
		q.pop();
		 
		for(auto it:adj[node]){
		    if(dist[node] + 1 < dist[it]){
		        dist[it]=dist[node]+1;
		        q.push(it);
		    }
		} 
	} 
    
    // printing the shortest distance.
	for(int i = 0;i<N;i++) cout << dist[i] << " "; 
}

// Shortest Path in Directed Acyclic Graph (DAG):
// step - 1 : find the topological sorting order for all the nodes.
// step - 2 : create a distance vector and marks distance of all nodes to be infinity, marks the distance of source node to be 0;
// step - 3 : now one by one take nodes as in the topological order and for each node perform the following tasks:
//         --> check if the distance[node] != infinity.
//         --> if it is not infinity, then that node is already reached out before.
//         --> traverse all the adjacent nodes of that node and for every node check if the distance[node] + adjancent_node.distance < distance[adjancent_node]
//             if yes then update the distance[adjancent_node] = distance[node] + adjancent_node.distance

void findTopoSort(int node, int vis[], stack<int> &st, vector<pair<int,int>> adj[]) {
    vis[node] = 1; 
    for(auto it : adj[node]) {
        if(!vis[it.first]) {
            findTopoSort(it.first, vis, st, adj); 
        }
    }
    st.push(node);
}

void shortestPath(int src, int N, vector<pair<int,int>> adj[]){ 
	int vis[N] = {0};
	stack<int> st; 
	for (int i = 0; i < N; i++) 
		if (!vis[i]) findTopoSort(i, vis, st, adj); 
			
	int dist[N]; 
	for (int i = 0; i < N; i++) dist[i] = 1e9; 
	dist[src] = 0; 

	while(!st.empty()) {  
		int node = st.top(); 
		st.pop(); 
 
		if (dist[node] != INF) {
		    for(auto it : adj[node]) {
		        if(dist[node] + it.second < dist[it.first]) {
		            dist[it.first] = dist[node] + it.second; 
		        }
		    }
		}
	} 

    // print shortest distance for all nodes
	for (int i = 0; i < N; i++) (dist[i] == 1e9)? cout << "INF ": cout << dist[i] << " "; 
}
