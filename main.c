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
    char *arg;
    struct argumentListArray *next;
};
//Initialising the table pointers
struct definitionTable* dtHead=NULL;
struct nameTable* ntHead=NULL;
struct argumentListArray* alHead=NULL;

//Index for the argument list array
int alIndex=1;

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

void pass1(FILE *fp)
{    
    //initialising the counters to 1
    MDTC=MNTC=1;

    char *line;
    ssize_t read;
    size_t len = 0;
    //Initialising the table pointers
    struct definitionTable* dtTemp = dtHead;
    struct nameTable* ntTemp = ntHead;
    struct argumentListArray* alTemp = alHead;
    //scanning the file line by line
    while((read = getline(&line, &len, fp)) != -1){
	    //printf("\n%s",line);
		if(strstr(line,"MACRO")){
			//identifying the macro name
			char* tokens= strtok(line," ");
			printf("\nMACRO %s Detected...\n",tokens);	
			//if Name table is not yet created the first row is initialised else the new entry is appended into the table
			if(ntHead == NULL){
				ntHead=(struct nameTable*)malloc(sizeof(struct nameTable));	
				ntTemp = ntHead;		 
			}
			else{
				ntTemp->next=(struct nameTable*)malloc(sizeof(struct nameTable));
					ntTemp = ntTemp;
			}
				ntTemp->index=MNTC;
			MNTC++;
			ntTemp->name=tokens;
			printf("\n%s added into Name Table",tokens);
			tokens = strtok(NULL, " ");
			//Identifying the arguments that needs to be added to the argument list array
			while(tokens!=NULL){
				if((strcmp(tokens,"MACRO")!=0) && tokens!="\n"){
					//If argument list is not yet created the first row is initialised else the new entry is appended to the existing lis
					if(alHead == NULL){
						alHead=(struct argumentListArray*)malloc(sizeof(struct argumentListArray));
						alTemp = alHead;
					}
					else{
						alTemp->next=(struct argumentListArray*)malloc(sizeof(struct argumentListArray));
						alTemp = alTemp->next;
					}
					alTemp->index=alIndex;
					alIndex++;
					alTemp->arg=tokens;
						printf("\nArgument %s added into argument list array",alTemp->arg);
				}
				tokens = strtok(NULL, " ");
			}
			//If Definition table is not yet created the first row is initialised else the new entry is added to the table
			if(dtHead == NULL){
				dtHead=(struct definitionTable*)malloc(sizeof(struct definitionTable));
				dtTemp = dtHead;
			}
			else{
				dtTemp->next=(struct definitionTable*)malloc(sizeof(struct definitionTable));
				dtTemp=dtTemp->next;
			}
			 dtTemp->definition=ntTemp->name;
			 printf("\nDefinition table entry created for %s",ntTemp->name);
			//The pointer to the definition table is stored in the name table for future references
			ntTemp->dtIndex=dtTemp;
			long int read;
			read = getline(&line, &len, fp);
			while(strcmp(line,"MEND\n")!=0){
				//printf("\nLine:%s",line);
				tokens = strtok(line, " ");
				int isArg = 0, index = 0;
				while(tokens!=NULL){
					if(isArg == 0){
						dtTemp->next=(struct definitionTable*)malloc(sizeof(struct definitionTable));
                        			dtTemp=dtTemp->next;
						dtTemp->index=MDTC;
						MDTC++;
						dtTemp->definition = tokens;
						printf("\nEntry appended for %s at index %d",dtTemp->definition,dtTemp->index);
						isArg = 1;
					}
					else
					{
						if(findArgIndex(tokens)==NULL){
						alTemp->next=(struct argumentListArray*)malloc(sizeof(struct argumentListArray));
						alTemp->next->index=alTemp->index+1;
                                                alTemp = alTemp->next;
						alTemp-> arg= tokens;
						dtTemp->arg[index]=alTemp;
						}
						else{
							dtTemp->arg[index]=findArgIndex(tokens);
						}
						index++;
					}
					tokens = strtok(NULL, " ");
				}
				read = getline(&line, &len, fp);
			}
		}
    }
    fclose(fp);
    printf("\nAll three tables are updated.Pass 1 Complete!\n");
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
		printf("\n%s",line);
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
	printf("\nOutput file updated with expanded code.Pass 2 Complete!\n");
}

int main(){
    FILE *fp;
    fp=fopen("input.asm","r");
    if(fp == NULL){
	    perror("\nFailed to open the assembly file!");
	    exit(0);
    }
    printf("\nPass 1 in progress\n");
    pass1(fp);
    printf("\nPass 2 in progress\n");
    pass2(fp);
    fclose(fp);
    return 0;
}
