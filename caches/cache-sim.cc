#include <unistd.h>
#include <getopt.h>
//#include <stdio.h>
#include <math.h>

#define __STDC_FORMAT_MACROS
#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include <sstream>
#include <iostream>
using namespace std;

void simulateCache(size_t addressBits, size_t capacity, size_t lineSize,
                   size_t assocWays, bool writeBack, bool allocateOnWrite,
                   bool tracing, bool unified, size_t missPenalty);

int main(int argc, char *argv[]) {
  size_t associativity = 1;
  size_t blockSize = 1;
  size_t capacity = 2;
  size_t addressSize = 64;
  bool writeBack = false;
  bool allocateOnWrite = false;
  bool tracing = true;
  bool unified = false;
  size_t missPenalty = 10;

  while (true) {
    int c;
    int option_index = 0;
    static struct option long_options[] = {
      {"associativity", required_argument, NULL, 'a'},
      {"block-size", required_argument, NULL, 'b'},
      {"capacity", required_argument, NULL, 'c'},
      {"write-through", no_argument, NULL, 'w'},
      {"write-back", no_argument, NULL, 'W'},
      {"allocate-on-write", no_argument, NULL, 'A'},
      {"trace", no_argument, NULL, 't'},
      {"unified", no_argument, NULL, 'u'},
      {"miss-penalty", required_argument, NULL, 'm'},
      {0, 0, 0, 0}
    };

    c = getopt_long (argc, argv, "",
                     long_options, &option_index);
    if (c == -1)
      break;

    switch (c) {
    case 'a':
      sscanf(optarg, "%d", &associativity);
      if (tracing)
        printf("Associativity = %d\n", associativity);
      break;

    case 'b':
      sscanf(optarg, "%d", &blockSize);
      if (tracing)
        printf("Block Size = %d\n", blockSize);
      break;

    case 'c':
      if (sscanf(optarg, "%dK%c", &capacity, &c) == 2)
        capacity *= 1024;
      else if (sscanf(optarg, "%dM%c", &capacity, &c) == 2)
        {
	  capacity *= 1024 * 1024;
        }
      else
        sscanf(optarg, "%d", &capacity);
      if (tracing)
        printf("Capacity = %d\n", capacity);
      break;

    case 'W':
      writeBack = true;
      if (tracing)
        printf("Write back\n");
      break;

    case 'w':
      writeBack = false;
      if (tracing)
        printf("Write through\n");
      break;

    case 'A':
      allocateOnWrite = true;
      if (tracing)
        printf("Allocate on write\n");
      break;

    case 't':
      tracing = true;
      printf("Tracing\n");
      break;

    case 'u':
      unified = true;
      if (tracing) 
        printf("Unified\n");
      break;

    case 'm':
      sscanf(optarg, "%d", &missPenalty);
      if (tracing)
        printf("Miss penalty = %d\n", missPenalty);
      break;


    case '?':
      printf("Missing option argument\n");
      return 1;

    default:
      printf ("Unknown option character %c(%d)\n", c, c);
      break;
    }
  }
  if (optind < argc) {
    printf ("unused command-line elements: ");
    while (optind < argc)
      printf ("%s ", argv[optind++]);
    printf ("\n");
    return 1;
  }
  simulateCache(addressSize, capacity, blockSize, associativity, writeBack, allocateOnWrite, tracing, unified, missPenalty);
  return 0;
}

struct block {
  bool valid;
  bool dirty;
  bool lru;
  long tag;
  long index;
  long offset;
 
  block(){
    valid = false;
    dirty = false;
    lru = false;
    tag = 0;
    index = 0;
    offset = 0;
  }
};

class Cache{
public:
  block* table;
  
  long offset_size;
  long index_size;
  long tag_size;
  long totalHits;
  long totalMisses;
  long totalReads;
  long totalWrites;
  long totalAccess;
  long bytesRead;
  long bytesWritten;
  long cycles;
  bool writeBack;
  bool allocateOnWrite;
  long missPenalty;
  size_t assocWays;
  block* ghostCache;

  long block_size;
  long table_size;

  Cache(long t, long a, long b, long c, bool x, bool y, long z, size_t v){
    table = new block[t];
    offset_size = a;
    index_size = b;
    tag_size = c;
    totalHits = 0;
    totalMisses = 0;
    totalReads = 0;
    totalWrites = 0;
    totalAccess = 0;
    bytesRead = 0;
    bytesWritten = 0;
    cycles = 0;
    writeBack = x;
    allocateOnWrite = y;
    missPenalty = z;
    
    assocWays = v;
    ghostCache = new block[t];


    block_size = (2L << (offset_size - 1));
    table_size = t;
 
  }

  void look_up (uint64_t address, uint64_t fallthrough){
    totalReads++;
    totalAccess++;
    long offset = address % block_size;
    long index = (address >> offset_size) % table_size;
    long tag = address >> (offset_size + index_size);
    long instructionSize = fallthrough - address;
    block blk;
    bool ghost;
    if(assocWays == 1){
      blk = table[index];
      ghost = false;
    }
    if(assocWays == 2 && table[index].lru == true){
      blk = ghostCache[index];
      ghost = true;
    }
    if(assocWays == 2 && table[index].lru == false){
      blk = table[index];
      ghost = false;
    }


    bool miss = true;
    if(blk.tag == tag && table[index].valid){
      miss = false;
      if(assocWays == 2){
	if(ghost){
	  table[index].lru = true;
	}else{table[index].lru = false;}
      }
    }
    if(miss == true && assocWays == 2){
      if(ghost){
	blk = table[index];
	ghost = false;
	if(blk.tag == tag && table[index].valid){
	  miss = false;
	  if(ghost){
	    table[index].lru = true;
	  }else{table[index].lru = false;}
	  if(offset + instructionSize > block_size){
	    look_up((address + block_size - offset), fallthrough);
	  }
	}
      }
      else if(!ghost){
	blk = ghostCache[index];
	ghost = true;
	if(blk.tag == tag && table[index].valid){
	  miss = false;
	  if(ghost){
	    table[index].lru = true;
	  }else{table[index].lru = false;}
	  if(offset + instructionSize > block_size){
	    look_up((address + block_size - offset), fallthrough);
	  }
	}
      }
    }
    if(miss == false){
      totalHits++;
      if(offset + instructionSize > block_size){
	look_up((address + block_size - offset), fallthrough);
      }
    }
    if(miss == true){
      totalMisses++;
      bytesRead += block_size;
      cycles += missPenalty;
      bool lru = false;
      if(assocWays == 2){
	lru = table[index].lru;
      }
      load_address(address, lru);
      if(offset + instructionSize > block_size){
       	look_up((address + block_size - offset), fallthrough);
      }
    }
  }


  void write (uint64_t address){
    totalWrites++;
    totalAccess++;
    long offset = address % block_size;
    long index = (address >> offset_size) % table_size;
    long tag = address >> (offset_size + index_size);

    block blk;
    bool ghost;
    if(assocWays == 1){
      blk = table[index];
      ghost = false;
   }
    if(assocWays == 2 && table[index].lru == true){
      blk = ghostCache[index];
      ghost = true;
    }
    if(assocWays == 2 && table[index].lru == false){
      blk = table[index];
      ghost = false;
    }

    bool miss = true;
    if(blk.tag == tag && table[index].valid){
      miss = false;
      if(assocWays == 2){
	if(ghost){
	  table[index].lru = true;
	}else{table[index].lru = false;}
      }
    }
    if(miss == true && assocWays == 2){
      if(ghost){
	blk = table[index];
	ghost = false;
	if(blk.tag == tag && table[index].valid){
	  miss = false;
	  if(ghost){
	    table[index].lru = true;
	  }else{table[index].lru = false;}
	}
      }
      else if(!ghost){
	blk = ghostCache[index];
	ghost = true;
	if(blk.tag == tag && table[index].valid){
	  miss = false;
	  if(ghost){
	    table[index].lru = true;
	  }else{table[index].lru = false;}
	}
      }
    }

    
    if(!writeBack){
      bytesWritten++;

      if(miss){
	totalMisses++;
	if(allocateOnWrite){
	  if(table[index].lru = false){
	    ghostCache[index].tag = tag;
	    table[index].lru = true;
	  }else{
	    table[index].tag = tag;
	    table[index].lru = false;
	  }
	  table[index].valid = true;
	  table[index].dirty = false;
	  bytesRead += block_size;
	  cycles += missPenalty;
	}
      }
      else{
	totalHits++;
      }
    }
    else{
      if(!miss){
	totalHits++;
	table[index].dirty = true;
      }
      else{
	totalMisses++;
	if(!allocateOnWrite){
	  bytesWritten++;
	}
	else{
	  if(table[index].dirty){
	    bytesWritten += block_size;
	  }
	  if(table[index].lru = false){
	    ghostCache[index].tag = tag;
	    table[index].lru = true;
	  }else{
	    table[index].tag = tag;
	    table[index].lru = false;
	  }
	  table[index].valid = true;
	  bytesRead += block_size;
	  cycles += missPenalty;
	}
      }
    }
  }
    
    
  void load_address (uint64_t address, bool lru){

    long offset = address  % block_size;
    long index = (address >> offset_size) % table_size;
    long tag = address >> (offset_size + index_size);
    if(lru == true && assocWays == 2){
      table[index].tag = tag;
      table[index].lru = false;
    }
    else if (lru == false && assocWays == 2){
      ghostCache[index].tag = tag;
      table[index].lru = true;
    }else{
      table[index].tag = tag;
    }
	
    
    table[index].valid = true;
    table[index].dirty = false;

  }
    


};




void simulateCache(size_t addressBits, size_t capacity, size_t lineSize,
                   size_t assocWays, bool writeBack, bool allocateOnWrite,
                   bool tracing, bool unified, size_t missPenalty) {


  long rows = capacity / lineSize;

  if(assocWays == 2){
    rows = rows / 2;
  }

  long offset_size = long(log2(lineSize));
  long index_size = long(log2(rows));
  long tag_size = addressBits - index_size - offset_size;


  Cache iCache = Cache(rows, offset_size, index_size, tag_size, writeBack, allocateOnWrite, missPenalty, assocWays);
  Cache dCache = Cache(rows, offset_size, index_size, tag_size, writeBack, allocateOnWrite, missPenalty, assocWays);
  

  // See the documentation to understand what these variables mean.
  int32_t microOpCount;
  uint64_t instructionAddress;
  int32_t sourceRegister1;
  int32_t sourceRegister2;
  int32_t destinationRegister;
  char conditionRegister;
  char TNnotBranch;
  char loadStore;
  int64_t immediate;
  uint64_t addressForMemoryOp;
  uint64_t fallthroughPC;
  uint64_t targetAddressTakenBranch;
  char macroOperation[12];
  char microOperation[23];

  int64_t totalMicroops = 0;
  int64_t totalMacroops = 0;

  
  fprintf(stdout, "Processing trace...\n");
  
  while (true) {
    int result = fscanf(stdin, 
                        "%" SCNi32
                        "%" SCNx64 
                        "%" SCNi32
                        "%" SCNi32
                        "%" SCNi32
                        " %c"
                        " %c"
                        " %c"
                        "%" SCNi64
                        "%" SCNx64
                        "%" SCNx64
                        "%" SCNx64
                        "%11s"
                        "%22s",
                        &microOpCount,
                        &instructionAddress,
                        &sourceRegister1,
                        &sourceRegister2,
                        &destinationRegister,
                        &conditionRegister,
                        &TNnotBranch,
                        &loadStore,
                        &immediate,
                        &addressForMemoryOp,
                        &fallthroughPC,
                        &targetAddressTakenBranch,
                        macroOperation,
                        microOperation);
                        
    if (result == EOF) {
      break;
    }

    if (result != 14) {
      fprintf(stderr, "Error parsing trace at line %" PRIi64 "\n", totalMicroops);
      abort();
    }

    // For each micro-op
    totalMicroops++;
    iCache.cycles++;

    if(unified){
      if(loadStore != '-'){
	if(loadStore == 'L'){
	  iCache.look_up(addressForMemoryOp, addressForMemoryOp + 1);
	}
	if(loadStore == 'S'){
	  iCache.write(addressForMemoryOp);
	}
	
      }
    }
    else{
      if(loadStore != '-'){
	if(loadStore == 'L'){
	  dCache.look_up(addressForMemoryOp, addressForMemoryOp + 1);
	}
	if(loadStore == 'S'){
	  dCache.write(addressForMemoryOp);
	}
	
      }
    }

    // For each macro-op:
    if (microOpCount == 1) {
      totalMacroops++;
      iCache.look_up(instructionAddress, fallthroughPC);
 

    }
  }  
  
  cout << "I-Cache: " << endl;
  cout << "Total Hits: " << iCache.totalHits << endl;
  cout << "Total Misses: " << iCache.totalMisses << endl;
  cout << "Total Cache Reads: " << iCache.totalReads << endl;
  cout << "Total Cache Writes: " << iCache.totalWrites << endl;
  printf("Hit rate: %.2f\%\n", double(iCache.totalHits) / double(iCache.totalAccess)*100);
  cout << "Total Accesses: " << iCache.totalAccess << endl;
  cout << "Bytes Read: " << iCache.bytesRead << endl;
  cout << "Bytes Written: " << iCache.bytesWritten << endl;
  

  if(unified == false){
    cout << "\nD-Cache: " << endl;
    cout << "Total Hits: " << dCache.totalHits << endl;
    cout << "Total Misses: " << dCache.totalMisses << endl;
    cout << "Total Cache Reads: " << dCache.totalReads << endl;
    cout << "Total Cache Writes: " << dCache.totalWrites << endl;
    printf("Hit rate: %.2f\%\n", double(dCache.totalHits) / double(dCache.totalAccess)*100);
    cout << "Total Accesses: " << dCache.totalAccess << endl;
    cout << "Bytes Read: " << dCache.bytesRead << endl;
    cout << "Bytes Written: " << dCache.bytesWritten << endl;
  }
  cout << "Total processor cycles: " << iCache.cycles + dCache.cycles << endl;


  fprintf(stdout, "Processed %" PRIi64 " trace records.\n", totalMicroops);

  fprintf(stdout, "Micro-ops: %" PRIi64 "\n", totalMicroops);
  fprintf(stdout, "Macro-ops: %" PRIi64 "\n", totalMacroops); 
}
