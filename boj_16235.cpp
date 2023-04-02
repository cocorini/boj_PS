#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#define MAX 200001
using namespace std;
int N,M,K;
vector<vector<int>> add, nourish;
vector<vector<vector<int>>> trees(11, vector<vector<int>>(11, vector<int>()));
int dy[8]={-1,-1,-1,0,0,1,1,1};
int dx[8]={-1,0,1,-1,1,-1,0,1};
void cycle();
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>N>>M>>K;
	add.assign(N+1, vector<int>(N+1, 0));
	nourish.assign(N+1, vector<int>(N+1, 5));
	for(int i=1;i<=N;i++)
		for(int j=1;j<=N;j++)
			cin>>add[i][j];
	for(int i=0;i<M;i++){
		int x, y, z;
		cin>>y>>x>>z;
		//나이,y,x 순으로 저장
		trees[y][x].push_back(z);
	}
	for(int i=0;i<K;i++) cycle();
	
	int ans=0;
	for(int i=1;i<=N;i++)
		for(int j=1;j<=N;j++)
			ans+=trees[i][j].size();
	cout<<ans;
}
void cycle(){
	for(int i=1;i<=N;i++){
		for(int j=1;j<=N;j++){
			sort(trees[i][j].begin(), trees[i][j].end());
			//이 뒤로 부턴 다 죽는거야
			int tmp_k=-1;
			for(int k=0;k<trees[i][j].size();k++){
				if(tmp_k>=0){
					nourish[i][j]+=trees[i][j][k]/2;
					continue;
				}
				//양분이 더 많아
				if(trees[i][j][k]<=nourish[i][j]){
					nourish[i][j]-=trees[i][j][k];
					trees[i][j][k]++;
				}
				//양분이 더 적어
				else{
					tmp_k=k;
					nourish[i][j]+=trees[i][j][k]/2;
				}
			}
			if(tmp_k>=0) trees[i][j].erase(trees[i][j].begin()+tmp_k,trees[i][j].end());
		}
	}
	//가을
	for(int i=1;i<=N;i++){
		for(int j=1;j<=N;j++){
			for(int k=0;k<trees[i][j].size();k++){
				if(trees[i][j][k]%5==0){
					for(int l=0;l<8;l++){
						int ny=i+dy[l];
						int nx=j+dx[l];
						if(ny>0&&nx>0&&nx<=N&&ny<=N) trees[ny][nx].push_back(1);
					}
				}
			}
		}
	}
	//겨울
	for(int i=1;i<=N;i++)
		for(int j=1;j<=N;j++)
			nourish[i][j]+=add[i][j];
}
