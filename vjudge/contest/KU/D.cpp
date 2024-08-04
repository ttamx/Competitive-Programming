#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,h;
    cin >> n >> h;
    vector<int> a(h);
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        if(i&1){
            a[h-x]++;
        }else{
            a[0]++,a[x]--;
        }
    }
    for(int i=0;i<h-1;i++)a[i+1]+=a[i];
    int mn=*min_element(a.begin(),a.end());
    int cnt=0;
    for(auto x:a)if(x==mn)cnt++;
    cout << mn << " " << cnt;
}