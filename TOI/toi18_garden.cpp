#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,q;
    cin >> n >> q;
    vector<int> a(n),l(n),r(n);
    for(auto &x:a)cin >> x;
    for(int t=0;t<2;t++){
        vector<int> lis;
        for(int i=0;i<n;i++){
            auto it=lower_bound(lis.begin(),lis.end(),a[i]);
            l[i]=it-lis.begin();
            if(it==lis.end())lis.emplace_back(a[i]);
            else *it=a[i];
        }
        reverse(a.begin(),a.end());
        swap(l,r);
    }
    reverse(r.begin(),r.end());
    while(q--){
        int x;
        cin >> x;
        cout << min(l[x],r[x]) << '\n';
    }
}