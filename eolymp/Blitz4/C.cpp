#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        int n,k;
        cin >> n >> k;
        set<int> s;
        map<int,int> cnt;
        for(int i=0;i<n;i++){
            int x;
            cin >> x;
            cnt[x]++;
            s.emplace(x);
        }
        vector<int> ans;
        for(auto e:s){
            if(cnt[e]>=cnt[k-e]){
                while(cnt[e]>0){
                    cnt[e]--;
                    ans.emplace_back(e);
                    if(cnt[k-e]>0){
                        ans.emplace_back(k-e);
                        cnt[k-e]--;
                    }
                }
            }
        }
        for(auto x:ans){
            cout << x << " ";
        }
        cout << "\n";
    }
}