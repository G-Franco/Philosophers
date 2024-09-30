#pragma once
#include "../include/Philo.hpp"
#include <gtest/gtest.h>

class Philo_fixture : public ::testing::Test {
protected:
  struct data test_data;
  Philo *philo;

  Philo_fixture()
      : test_data(5, 1000, 500, 500,
                  0), // Initialize test_data with appropriate values
        philo(nullptr) {}

  void SetUp() override {
    // Initialize test_data with appropriate values
    test_data.philos = 5;
    test_data.time_to_die = std::chrono::milliseconds(1000);
    test_data.time_to_eat = std::chrono::milliseconds(500);
    test_data.time_to_sleep = std::chrono::milliseconds(500);
    test_data.start = std::chrono::steady_clock::now();
    test_data.end = false;
    test_data.forks = std::vector<std::mutex>(test_data.philos);

    philo = new Philo(0, test_data);
  }

  void TearDown() override { delete philo; }
};
