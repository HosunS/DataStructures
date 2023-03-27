#include "CSVReader.hpp"
#include "IGWriter.hpp"
#include "InterferenceGraph.hpp"
#include "proj6.hpp"
#include "verifier.hpp"
#include "gtest/gtest.h"

// Warning: These are *NOT* exhaustive tests.
// You should consider creating your own unit tests
// to test the functionality of your code entirely.

namespace {

using namespace proj6;

TEST(RequiredPart1, SimpleAddEdgesAndVertices) {
  const auto &GRAPH = "gtest/graphs/simple.csv";

  const InterferenceGraph<Variable> &ig = CSVReader::load(GRAPH);

  EXPECT_EQ(ig.numEdges(), 3);
  EXPECT_EQ(ig.numVertices(), 3);
}

TEST(RequiredPart1, Neighbors) {
  const auto &GRAPH = "gtest/graphs/simple.csv";

  const InterferenceGraph<Variable> &ig = CSVReader::load(GRAPH);
  const std::unordered_set<Variable> &expected_neighbors = {"y", "z"};

  EXPECT_EQ(ig.neighbors("x"), expected_neighbors);
}

TEST(RequiredPart2, SimpleSuccess) {
  // Load the graph pointed to by simple.csv
  const auto &GRAPH = "gtest/graphs/simple.csv";
  const auto NUM_REGS = 3;

  // Provide 3 registers to the register allocation algorithm.
  // Note, the highest degree in this graph is two, so all three
  // will be needed.
  const auto &allocation = assignRegisters(GRAPH, NUM_REGS);
  IGWriter::write(CSVReader::load(GRAPH), "gtest/graphs/simple_success.dot",
                  allocation);

  EXPECT_TRUE(verifyAllocation(GRAPH, NUM_REGS, allocation));
}

TEST(RequiredPart2, SimpleFail) {
  // Load the graph pointed to by simple.csv
  const auto &GRAPH = "gtest/graphs/simple.csv";
  const auto NUM_REGS = 2;

  // Provide 2 registers to the register allocation algorithm.
  // Note, the highest degree in this graph is two, so the allocation
  // cannot be completed.
  const auto &allocation = assignRegisters(GRAPH, NUM_REGS);
  EXPECT_TRUE(allocation.empty());
}

TEST(RegisterAllocation, 500stress) {
  const auto &GRAPH = "gtest/graphs/500stress.csv";
  const auto NUM_REGS = 500;
  const auto &allocation = assignRegisters(GRAPH, NUM_REGS);
  IGWriter::write(CSVReader::load(GRAPH),"gtest/graphs/simple_success.dot",allocation);
  EXPECT_TRUE(verifyAllocation(GRAPH, NUM_REGS, allocation));
}

TEST(RegisterAllocation, 11reg) {
  const auto &GRAPH = "gtest/graphs/11reg.csv";
  const auto NUM_REGS = 11;
  const auto &allocation = assignRegisters(GRAPH, NUM_REGS);
  IGWriter::write(CSVReader::load(GRAPH),"gtest/graphs/11reg.dot",allocation);
  EXPECT_TRUE(verifyAllocation(GRAPH, NUM_REGS, allocation));
}

TEST(RegisterAllocation, 1000stress) {
  const auto &GRAPH = "gtest/graphs/1000stress.csv";
  const auto NUM_REGS = 1001;
  const auto &allocation = assignRegisters(GRAPH, NUM_REGS);
  IGWriter::write(CSVReader::load(GRAPH),"gtest/graphs/1000stress.dot",allocation);
  EXPECT_TRUE(verifyAllocation(GRAPH, NUM_REGS, allocation));
}

TEST(RegisterAllocation, smalltest) {
  const auto &GRAPH = "gtest/graphs/smalltest.csv";
  const auto NUM_REGS = 3;
  const auto &allocation = assignRegisters(GRAPH, NUM_REGS);
  IGWriter::write(CSVReader::load(GRAPH),"gtest/graphs/smalltest.dot",allocation);
  EXPECT_TRUE(verifyAllocation(GRAPH, NUM_REGS, allocation));
}

TEST(RegisterAllocation, bigbipartite) {
  const auto &GRAPH = "gtest/graphs/big_bipartite.csv";
  const auto NUM_REGS = 5;
  const auto &allocation = assignRegisters(GRAPH, NUM_REGS);
  IGWriter::write(CSVReader::load(GRAPH),"gtest/graphs/big_bipartite.dot",allocation);
  EXPECT_TRUE(verifyAllocation(GRAPH, NUM_REGS, allocation));
}

TEST(RegisterAllocation, lonevertex) {
  const auto &GRAPH = "gtest/graphs/lonevertex.csv";
  const auto NUM_REGS = 5;
  const auto &allocation = assignRegisters(GRAPH, NUM_REGS);
  IGWriter::write(CSVReader::load(GRAPH),"gtest/graphs/lonevertex.dot",allocation);
  EXPECT_TRUE(verifyAllocation(GRAPH, NUM_REGS, allocation));
}


} // end namespace
