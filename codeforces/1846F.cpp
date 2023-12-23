#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<int> f(10);
    int t=-1;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        f[x]++;
    }
    cout << "- 0" << endl;
    while(t==-1){
        vector<vector<int>> a(10);
        for(int i=0;i<n;i++){
            int x;
            cin >> x;
            a[x].emplace_back(i);
        }
        vector<int> res;
        for(int i=1;i<=9;i++){
            if(a[i].size()>f[i]){
                t=i;
            }else{
                for(auto x:a[i])res.emplace_back(x);
            }
        }
        if(t==-1){
            cout << "- 0" << endl;
        }else{
            cout << "- " << res.size();
            for(auto x:res)cout << " " << x+1;
            cout << endl;
            n-=res.size();
        }
    }
    while(true){
        int ans=0;
        for(int i=0;i<n;i++){
            int x;
            cin >> x;
            if(x!=t)ans=i+1;
        }
        if(ans)return void(cout << "! " << ans << endl);
        cout << "- 0" << endl;
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}