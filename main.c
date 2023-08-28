#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define type float
typedef struct
{
    type data;
    struct Node* next;
} Node;
typedef struct
{
    Node*top;
} Stack;
Node* newnode(float x)
{
    Node* n=malloc(sizeof(Node));
    n->data=x;
    n->next=NULL;
    return n;
}
Stack* initialize()
{
    Stack*s=malloc(sizeof(Stack));
    s->top=NULL;
    return s;
}
float pop (Stack*s)
{
    Node * n;
    n=s->top;
    s->top=n->next;
    float x=n->data;
    free(n);
    return x;
}
void push(Stack*s, float value)
{
    Node*p=newnode(value);
    p->next=s->top;
    s->top=p;
}
float peak (Stack*s)
{
    return s->top->data;
}
int isempty (Stack*s)
{
    return (s->top==NULL);
}
void display(Stack*s)
{
    Stack * b=initialize();
    while(!isempty(s))
    {
        float x=pop(s);
        printf("%.3f ",x);
        push(b,x);
    }
    while(!isempty(b))
        push(s,pop(b));
}
int isOperator (char c)
{
    return (c=='+'||c=='/'||c=='*'||c=='^'||c=='('||c==')');
}
char* spacer (char * str)
{
    char*p=malloc(strlen(str)+20);
    int i,j=0;
    for (i=0;i<strlen(str);i++)
    {
        if(isdigit(str[i]))
        {
            p[j++]=str[i];
            if(!isdigit(str[i+1]) && str[i+1]!='.')
                p[j++]=' ';
        }
        else if(isOperator(str[i]))
        {
            p[j++]=str[i];
            p[j++]=' ';
        }
        else if(str[i]=='.')
        {
            p[j++]=str[i];
        }
        else if(str[i]=='-')
        {
            if(i==0 || isOperator(str[i-1]) )
            {
                if(str[i-1]!= ')' )
                   p[j++]=str[i];
                else
                {
                    p[j++]=str[i];
                    p[j++]=' ';
                }
            }
           else
            {
                p[j++]=str[i];
                p[j++]=' ';
            }
        }
    }
    p[j]='\0';
    return p;
}
int isnumber (char *c)
{
    if (isdigit(c[0]))
            return 1;
    else if (c[0]=='-' && isdigit(c[1]))
            return 1;
        return 0;
}
int priority (char c)
{
    if (c=='(')
        return 5;
    else if (c=='^')
        return 4;
    else if (c=='*'||c=='/')
        return 3;
    else if (c=='+'||c=='-')
        return 2;
    return 0;
}
char*infixTopostfix(char *infix)
{
    char* post=malloc(strlen(infix));
    Stack*s=initialize();
    int i=0,j;
    char x;
    char *t=strtok(infix," ");
    while(t)
    {
        if (isnumber(t))
        {
            for (j=0;j<strlen(t);j++)
            {
                 post[i++]=t[j];
            }
            post[i++]=' ';
        }
        else if (isempty(s))
        {
             push(s,(float)t[0]);
        }
        else if (t[0]==')')
        {
            while (!isempty(s) && (char)peak(s)!='(')
                {
                    x=(char)pop(s);
                    post[i++]=x;
                    post[i++]=' ';
                }
            (char)pop(s);
        }
        else
        {
            while(!isempty(s) && (char)peak(s)!='(' && priority(*t)<= priority((char)peak(s)))
            {
                    x=(char)pop(s);
                    post[i++]=x;
                    post[i++]=' ';
            }
            push(s,(float)t[0]);
        }
       t=strtok(NULL," ");
    }
    while(!isempty(s))
    {
        x=(char)pop(s);
        post[i++]=x;
        post[i++]=' ';
    }
    post[i]='\0';
    return post;
}
float calculate(char x,float a,float b)
{
    if (x=='+')
        return(a+b);
    else if (x=='-')
        return(a-b);
    else if (x=='*')
        return(a*b);
    else if (x=='^')
        return(pow(a,b));
    else if (x=='/')
        return(a/b);
    return 0;
}
float evaluatePostfix(char* postfix)
{
    Stack*s=initialize();
    float a,b,val;
    char*token=strtok(postfix," ");
    while (token)
    {
        if (isnumber(token))
            push(s,atof(token));
        else
        {
            a=pop(s);
            b=pop(s);
            val=calculate(token[0],b,a);
            push(s,val);
        }
        token=strtok(NULL," ");
    }
   return pop(s);
}
int main()
{
    char str[40];
    printf("Please enter infix : ");
    gets(str);
    char* spacedinfix=spacer(str);
    printf("Spaced infix : %s\n",spacedinfix);
    char* postfix=infixTopostfix(spacedinfix);
    printf("Postfix : %s\n",postfix);
    printf("The value : %.6f",evaluatePostfix(postfix));
    return 0;
}
