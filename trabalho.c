/* C program for Merge Sort */
#include<stdlib.h> 
#include<stdio.h> 
#include <time.h>
#include <pthread.h>

#define MAX_THREADS 2

unsigned **matrix;


  
// Merges two subarrays of arr[]. 
// First subarray is arr[l..m] 
// Second subarray is arr[m+1..r] 
void merge(int arr[], int l, int m, int r) 
{ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
  
    /* create temp arrays */
    int L[n1], R[n2]; 
  
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1+ j]; 
  
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray 
    j = 0; // Initial index of second subarray 
    k = l; // Initial index of merged subarray 
    while (i < n1 && j < n2) 
    { 
        if (L[i] <= R[j]) 
        { 
            arr[k] = L[i]; 
            i++; 
        } 
        else
        { 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
  
    /* Copy the remaining elements of L[], if there 
       are any */
    while (i < n1) 
    { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
  
    /* Copy the remaining elements of R[], if there 
       are any */
    while (j < n2) 
    { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
} 
  
/* l is for left index and r is right index of the 
   sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r) 
{ 
    if (l < r) 
    { 
        // Same as (l+r)/2, but avoids overflow for 
        // large l and h 
        int m = l+(r-l)/2; 
  
        // Sort first and second halves 
        mergeSort(arr, l, m); 
        mergeSort(arr, m+1, r); 
  
        merge(arr, l, m, r); 
    }     
} 
  
/* UTILITY FUNCTIONS */
/* Function to print an array */
void printArray(int A[], int size) 
{ 
    int i; 
    for (i=0; i < size; i++) 
        printf("%d ", A[i]); 
    printf("\n"); 
} 


void fillMatrix(int x, int y){
    
    int i, j;   
    int matrix[x][y]; 
    int *arrp = &matrix[x][y];
    int arr_size = sizeof(matrix[0])/sizeof(matrix[0][0]);

    
    srand(time(NULL));

    for(i = 0; i <= x-1;i++) {
        for(j = 0; j <= y-1 ;j++) {
            //*(arrp+j) = rand() % 100;
            matrix[i][j] = rand() % 100;
            //printf("%d ", *(arrp+j));
            //printf("%d ", arr[i][j]);
        }
        //printf("\n");
    }   
   
  }

typedef struct{

    int id;
}thread_arg;



void *sorting(void *thread_id){
    int i = 0;
    thread_arg *thread = (thread_arg *) thread_id;
    int matrix_size = sizeof(matrix[0])/sizeof(matrix[0][0]);


    for(i = (thread -> id) % MAX_THREADS; i < matrix_size; i+MAX_THREADS){
        printf("Given array is \n"); 
        printArray(matrix[i], matrix_size); 
  
        mergeSort(matrix[i], 0, matrix_size - 1); 
    
        printf("\nSorted array is \n"); 
        printArray(matrix[i], matrix_size);
        
        }
        //pthread_exit((void *)NULL);
    }

/* Driver program to test above functions */
int main() 
{ 
    int i = 0;
    thread_arg a[2];
    pthread_t tid[MAX_THREADS];


    fillMatrix(2,2);
    
    for(i=0; i< MAX_THREADS; i++){
        a[i].id = i;
        pthread_create(&(tid[i]), NULL, &sorting, (void *)&(a[i]));
    }

      for(i=0; i<MAX_THREADS; i++)
    {
        pthread_join(tid[i], NULL);
    }
     //pthread_exit((void *)NULL);

    return 0; 
} 