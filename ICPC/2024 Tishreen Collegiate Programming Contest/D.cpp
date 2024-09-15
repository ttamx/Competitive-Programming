#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    vector<int> b(n,-1);
    for(int i=0;i<n-1;i++){
        if(a[i]!=a[i+1]){
            b[i]=31-__builtin_clz(a[i]^a[i+1]);
        }
    }
    vector<int> cnt(30);
    int mask=0;
    long long ans=1;
    for(int l=0,r=1;r<n;r++){
        if(b[r-1]!=-1){
            int s=(a[r]<a[r-1]);
            int x=b[r-1];
            if((mask>>x&1)!=s){
                while(cnt[x]>0){
                    if(b[l]!=-1){
                        cnt[b[l]]--;
                    }
                    l++;
                }
                mask^=(1<<x);
            }
            if(l<r){
                cnt[b[r-1]]++;
            }
        }
        ans+=r-l+1;
    }
    cout << ans << "\n";
}