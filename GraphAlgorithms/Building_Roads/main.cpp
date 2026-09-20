#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
using namespace std;

int find(int x, vector<int> &parent){
    int i = x;
    vector<int> path;
    while (parent[i] != i)
    {
        path.push_back(i);
        i = parent[i];
    }
    for(int a: path){
        parent[a] = i;
    }
    return i;
}

void union_group(int a, int b, vector<int> &parent){
    int rootA = find(a, parent);
    int rootB = find(b, parent);

    if (rootA != rootB){
        parent[rootA] = rootB;
    }
}

int main(){
    int n, m;
    cin >> n >> m;
    
    vector<int> parent(n + 1);
    for(int i = 0; i <= n; i++){
        parent[i] = i;
    }
    int count = n;
    for(int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        union_group(a, b, parent);
    }

    set<int> s;
    for(int i = 1; i <= n; i++){
        s.insert(find(i, parent));
    }
    cout << s.size() - 1 << endl;
    for(int x: s){
        if(x == *s.begin())
            continue;
        cout << *s.begin() << " " << x << endl;
    }

    
}