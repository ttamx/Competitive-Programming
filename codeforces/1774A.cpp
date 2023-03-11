#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    string s;
    cin >> n;
    cin >> s;
    int val=s[0]-'0';
    for(int i=1;i<n;i++){
        if(s[i]=='1'){
            if(val>0){
                cout << '-';
                val--;
            }else{
                cout << '+';
                val++;
            }
        }else{
            cout << '+';
        }
    }
    cout << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();
}