#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    auto ask=[&](int i,int j){
        cout << "? " << i << " " << j << endl;
        int res;
        cin >> res;
        return res;
    };
    vector<int> a(n),b(n);
    for(int i=0;i<n;i++)a[i]=ask(i,0);
    for(int i=0;i<n;i++)b[i]=ask(0,i);
    int cnt=0;
    vector<int> ans;
    for(int x=0;x<n;x++){
        int y=b[0]^x;
        auto c=a;
        auto d=b;
        bool flag=true;
        for(auto &v:d){
            v^=x;
            if(v>=n)flag=false;
        }
        for(auto &v:c){
            v^=y;
            if(v>=n)flag=false;
        }
        if(!flag)continue;
        for(int i=0;i<n;i++)if(d[c[i]]!=i)flag=false;
        if(flag){
            cnt++;
            ans=c;
        }
    }
    cout << "!\n";
    cout << cnt << "\n";
    for(auto x:ans)cout << x << " ";
    cout << endl;
}