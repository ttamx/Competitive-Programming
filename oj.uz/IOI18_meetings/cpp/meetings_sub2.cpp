#include "meetings.h"

using namespace std;

typedef long long ll;

const int N=750005;

int n,q;

struct node;
typedef node* pnode;
struct node{
	ll val,idx,sz,cnt;
	pnode l,r,p;
	node(int val,int idx):val(val),idx(idx),sz(1),cnt(1),l(nullptr),r(nullptr),p(nullptr){}
};
pnode rt,lf,nd[N];

int dfssz(pnode t){
	if(!t)return 0;
	t->sz=t->cnt;
	t->sz+=dfssz(t->l);
	t->sz+=dfssz(t->r);
	return t->sz;
}

ll dfs(pnode t){
	if(!t)return 0;
	if(!(t->l))return t->val+dfs(t->r);
	if(!(t->r))return t->val+dfs(t->l);
	return min(t->val*(t->l->sz+t->cnt)+dfs(t->r),t->val*(t->r->sz+t->cnt)+dfs(t->l));
}

vector<ll> minimum_costs(vector<int> H, vector<int> L, vector<int> R) {
	n=H.size();
	q=L.size();
	for(int i=0;i<n;i++)nd[i]=new node(H[i],i);
	vector<ll> ans;
	for(int i=0;i<q;i++){
		*nd[L[i]]=node(H[L[i]],L[i]);
		rt=lf=nd[L[i]];
		for(int j=L[i]+1;j<=R[i];j++){
			*nd[j]=node(H[j],j);
			if(rt->val<H[j]){
				nd[j]->l=rt;
				rt->p=nd[j];
				rt=lf=nd[j];
				continue;
			}
			while(lf->val<H[j])lf=lf->p;
			nd[j]->l=lf->r;
			if(lf->r)lf->r->p=nd[j];
			lf->r=nd[j];
			nd[j]->p=lf;
			lf=nd[j];
		}
		dfssz(rt);
		ans.emplace_back(dfs(rt));
	}
	return ans;
}