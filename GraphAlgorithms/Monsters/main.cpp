#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
using namespace std;
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};
char dir[] = {'U', 'D', 'L', 'R'};
int n, m;
int ei, ej;
bool bfs(vector<vector<char>> &grid, int si, int sj, vector<vector<char>> &parent,  vector<vector<bool>> &visited,
    vector<vector<int>> &monster_time){
    
    vector<vector<int>> timestep(n, vector<int>(m, 1e9));
    queue<pair<int,int>> q;

    visited[si][sj] = true;
    q.push({si, sj});
    timestep[si][sj] = 0;

    while (!q.empty())
    {
        auto [x, y] = q.front();
        q.pop();
        if (x == 0 || x == n - 1 || y == 0 || y == m - 1){
            ei = x, ej = y;
            return true;
        }
        for (int i = 0; i < 4; i++){
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (0 <= nx && nx < n && 0 <= ny && ny < m && !visited[nx][ny] && grid[nx][ny] != '#')
            {
                int t = timestep[x][y] + 1;
                if (t < monster_time[nx][ny]){
                    visited[nx][ny] = true;
                    timestep[nx][ny] = t;
                    q.push({nx, ny});
                    parent[nx][ny] = dir[i];
                }
            }
            
        }
    }
    return false;
}

void monsters_bfs(vector<vector<char>> &grid, vector<vector<bool>> &visited, vector<vector<int>> &monster_time, 
    vector<pair<int, int>> &monster_ij){
    queue<pair<int,int>> q;
    for (auto v: monster_ij){
        auto [x, y] = v;
        visited[x][y] = true;
        q.push({x, y});
    }
    while (!q.empty())
    {
        auto [x, y] = q.front();
        q.pop();
        for (int i = 0; i < 4; i++){
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (0 <= nx && nx < n && 0 <= ny && ny < m && !visited[nx][ny] && grid[nx][ny] != '#')
            {
                visited[nx][ny] = true;
                monster_time[nx][ny] = monster_time[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }
}

int main() {
    cin >> n >> m;    
    vector<vector<char>> grid(n, vector<char>(m));
    vector<vector<char>> parent(n, vector<char>(m));
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    int si = -1, sj = -1;
    vector<vector<int>> monster_time(n, vector<int>(m, 1e9));
    vector<vector<bool>> monsters_visited(n, vector<bool>(m, false));
    vector<pair<int, int>> monster_ij;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> grid[i][j];
            if (grid[i][j] == 'A'){
                si = i;
                sj = j;
            }
            if (grid[i][j] == 'M'){
                monster_time[i][j] = 0;
                monster_ij.push_back({i, j});
            }
        }
    }
    monsters_bfs(grid, monsters_visited, monster_time, monster_ij);

    if (bfs(grid, si, sj, parent, visited, monster_time)){
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

    return 0;
}