#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#define MAX 10000
#define X 1000000007
#define ll unsigned long long
using namespace std;
void input();
void solve();
ll recur(ll base, int exp);
int M;
vector<int> N(MAX, 0), S(MAX, 0);
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    input();
    solve();
}
void input() {
    cin >> M;
    for (int i = 0; i < M; i++)
        cin >> N[i] >> S[i];
}
void solve() {
    ll ans = 0;
    for (int i = 0; i < M; i++) {
        ll y = S[i] * recur(N[i], X - 2) % X;
        ans += y;
        ans %= X;
    }
    cout << ans;
}
ll recur(ll base, int exp) {
    if (exp == 1) return base;
    ll ret = recur(base, exp / 2);
    //지수가 홀수 일때
    if (exp % 2)
        return ret * ret % X * base % X;
    //지수가 짝수 일때
    return ret * ret % X;
}
