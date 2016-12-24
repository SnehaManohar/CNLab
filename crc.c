#include<stdio.h>
#include<string.h>
#define N strlen(g)
 
char d[32],cs[32],d1[32],cs1[32],g[35];
int n,i,k,error;
int codecheck();
void xor(){
    for(k = 1;k < N; k++)
    cs[k] = (( cs[k] == g[k])?'0':'1');
}
void xor1(){
    for(k = 1;k < N; k++)
    cs1[k] = (( cs1[k] == g[k])?'0':'1');
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
void crc1(){
    for(i=0;i<N;i++)
        cs1[i]=d1[i];
    do{
        if(cs1[0]=='1')
            xor1();
        for(k=0;k<N-1;k++)
            cs1[k]=cs1[k+1];
        cs1[k]=d1[i++];
    }while(i<=n+N-1);
}
int codecheck(){
for(i=0;i<strlen(cs1);i++){
//printf("\n%s is cs1",cs1);
if(cs1[i]!='0'){
//	printf("\n%c not zero",cs1[i]);
	return 0;
}
}
return 1;

}
int main()
{
    printf("\nEnter data : ");
    scanf("%s",d);
    printf("\nEnter Generatng polynomial :");
    scanf("%s",g);
    n=strlen(d);
    for(i=n;i<n+N-1;i++)
        d[i]='0';
    //printf("\nModified data is : %s",d);
    crc();
    printf("\nChecksum is : %s",cs);
    for(i=n;i<n+N-1;i++)
        d[i]=cs[i-n];
    printf("\nFinal codeword sent  is : %s",d);
    printf("\nEnter data recieved: ");
    scanf("%s",d1);
    for(i=n;i<n+N-1;i++)
        d1[i]=cs[i-n];
	//printf("\nModified data is : %s",d1);
    crc1();
    //printf("\nChecksum is : %s",cs);
    //printf("\nChecksum1 is : %s",cs1);

    if(codecheck())
	printf("\ncorrect data recieved\n");
    else
	{for(i=0;i<n;i++){
	if(d[i]!=d1[i]){
	error=i;
	break;
	}
	}
	printf("error at %d\n",error+1);
        return 0;
}
}
