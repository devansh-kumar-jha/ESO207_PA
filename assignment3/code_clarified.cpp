#include <iostream>
using namespace std;
#define int long long int

///////////////////////////////////////// Structures and Pointers implementation /////////////////////////////////////////////////

/// This structure represents a single vertex in the graph.
/// The fields `next` and `prev` are not related to
/// the edges but rather correspond to the linked list in
/// the adjacency list representation.
struct vertex
{
    int num;  // Shows the number of the vertex in the graph
    struct vertex* next;
    struct vertex* prev;
};

/// Class for controlling the adjacency list
/// structure of the graph.
class graph
{
    private:
    struct vertex** head;
    struct vertex** tail;
    struct vertex** SENT;
    int size;

    public:
    graph(int x);
    int length();
    vertex* get(int i);
    vertex* sent(int i);
    void insert(int a,int b);
};

/// Making of a new vertex with required index number.
/// O(1) time.
vertex* make_vertex(int num)
{
    vertex *temp=new vertex;
    if(temp!=NULL) temp->num=num;
    temp->next=NULL;
    temp->prev=NULL;
    return temp;
}

/// Inserting the vertex with required index value in a list's tail.
/// O(1) time.
vertex* insert_vertex(int num,vertex* TAIL,vertex* S)
{
    vertex *temp=make_vertex(num);
    if(temp==NULL) {
        cerr<<"Memory full";
        return TAIL;
    }
    temp->next=S;       temp->prev=TAIL;
    if(TAIL!=NULL) TAIL->next=temp;    
    S->prev=temp;       TAIL=temp;
    return TAIL;
}

/// Contructor for making a graph with x number of vertices.
/// O(x) time.
graph::graph(int x)
{
    size=x;
    SENT=(vertex**)malloc(x*sizeof(vertex*));
    head=(vertex**)malloc(x*sizeof(vertex*));
    tail=(vertex**)malloc(x*sizeof(vertex*));
    for(int i=0;i<x;i++) {
        SENT[i]=new vertex;
        SENT[i]->num=-1;
        SENT[i]->next=SENT[i];
        SENT[i]->prev=SENT[i];
        head[i]=SENT[i];
        tail[i]=SENT[i];
    }
    return;
}

/// Returns the size of graph.
/// O(1) time.
int graph::length()
{
    return size;
}

/// Returns the HEAD for the linked list
/// containing vertices directly connected to the
/// vertex with index i.
/// O(1) time.
vertex* graph::get(int i)
{
    if(i>=size) return NULL;
    else return head[i];
}

/// Returns the SENTINEL vertex for the linked list
/// containing vertices directly connected to the
/// vertex with index i.
/// O(1) time.
vertex* graph::sent(int i)
{
    if(i>=size) return NULL;
    else return SENT[i];
}

/// insert an edge joining the a th 
/// and b th vertices in the graph.
/// O(1) time.  
void graph::insert(int a,int b)
{
    if(a>=size || b>=size) return;
    
    tail[a]=insert_vertex(b,tail[a],SENT[a]);
    if(head[a]==SENT[a]) {
        head[a]=tail[a];    SENT[a]->next=head[a];
        head[a]->prev=SENT[a];
    }
    
    tail[b]=insert_vertex(a,tail[b],SENT[b]);
    if(head[b]==SENT[b]) {
        head[b]=tail[b];    SENT[b]->next=head[b];
        head[b]->prev=SENT[b];
    }
    
    return;
}

/////////////////////////////////////////////////// Main Functions related to the Problem ///////////////////////////////////////////

/// This is a recursive function executed on the graph G.
/// It implements the depth first search algorithm on the graph G.
bool dfs(graph G,bool visited[],int part[],int i,int last)
{
    visited[i]=true;
    if(last==-1) part[i]=1;
    else {
        if(part[last]==1) part[i]=2;
        else part[i]=1;
    }

    vertex* temp=G.get(i);
    while(temp!=G.sent(i)) {
        if(visited[temp->num]==true) {
            if(part[i]==part[temp->num]) return true;
        }
        else {
            bool x=dfs(G,visited,part,temp->num,i);
            if(x==true) return true;
        }
        temp=temp->next;
    }

    return false;
}

/// This is the main function which was demanded by the problem statement.
/// This runs over the whole graph once.
/// O(|V|+|E|) time.
int* Bipartite(graph G)
{
    int n=G.length();
    bool* visited=(bool*)malloc(n*sizeof(bool));
    int* part=(int*)malloc(n*sizeof(int));
    
    if(n<2) return NULL;
    
    for(int i=0;i<n;i++) {
        visited[i]=false;
        part[i]=0;
    }

    for(int i=0;i<n;i++) {
        if(visited[i]==false) {
            bool flag=dfs(G,visited,part,i,-1);
            if(flag==true) return NULL;
        }
    }

    return part;
}

int32_t main()
{
    // Taking Inputs.
    int n,m;  cin>>n>>m;
    graph G(n);
    for(int i=0;i<m;i++) {
        int a,b;  cin>>a>>b;
        G.insert(a,b);
    }

    // Solving of the problem.
    int* ret=Bipartite(G);
    if(ret==NULL) cout<<"NO";
    else {
        cout<<"YES"<<"\n";
        for(int i=0;i<n;i++) cout<<ret[i]<<"\n";
    }

    // Ending the program.
    return 0;
}
