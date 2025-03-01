//
//  main.cpp
//  Algorithms
//
//  Created by Chris Kreienkamp on 3/10/21.
//

#include <iostream>
#include <vector>

using namespace std;

//### IDEAS ###
// include both the number and a comparitively-sized block to give better visual information https://www.toptal.com/developers/sorting-algorithms, https://visualgo.net/bn/sorting, https://www.cs.usfca.edu/~galles/visualization/ComparisonSort.html


void insertion_sort(vector<int>& A) {           // p. 24
    for (int j=1; j<A.size(); j++) {
        int key = A[j];
        // Insert A[j] into the sorted sequence A[1..j-1]
        int i = j-1;
        while (i>-1 && A[i]>key) {
            A[i+1] = A[i];
            i--;
        }
        A[i+1] = key;
    }
}

void selection_sort(vector<int>& A) {           // p. 27
    for (int i=0; i<A.size()-1; i++) {
        int currentMinId = i;
        for (int j=i+1; j<A.size(); j++) {
            if (A[j] < A[currentMinId]) {currentMinId = j;}
        }
        int minValue = A[currentMinId];
        A[currentMinId] = A[i];
        A[i] = minValue;
    }
}

void merge(vector<int>& A, int left, int mid, int right) {      // p. 29
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<int> L(n1+1);
    vector<int> R(n2+1);
    for (int i=0; i<n1; i++) {
        L[i] = A[left+i];
    }
    for (int j=0; j<n2; j++) {
        R[j] = A[mid+j+1];
    }
    L[n1] = INT_MAX;
    R[n2] = INT_MAX;
    int i=0;
    int j=0;
    for (int k=left; k<right+1; k++) {
        if (L[i] <= R[j]) {
            A[k] = L[i];
            i++;
        } else {
            A[k] = R[j];
            j++;
        }
    }
}

void merge_sort(vector<int>& A, int left=0, int right=-1) {     // p. 32
    if (right==-1) {right = static_cast<int>(A.size()-1);}
    if (left<right) {
        int mid = (left+right)/2;
        merge_sort(A, left, mid);
        merge_sort(A, mid+1, right);
        merge(A, left, mid, right);
    }
}

void bubblesort(vector<int>& A) {               // p. 38
    for (int i=0; i<A.size(); i++) {
        for (int j=static_cast<int>(A.size()-1); j>i; j--) {
            if (A[j] < A[j-1]) {
                int minValue = A[j];
                A[j] = A[j-1];
                A[j-1] = minValue;
            }
        }
    }
}



int main() {
    vector<int> A = {4, 1, 5, 3, 9, 6, 8, 2, 7};
    
    cout<<"unsorted: (";
    for (int i=0; i<A.size(); i++) {
        cout<<A[i]<<" ";
    }
    cout<<")"<<endl;
    
    //insertion_sort(A);
    //selection_sort(A);
    //merge_sort(A);
    //bubblesort(A);
    // SHELL SORT
    // HEAP SORT
    // QUICK SORT
    // QUICK SORT3
    
    cout<<"sorted: (";
    for (int i=0; i<A.size(); i++) {
        cout<<A[i]<<" ";
    }
    cout<<")"<<endl;
    
    
    
    return 0;
}
