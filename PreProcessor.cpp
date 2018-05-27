#include <iostream>
#include <stdlib.h>
#define null 0
using namespace std;
struct Node{char *c;Node *next;};
class stack
{
public: stack();
void push(char *c);
int pop(char * &c);
private:Node *top;
};
stack::stack()
{top=null;}
void stack::push(char *c)
{Node *node=new Node;
node->c=c;node->next=null;
if(top==null){top=node;return;}
node->next=top;
top=node;
}
int stack::pop(char *&data)
{if(top==null){return 0;}
Node *nd=top;
top=top->next;
data=nd->c;
delete nd;
return 1;
}
struct dNode
{
char *c; dNode *next;dNode *prev;
};
class queue
{
public : queue(); void push(char*);
int pop(char*&);void fpush(char*);
int rpop(char*&);
void clear();
private : dNode *front,*rear;
};
queue::queue()
{front=null;rear=null;
}
void queue::push(char* c)
{dNode *nd=new dNode; nd->c=c;nd->next=null;nd->prev=null;
if(front==null){
front=nd;rear=nd;return;
}nd->prev=rear;
rear->next=nd; rear=nd;
}
int queue::pop (char* &s)
{
if(front==null)return 0;
if(front==rear){dNode *n=front;front=null;rear=null;s=n->c;delete n;return 1;}
dNode *n=front;
front=front->next;
s=n->c;
delete n;
return 1;
}
void queue::fpush(char * c)
{
dNode *nd=new dNode;
nd->c=c;
nd->next=front;nd->prev=null;
if(front!=null)front->prev=nd;
front=nd;
if(rear==null)rear=front;
}
int queue::rpop(char*& c)
{
if(rear==null)return 0;
dNode *nd=rear;
c=nd->c;
if(rear->prev==null){front=null;rear=null;delete nd;return 1;}
rear=nd->prev;
delete nd;
return 1;
}
void queue::clear(){rear=null;front=null;}
class bstack : public stack
{public :int bpop(char*&);
stack buffer;void bpush();
};
int bstack::bpop(char*& s)
{if(pop(s)){buffer.push(s);return 1;}
return 0;
}
void bstack::bpush()
{char* ele;while(buffer.pop(ele))push(ele);}
//Data Structures End
//Variable Declaration Parser Code :
int vnum=47;
char *currentvar;
char* retVar()
{
char *c=new char[5];c[0]='v';c[1]='a';c[2]='r';c[3]=(char)(++vnum);c[4]='\0';
currentvar=c;
return c;
}
char* cmpVar()
{
return currentvar;
}
bstack expprocess(queue exp){int equalsnc(char*,char*);bstack output;
stack to;
queue of;
output.push(retVar());
char *com;
while(true)
{
exp.pop(com);
if(equalsnc(com,"pointer"))to.push("*");
 else if(equalsnc(com,"array")){
char *len=new char[10];
exp.pop(len);
if(equalsnc(len,"of")){exp.fpush(len);of.push("length");}
else of.push(len);}
else if(equalsnc(com,"of")){char *carrier;
while(output.bpop(carrier));
while(to.pop(carrier))output.push(carrier);
output.bpush();
}
else if(equalsnc(com,"to"))
{
char *carrier;
if(of.pop(carrier))
{output.push(")");
output.push("[");
output.push(carrier);
output.push("]");
while(of.pop(carrier)){output.push("[");output.push(carrier);output.push("]");}
while(output.bpop(carrier));
output.push("(");
output.bpush();}
}
else{char *carrier;
if(of.pop(carrier))
{output.push(")");
output.push("[");
output.push(carrier);
output.push("]");
while(of.pop(carrier)){output.push("[");output.push(carrier);output.push("]");}
while(output.bpop(carrier));
output.push("(");
output.bpush();}

while(output.bpop(carrier));
while(to.pop(carrier))output.buffer.push(carrier); output.push(com);output.bpush();break;
}
}
char *carrier;
while(exp.pop(carrier))output.buffer.push(carrier);
    return output;
}

int equalsnc(char* c1,char* c2)
{int length(char*);
 if(length(c1)!=length(c2))return 0;
 else
 {
 int l=length(c1);
for(int i=0;i<l;i++)if(toupper(c1[i])!=toupper(c2[i]))return 0;
 }
 return 1;
}

int length(char* c)
{   int i=0;
 while(c[i]!='\0')i++;
 return i;
}

void display(bstack s)
{
char *carrier;
while(s.bpop(carrier));
while (s.buffer.pop(carrier))cout<<carrier<<" ";
cout<<endl;
}
//Parser Ends
queue tokenize(bstack b)
{char *com;
queue exp;
while(b.bpop(com));
while(b.buffer.pop(com))
{char *token=new char[50];
int pos=0;int opos=0;char tc;
while((tc=com[opos++])!='\0')
{if(tc!='(' && tc!=')' && tc!=';' && tc!=',' && tc!='[' && tc!=']')token[pos++]=tc;
else{if(pos!=0){token[pos]='\0';exp.push(token);token=new char[50];}
token[0]=tc;token[1]='\0';
exp.push(token);
token=new char[50];pos=0;
}
}
if(pos!=0){token[pos]='\0';exp.push(token);}
delete com;
}
return exp;
}
int hasVar(char* c)
{
  if(c[0]=='v'&&c[1]=='a'&&c[2]=='r'){if(length(c)==4)return 1;}
  else if(c[0]=='&'&&c[1]=='v'&&c[2]=='a'&&c[3]=='r'){if(length(c)==5)return 2;}
return 0;
}
void repVar(char* &c,int type,int num)
{
c=new char[(type==1)?5:6];
int index=0;
if(type==2){index=1;c[0]='&';}
c[index++]='v';c[index++]='a';c[index++]='r';c[index++]=(char)(47+num);c[index++]='\0';

}
int main()
{char *token;void refgen(char*&);
bstack f_proc(queue);
queue tokenize(bstack);
bstack exp;
cout<<"Enter the Function Description : \n\n";
while(true){
token=new char[50];
cin>>token;
if(equalsnc(token,";"))break;
exp.push(token);}

cout<< "\n\nRequired Function Declaration :\n\n";
bstack ps=f_proc(tokenize(exp));
char *com;
if(ps.buffer.pop(com))
{
char *name=com; if(equalsnc(name,"&"))if(ps.buffer.pop(com)){refgen(com);name=com;}
if(ps.buffer.pop(com)){ cout<<"Unknown Error"; exit (0);}
while ( ps.bpop(com))if(equalsnc(com,cmpVar())){if(equalsnc(name,"&")){refgen(com);ps.push(com);}else ps.push(name);ps.buffer.pop(com);ps.bpush();break;}
}
int num=0;int type=0;
while(ps.bpop(com));while(ps.buffer.pop(com)){if(type=hasVar(com))repVar(com,type,++num);ps.push(com);}
display(ps);
return 0;
}
int canfunc_dec=0;
void refgen(char* &c)
{
 int n=length(c);
 char *d=new char[n+2];
 for(int i=n+1;i>0;i--)d[i]=c[i-1];
 d[0]='&';
c=d;
}
bstack f_proc(queue exp)
{queue takes;
queue returns;
char *com;char *fname;
queue mainexp;int state=0;
exp.pop(com);
 bool ref=false;
if(equalsnc(com,"["))
  {
ref=true;
int nb=0;
queue subexp;
while(exp.pop(com))
{
if(equalsnc(com,"]"))
{nb--;if(nb==-1){
 if(exp.pop(com)){cout<<"Unexpected : ]"; exit(0); }
 while(subexp.pop(com))exp.push(com);
 break;}
}
else if(equalsnc(com,"["))nb++;
subexp.push(com);
}
}
else exp.fpush(com);
while (exp.pop (com))
{
if(state==0)
{
if(equalsnc(com,"pointer")||equalsnc(com,"array")||equalsnc(com,"to")||equalsnc(com,"of"))mainexp.push(com);
else if(equalsnc(com,"function"))
{if(mainexp.rpop(com))if(equalsnc(com,"of")){cout<<"Error : Cannot declare array of functions";exit(0);}
else {if(canfunc_dec==0)canfunc_dec=-1;mainexp.push(com);}
exp.pop(com);
if(equalsnc(com,"which")){fname=null;}
else {fname=com;exp.pop(com);
if(equalsnc(com,"which"));else {cout<<"Error : Format Exception : which expected";exit(0);}
}
exp.pop(com);if(equalsnc(com,"takes"))state=1;else if(equalsnc(com,"returns"))state=3;else {cout<<"Error : Format Exception : takes or returns expected"; exit(0);}
}
else {
  //Checking for reference
if(equalsnc(com,"[")||equalsnc(com,"]")){mainexp.push(com);continue;}

//check ends
        char *len=com;
if(exp.pop(com)){
if(equalsnc(com,"of")){exp.fpush(com);mainexp.push(len);continue;}
else{exp.fpush(com);com=len;}
}
mainexp.push(com);bstack squeue=expprocess(mainexp);
while(exp.pop(com))squeue.buffer.push(com);
if(ref)squeue.buffer.push("&");
return squeue;
}

}
else if(state==1){
queue subexp;int nb=0;
if(equalsnc(com,"("))
{while(exp.pop(com))if(equalsnc(com,")")){nb--;if(nb==-1){nb=-2;break;}else subexp.push(com);}
else if(equalsnc(com,"(")){subexp.push(com);nb++;}
else subexp.push(com);
}
else {cout<<"Error : Format Exception : ( expected";exit (0);}
if(exp.pop (com)){if(!equalsnc(com,"returns")){cout<<"Error : Format Exception"; exit(0);}else state=3;}
if(nb!=-2){cout<<"Error : Parentheses Mismatch";exit(0);}
nb=0;
if(subexp.pop(com))
{subexp.fpush(com);
queue argument;
subexp.push(",");
while(subexp.pop(com))
{if(equalsnc(com,"(")){nb++;argument.push(com);}
else if(equalsnc(com,")")){nb--;argument. push(com);if(nb<0){cout<<"Error : Parentheses mismatch";exit(0);}}
else if(equalsnc(com,",")&&nb==0){
canfunc_dec--;
bstack parg=f_proc(argument);
canfunc_dec++;
char *name=null;
if(parg.buffer.pop(com))
{ if(equalsnc(com,"&"))if(parg.buffer.pop(com))refgen(com);
    name=com;}
if(parg.buffer.pop(com)){cout<<"Error : Invalid Variable name";exit(0);}
while(parg.bpop(com)){if(equalsnc(com,cmpVar())){
if(canfunc_dec==0)
{if(name==null)name=com;
else if(equalsnc(name,"&")){refgen(com);name=com;}
parg.push(name);
}
else if (name != null ) {if(equalsnc(name,"&")){parg.push(name);}else {cout<<"Unexpected Variable name";exit(0);}}
else if(parg.bpop(com)){
if(equalsnc(com,"(")){
char *prevb,*vn;
parg.buffer.pop (prevb);
parg.buffer.pop(vn);
if(parg.buffer.pop(com)){if(equalsnc(com,")"))prevb=null; else parg.buffer.push(com);}
if(prevb!=null)parg.push(prevb);
parg.buffer.push(vn);
}
else {parg.push(com);parg.buffer.pop(com);}
}
parg.buffer.pop(com);parg.bpush();break;}
}

while(parg.bpop(com));
argument.clear();
while(parg.buffer.pop (com))takes.push(com);
takes.push(",");
}
else argument.push(com);
}}
if(state==1)break;
}
else if(state==3)
{int nb=0;queue subexp;
if (equalsnc(com,"("));
else {cout<<"Error : Format Exception : ( expected";
if(fname!=null)cout<<" in : "<<fname;
exit(0);}
while(exp.pop(com))
{if(equalsnc(com,"("))nb++;
else if(equalsnc(com,")")){nb--;if(nb==-1)break;}
subexp.push(com);}
if (nb!=-1){cout<<"Error : Parentheses Mismatch";exit(0);}
if(subexp.pop(com))
{subexp.fpush(com);
subexp.push(",");
queue argument;nb=0;
while(subexp.pop(com))
{
if(equalsnc(com,"("))nb++;
else if(equalsnc(com,")")){nb--;
if(nb<0){cout<<"Error : Parentheses Mismatch";exit(0);}}
else if(equalsnc(com,",")&&nb==0){
while(argument.pop(com))returns.push(com);
if(subexp.pop(com)){cout<<"Error : Cannot have more than 1 return value";exit(0);}
break;
}argument.push(com);}}
break;
}
}
if(returns.pop(com)){returns.fpush(com);}else returns.push("void");
canfunc_dec--;
bstack ms=f_proc(returns);
canfunc_dec++;
if (ms.buffer.pop(com)){if(equalsnc(com,"&")&&!ms.buffer.pop(com)){
while(ms.bpop(com))if(equalsnc(com,cmpVar())){ms.push("&");ms.bpush();break;}

}else {cout<<"Error : Unexpected Variable name";exit(0);}}
while(ms.bpop(com))
if(equalsnc(com,cmpVar())){
ms.push("(");
if (canfunc_dec<0) if ( !mainexp.pop(com)){cout<<"Error : Cannot declare function here";
exit (0);
}
else mainexp.fpush(com);
mainexp.push("func");
bstack mex=expprocess(mainexp);
if(mex.buffer.pop(com)){cout<<"Unknown Error Occured";exit(0);}
while(mex.bpop(com));
if(mex.buffer.pop(com)&&!equalsnc(com,"func")){cout<<"Unknown Error Occured";exit(0);}
while(mex.buffer.pop(com)){
/*if(equalsnc(com,cmpVar()))
{if ( canfunc_dec==0){
if(fname==null){ms.push(com);}else{ms.push(fname);}} else {ms.push(com);}continue;
}*/
ms.push(com);
}
ms.buffer.pop(com);
ms.push(")");ms.push("(");
takes.rpop(com);
while(takes.pop(com))ms.push(com);ms.push(")");
ms.bpush();
if(fname != null) ms.buffer.push(fname);
if(ref)ms.buffer.push("&");
return ms;
}
}
