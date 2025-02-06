#include <vector>
#include <algorithm>
#include <random>
#include <iostream>
#include <string>
#include "Hashtable.h"
#include <ctime>
#include <cstdlib>

using namespace std;

int main(){
    //string input("a");
    int iterations = 0;
    int inserts = 0;
    cout << "please enter the number of iterations you would like to run (0 < i <= 1,000,000) ... " << endl;
    while((iterations <= 0) || iterations >= 10000000){
        cin >> iterations;
        if(iterations <= 0 || iterations > 10000000){
            cout << "please enter a valid iteration count!" << endl;
        }
    }
    cout << "please enter the number of inserts you would like to test per iteration (0 < i <= 1,000,000/iterations) ... " << endl;
    while(inserts <= 0 || inserts > (10000000/iterations)){
        cin >> inserts;
        if(inserts <= 0 || inserts > 10000000){
            cout << "please enter a valid insertion count!" << endl;
        }
    }
    int iteration_max = 0;
    int individual_max = 0;
    srand(time(0));
    int total = 0;
    int randomvalue = 0;
    int probeCount = 0;
    int probes = 0;
    int k = 0;
    vector<int> counts;
    vector<string> randomStrings;
    string alphabet = "abcdefghijklmnopqrstuvwxyz";

    //creates a string of length 10, assigns each index a random letter,
    //adds string to vector of random strings
    for(int i = 0; i < (iterations * inserts); i++){
          string base = "aaaaaaaaaa";
        for(int j = 0; j < 10; j++){
            randomvalue = rand() % 26;
            base[j] = alphabet[randomvalue];
        }

        //each iteration ran with a new random string (not necessarily unique)
        randomStrings.push_back(base);
    }
        //runs user selected iterations of insertions into an empty hashtable
    for(int i = 0; i < iterations; i++){
         Hashtable<int> hashtable(false, 47);
        for(int j = 0; j < inserts; j++){
            if(k < randomStrings.size()){
            probes = hashtable.add(randomStrings[k], 1);
            }
            probeCount += probes;
            if(probeCount > iteration_max) iteration_max = probeCount;
            if(probes > individual_max) individual_max = probes;
            probes = 0;
            k++;
        }

        //prints results
        std::cout << "for iteration " << i + 1 << ": number of probes: " << probeCount << endl;
        counts.push_back(probeCount);
        probeCount = 0;
    }
    for(int i = 0; i < counts.size(); i++){
        total += counts[i];
    }
    double av = static_cast<double>(total)/inserts;
    std::cout << "average number of probes for " << inserts << " inserts: " << av << endl;
    cout << "Highest probe count from " << inserts << " inserts: " << iteration_max << endl;
    cout << "Highest probe count form 1 insert: " << individual_max << endl;
    return 0;
}
