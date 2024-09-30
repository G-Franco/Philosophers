#pragma once
#include "../include/Philo.hpp"
#include <gtest/gtest.h>

struct CheckInputTestParams {
  int argc;
  const char *argv[7];
  bool should_throw;
  int expected_philos;
  int expected_time_to_die;
  int expected_time_to_eat;
  int expected_time_to_sleep;
  int expected_meals;
  int extra_to_fail;
};

class CheckInputTest : public ::testing::TestWithParam<CheckInputTestParams> {};
