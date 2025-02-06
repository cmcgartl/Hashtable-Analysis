#ifndef _HASH_TABLE_H
#define _HASH_TABLE_H

#include <string>
#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <cstdlib>


template<typename T>
class Hashtable
{
public:

	Hashtable(bool debug = false, unsigned int size = 11);

	~Hashtable();

	int add(std::string k, const T& val);

	const T& lookup(std::string k) const;

	void reportAll(std::ostream& out) const;

	int hash(std::string k) const;

private:

	void resize();
	std::pair<std::string, T>* data;
    std::vector<int> sizes = {11,23,47,97,197,397,797,1597,3203,6421,12853,25717,51437,102877,205759,411527,823117};
    int sizesIndex;
    bool debug;
    int Hash(std::string k) const;
    unsigned int size;
    std::vector<int> rvals;
    std::vector<std::pair<std::string, T>> added;
    double load;

};

//constructor
template<typename T>
Hashtable<T>::Hashtable(bool debug, unsigned int size): debug(debug), size(size)
{
    data = new std::pair<std::string,T>[size];
    load = 0;
    sizesIndex = 0;
    //initializes values to random if debug is false, set values if true
    if(debug == false){
        rvals.resize(5);
        srand(time(0));
        for(int i = 0; i < 5; i++){
            rvals[i] = rand() % 12;
        }   
    }
    else{
        rvals.push_back(983132572);
        rvals.push_back(1468777056);
        rvals.push_back(552714139);
        rvals.push_back(984953261);
        rvals.push_back(261934300);
    }
}

//destructor
template<typename T>
Hashtable<T>::~Hashtable()
{
    delete[] data;
}

template<typename T>
int Hashtable<T>::add(std::string k, const T& val)
{
    //updates load factor, resize called if over 0.5
	load = static_cast<double>((added.size() + 1))/size;
	if(load >= 0.5){
		resize();
	}
    int index = 0;
    int count = 1;

    //creates new pair of k and T, hashes k to find hash value
    std::pair<std::string, T> newpair = std::make_pair(k, val);
    index = hash(newpair.first);
	int originalIndex = hash(newpair.first);

    //while the hashed index is occupied, move on to next using quadratic probing
    while (!data[index].first.empty() && data[index].first != k) {
    index = (originalIndex + (count * count)) % size;
    count++;
    }

    //insert data item, record that it was added, return number of probes
    data[index] = newpair;
    added.push_back(newpair);
    return count - 1;
}

template<typename T>
const T& Hashtable<T>::lookup(std::string k) const
{
    static T random = -1;
	int count = 1;

    //sets index to the hash value of string k
	int index = hash(k);
	int originalIndex = index;
  
    //walks throug htable with data index by quadratic probing until it k is found
    while (!data[index].first.empty() && data[index].first != k) {
        index = (originalIndex + (count * count)) % size;

        //ensure index is in bounds
        if (index < 0) index += size;
        count++;
        if (count > size) return random; 
    }
    //std::cout << "made it past while, data[" << index << "].first = " << data[index].first << " original = " << originalIndex << std::endl;
    if(data[index].first == k){
        //std::cout << "looking up " << k << " returned data[index].second: " << data[index].second << std::endl;
        return data[index].second;
    }
    //if not found, garbage value returned
    return random;
}

//prints entirety of hashtable data to ostream
template<typename T>
void Hashtable<T>::reportAll(std::ostream & out) const
{
    for(unsigned int i = 0; i < size; i++){
        if(data[i].first != ""){
            out << data[i].first << " " << data[i].second << std::endl;
        }
    }
}

//resize function to keep load factor < 0.5
template<typename T>
void Hashtable<T>::resize()
{
    //updates the size from size vector
    sizesIndex++;
	if(size < 11){
		sizesIndex = 0;
	}

    //if debug is false, new r values calculated
	if(debug == false){
        int random = 0;
        srand(time(0));
        for(int i = 0; i < 5; i++){
            random =  rand() % (size + 1);
            rvals[i] = random;
        }
    }
    while(sizesIndex < sizes.size() && sizes[sizesIndex] <= size){
    sizesIndex++;
    }

    //updates size and load factor
    size = sizes[sizesIndex];
	load = static_cast<double>(added.size())/size;

    //deletes data, and sets it equal to a new array of new size
    delete [] data;
    data = new std::pair<std::string, T>[size];

    //rehash all added items to new locations using quadratic probing
    for(unsigned int i = 0; i < added.size(); i++){
        int index = hash(added[i].first);
		int originalIndex = hash(added[i].first);
		int count = 1;
		while(data[index].first != added[i].first && data[index].first != ""){
        index = ((originalIndex + (count * count)) % size);
        count++;
    }
    data[index] = added[i];
    }
}

//compute base to the power of exponent, return as long long
long long power(int base, int exp)
{
    long long result = 1;
    for (int i = 0; i < exp; i++)
    {
        result *= base;
    }
    return result;
}

template <typename T>
int Hashtable<T>::hash(std::string k) const
{
	long long wvals[5] = {0};
    long long final = 0;
    long long a = 0;
    long long w = 0;

    //walks through string, breaks it into peices of 6 characters
    for (unsigned long long i = 0; i <= k.size() / 6; i++){
        for (int j = 0; j < 6; j++){
            int index = k.size() - 1 - (j + (i * 6));
            if (index < 0) break;
            if (k[index] >= 'a' && k[index] <= 'z'){
                a = k[index] - 'a' + 1;
                w += power(27, j) * a;
            }
        }
        if (i < 5) wvals[4 - i] = w;
        w = 0;
    }

    //multiply each r value with it's corresponding w value
    for(int i = 0; i < 5; i++){
        final += (wvals[i] * rvals[i]);
    }

    //return final hash
    return static_cast<int>(final % size);
}

#endif 
