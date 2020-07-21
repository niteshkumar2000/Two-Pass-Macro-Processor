#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int MDTC,MNTC;

//Definition table to hold the definition of the macro
struct definitionTable{
    int index;
    char* definition;
    struct argumentListArray *arg[2];
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
struct definitionTable* dtHead=NULL, *dtTemp = NULL;
struct nameTable* ntHead=NULL, *ntTemp = NULL;
struct argumentListArray* alHead=NULL, *alTemp = NULL;
//Index for the argument list array
int alIndex=0;


void printNameTable(){
	struct nameTable* temp = ntHead;
	printf("NAME TABLE\n");
	while(temp != NULL){
		printf("Index: %d, Name: %s\n", temp->index, temp->name);
		temp = temp->next;
	} 
}

void printArguentListArray(){
	struct argumentListArray* temp = alHead;
	printf("ARGUMENT LIST\n");
	while(temp != NULL){
		printf("Index: %d, Arg: %s\n", temp->index, temp->arg);
		temp = temp->next;
	} 
}

void printDefinitionTable(){
	struct definitionTable* temp = dtHead;
	printf("DEFINITION TABLE\n");
	while(temp != NULL){
		printf("Index: %d, Definition: %s, ArgIndex: %p\n", temp->index, temp->definition, temp->arg);
		temp = temp->next;
	} 
}

struct argumentListArray* findArgIndex(char * arg){
	struct argumentListArray* temp = alHead;
	while(temp != NULL){
		if(strcmp(temp->arg, arg) == 0){
			return temp;
		}
		temp = temp->next;
	}
	return NULL;
}

struct definitionTable* findName(char *name){
	struct nameTable* temp = ntHead;
	while (temp != NULL)
	{
		if (strcmp(temp->name, name) == 0)
		{
			return temp->dtIndex;
		}
		temp = temp->next;
	}
	return NULL;
} 

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
				ntHead=(struct nameTable*)malloc(sizeof(struct nameTable));	
				ntTemp = ntHead;		 
			}
			else{
				struct nameTable* entry =(struct nameTable*)malloc(sizeof(struct nameTable));
				ntTemp->next = entry;
				ntTemp = entry;
			}
				ntTemp->index=MNTC;
			MNTC++;
			ntTemp->name=tokens;
			tokens = strtok(NULL, " ");
			//Identifying the arguments that needs to be added to the argument list array
			while(tokens!=NULL){
				if((strcmp(tokens,"MACRO")!=0) && tokens!="\n"){
					//If argument list is not yet created the first roe is initialised else the new entry is appended to the existing list
					if(alHead == NULL){
						alHead=(struct argumentListArray*)malloc(sizeof(struct argumentListArray));
						alTemp = alHead;
					}
					else{
						struct argumentListArray* entry =(struct argumentListArray*)malloc(sizeof(struct argumentListArray));
						alTemp->next = entry;
						alTemp = entry;
					}
					alTemp->index=alIndex;
					alIndex++;
					alTemp->arg=tokens;
				}
				tokens = strtok(NULL, " ");
			}
			//If Definition table is not yet created the first row is initialised else the new entry is added to the table
			if(dtHead == NULL){
				dtHead=(struct definitionTable*)malloc(sizeof(struct definitionTable));
				dtTemp = dtHead;
			}
			else{
				struct definitionTable* entry =(struct definitionTable*)malloc(sizeof(struct definitionTable));
				dtTemp->next = entry;
				dtTemp = entry;
			}
			//The pointer to the definition table is stored in the name table for future references
			ntTemp->dtIndex=dtTemp;
			while((read = getline(&line, &len, fp)) != -1){
				if(strcmp(line,"MEND") != 0){
					tokens = strtok(line, " ");
					int isArg = 0, index = 0;
					while(tokens!=NULL){
						if(isArg == 0){
							dtTemp->definition = tokens;
							isArg = 1;
						}else{
							dtTemp->arg[index] = findArgIndex(tokens);
							index++;
						}
						tokens = strtok(NULL, " ");
					}
				}
				struct definitionTable* entry =(struct definitionTable*)malloc(sizeof(struct definitionTable));
				dtTemp->next = entry;
				dtTemp = entry;
			}
			struct definitionTable* entry =(struct definitionTable*)malloc(sizeof(struct definitionTable));
			entry->definition = line;
			dtTemp->next = entry;
			dtTemp = entry;
		}
    }
    fclose(fp);
}
void pass2(FILE *fp)
{
	char *line;
	ssize_t read;
	size_t len = 0;
    	FILE *Ofp;
    	Ofp=fopen("output.txt","a");
   
	//scanning the file line by line
	while ((read = getline(&line, &len, fp)) != -1)
	{
		struct definitionTable *temp = findName(line);
		if(temp != NULL)
		{
			while(strcmp(temp->definition, "MEND") != 0){
				fprintf(Ofp,"-\t%s\t%s\t%s\n",temp->definition, temp->arg[0], temp->arg[1]);
				temp = temp->next;
			}
		}
	}
	fclose(Ofp);
}

int main(){
    FILE *fp;
    fp=fopen("input.asm","r");
    if(fp == NULL){
	    perror("\nFailed to open the assembly file!");
	    exit(0);
    }
    pass1(fp);
    pass2(fp);
    fclose(fp);
	printNameTable();
	printArguentListArray();
	printDefinitionTable();
    return 0;
}
