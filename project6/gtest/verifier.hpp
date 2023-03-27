#ifndef __VERIFIER__HPP
#define __VERIFIER__HPP

#include "proj6.hpp"
#include "gtest/gtest.h"

using namespace proj6;

testing::AssertionResult verifyAllocation(const std::string &path_to_graph,
                                          int num_registers,
                                          const RegisterAssignment &mapping);

#endif