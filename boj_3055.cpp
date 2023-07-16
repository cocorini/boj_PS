#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <algorithm>
#include <stack>
#include <set>
#include <deque>
#include <map>
#include <cmath>
#include <tuple>
#define ll long long
#define MAX 2100000000
using namespace std;

int N, M, ans = MAX;
int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };
vector<vector<bool>> visited;

void moveWater(vector<string> &forest);
void moveKak(int yy, int xx, vector<string> &forest);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> M;
    visited.assign(N, vector<bool>(M, false));
    pair<int, int> hedgehog;
    vector<string> arr;
    for (int i = 0; i < N; i++) {
        string s;
        cin >> s;
        arr.push_back(s);
        for (int j = 0; j < M; j++) {
            if (arr[i][j] == 'S') {
                visited[i][j] = true;
                hedgehog = make_pair(i, j);
                arr[i][j] = '.';
            }
        }
    }
    moveKak(hedgehog.first, hedgehog.second, arr);

    if (ans != MAX) cout << ans;
    else cout << "KAKTUS";
}

void moveWater(vector<string>& forest) {
    deque<pair<int, int>> dq;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            if (forest[i][j] == '*') dq.emplace_back(i, j);
    int S = dq.size();

    for (int ii = 0; ii < S; ii++) {
        int y = dq.front().first;
        int x = dq.front().second;
        dq.pop_front();
        for (int i = 0; i < 4; i++) {
            int ny = y + dy[i];
            int nx = x + dx[i];
            if (ny < N && nx < M && ny >= 0 && nx >= 0) {
                if (forest[ny][nx] == '.') forest[ny][nx] = '*';
            }
        }
    }
}

//yy, xx는 S의 좌표를 뜻한다. S는 사실상 지워버려도 상관없다.
void moveKak(int yy, int xx, vector<string>& forest) {
    queue<tuple<int, int, int>> q;
    q.emplace(yy, xx, 1);
    visited[yy][xx] = true;
    int cnt = 1;
    while (!q.empty()) {
        int y = get<0>(q.front());
        int x = get<1>(q.front());
        int time = get<2>(q.front());
        if (time > cnt) {
            moveWater(forest);
            cnt++;
        }
        q.pop();
        if (forest[y][x] == '*') continue;
        for (int i = 0; i < 4; i++) {
            int ny = y + dy[i];
            int nx = x + dx[i];
            if (ny < N && nx < M && ny >= 0 && nx >= 0) {
                if (!visited[ny][nx]) {
                    if (forest[ny][nx] == '*') continue;
                    else if (forest[ny][nx] == '.') {
                        //다음 좌표로 이동
                        visited[ny][nx] = true;
                        q.emplace(ny, nx, time + 1);
                    }
                    else if (forest[ny][nx] == 'D') {
                        ans = min(ans, time);
                        return;
                    }
                }
            }
        }
    }
}
