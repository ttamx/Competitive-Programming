#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    string s;
    cin >> s;
    int ans=0;
    for(int i=0;i<n;i++){
        if(s[i]!='a')continue;
        int j=i;
        while(j+1<n&&s[j+1]=='a')j++;
        if(i<j){
            ans+=j-i+1;
        }
        i=j;
    }
    cout << ans << "\n";
}