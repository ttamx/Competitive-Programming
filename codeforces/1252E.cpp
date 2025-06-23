#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,lo,hi,k;
    cin >> n >> lo >> hi >> k;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    vector<int> l(n),r(n);
    l[n-1]=lo,r[n-1]=hi;
    for(int i=n-2;i>=0;i--){
        if(a[i]<a[i+1]){
            l[i]=max(lo,l[i+1]-k);
            r[i]=min(hi,r[i+1]-1);
        }else if(a[i]>a[i+1]){
            l[i]=max(lo,l[i+1]+1);
            r[i]=min(hi,r[i+1]+k);
        }else{
            l[i]=l[i+1];
            r[i]=r[i+1];
        }
        if(l[i]>r[i]){
            cout << -1 << "\n";
            exit(0);
        }
    }
    vector<int> b(n);
    b[0]=l[0];
    for(int i=1;i<n;i++){
        if(a[i-1]<a[i]){
            l[i]=max(l[i],b[i-1]+1);
            r[i]=min(hi,b[i-1]+k);
        }else if(a[i-1]>a[i]){
            l[i]=max(l[i],b[i-1]-k);
            r[i]=min(hi,b[i-1]-1);
        }else{
            l[i]=r[i]=b[i-1];
        }
        assert(l[i]<=r[i]);
        b[i]=l[i];
    }
    for(auto x:b){
        cout << x << " ";
    }
    cout << "\n";
}