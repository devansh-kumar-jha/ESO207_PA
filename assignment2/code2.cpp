/// Algorithm
/// if(twonode) -> if(val>=x) -> go left
///             -> else       -> go middle
/// if(threenode) -> if(val1>=x)      -> go left
///               -> else if(val2>=x) -> go middle
///               -> else             -> go right
/// if(leaf) -> split , repair and return
/// if(null) -> return
/// Iterations = h(T)+h(T)+h(T)

// #include<bits/stdc++.h>
// using namespace std;
// using int long long int

#include "twth.hpp"

void Split(twth* th,int x,twth* th1,twth* th2)
{
    twthnode* cut=th->get(x);
    ret_split* ans=th->split(cut);
    th1->set(ans->n1);
    th2->set(ans->n2);
    return;
}

int32_t main()
{
    twth th;
    int n;  cin>>n;
    int p,x;  cin>>p;
    for(int i=0;i<n;i++) { cin>>x; th.insert(x); }

    twth th1,th2;
    Split(&th,x,&th1,&th2);    
    th1.display();
    th2.display();

    th1.clear();
    th2.clear();
    th.clear();
    return 0;
}
