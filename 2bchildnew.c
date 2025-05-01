#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int main(int argc, char *argv[])
{
FILE *file;
int c=0,n,array[10],i=0;
printf("File name:%s",argv[1]);
file = fopen(argv[1],"r");
//while((c=getc(file))!=EOF)
// while(fscanf(file, "%d",&array[c])!=EOF)
/*for(c=0; c<5; c++)
{
fscanf(file,"%d", &array[c]);
printf("%d ",array[c]);
c=c++;
} */
while((c=getc(file))!=EOF){
fscanf(file,"%d",&array[c]);
printf("%d",array[c]);
i++;
}
printf("\n %d",i);
n=i;
printf("\n %d",n);
}

