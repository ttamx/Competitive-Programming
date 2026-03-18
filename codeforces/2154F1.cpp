#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"
#include "modular-arithmetic/combinatorics.hpp"

using mint = mint998;

Combinatorics<mint> comb;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    mint ans=0;
    auto work=[&](int v){
        mint res=1;
        int last1=-1,last2=-1,last=-1;
        int left1=0,left2=0;
        for(int i=0;i<n;i++){
            if(a[i]==-1){
                continue;
            }
            int len=i-last-1;
            if(a[i]<=v){
                if(last1!=-1&&a[i]<a[last1]){
                    return;
                }
                int c=a[i]-(last1==-1?0:a[last1])-1-left1;
                left1=0;
                res*=comb.C(len,c);
                left2+=len-c;
                last1=i;
            }else{
                if(last2!=-1&&a[i]<a[last2]){
                    return;
                }
                int c=a[i]-(last2==-1?0:a[last2])-1-left2;
                left2=0;
                res*=comb.C(len,c);
                left1+=len-c;
                last2=i;
            }
            last=i;
        }
        int rem=v-(last1==-1?0:a[last]);
        ans+=res*comb.C(n-last-1,rem);
    };
    for(int v=1;v<n;v++){
        work(v);
        cerr << ans << " ";
    }
    cerr << "\n";
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}