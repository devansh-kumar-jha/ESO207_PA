#include<bits/stdc++.h>
using namespace std;
#define int long long int

bool bfs(vector<vector<int>>& adj,vector<bool>& visited,vector<int>& part,int i,int last)
{
    part[i]=1;
    visited[i]=true;
    queue<int> q;
    q.push(i);
    while(q.empty()!=true) {
        int x=q.front();
        q.pop();
        for(int j=0;j<adj[x].size();j++) {
            if(visited[adj[x][j]]==false) {
                visited[adj[x][j]]=true;
                part[adj[x][j]]=3-part[x];
                q.push(adj[x][j]);
            }
            else if(part[x]==part[adj[x][j]]) return true;
        }
    }
    return false;
}


int32_t main()
{
    int n,m;  cin>>n>>m;
    vector<vector<int>> adj(n);
    for(int i=0;i<m;i++) {
        int a,b;  cin>>a>>b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<bool> visited(n,false);
    vector<int> part(n,0);

    for(int i=0;i<n;i++) {
        if(visited[i]==false) {
            bool flag=bfs(adj,visited,part,i,-1);
            if(flag==true) {
                cout<<"NO"<<"\n";
                cerr<<"Time:"<<1000*((double)clock())/(double)CLOCKS_PER_SEC<<"ms/n";
                return 0;
            }
        }
    }

    cout<<"YES"<<"\n";
    for(int i=0;i<n;i++) cout<<part[i]<<"\n";

    cerr<<"Time:"<<1000*((double)clock())/(double)CLOCKS_PER_SEC<<"ms/n";
    return 0;
}
