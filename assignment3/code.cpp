#include<bits/stdc++.h>
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
    void display();
    void clear();
};

/// This structure is of the type
/// to be returned by the function Bipartite()
struct ret_Bipartite
{
    int* V1;    int len1;
    int* V2;    int len2;
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

/// Releasing the memory used by the Doubly Linked List
/// representing edges connected to a single vertex.
/// O(N) time where N is the number of edges connected to this vertex.
void free_all(vertex *HEAD,vertex *TAIL,vertex* S)
{
    vertex *temp=HEAD;
    while(temp!=S) {
        if(temp->prev!=S) free(temp->prev);
        temp=temp->next;
    }
    free(TAIL);
    return;
}

/// Priting the contents of a Doubly Linked List
/// showing the edges for a vertex.
/// O(N) time where N is the number of edges connected to this vertex.
void print_all(vertex* HEAD,vertex* S)
{
    vertex* temp=HEAD;
    while(temp!=S) {
        cout<<temp->num<<" ";
        temp=temp->next;
    }
    cout<<"\n";
    return; 
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

/// display() the adjacency list representation
/// of the graph explicitly.
/// O(|V|+2*|E|) time where |V| is number of vertices and |E| is number of edges.
void graph::display()
{
    for(int i=0;i<size;i++) {
        cout<<i<<"->";
        print_all(head[i],SENT[i]);
    }
    return;
}

/// clear() all the data present in the graph.
/// O(|V|+2*|E|) time where |V| is number of vertices and |E| is number of edges.
void graph::clear()
{
    for(int i=0;i<size;i++) {
        free_all(head[i],tail[i],SENT[i]);
        SENT[i]->next=SENT[i];
        SENT[i]->prev=SENT[i];
        head[i]=SENT[i];
        tail[i]=SENT[i];
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
    else if(part[i]!=0) {
        if(part[i]!=part[last]) return false;
        else return true;
    }
    else {
        if(part[last]==1) part[i]=2;
        else part[i]=1;
    }

    vertex* temp=G.get(i);
    while(temp!=G.sent(i)) {
        if(temp->num==last) {}
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
ret_Bipartite* Bipartite(graph G)
{
    int n=G.length();
    bool visited[n];    int part[n];
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

    ret_Bipartite* p=new ret_Bipartite;
    p->len1=0;  p->len2=0;
    p->V1=(int*)malloc(n*sizeof(int));
    p->V2=(int*)malloc(n*sizeof(int));

    for(int i=0;i<n;i++) {
        if(part[i]==1) { (p->V1)[p->len1]=i;  (p->len1)++; }
        else { (p->V2)[p->len2]=i;  (p->len2)++; }
    }

    return p;
}

int32_t main()
{
    // Taking Inputs.
    int n,m;  cin>>n>>m;
    graph G(n);
    for(int i=0;i<m;i++) {
        int a,b;  cin>>a>>b;
        G.insert(a-1,b-1);
    }

    // Solving of the problem.
    ret_Bipartite* ret=Bipartite(G);
    if(ret==NULL) cout<<"The graph is not Bipartite"<<"\n";
    else {
        for(int i=0;i<(ret->len1);i++) cout<<(ret->V1)[i]+1<<" ";
        cout<<"\n";
        for(int i=0;i<(ret->len2);i++) cout<<(ret->V2)[i]+1<<" ";
        cout<<"\n";
    }

    // Ending the program.
    G.clear();
    cerr<<"Time:"<<1000*((double)clock())/(double)CLOCKS_PER_SEC<<"ms/n";
    return 0;
}
