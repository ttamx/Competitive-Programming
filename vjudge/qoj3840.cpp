#include<bits/stdc++.h>

using namespace std;

using ll = long long;
using db = double;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<db>;

const db PI=acosl(-1.L);

namespace fft{
    using cd = complex<db>;
    using vc = vector<cd>;
    void fft(vc &a){
        int n=a.size(),L=31-__builtin_clz(n);
        vc rt(n);
        rt[1]=1;
        for(int k=2;k<n;k*=2){
            cd z=polar(1.0,PI/k);
            for(int i=k;i<2*k;i++)rt[i]=i&1?rt[i/2]*z:rt[i/2];
        }
        vi rev(n);
        for(int i=1;i<n;i++)rev[i]=(rev[i/2]|(i&1)<<L)/2;
        for(int i=1;i<n;i++)if(i<rev[i])swap(a[i],a[rev[i]]);
        for(int k=1;k<n;k*=2)for(int i=0;i<n;i+=2*k)for(int j=0;j<k;j++){
            cd z=rt[j+k]*a[i+j+k];
            a[i+j+k]=a[i+j]-z;
            a[i+j]+=z;
        }
    }
    vl conv(const vl &a,const vl &b){
        if(a.empty()||b.empty())return {};
        vl res(a.size()+b.size());
        int n=1<<32-__builtin_clz(res.size());
        vc in(n),out(n);
        copy(a.begin(),a.end(),in.begin());
        for(int i=0;i<b.size();i++)in[i].imag(b[i]);
        fft(in);
        for(auto &x:in)x*=x;
        for(int i=0;i<n;i++)out[i]=in[-i&(n-1)]-conj(in[i]);
        fft(out);
        for(int i=0;i<res.size();i++)res[i]=imag(out[i])/(4*n)+.5;
        return res;
    }
}

const int N=1e5+5;

int n,q;
int p[N];
bool vis[N];
vl sum[N];
vi len;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=1;i<=n;i++)cin >> p[i];
    for(int i=1;i<=n;i++)if(!vis[i]){
        int u=i;
        vl a;
        do{
            vis[u]=true;
            a.emplace_back(u);
            u=p[u];
        }while(u!=i);
        int m=a.size();
        vl b(m+1);
        for(int i=0;i<m;i++)b[m-i]=a[i];
        vl c=fft::conv(a,b);
        sum[m].resize(m);
        len.emplace_back(m);
        for(int i=0;i<c.size();i++)sum[m][i%m]+=c[i];
    }
    sort(len.begin(),len.end());
    len.erase(unique(len.begin(),len.end()),len.end());
    while(q--){
        int k;
        cin >> k;
        ll ans=0;
        for(auto x:len)ans+=sum[x][k%x];
        cout << ans << "\n";
    }
}