#include<bits/stdc++.h>
using namespace std;
#define int long long int

int dfs(vector<vector<int>>& adj,vector<bool>& visited,vector<int>& part,int i,int last)
{
    visited[i]=true;
    // cerr<<"came"<<" ";
    if(last==-1) part[i]=1;
    else if(part[i]!=0) {
        if(part[last]==part[i]) return 1;
        else return 0;
    }
    else {
        if(part[last]==1) part[i]=2;
        else part[i]=1;
    }
    // cerr<<"checks ok"<<" ";

    for(int j=0;j<adj[i].size();j++) {
        if(adj[i][j]==last) continue;
        int t=dfs(adj,visited,part,adj[i][j],i);
        // cerr<<"recursive dfs"<<" ";
        if(t==1) return 1;
    }
    
    return 0;
}

int32_t main()
{
    int n;  cin>>n;
    int m;  cin>>m;
    vector<vector<int>> adj(n);
    vector<bool> visited(n,false);
    vector<int> part(n,0);

    for(int i=0;i<m;i++) {
        int a,b;  cin>>a>>b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    // cerr<<"Input done"<<" ";

    for(int i=0;i<n;i++) {
        if(visited[i]==false) {
            int flag=dfs(adj,visited,part,i,-1);
            if(flag==1) {
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
