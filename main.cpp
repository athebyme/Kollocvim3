#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Graph{
    vector<vector<int>>g, gr;
    vector<int>visited, parent, order, cycle;
    bool hasCycle;

    void dfs1(int v){
        visited[v] = 1;
        for(int to: gr[v]) if(!visited[to]) dfs1(to);
        order.push_back(v);
    }
    void dfs2(int v, int component){
        visited[v] = component;
        for (int to: g[v]){
            if (!visited[to]){
                dfs2(to,component);
            }
        }
    }

    void dfsTopSort(int v){
        visited[v] = 1;
        for(int to: g[v]){
            if (!visited[to]) dfsTopSort(to);
        }
        order.push_back(v);
    }

    void dfsCycle(int v, int from){
        visited[v] = 1;

        for (int to: g[v]){
            if(to!=from){
                if(visited[to] == 0){
                    parent[to] = v;
                    dfsCycle(to, v);
                }else if (visited[to] == 1){
                    hasCycle = true;
                    parent[to] = v; //тут есчто
                    cycle = getCycle(v);
                }
            }
        }
        visited[v] = 2;
    }

    vector<int> getCycle(int v){
        static vector<int> cycle = {v+1};
        int t = parent[v];
        while (t != v){
            cycle.push_back(t + 1);
            t = parent[t];
        }
        reverse(cycle.begin(), cycle.end());
        return cycle;
    }
public:
    Graph(int vertexCount){
        g.resize(vertexCount);
        gr.resize(vertexCount);
        parent.resize(vertexCount);
        visited.resize(vertexCount);
    }

    void add(int a, int b){
        g[a].push_back(b);
        gr[b].push_back(a);
    }

    vector<int> findScc(){
        visited.assign(g.size(),0);
        for (int v = 0 ; v < g.size(); v++){
            if(!visited[v]) dfs1(v);
        }
        reverse(order.begin(), order.end());

        visited.assign(g.size(),0);
        int sccCount = 0;
        for (int v: order){
            if (!visited[v]){
                dfs2(v, ++sccCount);
            }
        }
        return visited;
    }


    vector<int> topSort(){
        visited.assign(visited.size(),0);
        for(int v = 0; v < visited.size(); v++){
            if(!visited[v]) dfsTopSort(v);
        }
        reverse(order.begin(), order.end());
        return order;
    }

    vector<int> checkCycle(){
        for(int v = 0; v < g.size(); v++){
            if(!visited[v]) dfsCycle(v, -1);
        }
    }
};




int main() {
    freopen("C:/Users/Anton/Desktop/untitled4/input.txt", "r", stdin);
    freopen("C:/Users/Anton/Desktop/untitled4/output.txt", "w", stdout);

    int vertexCount = 0, edgeCount = 0;
    cin >> vertexCount >> edgeCount;
    Graph graph(vertexCount);

    vector<string> vertexName (vertexCount);
    for (string &name: vertexName) cin >> name;

    for (int v = 0; v < edgeCount; v++){
        int a,b;
        cin >> a >> b;
        graph.add(--a, --b);
    }

    vector<int> order = graph.topSort();
    for (int color: order) cout << color << " ";
    for (auto v: order) cout << vertexName[v] << "\n";
    return 0;
}
