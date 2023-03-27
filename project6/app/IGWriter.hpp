/**
   IGWriter.hpp

   InterfaceGraph Writer

   You do NOT need to modify this file as part of your project.

   See the "Visualizing Your Register Allocation" section of the README.md
   for more information.
   
   This file contains functionality for writing a colored InterferenceGraph
   to a file in the DOT format. The utility `dot` can be used to view the
   corresponding file. You are welcome to modify this file if you want to use 
   different/more colors for visualizing your register allocation algorithm output.

   Example use from a GTest:

    const std::string GRAPH = "gtest/graphs/four.csv";

    InterferenceGraph<Variable> ig = CSVReader::load(GRAPH);

    const RegisterMapping& mapping =  assignRegisters(ig,
   3);

    IGWriter::write(ig, "gtest/graphs/four.dot", mapping);

    Then you can use the command:

      dot gtest/graphs/four.dot -o gtest/graphs/four.png -Tpng

    Which will output a PNG of your colored graph that you can open. Note this
   requires the graphviz package:

      `sudo apt install graphviz` (note you made need to run `sudo apt update`
   first.)

     You can view the PNG in VS Code.

*/

#ifndef IG_WRITER_H
#define IG_WRITER_H

#include "InterferenceGraph.hpp"
#include "proj6.hpp"
#include <string>

using namespace proj6;

class IGWriter {
public:
  static void write(const InterferenceGraph<Variable> &IG,
                    const std::string &path,
                    const RegisterAssignment &registerAssignment);
};

#endif