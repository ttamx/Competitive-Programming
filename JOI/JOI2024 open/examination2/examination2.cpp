#include<bits/stdc++.h>
#include<bits/extc++.h>

using namespace std;
using namespace __gnu_pbds;

template<class T>
using ordered_set=tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;

const int N=1e6+5;
const int LIM=1e9+5;

int n,q;
string s;

struct Range:ordered_set<int>{
    bool is_toggle;
    void toggle(){
        is_toggle^=true;
    }
    bool eval(int x){
        return order_of_key(x+1)&1;
    }
    void add(int x){
        if(!insert(x).second)erase(x);
    }
    void push(){
        if(is_toggle){
            add(1);
            is_toggle=false;
        }
    }
}ran[N];

stack<int> opr,st;
int cur_val,cur_id;

void eval(int x){
    int cur_op=-1;
    bool toggle=false;
    std::priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
    auto solve=[&](int op){
        if(op!=cur_op){
            if(cur_op>0){
                if(cur_op==3){
                    if(toggle)ran[st.top()].toggle();
                }else if(cur_op==4||cur_op==6){
                    while(pq.size()>1){
                        Range &val2=ran[pq.top().second];
                        pq.pop();
                        int idx=pq.top().second;
                        Range &val=ran[idx];
                        pq.pop();
                        val.push(),val2.push();
                        for(auto it=val2.begin();it!=val2.end();){
                            int l=*it;
                            it++;
                            int r;
                            if(it!=val2.end()){
                                r=*it-1;
                                it++;
                            }else{
                                r=LIM;
                            }
                            int cnt=0;
                            if(!val.eval(l)){
                                val.add(l);
                                cnt++;
                            }
                            for(auto it2=val.upper_bound(l);it2!=val.end()&&*it2<=r;it2=val.erase(it2))cnt++;
                            if(cnt&1)val.add(r+1);
                        }
                        pq.emplace(val.size(),idx);
                    }
                    if(cur_op==4)ran[pq.top().second].toggle();
                }else if(cur_op==5){
                    while(pq.size()>1){
                        Range &val2=ran[pq.top().second];
                        pq.pop();
                        int idx=pq.top().second;
                        Range &val=ran[idx];
                        pq.pop();
                        val.is_toggle^=val2.is_toggle;
                        for(auto x:val2)val.add(x);
                        pq.emplace(val.size(),idx);
                    }
                }else{
                    assert(false);
                }
            }
            cur_op=op;
            while(!pq.empty()){
                st.emplace(pq.top().second);
                pq.pop();
            }
            if(op==3)toggle=false;
            else if(op>0){
                int x=st.top();
                if(op==4)ran[x].toggle();
                pq.emplace(ran[x].size(),x);
                st.pop();
            }
        }
        if(op==-2)return;
        if(op==3){
            toggle^=true;
        }else if(op>0){
            int x=st.top();
            if(op==4)ran[x].toggle();
            pq.emplace(ran[x].size(),x);
            st.pop();
        }
    };
    while(!opr.empty()&&opr.top()<x){
        solve(opr.top());
        opr.pop();
    }
    solve(-2);
    if(x==7)opr.pop();
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    cin >> s;
    cur_val=0;
    for(auto c:s){
        if(isdigit(c)){
            cur_val=cur_val*10+c-'0';
        }else if(c=='['){
            cur_val=0;
        }else if(c==']'){
            ran[++cur_id].add(cur_val);
            st.emplace(cur_id);
        }else if(c=='('){
            opr.emplace(8);
        }else if(c==')'){
            eval(7);
        }else if(c=='!'){
            opr.emplace(3);
        }else if(c=='&'){
            eval(4);
            opr.emplace(4);
        }else if(c=='^'){
            eval(5);
            opr.emplace(5);
        }else if(c=='|'){
            eval(6);
            opr.emplace(6);
        }
    }
    eval(10);
    ran[st.top()].push();
    while(q--){
        int x;
        cin >> x;
        cout << (ran[st.top()].eval(x)?"True":"False") << "\n";
    }
}