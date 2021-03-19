// Specification file for Bucket class
//
// Bucket is a class dependent on the Slot class.
// It provides a container structure of string keys and data, as well as
// information about the object itself.

#ifndef BUCKET_H
#define BUCKET_H

#include "Slot.h"
#include <iostream>
#include <string>
using namespace std;

// template <class data>
class Bucket {
  // Static member variables
  static const int numSlots = 3;  // size of slots array
  // typedef
  // typedef data dataType
  // Friend functions and classes
  friend ostream &operator<<(ostream& out, const Bucket& Bucket);
public:
  // Constructors
  Bucket();
  Bucket(string key, string data);
  Bucket(const Bucket& rhs);        // copy
  // Modification methods
  void set(string key, string data, int slotIndex);
  void setKey(string k, int slotIndex);
  void setData(string d, int slotIndex);
  void incrCount();
  void setOFindex(int index);
  // Constant methods
  string getKey(int slotIndex) const { return slots[slotIndex].getKey(); }
  string getData(int slotIndex) const { return slots[slotIndex].getData(); }
  int getNextOpenSlot() const { return nextOpenSlot; }
  int getCount() const { return count; }
  int getOFindex() const { return OFindex; }
  bool hasFreeSlot() const { return (nextOpenSlot < 3); }
  bool isOpen(int sIndex) const { return (slots[sIndex].getKey() == "EMPTY"); }
  // Overloaded operators
  Bucket& operator=(const Bucket& rhs);         // copy assignment
  // Static member functions
  static int getNumSlots() { return numSlots; }
private:
  // Member variables
  int OFindex;            // index to overflow bucket
  int count;              // number of collisions in bucket
  int nextOpenSlot;       // next available slot
  Slot slots[numSlots];   // array of numSlots slots
  // would change to template...
};

#endif
