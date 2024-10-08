#pragma once
#include <chrono>
#include <mutex>
#include <vector>

struct data {
  int philos;
  std::chrono::milliseconds time_to_die;
  std::chrono::milliseconds time_to_eat;
  std::chrono::milliseconds time_to_sleep;
  std::chrono::time_point<std::chrono::steady_clock> start;
  int meals;
  bool end;
  bool ok_end;
  std::vector<std::mutex> forks;
  std::mutex end_m;
  std::mutex write_m;

  data(int philos_number, int die, int eat, int sleep, int meals_number)
      : philos(philos_number), time_to_die(std::chrono::milliseconds(die)),
        time_to_eat(std::chrono::milliseconds(eat)),
        time_to_sleep(std::chrono::milliseconds(sleep)),
        meals(meals_number), end(false), ok_end(true), forks(philos_number) {}
};
