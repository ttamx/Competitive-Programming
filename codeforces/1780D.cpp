#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    auto ask=[&](int x){
        cout << "- " << x << endl;
        int res;
        cin >> res;
        return res;
    };
    int ans=0,add=0,prev=n;
    for(int i=0;i<30;i++){
        int res=ask((1<<i)+add);
        ans+=(1<<i);
        if(res>=prev){
            add=(1<<i);
            ans+=add;
            res--;
        }else{
            add=0;
        }
        prev=res;
        if(res==0)break;
    }
    cout << "! " << ans << endl;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}