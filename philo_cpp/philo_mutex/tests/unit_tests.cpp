#include "Philo_fixture.hpp"

// Check default values
TEST_F(Philo_fixture, default_values) {
  EXPECT_EQ(philo->get_total_meals(), 0);
  EXPECT_EQ(philo->get_last_meal(), test_data.start);
}

// Check min think time
TEST_F(Philo_fixture, think_method) {
  std::this_thread::sleep_for(std::chrono::milliseconds(MIN_THINK_THRESHOLD * 2));
  auto start_time = std::chrono::steady_clock::now();
  philo->think();
  auto end_time = std::chrono::steady_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
  EXPECT_GE(duration.count(), MIN_THINK_THRESHOLD / THINK_FACTOR);
}

// Check sleep duration
TEST_F(Philo_fixture, sleep_method) {
  auto start_time = std::chrono::steady_clock::now();
  philo->sleep();
  auto end_time = std::chrono::steady_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
  EXPECT_GE(duration.count(), test_data.time_to_sleep.count());
}

// Check total meals counter
TEST_F(Philo_fixture, eat_method) {
  EXPECT_EQ(philo->get_total_meals(), 0);
  philo->eat();
  EXPECT_EQ(philo->get_total_meals(), 1);
}

// Test the end_check method
TEST_F(Philo_fixture, end_check_method) {
  test_data.end = true;
  EXPECT_TRUE(philo->end_check());
}

// Test messaging
TEST_F(Philo_fixture, message_method) {
  testing::internal::CaptureStdout();
  philo->message("TESTING", false);
  std::string out = testing::internal::GetCapturedStdout();
  EXPECT_NE(out.find("TESTING"), std::string::npos);
}