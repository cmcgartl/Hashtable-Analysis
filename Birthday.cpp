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
    string input("a");
    srand(time(0));
    int randomvalue = 0;
    int probeCount = 0;
    int addCount = 0;
    int k = 0;
    vector<int> counts;
    vector<string> randomStrings;
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    for(int i = 0; i < 1000000; i++){
        string base = "aaaaaaaaaa";
        for(int j = 0; j < 10; j++){
            randomvalue = rand() % 26;
            base[j] = alphabet[randomvalue];
        }
        randomStrings.push_back(base);
    }
    for(int i = 0; i < 1000; i++){
        Hashtable<int> hashtable(true, 365);
        while(probeCount == 0 && k < 100000){
            probeCount += hashtable.add(randomStrings[k], 1);
            addCount++;
            k++;
        }
        //cout << "for iteration " << i + 1 << ": number of adds before collision: " << addCount << endl;
        counts.push_back(addCount);
        addCount = 0;
        probeCount = 0;
    }
    int under23orEqual = 0;
    int over23 = 0;
    for(int i = 0; i < counts.size(); i++){
        if(counts[i] <= 23){
            under23orEqual++;
        }
        else{
            over23++;
        }
    }
    double percentUnder = (static_cast<double>(under23orEqual)/1000) * 100;
    double percentOver = (static_cast<double>(over23)/1000) * 100;
    cout << "percent 23 or less: " << percentUnder << "%" << endl;
    cout << "percent over 23: " << percentOver << "%" << endl;

    return 0;
}

