#include<iostream>
#include<chrono>
#include<time.h>
using namespace std;
using namespace std::chrono;

//---------------QUICK SORT--------------------
void swap(int *a, int *b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

int partition (int arr[], int low, int high)
{
	int pivot = arr[high];
	int i = (low - 1);	// Index of smaller element 
	
	for(int j = low; j<= high - 1; j++)
	{
		if(arr[j] <= pivot)
		{
			i++; //increment index of smaller element 
			swap(&arr[i], &arr[j]);
		}
	}

	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

void quickSort(int arr[], int low, int high)
{
	if(low < high)
	{
		int pi = partition(arr, low, high); //Pi is partitoning index for p
	
		//Seperately sort elements before and after partition
		quickSort(arr, low, pi-1);	
		quickSort(arr, pi+1, high);
		
	
	}
}

void printArray(int arr[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		cout<< arr[i] << " ";
	cout << endl; 
}


//---------------MERGE SORT--------------------
void Merge(int *a, int low, int high, int mid)
{
	// We have low to mid and mid+1 to high already sorted.
	int i, j, k, temp[high-low+1];
	i = low;
	k = 0;
	j = mid + 1;
 
	// Merge the two parts into temp[].
	while (i <= mid && j <= high)
	{
		if (a[i] < a[j])
		{
			temp[k] = a[i];
			k++;
			i++;
		}
		else
		{
			temp[k] = a[j];
			k++;
			j++;
		}
	}
 
	// Insert all the remaining values from i to mid into temp[].
	while (i <= mid)
	{
		temp[k] = a[i];
		k++;
		i++;
	}
 
	// Insert all the remaining values from j to high into temp[].
	while (j <= high)
	{
		temp[k] = a[j];
		k++;
		j++;
	}
 
 
	// Assign sorted data stored in temp[] to a[].
	for (i = low; i <= high; i++)
	{
		a[i] = temp[i-low];
	}
}
 
// A function to split array into two parts.
void MergeSort(int *a, int low, int high)
{
	int mid;
	if (low < high)
	{
		mid=(low+high)/2;
		// Split the data into two half.
		MergeSort(a, low, mid);
		MergeSort(a, mid+1, high);
 
		// Merge them to get sorted output.
		Merge(a, low, high, mid);
	}
}

int main()
{
	int soa, choice;
	cout<<"\nEnter the size of array\n";
	cin>>soa;
	int arr[soa];

	srand(time(0)); 
    	for(int i = 0; i<soa; i++)
	{
		arr[i] = rand() % 100; 
	}

	do 
	{
		cout<<"\nChoose from the following: \n1. Quick Sort \n2. Merge Sort\n3. Exit\n";
		cin>>choice;
		switch(choice)
		{
			case 1:	
			{
				int n = sizeof(arr) / sizeof(arr[0]);	
				auto start = high_resolution_clock::now();
				quickSort(arr, 0, n-1);
				cout<<"Sorted array: \n";
				printArray(arr, n);
				auto stop = high_resolution_clock::now();
				auto duration = duration_cast<nanoseconds>(stop - start);
				cout<<"Time taken: "<< duration.count() <<endl;	
				break;
			}

			case 2:
			{
				int n = sizeof(arr) / sizeof(arr[0]);	
				auto start = high_resolution_clock::now();
				MergeSort(arr, 0, n-1);
				cout<<"Sorted array: \n";
				printArray(arr, n);
				auto stop = high_resolution_clock::now();
				auto duration = duration_cast<nanoseconds>(stop - start);
				cout<<"Time taken: "<< duration.count() <<endl;	
				break;
			}
			case 3:
				cout<<"\nThank you for using our program :)";
				break;

			default:
				cout<<"\nWrong input try again!";
				break;				
		}
	}while(choice != 3);
	
	
	
	//Use Random function here instead of below array
	//int arr[] = {10, 7, 8, 9, 1, 5};
	
	return 0;
}
