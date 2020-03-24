#include<stdio.h>

struct definitionTable{
    int index;
    char* definition;
    char* args;
};

struct nameTable{
    int index;
    char *name;
    int definitionTableIndex;
};

struct argumentListArray{
    int index;
    char* arg;
};

int main(){
    printf("Hello world!\n");
    return 0;
}