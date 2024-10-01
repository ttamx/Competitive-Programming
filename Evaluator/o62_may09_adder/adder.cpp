#include<bits/stdc++.h>

using namespace std;

enum Gate{AND,OR,NOT};

vector<tuple<Gate,int,int>> gate;

int new_gate(Gate g,int x,int y=-1){
    gate.emplace_back(g,x,y);
    return gate.size();
}

int build(Gate g,vector<int> a){
    function<int(int,int,int)> rec=[&](int l,int r,int n){
        if(l+n-1>=r)return rec(l,r,n/2);
        if(l==r)return a[l];
        return new_gate(g,rec(l,l+n-1,n/2),rec(l+n,r,n/2));
    };
    return rec(0,a.size()-1,128);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<int> and_gate(n+1),or_gate(n+1),carry(n+2);
    for(int i=1;i<=n;i++){
        and_gate[i]=new_gate(AND,-i,-i-n);
    }
    for(int i=1;i<=n;i++){
        or_gate[i]=new_gate(OR,-i,-i-n);
    }
    for(int i=1;i<=n+1;i++){
        vector<int> cur,range;
        for(int j=i-1;j>=1;j--){
            range.emplace_back(and_gate[j]);
            cur.emplace_back(build(AND,range));
            range.back()=or_gate[j];
        }
        range.emplace_back(0);
        cur.emplace_back(build(AND,range));
        carry[i]=build(OR,cur);
    }
    vector<int> ans(n+2);
    for(int i=1;i<=n;i++){
        int a=new_gate(AND,and_gate[i],carry[i]);
        int b=new_gate(AND,carry[i],new_gate(NOT,or_gate[i]));
        int t=new_gate(AND,or_gate[i],new_gate(NOT,and_gate[i]));
        int c=new_gate(AND,new_gate(NOT,carry[i]),t);
        ans[i]=build(OR,{a,b,c});
    }
    ans[n+1]=carry[n+1];
    cout << gate.size() << "\n";
    for(int i=1;i<=n+1;i++){
        cout << ans[i] << " \n"[i==n+1];
    }
    for(auto [g,x,y]:gate){
        if(g==NOT){
            cout << "NOT " << x << "\n";
        }else{
            cout << (g==AND?"AND":"OR") << " " << x << " " << y << "\n";
        }
    }
}