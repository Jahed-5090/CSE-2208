#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

// Universal Edge structure
struct Edge {
    int u, v, w;
};

class GraphTemplate {
public:
    int V, E, src;
    bool isDirected;
    vector<Edge> edgeList;
    vector<vector<pair<int, int>>> adjList;

    // Initializes memory for the graph
    void init(int nodes, bool directed) {
        V = nodes;
        isDirected = directed;
        adjList.assign(V, vector<pair<int, int>>());
        edgeList.clear();
    }

    // Safely adds an edge to both the Edge List and Adjacency List
    void addEdge(int u, int v, int w) {
        edgeList.push_back({u, v, w});
        adjList[u].push_back({v, w});
        if (!isDirected) {
            // Note: In an edge list, undirected graphs usually store both directions
            edgeList.push_back({v, u, w}); 
            adjList[v].push_back({u, w});
        }
    }

    // Generates a random graph without duplicate edges
    void generateRandom(int nodes, int edges, bool directed) {
        init(nodes, directed);
        E = edges;
        
        // High-quality random number generator   
        mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
        uniform_int_distribution<int> nodeDist(0, V - 1);  // 0-indexed nodes
        uniform_int_distribution<int> weightDist(1, 100);  // Weights from 1 to 100

        int count = 0;
        vector<vector<bool>> used(V, vector<bool>(V, false)); // Tracks existing edges

        while (count < E) {
            int u = nodeDist(rng);
            int v = nodeDist(rng);
            
            // Skip self-loops and duplicate edges
            if (u == v || used[u][v]) continue;

            addEdge(u, v, weightDist(rng));
            
            used[u][v] = true;
            if (!directed) used[v][u] = true;
            count++;
        }
    }

    // Reads lab parameters from config.txt
    void readConfig(const string& filename) {
        ifstream fin(filename);
        if (!fin) { 
            cerr << "Error: Cannot open " << filename << "\n"; 
            exit(1); 
        }
        
        int directedFlag;
        // Expected format: Nodes Edges Directed(1=Yes,0=No) SourceNode
        fin >> V >> E >> directedFlag >> src;
        isDirected = (directedFlag == 1);
        fin.close();

        // Auto-generate the graph after reading config
        generateRandom(V, E, isDirected);
    }

    // Dumps the generated graph to your output file
    void writeGraph(ofstream& fout) {
        fout << "--- Generated Graph Edges ---\n";
        for (auto& e : edgeList) {
            fout << e.u << " -> " << e.v << " : " << e.w << "\n";
        }
        fout << "\n";
    }
};

// ==========================================
// PUT YOUR LAB ALGORITHM HERE
// ==========================================
void solve(GraphTemplate& G, ofstream& fout) {
    // You can access G.V, G.E, G.src, G.edgeList, and G.adjList directly here.
    
    fout << "--- Algorithm Results ---\n";
    fout << "Simulating algorithm processing from source " << G.src << "...\n";
    
    // Example: Print neighbors of the source node
    for(auto& neighbor : G.adjList[G.src]) {
        fout << "Source connects to " << neighbor.first << " with weight " << neighbor.second << "\n";
    }
}

int main() {
    GraphTemplate G;
    
    // 1. Read input and generate graph
    G.readConfig("config.txt");

    // 2. Setup output file
    ofstream fout("output.txt");
    if (!fout) { 
        cerr << "Error: Cannot open output.txt\n"; 
        return 1; 
    }

    // 3. Document the generated graph
    G.writeGraph(fout);

    // 4. Start high-precision timer
    auto start_time = chrono::high_resolution_clock::now();

    // 5. Run your algorithm
    solve(G, fout);

    // 6. Stop timer and calculate elapsed milliseconds
    auto end_time = chrono::high_resolution_clock::now();
    double elapsed = chrono::duration<double, milli>(end_time - start_time).count();

    // 7. Print runtime to both console and file
    cout << fixed << setprecision(4) << "Algorithm Runtime: " << elapsed << " ms\n";
    fout << fixed << setprecision(4) << "\nAlgorithm Runtime: " << elapsed << " ms\n";

    fout.close();
    return 0;
}