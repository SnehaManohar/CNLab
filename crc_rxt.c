#include<stdio.h>
#include<string.h>
#define N strlen(g)
 
char d[32],cs[32],g[]="1011";
int n,i,k;
 
void xor(){
    for(k = 1;k < N; k++)
    cs[k] = (( cs[k] == g[k])?'0':'1');
}
 
void crc(){
    for(i=0;i<N;i++)
        cs[i]=d[i];
    do{
        if(cs[0]=='1')
            xor();
        for(k=0;k<N-1;k++)
            cs[k]=cs[k+1];
        cs[k]=d[i++];
    }while(i<=n+N-1);
}
 
int main()
{
    printf("\nEnter data : ");
    scanf("%s",d);
    printf("\nGeneratng polynomial : %s",g);
    n=strlen(d);
    for(i=n;i<n+N-1;i++)
        d[i]='0';
    printf("\nModified data is : %s",d);
    crc();
    printf("\nChecksum is : %s",cs);
    for(i=n;i<n+N-1;i++)
        d[i]=cs[i-n];
    printf("\nFinal codeword is : %s",d);
    printf("\nTest error detection 0(yes) 1(no)? : ");
    scanf("%d",&i);
    if(i==0)
    {
        do{
            printf("\nEnter the position where error is to be inserted : ");
            scanf("%d",&i);
        }while(i==0 || i>n+N-1);
        d[i-1]=(d[i-1]=='0')?'1':'0';
        printf("\nErroneous data : %s\n",d);
    }
    crc();
    for(i=0;(i<N-1) && (cs[i]!='1');i++);
        if(i<N-1)
            printf("\nError detected\n\n");
        else
            printf("\nNo error detected\n\n");
        return 0;
}
