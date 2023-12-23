#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef double ld;
typedef complex<ld> cd;

const ld PI=acos(-1);

void fft(vector<cd> &a,bool inv){
    int n=a.size();
    for(int i=1,j=0;i<n;i++){
        int b=n>>1;
        for(;j&b;b>>=1)j^=b;
        j^=b;
        if(i<j)swap(a[i],a[j]);
    }
    for(int l=2;l<=n;l<<=1){
        ld ang=2*PI/l*(inv?-1:1);
        cd wl(cos(ang),sin(ang));
        for(int i=0;i<n;i+=l){
            cd w(1);
            for(int j=0;j<l/2;j++){
                cd u=a[i+j],v=a[i+j+l/2]*w;
                a[i+j]=u+v;
                a[i+j+l/2]=u-v;
                w*=wl;
            }
        }
    }
    if(inv)for(auto &x:a)x/=n;
}

vector<ll> mul(const vector<ll> &a,const vector<ll> &b){
    vector<cd> fa(a.begin(),a.end()),fb(b.begin(),b.end());
    int n=1;
    while(n<a.size()+b.size())n<<=1;
    fa.resize(n);
    fb.resize(n);
    fft(fa,false);
    fft(fb,false);
    for(int i=0;i<n;i++)fa[i]*=fb[i];
    fft(fa,true);
    vector<ll> res(n);
    for(int i=0;i<n;i++)res[i]=round(fa[i].real());
    return res;
}

string sa,sb;
int n,m;
vector<ll> pa[4],pb[4],pc;
map<char,int> mp;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    mp['A']=0,mp['T']=1,mp['C']=2,mp['G']=3;
    cin >> sa >> sb;
    n=sa.size(),m=sb.size();
    for(int i=0;i<4;i++){
        pa[i].resize(n);
        pb[i].resize(m);
    }
    pc.resize(n+m-1);
    for(int i=0;i<n;i++)pa[mp[sa[i]]][i]++;
    for(int i=0;i<m;i++)pb[mp[sb[m-i-1]]][i]++;
    for(int i=0;i<4;i++){
        auto res=mul(pa[i],pb[i]);
        for(int j=0;j<n+m-1;j++)pc[j]+=res[j];
    }
    ll ans=m;
    for(int i=m-1;i<n;i++)ans=min(ans,m-pc[i]);
    cout << ans;
}