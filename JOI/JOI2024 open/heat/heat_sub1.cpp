#include<bits/stdc++.h>

using namespace std;

const int N=8005;
const int INF=INT_MAX/2;

int n,m;
int a[N];
int ans=0;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++)cin >> a[i];
    cin >> m;
    for(int i=1;i<=m;i++){
        int x;
        cin >> x;
        x++;
        if(a[x]>0)a[x]--;
        else if(a[x-1]>0){
            a[x-1]--;
        }else ans++;
    }
    cout << ans;
}