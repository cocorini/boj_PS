#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <tuple>
#define ll long long
using namespace std;
void input();
void solve();
int N;
vector<ll> v[31];
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	input();
	solve();
}
void input(){
	cin>>N;
}
void solve(){
	if(N%2){
		cout<<0;
		return;
	}
	v[2].push_back(3);
	for(int i=4;i<=N;i+=2){
		for(int j=2;j<i;j+=2){
			for(int k=0;k<v[j].size();k++){
				int B=i-j;
				//cout<<B<<'\n';
				if(B!=2) v[i].push_back(v[j][k]*2);
				else if(B==2) v[i].push_back(v[j][k]*3);
			}
		}
		v[i].push_back(2);
	}
	ll ans=0;
	for(int i=0;i<v[N].size();i++) ans+=v[N][i];
	cout<<ans;
}
