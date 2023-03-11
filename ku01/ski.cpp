#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int l,m,n;
    cin >> l >> m >> n;
    while(n--){
        int pos=0,ans=1;
        for(int i=0;i<m;i++){
            int x;
            cin >> x;
            if(x)pos++;
            else pos--;
            if(abs(pos)>l)ans=0;
        }
        cout << ans << '\n';
    }
}