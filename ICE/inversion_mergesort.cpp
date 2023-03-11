#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 1e5 + 5;

int n;
int a[N];

pair<vector<int>, ll> solve(int l, int r)
{
    if (l == r)
    {
        return {{a[l]}, 0};
    }
    int m = (l + r) / 2;
    auto [vl, il] = solve(l, m);
    auto [vr, ir] = solve(m + 1, r);
    vector<int> vec;
    ll inv = il + ir;
    int lid = 0, rid = 0;
    while (lid < vl.size() && rid < vr.size())
    {
        while (lid < vl.size() && vl[lid] <= vr[rid])
        {
            vec.push_back(vl[lid++]);
        }
        inv += vl.size() - lid;
        vec.push_back(vr[rid++]);
    }
    while (lid < vl.size())
    {
        vec.push_back(vl[lid++]);
    }
    while (rid < vr.size())
    {
        vec.push_back(vr[rid++]);
        inv += vl.size() - lid;
    }
    return {vec, inv};
}

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    cout << solve(1, n).second;
}