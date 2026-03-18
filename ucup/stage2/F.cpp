#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        int nn,n;
        cin >> nn >> n;
        vector<int> a[2];
        set<int> s;
        for(int i=0;i<n;i++){
            int x,y;
            cin >> x >> y;
            a[x-1].emplace_back(y);
            if(!s.emplace(y).second){
                s.erase(y);
            }
        }
        mint ans=1;
        if(a[0].empty()||a[1].empty()){
            for(int i=0;i<n*2+2;i++){
                ans*=2;
            }
            cout << ans << "\n";
            continue;
        }
        sort(a[0].begin(),a[0].end());
        sort(a[1].begin(),a[1].end());
        for(int t=0;t<2;t++){
            for(int i=0;i<a[0].size();i++){
                ans*=2;
            }
            {
                mint cur=1;
                int l=a[0][0];
                for(auto &x:a[1]){
                    if(x<l){
                        cur*=2;
                        s.erase(x);
                    }
                }
                ans*=(cur+1);
            }
            {
                mint cur=1;
                int r=a[0].back();
                for(auto &x:a[1]){
                    if(x>r){
                        cur*=2;
                        s.erase(x);
                    }
                }
                ans*=(cur+1);
            }
            swap(a[0],a[1]);
        }
        for(int i=0;i<s.size();i++){
            ans*=2;
        }
        cout << ans << "\n";
    }
}