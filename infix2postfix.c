#include<stdio.h>
#include<stdlib.h>
#include<tm_stack.h>

void appendToPostfix(char m,char *ptf,int *elementIndex)
{
ptf[*elementIndex]=m;
*elementIndex=*elementIndex+1;
ptf[*elementIndex]='\0';
}
int isOperator(char m)
{
return m=='+' || m=='-' || m=='/' || m=='*';
}
int isOperand(char m)
{
return !isOperator(m);
}

int getPrecedenceLevel(char m)
{
if(m=='*' || m=='/') return 2;
if(m=='+' || m=='-') return 1;
return 0;
}


int main()
{
bool succ;
char infix[51],postfix[51];
char *m,elem;
int i,elementIndex;
printf("Enter infix expression : ");
scanf("%s",infix);
postfix[0]='\0';
elementIndex=0;
i=0;
Stack *stack;
stack=createStack(&succ);
while(infix[i]!='\0')
{

elem=infix[i];
if(elem=='(')
{
m=(char *)malloc(sizeof(char));
*m=elem;
pushOnStack(stack,(void *)m,&succ);
}
else 
if(elem==')')
{
while(1)
{
m=(char *)popFromStack(stack,&succ);
if(*m=='(')
{
free(m);
break;
}
appendToPostfix(*m,postfix,&elementIndex);
free(m);
}
}
else
if(isOperand(elem))
{
appendToPostfix(elem,postfix,&elementIndex);
}
else //now 100% elem is operator
{
if(isStackEmpty(stack) || *(char *)getFromTopOfStack(stack,&succ)=='(')
{
m=(char *)malloc(sizeof(char));
*m=elem;
pushOnStack(stack,(void *)m,&succ);
}
else
{

m=(char *)getFromTopOfStack(stack,&succ);
if(getPrecedenceLevel(*m)<getPrecedenceLevel(elem))
{
m=(char *)malloc(sizeof(char));
*m=elem;
pushOnStack(stack,(void *)m,&succ);
}
else
{
while(1) //popping loop starts
{
if(isStackEmpty(stack)) break;
m=(char *)getFromTopOfStack(stack,&succ);
if(*m=='(') break;
if(getPrecedenceLevel(*m)<getPrecedenceLevel(elem)) break;
m=(char *)popFromStack(stack,&succ);
appendToPostfix(*m,postfix,&elementIndex);
free(m);
} //poping loop ends
m=(char *)malloc(sizeof(char));
*m=elem;
pushOnStack(stack,(void *)m,&succ);
}

}


} //operator part end

i++;
}//infix loop ends


while(!isStackEmpty(stack))
{
m=(char *)popFromStack(stack,&succ);
appendToPostfix(*m,postfix,&elementIndex);
free(m);
}
printf("Postfix expression is :\n%s",postfix);
return 0;
}