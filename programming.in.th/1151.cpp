#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> v;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        auto it=lower_bound(v.begin(),v.end(),x);
        if(it==v.end())v.push_back(x);
        else *it=x;
    }
    cout << v.size();
}