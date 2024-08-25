#include "template.hpp"

void runcase(){
    int n,k;
    cin >> n >> k;
    vector<int> ans;
    for(int i=1;i<=2*n;i+=2){
        if(i>=(1<<k)){
            ans.emplace_back(1);
        }else{
            int res=0;
            for(int j=0;j<k;j++){
                res|=(i>>j&1)<<(k-j-1);
            }
            ans.emplace_back(res);
        }
    }
    for(auto x:ans)cout << x << " ";
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}