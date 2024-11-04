#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n),b(n);
    for(auto &x:a){
        cin >> x;
    }
    for(auto &x:b){
        cin >> x;
    }
    function<void(int,int,int,int)> dnc=[&](int l1,int r1,int l2,int r2){
        if(l1>r1)return;
        if(l1==r1){
            cout << a[l1] << "\n";
            return;
        }
        int cur=a[l1];
        l1++,r2--;
        int mid=r2;
        while(b[mid]!=a[l1]){
            mid--;
        }
        dnc(l1,l1+mid-l2,l2,mid);
        cout << cur << "\n";
        dnc(l1+mid-l2+1,r1,mid+1,r2);
    };
    dnc(0,n-1,0,n-1);
}