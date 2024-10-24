#include "../../include/Philo_helper.hpp"
#include <gtest/gtest.h>

struct test_params {
  int ac;
  const char *av[6];
  int expected_return;
};

class Philo_atom_test : public ::testing::TestWithParam<test_params> {
  protected:
    data t_data;
};
