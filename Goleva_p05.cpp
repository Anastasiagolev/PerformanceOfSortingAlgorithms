//Anastasia Golev  Project 5
//  Goleva_p05.cpp
//  Created by Anastasia Golev on 11/2/20.
//

/* This program measures the time performance of 5 sorting algorithms: bubble, select, insert, merge and quick sort. */

#include <iostream>
#include <algorithm>
#include <chrono>
#include <iomanip>
#define MAX 1000000

using namespace std;
using namespace chrono;


/* Bubble sort takes two parameters, a T array and an integer variable n which represents the input size. Bubble sort sorts an array through the methods of comparison and swap. With each iteration, the unsorted array becomes shorter. */
template <class T>
void bubbleSort( T arr[], int n){
    //    declare integer variables iter (iterations) and i
    int  iter, i;
    for (iter=1; iter<n;iter++){
        for (i=0;i<n-iter;i++){
            if (arr[i]>arr[i+1]){swap(arr[i], arr[i+1]);}
        }
    }
} //end bubble sort


/* Select sort takes two parameters, a T array and an integer variable n which represents the input size. To implement selectSort we must create swap function using dynamic allocation. */
template <class T>
void swap( T *p1, T* p2){
    T *temp = *p1;
    *p1=*p2;
    *p2=*temp;
}
template <class T>
void selectSort( T arr[], int n){
//    declare integer variables f (first), l (last) and min (min index)
    int  f, min;
    //for loop to traverse the unsorted region of the array
    for (f=0; f<n-1; f++){
        //step 1: select smallest item
        min= f; //we assume smallest item is at index 0 since arr[0] is part of the sorted region
        //step 2: find the actual smalles item beginning at index 1 since this is the first part of unsorted region
        for (int i=f+1; i< n; i++){
            if (arr[i]<arr[min]) {min=i;} //update smalled index =min
        //step 3: swap arr[mi] with the last item which is arr[n-iter]
            swap(arr[i], arr[min]);
            
        }
    }
} //end select sort


/* Insert sort takes two parameters, a T array, and an integer variable n which represents the input size. This algorithm sorts an array using the methods copy, shift and insert. When beggining the sort, arr[0] is sorted, arr[i-n-1] is unsorted. */
template <class T>
void insertSort( T arr[], int n){
    // i is the first index of the unsorted region
//    loc is the index of insetion in the sorted region
    for (int i=1; i<n; i++){
// T variable next holds the copy of arr[i], which represents the next index in the unsorted region
        T next =arr[i];
        int loc =i;
        while (loc>0 && arr[loc-1]>next){
            //perform shift
            arr[loc] =arr[loc-1];
            loc--;
        }
        arr[loc]=next; //insert copy
    }
} //end insertSort


/* In order to perform a merge sort, we create a function merge to store the halves arrays in a temporary array, later to combine them. */
template <class T>
void merge( T arr[], int f, int m, int l){
    //declare a T array of MAX size
    T temp[MAX];
    //first subarray
    int f1 =f, l1=m;
    //second subarray
    int f2 = m+1, l2=l;
//    set variable index equal to f1
    int idx=f1;
/*  While loop to do the comparison. While the index f1 is less than or equal to the middle index m (our first sub array) and index of f2 is less than l2, the last index (second subarray), we begin merging*/
    while (f1<=l1 && f2<=l){
        //assign smallest element of first half to temp[idx];
        if (arr[f1] <=arr[f2]) {temp[idx]=arr[f1]; f1++;}
        //else f2 is larger, we assign f2 to temp[idx]
        else {temp[idx]=arr[f2]; f2++;}
        idx++; //increment index
    }
    //copy the remaining elements
    while (f1<=l1){temp[idx] = arr[f1]; f1++; idx++;} //first half
    while(f2<=l2){temp[idx]=arr[f2]; f2++; idx++;} //second half
    
    //copy temp array to the original array
    for (idx=f; idx<=l; idx++){arr[idx]= temp[idx];}
}//end merge

template <class T>
void mergeSort(T arr[], int f, int l){
    if (f<l){
        //create integer variable m to represent the middle index of the array, we will use this to divide the array recursively
        int m = (f+l)/2;
        //recursive call of mergeSort
        mergeSort(arr, f, m);
        mergeSort(arr, m+1, l);
        merge(arr, f, m, l);
    }
}//end mergeSort


/* Quick sort algorithm uses a pivot point ( pivot index ) to connect positions in final sorted array. Items in the left are smaller and items to the right are larger. We create partition function in order to implement the pivot point. */
template <class T>
int partition( T arr[], int f, int l){
//    integer variable pivot declared as the last index of the array
    int pivot=arr[l];
    
//    integer variables L and R represent left and right, referring to the left and right side paritions of array
    int L=f, R=l;
    while (L<R){ 
        do{L++;} while(arr[L]<= pivot);
        do{R--;} while(arr[R]> pivot);
        if (L<R) swap(arr[L], arr[R]);
    }
    swap(arr[f], arr[R]);
    return R;
}//end partition

template <class T>
void quickSort( T arr[], int f, int l){
    if (f<l){
        //choose a pivot item p from array, partition the array about p
        int pIdx=partition(arr, f, l);
        
        //quick sort
        quickSort(arr, f, pIdx-1); //left region of array
        quickSort(arr, pIdx+1, l); //right region of array
    }
} //end quickSort

//function to generate random decimal numbers
double randomdoublegen(double min, double max){
    return (double)rand()/RAND_MAX*(max-min)+min;
}

int main() {
    /* initialize random seed: */
      srand (time(NULL));
    
    //Begin calculating running time of sorting algorithms using integers
    cout<<"Integers: "<<endl;
     
    cout<<"************Bubble sort Algorithm***********"<<endl;
    
    cout<<"Starting count bubble sort 100 entries"<<endl;
    auto start1 = high_resolution_clock::now();
    int farr1Size=100;
    int farr1[farr1Size];
    for (int i=0;i<farr1Size;i++){
        farr1[i]=rand() % 100+1;
    }
    
    bubbleSort(farr1, farr1Size);

    auto stop1 = high_resolution_clock::now();
    
    auto duration = duration_cast<milliseconds>(stop1-start1);
    
    cout<< duration.count()<<" milliseconds"<<endl;
    
    cout<<"Starting count bubble sort 1,000 entries"<<endl;
    auto start2 = high_resolution_clock::now();
    int farrSize2=1000;
    int farr2[farrSize2];
    for (int i=0;i<farrSize2;i++){
        farr2[i]=rand() % 1000+1;
    }
    
    bubbleSort(farr2, farrSize2);

    auto stop2 = high_resolution_clock::now();
    
    auto duration2 = duration_cast<milliseconds>(stop2-start2);
    
    cout<< duration2.count()<<" milliseconds"<<endl;
    
    cout<<"Starting count bubble sort 10,000 entries"<<endl;
    auto start3 = high_resolution_clock::now();
    int farrSize3=10000;
    int farr3[farrSize3];
    for (int i=0;i<farrSize3;i++){
        farr3[i]=rand() % 1000+1;
    }
    
    bubbleSort(farr3, farrSize3);

    auto stop3 = high_resolution_clock::now();
    
    auto duration3 = duration_cast<milliseconds>(stop3-start3);
    
    cout<< duration3.count()<<" milliseconds"<<endl;
    
    cout<<"Starting count bubble sort 100,000 entries"<<endl;
    auto start4 = high_resolution_clock::now();
    int farrSize4=100000;
    int farr4[farrSize4];
    for (int i=0;i<farrSize4;i++){
        farr4[i]=rand() % 100000+1;
    }
    
    bubbleSort(farr4, farrSize4);

    auto stop4 = high_resolution_clock::now();
    
    auto duration4 = duration_cast<milliseconds>(stop4-start4);
    
    cout<< duration4.count()<<" milliseconds"<<endl;
    
    cout<<"Starting count bubble sort 500,000 entries"<<endl;
    auto start5 = high_resolution_clock::now();
    int farrSize5=500000;
    int farr5[farrSize5];
    for (int i=0;i<farrSize5;i++){
        farr5[i]=rand() % 500000+1;
    }
    
    bubbleSort(farr5, farrSize5);

    auto stop5 = high_resolution_clock::now();
    
    auto duration5 = duration_cast<milliseconds>(stop5-start5);
    
    cout<< duration5.count()<<" milliseconds"<<endl;
  
    cout<<"***********Select Sort Algorithm*********"<<endl;
    
    cout<<"Starting count select sort 100 entries"<<endl;
    auto selectstart1 = high_resolution_clock::now();
    int selectarr1Size=100;
    int selectarr1[selectarr1Size];
    for (int i=0;i<selectarr1Size;i++){
        selectarr1[i]=rand() % 100+1;
    }
    
    selectSort(selectarr1, selectarr1Size);

    auto selectstop1 = high_resolution_clock::now();
    
    auto selectduration1 = duration_cast<milliseconds>(selectstop1-selectstart1);
    
    cout<< selectduration1.count()<<" milliseconds"<<endl;
    
    cout<<"Starting count select sort 1,000 entries"<<endl;
    auto selectstart2 = high_resolution_clock::now();
    int selectarr2Size=1000;
    int selectarr2[selectarr2Size];
    for (int i=0;i<selectarr2Size;i++){
        selectarr2[i]=rand() % 1000+1;
    }
  
    selectSort(selectarr2, selectarr2Size);

    auto selectstop2 = high_resolution_clock::now();
    
    auto selectduration2 = duration_cast<milliseconds>(selectstop2-selectstart2);
    
    cout<< selectduration2.count()<<" milliseconds"<<endl;
    
    cout<<"Starting count select sort 10,000 entries"<<endl;
    
    auto selectstart3 = high_resolution_clock::now();
    int selectarr3Size=10000;
    int selectarr3[selectarr3Size];
    for (int i=0;i<selectarr3Size;i++){
        selectarr3[i]=rand() % 10000+1;
    }
    
    selectSort(selectarr3, selectarr3Size);

    auto selectstop3 = high_resolution_clock::now();
    
    auto selectduration3 = duration_cast<milliseconds>(selectstop3-selectstart3);
    
    cout<< selectduration3.count()<<" milliseconds"<<endl;
    
    
    cout<<"Starting count select sort 100,000 entries"<<endl;
    auto selectstart4 = high_resolution_clock::now();
    int selectarr4Size=100000;
    int selectarr4[selectarr4Size];
    for (int i=0;i<selectarr4Size;i++){
        selectarr4[i]=rand() % 100000+1;
    }
    
  
    selectSort(selectarr4, selectarr4Size);

    auto selectstop4 = high_resolution_clock::now();
    
    auto selectduration4 = duration_cast<milliseconds>(selectstop4-selectstart4);
    
    cout<< selectduration4.count()<<" milliseconds"<<endl;
     
    
    cout<<"Starting count select sort 500,000 entries"<<endl;
    auto selectstart5 = high_resolution_clock::now();
    int selectarr5Size=500000;
    int selectarr5[selectarr5Size];
    for (int i=0;i<selectarr5Size;i++){
        selectarr5[i]=rand() % 500000+1;
    }
    
    selectSort(selectarr5, selectarr5Size);

    auto selectstop5 = high_resolution_clock::now();
    
    auto selectduration5 = duration_cast<milliseconds>(selectstop5-selectstart5);
    
    cout<< selectduration5.count()<<" milliseconds"<<endl;
     
    
    
    cout<<"***********Insert Sort Algorithm*********"<<endl;
    
    cout<<"Starting count insert sort 100 entries"<<endl;
    auto insertstart1 = high_resolution_clock::now();
    int insertarr1Size=100;
    int insertarr1[insertarr1Size];
    for (int i=0;i<insertarr1Size;i++){
        insertarr1[i]=rand() % 100+1;
    }
    
  
    insertSort(insertarr1, insertarr1Size);

    auto insertstop1 = high_resolution_clock::now();
    
    //getting duration using microseconds because milliseconds would result in 0
    //manually convert result to milliseconds
    auto insertduration1 = duration_cast<microseconds>(insertstop1-insertstart1);
    
    cout<< insertduration1.count()<<" milliseconds"<<endl;
    
    cout<<"Starting count insert sort 1000 entries"<<endl;
    auto insertstart2 = high_resolution_clock::now();
    int insertarr2Size=1000;
    int insertarr2[insertarr2Size];
    for (int i=0;i<insertarr2Size;i++){
        insertarr2[i]=rand() % 1000+1;
    }
    
  
    insertSort(insertarr2, insertarr2Size);

    auto insertstop2 = high_resolution_clock::now();
    
    //getting duration using microseconds because milliseconds would result in 0
    //manually convert result to milliseconds
    auto insertduration2 = duration_cast<microseconds>(insertstop2-insertstart2);
    
    cout<< insertduration2.count()<<" milliseconds"<<endl;
    
    cout<<"Starting count insert sort 10,000 entries"<<endl;
    auto insertstart3 = high_resolution_clock::now();
    int insertarr3Size=10000;
    int insertarr3[insertarr3Size];
    for (int i=0;i<insertarr3Size;i++){
        insertarr3[i]=rand() % 10000+1;
    }
    
    insertSort(insertarr3, insertarr3Size);

    auto insertstop3 = high_resolution_clock::now();
    
    auto insertduration3 = duration_cast<milliseconds>(insertstop3-insertstart3);
    
    cout<< insertduration3.count()<<" milliseconds"<<endl;
    
    cout<<"Starting count insert sort 100,000 entries"<<endl;
    auto insertstart4 = high_resolution_clock::now();
    int insertarr4Size=100000;
    int insertarr4[insertarr4Size];
    for (int i=0;i<insertarr4Size;i++){
        insertarr4[i]=rand() % 100000+1;
    }
  
    insertSort(insertarr4, insertarr4Size);

    auto insertstop4 = high_resolution_clock::now();
    
    auto insertduration4 = duration_cast<milliseconds>(insertstop4-insertstart4);
    
    cout<< insertduration4.count()<<" milliseconds"<<endl;
    
    cout<<"Starting count insert sort 500,000 entries"<<endl;
    auto insertstart5 = high_resolution_clock::now();
    int insertarr5Size=500000;
    int insertarr5[insertarr5Size];
    for (int i=0;i<insertarr5Size;i++){
        insertarr5[i]=rand() % 500000+1;
    }
    
    insertSort(insertarr5, insertarr5Size);
    auto insertstop5 = high_resolution_clock::now();
    
    auto insertduration5 = duration_cast<milliseconds>(insertstop5-insertstart5);
    
    cout<< insertduration5.count()<<" milliseconds"<<endl;

    
    cout<<"***********Merge Sort Algorithm*********"<<endl;
    
    cout<<"Starting count merge sort 100 entries"<<endl;
    auto mergestart1 = high_resolution_clock::now();
    int mergearr1Size=100;
    int mergearr1[mergearr1Size];
    for (int i=0;i<mergearr1Size;i++){
        mergearr1[i]=rand() % 100+1;
    }
    
    mergeSort(mergearr1,mergearr1[0], mergearr1[99]);

    auto mergestop1 = high_resolution_clock::now();
    
    //milliseconds would result in 0, so do *1000 to see result
    auto mergeduration1 = duration_cast<milliseconds>((mergestop1-mergestart1)*1000);
    
    cout<< mergeduration1.count()<<" milliseconds"<<endl;
    
    cout<<"Starting count merge sort 1,000 entries"<<endl;
    auto mergestart2 = high_resolution_clock::now();
    int mergearr2Size=1000;
    int mergearr2[mergearr2Size];
    for (int i=0;i<mergearr2Size;i++){
        mergearr2[i]=rand() % 1000+1;
    }
    
  
    mergeSort(mergearr1,mergearr2[0], mergearr2[999]);

    auto mergestop2 = high_resolution_clock::now();
    
    //milliseconds would result in 0, multiply by *1000 to see result
    auto mergeduration2 = duration_cast<milliseconds>((mergestop2-mergestart2)*1000);
    
    cout<< mergeduration2.count()<<" milliseconds"<<endl;
    
    cout<<"Starting count merge sort 10,000 entries"<<endl;
    auto mergestart3 = high_resolution_clock::now();
    int mergearr3Size=10000;
    int mergearr3[mergearr3Size];
    for (int i=0;i<mergearr3Size;i++){
        mergearr3[i]=rand() % 10000+1;
    }
  
    mergeSort(mergearr3,mergearr3[0], mergearr3[9999]);

    auto mergestop3 = high_resolution_clock::now();
    
    auto mergeduration3 = duration_cast<milliseconds>((mergestop3-mergestart3)*1000);
    
    cout<< mergeduration3.count()<<" milliseconds"<<endl;
    
    cout<<"Starting count merge sort 100,000 entries"<<endl;
    auto mergestart4 = high_resolution_clock::now();
    int mergearr4Size=100000;
    int mergearr4[mergearr4Size];
    for (int i=0;i<mergearr4Size;i++){
        mergearr4[i]=rand() % 100000+1;
    }
    
    mergeSort(mergearr4,mergearr4[0], mergearr4[99999]);

    auto mergestop4 = high_resolution_clock::now();
    
    auto mergeduration4 = duration_cast<milliseconds>((mergestop4-mergestart4));
    
    cout<< mergeduration4.count()<<" milliseconds"<<endl;
    
    
    cout<<"Starting count merge sort 500,000 entries"<<endl;
    auto mergestart5 = high_resolution_clock::now();
    int mergearr5Size=500000;
    int mergearr5[mergearr5Size];
    for (int i=0;i<mergearr5Size;i++){
        mergearr5[i]=rand() % 500000+1;
    }
    
    mergeSort(mergearr5,mergearr5[0], mergearr5[49999]);

    auto mergestop5 = high_resolution_clock::now();
    
    auto mergeduration5 = duration_cast<milliseconds>((mergestop5-mergestart5));
    
    cout<< mergeduration5.count()<<" milliseconds"<<endl;
    
    cout<<"***********Quick Sort Algorithm*********"<<endl;
    
    cout<<"Starting count quick sort 100 entries"<<endl;
    auto quickstart1 = high_resolution_clock::now();
    int quickarr1Size=100;
    int quickarr1[quickarr1Size];
    for (int i=0;i<quickarr1Size;i++){
        quickarr1[i]=rand() % 100+1;
    }
    
    quickSort(quickarr1,quickarr1[0], quickarr1[99]);

    auto quickstop1 = high_resolution_clock::now();
    
    //milliseconds would result in 0, so do *1000 to see result
    auto quickduration1 = duration_cast<milliseconds>((quickstop1-quickstart1)*1000);
    
    cout<< quickduration1.count()<<" milliseconds"<<endl;
    
    cout<<"Starting count quick sort 1,000 entries"<<endl;
    auto quickstart2 = high_resolution_clock::now();
    int quickarr2Size=1000;
    int quickarr2[quickarr2Size];
    for (int i=0;i<quickarr2Size;i++){
        quickarr2[i]=rand() % 1000+1;
    }
    
    quickSort(quickarr1,quickarr2[0], quickarr2[999]);

    auto quickstop2 = high_resolution_clock::now();
    
    //milliseconds would result in 0, multiply by 1000
    auto quickduration2 = duration_cast<milliseconds>((quickstop2-quickstart2)*1000);
    
    cout<< quickduration2.count()<<" milliseconds"<<endl;
    
    cout<<"Starting count quick sort 10,000 entries"<<endl;
    auto quickstart3 = high_resolution_clock::now();
    int quickarr3Size=10000;
    int quickarr3[quickarr3Size];
    for (int i=0;i<quickarr3Size;i++){
        quickarr3[i]=rand() % 10000+1;
    }
    
  
    quickSort(quickarr3,quickarr3[0], quickarr3[9999]);

    auto quickstop3 = high_resolution_clock::now();
    
    //milliseconds would result in 0, multiply by 1000
    auto quickduration3 = duration_cast<milliseconds>((quickstop3-quickstart3)*1000);
    
    cout<< quickduration3.count()<<" milliseconds"<<endl;
    
    cout<<"Starting count quick sort 100,000 entries"<<endl;
    auto quickstart4 = high_resolution_clock::now();
    int quickarr4Size=100000;
    int quickarr4[quickarr4Size];
    for (int i=0;i<quickarr4Size;i++){
        quickarr4[i]=rand() % 100000+1;
    }
    
    quickSort(quickarr4,quickarr4[0], quickarr4[99999]);

    auto quickstop4 = high_resolution_clock::now();
    
    auto quickduration4 = duration_cast<milliseconds>((quickstop4-quickstart4));
    
    cout<< quickduration4.count()<<" milliseconds"<<endl;
     
    cout<<"Starting count quick sort 500,000 entries"<<endl;
    auto quickstart5 = high_resolution_clock::now();
    int quickarr5Size=500000;
    int quickarr5[quickarr5Size];
    for (int i=0;i<quickarr5Size;i++){
        quickarr5[i]=rand() % 500000+1;
    }
    
  
    quickSort(quickarr5,quickarr5[0], quickarr5[499999]);

    auto quickstop5 = high_resolution_clock::now();
    
    auto quickduration5 = duration_cast<milliseconds>((quickstop5-quickstart5));
    
    cout<< quickduration5.count()<<" milliseconds"<<endl;
    
    
    //Begin calculating running time of sorting algorithms using doubles
    cout<<"Doubles: "<<endl;
     
    cout<<"************ Bubble sort Algorithm ***********"<<endl;
    
    cout<<"Starting count bubble sort 100 entries"<<endl;
    auto dbubblestart1 = high_resolution_clock::now();
    int dbubblearr1Size=100;
    double dbubblearr1[dbubblearr1Size];
    for (int i=0;i<dbubblearr1Size;i++){
        dbubblearr1[i]=randomdoublegen(1.0, 100.0);
    }
  
    bubbleSort(dbubblearr1, dbubblearr1Size);

    auto dbubblestop1 = high_resolution_clock::now();
    
    //cast to microseconds because milliseconds would result in 0, manually convert to milliseconds
    auto dbubbleduration = duration_cast<microseconds>(dbubblestop1-dbubblestart1);
    
    cout<< dbubbleduration.count()<<" milliseconds"<<endl;
    
    cout<<"Starting count bubble sort 1,000 entries"<<endl;
    auto dbubblestart2 = high_resolution_clock::now();
    int dbubblearrSize2=1000;
    double dbubblearr2[dbubblearrSize2];
    for (int i=0;i<dbubblearrSize2;i++){
        dbubblearr2[i]=randomdoublegen(1.0, 1000.0);
    }
    
    bubbleSort(dbubblearr2, dbubblearrSize2);

    auto dbubblestop2 = high_resolution_clock::now();
    
    auto dbubbleduration2 = duration_cast<milliseconds>(dbubblestop2-dbubblestart2);
    
    cout<< dbubbleduration2.count()<<" milliseconds"<<endl;
    
    cout<<"Starting count bubble sort 10,000 entries"<<endl;
    auto dbubblestart3 = high_resolution_clock::now();
    int dbubblearrSize3=10000;
    double dbubblearr3[dbubblearrSize3];
    for (int i=0;i<dbubblearrSize3;i++){
        dbubblearr3[i]=randomdoublegen(1.0, 10000.0);
    }
    
    bubbleSort(dbubblearr3, dbubblearrSize3);

    auto dbubblestop3 = high_resolution_clock::now();
    
    auto dbubbleduration3 = duration_cast<milliseconds>(dbubblestop3-dbubblestart3);
    
    cout<< dbubbleduration3.count()<<" milliseconds"<<endl;
    
    cout<<"Starting count bubble sort 100,000 entries"<<endl;
    auto dbubblestart4 = high_resolution_clock::now();
    int dbubblearrSize4=100000;
    double dbubblearr4[dbubblearrSize4];
    for (int i=0;i<dbubblearrSize4;i++){
        dbubblearr4[i]=randomdoublegen(1.0, 100000.0);
    }
    
    bubbleSort(dbubblearr4, dbubblearrSize4);

    auto dbubblestop4 = high_resolution_clock::now();
    
    auto dbubbleduration4 = duration_cast<milliseconds>(dbubblestop4-dbubblestart4);
    
    cout<< dbubbleduration4.count()<<" milliseconds"<<endl;
    
    
    cout<<"Starting count bubble sort 500,000 entries"<<endl;
    auto dbubblestart5 = high_resolution_clock::now();
    int dbubblearrSize5=500000;
    double dbubblearr5[dbubblearrSize5];
    for (int i=0;i<dbubblearrSize5;i++){
        dbubblearr5[i]=randomdoublegen(1.0, 500000.0);
    }
    
    bubbleSort(dbubblearr5, dbubblearrSize5);

    auto dbubblestop5 = high_resolution_clock::now();
    
    auto dbubbleduration5 = duration_cast<milliseconds>(dbubblestop5-dbubblestart5);
    
    cout<< dbubbleduration5.count()<<" milliseconds"<<endl;
  
    cout<<"***********Select Sort Algorithm*********"<<endl;
    
    cout<<"Starting count select sort 100 entries"<<endl;
    auto dselectstart1 = high_resolution_clock::now();
    int dselectarr1Size=100;
    double dselectarr1[dselectarr1Size];
    for (int i=0;i<dselectarr1Size;i++){
        dselectarr1[i]=randomdoublegen(1.0, 100.0);
    }
    
  
    selectSort(dselectarr1, dselectarr1Size);

    auto dselectstop1 = high_resolution_clock::now();
    
    //cast to microseconds because milliseconds would result in 0, manually convert to milliseconds
    auto dselectduration1 = duration_cast<microseconds>(dselectstop1-dselectstart1);
    
    cout<< dselectduration1.count()<<" milliseconds"<<endl;
    
    
    cout<<"Starting count select sort 1,000 entries"<<endl;
    auto dselectstart2 = high_resolution_clock::now();
    int dselectarr2Size=1000;
    double dselectarr2[dselectarr2Size];
    for (int i=0;i<dselectarr2Size;i++){
        dselectarr2[i]=randomdoublegen(1.0, 1000.0);
    }
    
  
    selectSort(dselectarr2, dselectarr2Size);

    auto dselectstop2 = high_resolution_clock::now();
    
    auto dselectduration2 = duration_cast<milliseconds>(dselectstop2-dselectstart2);
    
    cout<< dselectduration2.count()<<" milliseconds"<<endl;
    
    cout<<"Starting count select sort 10,000 entries"<<endl;
    
    auto dselectstart3 = high_resolution_clock::now();
    int dselectarr3Size=10000;
    double dselectarr3[dselectarr3Size];
    for (int i=0;i<dselectarr3Size;i++){
        dselectarr3[i]=randomdoublegen(1.0, 10000.0);
    }
    
  
    selectSort(dselectarr3, dselectarr3Size);

    auto dselectstop3 = high_resolution_clock::now();
    
    auto dselectduration3 = duration_cast<milliseconds>(dselectstop3-dselectstart3);
    
    cout<< dselectduration3.count()<<" milliseconds"<<endl;
    
    
    cout<<"Starting count select sort 100,000 entries"<<endl;
    
    auto dselectstart4 = high_resolution_clock::now();
    int dselectarr4Size=100000;
    double dselectarr4[dselectarr4Size];
    for (int i=0;i<dselectarr4Size;i++){
        dselectarr4[i]=randomdoublegen(1.0, 100000.0);
    }
    
  
    selectSort(dselectarr4, dselectarr4Size);

    auto dselectstop4 = high_resolution_clock::now();
    
    auto dselectduration4 = duration_cast<milliseconds>(dselectstop4-dselectstart4);
    
    cout<< dselectduration4.count()<<" milliseconds"<<endl;
     
    
    cout<<"Starting count select sort 500,000 entries"<<endl;
    auto dselectstart5 = high_resolution_clock::now();
    int dselectarr5Size=500000;
    double dselectarr5[dselectarr5Size];
    for (int i=0;i<dselectarr5Size;i++){
        dselectarr5[i]=randomdoublegen(1.0, 500000.0);
    }
    
  
    selectSort(dselectarr5, dselectarr5Size);

    auto dselectstop5 = high_resolution_clock::now();
    
    auto dselectduration5 = duration_cast<milliseconds>(dselectstop5-dselectstart5);
    
    cout<< dselectduration5.count()<<" milliseconds"<<endl;
   
    cout<<"***********Insert Sort Algorithm*********"<<endl;
     
    cout<<"Starting count insert sort 100 entries"<<endl;
    auto dinsertstart1 = high_resolution_clock::now();
    int dinsertarr1Size=100;
    double dinsertarr1[dinsertarr1Size];
    for (int i=0;i<dinsertarr1Size;i++){
        dinsertarr1[i]=randomdoublegen(1.0, 100.0);
    }
    
  
    insertSort(dinsertarr1, dinsertarr1Size);

    auto dinsertstop1 = high_resolution_clock::now();
    
    //cast to microseconds because milliseconds would result in 0, manually convert to milliseconds
    auto dinsertduration1 = duration_cast<microseconds>(dinsertstop1-dinsertstart1);
    
    cout<< dinsertduration1.count()<<" milliseconds"<<endl;
    
    cout<<"Starting count insert sort 1000 entries"<<endl;
    auto dinsertstart2 = high_resolution_clock::now();
    int dinsertarr2Size=1000;
    double dinsertarr2[dinsertarr2Size];
    for (int i=0;i<dinsertarr2Size;i++){
        dinsertarr2[i]=randomdoublegen(1.0, 1000.0);
    }
    
  
    insertSort(dinsertarr2, dinsertarr2Size);

    auto dinsertstop2 = high_resolution_clock::now();
    
    //cast to microseconds because milliseconds would result in 0, manually convert to milliseconds
    auto dinsertduration2 = duration_cast<microseconds>(dinsertstop2-dinsertstart2);
    
    cout<< dinsertduration2.count()<<" milliseconds"<<endl;
    
    cout<<"Starting count insert sort 10,000 entries"<<endl;
    auto dinsertstart3 = high_resolution_clock::now();
    int dinsertarr3Size=10000;
    double dinsertarr3[dinsertarr3Size];
    for (int i=0;i<dinsertarr3Size;i++){
        dinsertarr3[i]=randomdoublegen(1.0, 10000.0);
    }
    
  
    insertSort(dinsertarr3, dinsertarr3Size);

    auto dinsertstop3 = high_resolution_clock::now();
    
    auto dinsertduration3 = duration_cast<milliseconds>(dinsertstop3-dinsertstart3);
    
    cout<< dinsertduration3.count()<<" milliseconds"<<endl;
    
    cout<<"Starting count insert sort 100,000 entries"<<endl;
    auto dinsertstart4 = high_resolution_clock::now();
    int dinsertarr4Size=100000;
    double dinsertarr4[dinsertarr4Size];
    for (int i=0;i<dinsertarr4Size;i++){
        dinsertarr4[i]=randomdoublegen(1.0, 100000.0);
    }
    
  
    insertSort(dinsertarr4, dinsertarr4Size);

    auto dinsertstop4 = high_resolution_clock::now();
    
    auto dinsertduration4 = duration_cast<milliseconds>(dinsertstop4-dinsertstart4);
    
    cout<< dinsertduration4.count()<<" milliseconds"<<endl;
    
    
    cout<<"Starting count insert sort 500,000 entries"<<endl;
    auto dinsertstart5 = high_resolution_clock::now();
    int dinsertarr5Size=500000;
    double dinsertarr5[dinsertarr5Size];
    for (int i=0;i<dinsertarr5Size;i++){
        dinsertarr5[i]=randomdoublegen(1.0, 500000.0);
    }
    
  
    insertSort(dinsertarr5, dinsertarr5Size);

    auto dinsertstop5 = high_resolution_clock::now();
    
    auto dinsertduration5 = duration_cast<milliseconds>(dinsertstop5-dinsertstart5);
    
    cout<< dinsertduration5.count()<<" milliseconds"<<endl;
    
    
    cout<<"***********Merge Sort Algorithm*********"<<endl;
    
    cout<<"Starting count merge sort 100 entries"<<endl;
    auto dmergestart1 = high_resolution_clock::now();
    int dmergearr1Size=100;
    double dmergearr1[dmergearr1Size];
    for (int i=0;i<dmergearr1Size;i++){
        dmergearr1[i]=randomdoublegen(1.0, 100.0);
    }
    
  
    mergeSort(dmergearr1,dmergearr1[0], dmergearr1[99]);

    auto dmergestop1 = high_resolution_clock::now();
    
    //milliseconds would result in 0, so multiply *1000 to see result
    auto dmergeduration1 = duration_cast<milliseconds>((dmergestop1-dmergestart1)*1000);
    
    cout<< dmergeduration1.count()<<" milliseconds"<<endl;
    
    cout<<"Starting count merge sort 1,000 entries"<<endl;
    auto dmergestart2 = high_resolution_clock::now();
    int dmergearr2Size=1000;
    double dmergearr2[dmergearr2Size];
    for (int i=0;i<dmergearr2Size;i++){
        dmergearr2[i]=randomdoublegen(1.0, 1000.0);
    }
    
  
    mergeSort(dmergearr1,dmergearr2[0], dmergearr2[999]);

    auto dmergestop2 = high_resolution_clock::now();
    
    //milliseconds would result in 0, so multiply *1000 to see result
    auto dmergeduration2 = duration_cast<milliseconds>((dmergestop2-dmergestart2)*1000);
    
    cout<< dmergeduration2.count()<<" milliseconds"<<endl;
    
    cout<<"Starting count merge sort 10,000 entries"<<endl;
    auto dmergestart3 = high_resolution_clock::now();
    int dmergearr3Size=10000;
    double dmergearr3[dmergearr3Size];
    for (int i=0;i<dmergearr3Size;i++){
        dmergearr3[i]=randomdoublegen(1.0, 10000.0);
    }
    
  
    mergeSort(dmergearr3,dmergearr3[0], dmergearr3[9999]);

    auto dmergestop3 = high_resolution_clock::now();
    
    //milliseconds would result in 0, so multiply *1000 to see result
    auto dmergeduration3 = duration_cast<milliseconds>((dmergestop3-dmergestart3)*1000);
    
    cout<< dmergeduration3.count()<<" milliseconds"<<endl;
    
    cout<<"Starting count merge sort 100,000 entries"<<endl;
    auto dmergestart4 = high_resolution_clock::now();
    int dmergearr4Size=100000;
    double dmergearr4[dmergearr4Size];
    for (int i=0;i<dmergearr4Size;i++){
        dmergearr4[i]=randomdoublegen(1.0, 100000.0);
    }
    
  
    mergeSort(dmergearr4,dmergearr4[0], dmergearr4[99999]);

    auto dmergestop4 = high_resolution_clock::now();
    
    auto dmergeduration4 = duration_cast<milliseconds>((dmergestop4-dmergestart4));
    
    cout<< dmergeduration4.count()<<" milliseconds"<<endl;
    

    cout<<"Starting count merge sort 500,000 entries"<<endl;
    auto dmergestart5 = high_resolution_clock::now();
    int dmergearr5Size=500000;
    double dmergearr5[dmergearr5Size];
    for (int i=0;i<dmergearr5Size;i++){
        dmergearr5[i]=randomdoublegen(1.0, 500000.0);
    }
    
  
    mergeSort(dmergearr5,dmergearr5[0], dmergearr5[49999]);

    auto dmergestop5 = high_resolution_clock::now();
    
    auto dmergeduration5 = duration_cast<milliseconds>((dmergestop5-dmergestart5));
    
    cout<< dmergeduration5.count()<<" milliseconds"<<endl;
    
    
    cout<<"***********Quick Sort Algorithm*********"<<endl;
    
    cout<<"Starting count quick sort 100 entries"<<endl;
    auto dquickstart1 = high_resolution_clock::now();
    int dquickarr1Size=100;
    double dquickarr1[dquickarr1Size];
    for (int i=0;i<dquickarr1Size;i++){
        dquickarr1[i]=randomdoublegen(1.0, 100.0);
    }
    
  
    quickSort(dquickarr1,dquickarr1[0], dquickarr1[99]);

    auto dquickstop1 = high_resolution_clock::now();
    
    //milliseconds would result in 0, so multiply *1000 to see result
    auto dquickduration1 = duration_cast<milliseconds>((dquickstop1-dquickstart1)*1000);
    
    cout<< dquickduration1.count()<<" milliseconds"<<endl;
    
    cout<<"Starting count quick sort 1,000 entries"<<endl;
    auto dquickstart2 = high_resolution_clock::now();
    int dquickarr2Size=1000;
    double dquickarr2[dquickarr2Size];
    for (int i=0;i<dquickarr2Size;i++){
        dquickarr2[i]=randomdoublegen(1.0, 1000.0);
    }
    
  
    quickSort(dquickarr1,dquickarr2[0], dquickarr2[999]);

    auto dquickstop2 = high_resolution_clock::now();
    
    //milliseconds would result in 0, so multiply *1000 to see result
    auto dquickduration2 = duration_cast<milliseconds>((dquickstop2-dquickstart2)*1000);
    
    cout<< dquickduration2.count()<<" milliseconds"<<endl;
    
    cout<<"Starting count quick sort 10,000 entries"<<endl;
    auto dquickstart3 = high_resolution_clock::now();
    int dquickarr3Size=10000;
    double dquickarr3[dquickarr3Size];
    for (int i=0;i<dquickarr3Size;i++){
        dquickarr3[i]=randomdoublegen(1.0, 10000.0);
    }
    
  
    quickSort(dquickarr3,dquickarr3[0], dquickarr3[9999]);

    auto dquickstop3 = high_resolution_clock::now();
    
    //milliseconds would result in 0, so multiply *1000 to see result
    auto dquickduration3 = duration_cast<milliseconds>((dquickstop3-dquickstart3)*1000);
    
    cout<< dquickduration3.count()<<" milliseconds"<<endl;
    
    cout<<"Starting count quick sort 100,000 entries"<<endl;
    auto dquickstart4 = high_resolution_clock::now();
    int dquickarr4Size=100000;
    double dquickarr4[dquickarr4Size];
    for (int i=0;i<dquickarr4Size;i++){
        dquickarr4[i]=randomdoublegen(1.0, 100000.0);
    }
    
    quickSort(dquickarr4,dquickarr4[0], dquickarr4[99999]);

    auto dquickstop4 = high_resolution_clock::now();
    
    auto dquickduration4 = duration_cast<milliseconds>((dquickstop4-dquickstart4));
    
    cout<< dquickduration4.count()<<" milliseconds"<<endl;
     
    cout<<"Starting count quick sort 500,000 entries"<<endl;
    auto dquickstart5 = high_resolution_clock::now();
    int dquickarr5Size=500000;
    double dquickarr5[dquickarr5Size];
    for (int i=0;i<dquickarr5Size;i++){
        dquickarr5[i]=randomdoublegen(1.0, 500000.0);
    }
    
  
    quickSort(dquickarr5,dquickarr5[0], dquickarr5[499999]);

    auto dquickstop5 = high_resolution_clock::now();
    
    auto dquickduration5 = duration_cast<milliseconds>((dquickstop5-dquickstart5));
    
    cout<< dquickduration5.count()<<" milliseconds"<<endl;
     
    
    return 0;
}
