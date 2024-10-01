#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    auto solve=[&](vector<int> a){
        int n=a.size();
        assert(n%2==0);
        a[0]+=n/2;
        if(a[0]>n)a[0]-=n;
        vector<int> vals(a.begin()+1,a.end());
        sort(vals.begin(),vals.end());
        for(int i=1;i<n;i++){
            a[i]=lower_bound(vals.begin(),vals.end(),a[i])-vals.begin()+1;
            if(a[i]>=a[0])a[i]++;
        }
        return a;
    };
    if(n%2==0){
        a=solve(a);
    }else{
        a[0]+=n/2;
        vector<int> b(a.begin()+1,a.end());
        vector<int> vals(b);
        sort(vals.begin(),vals.end());
        for(auto &x:b)x=lower_bound(vals.begin(),vals.end(),x)-vals.begin()+1;
        b=solve(b);
        if(b[0]<=n/2)a[0]++;
        if(a[0]>n)a[0]-=n;
        for(int i=1;i<n;i++){
            a[i]=b[i-1];
            if(a[i]>=a[0])a[i]++;
        }
    }
    for(auto x:a){
        cout << x << " ";
    }
}