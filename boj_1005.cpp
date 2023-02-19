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
#define MAX 1001
using namespace std;
void solve();
void input();
void clear();
void recur(int craft_num);
int T, N, K, W;
vector<int> cost, graph[MAX], complete;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	input();
}
void input() {
	cin >> T;
	for(int i=0;i<T;i++){
		cin>>N>>K;
		cost.assign(N+1,0);
		for(int j=1;j<=N;j++) cin>>cost[j];
		for(int j=0;j<K;j++){
			int a, b;
			cin>>a>>b;
			graph[b].push_back(a);
		}
		cin>>W;
		complete.assign(N+1,-1);
		solve();
		clear();
	}
}
void solve() {
	//재귀로 조져야함?
	recur(W);
	cout<<complete[W]<<'\n';
}
void clear(){
	for(int i=1;i<=N;i++) graph[i].clear();
}
void recur(int craft_num){
	//cout<<craft_num<<' ';
	//종료 조건
	if(graph[craft_num].empty()) {
		complete[craft_num]=cost[craft_num];
		return;
	}
	int maxx=0;
	//이 반복문을 실행하는 이유는 최댓값 찾으려고.
	for(int i=0;i<graph[craft_num].size();i++){
		int past=graph[craft_num][i];
		if(complete[past]<0)
			//recur의 동작이 끝나면 현재 우리가 필요한 값이 complete에 저장되어 있어야함.
			recur(past);
		//현재 순서의 건축물을 짓기 위해 이전에 지어져야 하는 건물들을 짓는데 걸리는 시간을 구하려는거
		if(maxx<complete[past]+cost[craft_num]) maxx=complete[past]+cost[craft_num];
	}
	complete[craft_num]=maxx;
}
