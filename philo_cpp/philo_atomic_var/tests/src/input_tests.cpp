#include "../include/input_fixture.hpp"

TEST_P(Input_test, input_check_test) {
  const input_params &params = GetParam();
  if (params.should_throw) {
    EXPECT_ANY_THROW(check_input(params.t_ac, const_cast<char**>(params.t_av), const_cast<data&>(params.t_data)));
  }
  else {
    EXPECT_NO_THROW(check_input(params.t_ac, const_cast<char**>(params.t_av), const_cast<data&>(params.t_data)));
  }
}

// Named arrays for test cases
const char *av1[] = {"./philo", "10", "410", "200", "200"};
const char *av2[] = {"./philo", "10", "410", "200", "200", "5"};
const char *av3[] = {"./philo", "10", "410", "200"};
const char *av4[] = {"./philo", "10", "410", "200", "200", "100", "100"};
const char *av5[] = {"./philo", "AA", "410", "200", "200"};
const char *av6[] = {"./philo", "10", "AA", "200", "200"};
const char *av7[] = {"./philo", "10", "410", "AA", "200"};
const char *av8[] = {"./philo", "10", "410", "200", "AA"};
const char *av9[] = {"./philo", "10", "410", "200", "200", "AA"};
const char *av10[] = {"./philo", "2147483648", "410", "200", "200"};
const char *av11[] = {"./philo", "-2147483649", "410", "200", "200"};
const char *av12[] = {"./philo", "10", "2147483648", "200", "200"};
const char *av13[] = {"./philo", "10", "-2147483649", "200", "200"};
const char *av14[] = {"./philo", "10", "410", "2147483648", "200"};
const char *av15[] = {"./philo", "10", "410", "-2147483649", "200"};
const char *av16[] = {"./philo", "10", "410", "200", "2147483648"};
const char *av17[] = {"./philo", "10", "410", "200","-2147483649"};
const char *av18[] = {"./philo", "10", "410", "200", "200", "2147483648"};
const char *av19[] = {"./philo", "10", "410", "200", "200", "-2147483649"};
const char *av20[] = {"./philo", "0", "410", "200", "200"};
const char *av21[] = {"./philo", "10", "0", "200", "200"};
const char *av22[] = {"./philo", "10", "410", "0", "200"};
const char *av23[] = {"./philo", "10", "410", "200", "0"};
const char *av24[] = {"./philo", "10", "410", "200", "200", "0"};
const char *av25[] = {"./philo", "-1", "410", "200", "200"};
const char *av26[] = {"./philo", "10", "-1", "200", "200"};
const char *av27[] = {"./philo", "10", "410", "-1", "200"};
const char *av28[] = {"./philo", "10", "410", "200", "-1"};
const char *av29[] = {"./philo", "10", "410", "200", "200", "-1"};

INSTANTIATE_TEST_SUITE_P(
    Input_tests, Input_test,
    ::testing::Values(
        input_params{5, av1, data(), false},
        input_params{6, av2, data(), false},
        input_params{4, av3, data(), true},
        input_params{7, av4, data(), true},
        input_params{5, av5, data(), true},
        input_params{5, av6, data(), true},
        input_params{5, av7, data(), true},
        input_params{5, av8, data(), true},
        input_params{6, av9, data(), true},
        input_params{5, av10, data(), true},
        input_params{5, av11, data(), true},
        input_params{5, av12, data(), true},
        input_params{5, av13, data(), true},
        input_params{5, av14, data(), true},
        input_params{5, av15, data(), true},
        input_params{5, av16, data(), true},
        input_params{5, av17, data(), true},
        input_params{6, av18, data(), true},
        input_params{6, av19, data(), true},
        input_params{5, av20, data(), true},
        input_params{5, av21, data(), true},
        input_params{5, av22, data(), true},
        input_params{5, av23, data(), true},
        input_params{6, av24, data(), true},
        input_params{5, av25, data(), true},
        input_params{5, av26, data(), true},
        input_params{5, av27, data(), true},
        input_params{5, av28, data(), true},
        input_params{6, av29, data(), true}
));
