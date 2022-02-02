#include<stdio.h>
#include<stdlib.h>
#include<tm_stack.h>
#include<tm_queue.h>
typedef struct __element
{
int num;
char m;
}Element;

int evaluatingExpression(int leftOperand,char opr,int rightOperand)
{
if(opr=='+') return leftOperand+rightOperand;
if(opr=='-') return leftOperand-rightOperand;
if(opr=='*') return leftOperand*rightOperand;
if(opr=='/') return leftOperand/rightOperand;
}

void addToPostfixQueue(Queue *queue,char m,int num,bool *succ)
{
Element *e;
e=(Element *)malloc(sizeof(Element));
e->num=num;
e->m=m;
addToQueue(queue,(void *)e,succ);
}

int isOperator(char m)
{
return m=='+' || m=='-' || m=='*' || m=='/';
}

int getPrecedenceLevel(char m)
{
if(m=='/' || m=='*') return 2;
return 1;
}

int main()
{
Element *e;
bool succ;
char infix[101];
char *m,elem;
int i;
Stack *stack;
Queue *queue;
stack=createStack(&succ);
queue=createQueue(&succ);
printf("Enter infix expression: ");
scanf("%s",infix);
int num,result,leftOperand,rightOperand;
char oper;
i=0;
while(infix[i]!='\0')
{
elem=infix[i];
i++;
if(elem=='(')
{
m=(char *)malloc(sizeof(char));
*m=elem;
pushOnStack(stack,(void *)m,&succ);
continue;
}
if(elem==')')
{
while(1)
{
m=(char *)popFromStack(stack,&succ);
if(*m=='(')
{
free(m); break;
}
addToPostfixQueue(queue,*m,0,&succ);
free(m);
}
continue;
}
if(isOperator(elem))
{

while(1)
{
if(isStackEmpty(stack)) break;
m=(char *)getFromTopOfStack(stack,&succ);
if(*m=='(') break;
if(getPrecedenceLevel(*m)<getPrecedenceLevel(elem)) break;
m=(char *)popFromStack(stack,&succ);
addToPostfixQueue(queue,*m,0,&succ);
free(m);
}

m=(char *)malloc(sizeof(char));
*m=elem;
pushOnStack(stack,(void *)m,&succ);
continue;
}//Operator part ends

// now 100% operand
num=elem-'0';
while(infix[i]>='0' && infix[i]<='9')
{
elem=infix[i];
i++;
num=num*10+(elem-'0');
}

addToPostfixQueue(queue,' ',num,&succ);


}//infix loop ends

while(!isStackEmpty(stack))
{
m=(char *)popFromStack(stack,&succ);
addToPostfixQueue(queue,*m,0,&succ);
free(m);
}

while(!isQueueEmpty(queue)) //evaluting postfix expression
{
e=(Element *)removeFromQueue(queue,&succ);
if(e->m==' ') pushOnStack(stack,(void *)e,&succ);
else
{
oper=e->m;
free(e);
e=popFromStack(stack,&succ);
rightOperand=e->num;
free(e);
e=popFromStack(stack,&succ);
leftOperand=e->num;
free(e);
result=evaluatingExpression(leftOperand,oper,rightOperand);
e=(Element *)malloc(sizeof(Element));
e->num=result;
e->m=' ';
pushOnStack(stack,(void *)e,&succ);
}
}

e=(Element *)popFromStack(stack,&succ);
result=e->num;
free(e);
printf("ans is :(%d)",result);

destroyStack(stack);
destroyQueue(queue);
return 0;
}