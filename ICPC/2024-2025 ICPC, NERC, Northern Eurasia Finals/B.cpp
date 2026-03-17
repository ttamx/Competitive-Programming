#include<bits/stdc++.h>

using namespace std;

using ll = long long;

vector<int> ans;

void init(int n){
    while(ans.size()<=n){
        ans.emplace_back(0);
    }
}

int enc(int word,int bit){
    return word<<4|bit;
}

void set_bad(int i){
    // cerr << i << "\n";
    init(i+2);
    ans[i]=enc(0,0);
    ans[i+1]=enc((1<<12)-1,0);
    ans[i+2]=1<<12;
}

int val;

void build(int word,int bit,int pos=3){
    // cerr << word << "\n";
    init(word+2);
    if(bit==16){
        ans[word]=enc(0,4);
        ans[word+1]=enc((1<<12)-1,0);
        ans[word+2]=1<<12;
        return;
    }
    int b=val>>bit&1;
    ans[word]=enc((1<<12)-1,bit);
    ans[word+1]=enc(word+2,2);
    ans[word+2]=pos;
    set_bad(pos+(4-b*4));
    build(pos+b*4,bit+1,pos+8);
    
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> val;
    build(0,0);
    for(auto x:ans){
        for(int i=3;i>=0;i--){
            int v=(x>>(i*4))&15;
            if(v<10){
                cout << v;
            }else{
                cout << char(v-10+'a');
            }
        }
        cout << " ";
    }
}