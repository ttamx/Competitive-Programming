#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const ll LIM=4e18;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        ll a,b,c,d;
        cin >> a >> b >> c >> d;
        ll g1=gcd(a,b);
        ll g2=gcd(c,d);
        a/=g1,b/=g1;
        c/=g2,d/=g2;
        ll ans=b+d;
        queue<pair<pair<ll,ll>,pair<ll,ll>>> q;
        q.push({{a,b},{c,d}});
        cerr << a << " / " << b << " " << c << " / " << d << "\n";
        cerr << b*c-a*d << "\n";
        int t=0;
        while(!q.empty()&&++t<=1000){
            auto [x,y]=q.front();
            q.pop();
            if(__int128_t(x.second)*y.first-__int128_t(x.first)*y.second==1)continue;
            ll e=x.first+y.first;
            ll f=x.second+y.second;
            ll g=gcd(e,f);
            if(g>1){
                cerr << "FOUND " << e << " " << f << " : " << g << "\n";
            }
            e/=g;
            f/=g;
            ans=min(ans,f);
            if(e>LIM||f>LIM)continue;
            q.push({x,{e,f}});
            q.push({{e,f},y});
        }
        cout << ans << "\n";
    }
}