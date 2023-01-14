#include <iostream>
#include <vector>
#define MAX 100001
using namespace std;
void input();
void solve(int in_first, int in_end, int post_first, int post_end);
int N;
vector<int> inorder(MAX, 0), postorder(MAX, 0), idx(MAX, 0);
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	input();
	solve(1,N,1,N);
}
void input(){
	cin>>N;
	for(int i=1;i<=N;i++) {
		cin>>inorder[i];
		idx[inorder[i]]=i;
	}
	for(int i=1;i<=N;i++)
		cin>>postorder[i];
}
//재귀를 진행하면서 사실상 root노드만 출력해내면 된다. preorder 특성상
void solve(int in_first, int in_end, int post_first, int post_end){
	//종료 조건: 더이상 분할이 되지 않는 경우..
	if (in_first > in_end||post_first > post_end) return;
	
	int rootidx_inorder=idx[postorder[post_end]];
	//중위순회의 idx를 이용해서 left, right 파트의 노드 개수를 알 수 있다.
	int left_cnt=rootidx_inorder-in_first;
	int right_cnt=in_end-rootidx_inorder;
	cout<<postorder[post_end]<<' ';
	
	//left_node
	solve(in_first, in_first+left_cnt-1, post_first, post_first+left_cnt-1);
	//right_node
	solve(rootidx_inorder+1, rootidx_inorder+right_cnt, post_end-right_cnt, post_end-1);
}
