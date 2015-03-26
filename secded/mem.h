typedef unsigned int secded_mem_unit;
typedef unsigned short mem_unit;
typedef unsigned int address;

void store (address addr, secded_mem_unit data);
secded_mem_unit load (address addr);
