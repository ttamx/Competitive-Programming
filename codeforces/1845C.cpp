#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

void runcase(){
    string s;
    cin >> s;
    int n=s.size();
    s=" "+s;
    int m;
    cin >> m;
    string l,r;
    cin >> l >> r;
    l=" "+l;
    r=" "+r;
    int idx=1;
    for(int i=1;i<=m;i++){
        int all=r[i]-l[i]+1;
        vector<bool> b(10,true);
        while(idx<=n&&all>0){
            int x=s[idx];
            if(b[x-'0']){
                b[x-'0']=false;
                if(l[i]<=x&&x<=r[i])all--;
            }
            idx++;
        }
        if(idx>n&&all>0)return void(cout << "YES\n");
    }
    cout << "NO\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}