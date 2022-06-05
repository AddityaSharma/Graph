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

// Shortest Path in Undirected Graph from a given source - Dijkstra's Algorithm:
// In Dijkstra's Algorithm, we use a minimum priority queue to keep track of nodes instead of a simple queue data structure, we store nodes in <distance, node> 
// fashion. initially we put the source node in the priority queue as <0, source_node>, where 0 is the distance of source node from itself. after this we 
// implement a bfs kind of an algorithm. we maintain a distance array and mark the distance of all the nodes to be INT_MAX and marking the distance of source node
// to be zero, then in each iteration we take out a node from the priority queue and traverse all its adjacent nodes, while traversing the nodes, we compute the 
// distance required to reach that node and if the newly computed distance is lesser than the one already there in the distance array, then we update the shorter
// distance in the distance array and at the same time put that node along with the shorter distance in the priority queue. we keep repeating the same process, until 
// the priority queue becomes empty.
// now there can be instances where we have multiple instances of a single node in our priority queue, and thats totally fine, as we are placing the elements in
// priority queue as <distance, node> the occurance with minimum distance will be always on the top and we will always perfrom our logic using that node first and 
// then will all the other occurances of that node, this way they are simply ignored as they will never provide us with a shorter distance. 

// algorithm step-by-step explanation:
// 1) We would be using a min-heap and a distance array of size N initialized with infinity (indicating that at present none of the nodes are reachable from the
// source node) and initialize the distance to source node as 0.
// 2) We push the source node to the queue.
// 3) For every node at the top of the queue we pop that element out and look out for its adjacent nodes. If the current reachable distance is better than the 
// previous distance indicated by the distance array, we update the distance and push it in the queue.
// 4) A node with a lower distance would be at the top of the priority queue as opposed to a node with a higher distance. By following the steps 3, until our queue
// becomes empty, we would get the minimum distance from the source node to all other nodes.

void dijkstra_Algorithm(vector<pair<int, int>> adj[], int N, int src){
	priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int>>> pq; // minimum priority queue
    vector<int> distTo(V+1, INT_MAX); // 0-indexed array for calculating shortest paths
    	
    distTo[src] = 0;
    pq.push(make_pair(0,src));	// <distance ,source>
    	
    while(!pq.empty()){
    	int curr_node_dist = pq.top().first;
    	int curr_node = pq.top().second;
    	pq.pop();
    
    	for(auto it : adj[curr_node]){
    		int next_node = it.first;
    		int next_node_dist = it.second;
    		if(distTo[next_node] > next_node_dist + next_node_dist){
    			distTo[next_node] = next_node_dist + next_node_dist;
    			pq.push(make_pair(next_node_dist, next_node));
    		}
    	}
    }
	
	cout << "The distances from source " << src << " are : \n";
	for(int i = 1 ; i<=n ; i++)	cout << distTo[i] << " ";
}


// Shortest Path Algorithm for Graphs with negative weight edges - Bellman Ford Algorithm: - T.C : O(VE) | S.C : O(V)

// Bellman Ford Algorithm only works for Directed Acyclic Graphs, if we want to apply this algorithm on undirected graph
// then we have to replace each undirected edge by a pair of directed edges. Also there should not be negative cycles in
// graph
// Bellman Ford algorithm helps us to find negative weight cycles in the graph, if any.
struct node {
    int u;
    int v;
    int wt; 
    node(int first, int second, int weight) {
        u = first;
        v = second;
        wt = weight;
    }
};

int main(){
    int N, m;
    cin >> N >> m;
    vector<node> edges; 
    for(int i = 0; i < m; i++) {
        int u, v, wt;
        cin >> u >> v >> wt; 
        edges.push_back(node(u, v, wt)); 
    }

    int src;
    cin >> src; 
	
    // Main logic of Bellman Ford Algorithm:
    int inf = 1e8; 
    vector<int> dist(N, inf); 

    dist[src] = 0; 

    // relaxing all edges (N-1) times:
    for(int i = 1; i <= N-1; i++) {
        for(auto it : edges) {
            if(dist[it.u] + it.wt < dist[it.v]) {
                dist[it.v] = dist[it.u] + it.wt; 
            }
        }
    }

    /*
    // check for negative cycle in graph
    int flag = 0; 
    for(auto it: edges) {
        if(dist[it.u] + it.wt < dist[it.v]) { 
            flag = 1; 
            break; 
        }
    }

    if(flag) {
        "Negative cycle detected";
        return 0;
    }
    */

    // printing out the shortest distances for each vertex from given source:
    if(!flag) {
        for(int i = 0; i < N; i++) {
            cout << i << " " << dist[i] << endl;
        }
    }

    return 0;
}
