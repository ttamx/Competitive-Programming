#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,q;
    cin >> n >> q;
    int ans=0;
    set<int> s;
    for(int i=0;i<q;i++){
        int x;
        cin >> x;
        if(x>0){
            if(s.count(x)){
                s.clear();
                ans++;
            }
            s.emplace(x);
        }else{
            x=-x;
            s.erase(x);
        }
    }
    cout << ans;
}