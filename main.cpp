//created by Natalia

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/stat.h>
using namespace std;

struct stat st = {};

void ReadPoem(int size , char buf[]);
long long int Count_change(char buf[], int size, char* text[]);
void OutputFile(char* text[],long long int nlines);
int AlphEncoding(char chr);
const void Sort(char* text[],long long int nlines);
int ComparatorStr(const void* ptr1,const void* ptr2);


int main()
{
stat("poem.txt", &st);
int size = st.st_size +1;
char * buf = (char*) calloc(size, sizeof(char));
char** text = (char**)calloc(size,sizeof(char*));


ReadPoem(size, buf);
long long int nlines = Count_change(buf, size, text);
printf("%ld", nlines);
//Sort(text , nlines);
printf("\nmeow");
OutputFile(text, nlines);







free(text);
text = NULL;
free(buf);
buf = NULL;
return 0;
}

void ReadPoem(int size , char buf[])
{

    FILE* onegin = fopen("poem.txt", "r");

    if (onegin == NULL)
    {
        printf("Cannot open file");
        return;
    }

    fread(buf, sizeof(char), size,onegin);
    buf [size] = '\n';
    fclose(onegin);
}

long long int Count_change(char buf[], int size, char* text[])
{
    long long int nlines = 1;
    int n = 1;
    text[0] = &buf[0];
    for (int i = 0; i < size; i++)
    {
        if (buf[i] == '\n')
        {
            nlines++;
            text[n] = &buf[i+1];
            buf[i] = '\0';
            n++;
        }
    }

    return nlines;
}
int AlphEncoding(char chr)
{

    char alph[67]={"ÀÁÂÃÄÅ¨ÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäå¸æçèéêëìíîïðñòóôõö÷øùúûüýþÿ"};

    int i = 0;

    while(chr)
    {
        if ( chr == alph[i] )
            return i;
        i++;

        if (i > 66) return -2;
    }
    return -1;
}

int ComparatorStr(const void* ptr1,const void* ptr2)
{
    char* str1 = *((char**) ptr1);
    char* str2 = *((char**) ptr2);
    while ((AlphEncoding( *str1) != -1) && (AlphEncoding( *str2) != -1))
    {
        while(AlphEncoding( *str1) == -2)  str1++;

        while(AlphEncoding( *str2) == -2) str2++;

        if (AlphEncoding(*str1) != AlphEncoding(*str2))
            return (AlphEncoding(*str1) - AlphEncoding(*str2));
    }

}

const void Sort(char* text[],long long int nlines)
{
    printf("\nmeow");
    qsort(text, nlines, sizeof(char*), & ComparatorStr);
}

void OutputFile(char* text[], long long int nlines)
{
    FILE* f2 = fopen("result.txt", "w");

    if (f2 == NULL)
    {
        printf("Cannot open file");
        return;
    }


    for(int i = 0; i < nlines; i++)
    {
        fputs(text[i], f2);
        fprintf (f2,"\n");
    }
    fclose(f2);
}
