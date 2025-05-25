#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int calc(int *q, int t, int l, int r) {
    int s1 = q[min(t, r)] - q[l];
    if (r < t) return s1;
    l = min(t, r);
    int times = (r-l+1)/t;
    int s2 = q[t]*times;
    int s3 = q[r%t];
    return s1+s2+s3;
}

void test() {
    int n, m;
    cin >> n >> m;
    string s;
    cin >> s;
    int t = s.size();

    pair<int, int> pos[n*m+1];
    pos[0] = make_pair(0, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int a;
            cin >> a;
            pos[a] = make_pair(i, j);
        }
    }

    s = '.'+s;
    vector<int> px(t+1),py(t+1),sx(t+1),sy(t+1);
    for (int i = 0; i < t; i++) {
        if (s[i] == 'U') px[i]--;
        if (s[i] == 'D') px[i]++;
        if (s[i] == 'L') py[i]--;
        if (s[i] == 'R') py[i]++;
        sx[i]=px[i],sy[i]=py[i];
    }
    for(int i=1;i<t;i++)px[i]+=px[i-1],py[i]+=py[i-1];
    for(int i=t-2;i>=0;i--)sx[i]+=sx[i+1],sy[i]+=sy[i+1];
    auto calc=[&](ll l,ll r){
        ll res=0;
        if(l/t==r/t){
            l%=t,r%=t;
            return px[r]-(l?px[l-1]:0);
        }
        res+=px[r%t];
        res+=sx[l%t];
        res+=px.back()*(r/t-l/t-1);
    };
    int ptr = 0;
    ll ans = 0;
    for (int i = 0; i < n*m; i++) {
        int dx = pos[i+1].first - pos[i].first;
        int dy = pos[i+1].second - pos[i].second;
        if (dx < 0) dx += n;
        if (dy < 0) dy += m;

        int l = -1, r = (int)1e6;
        while (r-l > 1) {
            int mid = (l+r)>>1;

            int targ = ptr+mid;
            int ddx = calc(qx, t, ptr, ptr+mid);
            int ddy = calc(qy, t, ptr, ptr+mid);

            if (min(abs(dx-ddx), abs(n-dx-ddx)) + min(abs(dy-ddy), abs(m-dy-ddy)) <= mid) r = mid;
            else l = mid;
        }

        ptr = (ptr+r)%t;
        ans += r;
    }

    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while (t--) test();
}

/*
5
2 2
UUD
1 2
3 4
1 4
L
4 1 2 3
2 3
UD
1 3 5
2 4 6
3 3
RRLLUUDD
1 2 3
4 5 6
7 8 9
1 1
UDLR
1
*/