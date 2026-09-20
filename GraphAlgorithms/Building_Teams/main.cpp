#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
using namespace std;

bool bfs(int n, vector<vector<int>> &adj, vector<int> &group){
    queue<int> q;
    for(int i = 1; i <= n; i++){
        if(q.empty() && group[i] == 0){
            q.push(i);
            group[i] = 1;
        }
        
        while (!q.empty())
        {
            int v = q.front();
            q.pop();
            for(auto a: adj[v]){
                if(group[a] == group[v])
                    return false;
                if(group[a] == 0){
                    q.push(a);
                    group[a] = group[v] * -1;
                }
            }
        }
    }
    return true;
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

    vector<int> group(n + 1, 0);
    if(bfs(n, adj, group)){
        for(int i = 1; i <= n; i++){
            if(group[i] == -1) group[i] = 2;
            cout << group[i] << ' ';
        }
    }
    else{
        cout << "IMPOSSIBLE";
    }

    return 0;
}