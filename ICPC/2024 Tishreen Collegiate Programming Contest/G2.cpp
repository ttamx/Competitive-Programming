#include<bits/stdc++.h>

using namespace std;

const int N=1e6+5;

int lp[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    for(int i=2;i<N;i++){
        if(lp[i]){
            continue;
        }
        lp[i]=i;
        for(int j=i*2;j<N;j+=i){
            if(lp[j]==0){
                lp[j]=i;
            }
        }
    }
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        if(n%2==0){
            cout << 2 << "\n";
            continue;
        }
        int p=0,cnt=0;
        for(int x=n;x>1;x/=lp[x]){
            cnt++;
            if(p){
                if(p!=lp[x]){
                    p=1;
                    break;
                }
            }else{
                p=lp[x];
            }
        }
        if(p==1){
            cout << 2 << "\n";
        }else{
            cout << 4 << "\n";
        }
    }
}