#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>
#define MAX 51
using namespace std;
void input();
bool solve();
int N, L, R;
int dy[4]={-1,1,0,0};
int dx[4]={0,0,-1,1};
vector<vector<int>> map(MAX, vector<int>(MAX, 0));
vector<vector<bool>> visited;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    input();
    int ans=0;
    while(1){
        visited.assign(N,vector<bool>(N,false));
        if(!solve()) break;
        ans++;
    }
    cout<<ans;
}
void input() {
    cin>>N>>L>>R;
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++) cin>>map[i][j];
}
bool solve() {
    int cnt=0;
    for(int ii=0;ii<N;ii++){
        for(int jj=0;jj<N;jj++){
            if(!visited[ii][jj]){
                vector<pair<int,int>> axis;
                visited[ii][jj]=true;
                queue<pair<int,int>> q;
                q.emplace(ii,jj);
                axis.emplace_back(ii,jj);
                while(!q.empty()){
                    int y=q.front().first;
                    int x=q.front().second;
                    q.pop();
                    for(int i=0;i<4;i++){
                        int ny=y+dy[i];
                        int nx=x+dx[i];
                        if(ny>=0&&nx>=0&&ny<N&&nx<N){
                            if(!visited[ny][nx]){
                    	      int gap=abs(map[y][x]-map[ny][nx]);
                        	      if(L<=gap&&gap<=R){
                            	      visited[ny][nx]=true;
                                    q.emplace(ny,nx);
                                    axis.emplace_back(ny,nx);
                                }
                            }
                        }
                    }
                }
                if(axis.size()>1){
                    int sum=0;
                    for(int i=0;i<axis.size();i++) sum+=map[axis[i].first][axis[i].second];
                    sum/=axis.size();
                    for(int i=0;i<axis.size();i++)
                        map[axis[i].first][axis[i].second]=sum;
                }
                else cnt++;
            }
        }
    }
    if(cnt==N*N) return false;
    return true;
}
