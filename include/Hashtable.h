// Specification file for Hashtable class
//
// Hashtable is a template class dependent on the Bucket class that provides
// features of a hashtable data structure.
// Allows multiple entries to hash to same index by inserting into slots
// and allocating overflow buckets.
// Also contains search and hashtable report features.

#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "Bucket.h"     // Hashtable entry
#include <iostream>
#include <string>       // used for key and data pair type
#include <vector>       // main table structure
using namespace std;

class Hashtable {
public:
  // Constructors
  Hashtable();
  // Modification methods
  void insertToHT(string entryKey, string entryData);
  void resetHT();
  // Constant methods
  string getValue(string key);
  bool findRecord(string key);
  void GenStatReport();
  int size() const { return buckets.size(); }
  int numEntries() const;
private:
  // Helper functions
  void insertToHT(string entryKey, string entryData, int index);
  int hashFunc(string key) const;
  void findRecord(string key, bool &found, int& slot, int& index);
  string centerText(string s);
  // Member variables
  static const int CAP = 20;    // size or number of PRIMARY buckets
  vector<Bucket> buckets;
  int nextOFBucket;             // index of available overflow bucket
};

#endif
