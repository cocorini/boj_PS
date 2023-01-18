#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <queue>
#include <tuple>
#include <deque>
#include <algorithm>
#define ll long long
//#define MAX 2501
#define INF 1e9
using namespace std;
void solve();
void input();
int N, E, v1, v2;
vector<int> dist;
vector<pair<int,int>> graph[801];
void initial(int start);
void find_dist(int start, int end);
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	input();
}
void input() {
	cin>>N>>E;
	for(int i=0;i<E;i++){
		int a, b, c;
		cin>>a>>b>>c;
		graph[a].emplace_back(b, c);
		graph[b].emplace_back(a, c);
	}
	cin>>v1>>v2;
	solve();
}
void solve() {
	//내가 필요한 경로는 v1과 v2사이의 경로 최솟값.
	//1	과 v1사이 최솟값+v2와 N사이 최솟값 vs 1과 v2사이 최솟값+v1과 N사이 최솟값.
	int suum=0, sum1=0, sum2=0;
	
	find_dist(v1, v2);
	suum=dist[v2];
	
	find_dist(1, v1);
	sum1+=dist[v1];
	
	find_dist(v2, N);
	sum1+=dist[N];
	
	find_dist(1, v2);
	sum2+=dist[v2];
	
	find_dist(v1, N);
	sum2+=dist[N];
	
	sum1=min(sum1, sum2);
	if(suum>=INF || sum1>=INF) cout<<-1;
	else cout<<suum+sum1;
}
void find_dist(int start, int end) {
	initial(start);
	priority_queue<pair<int,int>> pq;
	pq.emplace(0, start);
	while(!pq.empty()) {
		int cur_dist=pq.top().first;
		int cur_node=pq.top().second;
		pq.pop();
		
		//중복 제거..?
		if(dist[cur_node]<cur_dist) continue;
		
    //여기를 graph[start].size()로 하니깐 답이 안나오지..
		for(int i=0;i<graph[cur_node].size();i++) {
			int next_node=graph[cur_node][i].first;
			int next_dist=graph[cur_node][i].second;
			if(dist[next_node]>next_dist+cur_dist){
				dist[next_node]=next_dist+cur_dist;
				pq.emplace(dist[next_node], next_node);
			}
		}
	}
}
void initial(int start){
	dist.assign(N+1, INF);
	dist[start]=0;
}
