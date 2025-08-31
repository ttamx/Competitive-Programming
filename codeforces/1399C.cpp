#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<int> cnt(2*n+1);
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        cnt[x]++;
    }
    int ans=0;
    for(int s=1;s<=2*n;s++){
        int res=0;
        for(int i=1;i*2<s;i++){
            res+=min(cnt[i],cnt[s-i]);
        }
        if(s%2==0){
            res+=cnt[s/2]/2;
        }
        ans=max(ans,res);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}