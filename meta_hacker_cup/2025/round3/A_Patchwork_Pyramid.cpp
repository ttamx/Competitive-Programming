#include<bits/stdc++.h>

using namespace std;

using ll = long long;

void runcase(){
    int n,k;
    cin >> n >> k;
    if(k==1){
        cout << n << "\n";
        for(int i=1;i<=n;i++){
            for(int j=1;j<=i;j++){
                cout << char('a'+(i+j)%2);
            }
            cout << "\n";
        }
        return;
    }
    if(k==2){
        int ans=0;
        for(int i=1;i<=n;i++){
            ans+=(i+1)/2;
        }
        cout << ans << "\n";
        for(int i=1;i<=n;i++){
            for(int j=1;j<=i;j++){
                cout << char('a'+(i+(j-1)/2)%2);
            }
            cout << "\n";
        }
        return;
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cout << fixed << setprecision(15);
    int t(1);
    cin >> t;
    for(int i=1;i<=t;i++){
        cout << "Case #" << i << ": ";
        runcase();
    }
}