#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};
char dir[] = {'U', 'D', 'L', 'R'};

bool bfs(int n, int m, vector<vector<char>> &grid, int si, int sj, int ei, int ej, vector<vector<char>> &parent,  vector<vector<bool>> &visited){
    queue<pair<int,int>> q;
    visited[si][sj] = true;
    q.push({si, sj});
    while (!q.empty())
    {
        auto [x, y] = q.front();
        q.pop();
        if (x == ei && y == ej){
            return true;
        }
        for (int i = 0; i < 4; i++){
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (0 <= nx && nx < n && 0 <= ny && ny < m && !visited[nx][ny] && grid[nx][ny] != '#')
            {
                visited[nx][ny] = true;
                q.push({nx, ny});
                parent[nx][ny] = dir[i];
            }
            
        }
    }
    return false;

    
}
int main(){
    int n, m;
    cin >> n >> m;

    int si, sj, ei, ej;

    vector<vector<char>> grid(n, vector<char>(m));
    vector<vector<char>> parent(n, vector<char>(m));
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> grid[i][j];
            if (grid[i][j] == 'A'){
                si = i;
                sj = j;
            }
            if (grid[i][j] == 'B'){
                ei = i;
                ej = j;
            }
        }
    }
    if (bfs(n, m, grid, si, sj, ei, ej, parent, visited)){
        cout << "YES" << endl;
        int x = ei, y = ej;
        string path = "";
        while (x != si || y != sj)
        {
            char d = parent[x][y];
            path += d;

            if (d == 'U') x++;
            else if (d == 'D') x--;
            else if (d == 'L') y++;
            else if (d == 'R') y--;
        }

        reverse(path.begin(), path.end());

        cout << path.size() << endl;
        cout << path << endl;
        
    }
    else{
        cout << "NO" << endl;
    }
}