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
void solve(int cnt);
void check(int cnt, int num, int look);
void go(int cnt, int look);
int N, M, ANS=MMAX;
bool ZERO_FLAG=false;
vector<vector<int>> office(MAX, vector<int>(MAX,0)), tmp_office;
vector<pair<int,int>> CCTV;
vector<int> CCTV_LOOK;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    input();
    solve(0);
    cout<<ANS;
}
void input() {
	cin>>N>>M;
	for(int i=0;i<N;i++)
		for(int j=0;j<M;j++){
			cin>>office[i][j];
			if(office[i][j]&&office[i][j]<6)
				CCTV.emplace_back(i,j);
		}
	CCTV_LOOK.assign(CCTV.size(),0);
}
void solve(int cnt) {
	if(ZERO_FLAG) return;
  //종료조건
	if(cnt==CCTV.size()){
		tmp_office=office;
		int TMP=0;
		//케이스를 구해보자.
		for(int i=0;i<CCTV.size();i++){
			int cctv_look=CCTV_LOOK[i];
			int cctv_num=office[CCTV[i].first][CCTV[i].second];
			check(i, cctv_num, cctv_look);
		}
		for(int i=0;i<N;i++)
			for(int j=0;j<M;j++)
				if(!office[i][j]) TMP++;
		
		/*for(int i=0;i<N;i++){
			for(int j=0;j<M;j++)
				cout<<office[i][j]<<' ';
			cout<<'\n';
		}*/
		
		office=tmp_office;
		if(!TMP) {
			ANS=0;
			ZERO_FLAG=true;
			return;
		}
		ANS=min(ANS,TMP);
		return;
	}
	int cctv_num=office[CCTV[cnt].first][CCTV[cnt].second];
	switch(cctv_num){
		case 2:
		for(int i=0;i<2;i++){
			//방향 정하고 바로 다음 걸로 넘겨야지
			CCTV_LOOK[cnt]=i;
			solve(cnt+1);
		}
		break;
		case 5:
			//4방으로 무조건 다 체크
			CCTV_LOOK[cnt]=0;
			solve(cnt+1);
		break;
		default:
		for(int i=0;i<4;i++){
			//방향 정하고 바로 다음 걸로 넘겨야지
			CCTV_LOOK[cnt]=i;
			solve(cnt+1);
		}
		break;
	}
	
}
void check(int cnt, int num, int look){
	switch(num){
		case 1:
		go(cnt, look);
        break;
        case 2:
        if(look==0) {go(cnt, 0);go(cnt, 2);}
        else {go(cnt, 1);go(cnt, 3);}
        break;
        case 3:
        if(look==0) {go(cnt, 0);go(cnt, 1);}
        else if(look==1)
            {go(cnt, 1);go(cnt, 2);}
        else if(look==2)
        	{go(cnt, 2);go(cnt, 3);}
        else
            {go(cnt, 3);go(cnt, 0);}
        break;
        case 4:
        if(look==0)
            {go(cnt, 0);go(cnt, 1);go(cnt, 2);}
        else if(look==1)
            {go(cnt, 1);go(cnt, 2);go(cnt, 3);}
        else if(look==2)
            {go(cnt, 2);go(cnt, 3);go(cnt, 0);}
        else
            {go(cnt, 3);go(cnt, 0);go(cnt, 1);}
        break;
        default:
            go(cnt, 0);go(cnt, 1);go(cnt, 2);go(cnt, 3);
        break;
	}
}
void go(int cnt, int look){
    int y=CCTV[cnt].first;
    int x=CCTV[cnt].second;
    switch(look){
        case 0:
            for(int i=x+1;i<M;i++){
                if(office[y][i]==6) break;
                else if(!office[y][i]) office[y][i]=-1;
            }
        break;
        case 1:
            for(int i=y+1;i<N;i++){
                if(office[i][x]==6) break;
                else if(!office[i][x]) office[i][x]=-1;
            }
        break;
        case 2:
            for(int i=x-1;i>=0;i--){
                if(office[y][i]==6) break;
                else if(!office[y][i]) office[y][i]=-1;
            }
        break;
        default:
            for(int i=y-1;i>=0;i--){
                if(office[i][x]==6) break;
                else if(!office[i][x]) office[i][x]=-1; 
            }
        break;
    }
}
