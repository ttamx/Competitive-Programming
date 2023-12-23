// tested on  https://www.spoj.com/problems/POLYMUL/
#include<bits/stdc++.h>

using namespace std;

typedef long double ld;
typedef complex<ld> cd;

const ld PI=acosl(-1);

void fft(vector<cd> &a){
    int n=a.size(),L=31-__builtin_clz(n);
    vector<cd> rt(n);
    rt[1]=1;
    for(int k=2;k<n;k*=2){
        cd z=polar(1.0L,PI/k);
        for(int i=k;i<2*k;i++)rt[i]=i&1?rt[i/2]*z:rt[i/2];
    }
    vector<int> rev(n);
    for(int i=1;i<n;i++)rev[i]=(rev[i/2]|(i&1)<<L)/2;
    for(int i=1;i<n;i++)if(i<rev[i])swap(a[i],a[rev[i]]);
    for(int k=1;k<n;k*=2)for(int i=0;i<n;i+=2*k)for(int j=0;j<k;j++){
        cd z=rt[j+k]*a[i+j+k];
        a[i+j+k]=a[i+j]-z;
        a[i+j]+=z;
    }
}

vector<ld> conv(const vector<ld> &a,const vector<ld> &b){
    if(a.empty()||b.empty())return {};
    vector<ld> res(a.size()+b.size()-1);
    int L=32-__builtin_clz(res.size()),n=1<<L;
    vector<cd> in(n),out(n);
    copy(a.begin(),a.end(),in.begin());
    for(int i=0;i<b.size();i++)in[i].imag(b[i]);
    fft(in);
    for(auto &x:in)x*=x;
    for(int i=0;i<n;i++)out[i]=in[-i&(n-1)]-conj(in[i]);
    fft(out);
    for(int i=0;i<res.size();i++)res[i]=out[i].imag()/(4*n);
    return res;
}

void runcase(){
    int n;  
    cin >> n;
    n++;
    vector<ld> a(n),b(n);
    for(auto &x:a)cin >> x;
    for(auto &x:b)cin >> x;
    reverse(a.begin(),a.end());
    reverse(b.begin(),b.end());
    auto c=conv(a,b);
    reverse(c.begin(),c.end());
    for(auto x:c)cout << (long long)round(x) << ' ';
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}