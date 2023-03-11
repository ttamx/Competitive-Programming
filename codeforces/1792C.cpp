#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

void runcase(){
    int n;
    cin >> n;
    vector<int> p(n+1);
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        p[x]=i;
    }
    int l=n/2,r=(n+1)/2+1;
    int pl=p[l+1],pr=p[r-1];
    int ans=n/2;
    while(0<l&&r<=n&&p[l]<p[r]&&p[l]<=pl&&p[r]>=pr){
        ans--;
        pl=p[l--];
        pr=p[r++];
    }
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}