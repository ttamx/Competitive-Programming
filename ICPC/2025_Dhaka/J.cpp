#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        string s;
        cin >> s;
        int ans=0;
        for(int i=0;i<s.size();i++){
            if(s[i]=='\\'){
                if(i+1==s.size()){
                    ans=-1;
                    break;
                }
                if(s[i+1]=='0'){
                    break;
                }
                i++;
            }
            ans++;
        }
        if(ans==-1){
            cout << "INVALID\n";
        }else{
            cout << ans << "\n";
        }
    }
}