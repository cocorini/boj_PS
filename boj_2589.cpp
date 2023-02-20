#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <queue>
#include <tuple>
#include <deque>
#include <algorithm>
#define ll long long
#define MAX 1001
using namespace std;
void solve();
int bfs(int yy, int xx);
void input();
int N,M;
int dx[4]={-1,1,0,0};
int dy[4]={0,0,-1,1};
vector<string> map;
vector<vector<bool>> visited;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	input();
	solve();
}
void input() {
	cin>>N>>M;
	for(int i=0;i<N;i++){
		string s;
		cin>>s;
		map.push_back(s);
	}
	visited.assign(N, vector<bool>(M,false));
}
void solve() {
	int ans=0;
	for(int i=0;i<N;i++){
		for(int j=0;j<M;j++){
			if(map[i][j]=='L'&&!visited[i][j]){
				visited[i][j]=true;
				ans=max(ans,bfs(i, j));
			}
		}
	}
	cout<<ans;
}
int bfs(int yy, int xx){
	vector<vector<int>> visited_two(N, vector<int>(M,-1));
	queue<pair<int,int>> q;
	q.emplace(yy,xx);
	visited_two[yy][xx]=0;
	int maxx=0;
	while(!q.empty()){
		int y=q.front().first;
		int x=q.front().second;
		q.pop();
		for(int i=0;i<4;i++){
			int ny=y+dy[i];
			int nx=x+dx[i];
			if(ny<N&&nx<M&&ny>=0&&nx>=0){
				if(map[ny][nx]=='L'&&visited_two[ny][nx]<0){
					visited_two[ny][nx]=visited_two[y][x]+1;
					q.emplace(ny, nx);
					maxx=max(maxx,visited_two[ny][nx]);
				}
			}
		}
	}
	return maxx;
}
