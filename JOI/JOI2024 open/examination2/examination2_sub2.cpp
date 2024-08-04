#include<bits/stdc++.h>

using namespace std;

int n,q;
string s;
stack<pair<int,int>> st;

void eval(int x){
    bool val=st.top().second;
    st.pop();
    while(!st.empty()&&st.top().first<=x){
        int op=st.top().first;
        st.pop();
        if(op==3){
            val=!val;
        }else if(op==4){
            val&=st.top().second;
            st.pop();
        }else if(op==5){
            val^=st.top().second;
            st.pop();
        }else if(op==6){
            val|=st.top().second;
            st.pop();
        }else{
            assert(false);
        }
    }
    if(x==7)st.pop();
    st.emplace(0,val);
}

bool solve(int x){
    while(!st.empty())st.pop();
    for(auto c:s){
        if(isdigit(c)){
            st.emplace(0,c-'0');
        }else if(c=='['){
            st.emplace(1,0);
        }else if(c==']'){
            int val=0,dig=1;
            while(st.top().first!=1){
                val+=st.top().second*dig;
                dig*=10;
                st.pop();
            }
            st.pop();
            st.emplace(0,x>=val);
        }else if(c=='('){
            st.emplace(8,0);
        }else if(c==')'){
            eval(7);
        }else if(c=='!'){
            st.emplace(3,0);
        }else if(c=='&'){
            eval(4);
            st.emplace(4,0);
        }else if(c=='^'){
            eval(5);
            st.emplace(5,0);
        }else if(c=='|'){
            eval(6);
            st.emplace(6,0);
        }
    }
    eval(6);
    return st.top().second;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    cin >> s;
    while(q--){
        int x;
        cin >> x;
        cout << (solve(x)?"True":"False") << '\n';
    }
}