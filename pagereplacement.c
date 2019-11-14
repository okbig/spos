#include<stdio.h>


int n,nf;  		
int in[25];	
int p[10];		
int pgHitCnt, pgFaultCnt;  
int i,j,k;	
int near[10], least[10];  

void getData();
void initialize();
int isHit(int);
void dispPages();
void dispPgFaultsHits();
void fifo();
void lru();
void findLeastPastPage();
void replacePageLRU();

void getData()
{
	printf("\nEnter length of page reference sequence:");
	scanf("%d",&n);

	printf("\nEnter the page reference sequence:");
	for(i=0; i<n; i++)
		scanf("%d",&in[i]);

	printf("\nEnter no of frames:");
	scanf("%d",&nf);
}//end getData()
 
void initialize()
{
	pgFaultCnt = 0;
	pgHitCnt = 0;
	for(i=0; i<nf; i++)
		p[i]=9999;
}//end initialize
 
int isHit(int data)
{
	int flag=0;
	for(j=0; j<nf; j++)
	{
		if(p[j]==data)
		{
			pgHitCnt++;
			flag=1;
			break;
		}//end if
	}//end for

	return flag;
}//end  isHit
 
void dispPages()
{
	for (k=0; k<nf; k++)
		if(p[k] != 9999)
			printf(" %d",p[k]);
}//end dispPages
 
void dispPgFaultsHits()
{
	printf("\n\nTotal no of page faults:%d",pgFaultCnt);
	printf("\nTotal no of page hits:%d\n",pgHitCnt);
}//end dispPgFaultsHits
 
void fifo()
{
	initialize();
	printf("\n FIFO:");
	for(i=0; i<n; i++) { 
		printf("\nFor %d :",in[i]);

		if(isHit(in[i])==0) 
		{
			for(k=0; k<nf-1; k++) { p[k]=p[k+1]; } 

			p[k]=in[i];
			pgFaultCnt++;
			dispPages();
		}
		else
			printf("No page fault");
	}//for (i=0)
	dispPgFaultsHits();
}//end fifo

void lru()
{
	initialize();
	printf("\nLRU:");
	for(i=0; i<n; i++) 
	{
		printf("\nFor %d :",in[i]);

		if(isHit(in[i])==0) // No Hit
		{
			findLeastPastPage();
			replacePageLRU();		
		}
		else
			printf("No page fault!");
	}//end for
	dispPgFaultsHits();
}//end lru

void findLeastPastPage()
{
	for(j=0; j<nf; j++)
	{
		int pg=p[j];
		int found=0;
		for(k=i-1; k>=0; k--){
			if(pg==in[k])	{
				least[j]=k;
				found=1;
				break;
			}
			else
				found=0;
		}//end inner for
		if(!found)
			least[j]=-9999;
	}//end outer for
	
}//end findLeastPastPage

void replacePageLRU(){
	int min=9999;
	int repindex;
	for(j=0; j<nf; j++)
	{
		if(least[j]<min)
		{
			min=least[j];
			repindex=j;
		}//end if
	}//end for
	p[repindex]=in[i];
	pgFaultCnt++;
	dispPages();
}//end replacePageLRU

int main()
{
	int choice;
	while(1)
	{
		printf("\nPage Replacement Algorithms\n1.Enter data\n2.FIFO\n4.LRU\n5.Exit\nEnter your choice:");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1: 
				getData();
				break;
			case 2:
				fifo();
				break;
			case 3:
				optimal();
				break;
			case 4:
				lru();
				break;
			default:
				return 0;
		}//end switch
	}//end while
}//end program 