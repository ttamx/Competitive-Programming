#include <bits/stdc++.h>
#include "messy.h"

using namespace std;

vector<int> restore_permutation(int n, int w, int r){
    for(int i=0;i<n;i++){
        string res="";
        for(int j=0;j<n;j++)res.push_back('0'+(j<=i));
        add_element(res);
    }
    compile_set();
    vector<int> ans(n);
    string str(n,'0');
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(str[j]=='1')continue;
            string res=str;
            res[j]='1';
            if(check_element(res)){
                ans[j]=i;
                str[j]='1';
                break;
            }
        }
    }
    return ans;
}