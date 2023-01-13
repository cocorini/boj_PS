#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <queue>
#include <tuple>
#include <deque>
#include <algorithm>
#define ll long long
#define INF 1e9
#define MAX 1001
using namespace std;
bool solve(int size);
void input();
vector<pair<int, int>> edge[501];
vector<int> dist;
int T;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	input();
}
void input() {
	cin >> T;
	for (int i = 0; i < T; i++) {
		int N, M, W;
		bool cycle = false;
		cin >> N >> M >> W;
		dist.assign(N + 1, INF);
		for (int j = 0; j < M; j++) {
			int S, E, T;
			cin >> S >> E >> T;
			edge[S].emplace_back(E, T);
			edge[E].emplace_back(S, T);
		}
		for (int j = 0; j < W; j++) {
			int S, E, T;
			cin >> S >> E >> T;
			edge[S].emplace_back(E, -T);
		}
		cycle = solve(N);
		if (!cycle) cout << "NO\n";
		for (int j = 1; j <= N; j++) edge[j].clear();
	}
}
bool solve(int size) {
	dist[1] = 0;
	for (int i = 1; i <= size; i++) {
		for (int j = 1; j <= size; j++) {
			for (int k = 0; k < edge[j].size(); k++) {
				int next = edge[j][k].first;
				int cost = edge[j][k].second;
				if (dist[next] > dist[j] + cost) {
					dist[next] = dist[j] + cost;
					if (i == size) {
						cout << "YES\n";
						return true;
					}
				}
			}
		}
	}
	return false;
}
