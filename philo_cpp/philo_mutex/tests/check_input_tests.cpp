#include "../include/philo_helper.hpp"
#include "check_input_fixture.hpp"

TEST_P(CheckInputTest, CheckInput) {
  const CheckInputTestParams &params = GetParam();
  int philos, time_to_die, time_to_eat, time_to_sleep, meals;

  if (params.should_throw) {
    EXPECT_THROW(check_input(params.argc, const_cast<char **>(params.argv),
                             philos, time_to_die, time_to_eat, time_to_sleep,
                             meals),
                 std::runtime_error);
  } else {
    EXPECT_NO_THROW(check_input(params.argc, const_cast<char **>(params.argv),
                                philos, time_to_die, time_to_eat, time_to_sleep,
                                meals));
    EXPECT_EQ(philos, params.expected_philos);
    EXPECT_EQ(time_to_die, params.expected_time_to_die);
    EXPECT_EQ(time_to_eat, params.expected_time_to_eat);
    EXPECT_EQ(time_to_sleep, params.expected_time_to_sleep);
    EXPECT_EQ(meals, params.expected_meals);
  }
}

INSTANTIATE_TEST_SUITE_P(
    CheckInputTests, CheckInputTest,
    ::testing::Values(CheckInputTestParams{6,
                                           {"./philo", "5", "1000", "500",
                                            "500", "3", nullptr},
                                           false,
                                           5,
                                           1000,
                                           500,
                                           500,
                                           3},
                      CheckInputTestParams{5,
                                           {"./philo", "5", "1000", "500",
                                            "500", nullptr, nullptr},
                                           false,
                                           5,
                                           1000,
                                           500,
                                           500,
                                           0},
                      CheckInputTestParams{5,
                                           {"./philo", "-5", "1000", "500",
                                            "500", nullptr, nullptr},
                                           true,
                                           0,
                                           0,
                                           0,
                                           0,
                                           0},
                      CheckInputTestParams{5,
                                           {"./philo", "0", "1000", "500",
                                            "500", nullptr, nullptr},
                                           true,
                                           0,
                                           0,
                                           0,
                                           0,
                                           0},
                      CheckInputTestParams{5,
                                           {"./philo", "2147483648", "1000",
                                            "500", "500", nullptr, nullptr},
                                           true,
                                           0,
                                           0,
                                           0,
                                           0,
                                           0},
                      CheckInputTestParams{4,
                                           {"./philo", "5", "1000", "500",
                                            nullptr, nullptr, nullptr},
                                           true,
                                           0,
                                           0,
                                           0,
                                           0,
                                           0},
                      CheckInputTestParams{
                          7,
                          {"./philo", "5", "1000", "500", "500", "3", "extra"},
                          true,
                          0,
                          0,
                          0,
                          0,
                          0}));