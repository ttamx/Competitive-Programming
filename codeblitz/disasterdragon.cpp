#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll,ll> p2;

const int N=1e5+5;
const int K=1<<18;

int n,q,a,b;

struct fenwick{
    int t[N];
    void add(int i,int v){
        while(i<N)t[i]+=v,i+=i&-i;
    }
    int read(int i){
        int res=0;
        while(i)res+=t[i],i-=i&-i;
        return res;
    }
    int l(){
        int l=1,r=n;
        while(l<r){
            int m=(l+r)/2;
            if(read(m)>b)l=m+1;
            else r=m;
        }
        return l;
    }
    int r(){
        int l=1,r=n;
        while(l<r){
            int m=(l+r+1)/2;
            if(read(m)<a)r=m-1;
            else l=m;
        }
        return l;
    }
}f;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q >> a >> b;
    while(q--){
        int o,x,c;
        cin >> o >> x >> c;
        if(o==1){
            f.add(1,c);
            f.add(x+1,-c);
        }else{
            f.add(x,-c);
        }
        int l=f.l(),r=f.r();
        if(l>r)cout << -1 << '\n';
        else if(l==r)cout << l << '\n';
        else cout << l << ' ' << r << '\n';
    }
}