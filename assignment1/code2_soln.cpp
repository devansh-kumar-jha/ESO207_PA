#include <iostream>
using namespace std;
#define int long long int

// Self Referential Structure for the Doubly Linked List.
struct node 
{
    node *prev;
    int cof;
    int exp;
    node *next;
};

// Making of a new node with required initial values.
node* make_node(int cof,int exp)
{
    node *temp=new node;
    temp->cof=cof;
    temp->exp=exp;
    return temp;
}

// Setting up of global Sentinal Nodes for the Doubly Linked List.
// As a precaution we will start with values which are not possible for any polynomial's actual node.
node* SENT=make_node(0,-1);                     // Sentinel Node for Addition Polynomial
node* SENT1=make_node(0,-1);                    // Sentinel Node for First Polynomial
node* SENT2=make_node(0,-1);                    // Sentinel Node for Second Polynomial

// Inserting the node with required value in a doubly linked list's tail.
node* insert_node(int cof,int exp,node* TAIL,node* S)
{
    node *temp=make_node(cof,exp);
    temp->next=S;
    if(TAIL!=NULL) temp->prev=TAIL;
    if(TAIL!=NULL) TAIL->next=temp;
    TAIL=temp;
    S->prev=TAIL;
    return TAIL;
}

// Priting the contents of a Doubly Linked List.
void print_all(node* HEAD,node* S)
{
    node* temp=HEAD;
    while(temp!=S) {
        cout<<temp->cof<<" "<<temp->exp<<" ";
        temp=temp->next;
    }
    return; 
}

// Structure for lists.
struct lst
{
    node* poly;
    lst* prev;
    lst* next;
};

// Lists class to control the lists in Divide and Conquer algorithm making.
class lists
{
    public:
    lst* head;
    lst* tail;
    lst* sent;
    int len;
    lists();
    void insert(node* head);
    void copy(lists F);
};

// Constructor for lists.
lists::lists()
{
    sent=new lst;
    sent->next=sent;
    sent->prev=sent;
    // sent->poly=make_node(0,-1);
    // sent->poly->next=sent->poly;
    // sent->poly->prev=sent->poly;
    head=sent;
    tail=sent;
    len=0;
    return;
}

// Insert a particular node to a particular list number.
void lists::insert(node* HEAD)
{
    lst* temp=new lst;
    temp->next=sent;
    tail->next=temp;
    temp->prev=tail;
    sent->prev=temp;
    if(head==sent) head=tail;
    temp->poly=HEAD;
    tail=temp;
    len++;
    return;
}

// Copy a lists object into E.
void lists::copy(lists F)
{
    len=F.len;
    head=F.head;
    tail=F.tail;
    sent=F.sent;
    return;
}

// Polynomial adding function which works in O(n+m) time.
// Here n and m are the lengths of the polynomials being added.
void poly_add(node** HEAD,node** TAIL,node** SENT,node* HEAD1,node* TAIL1,node* SENT1,node* HEAD2,node* TAIL2,node* SENT2)
{
    node *temp1=HEAD1,*temp2=HEAD2;

    while(temp1!=SENT1 || temp2!=SENT2) {
        if(temp1==SENT1) { 
            (*TAIL)=insert_node(temp2->cof,temp2->exp,(*TAIL),(*SENT));
            if((*HEAD)==(*SENT)) {
                (*HEAD)=(*TAIL);   (*SENT)->next=(*HEAD);
                (*HEAD)->prev=(*SENT);
            }    
            temp2=temp2->next;
        }
        else if(temp2==SENT2) { 
            (*TAIL)=insert_node(temp1->cof,temp1->exp,(*TAIL),(*SENT));
            if((*HEAD)==(*SENT)) {
                (*HEAD)=(*TAIL);   (*SENT)->next=(*HEAD);
                (*HEAD)->prev=(*SENT);
            }
            temp1=temp1->next;
        }
        else { 
            if(temp1->exp<temp2->exp) {
                (*TAIL)=insert_node(temp1->cof,temp1->exp,(*TAIL),(*SENT));
                temp1=temp1->next;
            }
            else if(temp1->exp>temp2->exp) {
                (*TAIL)=insert_node(temp2->cof,temp2->exp,(*TAIL),(*SENT));
                temp2=temp2->next;
            }
            else {
                if(temp1->cof+temp2->cof!=0) {
                    (*TAIL)=insert_node(temp1->cof+temp2->cof,temp1->exp,(*TAIL),(*SENT));
                }
                temp1=temp1->next;
                temp2=temp2->next;
            }
            if((*HEAD)==(*SENT)) {
                (*HEAD)=(*TAIL);   (*SENT)->next=(*HEAD);
                (*HEAD)->prev=(*SENT);
            }
        }
    }
    return;
}

// Polynomial multiplication function which works in O(m*n*log n) time.
// Here n and m are the lengths of both the polynomials.
void poly_mult(node** HEAD,node** TAIL,node* HEAD1,node* TAIL1,node* HEAD2,node* TAIL2,int n,int m)
{
    // Implement the Divide and Conquer Algorithm here !!!
    // Implement this as soon as possible now !!!
    
    // Declaring of a empty set of lists to store n polynomials.
    lists E;

    // Filling of the set of n polynomials.
    node* temp=HEAD1;
    while(temp!=SENT1) {
        node *s,*h,*t;
        s=make_node(0,-1);
        s->next=s;  s->prev=s;
        h=s; t=s;
        int a=temp->cof,e=temp->exp;
        node* ta=HEAD2;
        while(ta!=SENT2) {
            t=insert_node(a*(ta->cof),e+(ta->exp),t,s);
            if(h==s) { h=t; h->prev=s; s->next=h; }
            ta=ta->next;
        }
        E.insert(h);
        temp=temp->next;
    }
    cerr<<"Formed E"<<" ";

    // Adding using divide and conquer strategy.
    while(E.len>1) {
        lists F;
        lst* temp=E.head;
        while(temp!=E.sent) {
            if(temp==E.tail) {
                F.insert(temp->poly);
                temp=temp->next;
            }
            else {
                lst* k=temp->next;
                node *s,*h,*t;
                s=make_node(0,-1);
                s->next=s;  s->prev=s;
                h=s; t=s;
                poly_add(&h,&t,&s,temp->poly,temp->poly->prev->prev,temp->poly->prev,k->poly,k->poly->prev->prev,k->poly->prev);
                F.insert(h);
                temp=temp->next->next;
            }
            cerr<<"adds"<<" ";
        }
        E.copy(F);
        cerr<<"Completed a iteration"<<" ";
    }

    print_all(E.head->poly,E.head->poly->prev);
    // Giving the output values.
    (*HEAD)=(E.head)->poly;
    (*TAIL)=(E.head)->poly;
    SENT=((E.head)->poly)->prev;

    return;
}

// The main() contains the exact control flow of the program.
int32_t main()
{
    /* Setting up the Sentinel Node for zero sized polynomial */
    
    SENT->next=SENT;       SENT->prev=SENT;
    SENT1->next=SENT1;     SENT1->prev=SENT1;
    SENT2->next=SENT2;     SENT2->prev=SENT2;
    
    /* Taking the Required Input */
    
    int n;  cin>>n;
    int m;  cin>>m;
    
    struct node *HEAD1=SENT1,*TAIL1=SENT1;
    struct node *HEAD2=SENT2,*TAIL2=SENT2;
    
    for(int i=0;i<n;i++) {
        int a,b;
        cin>>a>>b;
        TAIL1=insert_node(a,b,TAIL1,SENT1);
        if(HEAD1==SENT1) {
            HEAD1=TAIL1;    SENT1->next=HEAD1;
            HEAD1->prev=SENT1;  
        }    
    }
    
    for(int i=0;i<m;i++) {
        int a,b;
        cin>>a>>b;
        TAIL2=insert_node(a,b,TAIL2,SENT2);
        if(HEAD2==SENT2) {
            HEAD2=TAIL2;    SENT2->next=HEAD2;
            HEAD2->prev=SENT2;  
        }
    }

    /* Solving of the Problem Statement */
    
    struct node *HEAD=SENT,*TAIL=SENT;
    cerr<<"Going to function"<<" ";
    if(n<m) poly_mult(&HEAD,&TAIL,HEAD1,TAIL1,HEAD2,TAIL2,n,m);
    else poly_mult(&HEAD,&TAIL,HEAD2,TAIL2,HEAD1,TAIL1,m,n);
    cerr<<"Back to main"<<" ";
    print_all(HEAD,SENT);

    /* Ending of the Program */
    
    cerr<<"Program finished"<<" ";
    return 0;
}
