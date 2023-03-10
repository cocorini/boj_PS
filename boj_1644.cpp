#include <iostream>
#include <vector>
using namespace std;

void find_primenum();
void make_partsum();
void twopo();
int N, ans=0;
vector<int> primenum, summ;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin>>N;
	if(N==1){
		cout<<0;
		return 0;
	}
	find_primenum();
	summ.assign(primenum.size()+1,0);
	make_partsum();
	twopo();
	cout<<ans;
}
void find_primenum(){
	for(int i=2;i<=N;i++){
		bool flag=true;
		for(int j=2;j*j<=i;j++) {
			if(i%j==0) {
				flag=false;
				break;
			}
		}
		if(flag) {
			primenum.push_back(i);}
	}
}
void make_partsum(){
	summ[1]=primenum[0];
	for(int i=2;i<summ.size();i++) summ[i]=summ[i-1]+primenum[i-1];
}
void twopo(){
	int left=0, right=0;
	bool flag=true;
	while(left<=right){
		if(right>=summ.size()) break;
		if(flag) right++;
		else left++;
		if(summ[right]-summ[left]>N) flag=false;
		else if(summ[right]-summ[left]==N) ans++;
		else flag=true;
	}
}
