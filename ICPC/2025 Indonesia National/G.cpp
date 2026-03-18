#include<bits/stdc++.h>

using namespace std;

const int N=1<<18;

int a[N],mn[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,k;
    cin >> n >> k;
    multiset<int> ms;
    for(int i=0;i<N;i++){
        int cur=0;
        for(int j=29;j>=0;j--){
            if(i>>j&1){
                if(cur+(1<<j)<=k){
                    cur+=1<<j;
                }
            }
        }
        mn[i]=i-cur;
        ms.emplace(mn[i]);
    }
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        if(x<N){
            a[x]^=1;
            if(a[x]){
                ms.erase(ms.find(mn[x]));
            }else{
                ms.emplace(mn[x]);
            }
        }
        cout << *ms.begin() << "\n";
    }
}