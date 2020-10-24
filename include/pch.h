#pragma once

// I/O
#include <iostream>
#include <fstream>

// STL
#include <vector>
#include <string>
#include <bitset>
#include <tuple>
#include <array>
#include <random>
#include <algorithm>
#include <type_traits>

// C
#include <cmath>
#include <ctime>

// MPC
#include <eigen3/Eigen/QR>
#include <eigen3/Eigen/Core>
#include <cppad/cppad.hpp>
#include <cppad/ipopt/solve.hpp>

// Other libraries
#include <yaml-cpp/yaml.h>
#include <jsoncpp/json/writer.h>

// CMake defines NDEBUG when built in any configuration other that debug
#ifndef NDEBUG
#define DEBUG_LOG(x) std::cout << "\033[0;33m [ LOG-DEBUG ] \033[0m" << x << "\n"
#else
#define DEBUG_LOG(x)
#endif // NDEBUG