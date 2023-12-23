#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int n;
int x[N],h[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++)cin >> x[i] >> h[i];
    int ans=0,idx=0;
    char dir='L';
    for(int i=n;i>=1;i--){
        int res=1;
        int mn=x[i]-h[i];
        while(mn<)
        if(res>ans){
            ans=res;
            idx=i;
        }
    }
    for(int i=1;i<=n;i++){
        int res=1;
        if(res>ans){
            ans=res;
            idx=i;
            dir='R';
        }else if(res==ans){
            if(i<idx){
                idx=i;
                dir='R';
            }
        }
    }
    cout << idx << ' ' << dir;
}