//
//  main.cpp
//  A simple program that implements quicksort and mergesort, and then finds the difference in 
//  time efficiencies between each algorithm.
//
//  Created by Lily Naoudom on 4/19/16.
//  Copyright © 2016 Lily Naoudom. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

using namespace std;

void quickSort(int[], int, int);
void merge(int[], int, int, int);
void mergeSort(int[], int, int);
double get_time();

int main() {

    srand(time(NULL));
    
    int arr[500], arr2[500];        //declare arrays
    int num;
    
    
    for (int i=0; i<500; i++) {     //populate first array with 500 random numbers in range 1-100
        num = rand()%101+1;
        arr[i] = num;
    }
    
    for (int i=0; i<500; i++) {     //copy elements from first array to second array to be used for merge sort
        arr2[i] = arr[i];           //ensures that merge sort is not using the array that was sorted using quick sort
    }
    
    cout<<"--Quick Sort--"<<endl;
    cout<<"Pre sort: ";
    for (int i=0; i<500; i++) {     //display contents of first array before implementing quick sort
        cout<<arr[i]<<" ";
    }
    
    cout<<endl;
    cout<<endl;
    
    double start_QS = get_time();   //get start time of quick sort
    
    quickSort(arr, 0, 499);         //call to quicksort function, passing the array and first and last indices
    
    double end_QS = get_time();     //get end time of quick sort
    double totalQSTime = end_QS - start_QS;     //calculate total run time of quick sort
    
    cout<<"Post sort: ";
    for (int i=0; i<500; i++) {     //display contents of first array after implementing quick sort
        cout<<arr[i]<<" ";
    }
    cout<<endl;
    
    cout<<endl;
    cout<<endl;
    
    //begin merge sort
    cout<<"--Merge Sort--"<<endl;
    cout<<"Pre sort: ";             //display contents of second array before implementing merge sort
    for (int i=0; i<500; i++) {
        cout<<arr2[i]<<" ";
    }
    
    cout<<endl;
    cout<<endl;
    
    double start_MS = get_time();   //get start time for merge sort
    
    mergeSort(arr2, 0, 499);        //call to merge sort function
    
    double end_MS = get_time();     //get end time for merge sort
    double totalMSTime = end_MS - start_MS; //calculate total run time of merge sort
    
    cout<<"Post sort: ";
    for (int i=0; i<500; i++) {     //display contents of second array after implementing merge sort
        cout<<arr2[i]<<" ";
    }
    
    cout<<endl;
    cout<<endl;
    
    //display time efficiency of each sorting algorithm
    cout<<"Total running time for Quick Sort: "<<totalQSTime <<" seconds."<<endl;
    cout<<"Total running time for Merge Sort: "<<totalMSTime <<" seconds."<<endl;
    
    return 0;
}

//quick sort
void quickSort(int arr[], int lo, int hi) {
    int i = lo, j = hi;             //lo is first index, hi is last index
    int tmp;
    int pivot = arr[(lo + hi) / 2]; //define pivot (here defined as middle element)

    //partition
    while (i <= j) {
        while (arr[i] < pivot)      //traverse forward through array until element (number)
            i++;                    //that is greater than or equal to pivot is found
        while (arr[j] > pivot)
            j--;                    //traverse backward through array until element
                                    //that is lesser than or equal to pivot is found
        
        if (i <= j) {               //after both numbers are found, swap only if the two pointers (lo and hi),
            tmp = arr[i];           //which are first and last index, have not met yet. (there still more numbers to compare to)
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
            j--;
        }
    }
    
    //recursively sort the newly partitioned elements
    if (lo < j)
        quickSort(arr, lo, j);
    if (i < hi)
        quickSort(arr, i, hi);
    if (i >= hi && lo >= j){
        
    }
}

//merge sort
void mergeSort(int arr[], int lo, int hi)
{
    if (arr[hi] > arr[lo]) {
        int m = lo+(hi-lo)/2;
        mergeSort(arr, lo, m);       //recursive call to merge sort
        mergeSort(arr, m+1, hi);
        merge(arr, lo, m, hi);
    } else if (arr[hi] < arr[lo]) {
        int m = lo+(hi-lo)/2;
        mergeSort(arr, lo, m);       //recursive call to merge sort
        mergeSort(arr, m+1, hi);
        merge(arr, lo, m, hi);
    }
    
}

//merge sort helper (merges smaller arrays together)

void merge(int arr[], int lo, int m, int hi)
{
    int i, j, k;
    int n1 = m - lo + 1;
    int n2 =  hi - m;
    
    //temp arrays (left and right split)
    int L[n1], R[n2];
    
    //copy contents
    for (i = 0; i < n1; i++)
        L[i] = arr[lo + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];
    
    //Merge the temp arrays (back into original array)
    i = 0;
    j = 0;
    k = lo;
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
    
    //copy any remaining elements in L
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    //copy any remaining elements in R
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}


//determine running time of functions
double get_time()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    double d = t.tv_sec + (double) t.tv_usec/1000000;
    return d;
}