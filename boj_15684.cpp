#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int N, M, H, ans=2100000000;
vector<vector<bool>> ladder(31, vector<bool>(11, false));
vector<bool> route(11, false);
bool check();
void recur(int h, int cnt, int target);
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin>>N>>M>>H;
	if(!M){
		cout<<0;
		return 0;
	}
	for(int i=0;i<M;i++){
		int a, b;
		cin>>a>>b;
		ladder[a][b]=true;
	}
	for(int i=0;i<=3;i++){
		recur(1, 0, i);
		if(ans!=2100000000){
			cout<<ans;
			return 0;
		}
	}
	cout<<-1;
}
//백트래킹 구현
void recur(int h, int cnt, int target){
	//종료 조건
	if(cnt==target){
		if(check()) ans=cnt;
		return;
	}
	for(int i=h;i<=H;i++){
		for(int j=1;j<N;j++){
			//연속 사다리 피하기
			if(ladder[i][j-1]||ladder[i][j]||ladder[i][j+1]) continue;
			else{
				ladder[i][j]=true;
				recur(i, cnt+1, target);
				ladder[i][j]=false;
			}
		}
	}
}
//다시 제 자리로 돌아오는지 체크
bool check(){
	for(int start=1;start<=N;start++){
		int last=start;
		for(int i=1;i<=H;i++){
			if(last+1<=N&&ladder[i][last]==true){
				last++;
			}
			else if(last-1>=1&&ladder[i][last-1]==true){
				last--;
			}
		}
		if(last!=start) return false;
	}
	return true;
}
