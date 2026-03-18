#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<int> a(n),b(m);
    for(auto &x:a)cin >> x;
    for(auto &x:b)cin >> x;
    mint ans=1;
    int last=-1,mn=INF;
    for(int i=n-1;i>=0;i--){
        if(a[i]<mn){
            mn=a[i];
            if(!b.empty()&&mn>=b.back()){
                if(last!=-1){
                    ans*=last-i;
                    last=-1;
                }
                if(b.back()==mn){
                    b.pop_back();
                    last=i;
                }
            }else{
                cout << 0 << "\n";
                return;
            }
        }
    }
    if(!b.empty()){
        cout << 0 << "\n";
    }else{
        cout << ans << "\n";
    }

}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}