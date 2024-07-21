#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool foundLever = false; // 레버를 찾았는지 여부를 저장하는 변수

int dfs(vector<string>& maps, vector<vector<bool>>& visited, int x, int y, int depth) {
    int n = maps.size();
    int m = maps[0].size();

    // 범위를 벗어나거나 벽이거나 이미 방문한 곳인 경우
    if (x < 0 || x >= n || y < 0 || y >= m || maps[x][y] == 'X' || visited[x][y]) {
        return -1; // 이동 불가능한 경우 -1 반환
    }

    // 출구에 도착한 경우
    if (maps[x][y] == 'E') {
        return depth; // 현재 깊이 반환
    }

    visited[x][y] = true; // 현재 위치 방문 표시

    // 레버를 처음 찾은 경우
    if (maps[x][y] == 'L' && !foundLever) {
        foundLever = true;
        fill(visited.begin(), visited.end(), vector<bool>(m, false)); // 방문 기록 초기화
    }

    int minDist = -1; // 최소 거리 초기값을 -1로 설정 (이동 불가능을 의미)

    // 상하좌우 이동 시도
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    for (int i = 0; i < 4; ++i) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        int result = dfs(maps, visited, nx, ny, depth + 1);
        if (result != -1) { // 이동 가능한 경로가 있는 경우
            if (minDist == -1 || result < minDist) { // 더 짧은 경로를 찾았으면 갱신
                minDist = result;
            }
        }
    }

    // 레버를 찾았고, 레버가 아닌 곳을 방문했다면 방문 기록 해제
    if (foundLever && maps[x][y] != 'L') {
        visited[x][y] = false;
    }

    return minDist;
}

int solution(vector<string> maps) {
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

    return dfs(maps, visited, start_x, start_y, 0); // 최종 결과 반환
}