#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,d,k;
    cin >> n >> d >> k;
    if(n==2){
        cout << "YES\n";
        exit(0);
    }
    if(k<2||d>=n||(k==2&&d!=n-1)){
        cout << "NO\n";
        exit(0);
    }
    vector<pair<int,int>> ans;
    for(int i=0;i<d;i++){
        ans.emplace_back(i,i+1);
    }
    int cur=d+1;
    for(int i=1;i<d;i++){
        if(cur==n)break;
        int dep=min(i,d-i);
        vector<int> a{i};
        for(int j=0;j<dep;j++){
            if(cur==n||a.empty())break;
            vector<int> b;
            int sub=(j==0?2:1);
            for(auto x:a){
                if(cur==n)break;
                for(int t=0;t<k-sub;t++){
                    if(cur==n)break;
                    ans.emplace_back(x,cur);
                    b.emplace_back(cur);
                    cur++;
                }
            }
            a=move(b);
        }
    }
    if(cur<n){
        cout << "NO\n";
        exit(0);
    }
    cout << "YES\n";
    for(auto [u,v]:ans){
        cout << u+1 << " " << v+1 << "\n";
    }
}