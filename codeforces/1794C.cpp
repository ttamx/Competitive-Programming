#include<bits/stdc++.h>
 
using namespace std;
 
typedef double db;
 
void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i=0;i<n;i++){
        cin >> a[i];
        a[i]-=(n-i);
    }
    for(int i=0;i<n;i++){
        int idx=lower_bound(a.begin(),a.end(),i-(n-1))-a.begin();
        cout << i-idx+1 << ' ';
    }
    cout << '\n';
}
 
int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}