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
#define MAX 1000001
using namespace std;
void solve();
void input();
vector<pair<int, int>> arr(MAX, { 0,0 }), ans[MAX], answer(MAX, { -2e9, -2e9 });
vector<int> v;
int N;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	input();
	solve();
}
void input() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> arr[i].first;
		arr[i].second = i;
	}
}
void solve() {
	v.push_back(arr[1].first);
	ans[1].push_back(arr[1]);

	for (int i = 2; i <= N; i++) {
		if (v.back() < arr[i].first) {
			v.push_back(arr[i].first);
			ans[v.size()].push_back(arr[i]);
		}
		else {
			int idx = lower_bound(v.begin(), v.end(), arr[i].first) - v.begin();
			v[idx] = arr[i].first;
			ans[idx + 1].push_back(arr[i]);
		}
	}
	for (int i = v.size(); i > 0; i--) {
		for (int j = 0; j < ans[i].size(); j++) {
			if (i == v.size()) {
				if (answer[i].first < ans[i][j].first) answer[i] = ans[i][j];
			}
			else {
				int prev_val = answer[i + 1].first;
				int prev_idx = answer[i + 1].second;
				if (prev_val > ans[i][j].first && prev_idx > ans[i][j].second) {
					if (answer[i].first < ans[i][j].first) answer[i] = ans[i][j];
				}
			}
		}
	}
	cout << v.size() << '\n';
	for (int i = 1; i <= v.size(); i++) cout << answer[i].first << ' ';
}
