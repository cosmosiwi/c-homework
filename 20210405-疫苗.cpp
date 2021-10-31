#include <iostream>
#include <queue>
#include <vector>
using namespace std;
typedef long long ll;
typedef pair<ll, int> pli;
const ll inf = 1e18;
const int maxn = 505;
inline ll factor(ll a, ll b, ll& x, ll& y) {
    if (b == 0)
        return x = 1, y = 0, a;
    ll r = factor(b, a % b, y, x);
    return y -= (a / b) * x, r;
}
ll dmin[maxn], sum[maxn], d[maxn], ind[maxn], fac[maxn][maxn], res[maxn][maxn];
int n, m;
void build() {
    //预处理，计算两两线路周期 a、b 之间的最大公约数 r
    //以及满足 ax + by = r 的一个解 x
    ll x, y;
    for (int i = 1; i <= m; i++)
        for (int j = i + 1; j <= m; j++)
            fac[i][j] = fac[j][i] = factor(sum[i], sum[j], x, y), res[i][j] = x,
            res[j][i] = y;
}
inline ll tmin(ll i, ll j, ll c) {
    ll a = sum[i], b = sum[j], x = res[i][j], r = fac[i][j];
    c = (c % b + b) % b;
    return c % r ? inf : (b /= r, a * ((x * c / r % b + b) % b));
}
struct Node {
    int next;
    ll sum, num;
} g[maxn][maxn];
vector<int> station[maxn];
priority_queue<pli, vector<pli>, greater<pli>> pq;
bool vis[maxn];
void dijkstra() {
    for (int i = 0; !pq.empty() && i != m;) {
        int x = pq.top().second, y;
        ll min_ = pq.top().first;
        pq.pop();
        if (vis[x])
            continue;
        i++, vis[x] = 1, y = ind[x];
        while (true) {
            dmin[y] = min(dmin[y], min_);
            for (auto& xx : station[y]) {
                if (vis[xx])
                    continue;
                ll dtmp = min_ + tmin(x, xx, g[xx][y].sum - min_);
                if (d[xx] > dtmp)
                    d[xx] = dtmp, ind[xx] = y, pq.push({dtmp, xx});
            }
            min_ += g[x][y].num, y = g[x][y].next;
            if (y == ind[x])
                break;
        }
    }
}
int v[maxn];
int main() {
    ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0), cin >> n >> m,
        fill(d, d + maxn, inf), fill(dmin, dmin + maxn, inf);
    for (int i = 1, k, j, a, b; i <= m; i++) {
        for (cin >> k, j = 0; j != k; j++) {
            cin >> a >> b, station[a].push_back(i),
                v[j] = a, g[i][a].sum = sum[i], g[i][a].num = b, sum[i] += b;
            if (a == 1)
                d[i] = g[i][a].sum, ind[i] = a, pq.push({d[i], i});
        }
        for (j = 0; j != k; j++)
            g[i][v[j]].next = v[(j + 1) % k];
    }
    build(), dijkstra();
    for (int i = 2; i <= n; i++)
        dmin[i] == inf ? cout << "inf\n" : cout << dmin[i] << "\n";
}
