#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,m,k;
    cin >> n >> m >> k;
    multiset<int> a,b;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        a.emplace(x);
    }
    for(int i=0;i<m;i++){
        int x;
        cin >> x;
        b.emplace(x);
    }
    for(int i=1;i<=min(k,1000);i++){
        if(i%2){
            if(*b.rbegin()-*a.begin()>0){
                int x=*b.rbegin();
                int y=*a.begin();
                b.erase(prev(b.end()));
                a.erase(a.begin());
                a.emplace(x);
                b.emplace(y);
            }
        }else{
            if(*a.rbegin()-*b.begin()>0){
                int x=*a.rbegin();
                int y=*b.begin();
                a.erase(prev(a.end()));
                b.erase(b.begin());
                b.emplace(x);
                a.emplace(y);
            }
        }
    }
    if(k>1000&&k%2==1){
        if(*b.rbegin()-*a.begin()>0){
            int x=*b.rbegin();
            int y=*a.begin();
            b.erase(prev(b.end()));
            a.erase(a.begin());
            a.emplace(x);
            b.emplace(y);
        }
    }
    long long sum=0;
    for(auto x:a)sum+=x;
    cout << sum << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}