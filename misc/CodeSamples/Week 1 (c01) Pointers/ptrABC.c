/*
 * Pointer manipulation recap
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main()
{
  const char* p = "abc";

  assert(*p == 'A'); //Force an error to confirm build, etc...
  /*
   * NOTE: This code will NOT OUTPUT any thing for the rest of this
   * program. Why? The "assert" will only create output if there is
   * an error. You can think of the statement "assert(condition);"
   * as if it was "if(condition) true - do nothing, false print error".
   *
   * continuing on with the code...
   * BASED ON:
   * http://stackoverflow.com/questions/4955198/what-does-dereferencing-a-pointer-mean
   *
   * You might want to use this code to experiment with different
   * dereferencing modalities. Perhaps by using your trusty, dusty
   * printf SHOTGUN to see the results of some of the data
   * manipulations.
   */
  //Dereferencing the pointer - TWO WAYS
  assert(*p == 'a');  // the first character at address p will be 'a'
  assert(p[1] == 'b'); // p[1] actually dereferences a pointer created by adding
                     // p and 1 times the size of the things to which p points:
                     // in this case they're char which are 1 byte in C...
  assert(*(p + 1) == 'b');  // another notation for p[1]

  ++p;  // increment p so it's now 0x1001
  assert(*p == 'b');  // p == 0x1001 which is where the 'b' is...

  // Another dereferencing example...
  int x = 2;
  int* p_x = &x;  // put the address of the x variable into the pointer p_x
  *p_x = 4;       // change the memory at the address in p_x to be 4
  assert(x == 4); // check x is now 4

  // Dereferencing and accessing a structure data member
  typedef struct X { int i_; double d_; } X;
  X y;
  X* q = &y;
  q->d_ = 3.14159;  // dereference and access data member x.d_
  (*q).d_ *= -1;    // another equivalent notation for accessing x.d_

  // Multi-byte data types
  double sizes[] = { 10.3, 13.4, 11.2, 19.4 };
  double* r = sizes;
  assert(r[0] == 10.3);  // knows to look at all the bytes in the first double value
  assert(r[1] == 13.4);  // actually looks at bytes from address p + 1 * sizeof(double)
                         // (sizeof(double) is almost always eight bytes)
  assert(++r);           // advance p by sizeof(double)
  assert(*r == 13.4);    // the double at memory beginning at address p has value 13.4
  *(r + 2) = 29.8;       // change sizes[3] from 19.4 to 29.8
                         // note: earlier ++p and + 2 here => sizes[3]

  // Pointers to dynamically allocated memory
  

  int* s = malloc(sizeof(int));   // get some memory somewhere...
  *s = 10;            // dereference the pointer to the memory, then write a value in
  //  fn(*s);             // call a function, passing it the value at address p
  (*s) += 3;          // change the value, adding 3 to it
  free(s);            // release the memory back to the heap allocation library

  //
}
