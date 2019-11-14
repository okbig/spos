#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX 20 //MAximujm SymbolEntries
#define M_MAX 11 //MAximum Mnemonics
#define AD_MAX 5
#define R_MAX 4
#define C_MAX 6

struct SYMBTAB{
	char Symb[10];
	int Addr;
}S[MAX];

struct LITTAB{
	char Lit[5];
	int Addr;
}L[MAX];

int POOLTAB[MAX],SymbCnt,LitCnt,PoolCnt,TokCnt,LC,i,j,k;
char Tok1[MAX],Tok2[MAX],Tok3[MAX],Tok4[MAX],Buffer[80],temp[MAX];
FILE *fp,*fp1,*fp2;

//Data Structure Initialization
char MOTAB[][6] = {"STOP","ADD","SUB","MULT","MOVER","MOVEM","COMP","BC","DIV","READ","PRINT"};
char REGTAB[][5]= {"AREG","BREG","CREG","DREG"};
char CONDTAB[][5]= {"LT","LE","EQ","GT","GE","ANY"};
char ADTAB[][7]= {"START","END","ORIGIN","EQU","LTORG"};

int SearchSymb(char *s){
	int i;
	for(i=0;i<SymbCnt;i++)
	{
		if(strcmp(S[i].Symb,s)==0)
		return(i);
	}
	return -1;
}

int SearchLit(char *s){
	int i;
	for(i=POOLTAB[PoolCnt];i<LitCnt;i++)
	{
		if(strcmp(L[i].Lit,s)==0)
		return(i);
	}
	return -1;
}

int SearchCond(char *s){
	int i;
	for(i=0;i<C_MAX;i++)
	{
		if(strcmp(CONDTAB[i],s)==0)
		return(i);
	}
	return -1;
}

int SearchReg(char *s){
	int i;
	for(i=0;i<R_MAX;i++)
	{
		if(strcmp(REGTAB[i],s)==0)
		return(i);
	}
	return -1;
}

int SearchOp(char *s){
	int i;
	for(i=0;i<M_MAX;i++)
	{
		if(strcmp(MOTAB[i],s)==0)
		return(i);
	}
	return -1;
}

//Aditya
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
 printf("\nPool\tAddr");
 printf("\n-----------------------------");
	for(i=0;i<LitCnt;i++){
		printf("\n%s\t%d" , L[i].Lit , L[i].Addr);
		printf("\n-----------------------------");
    }
}//

void DispPoolTab(){
 int i;///Listing Symbol table
 printf("\n-----------------------------");
 printf("\nPool\tpoolCnt");
 printf("\n-----------------------------");
	for(i=0;i<PoolCnt;i++){
		printf("\n%d\t%d",i,POOLTAB[i]);
		printf("\n-----------------------------");
    }
}///End of DispPoolTab


void PrintFile( char *fn){
	fp = fopen(fn , "r");
	if(fp == NULL){
		printf("\nCannot open the File %s" ,fn);
		exit(0);
	 }
	while(fgets(Buffer,80,fp)){
		printf("%s", Buffer);
	}
	fclose(fp);
}///End of PrintFile

int searchDirective(char *s){
	int i;
	for(i = 0;i < AD_MAX;i++){
		if(strcmp(ADTAB[i], s) == 0)
			return(i);
	}
	return -1;
}

void passOne(){
	///fp - ptr of source file and fp1 - pointer of intermediate file
	fp = fopen("input.asm","r");///input file in read mode
	fp1=fopen("ic.txt","w");///input file in write mode

	if(fp == NULL || fp1 == NULL){
		printf("\nCannot Create file");
		exit(0);
	}

	while(fgets(Buffer,80,fp)){
		///Initialize Token to NULL
		strcpy(Tok1,"");
		strcpy(Tok2,"");
		strcpy(Tok3,"");
		strcpy(Tok4,"");

		TokCnt = sscanf(Buffer,"%s%s%s%s",Tok1,Tok2,Tok3,Tok4);
		switch(TokCnt){
			
			case 1:
			 		i = SearchOp(Tok1);
			 		if(i == 0){
			 		fprintf(fp1,"(IS, %02d)\n", i);
			 		break;
			 		}
			 		
			 		i = searchDirective(Tok1);
			 		if(i == 0 || i == 3){
				 		fprintf(fp1,"(AD, %02d)\n", i);
				 		LC = -1;
			 		}
			 		else if(i == 1 || i == 4){
			 		fprintf(fp1,"(AD, %02d)\n", i);
			 		for(k = POOLTAB[PoolCnt]; k < LitCnt ; k++){L[k].Addr = LC++;}
			 		POOLTAB[++PoolCnt] = LitCnt;
			 		LC--;
			 		}
			 		break;
			case 2:
				i = SearchOp(Tok1);
				if(i==9 || i==10){
					j = SearchSymb(Tok2);
					if(j==-1){
						fprintf(fp1,"(IS,%02d)(S,%02d)\n",i,SymbCnt);
						strcpy(S[SymbCnt++].Symb,Tok2);
					}
					else{
						fprintf(fp1,"(IS,%02d)(S,%02d)\n",i,j);
					}
					break;
				}
				i = searchDirective(Tok1);
				if(i == 0 || i == 2){
					LC = atoi(Tok2) - 1;
					fprintf(fp1, "(AD, %02d)(C, %02d)\n", i, LC + 1);
				}
				break;

			case 3:
				i = SearchOp(Tok1);
				if(i >= 1 && i <= 8){
					if(Tok3[0] == '='){
						j = SearchLit(Tok3);
						if(j == -1){
							sprintf(temp, "(L, %02d)", LitCnt);
							strcpy(L[LitCnt++].Lit, Tok3);
						}
						else{
							sprintf(temp, "(L, %02d)", j);
						}
					}
					else{
						j = SearchSymb(Tok3);
						if(j == -1){
							sprintf(temp, "(S, %02d)", SymbCnt);
							strcpy(S[SymbCnt++].Symb, Tok3);
						}
						else{
							sprintf(temp, "(S, %02d)", j);
						}
					}
				
				j = i == 7 ? j = SearchCond(Tok2) : SearchReg(Tok2);
				fprintf(fp1, "(IS, %02d) (%d) %s\n", i, j, temp);
				}//End of is
				///ds and dc
				if((strcmp(Tok2,"DC")==0) || (strcmp(Tok2,"DS")==0))
				 {
				 	j=SearchSymb(Tok1);
				 	if(j==-1)
				 	{
						strcpy(S[SymbCnt].Symb,Tok1);
						S[SymbCnt++].Addr = LC;
					}
					else
					{
						S[j].Addr = LC;
					}
					if(strcmp(Tok2,"DC")== 0)
					{
						fprintf(fp1,"(DL,00)(C,%02d)\n",atoi(Tok3));
					}
					else 
					{
						LC+=atoi(Tok3)-1;
						fprintf(fp1,"(DL,01) (C, %02d)\n",atoi(Tok3));
					}
					break;
				}
				
				//EQUATE
				i=searchDirective(Tok2);
				if(i==3)
				{
					k=SearchSymb(Tok3);
					j=SearchSymb(Tok1);
					
					if(j==-1) /// NOt Present
					{
						strcpy(S[SymbCnt].Symb,Tok1);
						S[SymbCnt++].Addr = S[k].Addr;
					}
					else//Symbol Present
					{
						S[j].Addr=S[k].Addr;
					}
					
					fprintf(fp1,"(AD,%02d)\n",i);
					LC--;
					break;
				}
				break;
				
			case 4:
				j=SearchSymb(Tok1);
				 	if(j==-1)
				 	{
						strcpy(S[SymbCnt].Symb,Tok1);
						S[SymbCnt++].Addr = LC;
					}
					else
					{
						S[j].Addr = LC;
					}
					
				i = SearchOp(Tok2);
				if(i >= 1 && i <= 8){
					if(Tok4[0] == '='){
						j = SearchLit(Tok4);
						if(j == -1){
							sprintf(temp, "(L, %02d)", LitCnt);
							strcpy(L[LitCnt++].Lit, Tok4);
						}
						else{
							sprintf(temp, "(L, %02d)", j);
						}
					}
					else{
						j = SearchSymb(Tok4);
						if(j == -1){
							sprintf(temp, "(S, %02d)", SymbCnt);
							strcpy(S[SymbCnt++].Symb, Tok4);
						}
						else{
							sprintf(temp, "(S, %02d)", j);
						}
					}
				
				j = i == 7 ? j = SearchCond(Tok3) : SearchReg(Tok3);
				fprintf(fp1, "(IS, %02d) (%d) %s\n", i, j, temp);
				}//End of is
				break;
				}//End of Switch
		LC++;
	}///End of While
	fclose(fp);
	fclose(fp1);
}///End of PASS-1


void display_tables(){
	DispSymbTab();
	DispLitTab();
	DispPoolTab();
}

int main(){
	char in[10]="ic.txt";
	passOne();
	display_tables();
	printf("\nIntermediate Code\n");
	PrintFile(in);
	return 0;
}
