#include "../include/system_tests.hpp"

TEST_P(Philo_atom_test, test_philo_atom) {
  test_params params = GetParam();

  int result = philo_atom(params.ac, const_cast<char **>(params.av), t_data);
  EXPECT_EQ(result, params.expected_return);
}

INSTANTIATE_TEST_SUITE_P(
    Philo_atom_tests,
    Philo_atom_test,
    ::testing::Values(
      test_params{5, "./philo", "1", "800", "200", "200", nullptr, 2},
      test_params{6, "./philo", "1", "800", "200", "200", "5", 2},
      test_params{5, "./philo", "5", "800", "400", "400", nullptr, 2},
      test_params{6, "./philo", "5", "800", "400", "400", "5", 2},
      test_params{5, "./philo", "5", "200", "400", "400", nullptr, 2},
      test_params{6, "./philo", "5", "200", "400", "400", "5", 2},
      test_params{5, "./philo", "10", "800", "200", "200", nullptr, 0},
      test_params{6, "./philo", "10", "800", "200", "200", "5", 0},
      test_params{5, "./philo", "10", "410", "200", "200", nullptr, 0},
      test_params{6, "./philo", "10", "410", "200", "200", "5", 0},
      test_params{5, "./philo", "10", "410", "200", "200", nullptr, 0},
      test_params{6, "./philo", "10", "410", "200", "200", "5", 0},
      test_params{5, "./philo", "200", "410", "200", "200", nullptr, 0},
      test_params{6, "./philo", "200", "410", "200", "200", "5", 0},
      test_params{5, "./philo", "2000", "410", "200", "200", nullptr, 0},
      test_params{6, "./philo", "2000", "410", "200", "200", "5", 0},
      test_params{5, "./philo", "20000", "410", "200", "200", nullptr, 0},
      test_params{6, "./philo", "20000", "410", "200", "200", "5", 0},
      test_params{5, "./philo", "200000", "410", "200", "200", nullptr, 0},
      test_params{6, "./philo", "200000", "410", "200", "200", "5", 0}
    )
);