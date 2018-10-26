//created by Natalia

#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <dos.h>
#include <windows.h>
#include <stdlib.h>
#include <math.h>
#include <sys/stat.h>
using namespace std;

struct stat st = {};

void ReadPoem(int size , char buf[]);
long long int Count_change(char buf[], int size, char* text[], char* textCOPY[]);
void OutputFile(char* text[],long long int nlines);
int AlphEncoding(char chr);
const void Sort(char* text[],long long int nlines);
int ComparatorStr(const void* ptr1,const void* ptr2);
int check(void* ptr);


int main()
{
stat("proba.txt", &st);
int size = st.st_size +1;
char * buf = (char*) calloc(size, sizeof(char));
char** text = (char**)calloc(size,sizeof(char*));
char** textCOPY = (char**)calloc(size,sizeof(char*));

if (check(buf) == -1) return -1;
if (check(text) == -1) return -1;
if (check(textCOPY) == -1) return -1;

FILE* f2 = fopen("result.txt", "w");

if (f2 == NULL)
    {
        printf("Cannot open file");
    }
fclose(f2);

ReadPoem(size, buf);
long long int nlines = Count_change(buf, size, text, textCOPY);

printf(" size %d ", size);
printf("Nlines %ld", nlines);

Sort(text , nlines);
OutputFile(text, nlines);
OutputFile(textCOPY, nlines);

free(text);
text = NULL;
free(buf);
buf = NULL;
return 0;
}

int check(void* ptr)
{
    if (ptr == NULL)
     {
        printf ("error in calloc");
        return -1;
     }
}

void ReadPoem(int size , char buf[])
{

    FILE* onegin = fopen("proba.txt", "r");

    if (onegin == NULL)
    {
        printf("Cannot open file");
        return;
    }

    fread(buf, sizeof(char), size,onegin);
    buf [size] = '\n';
    fclose(onegin);
}

long long int Count_change(char buf[], int size, char* text[], char* textCOPY[])
{
    long long int nlines = 0;
    int n = 1;
    text[0] = &buf[0];
    textCOPY[0] = &buf[0];
    for (int i = 0; i < size; i++)
    {
        if (buf[i] == '\n')
        {
            nlines++;
            text[n] = &buf[i+1];
            textCOPY[n] = &buf[i+1];
            buf[i] = '\0';
            n++;
        }
    }

    return nlines-1;
}
int AlphEncoding(char chr)
{

    char alph[53]={"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"};

    int i = 0;

    while(chr)
    {
        if ( chr == alph[i] )
            return i;

        i++;

        if (i > 51) return -2;
        if (chr == '\n') return -1;
    }
    return -1;
}

int ComparatorStr(const void* ptr1,const void* ptr2)
{
    char* str1 = *((char**) ptr1);
    char* str2 = *((char**) ptr2);

    if (AlphEncoding( *str1) == -1) return 0;
    if (AlphEncoding( *str2) == -1) return 0;

    while ((AlphEncoding( *str1) != -1) && (AlphEncoding( *str2) != -1))
    {
        while(AlphEncoding( *str1) == -2) str1++;

        while(AlphEncoding( *str2) == -2) str2++;

        if (AlphEncoding(*str1) != AlphEncoding(*str2))
            return (AlphEncoding(*str1) - AlphEncoding(*str2));
        else
        {
            str1++;
            str2++;
        }
    }

}

const void Sort(char* text[],long long int nlines)
{
    printf("\nmeow");
    qsort(text, nlines, sizeof(char*),  ComparatorStr);
}

void OutputFile(char* text[], long long int nlines)
{
    FILE* f2 = fopen("result.txt", "a+");

    for(int i = 0; i < nlines; i++)
    {
        fputs(text[i], f2);
        fprintf (f2,"\n");
    }
    fclose(f2);
}
