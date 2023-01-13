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
//#define INF 1e9
using namespace std;
void solve();
void input();
vector<int> party_num;
vector<vector<int>> party;
vector<bool> man;
int N,M;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	input();
}
void input() {
	cin>>N>>M;
	man.assign(N+1,false);
	party_num.assign(M+1,0);
	int T;
	cin>>T;
	for(int i=0;i<T;i++) {
		int a;
		cin>>a;
		man[a]=true;
	}
	for(int i=0;i<M;i++){
		int k, x_num;
		vector<int> v;
		cin>>k;
		for(int j=0;j<k;j++){
			cin>>x_num;
			v.push_back(x_num);
			if(man[x_num]) party_num[i]=1;
		}
		party.push_back(v);
	}
	solve();
}
void solve() {
	int cnt=0;
	while(1){
		for(int i=0;i<M;i++){
			bool flag=false;
			if(party_num[i]>1) continue;
			if(party_num[i]==1){
				for(int j=0;j<party[i].size();j++){
					int num=party[i][j];
					man[num]=true;
				}
				party_num[i]=2;
				cnt++;
			}
			else if(!party_num[i]){
				for(int j=0;j<party[i].size();j++){
					int num=party[i][j];
					if(!flag){
						if(man[num]){
							party_num[i]=1;
							flag=true;
							j=-1;
							cnt++;
						}
					}
					else{
						if(!man[num]) man[num]=true;
					}
				}
			}
		}
		if(!cnt) break;
		else cnt=0;
	}
	int ans=0;
	for(int i=0;i<M;i++)
		if(!party_num[i]) ans++;
	cout<<ans;
}
