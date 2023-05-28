#include <iostream>
#include <vector>
#define ll long long
using namespace std;
vector<vector<int>> sudoku(9, vector<int>(9, 0));
vector<pair<int, int>> empty_arr;
bool check(int cnt);
void recur(int cnt);
bool flag = false;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			cin >> sudoku[i][j];
			if (!sudoku[i][j]) empty_arr.emplace_back(i, j);
		}
	}
	recur(0);
}
void recur(int cnt) {
	//exit
	if (cnt == empty_arr.size()) {
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++)
				cout << sudoku[i][j] << ' ';
			cout << '\n';
		}
		flag = true;
		return;
	}
	int y = empty_arr[cnt].first;
	int x = empty_arr[cnt].second;
	for (int j = 1; j < 10; j++) {
		sudoku[y][x] = j;
		if (check(cnt)) recur(cnt + 1);
		if (flag) return;
	}
  # 이부분이 사실상 엄청 중요했음... 여기서 스도쿠 칸을 0으로 초기화하지 않는다면, 
  # 해당 칸이 9로 계속 남기 때문에 이전 단계의 dfs로 돌아갔을 때 계속해서 영향을 주기 때문에 완전 이상한 결과를 내게 된다...
	sudoku[y][x] = 0;
}
# 여기서 체크 함수도 문제였다.
# 기존의 내가 작성한 체크 함수의 경우에는 3행 10열의 배열을 만들고, 중복되는 숫자가 있는 경우
# return false를 해주는 코드였는데, 매번 check함수에 들어올때마다 배열초기화를 하는 과정에서
# 시간초과가 발생할 여지를 줬던 것 같다.
# 그래서 통과한 사람의 check함수를 참조했다.
# 내가 검사하려는 칸의 좌표는 어차피 고정이므로, 해당 칸에 이미 들어있는 수와 속한 행, 열 3*3구간을
# 검사했을 때, 같은 값이 있다면 return false를 해주면 되었다.. 왜 이 생각을 안했지?
# 하튼, 결론적으로 이 간단한 생각이 오히려 시간을 아끼는 방법이었음.. 쩝...
bool check(int cnt) {
	int y = empty_arr[cnt].first;
	int x = empty_arr[cnt].second;
	//세로, 가로 체크
	for (int i = 0; i < 9; i++) {
		if (sudoku[i][x] == sudoku[y][x] && i != y) return false; //행 확인
		if (sudoku[y][i] == sudoku[y][x] && i != x) return false; //열 확인
	}
	//3*3 체크
	int sec_y = y / 3, sec_x = x / 3;
	sec_y *= 3, sec_x *= 3;
	for (int i = sec_y; i < sec_y + 3; i++)
		for (int j = sec_x; j < sec_x + 3; j++) {
			if (i == y && j == x) continue;
			if (sudoku[i][j] == sudoku[y][x]) return false;
		}
	return true;
}
