#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef complex<ld> Z;

const ld PI=acos(-1);

void fft(vector<Z> &a,bool inv){
    int n=a.size();
    for(int i=1,j=0;i<n;i++){
        int b=n>>1;
        for(;j&b;b>>=1)j^=b;
        j^=b;
        if(i<j)swap(a[i],a[j]);
    }
    for(int l=2;l<=n;l<<=1){
        ld ang=2*PI/l*(inv?-1:1);
        Z wl(cos(ang),sin(ang));
        for(int i=0;i<n;i+=l){
            Z w(1);
            for(int j=0;j<l/2;j++){
                Z u=a[i+j],v=a[i+j+l/2]*w;
                a[i+j]=u+v;
                a[i+j+l/2]=u-v;
                w*=wl;
            }
        }
    }
    if(inv)for(auto &x:a)x/=n;
}

vector<ll> multiply(const vector<ll> &a,const vector<ll> &b){
    vector<Z> fa(a.begin(),a.end()),fb(b.begin(),b.end());
    ll n=1;
    while(n<a.size()+b.size())n<<=1;
    fa.resize(n);
    fb.resize(n);
    fft(fa,false);
    fft(fb,false);
    for(ll i=0;i<n;i++)fa[i]*=fb[i];
    fft(fa,true);
    vector<ll> res(n);
    for(ll i=0;i<n;i++)res[i]=llround(fa[i].real());
    return res;
}

void solve(){
    int n;
    cin >> n;
    vector<ll> pa(n+1),pb(n+1);
    for(int i=n;i>=0;i--)cin >> pa[i];
    for(int i=n;i>=0;i--)cin >> pb[i];
    auto pc=multiply(pa,pb);
    for(int i=2*n;i>=0;i--)cout << pc[i] << " \n"[i==0];
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)solve();
}