#include<bits/stdc++.h>

using namespace std;

int t;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> t;
    while(t--){
        int n;
        int a[55];
        string s;
        cin >> n;
        for(int i=n;i>0;--i){
            char c;
            cin >> c;
            a[i]=c-'0';
        }
        for(int i=1;i<=n;++i){
            if(a[i]==0){
                s=char('a'+(a[i+2]*10)+a[i+1]-1)+s;
                i+=2;
            }else{
                s=char('a'+a[i]-1)+s;
            }
        }
        cout << s << endl;
    }
}

