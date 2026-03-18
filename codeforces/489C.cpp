#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,s;
    cin >> n >> s;
    if(s==0){
        if(n==1){
            cout << 0 << " " << 0 << "\n";
        }else{
            cout << -1 << " " << -1 << "\n";
        }
        exit(0);
    }
    if(n*9<s){
        cout << -1 << " " << -1 << "\n";
        exit(0); 
    }
    {
        int cur=s;
        int v=max(1,s-9*(n-1));
        cout << v;
        string s="";
        cur-=v;
        for(int i=0;i<n-1;i++){
            v=min(9,cur);
            s.push_back('0'+v);
            cur-=v;
        }
        assert(cur==0);
        reverse(s.begin(),s.end());
        cout << s << " ";
    }
    {
        int cur=s;
        for(int i=0;i<n;i++){
            int v=min(9,cur);
            cout << v;
            cur-=v;
        }
        assert(cur==0);
        cout << "\n";
    }
}