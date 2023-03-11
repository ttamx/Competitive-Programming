#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<pair<int,int>> v(n);
    for(auto &[x,y]:v)cin >> x,y=x;
    int ans=0;
    for(int i=n;i>1;i/=2){
        vector<pair<int,int>> tmp;
        for(int j=0;j<i;j+=2){
            auto [a,b]=v[j];
            auto [c,d]=v[j+1];
            if((a<d&&b>c)||(c<b&&d>b)){
                cout << -1 << '\n';
                return;
            }
            if(a>c)swap(a,c),swap(b,d),++ans;
            tmp.emplace_back(a,d);
        }
        v=tmp;
    }
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();
}