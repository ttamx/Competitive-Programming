#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<pair<int,int>> a(m);
    for(auto &[l,r]:a){
        cin >> l >> r;
        l--,r--;
        if(l>r)swap(l,r);
    }
    sort(a.begin(),a.end());
    for(int i=1;i<n;i++){
        if(n%i==0){
            auto b=a;
            for(auto &[l,r]:b){
                l=(l+i)%n;
                r=(r+i)%n;
                if(l>r)swap(l,r);
            }
            sort(b.begin(),b.end());
            if(a==b){
                cout << "Yes\n";
                exit(0);
            }
        }
    }
    cout << "No\n";
}