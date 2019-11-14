#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 10

struct SYMBTAB{
    char Symb[10];
    int Addr;
}S[MAX];

struct LITTAB{
    char Lit[5];
    int Addr;
}L[MAX];

int POOLTAB[MAX], SymbCnt, LitCnt,PoolCnt, TokCnt,LC,i,j,k;
char Tok1[MAX],Tok2[MAX],Tok3[MAX],Tok4[MAX],Tok5[MAX], Buffer[80],temp[MAX];
FILE *fp1, *fp2;





void createSymbTab(){
    printf("\n Enter total number of symbols:");
    scanf("%d",&SymbCnt);
    printf("\n Enter symbols and address\n");
    for(int i=0;i<SymbCnt;i++){
        scanf("%s %d", S[i].Symb, &S[i].Addr);
    }
}

void createLitTab(){
    printf("\nEnter total number of literals");
    scanf("%d",&LitCnt);
    printf("\nEnter literals and address");
    for (int i = 0; i <LitCnt; i++)
    {
        scanf("%s %d", L[i].Lit,&L[i].Addr);
    }}

    void createPoolTab(){
        printf("\nenter total number of pools:");
        scanf("%d", &PoolCnt);
        printf("\nEnter Literal reference");
        for(int i=0;i<PoolCnt;i++){
            scanf("%d",&POOLTAB[i]);
        }
    }

    void DispSymbTab(){
 int i;///Listing Symbol table
 printf("\n-----------------------------");
 printf("\nSymb\tAddr");
 printf("\n-----------------------------");
	for(i=0;i<SymbCnt;i++){
		printf("\n%s\t%d" , S[i].Symb , S[i].Addr);
		printf("\n-----------------------------");
    }
}///End of DispSymbTab

void DispLitTab(){
 int i;///Listing Symbol table
 printf("\n-----------------------------");
 printf("\nLIT\tAddr");
 printf("\n-----------------------------");
	for(i=0;i<LitCnt;i++){
		printf("\n%s\t%d",  L[i].Lit , L[i].Addr);
		printf("\n-----------------------------");
    }
}///End of DispLITTab

void DispPoolTab(){
 int i;///Listing Symbol table
 printf("\n-----------------------------");
 printf("\n\tindex\tPOOL");
 printf("\n-----------------------------");
	for(i=0;i<PoolCnt;i++){
		printf("\n%02d\t%d" ,i, POOLTAB[i]);
		printf("\n-----------------------------");
    }
}///End of DispSymbTab

   
    
void PassTwo(){
    int i,j,k;
    static int ind=0;
    char temp[MAX];
    LC=0;
    fp1=fopen("ic.txt","r");
    fp2=fopen("tc.txt","w");

    while(fgets(Buffer,80,fp1)){
        TokCnt=sscanf(Buffer, "%s %s %s %s %s",Tok1,Tok2,Tok3,Tok4,Tok5);

        Tok1[strlen(Tok1)-1]='\0';
        Tok2[strlen(Tok2)-1]='\0';
        Tok3[strlen(Tok3)-1]='\0';
        Tok4[strlen(Tok4)-1]='\0';
        Tok5[strlen(Tok5)-1]='\0';

        switch(TokCnt){
            case 2: if((strcmp(Tok1+1,"AD")==0)&&(atoi(Tok2)==1||atoi(Tok2)==4)){
                        for(i=POOLTAB[ind];i<POOLTAB[ind+1];i++){
                            strcpy(temp,L[i].Lit);
                            temp[strlen(temp)-1]='\0';
                            fprintf(fp2,"%d) + 00 0 %03d\n",LC++,atoi((temp,"'")+1));
                        }
                        ind++;
                        LC--;

            }
            else 
            if(strcmp(Tok1+1,"IS")==0)
                fprintf(fp2, "%d) + 00 0 000\n",LC); 
            break;
            case 4: if(strcmp(Tok1+1,"AD")==0||strcmp(Tok1+1,"AD")==2)
                        LC=atoi(Tok4)-1;
                    else
                    if(strcmp(Tok1+1, "IS")==0)
                        fprintf(fp2,"%d) + %02d 0 %03d\n", LC, atoi(Tok2),S[atoi(Tok4)].Addr);
                    else 
                    if(strcmp(Tok1+1,"DL")==0){
                        if(atoi(Tok2)==1){
                            for(i=0;i<atoi(Tok4);i++)
                                fprintf(fp2,"%d)\n",LC++);
                            LC--;
                        }

                        else if(atoi(Tok2)==0)
                                fprintf(fp2, "%d)+00 0 %03d\n",LC,atoi(Tok4));
                    }
                        break;
            case 5:if(Tok4[1]=='S')
                        fprintf(fp2,"%d)+ %02d %d %03d\n",LC,atoi(Tok2),atoi(Tok3+1),S[atoi(Tok5)].Addr);
                    else
                    if(Tok4[1]=='L')
                        fprintf(fp2,"%d)+ %02d %d %03d\n",LC,atoi(Tok2),atoi(Tok3+1),L[atoi(Tok5)].Addr);
                     break;
        }
        LC++;
    }
    fclose(fp1);
    fclose(fp2);
}

 void generate_dataStructures(){
    createSymbTab();
    DispSymbTab();
    createLitTab();
    DispLitTab();
    createPoolTab();
    DispPoolTab();
}



int main(){
    generate_dataStructures();
    PassTwo();
    printf("\nTarget Code\n");
    //PrintFile("tc.txt");
    return 0;
}