#include<iostream>
#include<cstdio>
#include<algorithm>
#include<set>
#include<map>
#include<queue>
#include<cassert>
#define PB push_back
#define MP make_pair
#define sz(v) (in((v).size()))
#define forn(i,n) for(in i=0;i<(n);++i)
#define forv(i,v) forn(i,sz(v))
#define fors(i,s) for(auto i=(s).begin();i!=(s).end();++i)
#define all(v) (v).begin(),(v).end()
using namespace std;
typedef int in;
typedef vector<in> VI;
typedef vector<VI> VVI;
const in pmod=1000000007LL;
long long p2(long long a){
  return (1LL<<a);
}
template<typename T> T pw(T a, in b){
  T r=1LL;
  for(long long i=30;i>=0;i--){
    r*=r;
    if(b&p2(i))
      r*=a;
  }
  return r;
}
struct fp{
  long long a;
  fp(long long aa=0){
    a=aa;
    if(a<0 || a>=pmod){
      a%=pmod;
      if(a<0)
	a+=pmod;
    }
  }
  fp inv()const{
    return pw(*this,pmod-2);
  }
  fp operator*(const fp cp)const{
    return fp((a*cp.a)%pmod);
  }
  fp operator+(const fp cp)const{
    return fp((a+cp.a)>pmod?a+cp.a-pmod:a+cp.a);
  }
  fp operator/(const fp cp)const{
    return (*this)*cp.inv();
  }
  fp operator-(const fp cp)const{
    return (*this)+(-cp);
  }
  fp operator-()const{
    return (a==0?0:pmod-a);
  }
  fp& operator*=(const fp cp){
    return (*this)=(*this)*cp;
  }
  fp& operator/=(const fp cp){
    return (*this)=(*this)/cp;
  }
  fp& operator+=(const fp cp){
    return (*this)=(*this)+cp;
  }
  fp& operator-=(const fp cp){
    return (*this)=(*this)-cp;
  }
  bool operator==(const fp cp)const{
    return a==cp.a;
  }
  bool operator!=(const fp cp)const{
    return a!=cp.a;
  }
};
ostream& operator<<(ostream& os, fp a){
  return os<<a.a;
}
struct mat{
  vector<vector<fp> > a;
  in n,m;
  void ini(in pn, in pm){
    a.clear();
    n=pn;
    m=pm;
    a.resize(n,vector<fp>(m,fp(0LL)));
  }
  mat operator*(const mat& cp)const{
    assert(m==cp.n);
    mat r;
    r.ini(n,cp.m);
    long long t;
    forn(i,n){
      forn(j,cp.m){
	t=0;
	forn(k,m){
	  t+=a[i][k].a*cp.a[k][j].a;
	}
	r.a[i][j]=t;
      }
    }
    return r;
  }
  mat& operator*=(const mat& cp){
    assert(m==cp.n);
    mat r;
    r.ini(n,cp.m);
    long long t;
    forn(i,n){
      forn(j,cp.m){
	t=0;
	forn(k,m){
	  t+=a[i][k].a*cp.a[k][j].a;
	}
	r.a[i][j]=t;
      }
    }
    return *this=r;
  }
  mat operator+(const mat& cp)const{
    assert(n==cp.n && m==cp.m);
    mat r;
    r.ini(n,m);
    forn(i,n){
      forn(j,m){
	r.a[i][j]=a[i][j]+cp.a[i][j];
      }
    }
    return r;
  }
  mat& operator+=(const mat& cp){
    assert(n==cp.n && m==cp.m);
    forn(i,n){
      forn(j,m){
	a[i][j]+=cp.a[i][j];
      }
    }
    return *this;
  }
};
mat pwm(mat a, long long b){
  mat r=a;
  forv(i,r.a){
    forv(j,r.a[i])
      r.a[i][j]=(i==j);
  }
  bool odn=0;
  for(long long i=51;i>=0;i--){
    if(odn)
      r*=r;
    if(b&p2(i)){
      odn=1;
      r*=a;
    }
  }
  return r;
}
mat basfib;
mat fibmat;
mat ttp,ts;
mat smfib,sft;
vector<mat> smpw;
pair<fp,fp> fbat(long long a){
  ttp=pwm(fibmat,a-1)*basfib;
  return MP(ttp.a[0][0],ttp.a[1][0]);
}
struct fenw{
  vector<mat> fw;
  in n;
  void ini(in pn){
    n=pn;
    fw.clear();
    fw.resize(n);
    forn(i,n)
      fw[i].ini(3,1);
  }
  void ad(in l, mat ts){
    in ol=l;
    while(l<n){/*
		 mat tt=smpw[l-ol]*ts;
		 cout<<"ad "<<l<<endl;
		 forv(i,tt.a){
		 forv(j,tt.a[i]){
		 cout<<tt.a[i][j]<<" ";
		 }
		 cout<<endl;
		 }
		 cout<<endl;*/
      fw[l]+=smpw[l-ol]*ts;
      l|=(l+1);
    }
  }
  mat sm(in l){
    mat r;
    r.ini(3,1);
    in ol=l;
    while(l>=0){/*
		  mat tt=smpw[ol-l]*fw[l];
		  cout<<"sm "<<l<<endl;
		  forv(i,tt.a){
		  forv(j,tt.a[i]){
		  cout<<tt.a[i][j]<<" ";
		  }
		  cout<<endl;
		  }
		  cout<<endl;*/
      r+=smpw[ol-l]*fw[l];
      l&=(l+1);
      --l;
    }
    return r;
  }
};
vector<fenw> fws;
VI fid,floc;
VI sts;
const in mxp=18;
VI pr[mxp];
vector<fp> vlf,vls;
VI ht,pap;
void mkfid(in u, bool rq){
  if(fid[u]!=-2)
    return;
  if(sts[u]*2<sts[pr[0][u]] || u==0){
    if(rq==0){
      fid[u]=floc[u]=-1;
      return;
    }
    in s=sz(fws);
    fws.PB(fenw());
    fid[u]=s;
    floc[u]=0;
    return;
  }
  mkfid(pr[0][u],1);
  fid[u]=fid[pr[0][u]];
  floc[u]=floc[pr[0][u]]+1;
}
void proct(){
  in n=sz(pr[0]);
  sts.resize(n,1);
  fid=floc=VI(n,-2);
  for(in i=n-1;i>0;--i){
    sts[pr[0][i]]+=sts[i];
  }
  for(in i=n-1;i>=0;--i){
    mkfid(i,0);
  }
  for(in i=n-1;i>=0;--i){
    if(fid[i]<0)
      continue;
    if(sz(fws[fid[i]].fw))
      continue;
    fws[fid[i]].ini(floc[i]+1);
  }
  pap.resize(n);
  forn(i,n){
    if(i==0){
      pap[i]=-1;
      continue;
    }
    if(floc[i]==0 || floc[i]==-1){
      pap[i]=pr[0][i];
      continue;
    }
    pap[i]=pap[pr[0][i]];
  }
}
in lca(in u, in v){
  if(ht[u]<ht[v])
    swap(u,v);
  for(in i=mxp-1;i>=0;--i){
    if(ht[u]-p2(i)>=ht[v])
      u=pr[i][u];
  }
  assert(ht[u]==ht[v]);
  for(in i=mxp-1;i>=0;--i){
    if(pr[i][u]!=pr[i][v]){
      u=pr[i][u];
      v=pr[i][v];
    }
  }
  if(u!=v){
    u=pr[0][u];
    v=pr[0][v];
  }
  assert(u==v);
  return u;
}
struct qel{
  in u;
  qel(in a=0){
    u=a;
  }
  bool operator<(const qel& cp)const{
    return ht[u]<ht[cp.u];
  }
};
priority_queue<qel> q;
VI lvs,lad;
in vdt;
vector<mat> fv;
mat r;
vector<mat> ucm;
void clr(mat& c){
  forv(i,c.a){
    forv(j,c.a[i])
      c.a[i][j]=0;
  }
}
void prq(){
  qel tel;
  in tx;
  while(!q.empty()){
    tel=q.top();
    q.pop();
    tx=tel.u;
    if(lvs[tx]==vdt)
      continue;
    lvs[tx]=vdt;
    if(fid[tx]==-1){
      r+=ucm[tx]*fv[tx];
      if(tx==pr[0][tx]){
	clr(ucm[tx]);
	continue;
      }
      ucm[pr[0][tx]]+=smpw[1]*ucm[tx];
      clr(ucm[tx]);
      if(lad[pr[0][tx]]!=vdt){
	lad[pr[0][tx]]=vdt;
	q.push(qel(pr[0][tx]));
      }
      continue;
    }
    r+=ucm[tx]*fws[fid[tx]].sm(floc[tx]);
    if(pap[tx]==-1){
      clr(ucm[tx]);
      continue;
    }
    ucm[pap[tx]]+=smpw[floc[tx]+1]*ucm[tx];
    clr(ucm[tx]);
    if(lad[pap[tx]]!=vdt){
      lad[pap[tx]]=vdt;
      q.push(qel(pap[tx]));
    }
  }
}
void ansq(in tx, in ty){
  r.ini(3,1);
  mat cm;
  cm.ini(3,3);
  forn(i,3)
    cm.a[i][i]=1;
  in u=lca(tx,ty);
  q.push(qel(tx));
  q.push(qel(ty));
  q.push(qel(u));
  ucm[tx]+=cm;
  ucm[ty]+=cm;
  forn(i,3)
    cm.a[i][i]*=-1;
  ucm[u]+=cm;
  if(u!=0){
    q.push(qel(pr[0][u]));
    ucm[pr[0][u]]+=cm;
  }
  ++vdt;
  prq();
  cout<<r.a[0][0]<<"\n";
}
void adq(in tx, long long ty){
  mat crm;
  crm.ini(3,1);
  pair<fp,fp> tt=fbat(ty);
  crm.a[0][0]=crm.a[1][0]=tt.first;
  crm.a[2][0]=tt.second;
  if(fid[tx]==-1){
    fv[tx]+=crm;
    return;
  }
  fws[fid[tx]].ad(floc[tx],crm);
}
VI tpr;
VI cod,decod;
VVI tcd;
in nxdec;
void dfscod(in u){
  forv(i,tcd[u]){
    cod[nxdec]=tcd[u][i];
    decod[tcd[u][i]]=nxdec;
    ++nxdec;
    dfscod(tcd[u][i]);
  }
}
void mkcod(){
  in n=sz(tpr);
  cod=decod=VI(n,-1);
  tcd.resize(n);
  for(in i=1;i<n;++i)
    tcd[tpr[i]].PB(i);
  cod[0]=decod[0]=0;
  nxdec=1;
  dfscod(0);
}
void mkt(){
  in n,m;
  cin>>n>>m;
  lvs.resize(n,0);
  lad=lvs;
  vdt=1;
  ucm.resize(n);
  forn(i,n)
    ucm[i].ini(3,3);
  tpr.resize(n);
  tpr[0]=0;
  forn(i,n-1){
    cin>>tpr[i+1];
    --tpr[i+1];
  }
  mkcod();
  forn(z,mxp)
    pr[z].resize(n);
  ht.resize(n);
  fv.resize(n);
  forn(i,n)
    fv[i].ini(3,1);
  ht[0]=0;
  pr[0][0]=0;
  forn(i,n-1){
    pr[0][i+1]=decod[tpr[cod[i+1]]];
    assert(pr[0][i+1]<i+1);
    ht[i+1]=ht[pr[0][i+1]]+1;
  }
  for(in i=1;i<mxp;++i){
    forn(j,n)
      pr[i][j]=pr[i-1][pr[i-1][j]];
  }
  proct();
  char typ;
  in tx;
  long long ty;
  forn(zz,m){
    cin>>typ>>tx>>ty;
    if(typ=='Q'){
      ansq(decod[tx-1],decod[ty-1]);
    }
    else{
      adq(decod[tx-1],ty);
    }
  }
}
const in mx=100009;
int main(){
  ios::sync_with_stdio(0);
  cin.tie(0);
  smfib.ini(3,3);
  smfib.a[0][0]=smfib.a[0][2]=smfib.a[1][2]=smfib.a[2][1]=smfib.a[2][2]=1;
  sft.ini(3,1);
  basfib.ini(2,1);
  basfib.a[0][0]=basfib.a[1][0]=1LL;
  fibmat.ini(2,2);
  fibmat.a[0][0]=0;
  fibmat.a[0][1]=fibmat.a[1][0]=fibmat.a[1][1]=1LL;
  smpw.resize(mx);
  smpw[0].ini(3,3);
  forn(i,3)
    smpw[0].a[i][i]=1;
  for(in i=1;i<sz(smpw);++i)
    smpw[i]=smpw[i-1]*smfib;
  mkt();
  return 0;
}
