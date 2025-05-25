#include<bits/stdc++.h>

using namespace std;

const int INF=INT_MAX/2;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    {
        bool flag=true;
        int mn=INF,mx=-INF;
        for(int i=0;i<n;i++){
            if(mn<a[i]&&a[i]<mx){
                flag=false;
                break;
            }
            mn=min(mn,a[i]);
            mx=max(mx,a[i]);
        }
        if(flag){
            cout << "YES\n";
            return;
        }
    }
    for(int st=0;st<n;st++){
        bool flag=true;
        int mn=INF,mx=-INF;
        for(int i=0;i<st;i++){
            if(mn<a[i]&&a[i]<mx){
                flag=false;
                break;
            }
            mn=min(mn,a[i]);
            mx=max(mx,a[i]);
        }
        if(!flag||(mn<a[st]&&a[st]<=mx)){
            continue;
        }
        for(int i=st+1;i<n;i++){
            if(mn<a[i]&&a[i]<mx){
                flag=false;
                break;
            }
            mn=min(mn,a[i]);
            mx=max(mx,a[i]);
        }
        if(flag){
            cout << "YES\n";
            return;
        }
    }
    cout << "NO\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}