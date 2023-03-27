/**
   IGWriter.cpp

   You do NOT need to modify this file as part of your project. See IGWriter.hpp
   for more info on how to use the graph writer. You may want to change the
   colors that are used for the different registers though :)

*/

#include "IGWriter.hpp"
#include "proj6.hpp"

#include <array>
#include <fstream>
#include <set>
#include <utility>

namespace {

std::string lookupColor(const Variable &var,
                        const RegisterAssignment &regAssignment) {
  const int NUM_DEFAULT_COLORS = 8;
  // For alternate colors see: https://graphviz.org/doc/info/colors.html
  std::array<std::string, NUM_DEFAULT_COLORS> const colors = {
      "lightpink",       "lightsalmon",  "lightseagreen",   "lightskyblue4",
      "lightsteelblue1", "lightyellow1", "lightgoldenrod4", "lightcoral"};
  if (regAssignment.find(var) == regAssignment.end()) {
    // Value didn't get colored
    return "white";
  }

  int const reg = regAssignment.at(var);

  // Lookup color for this register
  if (reg <= NUM_DEFAULT_COLORS && reg >= 1) {
    return colors.at(reg - 1);
  }

  // More registers than colors. You get a nice boring grey :(
  return "darkgrey";
}

void writeEdges(const InterferenceGraph<Variable> &ig, std::ofstream &stream) {

  std::set<InterferenceGraph<Variable>::EdgeTy> written_edges;

  for (const auto &source : ig.vertices()) {
    for (const auto &destination : ig.neighbors(source)) {

      if (written_edges.find(InterferenceGraph<Variable>::EdgeTy(
              source, destination)) != written_edges.end() ||
          written_edges.find(InterferenceGraph<Variable>::EdgeTy(
              destination, source)) != written_edges.end()) {
        continue;
      }

      stream << source << " -- " << destination << std::endl;
      written_edges.insert(
          InterferenceGraph<Variable>::EdgeTy(source, destination));
    }
  }
}

void writeNodes(const InterferenceGraph<Variable> &ig, std::ofstream &stream,
                const RegisterAssignment &register_assignment) {
  for (const auto &vertex : ig.vertices()) {
    stream << vertex;
    stream << " [style=\"filled\", fillcolor="
           << lookupColor(vertex, register_assignment) << "]" << std::endl;
  }
}

void writeIG(const InterferenceGraph<Variable> &ig, std::ofstream &stream,
             const RegisterAssignment &register_assignment) {
  writeNodes(ig, stream, register_assignment);
  writeEdges(ig, stream);
}

}; // namespace

void IGWriter::write(const InterferenceGraph<Variable> &ig,
                     const std::string &path,
                     const RegisterAssignment &register_assignment) {
  std::ofstream fs;
  fs.open(path);
  fs << "graph {" << std::endl;
  fs << "graph [layout=circo]" << std::endl;
  writeIG(ig, fs, register_assignment);
  fs << "}";
  fs.close();
}