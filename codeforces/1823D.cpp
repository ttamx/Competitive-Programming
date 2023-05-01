#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,k;
    cin >> n >> k;
    vector<int> a(k),c(k);
    for(auto &x:a)cin >> x;
    for(auto &x:c)cin >> x;
    int pa=0,pc=0,ps=0;
    string s="";
    char ch='a';
    string ed={"ux","yz"};
    string ans="";
    for(int i=0;i<k;i++){
        int da=a[i]-pa,dc=c[i]-pc;
        pa=a[i],pc=c[i];
        if(dc>da)return void(cout << "NO\n");
        if(da==1){
            if(dc==0){
                if(s.empty())return void(cout << "NO\n");
                ans=ans+s[0];
                ps=0;
            }else{
                ans=ans+ch;
                ch++;
                ps=0;
            }
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}