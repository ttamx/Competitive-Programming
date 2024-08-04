#include<bits/stdc++.h>
#include<bits/extc++.h>

using namespace std;
using namespace __gnu_pbds;

template<class T>
using ordered_set=tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;

int n,q;
string s;
int cur_val=0;

struct Range:ordered_set<int>{
    bool eval(int x){
        return order_of_key(x+1)&1;
    }
    void add(int x){
        if(!insert(x).second)erase(x);
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    cin >> s;
    cur_val=0;
    Range r;
    for(auto c:s){
        if(isdigit(c)){
            cur_val=cur_val*10+c-'0';
        }else if(c=='['){
            cur_val=0;
        }else if(c==']'){
            r.add(cur_val);
        }else if(c=='('){
        }else if(c==')'){
        }else if(c=='!'){
            r.add(1);
        }else if(c=='&'){
        }else if(c=='^'){
        }else if(c=='|'){
        }
    }
    while(q--){
        int x;
        cin >> x;
        cout << (r.eval(x)?"True":"False") << "\n";
    }
}