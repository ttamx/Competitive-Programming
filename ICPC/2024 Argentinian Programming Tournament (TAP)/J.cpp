#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,v;
    cin >> n >> v;
    vector<int> a,b,c;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        if(x*2==v){
            a.emplace_back(x);
        }else if(x*2<v){
            b.emplace_back(x);
        }else{
            c.emplace_back(x);
        }
    }
    sort(b.begin(),b.end());
    sort(c.begin(),c.end());
    vector<int> ans,d;
    if(b.empty())d=c;
    else if(c.empty())d=b;
    else{
        if(b[0]+c[0]<v){
            reverse(b.begin(),b.end());
            d=b;
            d.insert(d.end(),c.begin(),c.end());
        }else if(b.back()+c.back()>v){
            reverse(c.begin(),c.end());
            d=b;
            d.insert(d.end(),c.begin(),c.end());
        }else if(a.empty()||a.size()>b.size()+c.size()+1){
            cout << "*";
            exit(0);
        }else{
            a.pop_back();
            for(auto x:b){
                if(!a.empty()){
                    a.pop_back();
                    ans.emplace_back(v/2);
                }
                ans.emplace_back(x);
            }
            ans.emplace_back(v/2);
            for(auto x:c){
                ans.emplace_back(x);
                if(!a.empty()){
                    a.pop_back();
                    ans.emplace_back(v/2);
                }
            }
            for(auto x:ans)cout << x << " ";
            exit(0);
        }
    }
    for(auto x:d){
        if(!a.empty()){
            a.pop_back();
            ans.emplace_back(v/2);
        }
        ans.emplace_back(x);
    }
    if(!a.empty()){
        a.pop_back();
        ans.emplace_back(v/2);
    }
    if(!a.empty()){
        cout << "*";
    }else{
        for(auto x:ans)cout << x << " ";
    }
}