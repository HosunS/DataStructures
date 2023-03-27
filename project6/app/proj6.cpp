#include "proj6.hpp"
#include "CSVReader.hpp"
#include "InterferenceGraph.hpp"
#include <vector>
#include <unordered_map>
#include <iostream>
using namespace proj6;
void selectionSort(std::vector<std::pair<int,Variable>> &vector) 
{
  int i;
  int j;
  int max;

  for(i = 0 ; i < vector.size(); i++)
  {
    max = i;
    for( j = i + 1; j < vector.size(); j++)
    {
      if(vector[j].first > vector[max].first)
      {
        max = j;
      }
    }
    if ( max != i)
    {
      std::swap(vector[max], vector[i]);
    }
  }
}

// int part(std::vector<std::pair<int,Variable>> &vect, int lowest, int highest)
// {
//   auto pivot = vect[highest];
//   int i = (lowest - 1);

//   for(int j = lowest;j <= highest - 1; j++)
//   {
//     if(vect[j].first > pivot.first)
//     {
//       i++;
//       std::swap(vect[i],vect[j]);
//     }
//   }
//   std::swap(vect[i + 1],vect[highest]);
//   return (i + 1);

// }

// void quicksort(std::vector<std::pair<int,Variable>> &vect,int lowest,int highest)
// {
//   if(lowest < highest){
//     int partindex = part(vect,lowest,highest);
//     quicksort(vect,lowest,partindex-1);
//     quicksort(vect,partindex + 1,highest);
//   }
// }
// assignRegisters
//
// This is where you implement the register allocation algorithm
// as mentioned in the README. Remember, you must allocate at MOST
// d(G) + 1 registers where d(G) is the maximum degree of the graph G.
// If num_registers is not enough registers to accomodate the passed in
// graph you should return an empty map. You MUST use registers in the
// range [1, num_registers] inclusive.
RegisterAssignment proj6::assignRegisters(const std::string &path_to_graph, int num_registers) noexcept {
  InterferenceGraph<Variable> ig = CSVReader::load(path_to_graph);
  std::unordered_map<Variable,int> registers;
  std::vector<std::pair<int,Variable>> desVector; // descending order by its degrees holds degrees and vertex value
  std::unordered_set<Variable> vertex = ig.vertices();
  std::vector<int> color;

  for(auto x: vertex)
  {
    desVector.push_back({ig.degree(x),x});
  }

  // for(int i = 0 ; i < desVector.size(); i++)
  // {
  //   std::cout << desVector[i].first << " " << desVector[i].second << std::endl;
  // }
  selectionSort(desVector); // have it sort descending
  // quicksort(desVector,0,desVector.size()-1);
  // for(int i = 0 ; i < desVector.size(); i++)
  // {
  //   std::cout << desVector[i].first << " " << desVector[i].second << std::endl;
  // }

  int max = desVector[0].first + 1; //get the max from the descending vector (holds highest value) (g)+1
  for(int i = 1; i <= max;i++) 
  {
    color.push_back(i);
  }

  // for(int i = 0; i < color.size(); i++)
  // {
  //   std::cout << color.at(i) << std::endl;
  // }
  auto iterator = color.begin(); // start at first register color
  auto iterator1 = desVector.begin();

  while(iterator1 != desVector.end()) //while we havent gone through the whole register list
  {
    std::unordered_set<std::string> temp; // holds neighbors of vertex + 
    if(registers.find(iterator1->second) == registers.end())// if vertex from sorted list is not in  registers
    {
      if(num_registers < *iterator) // if #of edges is greater than the number of registers return empty
      {
        return {};
      }
      else if(num_registers >= *iterator and color.end() != iterator) // color exists, and the #of edges is less than number of registers
      {
        registers.insert({iterator1->second,*iterator}); // insert (vertex element, color)
        temp = ig.neighbors(iterator1->second);
        temp.insert(iterator1->second);
        
        for(auto i = desVector.begin(); i != desVector.end(); i++) //iterate through desVector
        {
          if(temp.find(i->second) == temp.end())
          {
            registers.insert({i->second, *iterator});
            temp.insert(ig.neighbors(i->second).begin(), ig.neighbors(i->second).end());
            temp.insert(i->second);
          }
        }
        iterator++;
      }
    }
    iterator1++;
  }
  // for(auto x: registers)
  // {
  //   std::cout << x.first << " " << x.second << std::endl;
  // }
    return registers;
}