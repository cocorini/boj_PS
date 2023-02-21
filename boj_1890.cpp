#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>
#define MMAX 1000000000
#define MAX 101
#define ll long long
using namespace std;
void input();
void solve();
int dy[2]={0,1};
int dx[2]={1,0};
int N;
vector<vector<int>> board(MAX, vector<int>(MAX,0));
vector<vector<ll>> dp(MAX, vector<ll>(MAX,0));
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    input();
    solve();
}
void input() {
	cin>>N;
	for(int i=0;i<N;i++)
		for(int j=0;j<N;j++)
			cin>>board[i][j];
}
void solve() {
	dp[0][0] = 1;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (board[i][j] == 0) continue;
			if (i + board[i][j] < N) dp[i + board[i][j]][j] += dp[i][j];
			if (j + board[i][j] < N) dp[i][j + board[i][j]] += dp[i][j];
		}
	}
	cout << dp[N - 1][N - 1];
}
