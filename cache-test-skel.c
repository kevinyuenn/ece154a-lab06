/*
YOUR NAME HERE
ECE 154A - Fall 2012
Lab 2 - Mystery Caches
Due: 12/3/12, 11:00 pm

Mystery Cache Geometries:
mystery0:
    block size = 4194304 bytes
    cache size = 16
    associativity = 64 bytes
mystery1:
    block size = 4096 bytes
    cache size = 1
    associativity = 4 bytes
mystery2:
    block size = 4096
    cache size = 128
    associativity = 32 bytes
*/

#include <stdlib.h>
#include <stdio.h>

#include "mystery-cache.h"

/* 
   Returns the size (in B) of the cache
*/
int get_cache_size(int block_size) {
  /* YOUR CODE GOES HERE */
  int addr = 0;
  int blockcount = 1; 
  int cachesize = 0;
  access_cache(0);
  while(access_cache(addr)){
      cachesize = 0;

      do{
        access_cache(addr+cachesize);
        cachesize += block_size;
      } while (cachesize <= blockcount*block_size);

      blockcount *= 2;
  }
  return cachesize-block_size;
}

/*
   Returns the associativity of the cache
*/
int get_cache_assoc(int size) {
  /* YOUR CODE GOES HERE */
  int blocksize = 0;
  access_cache(0);
  while(access_cache(blocksize)){
    blocksize += 4;
  }
  return size/blocksize;

}

/*
   Returns the size (in B) of each block in the cache.
*/
int get_block_size() {
  /* YOUR CODE GOES HERE */
  int addr = 0;
  access_cache(0);
  while(access_cache(addr)){
    addr += 4;
  }
  return addr;

}

int main(void) {
  int size;
  int assoc;
  int block_size;
  
  /* The cache needs to be initialized, but the parameters will be
     ignored by the mystery caches, as they are hard coded.
     You can test your geometry paramter discovery routines by 
     calling cache_init() w/ your own size and block size values. */
  cache_init(0,0);
  
  block_size = get_block_size();
  size = get_cache_size(block_size);
  assoc = get_cache_assoc(size);


  printf("Cache size: %d bytes\n",size);
  printf("Cache associativity: %d\n",assoc);
  printf("Cache block size: %d bytes\n",block_size);
  
  return EXIT_SUCCESS;
}
