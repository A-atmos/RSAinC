#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
int save (int a[99])
{
    FILE *file;
        int i;
        char name[99];
        printf("Name of file:");
        scanf("%s",name);
        file=fopen(name,"w");
        if(file==NULL)
            printf("No file found");
        for (i=0;a[i]!='\0';i++)
            fprintf(file,"%d ",a[i]);
    fprintf(file,"\0");
    return 0;
}
int read(int a[99])
{
    FILE *file;
    int i=0;
    char fn[99];
    printf("Enter the name of file to open:");
    scanf("%s",fn);
    file=fopen(fn,"r");
    if(fopen==NULL)
        exit(0);
    for (i=0;a[i]!=EOF;i++)
    {
    fscanf(file," %d",&a[i]);
    }
    a[i]=EOF;
    return 0;
}
