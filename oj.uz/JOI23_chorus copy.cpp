#include <bits/stdc++.h>
#define ll long long
#define plll pair<pll, int>
#define pll pair<ll, ll>
#define F first
#define S second
using namespace std;
 
ll N, K;
ll in[1000006], suf[1000006];
pll dp[1000006];
char c[2000006];
 
pll f(plll p, ll x)
{
    auto [a, b] = p;
    return pll(a.F * x + a.S, b);
}
 
ll check(pll p1, pll p2, pll p3)
{
    return (p1.S - p2.S) * (p3.F - p2.F) >= (p2.S - p3.S) * (p2.F - p1.F);
}
 
pll operator+(pll p, pll q)
{
    return pll(p.F + q.F, p.S + q.S);
}
 
void calc(ll pen)
{
    for (int i = 1; i <= N; i++)
        dp[i] = pll(1e18, 0);
 
    deque<plll> hull, free;
    auto update = [&](plll p)
    {
        while (hull.size() >= 2 && check(hull[(int)hull.size() - 2].F, hull.back().F, p.F))
            hull.pop_back();
        hull.emplace_back(p);
    };
    free.emplace_back(plll(dp[0], 0));
    cerr  << pen << "\n";
    for (int i = 1; i <= N; i++)
    {
        // dp[j][k - 1] + (i - in[j]) * (N - j) - (suf[in[j] + 1] - suf[i + 1])
        // dp[j][k - 1] + i * N - i * j - in[j] * N + in[j] * j - suf[in[j] + 1] + suf[i + 1]
        // dp[j][k - 1] - in[j] * N + in[j] * j - suf[in[j] + 1]
        //                                                       - i * j
        //                                                               + i * N + suf[i + 1]
        while (!free.empty() && in[free.front().S] < i)
        {
            int j = free.front().S;
            update(plll(pll(-j, dp[j].F - in[j] * N + in[j] * j - suf[in[j] + 1]), dp[j].S));
            free.pop_front();
        }
        while (hull.size() >= 2 && f(hull[0], i) > f(hull[1], i))
            hull.pop_front();
 
        if (!hull.empty())
            dp[i] = min(dp[i], f(hull[0], i) + pll(i * N + suf[i + 1] + pen, -1));
        if (!free.empty())
            dp[i] = min(dp[i], free[0].F + pll(pen, -1));
        free.emplace_back(plll(dp[i], i));
        cerr << "(" << dp[i].first << "," << -dp[i].second << ")" << " \n"[i == N];
    }
}
 
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> N >> K;
    for (int i = 1; i <= 2 * N; i++)
        cin >> c[i];
    for (int i = 1, j = 0, k = 1; i <= N; i++, k++)
    {
        while (c[k] != 'B')
            j++, k++;
        in[i - 1] = j;
    }
    for (int i = 0; i < N; i++)
        in[i] = max((ll)i, in[i]);
    for (int i = 1, j = N, k = 1; i <= N; i++, k++)
    {
        while (c[k] != 'A')
            j--, k++;
        suf[i] = j;
    }
    for (int i = N; i >= 0; i--)
        suf[i] += suf[i + 1];
 
    ll l = 0, r = 1LL*N*N;
    while(l < r)
    {
        ll mid = (l + r + 1) / 2;
        calc(mid);
        if(-dp[N].S < K)
            r = mid - 1;
        else
            l = mid;
    }
    
    calc(l);
    cout << dp[N].F - l * K << '\n';
}