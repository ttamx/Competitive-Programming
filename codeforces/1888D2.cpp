#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<int> a(n),b(n);
    for(int i=1;i<n;i++)cin >> a[i];
    for(int i=0;i<n;i++)cin >> b[i];
    sort(b.begin(),b.end());
    auto calc=[&](int val){
        auto c=a;
        c[0]=val;
        sort(c.begin(),c.end());
        auto check=[&](int x){
            for(int i=0;i<n-x;i++)if(c[i]>=b[i+x])return false;
            return true;
        };
        int l=0,r=n;
        while(l<r){
            int m=(l+r)/2;
            if(check(m))r=m;
            else l=m+1;
        }
        return l;
    };
    long long ans=calc(1);
    int l=1,r=m+1;
    while(l<r){
        int m=(l+r)/2;
        if(calc(m)>ans)r=m;
        else l=m+1;
    }
    ans*=m;
    ans+=m-l+1;
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}