#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<int> a(n+1);
    for(int i=0;i<m;i++){
        int l,r;
        cin >> l >> r;
        a[l-1]++,a[r]--;
    }
    for(int i=1;i<=n;i++)a[i]+=a[i-1];
    cout << *min_element(a.begin(),a.end()-1) << "\n";
}