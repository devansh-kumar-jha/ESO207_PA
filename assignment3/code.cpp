//! First a linked list implementation
//! is required to form a Adjacency List Representation
//! for any graph G(V,E) after which we will implement the specific
//! dfs algorithm within the graph for solving the problem.

#include<bits/stdc++.h>
using namespace std;
#define int long long int

struct vertex
{
    int data;
    struct vertex* next;
    struct vertex* prev;
};

class graph
{
    private:
    struct vertex** adj;
    int size;

    public:
    graph(int x);
    void insert();
};

graph::graph(int x)
{
    size=x;
    adj=(struct vertex**)malloc(x*sizeof(struct vertex*));
    return;
}

struct vertex* SENT=NULL;

struct vertex* make_vertex(int data)
{
    vertex* temp=new vertex;
    temp->data=data;
    temp->next=SENT;
    return temp;
}


int32_t main()
{
    int n,m;  cin>>n>>m;
    graph G(n);
    G.insert();

    return 0;
}
