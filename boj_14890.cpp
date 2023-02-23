#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>
#define MMAX 1000000000
#define MAX 101
#define ll long long
using namespace std;
void input();
void solve();
int N, L;
vector<vector<int>> map(MAX, vector<int>(MAX,0));
vector<vector<bool>> slope(MAX, vector<bool>(MAX, false));
vector<int> row(MAX, 0), col(MAX, 0);
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    input();
    solve();
}
void input() {
	cin>>N>>L;
	for(int i=0;i<N;i++)
		for(int j=0;j<N;j++)
			cin>>map[i][j];
}
void solve() {
	//행 기준 탐색
	for(int i=0;i<N;i++){
		for(int j=0;j<N-1;j++){
			if(row[i]<0) break;
			int x=map[i][j];
			int next_x=map[i][j+1];
			if(x!=next_x){
				//낮은 칸과 높은 칸의 높이 차이가 1보다 큰 경우
				if(abs(next_x-x)>1){
					row[i]=-1;
					break;
				}
				//낮은 칸과 높은 칸의 높이 차이가 1인 경우
				else{
					//경사로가 이전 경로상에 만들어져야 하는 경우
					if(next_x>x){
						for(int k=0;k<L;k++){
							if(j-k>=0) {
								//경사로를 놓은 곳에 또 경사로를 놓는 경우
								if(slope[i][j-k]){
									row[i]=-1;
									break;
								}
								int nx=map[i][j-k];
								//L개의 블록이 연속되지 않는 경우
								if(x!=nx){
									row[i]=-1;
									break;
								}
							}
							//경사로를 놓다가 범위를 벗어나는 경우
							else {
								row[i]=-1;
								break;
							}
							slope[i][j-k]=true;
						}
					}
					//경사로가 이후 경로상에 만들어져야 하는 경우
					else{
						for(int k=1;k<=L;k++){
							if(j+k<N) {
								//경사로를 놓은 곳에 또 경사로를 놓는 경우
								if(slope[i][j+k]){
									row[i]=-1;
									break;
								}
								int nx=map[i][j+k];
								//L개의 블록이 연속되지 않는 경우
								if(next_x!=nx){
									row[i]=-1;
									break;
								}
							}
							//경사로를 놓다가 범위를 벗어나는 경우
							else {
								row[i]=-1;
								break;
							}
							slope[i][j+k]=true;
						}
						if(!row[i]) j+=L-1;
					}
				}
			}
		}
	}
	slope.assign(MAX,vector<bool>(MAX, false));
	for(int j=0;j<N;j++){
		for(int i=0;i<N-1;i++){
			if(col[j]<0) break;
			int y=map[i][j];
			int next_y=map[i+1][j];
			if(y!=next_y){
				//낮은 칸과 높은 칸의 높이 차이가 1보다 큰 경우
				if(abs(next_y-y)>1){
					col[j]=-1;
					break;
				}
				//낮은 칸과 높은 칸의 높이 차이가 1인 경우
				else{
					//경사로가 이전 경로상에 만들어져야 하는 경우
					if(next_y>y){
						for(int k=0;k<L;k++){
							if(i-k>=0) {
								//경사로를 놓은 곳에 또 경사로를 놓는 경우
								if(slope[i-k][j]){
									col[j]=-1;
									break;
								}
								int ny=map[i-k][j];
								//L개의 블록이 연속되지 않는 경우
								if(y!=ny){
									col[j]=-1;
									break;
								}
							}
							//경사로를 놓다가 범위를 벗어나는 경우
							else {
								col[j]=-1;
								break;
							}
							slope[i-k][j]=true;
						}
					}
					//경사로가 이후 경로상에 만들어져야 하는 경우
					else{
						for(int k=1;k<=L;k++){
							if(i+k<N) {
								//경사로를 놓은 곳에 또 경사로를 놓는 경우
								if(slope[i+k][j]){
									col[j]=-1;
									break;
								}
								int ny=map[i+k][j];
								//L개의 블록이 연속되지 않는 경우
								if(next_y!=ny){
									col[j]=-1;
									break;
								}
							}
							//경사로를 놓다가 범위를 벗어나는 경우
							else {
								col[j]=-1;
								break;
							}
							slope[i+k][j]=true;
						}
						if(!col[j]) i+=L-1;
							
					}
				}
			}
		}
	}
	int ANS=0;
	for(int i=0;i<N;i++)
		if(!row[i]) ANS++;
	for(int i=0;i<N;i++)
		if(!col[i]) ANS++;
	cout<<ANS;
	/*for(int i=0;i<N;i++) cout<<row[i]<<' ';
	cout<<"\n";
	for(int i=0;i<N;i++) cout<<col[i]<<' ';
	cout<<'\n';*/
}
