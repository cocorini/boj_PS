#include <iostream>
#include <string>
#include <bitset>
#include <vector>
#include <algorithm>
#define ll long long
using namespace std;

int N;
ll K;
vector<ll> p[200001];
void make_table();
void solve();
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>N;
    for(int i=0;i<N;i++) {
    	int a;
    	cin>>a;
    	p[i].push_back(a);
    }
    cin>>K;
    make_table();
    solve();
}
void make_table(){
    for(int i=0;i<N;i++){
        ll cur=p[i][0];
        while(cur*p[i].back()<=K){
            p[i].push_back(cur*p[i].back());
        }
    }
}
void solve(){
    ll ans=0;
    for(int i=0;i<N;i++)
    	for(int j=0;j<p[i].size();j++)
    		ans+=K/p[i][j];
    cout<<ans;
}
