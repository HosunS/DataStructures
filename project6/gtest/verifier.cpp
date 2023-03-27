/**
   verifier.cpp

   You do NOT need to modify this file as part of your project. This is simply
   a utility for verifying that your register allocation is correct for a given
   graph.

*/

#include "verifier.hpp"
#include "CSVReader.hpp"
#include "InterferenceGraph.hpp"
#include <fstream>
#include <gtest/gtest.h>
#include <sstream>

using namespace proj6;

testing::AssertionResult verifyAllocation(const std::string &path_to_graph,
                                          int num_registers,
                                          const RegisterAssignment &mapping) {

  std::string line;
  std::ifstream file_stream(path_to_graph);
  std::unordered_map<Variable, unsigned> degrees;
  std::unordered_set<Variable> variables;
  std::vector<std::pair<Variable, Variable>> interferences;

  while (std::getline(file_stream, line)) {
    const auto &row = CSVReader::readRow(line);
    for (const auto &v: row) {
      variables.insert(v);
      if (degrees.find(v) == degrees.end()) {
        degrees[v] = 0;
      }
    }
    if (row.size() == 2) {
      degrees[row[0]]++;
      degrees[row[1]]++;
      interferences.push_back(std::make_pair(row[0], row[1]));
    }
  }

  for (const auto& v: variables) {
    if (mapping.find(v) == mapping.end()) {
      return testing::AssertionFailure()
             << "Variable " << v
             << " did not get mapped to a register!";
    }

    if (mapping.at(v) < 1 || mapping.at(v) > num_registers)
      return testing::AssertionFailure()
             << "Variable " << v << " mapped to register "
             << mapping.at(v) << " which is out of range [" << 1 << ","
             << num_registers << "]";
  }

  for (const auto& interference : interferences) {
    if (mapping.at(interference.first) == mapping.at(interference.second))
      return testing::AssertionFailure()
             << "Variables " << interference.first << " and " << interference.second
             << " were mapped to the same register: " << mapping.at(interference.first);
  }

  if (variables.empty()) {
    return testing::AssertionSuccess();
  }

  const auto highest_degree =
      std::max_element(
          std::begin(degrees), std::end(degrees),
          [](const auto &p1, const auto &p2) { return p1.second < p2.second; })
          ->second;

  std::unordered_set<Register> unique_registers;
  for (const auto &e : mapping)
    unique_registers.insert(e.second);

  const auto MAX_ALLOWED_REGS = highest_degree + 1;
  const auto NUM_USED_REGS = unique_registers.size();
  if (NUM_USED_REGS > MAX_ALLOWED_REGS) {
    return testing::AssertionFailure()
           << "Too many registers were used! Expected at most "
           << MAX_ALLOWED_REGS << " but you used " << NUM_USED_REGS;
  }

  return testing::AssertionSuccess();
}