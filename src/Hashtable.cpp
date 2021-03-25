// Hashtable.cpp
// implementation file of Hashtable class

#include "Hashtable.h"  // header file
#include <iostream>     // used for key and data pair type
#include <iomanip>      // for restoring hash
#include <cassert>      // for assert function (debugging)
#include <string>       // used for processing files
#include <vector>       // main table structure
#include <fstream>      // for reading and writing to data files
#include <sstream>      // for parsing lines of data file
using namespace std;

// default constructor sets up hashtable structure (vector) and
// sets default value for nextOFBucket
Hashtable::Hashtable() {
  buckets = vector<Bucket>(CAP);    // table has CAP number of buckets
  nextOFBucket = CAP;         // index of next overflow bucket is after primary
}

// FIX! add check to overwrite data
// This method takes a key and data pair, hashes the key to an index, then
// inserts pair into hashtable.
void Hashtable::insertToHT(string entryKey, string entryData) {
  int slot = 0;     // slot index in bucket
  int index = -1;   // bucket index
  bool alreadyPres = false;    // to see if already an entry

  // determine index in table by hashing the key, if NOT searching OF bucket
  index = hashFunc(entryKey);

  // find exact match using key, then overwrite the data
  findRecord(entryKey, alreadyPres, slot, index);

  if (alreadyPres) {
    buckets[index].set(entryKey, entryData, slot);
  }
  // insert key and data in next open slot in bucket
  else if (buckets[index].hasFreeSlot()) {
    slot = buckets[index].getNextOpenSlot();
    buckets[index].set(entryKey, entryData, slot);

    if (slot > 0) buckets[index].incrCount();   // keep track of collisions
  }
  // if bucket has overflow bucket index, insert there
  else if (buckets[index].getOFindex() != -1) {
    buckets[index].incrCount();         // count as collision for old bucket

    index = buckets[index].getOFindex();

    insertToHT(entryKey, entryData, index);   // recursive call
  }
  // create new overflow bucket and add key and data to 1st slot
  else {
    buckets[index].incrCount();   // keep track of collisions

    // link current bucket to overflow bucket index
    buckets[index].setOFindex(nextOFBucket++);

    Bucket newBucket;

    // index of overflow bucket being linked
    index = buckets[index].getOFindex();

    // allocate space at end of buckets and add newBucket to end
    buckets.resize(nextOFBucket, newBucket);
    insertToHT(entryKey, entryData, index);
  }
}

// This method searches for a record with a matching key then returns its data.
// Returns empty string if not found.
string Hashtable::getValue(string key) {
  string value = "";
  bool found = false;
  int index = hashFunc(key),
      slot = -1;

  findRecord(key, found, slot, index);

  if (found) {
    value = buckets[index].getData(slot);
  }
  else {
    cout << "Record not found.";
  }

  return value;
}

// This method takes a key argument and searches the hashtable for a record.
// Returns true if exact key found.
bool Hashtable::findRecord(string key) {
  bool found = false;
  int index = hashFunc(key),
      slot = -1;

  findRecord(key, found, slot, index);

  return found;
}

// This method outputs current hashtable items to console.
void Hashtable::GenStatReport() {
  cout << centerText("Hash Table")
       << centerText("Verification Report")
       << centerText("Before | After Restoration");

  // loop over ALL buckets in hash table and display their contents
  for (int i = 0; i < size(); i++)
    cout << "\nBucket " << i + 1 << "\n" << buckets[i];
}

// This method resets the hashtable in memory by clearing data and resizing.
void Hashtable::resetHT() {
  buckets.clear();                  // clear current contents of buckets
  buckets = vector<Bucket>(CAP);    // shrink to default size
  nextOFBucket = CAP;   // reset index of available overflow bucket
}

// This method returns total number of used entries in table (for debugging).
int Hashtable::numEntries() const{
  int count = 0;
  for (int i = 0; i < size(); i++) {
    for (int slot = 0; slot < 3; slot++)
      if (buckets[i].getKey(slot) != "EMPTY") count++;
  } return count;
}

// This helper function (for recursive call) takes a key and data pair, then
// inserts pair into hashtable (do NOT hash key or program will crash!).
void Hashtable::insertToHT(string entryKey, string entryData, int index) {
  int slot = 0;   // slot index in bucket

  // insert key and data in next open slot in bucket
  if (buckets[index].hasFreeSlot()) {
    slot = buckets[index].getNextOpenSlot();
    buckets[index].set(entryKey, entryData, slot);

    if (slot > 0) buckets[index].incrCount();   // keep track of collisions
  }
  // if bucket has overflow bucket index, insert there
  else if (buckets[index].getOFindex() != -1) {
    buckets[index].incrCount();         // count as collision for old bucket

    index = buckets[index].getOFindex();

    insertToHT(entryKey, entryData, index);   // recursive call
  }
  // create new overflow bucket and add key and data to 1st slot
  else {
    buckets[index].incrCount();   // keep track of collisions

    // link current bucket to overflow bucket index
    buckets[index].setOFindex(nextOFBucket++);

    Bucket newBucket;

    // index of overflow bucket being linked
    index = buckets[index].getOFindex();

    // allocate space at end of buckets and add newBucket to end
    buckets.resize(nextOFBucket, newBucket);
    insertToHT(entryKey, entryData, index);
  }
}

// Hash function takes ordinal value of 2nd, 4th and 6th chars of a key
// then modulo by the number of primary buckets (20) to obtain index of table
int Hashtable::hashFunc(string key) const {
  int sum = 0;
  
  for (int i = 0; i < int(key.length()); i++)
    sum += key[i];

  return (sum % CAP);
}

// This helper function takes an index from a hashed key and determines bucket
// and slot of item if already present in table
// Prerequisite: hashFunc was called on the key before this is called
void Hashtable::findRecord(string key, bool& found, int& slot, int& index) {
  int s = 0;        // counter for while loop below for slots
  string currKey;   // current slot's key
  found = false;    // false until found

  // loop until all slots searched, key or empty found
  while (s < Bucket::getNumSlots() && !found) {
    currKey = buckets[index].getKey(s);

    // found EXACT match so set found to true and get slot number
    if (currKey == key) {
      found = true;
      slot = s;
    }
    s++;
  }

  // if not found, search overflow bucket for key IF ALLOCATED
  if (!found && (buckets[index].getOFindex() != -1) && index < size()) {
    index = buckets[index].getOFindex();
    findRecord(key, found, slot, index);
  }
}

// This helper function centers text for reports.
string Hashtable::centerText(string s) {
  const int consoleWidth = 80;
  int length = 0,   // length of combined string with space
      spaces = 0;   // spaces to pad to center
  string centered = "";   // centered text

  length = s.length() + 1;
  spaces = (consoleWidth - length) / 2;

  // center by adding padding with spaces before string
  centered = string(spaces, ' ') + s + '\n';

  return centered;
}