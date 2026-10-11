#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
using namespace std;
int n, m;
vector<int> adj[100001];
int parent[100001];
bool visited[100001] = {false};
vector<int> cycle;

bool dfs(int a) {
    for(int v: adj[a]){
        if(v == parent[a]) continue;
        if(!visited[v]) {
            visited[v] = true;
            parent[v] = a;
            if(dfs(v)) {
                if(cycle.size() == 1 || cycle.front() != cycle.back()) cycle.push_back(v);
                return true;
            }
        }
        else {
            cycle.push_back(v);
            return true;
        }
    }
    return false;
}
int main() {
    cin >> n >> m;

    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    for(int i = 1; i <= n; i++){
        if (!visited[i]){
            visited[i] = true;
            if(dfs(i)){
                if (cycle.front() != cycle.back()) cycle.push_back(cycle.front());
                cout << cycle.size() << endl;
                reverse(cycle.begin(), cycle.end());
                for (int v: cycle)
                {
                    cout << v << ' ';
                }
                return 0;
            }
        }
    }
    cout << "IMPOSSIBLE" << endl;
    
    return 0;
}