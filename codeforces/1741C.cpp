#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<int> qs(n+1);
    for(int i=1;i<=n;++i){
        cin >> qs[i];
        qs[i]+=qs[i-1];
    }
    int ans=n;
    for(int i=1;i<=n;++i){
        if(i>=ans)break;
        int sum=qs[i];
        int pre=i,cur=i+1;
        bool can=true;
        int tmp=i;
        while(can&&cur<=n){
            while(cur<=n&&qs[cur]-qs[pre]<sum)cur++;
            if(cur>n||qs[cur]-qs[pre]>sum)can=false;
            else tmp=max(tmp,cur-pre),pre=cur,cur++;
        }
        if(can)ans=min(ans,tmp);
    }
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();
}