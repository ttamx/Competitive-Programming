#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;
const int M=2e5+5;

int n;
int v1[M],v2[M],id1[N],id2[N];

struct Trapezoid{
    int a,b,c,d;
    Trapezoid(){};
}t[N];

struct Info{
    int val,freq;
    Info():val(0),freq(0){}
    Info(int _val,int _freq):val(_val),freq(_freq){}
    friend Info operator+(const Info &lhs,const Info &rhs){
        if(lhs.val>rhs.val)return lhs;
        if(lhs.val<rhs.val)return rhs;
        return Info(lhs.val,(lhs.freq+rhs.freq)%30013);
    }
    Info &operator+=(const Info &rhs){
        *this=*this+rhs;
        return *this;
    }
}dp[N];

struct fenwick{
    Info t[M];
    void update(int i,Info v){
        for(;i<M;i+=i&-i)t[i]+=v;
    }
    Info query(int i){
        Info res{};
        for(;i;i-=i&-i)res+=t[i];
        return res;
    }
}f;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> t[i].a >> t[i].b >> t[i].c >> t[i].d;
        v1[i*2-1]=t[i].a;
        v1[i*2]=t[i].b;
        v2[i*2-1]=t[i].c;
        v2[i*2]=t[i].d;
    }
    sort(v1+1,v1+2*n+1);
    sort(v2+1,v2+2*n+1);
    for(int i=1;i<=n;i++){
        t[i].a=lower_bound(v1+1,v1+2*n+1,t[i].a)-v1;
        t[i].b=lower_bound(v1+1,v1+2*n+1,t[i].b)-v1;
        t[i].c=lower_bound(v2+1,v2+2*n+1,t[i].c)-v2;
        t[i].d=lower_bound(v2+1,v2+2*n+1,t[i].d)-v2;
    }
    iota(id1+1,id1+n+1,1);
    iota(id2+1,id2+n+1,1);
    sort(id1+1,id1+n+1,[&](int i,int j){return t[i].a<t[j].a;});
    sort(id2+1,id2+n+1,[&](int i,int j){return t[i].b<t[j].b;});
    Info ans{};
    for(int _i=1,p=1;_i<=n;_i++){
        int i=id1[_i];
        while(t[id2[p]].b<t[i].a){
            f.update(t[id2[p]].d,dp[id2[p]]);
            p++;
        }
        dp[i]=f.query(t[i].c-1);
        if(dp[i].val==0)dp[i].freq=1;
        dp[i].val++;
        ans+=dp[i];
    }
    cout << ans.val << " " << ans.freq;
}