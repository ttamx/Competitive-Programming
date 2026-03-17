#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int M[6] = {
    int(1e9+7),
    int(1e9+9),
    998244353,
    964664131,
    991278907,
    983199559
};

ll binpow(ll a,ll b,ll MOD){
    ll res=1;
    while(b>0){
        if(b&1)res=res*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return res;
}

struct Fenwick{
    int n;
    vector<int> t;
    void init(int _n){
        n=_n;
        t.assign(n+1,0);
    }
    void update(int i,int v){
        for(i++;i<=n;i+=i&-i)t[i]+=v;
    }
    int query(int i){
        int res=0;
        for(i++;i>0;i-=i&-i)res+=t[i];
        return res;
    }
}f[6];

const int N=2e5+5;

ll a[6][N];
ll vals[6][N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    for(int i=1;i<=n;i++){
        ll p,q;
        cin >> p >> q;
        for(int j=0;j<6;j++){
            a[j][i]=(a[j][i-1]+p*binpow(q,M[j]-2,M[j]))%M[j];
            vals[j][i]=a[j][i];
        }
    }
    for(int i=0;i<6;i++){
        sort(vals[i],vals[i]+n+1);
        f[i].init(n+1);
        f[i].update(0,+1);
    }
    ll ans=0;
    for(int i=1;i<=n;i++){
        ll res=n;
        for(int j=0;j<6;j++){
            ll c=0;
            {
                int r=lower_bound(vals[j],vals[j]+n+1,a[j][i])-vals[j];
                int l=lower_bound(vals[j],vals[j]+n+1,a[j][i]-i-1)-vals[j];
                if(l<=r){
                    c+=f[j].query(r)-f[j].query(l-1);
                }
            }
            {
                int r=lower_bound(vals[j],vals[j]+n+1,M[j])-vals[j]-1;
                int l=lower_bound(vals[j],vals[j]+n+1,a[j][i]-i-1+M[j])-vals[j];
                if(l<=r){
                    c+=f[j].query(r)-f[j].query(l-1);
                }
            }
            int pos=lower_bound(vals[j],vals[j]+n+1,a[j][i])-vals[j];
            f[j].update(pos,+1);
            res=min(res,c);
        }
        ans+=res;
    }
    cout << ans;
}