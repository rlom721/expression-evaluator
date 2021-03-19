// Specification file for Slot class
//
// The Slot class is a small container structure of a string key and std::string
// data (as a key and data pair).

#ifndef SLOT_H
#define SLOT_H

#include <string>

class Slot {
public:
  // typedef 
  typedef std::string dataType;
  // Constructors
  Slot();
  Slot(std::string k, std::string d);
  Slot(const Slot& rhs);  // copy
  // Modification methods
  void set(std::string k, std::string d);
  void setKey(std::string k);
  void setData(std::string d);
  // Constant methods
  std::string getKey() const { return key; };
  dataType getData() const { return data; };
  // Overloaded operators
  Slot& operator=(const Slot& rhs);
private:
  // Member variables
  std::string key;
  std::string data;
};

#endif
