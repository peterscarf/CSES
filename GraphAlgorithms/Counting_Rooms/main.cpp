#include <iostream>
#include <vector>
using namespace std;

void FindWall(vector<vector<char>>& grid, vector<vector<int>>& visited, int i, int j, int n, int m){
    if (i < 0 || i >= n || j < 0 || j >= m) return;
    if (grid[i][j] == '#' || visited[i][j] == 1) return;

    visited[i][j] = 1;
    FindWall(grid, visited, i + 1, j, n, m);
    FindWall(grid, visited, i - 1, j, n, m);
    FindWall(grid, visited, i, j + 1, n, m);
    FindWall(grid, visited, i, j - 1, n, m);
}

int main(){
    int n, m;
    cin >> n >> m;

    vector<vector<char>> grid(n, vector<char>(m));
    vector<vector<int>> visited(n, vector<int>(m, 0));
    int room_num = 0;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> grid[i][j];
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if (grid[i][j] == '.' && visited[i][j] == 0){
                room_num++;
                FindWall(grid, visited, i, j, n, m);
            }
        }
    }

    cout << room_num << endl;
}