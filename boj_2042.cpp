#include <iostream>
#include <vector>
#include <cmath>
#define ll long long
#define MAX 1000001
using namespace std;
void input();
vector<ll> v(MAX, 0), tree;
void solve(int a, int b, ll c);
void insert(int node, int start, int end, int idx, ll diff);
ll summation(int node, int start, int end, int section_start, int section_end);
ll mkST(int node, int start, int end);
int N, M, K, sizze;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	input();
}
void input() {
	cin >> N >> M >> K;
	int h = (int)ceil(log(N) / log(2));
	sizze = (int)pow(2, h + 1);
	tree.assign(sizze, 0);
	for (int i = 1; i <= N; i++) cin >> v[i];
	mkST(1, 1, N);
	for (int j = 0; j < M + K; j++) {
		int a, b;
		ll c;
		cin >> a >> b >> c;
		solve(a, b, c);
	}
}
void solve(int a, int b, ll c) {
	//업데이트
	if (a == 1) {
		//cout << "v[b]는 " << v[b] << '\n';
    //여기서 v[b]를 빼지않고, b를 빼서 계속해서 틀림...
		insert(1, 1, N, b, c - v[b]);
    //처음에는 v 배열 갱신도 안해줌...
		v[b] = c;
		//cout << "v[b]는 " << v[b] << '\n';
		//for (int i = 1; i < sizze; i++) cout << tree[i] << ' ';
		//cout << '\n';
	}
	//구간 합 출력하기
	else if (a == 2) cout << summation(1, 1, N, b, c) << '\n';
}
ll mkST(int node, int start, int end) {
	if (start == end) return tree[node] = v[start];
	int mid = (start + end) / 2;
	return tree[node] = mkST(node * 2, start, mid) + mkST(node * 2 + 1, mid + 1, end);
}
void insert(int node, int start, int end, int idx, ll diff) {
	//leaf node라는 것을 이용해서 idx를 찾으려고 했음->불가능함..
	//start와 end값은 v의 인덱스의 범위를 나타내는 것이므로, idx가 start와 end사이의 값이 아니라면 반환
	if (!(start <= idx && idx <= end)) return;
	tree[node] += diff;
	if (start != end) {
		int mid = (start + end) / 2;
		insert(node * 2, start, mid, idx, diff);
		insert(node * 2 + 1, mid + 1, end, idx, diff);
	}
}
ll summation(int node, int start, int end, int section_start, int section_end) {
	if (end < section_start || start > section_end) return 0;
	else if (section_start <= start && end <= section_end) return tree[node];
	int mid = (start + end) / 2;
	return summation(node * 2, start, mid, section_start, section_end) + summation(node * 2 + 1, mid + 1, end, section_start, section_end);
}
