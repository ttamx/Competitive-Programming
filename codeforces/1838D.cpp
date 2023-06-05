#include<bits/stdc++.h>

using namespace std;

const int K=1<<19;

int n,q;
string s;
multiset<int> ml,mr;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    cin >> s;
    s=" "+s;
    for(int i=1;i<n;i++)if(s[i]=='('&&s[i+1]=='(')ml.emplace(i);
    for(int i=2;i<=n;i++)if(s[i]==')'&&s[i-1]==')')mr.emplace(i);
    while(q--){
        int x;
        cin >> x;
        if(s[x]=='('&&s[x+1]=='(')ml.erase(ml.find(x));
        if(s[x-1]=='('&&s[x]=='(')ml.erase(ml.find(x-1));
        if(s[x]==')'&&s[x-1]==')')mr.erase(mr.find(x));
        if(s[x+1]==')'&&s[x]==')')mr.erase(mr.find(x+1));
        s[x]=(s[x]==')'?'(':')');
        if(s[x]=='('&&s[x+1]=='(')ml.emplace(x);
        if(s[x-1]=='('&&s[x]=='(')ml.emplace(x-1);
        if(s[x]==')'&&s[x-1]==')')mr.emplace(x);
        if(s[x+1]==')'&&s[x]==')')mr.emplace(x+1);
        if(n%2!=0||s[1]!='('||s[n]!=')'){
            cout << "NO\n";
            continue;
        }
        if(ml.empty()&&mr.empty()){
            cout << "YES\n";
            continue;
        }
        if(ml.empty()||mr.empty()){
            cout << "NO\n";
            continue;
        }
        if(*mr.rbegin()>*ml.begin()&&(*mr.rbegin()-*ml.begin()+1)%2==0&&*ml.begin()<*mr.begin()&&*mr.rbegin()>*ml.rbegin()){
            cout << "YES\n";
            continue;
        }
        cout << "NO\n";
    }
}