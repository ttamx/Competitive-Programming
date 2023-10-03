#include <bits/stdc++.h>
#include "messy.h"

using namespace std;

vector<int> restore_permutation(int n, int w, int r){
    function<void(int,int)> sol1=[&](int l,int r){
        if(l==r)return;
        int m=(l+r)/2;
        string str(n,'1');
        for(int i=l;i<=r;i++)str[i]='0';
        for(int i=l;i<=m;i++){
            string res=str;
            res[i]='1';
            add_element(res);
        }
        sol1(l,m);
        sol1(m+1,r);
    };
    sol1(0,n-1);
    compile_set();
    vector<int> p(n);
    function<void(int,int,vector<int>)> sol2=[&](int l,int r,vector<int> b){
        if(l==r)return;
        int m=(l+r)/2;
        string str(n,'0');
        vector<int> vl,vr;
        for(auto x:b)str[x]='1';
        for(int i=0;i<n;i++){
            if(str[i]=='1')continue;
            string res=str;
            res[i]='1';
            if(check_element(res))vl.emplace_back(i);
            else vr.emplace_back(i);
        }
        if(vl.size()==1)p[vl[0]]=l;
        if(vr.size()==1)p[vr[0]]=r;
        for(auto x:b)vl.emplace_back(x);
        for(auto x:b)vr.emplace_back(x);
        sol2(l,m,vr);
        sol2(m+1,r,vl);
    };
    sol2(0,n-1,vector<int>(0));
    return p;
}