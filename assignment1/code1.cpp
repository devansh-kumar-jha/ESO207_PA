#include<bits/stdc++.h>
using namespace std;
#define int long long int

struct node {
    node *prev;
    int cof;
    int exp;
    node *next;
};

node* make_node(int cof,int exp)
{
    node *temp=new node;
    temp->cof=cof;
    temp->exp=exp;
    return temp;
}

node* insert_node(int cof,int exp,struct node* TAIL)
{
    node *temp=make_node(cof,exp);
    temp->next=NULL;
    temp->prev=TAIL;
    if(TAIL!=NULL) TAIL->next=temp;
    TAIL=temp;
    return TAIL;
}

void free_all(node *HEAD,node *TAIL)
{
    node *temp=HEAD;
    while(temp!=NULL) {
        if(temp->prev!=NULL) free(temp->prev);
        temp=temp->next;
    }
    free(TAIL);
    return;
}

void print_all(node* HEAD)
{
    node* temp=HEAD;
    while(temp!=NULL) {
        cout<<temp->cof<<" "<<temp->exp<<"/n";
        temp=temp->next;
    }
    return; 
}

void make_list(node** HEAD,node** TAIL,node* HEAD1,node* TAIL1,node* HEAD2,node* TAIL2)
{
    node *temp1=HEAD1,*temp2=HEAD2;

    while(temp1!=NULL || temp2!=NULL) {
        if(temp1==NULL) { 
            (*TAIL)=insert_node(temp2->cof,temp2->exp,(*TAIL));
            if(HEAD==NULL) HEAD=TAIL;
            temp2=temp2->next;
        }
        else if(temp2==NULL) { 
            (*TAIL)=insert_node(temp1->cof,temp1->exp,(*TAIL));
            if((*HEAD)==NULL) (*HEAD)=(*TAIL);
            temp1=temp1->next;
        }
        else { 
            (*TAIL)=insert_node(temp1->cof+temp2->cof,temp1->exp,(*TAIL));
            if((*HEAD)==NULL) (*HEAD)=(*TAIL);
            temp1=temp1->next;
            temp2=temp2->next;
        }
    }
    return;
}

// int lsearch(node* HEAD,int find)
// {
//     node* temp=HEAD;
//     while(temp!=NULL) {
//         if(temp->cof==find) return 1;
//         temp=temp->next;
//     }
//     return 0;
// }

int main()
{
    int n=9;  cin>>n;
    int m=9;  cin>>m;
    // scanf("%d",&n);
    
    struct node *HEAD1=NULL,*TAIL1=NULL;
    struct node *HEAD2=NULL,*TAIL2=NULL;
    
    for(int i=0;i<n;i++) {
        int a=7,b=7;   //scanf("%d ",&a);
        cin>>a>>b;
        TAIL1=insert_node(a,b,TAIL1);
        if(HEAD1==NULL) HEAD1=TAIL1;
    }
    
    for(int i=0;i<m;i++) {
        int a=7,b=7;   //scanf("%d ",&a);
        cin>>a>>b;
        TAIL2=insert_node(a,b,TAIL2);
        if(HEAD2==NULL) HEAD2=TAIL2;
    }

    /* Write the code */
    
    struct node *HEAD=NULL,*TAIL=NULL;
    make_list(&HEAD,&TAIL,HEAD1,TAIL1,HEAD2,TAIL2);
    print_all(HEAD);
    
    free_all(HEAD,TAIL);
    free_all(HEAD1,TAIL1);
    free_all(HEAD2,TAIL2);
    HEAD1=NULL;   TAIL1=NULL;
    HEAD2=NULL;   TAIL2=NULL;
    return 0;
}
