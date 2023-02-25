#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>
#define MMAX 1000000000
#define MAX 11
#define ll long long
using namespace std;
void input();
void solve();
void recur(int y, int x);
int T, N;
vector<pair<int,int>> conveni;
pair<int,int> house, rock_fe;
vector<bool> visited;
bool flag=false;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    input();
}
void input() {
	cin>>T;
	for(int i=0;i<T;i++){
		cin>>N;
		cin>>house.second>>house.first;
		for(int j=0;j<N;j++){
			int y, x;
			cin>>x>>y;
			conveni.emplace_back(y,x);
		}
		visited.assign(conveni.size(),false);
		cin>>rock_fe.second>>rock_fe.first;
		solve();
	}
}
void solve() {
	recur(house.first, house.second);
	if(!flag) cout<<"sad\n";
	else cout<<"happy\n";
	flag=false;
	conveni.clear();
}
void recur(int y, int x){
    //종료조건
	if(abs(y-rock_fe.first)+abs(x-rock_fe.second)<=1000){
		flag=true;
		return;
	}
	vector<bool> check(conveni.size(),false);
	for(int i=0;i<conveni.size();i++){
		int ny=conveni[i].first;
		int nx=conveni[i].second;
		int dist=abs(ny-y)+abs(nx-x);
		if(!visited[i]&&dist<=1000) check[i]=true;
	}
	for(int i=0;i<conveni.size();i++){
		if(!check[i]) continue;
		else {
			visited[i]=true;
			recur(conveni[i].first,conveni[i].second);
			if(flag) return;
			//visited[i]=false;
		}
	}
}
