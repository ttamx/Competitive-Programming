#include<bits/stdc++.h>

using namespace std;

void runcase(){
    string s;
    cin >> s;
    int n=s.size();
    int sum=0;
    for(auto x:s){
        sum=(sum+x-'0')%3;
    }
    if(s==string(n,'1')||s==string(n,'2')){
        if(n%2==1)s.pop_back();
        cout << s << " " << s.substr(0,n/2) << "\n";
        return;
    }
    if(sum!=0){
        string t="";
        for(int i=0;i<s.size();i++){
            if(s[i]-'0'==sum){
                t=s.substr(0,i)+s.substr(i+1,s.size()-i-1);
                break;
            }
        }
        assert(t!="");
        s=move(t);
    }
    string ans="";
    int val=0;
    for(auto x:s){
        val=val*10+x-'0';
        int cur=val/3;
        if(cur>0||!ans.empty()){
            ans.push_back(cur+'0');
        }
        val%=3;
    }
    assert(val==0);
    cout << s << " 3\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();
}