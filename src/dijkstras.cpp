#include "dijkstras.h"

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous);
{
    int V = G.numVertices;
    vector<int> distance(V, numeric_limits<int>::max());
    previous.assign(V,-1);
    priority_queue<pair<int, int>, vector<pair<int,int>>, greater<pair<int,int>>pq;
    distance[source] = 0;
    pq.push({0, source});

    while (!pq.empty())
    {
        int dist = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if(dist > distance[u]) continue;

        for(const auto& edge : G[u])
        {
            int v edge.dst, weight = edge.weight;
            if(distance[u] + weight < distance[v])
            {
                distance[v] = distance[u] + weight;
                previous[v] = u;
                pq.push({distance[v],v});
            }
        }
    }
    return distance;
}

