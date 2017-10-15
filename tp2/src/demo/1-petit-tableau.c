#include "../colimacon/colimacon.h"


int main(int argc, char** argv)
{
  if(argc < 3)
  {
    printf("Usage: colimacon [cols] [rows]\n");
    return -1;
  }
  int line= atoi(argv[1]);
  int col= atoi(argv[2]);

  int** table= colimacon(line, col); 
  print_table( table, line, col);
}
