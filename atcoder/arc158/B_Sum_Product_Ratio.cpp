#include<bits/stdc++.h>

using namespace std;

typedef double db;

void runcase(){
    int n;
    cin >> n;
    vector<db> pos,neg;
    vector<db> a(n);
    for(auto &x:a){
        cin >> x;
        if(x>0)pos.emplace_back(x);
        else neg.emplace_back(x);
    }
    sort(pos.begin(),pos.end());
    sort(neg.rbegin(),neg.rend());
    db mx=(a[0]+a[1]+a[2])/(a[0]*a[1]*a[2]);
    db mn=mx;
    vector<db> val;
    for(int i=0;i<min((int)pos.size(),3);i++)val.emplace_back(pos[i]);
    for(int i=0;i<min((int)neg.size(),3);i++)val.emplace_back(neg[i]);
    for(int i=0;i<val.size();i++)for(int j=0;j<i;j++)for(int k=0;k<j;k++){
        db res=(val[i]+val[j]+val[k])/(val[i]*val[j]*val[k]);
        mn=min(mn,res),mx=max(mx,res);
    }
    val.clear();
    for(int i=0;i<min((int)pos.size(),3);i++)val.emplace_back(pos[pos.size()-i-1]);
    for(int i=0;i<min((int)neg.size(),3);i++)val.emplace_back(neg[neg.size()-i-1]);
    for(int i=0;i<val.size();i++)for(int j=0;j<i;j++)for(int k=0;k<j;k++){
        db res=(val[i]+val[j]+val[k])/(val[i]*val[j]*val[k]);
        mn=min(mn,res),mx=max(mx,res);
    }
    val.clear();
    for(int i=0;i<min((int)pos.size(),3);i++)val.emplace_back(pos[pos.size()-i-1]);
    for(int i=0;i<min((int)neg.size(),3);i++)val.emplace_back(neg[i]);
    for(int i=0;i<val.size();i++)for(int j=0;j<i;j++)for(int k=0;k<j;k++){
        db res=(val[i]+val[j]+val[k])/(val[i]*val[j]*val[k]);
        mn=min(mn,res),mx=max(mx,res);
    }
    val.clear();
    for(int i=0;i<min((int)pos.size(),3);i++)val.emplace_back(pos[i]);
    for(int i=0;i<min((int)neg.size(),3);i++)val.emplace_back(neg[neg.size()-i-1]);
    for(int i=0;i<val.size();i++)for(int j=0;j<i;j++)for(int k=0;k<j;k++){
        db res=(val[i]+val[j]+val[k])/(val[i]*val[j]*val[k]);
        mn=min(mn,res),mx=max(mx,res);
    }
    cout << mn << '\n' << mx;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}