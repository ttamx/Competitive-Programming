#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    stack<string> st;
    int n;
    cin >> n;
    while(n--){
        string str,s;
        getline(cin >> ws,str);
        vector<string> v;
        auto ss=stringstream(str);
        while(getline(ss,s,' ')){
            v.push_back(s);
        }
        if(v[0]=="cd"&&v.size()==2){
            if(v[1]==".."){
                if(!st.empty())st.pop();
            }else if(v[1]!="."){
                st.push(v[1]);
            }
        }else if(v[0]=="pwd"&&v.size()==1){
            if(st.empty())cout << "root\n";
            else cout << st.top() << '\n';
        }else{
            cout << "ClitzBode is invaded!\n";
        }
    }
}