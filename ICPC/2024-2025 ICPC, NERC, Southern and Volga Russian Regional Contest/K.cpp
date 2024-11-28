#include<bits/stdc++.h>

using namespace std;

using ll = long long;

struct Info{
    ll c0,c1,ans;
    bool operator<(const Info &o)const{
        return c0*o.c1<c1*o.c0;
    }
    friend Info operator+(const Info &l,const Info &r){
        return {l.c0+r.c0,l.c1+r.c1,l.ans+r.ans+l.c1*r.c0};
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,va,vb;
    cin >> n >> va >> vb;
    vector<int> a(n),b(n);
    for(int i=0;i<n;i++){
        a[i]=gcd(i+1,va);
    }
    for(int i=0;i<n;i++){
        b[i]=gcd(i+1,vb);
    }
    vector<Info> sa,sb;
    for(int t=0;t<2;t++){
        for(int i=1;i<n;i++){
            Info cur{1,a[i]-a[i-1],a[i]-a[i-1]};
            while(!sa.empty()&&sa.back()<cur){
                cur=sa.back()+cur;
                sa.pop_back();
            }
            sa.emplace_back(cur);
        }
        swap(a,b);
        swap(sa,sb);
    }
    Info cur{0,0,0};
    int ia=0,ib=0;
    while(ia<sa.size()||ib<sb.size()){
        if(ib==sb.size()||(ia<sa.size()&&sb[ib]<sa[ia])){
            cur=cur+sa[ia];
            ia++;
        }else{
            cur=cur+sb[ib];
            ib++;
        }
    }
    cout << cur.ans+n*4-2;
}