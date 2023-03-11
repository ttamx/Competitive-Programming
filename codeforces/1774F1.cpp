#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;

struct node{
    int val;
    vector<int> adj;
    vector<int> v;
}t[N];

vector<int> merge(vector<int> a,vector<int> b){
    vector<int> c;
    int i=0,j=0;
    while(i<a.size()&&j<b.size()){
        while(i<a.size()&&a[i]<b[j])c.push_back(a[i++]);
        if(i>=a.size())break;
        while(j<b.size()&&a[i]>b[j])c.push_back(b[j++]);
    }
    while(i<a.size())c.push_back(a[i++]);
    while(j<b.size())c.push_back(b[j++]);
    return c;
}

int n,idx;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    int prev=-1;
    for(int i=0;i<n;i++){
        int o;
        cin >> o;
        if(o<3){
            if(prev==o){
                sort(t[idx].v.begin(),t[idx].v.end());
                idx++;
                t[idx].adj.push_back(idx-1);
            }
            prev=o;
            int x;
            cin >> x;
            if(o==1){
                t[idx].v.push_back(x);
            }else{
                t[idx].val+=x;
            }
        }else{
            idx++;
            t[idx].adj.push_back(idx-1);
        }
    }
}