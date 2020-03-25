#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int MDTC,MNTC;

//Definition table to hold the definition of the macro
struct definitionTable{
    int index;
    char* definition;
    char* args;
    struct definitionTable *next;
};

//nameTable contains the name of the macro and its corresponding index in Definition table
struct nameTable{
    int index;
    char *name;
    struct definitionTable *dtIndex;
    struct nameTable *next;
};

//Argument List array holds the arguments used in the macro definition
struct argumentListArray{
    int index;
    char* arg;
    struct argumentListArray *next;
};

//Initialising the table pointers
struct definitionTable* dtHead=NULL;
struct nameTable* ntHead=NULL;
struct argumentListArray* alHead=NULL;
//Index for the argument list array
int alIndex=0;

void pass1(FILE *fp){
    
    //initialising the counters to 1
    MDTC=MNTC=1;

    char *line;
    ssize_t read;
    size_t len = 0;

    //scanning the file line by line
    while((read = getline(&line, &len, fp)) != -1){
	if(strstr(line,"MACRO")){
		//identifying the macro name
	        char* tokens= strtok(line," ");
		//if Name table is not yet created the first row is initialised else the new entry is appended into the table
		if(ntHead == NULL){
			ntHead=(struct nameTable*)malloc(sizeof(struct nameTable));			 }
		else{
			struct nameTable* entry =(struct nameTable*)malloc(sizeof(struct nameTable));
			ntHead->next = entry;
			ntHead = entry;
		}
	        ntHead->index=MNTC;
		MNTC++;
		ntHead->name=tokens;
		//If Definition table is not yet created the first row is initialised else the new entry is added to the table
		if(dtHead == NULL){
                        dtHead=(struct definitionTable*)malloc(sizeof(struct definitionTable));                      }
                else{
                        struct definitionTable* entry =(struct definitionTable*)malloc(sizeof(struct definitionTable));
                        dtHead->next = entry;
                        dtHead = entry;
                }
		//The pointer to the definition table is stored in the name table for future references
		ntHead->dtIndex=dtHead;
		tokens = strtok(NULL, " ");
		//Identifying the arguments that needs to be added to the argument list array
		while(tokens!=NULL){
			if((strcmp(tokens,"MACRO")!=0) && tokens!="\n"){
				//If argument list is not yet created the first roe is initialised else the new entry is appended to the existing list
				if(alHead == NULL){
                        		alHead=(struct argumentListArray*)malloc(sizeof(struct argumentListArray));
				}
               			 else{
                        		struct argumentListArray* entry =(struct argumentListArray*)malloc(sizeof(struct argumentListArray));
                        		alHead->next = entry;
                        		alHead = entry;
                		}
				alHead->index=alIndex;
				alIndex++;
				alHead->arg=tokens;
			}
      			tokens = strtok(NULL, " ");
		}
	}
    }
    fclose(fp);
}

void pass2(){

}

int main(){
    FILE *fp;
    fp=fopen("cfile.c","r");
    if(fp == NULL){
	    printf("\nFailed to open the fail!");
	    exit(0);
    }
    pass1(fp);
    pass2(fp);
    fclose(fp);
    return 0;
}
