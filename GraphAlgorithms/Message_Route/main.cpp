#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
using namespace std;

bool bfs(int n, vector<vector<int>> &adj, vector<int> &parent){
    queue<int> q;
    vector<bool> visited(n + 1, false);
    visited[1] = true;
    q.push(1);

    while (!q.empty())
    {
        int v = q.front();
        q.pop();
        if (v == n)
        {
            return true;
        }

        for(auto i: adj[v]){
            if (!visited[i])
            {
                q.push(i);
                visited[i] = true;
                parent[i] = v;
            }
        }
    }
    return false;
    

}

int main() {
    int n, m;
    cin >> n >> m;
    
    //adjacency list
    vector<vector<int>> adj(n + 1);
    for(int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> parent(n + 1);

    if (bfs(n, adj, parent))
    {
        int v = n;
        vector<int> output;
        output.push_back(n);
        while (v != 1)
        {
            v = parent[v];
            output.push_back(v);
        }

        cout << output.size() << endl;
        for (int i = output.size() - 1; i >= 0; i--)
        {
            cout << output[i];
            if(i != 0) cout << " ";
        }
        
        
    }
    else{
        cout << "IMPOSSIBLE" << endl;
    }
    
    return 0;
}