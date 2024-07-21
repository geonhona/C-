#include <string>
#include <vector>
#include <queue>

using namespace std;

struct Point {
    int x, y, dist, foundLever; // 레버 발견 여부 추가
};

int bfs(vector<string>& maps) {
    int n = maps.size();
    int m = maps[0].size();

    vector<vector<bool>> visited(n, vector<bool>(m, false));
    queue<Point> q;

    // 시작 지점 찾기 및 큐에 삽입
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (maps[i][j] == 'S') {
                q.push({i, j, 0, false});
                visited[i][j] = true;
                break;
            }
        }
    }

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    while (!q.empty()) {
        Point cur = q.front(); q.pop();

        // 출구에 도착한 경우
        if (maps[cur.x][cur.y] == 'E' && cur.foundLever) {
            return cur.dist;
        }

        // 레버를 찾은 경우
        if (maps[cur.x][cur.y] == 'L') {
            cur.foundLever = true; // 레버 발견 표시
            fill(visited.begin(), visited.end(), vector<bool>(m, false)); // 방문 기록 초기화
        }

        // 상하좌우 이동 시도
        for (int i = 0; i < 4; ++i) {
            int nx = cur.x + dx[i];
            int ny = cur.y + dy[i];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && !visited[nx][ny] && maps[nx][ny] != 'X') {
                q.push({nx, ny, cur.dist + 1, cur.foundLever});
                visited[nx][ny] = true;
            }
        }
    }

    return -1; // 출구에 도달할 수 없는 경우
}

int solution(vector<string> maps) {
    return bfs(maps);
}