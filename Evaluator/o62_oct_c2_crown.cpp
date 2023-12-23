#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll,ll> p2;

const int N=2e5+5;
const ll inf=1e18;

int n;
int a[N];
ll ans=-1;

struct node;
typedef node* pnode;
struct node{
	int val,li,ri,h;
	ll dp1,dp2,dpl,dpr,dpm;
	pnode l,r;
	node(ll val,ll id):val(val),h(val),li(id),ri(id),dp1(0),dp2(-inf),dpl(-inf),dpr(-inf),dpm(-inf),l(nullptr),r(nullptr){}
};

void dfs(pnode t){
	vector<pnode> adj;
	if(t->l)adj.emplace_back(t->l);
	if(t->r)adj.emplace_back(t->r);
	for(auto u:adj){
		u->h-=t->val;
		dfs(u);
		t->li=min(t->li,u->li);
		t->ri=max(t->ri,u->ri);
	}
	ll sz=t->ri-t->li+1;
	t->dp1=sz*t->h;
	if(sz>1)t->dpl=t->dpr=(sz-1)*t->h;
	if(sz>2)t->dpm=sz*t->h-1;
	p2 mx(-inf,-inf);
	for(auto u:adj){
		if(u->li>t->li){
			t->dpm=max(t->dpm,u->dpl+sz*t->h-1);
			t->dpl=max(t->dpl,u->dp1+(sz-1)*t->h);
		}else{
			t->dpl=max(t->dpl,u->dpl+(sz-1)*t->h);
		}
		if(u->ri<t->ri){
			t->dpm=max(t->dpm,u->dpr+sz*t->h-1);
			t->dpr=max(t->dpr,u->dp1+(sz-1)*t->h);
		}else{
			t->dpr=max(t->dpr,u->dpr+(sz-1)*t->h);
		}
		if(u->li-t->li>1||t->ri-u->ri>1)t->dpm=max(t->dpm,u->dp1+sz*t->h-1);
		t->dp1=max(t->dp1,u->dp1+sz*t->h);
		t->dp2=max(t->dp2,u->dp2+sz*t->h);
		t->dp2=max(t->dp2,u->dpm+sz*t->h);
		mx.second=max(mx.second,u->dp1);
		if(mx.second>mx.first)swap(mx.first,mx.second);
	}
	if(t->h>1)t->dp2=max(t->dp2,t->dpm);
	if(mx.second>0)t->dp2=max(t->dp2,mx.first+mx.second+sz*t->h);
}

int main(){
	cin.tie(nullptr)->sync_with_stdio(false);
	cin >> n;
	for(int i=1;i<=n;i++)cin >> a[i];
	stack<pnode> st;
	pnode rt;
	for(int i=1;i<=n+1;i++){
		if(a[i]==0){
			if(!st.empty()){
				dfs(rt);
				ans=max(ans,rt->dp2);
				while(!st.empty())st.pop();
			}
			continue;
		}
		pnode t=new node(a[i],i);
		while(!st.empty()&&st.top()->val>=a[i]){
			t->l=st.top();
			st.pop();
		}
		if(st.empty())rt=t;
		else st.top()->r=t;
		st.emplace(t);
	}
	cout << ans;
}