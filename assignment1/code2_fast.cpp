#include<bits/stdc++.h>
using namespace std;
#define int long long int


// Self Referential Structure for the Doubly Linked List.
struct node {
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


// Releasing the memory used in a Doubly Linked List.
void free_all(node *HEAD,node *TAIL,node* S)
{
    node *temp=HEAD;
    while(temp!=S) {
        if(temp->prev!=S) free(temp->prev);
        temp=temp->next;
    }
    free(TAIL);
    return;
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



// This is the main problem solver function which implements the O(n*m*m) algorithm.
// This will take the two polynomials and also 2 pointers for the output polynomial.
void make_list(node** HEAD,node** TAIL,node* HEAD1,node* TAIL1,node* HEAD2,node* TAIL2)
{
    node* temp1=HEAD1;
    while(temp1!=SENT1) {
        node *temp2=HEAD2,*temp=(*HEAD);
        while(temp2!=SENT2) {
            while(temp!=SENT && temp->exp<(temp1->exp)+(temp2->exp)) temp=temp->next;
            if(temp==SENT) {
                (*TAIL)=insert_node((temp1->cof*temp2->cof),(temp1->exp+temp2->exp),(*TAIL),SENT);
                if((*HEAD)==SENT) {
                    (*HEAD)=(*TAIL);  SENT->next=(*HEAD);
                    (*HEAD)->prev=SENT;
                }
                temp=(*TAIL);
            }
            else if(temp->exp==(temp1->exp)+(temp2->exp)) temp->cof += (temp1->cof)*(temp2->cof);
            else {
                insert_node((temp1->cof*temp2->cof),(temp1->exp+temp2->exp),temp->prev,temp);
                if((*HEAD)==SENT) {
                    (*HEAD)=(*TAIL);  SENT->next=(*HEAD);
                    (*HEAD)->prev=SENT;
                }
                temp=temp->prev;
            }
            temp2=temp2->next;
        }
        temp1=temp1->next;
    }

    node* temp=(*HEAD);
    if((*HEAD)->cof==0) (*HEAD)=(*HEAD)->next;
    if((*TAIL)->cof==0) (*TAIL)=(*TAIL)->prev;
    while(temp!=SENT) {
        if(temp->cof==0) {
            (temp->prev)->next=temp->next;
            (temp->next)->prev=temp->prev;
            node* a=temp;
            temp=temp->next;
            free(a);
        }
        else temp=temp->next;
    }

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
    make_list(&HEAD,&TAIL,HEAD1,TAIL1,HEAD2,TAIL2);
    print_all(HEAD,SENT);
    
    /* Releasing the Memory Used */
    
    free_all(HEAD,TAIL,SENT);
    free_all(HEAD1,TAIL1,SENT1);
    free_all(HEAD2,TAIL2,SENT2);
    
    HEAD1=NULL;   TAIL1=NULL;
    HEAD2=NULL;   TAIL2=NULL;
    HEAD =NULL;   TAIL =NULL;

    free(SENT1);
    free(SENT2);
    free(SENT);

    /* Ending of the Program */
    
    return 0;
}
