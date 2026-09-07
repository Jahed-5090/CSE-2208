#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9; // Added missing INF definition

map<int, vector<pair<int, int>>> createRandom(int n, int edges) {
    map<int, vector<pair<int, int>>> adj;
    set<pair<int, int>> used;
    while ((int)used.size() < edges) {
        int u = rand() % n;
        int v = rand() % n;
        if (u == v || used.count({u, v})) continue;

        used.insert({u, v});
        int weight = (rand() % 15);
        adj[u].push_back({v, weight});
    }
    return adj;
}

// Fixed signature and matrix initialization
vector<vector<int>> floyd(int V, const map<int, vector<pair<int, int>>> &adj) {
    vector<vector<int>> dist(V, vector<int>(V, INF));

    // 1. Set diagonal to 0
    for (int i = 0; i < V; i++) {
        dist[i][i] = 0;
    }

    // 2. Load the edge weights from the map into the matrix
    for (auto const& [u, edges] : adj) {
        for (auto const& edge : edges) {
            int v = edge.first;
            int w = edge.second;
            dist[u][v] = w;
        }
    }

    // 3. Run Floyd-Warshall
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                // Fixed index logic: dist[k][j] instead of dist[j][k]
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
    return dist;
}

void saveToFile(string filename, const vector<vector<int>> &dist) {
    ofstream file(filename);
    for (int i = 0; i < (int)dist.size(); i++) {
        for (int j = 0; j < (int)dist[i].size(); j++) {
            if (dist[i][j] == INF)
                file << "INF ";
            else
                file << dist[i][j] << " ";
        }
        file << endl;
    }
    file.close();
}

vector<vector<int>> readFromFile(string filename, int vtx) {
    vector<vector<int>> dist(vtx, vector<int>(vtx, INF));
    ifstream file(filename);
    string x;
    for (int i = 0; i < vtx; i++) {
        for (int j = 0; j < vtx; j++) {
            file >> x;
            if (x == "INF")
                dist[i][j] = INF;
            else
                dist[i][j] = stoi(x);
        }
    }
    file.close();
    return dist;
}

vector<int> Dijkstra(int n, const map<int, vector<pair<int, int>>> &adj, int src) {
    vector<int> dist(n, INF);
    dist[src] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, src});

    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u]) continue;

        if (adj.find(u) != adj.end()) {
            for (auto &edge : adj.at(u)) {
                int v = edge.first;
                int w = edge.second;

                if (dist[u] != INF && dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});
                }
            }
        }
    }
    return dist;
}

int main() {
    srand(time(0));

    int V = 33;
    
    // Using a dense graph (V * (V-1) edges) to ensure u=10 and v=20 
    // are likely connected, mimicking the "complete" graph assignment requirement.
    int edges = V * (V - 1) / 2; 

    map<int, vector<pair<int, int>>> adj = createRandom(V, edges);

    vector<vector<int>> dist = floyd(V, adj);
    saveToFile("Floyd_output.txt", dist);

    vector<vector<int>> newdist = readFromFile("Floyd_output.txt", V);

    int u = 10, v = 20;

    vector<int> du = Dijkstra(V, adj, u);
    int duv = du[v];
    
    vector<int> dv = Dijkstra(V, adj, v);
    int dvu = dv[u]; 

    cout << "Dijkstra U->V: " << duv << " | Floyd U->V: " << newdist[u][v] << endl;
    if(duv == newdist[u][v]) {
        cout << "U-V milse (Matched!)\n";
    }
    
    cout << "Dijkstra V->U: " << dvu << " | Floyd V->U: " << newdist[v][u] << endl;
    if(dvu == newdist[v][u]) {
        cout << "V-U milse (Matched!)\n";
    }

    return 0;
}