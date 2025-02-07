#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cctype>
#include<string>
#define debug cout
typedef long long int lli;
using namespace std;
const int maxn=1e2+1e1,maxe=1e2+1e1,maxt=1e2+1e1;
const int mod=1e9+9;

struct ACautomatic {
    int ch[maxt][26],fail[maxt],fa[maxt],way[maxt],isend[maxt],root,cnt;
    ACautomatic() { root = ++cnt; }
    inline int insert(int &pos,int cur,char* s,int li) {
        if( !pos ) pos = ++cnt , way[pos] = s[cur-1];
        if( cur > li ) return isend[pos] = 1 , pos;
        return fa[insert(ch[pos][(int)s[cur]-'a'],cur+1,s,li)] = pos;
    }
    inline void getfail() {
        queue<int> q;
        for(int i=0;i<26;i++) ( ch[root][i] ? q.push(ch[root][i]) , fail[ch[root][i]] : ch[root][i] ) = root;
        while( q.size() ) {
            const int pos = q.front(); q.pop() , isend[pos] |= isend[fail[pos]];
            for(int i=0;i<26;i++) ( ch[pos][i] ? q.push(ch[pos][i]) , fail[ch[pos][i]] : ch[pos][i] ) = ch[fail[pos]][i];
        }
        for(int i=1;i<=cnt;i++) if( isend[i] ) for(int j=0;j<26;j++) ch[i][j] = ch[root][j];
    }
    inline void getway(int pos,char *s,int &li) {
        if( isend[pos] ) pos = root;
        for(li=0;pos!=root;pos=fa[pos]) s[++li] = way[pos];
    }
    inline int step(int pos,char *s,const int &li) {
        int ret = 0;
        for(int i=1;i<=li;i++) pos = ch[pos][(int)s[i]-'a'] , ret += isend[pos];
        return ret;
    }
}str,rev;

inline int add(const int &x,const int &y) {
    const int ret = x + y;
    return ret >= mod ? ret - mod : ret;
}
inline int mul(const int &x,const int &y) {
    return (lli) x * y % mod;
}
inline void adde(int &dst,const int &x) {
    if( ( dst += x ) >= mod ) dst -= mod;
}

int pre[maxt][maxt],pows[maxe];

inline void getpre() {
    static char s[maxt];
    static int li;
    for(int i=1;i<=str.cnt;i++) for(int j=1;j<=rev.cnt;j++) {
        rev.getway(j,s,li) , pre[i][j] = str.step(i,s,li);
    }
}

struct Node {
    int way,sum;
    friend Node operator + (const Node &a,const Node &b) {
        return (Node){add(a.way,b.way),add(a.sum,b.sum)};
    }
    friend Node operator * (const Node &a,const int &x) {
        return (Node){mul(a.way,x),mul(a.sum,x)};
    }
    friend Node operator += (Node &a,const Node &b) {
        return a = a + b;
    }
}f[maxn][maxe][maxt],g[maxn][maxe][maxt],tp[maxe][maxt];

int n,m;

inline void getf() {
    for(int i=0;i<26;i++) f[1][1][str.ch[str.root][i]] += (Node){1,str.isend[str.ch[str.root][i]]};
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) for(int cur=1;cur<=str.cnt;cur++) if( f[i][j][cur].way || f[i][j][cur].sum) for(int nxt=0;nxt<26;nxt++) {
        if( i != n ) f[i+1][j][str.ch[cur][nxt]] += (Node){f[i][j][cur].way,add(f[i][j][cur].sum,mul(f[i][j][cur].way,str.isend[str.ch[cur][nxt]]))} * pows[m-1];
        if( j != m ) f[i][j+1][str.ch[cur][nxt]] += (Node){f[i][j][cur].way,add(f[i][j][cur].sum,mul(f[i][j][cur].way,str.isend[str.ch[cur][nxt]]))};
    }
    f[0][1][str.root] = (Node){1,0};
}
inline void getg() {
    for(int i=0;i<26;i++) g[n][m][rev.ch[rev.root][i]] += (Node){1,rev.isend[rev.ch[rev.root][i]]};
    for(int i=n;i;i--) for(int j=m;j;j--) for(int cur=1;cur<=rev.cnt;cur++) if( g[i][j][cur].way || g[i][j][cur].sum) for(int nxt=0;nxt<26;nxt++) {
        if( i != 1 ) g[i-1][j][rev.ch[cur][nxt]] += (Node){g[i][j][cur].way,add(g[i][j][cur].sum,mul(g[i][j][cur].way,rev.isend[rev.ch[cur][nxt]]))} * pows[m-1];
        if( j != 1 ) g[i][j-1][rev.ch[cur][nxt]] += (Node){g[i][j][cur].way,add(g[i][j][cur].sum,mul(g[i][j][cur].way,rev.isend[rev.ch[cur][nxt]]))};
    }
    g[n+1][m][rev.root] = (Node){1,0};
}
inline int calc(int row,char* s) {
    int ret = 0; memset(tp,0,sizeof(tp));
    for(int i=1;i<=m;i++) {
        for(int cur=1;cur<=str.cnt;cur++) if( f[row-1][i][cur].way || f[row-1][i][cur].sum ) {
            //debug<<"i = "<<i<<"cur = "<<cur<<endl;
            //debug<<"way = "<<f[row-1][i][cur].way<<"sum = "<<f[row-1][i][cur].sum<<endl;
            const int nxt = s[i] - 'a';
            //debug<<"target = "<<str.ch[cur][nxt]<<endl;
            tp[i][str.ch[cur][nxt]] += (Node){f[row-1][i][cur].way,add(f[row-1][i][cur].sum,mul(f[row-1][i][cur].way,str.isend[str.ch[cur][nxt]]))}  * ( row != 1 ? pows[m-i] : 1 );
        }
        if( i != m ) for(int cur=1;cur<=str.cnt;cur++) if( tp[i][cur].way || tp[i][cur].sum ) {
            const int nxt = s[i+1] - 'a';
            tp[i+1][str.ch[cur][nxt]] += (Node){tp[i][cur].way,add(tp[i][cur].sum,mul(tp[i][cur].way,str.isend[str.ch[cur][nxt]]))};
        }
        //debug<<"Merging at i = "<<i<<endl;
        for(int cur=1;cur<=str.cnt;cur++) if( tp[i][cur].way || tp[i][cur].sum ) for(int rem=1;rem<=rev.cnt;rem++) if( g[row+1][i][rem].way || g[row+1][i][rem].sum ) {
            //debug<<"cur = "<<cur<<"rem = "<<rem<<"gway = "<<g[row+1][i][rem].way<<"gsum = "<<g[row+1][i][rem].sum<<endl;
            //debug<<"f = "<<tp[i][cur].way<<" "<<tp[i][cur].sum<<"pre = "<<pre[cur][rem]<<endl;
            adde(ret,mul(row != n ? pows[i-1] : 1,add(add(mul(tp[i][cur].way,g[row+1][i][rem].sum),mul(tp[i][cur].sum,g[row+1][i][rem].way)),mul(pre[cur][rem],mul(tp[i][cur].way,g[row+1][i][rem].way)))));
        }
    }
    return ret;
}

namespace IO {
    inline char nextchar() {
        static const int BS = 1 << 21;
        static char buf[BS],*st,*ed;
        if( st == ed ) ed = buf + fread(st=buf,1,BS,stdin);
        return st == ed ? -1 : *st++;
    }
    inline int getint() {
        int ret = 0; char ch;
        while( !isdigit(ch=nextchar()) );
        do ret = ret * 10 + ch - '0'; while( isdigit(ch=nextchar()) );
        return ret;
    }
    inline void getstr(char* s) {
        char ch;
        while( !isalpha(ch=nextchar()) );
        do *s++ = ch; while( isalpha(ch=nextchar()) );
        *s++ = '\0';
    }
}
using IO::getint;
using IO::getstr;

string in[maxt];
bool marked[maxt];

int main() {
    static char s[maxt];
    static int k,li,qs,p;
    n = getint() , m = getint() , k = getint();
    *pows = 1; for(int i=1;i<=m;i++) pows[i] = mul(pows[i-1],26);
    for(int i=1;i<=k;i++) getstr(s) , in[i] = s;
    for(int i=1;i<=k;i++) for(int j=1;j<=k;j++) if( i != j && ~in[i].find(in[j]) ) marked[i] = 1;
    for(int i=1;i<=k;i++) if( !marked[i] ) {
        memcpy(s+1,in[i].c_str(),in[i].length()) , s[in[i].length()+1] = '\0';
        str.insert(str.root,1,s,li=strlen(s+1)) , reverse(s+1,s+1+li) , rev.insert(rev.root,1,s,li);
    }
    str.getfail() , rev.getfail() , getpre() , getf() , getg();
    qs = getint();
    while(qs--) p = getint() , getstr(s+1) , printf("%d\n",calc(p,s));
    return 0;
}

