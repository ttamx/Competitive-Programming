#include<bits/stdc++.h>

using namespace std;

bool can(string s,int x,int y){
    if(x>=y)return false;
    string a=s.substr(0,x);
    string b=s.substr(x,y-x);
    string c=s.substr(y,s.size()-y);
    if((a<=b&&c<=b)||(a>=b&&c>=b)){
        cout << a << ' ' << b << ' ' << c << '\n';
        return true;
    }
    return false;
}

void runcase(){
    string s;
    cin >> s;
    int n=s.size();
    int la=1,ra=n-1,lb=1,rb=n-1;
    while(la<n&&s[la]!='a')la++;
    while(lb<n&&s[lb]!='b')lb++;
    while(ra>0&&s[ra]!='a')ra--;
    while(rb>0&&s[rb]!='b')rb--;
    if(s[0]=='a'){
        if(lb<n-1)cout << s.substr(0,lb) << " " << s.substr(lb,n-lb-1) << " " << s[n-1] <<"\n";
        else cout << "a a " << s.substr(2,n-2) << "\n";
    }else{
        if(la<n-1)cout << s.substr(0,la) << " a " << s.substr(la+1,n-la-1) << '\n';
        else cout << "b b " << s.substr(2,n-2) << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}