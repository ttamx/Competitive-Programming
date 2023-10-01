#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    string s;
    cin >> n >> s;
    int a=0,b=0;
    for(int i=0;i<n;i++){
        if(s[i]=='(')a++;
        else b++;
    }
    if(a!=b)return void(cout << "-1\n");
    a=b=0;
    vector<int> ans(n);
    for(int i=0;i<n;i++){
        if(s[i]=='('){
            if(b>0){
                ans[i]=2;
                b--;
            }else{
                ans[i]=1;
                a++;
            }
        }else{
            if(a>0){
                ans[i]=1;
                a--;
            }else{
                ans[i]=2;
                b++;
            }
        }
    }
    bool ok=true;
    for(int i=1;i<n;i++)if(ans[i]!=ans[i-1])ok=false;
    if(ok){
        cout << 1 << "\n";
        for(int i=0;i<n;i++)cout << 1 << " \n"[i==n-1];
    }else{
        cout << 2 << "\n";
        for(int i=0;i<n;i++)cout << ans[i] << " \n"[i==n-1];
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}