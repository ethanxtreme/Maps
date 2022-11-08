//
// Created by we7289 on 4/19/2021.
//

#include "MapT.h"
#include <unordered_map>
//using namespace std;

const int DEFAULT_BUCKETS = 10;
const double DEFAULT_LOAD = 1.0;

template<class K, class T>
MapT<K, T>::MapT() {
    numBuckets = DEFAULT_BUCKETS;
    numKeys = 0;
    maxLoad = DEFAULT_LOAD;

    buckets = new forward_list<pair<K,T>>[numBuckets];
}

template<class K, class T>
MapT<K, T>::~MapT() {
    delete []buckets; //how you delete arrays
}

template<class K, class T>
void MapT<K, T>::Add(K key, T value) {

    // Find the appropriate bucket that key lives in
    int bucket = GetHashIndex(key);


    //repalce the value assocaited with the key if the key already exists
    for (auto it = buckets[bucket].begin(); it != buckets[bucket].end(); ++it){
        //"it" in this particular case is pointing to a pair<K,T>

        if(it->first == key){
            it->second = value;
            return;
        }
    }


    pair<K,T> keyValuePair;
    keyValuePair.first = key;
    keyValuePair.second = value;

    buckets[bucket].push_front(keyValuePair);


    if(LoadFactor() > maxLoad){
        Rehash(2*numBuckets); //rehash with double the number of buckets
    }
}

template<class K, class T>
void MapT<K, T>::Remove(K key) {
    // Find the appropriate bucket that key lives in
    int bucket = GetHashIndex(key);

    for (auto it = buckets[bucket].begin(); it != buckets[bucket].end(); ++it){
        //"it" in this particular case is pointing to a pair<K,T>

        if(it->first == key){
            buckets[bucket].remove(*it);
            numKeys--;
            return;
        }
    }

}

template<class K, class T>
bool MapT<K, T>::Contains(K key) {
    // Find the appropriate bucket that key lives in
    int bucket = GetHashIndex(key);


    //loops through each item in the bucket
    for (auto it = buckets[bucket].begin(); it != buckets[bucket].end(); ++it){
        cout << it->first << endl; //prints out the key
        cout << it->second << endl; //prints out the value associated with the key

        if(it->first == key){
            return true;
        }
    }

    return false;
}

template<class K, class T>
T MapT<K, T>::operator[](K key) {
    int bucket = GetHashIndex(key);

    //loops through each item in the bucket
    for (auto it = buckets[bucket].begin(); it != buckets[bucket].end(); ++it){
        if(it->first == key){
            return it->second;
        }
    }

    throw KeyDoesNotExist();
}

template<class K, class T>
double MapT<K, T>::LoadFactor() {
    return static_cast<double>(numKeys)/numBuckets;
}

template<class K, class T>
void MapT<K, T>::SetMaxLoad(double maxLoad) {
    this->maxLoad = maxLoad;
}

template<class K, class T>
void MapT<K, T>::Rehash(int numBuckets) {
    MapT<K, T> newMap(numBuckets);  // Need to copy over all elements to newMap
    //iterate through every bucket and the chains in each bucket

    //for each bucket
    for( int b = 0; b < this->numBuckets; b++){
        //for each item in the bucket
        for (auto it = buckets[b].begin(); it != buckets[b].end(); ++it){
            newMap.Add(it->first, it->second);
        }
    }

    *this = newMap; //copies everything over to current

}

template<class K, class T>
void MapT<K, T>::ResetIterator() {
    mapIter = buckets[0].begin();
    currBucket = 0;
}

template<class K, class T>
pair<K,T> MapT<K, T>::GetNextPair() {
    pair<K,T> currVal;



    return currVal;
}

template<class K, class T>
int MapT<K, T>::GetHashIndex(const K &key) {
    unordered_map<K,T> mapper;
    typename unordered_map<K,T>::hasher hashFunction = mapper.hash_function();
    return static_cast<int>(hashFunction(key) % numBuckets);
}





