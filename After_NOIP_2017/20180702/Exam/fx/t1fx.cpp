#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<cctype>
#define debug cout
typedef long long int lli;
using namespace std;
const int maxn=5e5+1e2,maxe=1e6+1e2;
const int mod=1e9+7;

int inv[maxe];
inline int mul(const int &x,const int &y) {
    return (lli) x * y % mod;
}
inline void adde(int &dst,const int &x) {
    if( ( dst += x ) >= mod ) dst -= mod;
}
inline void mule(int &dst,const int &x) {
    dst = (lli) dst * x % mod;
}
inline int fastpow(int base,int tim) {
    int ret = 1;
    while(tim) {
        if( tim & 1 ) mule(ret,base);
        if( tim >>= 1 ) mule(base,base);
    }
    return ret;
}
inline int c(int x,int y) {
    int ret = 1;
    for(int i=0;i<y;i++) mule(ret,x-i);
    for(int i=1;i<=y;i++) mule(ret,inv[i]);
    return ret;
}
inline int gcd(int x,int y) {
    register int t;
    while( t = x % y ) x = y , y = t;
    return y;
}

int u[maxe],v[maxe];
int s[maxn],t[maxe<<1],nxt[maxe<<1];
int dfn[maxn],low[maxn],stk[maxe],top,fs;
vector<int> es[maxn<<1];
bool vis[maxn];
int n,m,k,ans=1;

inline void coredge(int from,int to) {
    static int cnt = 1;
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void addedge(int a,int b) {
    coredge(a,b) , coredge(b,a);
}
inline void dfs(int pos,int sou) {
    static int dd; low[pos] = dfn[pos] = ++dd , vis[pos] = 1;
    for(int at=s[pos];at;at=nxt[at]) if( at != ( sou ^ 1 ) ) {
        if( !vis[t[at]] ) {
            stk[++top] = at;
            dfs(t[at],at) , low[pos] = min( low[pos] , low[t[at]] );
            if( low[t[at]] >= dfn[pos] ) {
                int x; ++fs;
                do es[fs].push_back((x=stk[top--])>>1); while( x != at );
            }
        } else {
            if( dfn[t[at]] < dfn[pos] ) stk[++top] = at;
            low[pos] = min( low[pos] , dfn[t[at]] );
        }
    }
}
inline void calc_ring(const vector<int> &vec) {
    if( vec.size() == 1 ) return mule(ans,k);
    int ps = 0;
    for(unsigned i=0;i<vec.size();i++) {
        if( !vis[u[vec[i]]] ) ps += vis[u[vec[i]]] = 1;
        if( !vis[v[vec[i]]] ) ps += vis[v[vec[i]]] = 1;
    }
    for(unsigned i=0;i<vec.size();i++) vis[u[vec[i]]] = vis[v[vec[i]]] = 0;
    if( ps == (signed)vec.size() ) {
        int ret = 0;
        for(int i=1;i<=ps;i++) adde(ret,fastpow(k,gcd(i,ps)));
        mule(ret,inv[ps]) , mule(ans,ret);
    } else mule(ans,c(k+vec.size()-1,vec.size()));
}

inline void init() {
    inv[0] = inv[1] = 1;
    for(int i=2;i<=m;i++) inv[i] = mul(mod-mod/i,inv[mod%i]);
}

inline int getint() {
    int ret = 0 , ch;
    while( !isdigit(ch=getchar()) );
    do ret = ret * 10 + ch - '0'; while( isdigit(ch=getchar()) );
    return ret;
}

int main() {
    n = getint() , m = getint() , k = getint() , init();
    for(int i=1;i<=m;i++) addedge(u[i]=getint(),v[i]=getint());
    for(int i=1;i<=n;i++) if( !vis[i] ) dfs(i,0);
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=fs;i++) calc_ring(es[i]);
    printf("%d\n",ans);
    return 0;
}

