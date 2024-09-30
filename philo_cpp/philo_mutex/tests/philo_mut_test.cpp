#include "../include/Philo.hpp"
#include "../include/philo_helper.hpp"
#include "time_limited_test.hpp"
#include <algorithm>
#include <gtest/gtest.h>
#include <memory>

#define TEST_TIME_LIMIT 120

int philo_mut(int ac, char **av, data &data);

struct SimulationTestParams {
  int ac;
  std::vector<const char *> av;
  int expected_return_value;
  bool expect_failure;
  std::shared_ptr<data> data_ptr;

  SimulationTestParams(int ac, std::initializer_list<const char *> av_list,
                       int expected_return_value, bool expect_failure)
      : ac(ac), av(av_list), expected_return_value(expected_return_value),
        expect_failure(expect_failure) {
    try {
      if (av_list.size() < 5 || (ac == 6 && av_list.size() < 6)) {
        throw std::invalid_argument("Insufficient arguments provided");
      }
      int arg1 = std::stoi(av_list.begin()[1]);
      int arg2 = std::stoi(av_list.begin()[2]);
      int arg3 = std::stoi(av_list.begin()[3]);
      int arg4 = std::stoi(av_list.begin()[4]);
      int arg5 = (ac == 6) ? std::stoi(av_list.begin()[5]) : -1;
      data_ptr = std::make_shared<data>(arg1, arg2, arg3, arg4, arg5);
    } catch (const std::exception &e) {
      std::cerr << "Error initializing SimulationTestParams: " << e.what()
                << std::endl;
      data_ptr = nullptr; // Set to nullptr to indicate initialization failure
    }
  }

  // Explicit copy constructor
  SimulationTestParams(const SimulationTestParams &other)
      : ac(other.ac), av(other.av),
        expected_return_value(other.expected_return_value),
        expect_failure(other.expect_failure), data_ptr(other.data_ptr) {}

  // Explicit move constructor
  SimulationTestParams(SimulationTestParams &&other) noexcept
      : ac(other.ac), av(std::move(other.av)),
        expected_return_value(other.expected_return_value),
        expect_failure(other.expect_failure),
        data_ptr(std::move(other.data_ptr)) {}

  // Explicit copy assignment operator
  SimulationTestParams &operator=(const SimulationTestParams &other) {
    if (this == &other)
      return *this;
    ac = other.ac;
    av = other.av;
    expected_return_value = other.expected_return_value;
    expect_failure = other.expect_failure;
    data_ptr = other.data_ptr;
    return *this;
  }

  // Explicit move assignment operator
  SimulationTestParams &operator=(SimulationTestParams &&other) noexcept {
    if (this == &other)
      return *this;
    ac = other.ac;
    av = std::move(other.av);
    expected_return_value = other.expected_return_value;
    expect_failure = other.expect_failure;
    data_ptr = std::move(other.data_ptr);
    return *this;
  }
};

SimulationTestParams
CreateSimulationTestParams(int ac, std::initializer_list<const char *> av_list,
                           int expected_return_value, bool expect_failure) {
  return SimulationTestParams(ac, av_list, expected_return_value, expect_failure);
}

class SimulationTest : public ::testing::TestWithParam<SimulationTestParams> {};

void RunSimulationTest(const SimulationTestParams &params) {
  std::vector<char *> av_copy(params.av.size());
  std::transform(params.av.begin(), params.av.end(), av_copy.begin(),
                 [](const char *arg) { return const_cast<char *>(arg); });
  EXPECT_EQ(philo_mut(params.ac, av_copy.data(), *params.data_ptr),
            params.expected_return_value);
}

TEST_P(SimulationTest, RunSimulation) {
  const SimulationTestParams &params = GetParam();
  RunTestWithTimeLimit(std::bind(RunSimulationTest, params), TEST_TIME_LIMIT,
                       params.expect_failure, *params.data_ptr);
}

INSTANTIATE_TEST_SUITE_P(
    RunSimulationTests, SimulationTest,
    ::testing::Values(
        // Argument count different from 5 and 6
        CreateSimulationTestParams(4, {"./philo", "1", "200", "500"}, 1, true),
        CreateSimulationTestParams(7, {"./philo", "1", "200", "500", "500", "5", "extra"}, 1, true),

        // Non-positive integers
        CreateSimulationTestParams(5, {"./philo", "0", "200", "500", "500"}, 1, true),
        CreateSimulationTestParams(5, {"./philo", "-1", "200", "500", "500"}, 1, true),
        CreateSimulationTestParams(5, {"./philo", "1", "-200", "500", "500"}, 1, true),
        CreateSimulationTestParams(5, {"./philo", "1", "200", "-500", "500"}, 1, true),
        CreateSimulationTestParams(5, {"./philo", "1", "200", "500", "-500"}, 1, true),
        CreateSimulationTestParams(6, {"./philo", "0", "200", "500", "500", "5"}, 1, true),
        CreateSimulationTestParams(6, {"./philo", "-1", "200", "500", "500", "5"}, 1, true),
        CreateSimulationTestParams(6, {"./philo", "1", "-200", "500", "500", "5"}, 1, true),
        CreateSimulationTestParams(6, {"./philo", "1", "200", "-500", "500", "5"}, 1, true),
        CreateSimulationTestParams(6, {"./philo", "1", "200", "500", "-500", "5"}, 1, true),
        CreateSimulationTestParams(6, {"./philo", "1", "200", "500", "500", "-5"}, 1, true),

        // Overflows and underflows
        CreateSimulationTestParams(5, {"./philo", "2147483648", "200", "500", "500"}, 1, true),
        CreateSimulationTestParams(5, {"./philo", "-2147483649", "200", "500", "500"}, 1, true),
        CreateSimulationTestParams(5, {"./philo", "1", "2147483648", "500", "500"}, 1, true),
        CreateSimulationTestParams(5, {"./philo", "1", "-2147483649", "500", "500"}, 1, true),
        CreateSimulationTestParams(6, {"./philo", "2147483648", "200", "500", "500", "5"}, 1, true),
        CreateSimulationTestParams(6, {"./philo", "-2147483649", "200", "500", "500", "5"}, 1, true),
        CreateSimulationTestParams(6, {"./philo", "1", "200", "2147483648", "500", "5"}, 1, true),
        CreateSimulationTestParams(6, {"./philo", "1", "200", "500", "-2147483649", "5"}, 1, true),
        CreateSimulationTestParams(6, {"./philo", "1", "200", "500", "500", "2147483648"}, 1, true),
        CreateSimulationTestParams(6, {"./philo", "1", "200", "500", "500", "-2147483649"}, 1, true),

        // Non-numeric inputs
        CreateSimulationTestParams(5, {"./philo", "one", "200", "500", "500"}, 1, true),
        CreateSimulationTestParams(5, {"./philo", "1", "two hundred", "500", "500"}, 1, true),
        CreateSimulationTestParams(5, {"./philo", "1", "200", "five hundred", "500"}, 1, true),
        CreateSimulationTestParams(5, {"./philo", "1", "200", "500", "five hundred"}, 1, true),
        CreateSimulationTestParams(6, {"./philo", "1", "200", "500", "500", "five"}, 1, true),

        // Cases that must fail
        CreateSimulationTestParams(5, {"./philo", "1", "800", "200", "200"}, 1, true),

        // Cases that must work
        CreateSimulationTestParams(5, {"./philo", "4", "800", "200", "200"}, 1, true),
        CreateSimulationTestParams(6, {"./philo", "4", "800", "200", "200", "5"}, 1, true),
        CreateSimulationTestParams(5, {"./philo", "4", "410", "200", "200"}, 1, true),
        CreateSimulationTestParams(6, {"./philo", "4", "410", "200", "200", "10"}, 1, true),
        CreateSimulationTestParams(5, {"./philo", "200", "800", "200", "200"}, 1, true),
        CreateSimulationTestParams(6, {"./philo", "200", "800", "200", "200", "100"}, 1, true),

        // Cases with a lot of philosophers
        CreateSimulationTestParams(5, {"./philo", "200", "410", "200", "200"}, 1, true),
        CreateSimulationTestParams(5, {"./philo", "2000", "410", "200", "200"}, 1, true),
        CreateSimulationTestParams(5, {"./philo", "20000", "410", "200", "200"}, 1, true),
        CreateSimulationTestParams(5, {"./philo", "200000", "410", "200", "200"}, 1, true)
        ));