#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e6+5;

int n,k;
string s;
ll qsa[N],qsb[N];
map<ll,int> pos;
int ans;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k >> s;
    for(int i=1;i<=n;i++){
        qsa[i]=qsa[i-1]+(s[i-1]=='O');
        qsb[i]=qsb[i-1]+(s[i-1]=='R');
        if(pos.find(k*qsb[i-1]-qsa[i-1])==pos.end()){
            pos[k*qsb[i-1]-qsa[i-1]]=i-1;
        }
        if(pos.find(k*qsb[i]-qsa[i])!=pos.end()){
            ans=max(ans,i-pos[k*qsb[i]-qsa[i]]);
        }
    }
    cout << ans;
}