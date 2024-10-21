#pragma once
#include "../../include/Philo.hpp"
#include <gtest/gtest.h>

class Philo_fixture : public ::testing::Test {
  protected:
    data t_data;
    Philo philo;

    Philo_fixture() : t_data(10, 410, 200, 200, 5), philo(0, t_data) {} 
};
