//
//  ch_5_probabilisticAnalysis.cpp
//  Algorithms
//
//  Created by Chris Kreienkamp on 3/17/21.
//

#include <iostream>
#include <vector>
#include <stdlib.h>

using namespace std;

//### IDEAS ###
//



// Suppose you need to hire a new office assistant, and you are committed to having, at all times, the best possible person for the job. After interviewing each applicant, if that applicant is better qualified than the current office assistant, you will fire the current office assistant and hire the new applicant.
void hire_assistant(int n) {                    // p. 92
    
    // create array of candidates of size n
    srand(static_cast<unsigned int>(time(nullptr)));
    int candidate[n];
    for (int i=0; i<n; i++) {
        candidate[i] = rand() % n + 1;
    }
    
    // find the best candidate
    int best = 0;        // candidate 0 is a least-qualified dummy candidate
    for (int i=1; i<n; i++) {
        if (candidate[i] > candidate[best]) {
            best = i;
        }
    }
    
    // print statement
    cout<<"Hire candidate: "<<to_string(best+1)<<" of "<<n<<endl;
    for (int i=0; i<n; i++) {
        cout<<candidate[i]<<" ";
    }
}

// Randomize the input by permuting the given input array. Assign each element A[i] of the array a random priority P[i], and then sort the elements of A according to these priorities.
void permute_by_sorting(vector<int>& A) {         // p. 101
    srand(static_cast<unsigned int>(time(nullptr)));
    vector<double> P;
    
    for (int i=0; i<A.size(); i++) {
        P.push_back(rand() % (A.size()*A.size()*A.size()) + 1);
    }
    
    // bubblesort
    for (int i=0; i<A.size(); i++) {
        for (int j=static_cast<int>(A.size()-1); j>i; j--) {
            if (P[j] < P[j-1]) {
                int minValue = P[j];
                int holder = A[j];
                A[j] = A[j-1];
                A[j-1] = holder;
                P[j] = P[j-1];
                P[j-1] = minValue;
            }
        }
    }
}

// Generate a random permutation by permuting the given array in place.
void randomize_in_place(vector<int>& A) {       // p. 103
    srand(static_cast<unsigned int>(time(nullptr)));
    for (int i=0; i<A.size(); i++) {
        int holder = A[i];
        int randomIterator = (rand() % A.size()-i) + i;
        A[i] = A[randomIterator];
        A[randomIterator] = holder;
    }
}

// Suppose that we do not wish to interview all the candidates in order to find the best one. We also do not wish to hire and fire as we find better and better applicants. Instead, we are willing to settle for a candidate who is close to the best, in exchange for hiring exactly once. However, after each interview we must either immediately offer the position to the applicant or must tell them that they will not receive the job. We decide to adopt the strategy of selecting a positive integer k<n, interviewing and then rejecting the first k applicatns, and hiring the first applicant thereafter who has a higher score than all preceding applicants.
int on_line_maximum(vector<int>& score, int k) {            // p. 115
    int bestscore = INT_MIN;
    for (int i=0; i<k; i++) {
        if (score[i] > bestscore) {bestscore = score[i];}
    }
    for (int i=k; i<score.size(); i++) {
        if (score[i] > bestscore) {return i+1;}
    }
    return static_cast<int>(score.size());
}


int main() {
    
    vector<int> A = {13, 2, 3, 4, 18, 9, 35, 101, 7};
    
    //hire_assistant(19);
    //permute_by_sorting(A);
    //randomize_in_place(A);
    int hireNumber = on_line_maximum(A, 5);
    cout<<to_string(hireNumber)<<endl;;
    
    for (int i=0; i<A.size(); i++) {
        cout<<A[i]<<" ";
    }
    
    return 0;
}
