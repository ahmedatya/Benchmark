//My INCLUDES
#include "getMemorySize.c"
#include "base.h"
#include "tictoc.h"

//Standard INCLUDES
#include <stdio.h>     /* printf, scanf, NULL */
#include <stdlib.h>     /* malloc, free, rand */

#ifdef __linux__
#include <string.h>
#endif


int main(int argc, char * argv[])
{
  double portion = 0.9;
  uint64 memory_size = getMemorySize() * portion;
  uint64 page_size = sysconf(_SC_PAGESIZE);
  uint64 page_nums = memory_size/page_size;
  // Need to Configure Parse
  bool debug = true;

  if(debug)
  {
    printf("*--------------------------*\nMemory Information... \n*--------------------------*\n");
    printf("Memory Size (bytes): %lu | ",memory_size);
    printf("Page Size (bytes): %lu | ",page_size);
    printf("Number of Pages: %lu \n",page_nums);
    printf("Note: We allocte %f of the memory \n",portion*100);
  }

  // Allocate memory
  Byte * memory = (Byte * ) malloc(memory_size);

  double iterations = 10;
  double total_mem_time = 0;
  double total_alligned_page = 0;
  double total_unalligned_page =0;

  for(double j =0 ; j < iterations; j++)
  {
      TicToc timer;
      timer.tic();
      memset(memory,0,memory_size);
      total_mem_time+= (timer.toc()/1000000);

      timer.tic();
      for(uint64 i =0 ; i < page_nums; i++ )
      {
         memset(memory + i* page_size,i,page_size);
      }
      total_alligned_page+= (timer.toc()/page_size);

      timer.tic();
      for(uint64 i =0 ; i < page_nums - 1 ; i++ )
      {
         memset(memory + i * page_size + 2,i,page_size);
      }
      total_unalligned_page+=(timer.toc()/(page_size - 1));

  }
  printf("*--------------------------*\nBenchmarking Starting... \n*--------------------------*\n");
  printf("Memory Access Time: %f (secs)\n",total_mem_time/iterations);
  printf("Alligned Page Access Time: %f (usec)\n",total_alligned_page/iterations);
  printf("Unalligned Page Access Time: %f (usec)\n",total_unalligned_page/iterations);

  // Free allocated memory
  free(memory);
}
