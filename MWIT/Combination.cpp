#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,r,k;
    cin >> n >> r >> k;
    k--;
    vector<int> a(r);
    iota(a.begin(),a.end(),1);
    while(k--){
        int idx=r-1;
        a[idx]++;
        int cnt=0;
        while(idx>=0){
            if(a[idx]>n-cnt){
                cnt++;
                a[--idx]++;
            }else{
                break;
            }
        }
        if(idx==-1){
            idx=0;
            a[0]=1;
        }
        while(++idx<r){
            a[idx]=a[idx-1]+1;
        }
    }
    for(auto x:a)cout << x << ' ';
}