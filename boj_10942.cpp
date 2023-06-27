#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <algorithm>
#include <stack>
#include <set>
#include <deque>
#include <tuple>
using namespace std;
int N, M;
void mkDP();
vector<int> num;
vector<vector<bool>> dp;

//처음 문제 접할 때부터 메모이제이션이 필요하다 생각했다. -> 역시나 dp문제.
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin >> N;
	num.assign(N + 1, 0);
	for (int i = 1; i <= N; i++) cin >> num[i];

	dp.assign(N + 1, vector<bool>(N + 1, false));
	mkDP();

	cin >> M;
	for (int i = 0; i < M; i++) {
		int S, E;
		cin >> S >> E;
		cout << dp[S][E] << '\n';
	}
}
void mkDP() {

  //초기값 세팅
  //원소 한개면 무조건 펠린드롬, 인접 원소 두개면 같아야 펠린드롬
	dp[N][N] = true;
	for (int i = 1; i < N; i++) {
		dp[i][i] = true;
		if (num[i] == num[i + 1]) dp[i][i + 1] = true;
	}

	//행: 시작점, 열: 끝점
  //이렇게 생각했기 때문에, 열부터 탐색 해야함. ex) dp[1][3]은 dp[2][2]의 값에 종속됨.
  //시작, 끝 사이에 홀수개 있을때, 짝수개 있을때 두가지 케이스 존재.
	//dp는 무조건 테이블을 직접 그려서 현재 값이 테이블상에서 어떤 값들의 영향을 받는지를 눈으로 확인하고 코드를 짜자.
  for (int j = 3; j <= N; j++) {
		for (int i = 1; i < j; i++) {
			int from = i + 1;
			int to = j - 1;
			if (from == to) {
				if (num[i] == num[j]) dp[i][j] = true;
			}
			else {
				if (dp[from][to] && num[i] == num[j]) dp[i][j] = true;
			}
		}
	}
}
