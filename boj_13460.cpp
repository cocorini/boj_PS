#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <tuple>
using namespace std;
void input();
void solve();
int search(int y, int x, int yy, int xx, int i, bool first_R);
//상,하,좌,우 순으로..
int dx[4]={0,0,-1,1};
int dy[4]={-1,1,0,0};
int N,M,tmp_Ry,tmp_Rx,tmp_By,tmp_Bx;
vector<string> board;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	input();
	solve();
}
void input(){
	cin>>N>>M;
	for(int i=0;i<N;i++) {
		string s;
		cin>>s;
		board.push_back(s);
	}
}
void solve(){
	//R, B 위치를 알아내자.
	pair<int,int> R, B;
	for(int i=0;i<N;i++){
		for(int j=0;j<M;j++){
			if(board[i][j]=='R') {
				R=make_pair(i,j);
				board[i][j]='.';
			}
			else if(board[i][j]=='B') {
				B=make_pair(i,j);
				board[i][j]='.';
			}
		}
	}
	//구슬 큐 만들기!
	queue<tuple<int,int,int,int,int>> RnB;
	RnB.emplace(R.first,R.second,B.first,B.second,0);
	while(!RnB.empty()){
		int R_y=get<0>(RnB.front());
		int R_x=get<1>(RnB.front());
		int B_y=get<2>(RnB.front());
		int B_x=get<3>(RnB.front());
		int cnt=get<4>(RnB.front());
		//cout<<cnt<<'\n'<<"R: "<<R_y<<' '<<R_x<<" || "<<"B: "<<B_y<<' '<<B_x<<'\n';
		RnB.pop();
		//cnt 확인하기!!
		if(cnt==10){
			cout<<-1;
			break;
		}
		//보드를 기울여보자
		//이때, 내가 보드를 기울이는 방향에 앞서 있는 구슬부터 움직인다..
		int hole_in;
		for(int i=0;i<4;i++){
			switch(i){
				//상
				case 0:
				//R부터 움직여
				if(R_y<B_y) hole_in=search(R_y,R_x,B_y,B_x,i,true);
				//B부터 움직여
				else hole_in=search(B_y,B_x,R_y,R_x,i,false);
				break;
				//하
				case 1:
				//B부터 움직여
				if(R_y<B_y) hole_in=search(B_y,B_x,R_y,R_x,i,false);
				//R부터 움직여
				else hole_in=search(R_y,R_x,B_y,B_x,i,true);
				break;
				//좌
				case 2:
				//R부터 움직여
				if(R_x<B_x) hole_in=search(R_y,R_x,B_y,B_x,i,true);
				//B부터 움직여
				else hole_in=search(B_y,B_x,R_y,R_x,i,false);
				break;
				//우
				default:
				//B부터 움직여
				if(R_x<B_x) hole_in=search(B_y,B_x,R_y,R_x,i,false);
				//R부터 움직여
				else hole_in=search(R_y,R_x,B_y,B_x,i,true);
				break;
			}
			//빨간구슬이 나왔다!!!
			if(hole_in==1){
				cout<<cnt+1;
				return;
			}
			//아무 구슬도 나오지 않았으므로, 다음 cnt를 진행하자.
			else if(hole_in==2)
				RnB.emplace(tmp_Ry,tmp_Rx,tmp_By,tmp_Bx,cnt+1);
		}
	}
}
int search(int y, int x, int yy, int xx, int i, bool first_R){
	queue<pair<int,int>> q;
	q.emplace(y,x);
	bool R_escape=false, B_escape=false;
	//첫번째 구슬 탐색
	while(!q.empty()){
		int y1=q.front().first;
		int x1=q.front().second;
		q.pop();
		int ny=y1+dy[i];
		int nx=x1+dx[i];
		if(ny>=0&&nx>=0&&ny<N&&nx<M){
			if(board[ny][nx]=='.'){
				if(ny==yy&&nx==xx) continue;
				else{
					y=ny;x=nx;
					q.emplace(ny, nx);
				}
			}
			else if(board[ny][nx]=='O'){
				y=-1;x=-1;
				if(first_R) R_escape=true;
				else B_escape=true;
				break;
			}
		}
	}
	//큐 초기화
	q=queue<pair<int,int>>();
	//두번째 구슬 탐색
	q.emplace(yy,xx);
	while(!q.empty()){
		int y1=q.front().first;
		int x1=q.front().second;
		q.pop();
		int ny=y1+dy[i];
		int nx=x1+dx[i];
		if(ny>=0&&nx>=0&&ny<N&&nx<M){
			if(board[ny][nx]=='.'){
				if(ny==y&&nx==x) continue;
				else{
					yy=ny;xx=nx;
					q.emplace(ny, nx);
				}
			}
			else if(board[ny][nx]=='O'){
				if(first_R) B_escape=true;
				else R_escape=true;
				break;
			}
		}
	}
	if(R_escape&&!B_escape) return 1;
	else if(B_escape) return 0;
	else {
		if(first_R){
			tmp_Ry=y;tmp_Rx=x;
			tmp_By=yy;tmp_Bx=xx;
		}
		else{
			tmp_Ry=yy;tmp_Rx=xx;
			tmp_By=y;tmp_Bx=x;
		}
		return 2;
	}
}
