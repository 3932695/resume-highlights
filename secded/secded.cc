/* Kevin Xiao - April 4th 2014 - Hwk6 */

#include <stdio.h>
#include "mem.h"
#include "secded.h"

// optional includes for debugging
#include <iostream>
#include <bitset>
using namespace std;

// =============================
// ========displayBits==========

// For debugging.
// Takes unsigned long (data bits).
// Outputs unsigned long in 32 bit binary form.

void displayBits(unsigned long bits){
  cout << "(>6_6)> " << bitset<32>(bits) << " <(6_6<)" << endl;
}

// =============================
// =========check_bits==========

// Takes unsigned long (data bits).
// Returns the five check bits for a 16 bit data segment.

int check_bits(unsigned long dac){

  // Dissects data segment into array of bits.
  int m [16];
  for(int i = 0; i < 16; i++){
    m[i] = (dac >> i) & 1;
  }
   
  // Computes checkbits.
  int c1 = m[0]^m[1]^m[3]^m[4]^m[6]^m[8]^m[10]^m[11]^m[13]^m[15];
  int c2 = m[0]^m[2]^m[3]^m[5]^m[6]^m[9]^m[10]^m[12]^m[13];
  int c4 = m[1]^m[2]^m[3]^m[7]^m[8]^m[9]^m[10]^m[14]^m[15];
  int c8 = m[4]^m[5]^m[6]^m[7]^m[8]^m[9]^m[10];
  int c16 = m[11]^m[12]^m[13]^m[14]^m[15];

  return c1 + c2*2 + c4*4 + c8*8 + c16*16;
}

// =============================
// ========parity_bit===========

// Takes unsigned long (data bits).
// Returns the parity for a 21 bit data segment (includes checkbits).

int parity_bit(unsigned long dac){

  // XOR's all the bits in the data segment.
  int p [21];
  p[0] = (dac >> 0) & 1;
  int result = p[0];
  for(int i = 1; i < 21; i++){
    p[i] = (dac >> i) & 1;
    result = p[i]^result;
  }

  return result;
}

// =============================
// ========secded_store=========

// Called by the system to store a word (16-bits) of data.
// Before storing the data in the error-prone memory using store, the 
// function should add check-bits and a parity bit for Single Error
// Correction, Double Error Detection (SECDED). 

// The function store() will take a 22-bit value (since it takes an unsigned
// long (32-bits), the high 10 bits will be cleared.

void secded_store (unsigned int address, unsigned short data) {

  unsigned long dac; //Data And Checkbits
  
  dac = data;

  dac = dac | check_bits(dac) << 16; // attaches checkbits

  dac = dac | parity_bit(dac) << 21; // attaches parity bit

  store(address, dac);
}

// ============================
// ==========calc_bit==========

// Takes stores checkbits and computed checkbits.
// Returns address of bit that should be flipped for correction.

int calc_bit(int stored_check, int computed_check){

  // Table for XOR operation later.
  // Result of operation on left, corresponds to address on right.
  int array [22]; 
  array[3] = 0;
  array[5] = 1;
  array[6] = 2;
  array[7] = 3;
  array[9] = 4;
  array[10] = 5;
  array[11] = 6;
  array[12] = 7;
  array[13] = 8;
  array[14] = 9;
  array[15] = 10;
  array[17] = 11;
  array[18] = 12;
  array[19] = 13;
  array[20] = 14;
  array[21] = 15;
  array[0] = 99;
  array[1] = 16;
  array[2] = 17;
  array[4] = 18;
  array[8] = 19;
  array[16] = 20;

// XOR operation (e.g. 10110 XOR 01100 = 11010)
  int code = stored_check ^ computed_check;
  return array[code];
}

// =============================
// ========secded_load==========


// Called by the system to load a word (16-bits) of data.
// After loading the data from the error-prone memory using load(), the
// function should verify the validity of the data using the check-bits and
// parity bit.

// The function should return the data in the location pointed to by
// data. The function should return false if there was an uncorrectable error
// that was detected. It should return true if there were no errors or if the
// errors were corrected.


bool secded_load (unsigned int address, unsigned short& data) {
    unsigned long unchecked_data;
    unsigned long checked_data;

    unchecked_data = load(address); // read from memory
    
    // Obtains stored checkbits and parity.
    int c1 = (unchecked_data >> 16) & 1;
    int c2 = (unchecked_data >> 17) & 1;
    int c4 = (unchecked_data >> 18) & 1;
    int c8 = (unchecked_data >> 19) & 1;
    int c16 = (unchecked_data >> 20) & 1;
    int stored_check = c1 + c2*2 + c4*4 + c8*8 + c16*16;
    int stored_parity = (unchecked_data >> 21) & 1;

    // Computes checkbits and parity for comparison.
    checked_data = unchecked_data;
    int computed_parity = parity_bit(checked_data);
    int computed_check = check_bits(checked_data);

    // Single Error Correction
    if(stored_parity != computed_parity and stored_check != computed_check){
      int flipped_bit = calc_bit(stored_check, computed_check);
      checked_data = checked_data ^ (1 << flipped_bit);
    }
    
    // Double Error Detection
    if(stored_parity == computed_parity and stored_check != computed_check){
      data = checked_data;
      
      return false;
    }
 
    // Write data if no errors, or errors corrected.
    data = checked_data;
    return true;
}

