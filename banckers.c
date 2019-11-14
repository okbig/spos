#include<stdio.h>
#include<stdlib.h>

int r,p,alloc[10][10],claim[10][10],avail[10],rs[10];
int sum=0,flag=0,safe_seq[10],s=1,match[10]={0};

int i,j;

// Function Prototypes
void acceptData();
void calculateAvailableMatrix();
void calculateSafeSeq();
void printSafeSeq();
void updateAvailableMatrix(int, int);

// Function Definitions
void acceptData(){
    printf("Enter the no of resources:");
    scanf("%d",&r);
    printf("Enter the no of processes:");
    scanf("%d",&p);

    printf("Enter the elements of allocation matrix:\n");
    for(i=1;i<=p;i++)
        for(j=1;j<=r;j++)
            scanf("%d",&alloc[i][j]);

    printf("Enter the elements of claim matrix:\n");
    for(i=1;i<=p;i++)
        for(j=1;j<=r;j++)
            scanf("%d",&claim[i][j]);
  
      printf("Enter the resource vector:\n");
      for(i=1;i<=r;i++)
        scanf("%d",&rs[i]);
}//acceptData

void calculateAvailableMatrix(){
    printf("\nThe Available Matrix is:");
    printf("\nR1  R2  R3");
    printf("\n");
    for(i=1;i<=r;i++) {
        for(j=1;j<=p;j++)
        {
            sum=sum+alloc[j][i]; //( [1,1], [2,1], [3,1] ...
        }
        avail[i]=rs[i] - sum; //Total resources - sum of alloted resources
        printf("%d   ",avail[i]);
        sum=0;
    }
}//calculateAvailable

void calculateSafeSeq(){
    int m = 1, k = 0; // m for iteration and k stores selected process number
    while (m<=p){ //For all the processes
        //Step 1 - Select the process with all claims <= Available
        for(i=1;i<=p;i++) { 
            for(j=1;j<=r;j++) {
                if(claim[i][j] <= avail[j] && match[i] == 0) 
                {
                    flag=0;
                    k=i;         //selected process k is i
                }
                else { flag=1; break; } //either of the claims cannot be fulfilled
            }// inner for
            if(flag==0) break;
        }//outer for (i)
        //Step 2 - update Available Matrix by releasing the resources of selected process;
        updateAvailableMatrix(flag, k);
        m++;
    }//while
}//calculateSafeSeq()

void updateAvailableMatrix(int flag, int k)
{
    if(flag==0)
    {
        printf("\n\n\nProcess %d is selected",k);
        printf("\n\nThe Available Matrix becomes:");
        printf("\n\nR1  R2  R3 \n");
        
        match[k] = 1;
        safe_seq[s] = k; //Make an entry in the safe_seq
        for(i=1;i<=r;i++) //update available matrix
        {
            avail[i]=avail[i]+alloc[k][i];
            printf("%d   ",avail[i]);
            claim[k][i]=0;
            alloc[k][i]=0;
        }
        s++;
    }//if flag is 0
}

void printSafeSeq()
{
    printf("\n\nThe safe sequence is:\n");
    for(i=1;i<=p;i++)
        printf("\tP%d",safe_seq[i]);

}//printSafeSeq()

int main()
{
    acceptData();
    calculateAvailableMatrix();
    calculateSafeSeq();
    printSafeSeq(); 
    printf("\n");
    exit(0);
}//main
