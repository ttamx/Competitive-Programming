#include "template.hpp"
#include "flow/binary-optimization.hpp"

const int N=2e5+5;

int lp[N];

void runcase(){
    int n,k;
    cin >> n >> k;
    vector<int> p(n),c(n),lv(n);
    for(int i=0;i<n;i++){
        cin >> p[i] >> c[i] >> lv[i];
    }
    auto calc=[&](int m){
        BinaryOptimization<ll,false> bo(n);
        int id=-1;
        for(int i=0;i<n;i++){
            if(lv[i]<=m&&c[i]==1){
                if(id==-1||p[i]>p[id]){
                    id=i;
                }
            }
        }
        for(int i=0;i<n;i++){
            if(lv[i]>m||(c[i]==1&&i!=id))continue;
            if(c[i]&1){
                bo.add1(i,0,p[i]);
            }else{
                bo.add1(i,p[i],0);
            }
        }
        for(int i=0;i<n;i++){
            if(lv[i]>m||(c[i]==1&&i!=id))continue;
            for(int j=0;j<i;j++){
                if(lv[j]>m||(c[j]==1&&j!=id))continue;
                int s=c[i]+c[j];
                if(lp[s]==s){
                    if(c[i]&1){
                        bo.add2(i,j,0,0,-INF,0);
                    }else{
                        bo.add2(i,j,0,-INF,0,0);
                    }
                }
            }
        }
        return bo.solve();
    };
    int l=0,r=n+1;
    while(l<r){
        int m=(l+r)/2;
        if(calc(m)>=k)r=m;
        else l=m+1;
    }
    cout << (l>n?-1:l) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    for(int i=2;i<N;i++){
        if(lp[i])continue;
        for(int j=i;j<N;j+=i){
            if(!lp[j])lp[j]=i;
        }
    }
    int t(1);
    while(t--)runcase();
}