#include<bits/stdc++.h>

using namespace std;

mt19937 rng(time(0));

int rnd(int n){
    return rng()%n;
}

int rnd(int l,int r){
    return l+rnd(r-l+1);
}

int main(){
    int n=rnd(10,100);
    int q=1000;
    vector<int> h(n),a(n),b(n);
    for(int i=0;i<n;i++){
        h[i]=rnd(1,10);
    }
    for(int i=0;i<n;i++){
        tie(a[i],b[i])=minmax(rnd(1,n-1),rnd(1,n-1));
    }
    cout << n << "\n";
    for(int i=0;i<n;i++){
        cout << h[i] << " " << a[i] << " " << b[i] << "\n";
    }
    cout << q << "\n";
    for(int i=0;i<q;i++){
        auto [l,r]=minmax(rnd(1,n-1),rnd(1,n-1));
        cout << l << " " << r << "\n";
    }

}