// Implementation file for DataClass class
// File name: DataClass.cpp

#include "DataClass.h"    // header file for DataClass class
#include <iostream>
using namespace std;
namespace lomboy_a2 {

  // Default constructor uses default constructor of data type to set
  // default value for data
  DataClass::DataClass() : data(dataType()), key(0) { }

  // Parametrized constructor sets argument value for data
  DataClass::DataClass(dataType data) : data(data), key(0) { }

  // Copy constructor copies data AND key value of another DataClass object
  DataClass::DataClass(const DataClass& dc) {
    data = dc.data;
    key = dc.key;
  }

  // This method sets data value based on argument provided.
  // Assumes argument passed is an dataType.
  void DataClass::set(dataType data) {
    this->data = data;
  }

  // This method sets key value based on argument provided.
  void DataClass::setKey(int key) {
    this->key = key;
  }

  // Overloaded copy assignment
  // This copies data AND key from another DataClass object.
  DataClass& DataClass::operator=(const DataClass& dc){
    if (this != &dc) {
      data = dc.data;
      key = dc.key;
    }

    return *this;
  }

  // Friend function: Overloaded outstream operator
  // Displays data of DataClass object
  ostream& operator<<(ostream& out, const DataClass& dc) {
    out << dc.get();

    return out;
  }

  // Friend function: Overloaded == operator
  // Returns true if dc1 and dc2 have equal data fields.
  bool operator==(const DataClass& dc1, const DataClass& dc2) {
    return (dc1.get() == dc2.get());
  }

  // Friend function: Overloaded < operator
  // Returns true if dc1 is less than dc2
  bool operator<(const DataClass& dc1, const DataClass& dc2) {
    return (dc1.get() < dc2.get());
  }

  // Friend function: Overloaded > operator
  // Returns true if dc1 is greater than dc2
  bool operator>(const DataClass& dc1, const DataClass& dc2) {
    return (dc1.get() > dc2.get());
  }

}
