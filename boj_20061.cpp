#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
#define ll long long
#define INF 2100000000
using namespace std;

int N, ans = 0;
vector<vector<bool>> red(4, vector<bool>(4, false)), green(6, vector<bool>(4, false)), blue(4, vector<bool>(6, false));
vector<vector<int>> input;

void play();
void save(int t, int y, int x);
void check();
int make_score();
void special_region();

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	// input 정리
	cin >> N;
	input.assign(N, vector<int>(3, 0));
	for (int i = 0; i < N; i++) cin >> input[i][0] >> input[i][1] >> input[i][2];
	
	// play
	play();
}

void play() {
	for (int ii = 0; ii < N; ii++) {
		save(input[ii][0], input[ii][1], input[ii][2]);
		check();
	}
	cout << ans << '\n';
	int cnt = 0;
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 4; j++) {
			if (green[i][j]) cnt++;
		}
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 6; j++) {
			if (blue[i][j]) cnt++;
		}
	}
	cout << cnt;
}

// 완료
void save(int t, int y, int x) {
	// 1칸
	if (t == 1) {
		// green
		for (int i = 0; i < 6; i++) {
			if (green[i][x]) {
				green[i - 1][x] = true;
				break;
			}
			if (i == 5) {
				green[5][x] = true;
			}
		}
		//blue
		for (int j = 0; j < 6; j++) {
			if (blue[y][j]) {
				blue[y][j - 1] = true;
				break;
			}
			if (j == 5) {
				blue[y][5] = true;
			}
		}
	}
	// 가로 모양
	else if (t == 2) {
		// green
		for (int i = 0; i < 6; i++) {
			if (green[i][x] || green[i][x + 1]) {
				green[i - 1][x] = true;
				green[i - 1][x + 1] = true;
				break;
			}
			if (i == 5) {
				green[i][x] = true;
				green[i][x + 1] = true;
			}
		}
		//blue
		for (int j = 0; j < 6; j++) {
			if (blue[y][j]) {
				blue[y][j - 1] = true;
				blue[y][j - 2] = true;
				break;
			}
			if (j == 5) {
				blue[y][j] = true;
				blue[y][j - 1] = true;
			}
		}
	}
	// 세로
	else {
		// green
		for (int i = 0; i < 6; i++) {
			if (green[i][x]) {
				green[i - 1][x] = true;
				green[i - 2][x] = true;
				break;
			}
			if (i == 5) {
				green[i][x] = true;
				green[i - 1][x] = true;
			}
		}
		//blue
		for (int j = 0; j < 6; j++) {
			if (blue[y][j] || blue[y + 1][j]) {
				blue[y][j - 1] = true;
				blue[y + 1][j - 1] = true;
				break;
			}
			if (j == 5) {
				blue[y][j] = true;
				blue[y + 1][j] = true;
			}
		}
	}
}

void check() {
	ans += make_score();
	special_region();

	/*cout << "=========blue==========\n";
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 6; j++) {
			cout << blue[i][j] << ' ';
		}
		cout << '\n';
	}
	cout << "=========green==========\n";
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 4; j++) {
			cout << green[i][j] << ' ';
		}
		cout << '\n';
	}*/
}

int make_score() {
	int score = 0;
	
	// green: 행 관찰
	pair<int, int> full_green = make_pair(0, 0);
	for (int i = 5; i >= 0; i--) {
		// 행 모든 원소 체크하기
		bool full = true;
		for (int j = 0; j < 4; j++) {
			if (!green[i][j]) full = false;
		}
		if (full) {
			score += 1;
			full_green.first = i;
			full_green.second++;
		}
	}
	int idx = full_green.first - 1;
	for (int i = idx; i >= 0; i--) {
		green[i + full_green.second] = green[i];
		if (i == 0) {
			for (int k = i + full_green.second - 1; k >= 0; k--) {
				green[k] = { false, false, false, false };
			}
		}
	}

	// blue: 열 관찰
	pair<int, int> full_blue = make_pair(0, 0);
	for (int j = 5; j >= 0; j--) {
		// 열 모든 원소 체크하기
		bool full = true;
		for (int i = 0; i < 4; i++) {
			if (!blue[i][j]) full = false;
		}
		if (full) {
			score += 1;
			full_blue.first = j;
			full_blue.second++;
		}
	}
	idx = full_blue.first - 1;
	for (int j = idx; j >= 0; j--) {
		for (int i = 0; i < 4; i++) {
			blue[i][j + full_blue.second] = blue[i][j];
		}
		if (j == 0) {
			for (int k = j + full_blue.second - 1; k >= 0; k--) {
				for (int i = 0; i < 4; i++) {
					blue[i][k] = false;
				}
			}
		}
	}
	
	return score;
}

void special_region() {
	// green
	int green_cnt = 0;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			if (green[i][j]) {
				green_cnt++;
				break;
			}
		}
	}

	// green: 행 관찰
	for (int i = 5; i > 5 - green_cnt; i--) {
		for (int j = 0; j < 4; j++) {
			green[i][j] = false;
		}
	}
	if (green_cnt) {
		int idx = 5 - green_cnt;
		for (int i = idx; i >= 0; i--) {
			green[i + green_cnt] = green[i];
		}
		for (int k = green_cnt - 1; k >= 0; k--) {
			green[k] = { false, false, false, false };
		}
	}

	// blue
	int blue_cnt = 0;
	for (int j = 0; j < 2; j++) {
		for (int i = 0; i < 4; i++) {
			if (blue[i][j]) {
				blue_cnt++;
				break;
			}
		}
	}

	// blue: 행 관찰
	for (int j = 5; j > 5 - blue_cnt; j--) {
		for (int i = 0; i < 4; i++) {
			blue[i][j] = false;
		}
	}
	if (blue_cnt) {
		int idx = 5 - blue_cnt;
		for (int j = idx; j >= 0; j--) {
			for (int i = 0; i < 4; i++) {
				blue[i][j + blue_cnt] = blue[i][j];
			}
		}

		for (int k = blue_cnt - 1; k >= 0; k--) {
			for (int i = 0; i < 4; i++) {
				blue[i][k] = false;
			}
		}
	}
}
