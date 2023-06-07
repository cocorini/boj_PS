/*
  사실은 증가하는 여러 수열들을 뽑아내는 문제라고 생각했다.
  그러나, 그 과정에서 가장긴증가하는부분수열 문제를 떠올려서 dp를 이용하려 했지만, 아무래도 해법이 떠오르지 않았음..
  스택을 이용해서 하는 것은 문제 풀 당시에는 시간초과가 날 것이라고 생각했는데, 사실 이유를 정확히 찾지는 못했지만 그렇지 않았다...
  일단 시간초과를 생각하기보다는 풀어보자.. 아직도 정직한 반복문이 아니고서야 시간 복잡도 계산이 너무도 미숙한듯...
  아무튼, 증가하는 부분수열은 스택을 이용해서 너무도 쉽게 찾아낼 수 있었다.
  순서는 애초에 스택에 쌓이면서 확정이 된 것이니까, 증가하는지에 대한 여부만 확인해주면 되었다.
  근데 생각해보면, 굳이굳이 엮자면 스택도 메모이제이션이라고 생각한다면.. 넓은 의미로는 dp인 것 아닌가?
  뭐.. 여튼 스택을 이용해서 가장 긴 증가하는 부분수열 문제를 한번 시도해봐야겠다.
*/

#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <algorithm>
#include <stack>
#include <set>
using namespace std;
int N;
vector<int> A;
void NGE();
int main() {
	ios::sync_with_stdio(0);
	cin.tie(NULL);
	cout.tie(NULL);
	cin >> N;
	A.assign(N, 0);
	for (int i = 0; i < N; i++) cin >> A[i];
	NGE();
}
void NGE() {
	stack<int> tmp;
	vector<int> ans;
  
	for (int i = N - 1; i >= 0; i--) {
		if (tmp.empty()) {
			ans.push_back(-1);
			tmp.push(A[i]);
		}
		else {
			while (!tmp.empty()) {
				int top = tmp.top();
				if (A[i] < top) {
					ans.push_back(top);
					tmp.push(A[i]);
					break;
				}
				tmp.pop();
			}
			if (tmp.empty()) {
				ans.push_back(-1);
				tmp.push(A[i]);
			}
		}
	}
	for (int i = N - 1; i >= 0; i--)
		cout << ans[i] << ' ';
}
