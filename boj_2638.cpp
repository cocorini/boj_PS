#include <iostream>
#include <vector>
#include <queue>
using namespace std;
bool solve();
void input();
int bfs(int i, int y, int x);
int N, M;
int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };
vector<vector<int>> cheese;
vector<vector<bool>> visited;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    input();
    int ans = 0;
    while (1) {
        ans++;
        bool flag = solve();
        if (flag) {
            cout << ans;
            return 0;
        }
    }
}
void input() {
    cin >> N >> M;
    cheese.assign(N, vector<int>(M, 0));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            cin >> cheese[i][j];
}
bool solve() {
    visited.assign(N, vector<bool>(M, false));
    queue<pair<int, int>> find_vaccum;
    for (int ii = 0; ii < N; ii++) {
        for (int jj = 0; jj < M; jj++) {
            if (!visited[ii][jj] && !cheese[ii][jj]) {
                find_vaccum.emplace(ii, jj);
                queue<pair<int, int>> q;
                q.emplace(ii, jj);
                visited[ii][jj] = true;
                while (!q.empty()) {
                    int y = q.front().first;
                    int x = q.front().second;
                    q.pop();
                    for (int i = 0; i < 4; i++) {
                        int ny = y + dy[i];
                        int nx = x + dx[i];
                        if (ny >= 0 && ny < N && nx >= 0 && nx < M) {
                            if (!visited[ny][nx]) {
                                if (!cheese[ny][nx]) {
                                    visited[ny][nx] = true;
                                    q.emplace(ny, nx);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    //치즈 내부공간인 부분표시
    visited.assign(N, vector<bool>(M, false));
    while (!find_vaccum.empty()) {
        int yy = find_vaccum.front().first;
        int xx = find_vaccum.front().second;
        find_vaccum.pop();
        //같은방향만 끝까지 탐색해야함
        int vaccum = 0;
        for (int i = 0; i < 4; i++)
            vaccum += bfs(i, yy, xx);
        //치즈 내부구나
        if (vaccum == 4) {
            queue<pair<int, int>> q;
            q.emplace(yy, xx);
            visited[yy][xx] = true;
            while (!q.empty()) {
                int y = q.front().first;
                int x = q.front().second;
                q.pop();
                for (int i = 0; i < 4; i++) {
                    int ny = y + dy[i];
                    int nx = x + dx[i];
                    if (ny >= 0 && ny < N && nx >= 0 && nx < M) {
                        if (!visited[ny][nx] && !cheese[ny][nx]) {
                            visited[ny][nx] = true;
                            q.emplace(ny, nx);
                        }
                    }
                }
            }
        }
    }
    //만약에 치즈 내부라면 visited가 true로 표시되어있는 상태임
    vector<pair<int, int>> evap_cheese;
    for (int ii = 0; ii < N; ii++) {
        for (int jj = 0; jj < M; jj++) {
            if (cheese[ii][jj] == 1) {
                int evap = 0;
                //visited가 false이고 cheese값이 0이여야지만 그냥 air임
                for (int i = 0; i < 4; i++) {
                    int ny = ii + dy[i];
                    int nx = jj + dx[i];
                    if (ny >= 0 && ny < N && nx >= 0 && nx < M) {
                        if (!visited[ny][nx] && !cheese[ny][nx]) evap++;
                    }
                }
                if (evap >= 2) evap_cheese.emplace_back(ii, jj);
            }
        }
    }
    for (int i = 0; i < evap_cheese.size(); i++) {
        int y = evap_cheese[i].first;
        int x = evap_cheese[i].second;
        cheese[y][x] = 0;
    }
    //모두 없어졌는지 확인해보자
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            if (cheese[i][j]) return false;
    return true;
}
int bfs(int i, int y, int x) {
    queue<pair<int, int>> q;
    q.emplace(y, x);
    while (!q.empty()) {
        int yy = q.front().first;
        int xx = q.front().second;
        q.pop();
        int ny = yy + dy[i];
        int nx = xx + dx[i];
        if (ny >= 0 && nx >= 0 && ny < N && nx < M) {
            if (!cheese[ny][nx]) q.emplace(ny, nx);
            else if (cheese[ny][nx] == 1) return 1;
        }
    }
    return 0;
}
