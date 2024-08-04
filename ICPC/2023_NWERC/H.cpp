#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    if(n==1){
        int x;
        cin >> x;
        cout << x;
        exit(0);
    }
    using P = pair<int,string>;
    priority_queue<P,vector<P>,greater<P>> pq;
    int one=0,two=0;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        if(x==1)one++;
        else if(x==2)two++;
        else pq.push(P(x,to_string(x)));
    }
    int three=min(one,two);
    one-=three;
    two-=three;
    for(int i=0;i<three;i++){
        pq.push(P(3,"1+2"));
    }
    while(one>4){
        pq.push(P(3,"1+1+1"));
        one-=3;
    }
    for(int i=0;i<two;i++)pq.push(P(2,"2"));
    if(one>1){
        string s="1";
        for(int i=1;i<one;i++)s+="+1";
        pq.push(P(one,s));
    }else if(one==1){
        auto [x,s]=pq.top();
        pq.pop();
        x++;
        s+="+1";
        pq.push(P(x,s));
    }
    bool first=true;
    while(!pq.empty()){
        if(first){
            first=false;
        }else{
            cout << "*";
        }
        cout << "(" << pq.top().second << ")";
        pq.pop();
    }
}