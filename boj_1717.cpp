#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <algorithm>
#include <stack>
#include <set>
#include <deque>
#include <tuple>
using namespace std;

int M, N;
vector<int> root;
vector<bool> decided, visited;

int Find(int x);
void Union(int x, int y);

//유니온 파인드 대표 문제라고 생각하면 될거같음
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin >> N >> M;
	root.assign(N+1, 0);
	for(int i=1;i<=N;i++) root[i]=i;
	for(int i=1;i<=M;i++){
		int K, a, b;
		cin>>K>>a>>b;
    //root 갱신 할 때 인덱스가 큰 경우 작은 값으로 갱신해야 함 혹은 뭐 반대로 해도 될듯..?
		if(!K) Union(min(a,b), max(a,b));
		else {
      //내가 잘 이해가 안되었던 부분.. 사실 Find함수에서 return을 통해 root가 계속해서 갱신되므로, 
      //어차피 root[a], root[b]만 비교하면 되는거아냐? 라고 생각했지만.. 유니온파인드 알고리즘의 특성상
			//같은 루트를 가지고 있지만 갱신이 덜 되었을 수도 있기 때문에 비교하는 상황에서는 Find함수를 이용해서 진짜 찐막 최종 부모 노드를 찾아서 비교해야 한다고 함..
      //어쩐지 계속 중간에서 틀렸습니다 뜨더라.. 끙
      //그리고 추가적으로, 유니온파인드는 크루스칼 알고리즘에서 MST찾을 때 사이클 확인하는 것에 이용된다는 것을 잊지말자!
      if(Find(a)==Find(b)) cout<<"YES\n";
			else cout<<"NO\n";
		}
	}
}

int Find(int x){
	if(x==root[x]) return x;
	return root[x]=Find(root[x]);
}
void Union(int x, int y){
	x=Find(x);
	y=Find(y);
	
	root[y]=x;
}
