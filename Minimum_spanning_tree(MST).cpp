// Kruskal's Algorithm - Along with DSU implementation.

// structure of a node in graph.
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

bool comp(node a, node b) {
    return a.wt < b.wt; 
}

// Disjoint Set implementation: -> we require a rank and parent vector for DSU.
int findPar(int u, vector<int> &parent) {
    if(u == parent[u]) return u; 
    return parent[u] = findPar(parent[u], parent); // path compression.
}

void unionn(int u, int v, vector<int> &parent, vector<int> &rank) {
    u = findPar(u, parent);
    v = findPar(v, parent);
    if(rank[u] < rank[v]) parent[u] = v;
    else if(rank[v] < rank[u]) parent[v] = u;
    else{
    	parent[v] = u;
    	rank[u]++; 
    }
}
// Disjoint set implementations ends.

int main(){
    // taking a graph as input directly in a vector named 'edges'.
    // driver code:
	int N=5,m=6;
	vector<node> edges; 
	edges.push_back(node(0,1,2));
	edges.push_back(node(0,3,6));
	edges.push_back(node(1,0,2));
	edges.push_back(node(1,2,3));
	edges.push_back(node(1,3,8));
	edges.push_back(node(1,4,5));
	edges.push_back(node(2,1,3));
	edges.push_back(node(2,4,7));
	edges.push_back(node(3,0,6));
	edges.push_back(node(3,1,8));
	edges.push_back(node(4,1,5));
	edges.push_back(node(4,2,7));
  
  // we want the egdes joining two nodes in increasing order of their weight - so we sort them.
	sort(edges.begin(), edges.end(), comp); 
	
  // creating rank and parent vectors for Disjoint set implementation.
	vector<int> parent(N);
	for(int i = 0; i < N; i++) parent[i] = i; 
	vector<int> rank(N, 0); 
	
  // traversing the 'edges' vector and finding which edge will be taken in account for our MST.
	int cost = 0;
	vector<pair<int,int>> mst; // this vectors cantain the edges that are used for MST. 
	for(auto it : edges) {
	    if(findPar(it.v, parent) != findPar(it.u, parent)) {
	        cost += it.wt; 
	        mst.push_back({it.u, it.v}); // storing the edges that we have considered.
	        unionn(it.u, it.v, parent, rank); 
	    }
	}
  
  // printing out the required edges and the total cost of MST. 
	cout << cost << endl;
	for(auto it : mst) cout << it.first << " - " << it.second << endl; 
	return 0;
}


// Prim's Algorithm Implementation:

// use this implementation if we need the edges that are required in the MST.
void prims_Algorithm(vector<pair<int, int> adj[], int N){
	vector<int> parent(N, -1);
 	vector<int> key(N, INT_MAX);
  	vector<int> mstSet(N, 0);
  	priority_queue<pair<int,int>, vector <pair<int,int>> , greater<pair<int,int>>> pq; // pq format - <weight, node>
  
  	key[0] = 0; 
  	parent[0] = -1; 
  	pq.push({0, 0});

  	while(!pq.empty()){ 
      	int u = pq.top().second; // every node which has been into priority queue once, will become part of MST as soon as it is taken out from pq. 
      	pq.pop(); 
      	mstSet[u] = true; 

      	for(auto it : adj[u]) {
        	int v = it.first;
          	int weight = it.second;
          	if (!mstSet[v] && weight < key[v]){ // make sure while traversing the adjacent nodes, we will not take in account the nodes which are already in the MST.
              	parent[v] = u;
              	key[v] = weight; 
              	pq.push({weight, v}); // when we put a node in our pq, we mean to say that we have reached out that node via the minimum possible distance so far.
              	// also having multiple instances of a single node with different weights in our priority queue is totally fine, as for a given node we always take the
              	// one with the minimum weight and use it to traverse its adjacency list, this way when we again encounter that node, we simply ignore them.
          	}
      	}
  	} 

  	// printing out the nodes of the MST.
  	for (int i = 1; i < N; i++) cout << parent[i] << " - " << i << " \n";
}

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

// if we want the cost of the edges:
// --> one way is to traverse the edges we have marked that will be in our MST.
// --> another way is to add the cost of the edges when we mark an edge to be in the MST. - (code below)
int prims_algorithm(int V, vector<vector<int>> adj[]){
    vector<int> parent(V, -1);
    vector<int> key(V, INT_MAX);
    vector<int> mstSet(V, 0);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    key[0] = 0;
    parent[0] = -1;
    mstSet[0] = 1;
    pq.push({0, 0}); // -> {weight, node}
    
    int cost = 0;
    
    while(!pq.empty()){
        int u = pq.top().second;
        int edgeWeight = pq.top().first;
        pq.pop();
        
        if(!mstSet[u]){ // this is the only change we have made to get the cost of the MST.
            mstSet[u] = 1;
            cost += edgeWeight;
        }
        
        for(auto v : adj[u]){
            int node = v[0];
            int weight = v[1];
            if(!mstSet[node] && weight < key[node]){
                key[node] = weight;
                parent[node] = u;
                pq.push({weight, node});
            }
        } 
    }
    
    return cost;
}
