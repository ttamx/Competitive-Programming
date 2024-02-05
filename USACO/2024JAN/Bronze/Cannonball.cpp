#include<bits/stdc++.h>

using namespace std;

const int INF=1e9;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,s;
    cin >> n >> s;
    s--;
    vector<int> a(n),b(n),c(n);
    for(int i=0;i<n;i++)cin >> a[i] >> b[i];
    int d=1,k=1;
    int ans=0;
    while(0<=s&&s<n){
        if(k*d==c[s])break;
        c[s]=k*d;
        if(a[s]){
            if(k>=b[s]){
                ans++;
                b[s]=INF;
            }
        }else{
            d=-d;
            k+=b[s];
        }
        s+=d*k;
    }
    cout << ans << "\n";
}