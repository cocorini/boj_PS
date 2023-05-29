#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
int N, M, max_a = 0;
vector<int> sum_arr, ans_arr;
void bin_search();
int blueray(int goal);
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		int a;
		cin >> a;
		max_a = max(max_a, a);
		if (!i) sum_arr.push_back(a);
		else sum_arr.push_back(a + sum_arr.back());
	}
	bin_search();
}
// 이분탐색으로 내가 어떤 값을 찾을지에 대해 생각하기 -> mid로 찾아내야 하는 값이 뭘까?
// 블루레이의 크기를 찾는 것!
// 블루레이의 크기를 설정해서 나눴을 때 생기는 블루레이의 갯수를 cnt에 저장.
// 내가 찾은 mid값 일 때, cnt==M이 되는 지를 검사해야함
// cnt==M이 되는 mid값(블루레이 크기들) 중 가장 작은 값은 left값이므로, left를 출력.
void bin_search() {
	int left = max_a;
	int right = sum_arr.back();
	while (left <= right) {
		int mid = (left + right) / 2;
		int cnt = blueray(mid);
		if (cnt >= M) left = mid + 1;
		else right = mid - 1;
	}
	cout << left;
}
int blueray(int goal) {
	int cnt = 0, sum = 0, k = 0;
	for (int i = 1; i < N; i++) {
		sum = sum_arr[i] - k;
		if (sum > goal) {
			i--;
			k = sum_arr[i];
			cnt++;
		}
	}
	return cnt;
}
