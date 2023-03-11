#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    int cur=0,mn=0,ans=0,left=0,all=0;
    for(int i=0;i<n;i++){
        int o;
        cin >> o;
        if(o==1){
            all++;
            cur++;
        }else{
            int mal=1;
            int fem=all-mal;
            mn=mal/2+fem/2;
            cur=all-(mal/2*2+fem/2*2);
        }
        ans=max(ans,mn+cur);
    }
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}