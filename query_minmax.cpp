#include<bits/stdc++.h>
using namespace std;
long long inf = 1e12;
long long query(long long u, long long v){
    long long x = C[u];
    long long y = C[v];
    priority_queue<array<long long,2>> djk;
    vector<long long> dis(ccount+1,inf);
    dis[x] = 0;
    djk.push({0,x});
    while(!djk.empty()){
        array<long long,2> q = djk.top();
        djk.pop();
        if(q[1] == y)return dis[y]; //la prima volta che estraggo y per monotonia dis[y] avrà valore minimo
        if(-q[0] > dis[q[1]])continue;
        for(auto node:adj[q[1]]){
            long long w = max(node[1],-q[0]);
            if(dis[node[0]] > w){
                dis[node[0]] = w;
                djk.push({-w,node[0]});
            }
        }
    }
    return dis[y];
}
