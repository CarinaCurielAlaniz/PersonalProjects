#include <iostream>
#include "MinHeap.h"
#include "graph.h"

int main(int argc, char *argv[]) 
{
  //read arguments
  std::string start = argv[1];         
  std::string goal = argv[2];         
  std::string fileName = argv[3];   
  //start A*
  graph newGraph(fileName,start, goal); 
}