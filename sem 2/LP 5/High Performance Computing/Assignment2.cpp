#include <bits/stdc++.h>

using namespace std;
using namespace std:: chrono; //to measure speed and openmp used for parallelism

void sequentialBubbleSort(vector<int> &arr)
{
   int n=arr.size(); //we are sorting 'arr'
   for(int i=0;i<n-1;i++)
   {
       for(int j=0;j<n-i-1;j++)
       {
           if(arr[j]>arr[j+1])
           swap(arr[j],arr[j+1]);
       }
   }
}

void parallelBubbleSort(vector<int> &arr)
{
   int n=arr.size();
   for(int i=0;i<n;i++)
   {
       if(i%2==0)//odd even transposition sorting
       {
           #pragma omp parallel for
           for(int j=0;j<n-1;j+=2)
           {
               if(arr[j]>arr[j+1])
               swap(arr[j],arr[j+1]);
           }
       }
       else{
           #pragma omp parallel for
           for(int j=1;j<n-1;j+=2)
           {
               if(arr[j]>arr[j+1])
               swap(arr[j],arr[j+1]);
           }
       }
   }
}

void merge(vector<int> &arr, int l, int m, int r)
{
   int n1=m-l+1; //size of vector L
   int n2=r-m;
   vector<int> L(n1), R(n2);
   for(int i=0;i<n1;i++)
       L[i]=arr[l+i];
   for(int i=0;i<n2;i++)
       R[i]=arr[m+1+i];
       
   int i=0,j=0, k=l;   
   while(i<n1 && j<n2)
   {
       arr[k++] = (L[i]<= R[j]) ? L[i++] : R[j++];
   } 
   while(i<n1)
   arr[k++]=L[i++];
   while(j<n2)
   arr[k++]=R[j++];
}

void mergeSortSequential(vector<int> &arr, int l, int r)
{
   if(l<r)
   {
       int m= (l+r)/2;
       mergeSortSequential(arr, l, m);
       mergeSortSequential(arr, m+1, r);
       merge(arr, l,m ,r);
   }
}

void mergeSortParallel(vector<int>&arr, int l, int r, int depth=0)
{
   if(l<r)
   {
       int m=(l+r)/2;
       if(depth<=3) //avoids too many threads
       {
           #pragma omp parallel sections 
           {
               #pragma omp section
               mergeSortParallel(arr, l,m, depth+1);
               #pragma omp section
               mergeSortParallel(arr, m+1, r, depth+1);
           }
       }
       else{
           mergeSortSequential(arr, l, m);
           mergeSortSequential(arr, m+1, r);
       }
       merge(arr, l, m, r);
   }
}

void printArray(vector<int> &arr)
{
   for(auto it:arr)
   cout<<it<< " ";
   cout<<endl;
}

int main ()
{
   int size=10000; // reverse order is worst sort
   vector<int> arr(size);
   for(int i=0; i<size; i++)
   arr[i]=size-i; // reverse

   vector<int> arr1=arr, arr2=arr, arr3=arr, arr4=arr; //storing val of original array in 4 arrays

   auto start = high_resolution_clock::now();
   sequentialBubbleSort(arr1);
   auto end = high_resolution_clock::now();
   duration<double> seqbubble= end-start;
   // printArray(arr1);
   cout <<"Sequential bubble sort time: "<<seqbubble.count()<< "seconds\n";

   start = high_resolution_clock::now();
   parallelBubbleSort(arr2);
   end = high_resolution_clock::now();
   duration<double> parbubble= end-start;
   // printArray(arr2);
   cout <<"Parallel bubble sort time: "<<parbubble.count()<< "seconds\n";

   start = high_resolution_clock::now();
   mergeSortSequential(arr3,0,size-1);
   end = high_resolution_clock::now();
   duration<double> seqmerge= end-start;
   // printArray(arr3);
   cout <<"Sequential merge sort time: "<<seqmerge.count()<< "seconds\n";

   start = high_resolution_clock::now();
   mergeSortParallel(arr4,0,size-1);
   end = high_resolution_clock::now();
   duration<double> parmerge= end-start;
   // printArray(arr4);
   cout <<"Parallel merge sort time: "<<parmerge.count()<< "seconds\n";
}