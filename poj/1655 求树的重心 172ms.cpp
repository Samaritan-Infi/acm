/*
 * @Samaritan_infi
 */
 ///求树的重心，这里通过par搜索，节省空间，发现同时节省时间，应该是省了memset的时间
//#include <bits/stdc++.h>
#include <cstring>
#include <cstdio>
#include <vector>
using namespace std;
typedef long long ll ;

template <class T>
inline void scan(T &ret) {
    char c ;
    ret = 0 ;
    while((c = getchar()) < '0' || c > '9') ;
    while(c >= '0' && c <= '9') {
        ret = ret * 10 + c - '0' , c = getchar() ;
    }
}

const int maxn = 20005 ;
vector<int> edge[maxn] ;
int son[maxn] ;
bool vis[maxn] ;
int ans , s ;
void init(int n) {
    for(int i = 1 ; i <= n ; i ++) edge[i].clear() ;
    memset(son , 0 , sizeof son) ;
    memset(vis , false , sizeof vis) ;
    ans = s = 1e9 + 5 ;
}

int n ;
void dfs(int x , int par) {
    int son_x = 0 , ans_x = 0 ;
    for(int i = 0 ; i < edge[x].size() ; i ++) {
        int u = edge[x][i] ;
        if(u == par) continue ;
        dfs(u , x) ;
        son_x += 1 + son[u] ;
        ans_x = max(ans_x , 1 + son[u]) ;
    }
    son[x] = son_x ;
    ans_x = max(ans_x , n - 1 - son[x]) ;
    if(ans_x < ans || (ans_x == ans && x < s)) {
        ans = ans_x ; s = x ;
    }
}

int main() {
    int kase ; scan(kase) ;
    while(kase --) {
        scan(n) ;
        init(n) ;
        int l , r ;
        for(int i = 1 ; i < n ; i ++) {
            scan(l) , scan(r) ;
            edge[l].push_back(r) ;
            edge[r].push_back(l) ;
        }
        dfs(1 , 0) ;
        printf("%d %d\n" , s , ans) ;
    }
    return 0 ;
}
