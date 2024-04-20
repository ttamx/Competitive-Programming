#include<bits/stdc++.h>
 
using namespace std;
 
using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n),b(n);
    for(auto &x:a)cin >> x;
    for(auto &x:b)cin >> x;
    vector<int> c;
    for(int i=0;i<n;i++)if(b[i]>=a[i])c.emplace_back(b[i]-a[i]);
    reverse(c.begin(),c.end());
    vector<int> lis;
    for(auto x:c){
        auto it=upper_bound(lis.begin(),lis.end(),x);
        if(it==lis.end())lis.emplace_back(x);
        else *it=x;
    }
    cout << lis.size();
}