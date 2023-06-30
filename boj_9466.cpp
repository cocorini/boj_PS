/*
우선 사이클을 파악해야된다는 사실을 알게되어, 얼마전에 공부했던 크루스칼 알고리즘의 사이클 판단하는 방법을 떠올렸다.
그때는 유니온 파인드를 이용했단 말이지..?
그래서 나는 유니온 파인드를 이용해 사이클을 찾으려 했다. 뭐 어찌됐든 재귀인거지 결국..?
근데 안되는 이유는 사이클이 문제가 아니라 걍 같은 그룹을 판단하는 놈들이니까, 사이클이 아니라도 같이 묶이면 무조건 한 그룹으로 판단한다.
그래서 애초에 안되는 방법이었슴!!
그러면 그냥 단순재귀로 판단하는 건데 -> 조건없이 단순 재귀로 돌리면 당연히 시간 초과겠지..? -> 역시나 시간초과
그래서 생각한게 경로 저장해서 사이클에 포함된 애들을 체크해주려고 했는데.. 이번엔 메모리 초과괗ㅎㅎㅎㅎ
결국 모범답안을 구글에서 쓱했따... 방문배열 뿐만 아니라, 이것이 지금 판단이 완료된 인덱스인지를 판단하는 배열 또한 필요했다.
첨엔 판단 완료인 인덱스 체크하는 배열은 왜 필요하지..? 생각했는데..
예를 들어, 1->2->3->6->7->3 에서 3에 방문체크만 한 채로 재귀 들어가서 다시 3에 들어갔을 때, 
방문체크는 되어있지만 사이클 판단 체크는 되어있지 않을 때 사이클이라는 것을 판단하고, 재귀를 decided를 true로 바꾸면서 빠져나옴..
이거 이해하려면 현재 노드 판단인지, 다음 노드 판단인지가 헷갈리지 않고 확실하게 되어야 하는듯..!
되게 간단하지만 어려웠따 게다가 이거 사이클에 속해있는 원소판단을 명확하게 어떤 노드가 사이클에 있다 라고 판단하지 않고,
있는놈은 카운트만 올려서 갯수만 판단하는 식이라.. 솔직히 나는 생각하기 어려운 풀이인거 같음...ㅠ
그래도 어떻게하리 해내야지!!
*/
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

int T, N, cnt;
vector<int> v, tmp;
vector<bool> decided, visited;

void recur(int cur);
void findCycle();

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin >> T;
	for (int i = 0; i < T; i++) {
		cin >> N;
		cnt = 0;
		v.assign(N + 1, 0);
		decided.assign(N + 1, false);
		for (int j = 1; j <= N; j++) cin >> v[j];
		
		findCycle();
		
		cout << N - cnt << '\n';
	}
}

void recur(int cur) {
	int next = v[cur];
	visited[cur]=true;
	if(!visited[next]) recur(next);
	else if(!decided[next]){
		int j = next;
		while(cur != j){
			cnt++;
			j=v[j];
		}
		cnt++;
	}
	decided[cur]=true;
}

void findCycle() {
	visited.assign(N + 1, false);
	for (int i = 1; i <= N; i++)
		if(!visited[i]) recur(i);
}
