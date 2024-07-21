#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// DFS (Depth-First Search) 함수
int dfs(vector<string>& maps, vector<vector<bool>>& visited, int x, int y, int depth, bool foundLever = false) {
    int n = maps.size();
    int m = maps[0].size();

    if (x < 0 || x >= n || y < 0 || y >= m || maps[x][y] == 'X' || visited[x][y]) {
        return -1; // 이동 불가능한 경우 -1 반환
    }

    if (maps[x][y] == 'E') {
        return depth; // 현재 깊이 반환
    }

    visited[x][y] = true; // 현재 위치 방문 표시

    if (maps[x][y] == 'L' && !foundLever) {
        foundLever = true;
        fill(visited.begin(), visited.end(), vector<bool>(m, false));
    }

    int minDist = -1;
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    for (int i = 0; i < 4; ++i) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        int result = dfs(maps, visited, nx, ny, depth + 1, foundLever);
        if (result != -1) {
            if (minDist == -1 || result < minDist) {
                minDist = result;
            }
        }
    }

    if (foundLever && maps[x][y] != 'L') {
        visited[x][y] = false;
    }

    return minDist;
}

// BFS (Breadth-First Search) 함수
int bfs(vector<string>& maps, vector<vector<bool>>& visited, int start_x, int start_y) {
    int n = maps.size();
    int m = maps[0].size();

    queue<pair<int, int>> q;
    q.push({start_x, start_y});
    visited[start_x][start_y] = true;

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    int depth = 0;

    while (!q.empty()) {
        int size = q.size();
        for (int i = 0; i < size; ++i) {
            int x = q.front().first;
            int y = q.front().second;
            q.pop();

            if (maps[x][y] == 'E') {
                return depth;
            }

            for (int j = 0; j < 4; ++j) {
                int nx = x + dx[j];
                int ny = y + dy[j];
                if (nx >= 0 && nx < n && ny >= 0 && ny < m && !visited[nx][ny] && maps[nx][ny] != 'X') {
                    q.push({nx, ny});
                    visited[nx][ny] = true;
                }
            }
        }
        depth++;
    }

    return -1;
}

int main() {
    // 테스트용 미로 (6x6)
    vector<string> maps = {
        "SOOOL",
        "XXXXO",
        "OOOOO",
        "OXXXX",
        "OOOOE"
    };

    int n = maps.size();
    int m = maps[0].size();
    vector<vector<bool>> visited(n, vector<bool>(m, false));

    // 시작 지점 찾기
    int start_x, start_y;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (maps[i][j] == 'S') {
                start_x = i;
                start_y = j;
                break;
            }
        }
    }

    // DFS 실행
    int dfsResult = dfs(maps, visited, start_x, start_y, 0);
    cout << "DFS 결과: " << dfsResult << endl;

    // BFS 실행 (visited 배열 초기화)
    fill(visited.begin(), visited.end(), vector<bool>(m, false));
    int bfsResult = bfs(maps, visited, start_x, start_y);
    cout << "BFS 결과: " << bfsResult << endl;

    return 0;
}