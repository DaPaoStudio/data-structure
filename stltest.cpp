#include <iostream>
#include <string>
#include <map>
#include <stack>
#include <queue>
#include <algorithm>
using namespace std;

typedef struct tte
{
    int data;
    char c;
} tte;

int ca(tte &t1, tte &t2)
{
    return t1.data < t2.data;
}
int main(void)
{
    /*
    string s;
    cin>>s;
    string s2;
    cin>>s2;
    printf("%d",s.find(s2));//kmp
    int t;
    cin>>t;
    cout<<t<<endl;
    */

    /*
    stack<int> a;//stack
    int x = 10;
    a.push(x);
    //a.pop();
    printf("%d",a.top());
    a.pop();
    printf(" %d",a.empty());
    */

    /*
    queue<tte> b;
    tte t1;
    t1.data = 100;
    b.push(t1);
    cout<<b.front().data<<endl;
    b.pop();
    cout<<b.empty()<<endl;
    */
    /*
   int x[5]={5,4,3,2,1};
   sort(x,x+5);
   for(int i = 0;i<=4;i++)
    cout<<x[i];
    cout<<'\n';
    tte r[10];
    for(int i = 0;i<=9;i++)
        r[i].data = 9-i;
    sort(r,r+10,ca);
    for(int i = 0;i<=9;i++)
    cout<<r[i].data;
    */
    /*
   vector <int> v1(100);
   v1[101]= 10;
   //v1.push_back(11);
   cout<<v1[101]<<endl;
   */
    /*
  tte *t;
  t = (tte*)malloc(sizeof(tte));
  t->data = 19;
  cout<<t->data;
  */
    map<char,int> m;
    m['a'] = 10;
    cout<<m['a'];
    cout<<(m.find('a')==m.end());
}