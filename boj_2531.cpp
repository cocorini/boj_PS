/*

회전초밥형태 -> deque를 이용하겠다고 생각함.
슬라이딩 윈도우 알고리즘에 대한 지식이 부족해, 처음에는 무작정 브루트포스로 하려다 시간초과.. 사실 30000*3000해서 9*10^7로 아슬아슬하게 통과하려나 했지만 그렇지 못함
고정된 창내부의 원소들의 부분합을 계산하는데 이용된다는 것을 이해하고 난후, 원소 개수를 체크하는 것에 이를 적용함.
deque의 front원소는 visited--가 되며, 가장 후순위로 다시 들어가게 되고, deque의 k-1번째 원소의 visited++가 되어 visited가 1이상인 갯수를 구해주었다.
60ms로 여유롭게 통과->일종의 memoization이 아닐까? 생각함.

*/
#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <algorithm>
#include <stack>
#include <set>
#include <deque>
#include <map>
#include <cmath>
#include <tuple>
#define ll long long
#define div 1000000
using namespace std;

int N, d, k, c;
deque<int> dq;

void solve();

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> N >> d >> k >> c;
    for (int i = 0; i < N; i++) {
        int a;
        cin >> a;
        dq.push_back(a);
    }

    solve();
}
void solve() {

    vector<int> visited(d + 1, 0);

    visited[c]++;

    int ans = 0;
    for (int i = 0; i < N; i++) {
        int tmp = 0;
        int front = dq.front();
        if (!i) {
            for (int j = 0; j < k; j++) visited[dq[j]]++;
            for (int j = 1; j <= d; j++) if (visited[j]) tmp++;
        }
        else {
            visited[dq[k - 1]]++;
            for (int j = 1; j <= d; j++) if (visited[j]) tmp++;
        }
        ans = max(tmp, ans);
        dq.pop_front();
        dq.push_back(front);
        visited[front]--;
    }
    cout << ans;
}
