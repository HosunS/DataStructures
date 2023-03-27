/**
   CSVReader.hpp

   You do NOT need to modify this file as part of your project. This is simply
   a utility for creating an InterferenceGraph type from a graph file as
   mentioned in the README.

*/

#ifndef CSV_READER_H
#define CSV_READER_H

#include "InterferenceGraph.hpp"
#include "proj6.hpp"
#include <string>
#include <unordered_map>
#include <utility>

using namespace proj6;

class CSVReader {
public:
  // You should NOT modify this function. It's used to read an edge in graph
  // file.
  static std::vector<std::string> readRow(std::string &csv_line);

  // You should NOT modify the following function.
  // The source code is provided to you so that you can
  // see how addVertex and addEdge are called to build
  // your InterferenceGraph.
  //
  // This function iterates through the file at `graph_path`
  // line by line, adding each edge to this InterferenceGraph.
  // See the README for an example.
  static InterferenceGraph<Variable> load(const std::string &graph_path);
};

#endif