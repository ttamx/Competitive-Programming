#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,k;
    cin >> n >> k;
    auto ask=[&](int i){
        cout << "? " << i << endl;
        int res;
        cin >> res;
        return res;
    };
    int pos=0,ans=0;
    while(pos<n){
        if(pos+k<=n){
            ans^=ask(pos+1);
            pos+=k;
            continue;
        }
        int x=pos+k-n;
        ans^=ask(pos+1-(k+x)/2)^ask(n-k+1);
        pos=n;
    }
    cout << "! " << ans << endl;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}