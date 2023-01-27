#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <queue>
#include <tuple>
#include <deque>
#include <algorithm>
#include <map>
#define ll long long
#define MAX 100001
using namespace std;
void solve();
void input();
int dx[2] = { -1,1 };
vector<pair<bool, int>> visited(MAX, { false, 0 });
int N, K;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	input();
	if (N == K) {
		cout << "0\n1";
		return 0;
	}
	solve();
}
void input() {
	cin >> N >> K;
	visited[N].first = true;
}
void solve() {
	queue<pair<int, int>> q;
	q.emplace(N, 0);
	int ans_cnt = 0;
	while (!q.empty()) {
		int x = q.front().first;
		int cnt = q.front().second;
		q.pop();
		if (x == K) {
			if (visited[K].second == cnt) ans_cnt++;
			continue;
		}
		for (int i = 0; i < 3; i++) {
			int nx;
			int ncnt = cnt + 1;
			if (i < 2) nx = x + dx[i];
			else nx = x * 2;
			if (nx >= 0 && nx < MAX) {
				if (!visited[nx].first) {
					visited[nx].first = true;
					visited[nx].second = ncnt;
					q.emplace(nx, ncnt);
				}
				else {
					if (ncnt == visited[nx].second) q.emplace(nx, ncnt);
				}
			}
		}
	}
	cout << visited[K].second << '\n' << ans_cnt;
}
