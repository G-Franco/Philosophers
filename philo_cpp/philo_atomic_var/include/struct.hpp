#pragma once
#include <chrono>
#include <atomic>
#include <vector>

struct data {
  int philos;
  std::chrono::milliseconds time_to_die;
  std::chrono::milliseconds time_to_eat;
  std::chrono::milliseconds time_to_sleep;
  std::chrono::time_point<std::chrono::steady_clock> start;
  int meals;
  std::atomic<bool> end;
  bool ok_end;
  std::vector<std::atomic<bool>> forks;
  std::atomic<bool> write;

  data()
      : philos(0),
        time_to_die(std::chrono::milliseconds(0)),
        time_to_eat(std::chrono::milliseconds(0)),
        time_to_sleep(std::chrono::milliseconds(0)),
        meals(0),
        end(false),
        ok_end(true),
        forks(),
        write(true) {}

  data(int philos_number, int die, int eat, int sleep, int meals_number)
      : philos(philos_number),
        time_to_die(std::chrono::milliseconds(die)),
        time_to_eat(std::chrono::milliseconds(eat)),
        time_to_sleep(std::chrono::milliseconds(sleep)),
        meals(meals_number),
        end(false),
        ok_end(true),
        forks(philos_number),
        write(true) {
          for (auto &fork : forks)
            fork.store(true);
  }

  data &operator=(const data &copy)
  {
    philos = copy.philos;
    time_to_die = copy.time_to_die;
    time_to_eat = copy.time_to_eat;
    time_to_sleep = copy.time_to_sleep;
    start = copy.start;
    meals = copy.meals;
    end.store(copy.end.load());
    write.store(copy.write.load());
    forks.resize(philos);
    for (auto i = 0; i < philos; i++)
      forks[i].store(copy.forks[i].load());
    return *this;
  }
};
