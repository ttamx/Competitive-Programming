#include<bits/stdc++.h>

using namespace std;

const int N=1e6+5;

int n;
int h[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++)cin >> h[i];
    vector<int> a;
    a.push_back(0);
    int lis=0;
    for(int i=1;i<=n;i++){
        int idx=upper_bound(a.begin(),a.end(),h[i])-a.begin();
        lis=max(lis,idx);
        if(idx<a.size()){
            a[idx]=h[i];
        }else{
            a.push_back(h[i]);
        }
    }
    cout << n-lis;
}