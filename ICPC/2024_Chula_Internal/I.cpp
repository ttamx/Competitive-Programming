#include<bits/stdc++.h>

using namespace std;

int ask(int a,int b){
    cout << "? " << a << " " << b << endl;
    int res;
    cin >> res;
    return res;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<int> a;
        int ans=(1<<30)-1;
        for(int i=2;i<=n;i++){
            int x=ask(1,i);
            ans=min(ans,x);
            a.emplace_back(x);
        }
        sort(a.begin(),a.end());
        for(int i=1;i<n-1;i++){
            ans=min(ans,a[i]^a[i-1]);
        }
        cout << "! " << ans << endl;
    }
}