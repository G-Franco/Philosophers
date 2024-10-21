#include "../include/Philo_fixture.hpp"

TEST_F(Philo_fixture, test_get_id) {
  EXPECT_EQ(philo.get_id(), 1);
}

TEST_F(Philo_fixture, test_get_last_meal) {
  EXPECT_EQ(philo.get_last_meal(), std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - t_data.start));
}

TEST_F(Philo_fixture, test_get_last_meal_2) {
  auto t = std::chrono::milliseconds(100);
  std::this_thread::sleep_for(t);
  EXPECT_GE(philo.get_last_meal(), std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - t_data.start));
}

TEST_F(Philo_fixture, test_get_total_meals) {
  EXPECT_EQ(philo.get_total_meals(), 0);
  philo.eat();
  EXPECT_EQ(philo.get_total_meals(), 1);
  philo.eat();
  EXPECT_EQ(philo.get_total_meals(), 2);
  philo.eat();
  philo.eat();
  philo.eat();
  philo.eat();
  EXPECT_EQ(philo.get_total_meals(), 6);
}

TEST_F(Philo_fixture, test_message) {
  const char *t_message = "TESTING";
  testing::internal::CaptureStdout();
  philo.message(t_message);
  std::string out = testing::internal::GetCapturedStdout();
  EXPECT_NE(out.find(t_message), std::string::npos);
}

TEST_F(Philo_fixture, test_think) {
  auto t_start = std::chrono::steady_clock::now();
  philo.think();
  auto t_end = std::chrono::steady_clock::now();
  auto t_duration = std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_start);
  EXPECT_GE(t_duration, MIN_THINK);
  EXPECT_LE(t_duration, MAX_THINK);
}

TEST_F(Philo_fixture, test_sleep) {
  auto t_start = std::chrono::steady_clock::now();
  philo.sleep();
  auto t_end = std::chrono::steady_clock::now();
  auto t_duration = std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_start);
  EXPECT_GE(t_duration, t_data.time_to_sleep);
}
