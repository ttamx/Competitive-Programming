#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int n,k;
string s;
ll suma,sumb;
map<ll,int> pos;
int ans=0;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k >> s;
    pos[0]=0;
    for(int i=1;i<=n;i++){
        if(s[i-1]=='O')suma++;
        else sumb++;
        ll val=k*sumb-suma;
        if(pos.find(val)!=pos.end()){
            ans=max(ans,i-pos[val]);
        }else{
            pos[val]=i;
        }
    }
    cout << ans;
}