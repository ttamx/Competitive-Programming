#include<bits/stdc++.h>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
#define rall(x) (x).rbegin(),(x).rend()

using namespace std;

using ll = long long;
using db = long double;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<db>;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using pdd = pair<db,db>;
const int INF=0x3fffffff;
// const int MOD=1000000007;
const int MOD=998244353;
const ll LINF=0x1fffffffffffffff;
const db DINF=numeric_limits<db>::infinity();
const db EPS=1e-9;
const db PI=acos(db(-1));

void runcase(){
    int n,m;
    cin >> n >> m;
    int k=n+m+1;
    vector<int> a(k),b(k);
    for(auto &x:a)cin >> x;
    for(auto &x:b)cin >> x;
    vector<int> p,t;
    for(int i=0;i<k;i++)(a[i]>b[i]?p:t).emplace_back(i);
    vector<int> c(k);
    int cp=0,ct=0;
    ll ans=0;
    for(int i=0;i<k;i++){
        if(cp==n){
            for(;i<k;i++){
                c[i]=2;
                ans+=b[i];
            }
            ct=-1;
            break;
        }
        if(ct==m){
            for(;i<k;i++){
                c[i]=1;
                ans+=a[i];
            }
            cp=-1;
            break;
        }
        if(a[i]>b[i]){
            c[i]=1;
            cp++;
            ans+=a[i];
        }else{
            c[i]=2;
            ct++;
            ans+=b[i];
        }
    }
    if(cp==n){
        for(int i=0;i<k;i++){
            ll res=ans;
            if(c[i]==1){
                res-=a[i];
                if(p.size()>n){
                    int j=p[n];
                    res+=a[j]-b[j];
                }else{
                    res+=a[k-1]-b[k-1];
                }
            }else{
                res-=b[i];
            }
            cout << res << " \n"[i==k-1];
        }
    }else if(ct==m){
        for(int i=0;i<k;i++){
            ll res=ans;
            if(c[i]==2){
                res-=b[i];
                if(t.size()>m){
                    int j=t[m];
                    res+=b[j]-a[j];
                }else{
                    res+=b[k-1]-a[k-1];
                }
            }else{
                res-=a[i];
            }
            cout << res << " \n"[i==k-1];
        }
    }else{
        assert(false);
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}