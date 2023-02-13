#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#define MAX 200001
using namespace std;
void input();
void solve();
int N,C;
vector<int> v;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    input();
    solve();
}
void input() {
    cin>>N>>C;
    for(int i=0;i<N;i++) {
		  int a;
		  cin>>a;
		  v.push_back(a);
    }
    //오름차순으로 정리
    sort(v.begin(),v.end());
}
void solve() {
  //left, right, mid는 필수요소!
	int left=1, right=v.back()-v[0], mid;
  //공유기 개수인 C와 비교할 내가 설치한 공유기 개수인 compare_C, 가장 왼쪽을 기준으로 간격을 띄워서 설치해야 하니깐.. prev_loc을 이용해서 이전에 설치한 공유기의 위치를 갱신해주자
  int prev_loc, compare_C, ans=0;
  //이분탐색 시작!!
	while(left<=right){
    //첫 탐색에서 항상 compare_C=1로 갱신하고, mid 값을 찾아준다. 그리고 매번 가장 첫번째 집에는 공유기를 설치할 것이기 때문에 prev_loc=v[0]으로 초기화해줌.
		compare_C=1;
		mid=(left+right)/2;
		prev_loc=v[0];
    //반복문을 이용해서 집에서 이전 공유기 설치한 지점의 거리가 mid값 이상인 경우를 찾는다
		for(int i=1;i<N;i++){
			if(v[i]-prev_loc>=mid){
        //만약 찾는다면, 이전 위치가 현재 위치로 갱신 되고, 설치된 공유기 개수를 나타내는 compare_C값이 1 증가될 것임.
				compare_C++;
				prev_loc=v[i];
			}
		}
    //조건이상으로 공유기를 설치 했다면? -> 이 조건문이 잘 이해가 안된다..
		if(compare_C>=C){
      //ans값이 최댓값으로 갱신, 왜? 조건을 만족한 부류니깐 최댓값 갱신이 필요한거..
			ans=max(ans,mid);
      //mid값을 키우는 방법 -> v[i]-prev_loc값이 더 많은 값들을 허용하게 함.
			left=mid+1;
		}
    //원하는 개수만큼 공유기 설치에 실패한 것!
    //mid값을 줄이는 방법 -> v[i]-prev_loc값이 더 적은 값들만을 허용하게 함.
		else right=mid-1;
	}
	cout<<ans;
}
