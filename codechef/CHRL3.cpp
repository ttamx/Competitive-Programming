#include<bits/stdc++.h>

using namespace std;

int n,ans;
set<int> s;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;++i){
        int x;
        cin >> x;
        auto it=s.upper_bound(x);
        if(it==s.begin()){
            ans++;
        }else{
            s.erase(prev(it));
        }
        s.insert(x);
    }
    cout << ans;
}