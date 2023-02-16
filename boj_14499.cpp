#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>
#define MAX 1002
using namespace std;
void input();
void solve();
void move_dice(int direc);
int N, M, X, Y, K;
int dy[5] = { 0,0,0,-1,1 };
int dx[5] = { 0,1,-1,0,0 };
vector<vector<int>> map(20, vector<int>(20, 0));
vector<int> order(MAX, 0), dice(7, 0);//dice->1부터 위, 북, 동, 서, 남, 아래
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	input();
	solve();
}
void input() {
	cin >> N >> M >> Y >> X >> K;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}
	for (int i = 0; i < K; i++) cin >> order[i];
}
void solve() {
	int y = Y, x = X;
	for (int i = 0; i < K; i++) {
		int direc = order[i];
		y += dy[direc], x += dx[direc];
		if (y < N && x < M && y >= 0 && x >= 0) {
			move_dice(direc);
			if (map[y][x]) {
				dice[6] = map[y][x];
				map[y][x] = 0;
			}
			else map[y][x] = dice[6];
			cout << dice[1] << '\n';
		}
		else y -= dy[direc], x -= dx[direc];
	}
}
void move_dice(int direc) {
	int cur = dice[6];
	switch (direc) {
	case 1:
		dice[6] = dice[3];
		dice[3] = dice[1];
		dice[1] = dice[4];
		dice[4] = cur;
		break;
	case 2:
		dice[6] = dice[4];
		dice[4] = dice[1];
		dice[1] = dice[3];
		dice[3] = cur;
		break;
	case 3:
		dice[6] = dice[5];
		dice[5] = dice[1];
		dice[1] = dice[2];
		dice[2] = cur;
		break;
	default:
		dice[6] = dice[2];
		dice[2] = dice[1];
		dice[1] = dice[5];
		dice[5] = cur;
		break;
	}
}
