/**
   CSVReader.cpp

   You do NOT need to modify this file as part of your project. This is simply
   a utility for creating an InterferenceGraph type from a graph file as
   mentioned in the README.

*/

#include "CSVReader.hpp"
#include "InterferenceGraph.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <utility>
#include <vector>

std::vector<std::string> CSVReader::readRow(std::string &s) {
  std::vector<std::string> row = {};

  std::stringstream stream(s);
  std::string cell;
  while(std::getline(stream, cell, ',')) {
    row.push_back(cell);
  }
  return row;
}

// Again, do NOT modify the following function.
InterferenceGraph<Variable> CSVReader::load(const std::string &graph_path) {

  InterferenceGraph<Variable> ig;
  std::string line;
  std::ifstream file_stream(graph_path);
  
  if (!file_stream.good()) {
    throw std::runtime_error("File " + graph_path + " does not exist!");
  }

  while (std::getline(file_stream, line)) {
    const auto &row = readRow(line);
    if (row.size() > 2) {
      throw std::runtime_error("Graph contains row with more than two vertices: " + graph_path);
    }

    for (const auto& v: row) {
      ig.addVertex(v);
    }

    if (row.size() == 2) {
      ig.addEdge(row.at(0), row.at(1));
    }
  }

  // Note: copy constructor not needed due to copy ellision.
  return ig;
}