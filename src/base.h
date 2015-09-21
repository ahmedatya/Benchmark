#ifndef ATYA_BASE_
#define ATYA_BASE_


#include <iostream>
typedef unsigned char uint8;
typedef unsigned char Byte;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long uint64;

class Object
{
private:
  uint64 count; //Counter to the number of bytes in this object
  Byte * p; //A pointer to the object

public:
  // Default Constructor
  Object()
  {
    count = 0;
    p = NULL;
  }

  //Copy Constructor
  Object(Object & obj)
  {
    this->p = new Byte[obj.count];
    memcpy(this->p,obj.p,obj.count);
    this->count = obj.count;
  }

  virtual ~Object()
  {
    delete [] p;
    p = NULL;
    count = 0;
  }

  void operator=(Object & obj)
  {
    this->p = new Byte[obj.count];
    memcpy(this->p,obj.p,obj.count);
    this->count = obj.count;
  }

  void Set(Byte * p, uint64 count)
  {
    this->p = p;
    this->count = count;
  }

  Byte * Get(uint64 & count)
  {
    count = this->count;
    return p;
  }

};

#endif //ATYA_BASE_
