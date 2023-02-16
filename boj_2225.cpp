#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>
#define div 1000000000
#define MAX 201
using namespace std;
void input();
void solve();
int N, K;
vector<vector<int>> v(MAX, vector<int>(MAX, 0));
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    input();
    solve();
}
void input() {
	cin>>N>>K;
}
void solve() {
	for(int j=0;j<=N;j++) v[1][j]=1;
	for(int i=1;i<=K;i++){
		for(int j=0;j<=N;j++){
			for(int l=0;l<=j;l++){
				v[i][j]+=v[i-1][l]*v[1][j-l]%div;
				v[i][j]%=div;
			}
		}
	}
	/*for(int j=1;j<=K;j++){
		for(int k=0;k<=N;k++) cout<<v[j][k]<<' ';
		cout<<'\n';
	}*/
	cout<<v[K][N];
}
