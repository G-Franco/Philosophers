#pragma once
#include "../../include/Philo_helper.hpp"
#include <gtest/gtest.h>

#define AV_SIZE 7

struct input_params {
  int         t_ac;
  const char  *t_av[AV_SIZE];
  data        t_data;
  bool        should_throw;

  input_params(int ac, const char *av[], data &&data, bool should_throw)
      : t_ac(ac), t_data(std::move(data)), should_throw(should_throw) {
    for (int i = 0; i < AV_SIZE; i++)
      t_av[i] = av[i];
  }

  input_params(const input_params &copy)
      : t_ac(copy.t_ac), t_data(std::move(copy.t_data)), should_throw(copy.should_throw) {
    for (int i = 0; i < AV_SIZE; i++)
      t_av[i] = copy.t_av[i];
  }

  input_params &operator=(const input_params &copy) {
    if (this != &copy) {
      t_ac = copy.t_ac;
      should_throw = copy.should_throw;
      t_data = std::move(copy.t_data);
      for (int i = 0; i < AV_SIZE; ++i) {
        t_av[i] = copy.t_av[i];
      }
    }
    return *this;
  }

  input_params(input_params &&move) noexcept
      : t_ac(move.t_ac), t_data(std::move(move.t_data)), should_throw(move.should_throw) {
    for (int i = 0; i < AV_SIZE; i++)
      t_av[i] = move.t_av[i];
  }

  input_params &operator=(input_params &&move) noexcept {
    if (this != &move) {
      t_ac = move.t_ac;
      should_throw = move.should_throw;
      t_data = std::move(move.t_data);
      for (int i = 0; i < AV_SIZE; ++i) {
        t_av[i] = move.t_av[i];
      }
    }
    return *this;
  }
};

class Input_test : public ::testing::TestWithParam<input_params> {};
