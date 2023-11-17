
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int from, to, weight;
};

bool operator<(const Edge& e1, const Edge& e2) {
    return e1.weight < e2.weight;
}

int main() {
    int n;
    cin >> n;

    vector<int> nails(n);
    for (int i = 0; i < n; i++) {
        cin >> nails[i];
    }

    vector<Edge> edges;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            Edge e;
            e.from = i;
            e.to = j;
            e.weight = nails[j] - nails[i];
            edges.push_back(e);
        }
    }

    sort(edges.begin(), edges.end());

    vector<int> parent(n);
    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }

    int totalWeight = 0;
    int numEdges = 0;
    for (int i = 0; i < edges.size(); i++) {
        Edge e = edges[i];

        int rootFrom = parent[e.from];
        int rootTo = parent[e.to];

        if (rootFrom != rootTo) {
            parent[rootTo] = rootFrom;
            totalWeight += e.weight;
            numEdges++;

            if (numEdges == n - 1) {
                break;
            }
        }
    }

    cout << totalWeight / 2 << endl;

    return 0;
}