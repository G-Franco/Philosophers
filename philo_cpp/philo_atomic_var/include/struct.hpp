#pragma once
#include <chrono>
#include <atomic>
#include <mutex>
#include <vector>
// #include "Message_queue.hpp"

#define MAX_DURATION std::chrono::milliseconds(120000)

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
  // std::atomic<bool> write;
  std::chrono::milliseconds max_duration;
  // Message_queue message_list;
  std::mutex write;

  data()
      : philos(0),
        time_to_die(std::chrono::milliseconds(0)),
        time_to_eat(std::chrono::milliseconds(0)),
        time_to_sleep(std::chrono::milliseconds(0)),
        start(std::chrono::steady_clock::now()),
        meals(0),
        end(false),
        ok_end(true),
        forks(),
        // write(true),
        max_duration(MAX_DURATION) {}

  data(int philos_number, int die, int eat, int sleep, int meals_number)
      : philos(philos_number),
        time_to_die(std::chrono::milliseconds(die)),
        time_to_eat(std::chrono::milliseconds(eat)),
        time_to_sleep(std::chrono::milliseconds(sleep)),
        start(std::chrono::steady_clock::now()),
        meals(meals_number),
        end(false),
        ok_end(true),
        forks(philos_number),
        // write(true),
        max_duration(MAX_DURATION) {
          for (auto &fork : forks)
            fork.store(true);
  }

  data(const data &copy)
      : philos(copy.philos),
        time_to_die(copy.time_to_die),
        time_to_eat(copy.time_to_eat),
        time_to_sleep(copy.time_to_sleep),
        start(copy.start),
        meals(copy.meals),
        end(copy.end.load()),
        ok_end(copy.ok_end),
        forks(copy.forks.size()),
        // write(copy.write.load()),
        max_duration(MAX_DURATION) {
          for (size_t i = 0; i < copy.forks.size(); ++i) {
            forks[i].store(copy.forks[i].load());
          }
  }

  data &operator=(const data &copy) {
    if (this != &copy) {
      philos = copy.philos;
      time_to_die = copy.time_to_die;
      time_to_eat = copy.time_to_eat;
      time_to_sleep = copy.time_to_sleep;
      start = copy.start;
      meals = copy.meals;
      end.store(copy.end.load());
      ok_end = copy.ok_end;
      // write.store(copy.write.load());
      max_duration = copy.max_duration;
      forks = std::vector<std::atomic<bool>>(copy.forks.size());
      for (size_t i = 0; i < copy.forks.size(); ++i) {
        forks[i].store(copy.forks[i].load());
      }
    }
    return *this;
  }

  data(data &&move) noexcept
      : philos(move.philos),
        time_to_die(move.time_to_die),
        time_to_eat(move.time_to_eat),
        time_to_sleep(move.time_to_sleep),
        start(move.start),
        meals(move.meals),
        end(move.end.load()),
        ok_end(move.ok_end),
        forks(std::move(move.forks)),
        // write(move.write.load()),
        max_duration(MAX_DURATION) {}

  data &operator=(data &&move) noexcept
  {
    if (this != &move) {
      philos = move.philos;
      time_to_die = move.time_to_die;
      time_to_eat = move.time_to_eat;
      time_to_sleep = move.time_to_sleep;
      start = move.start;
      meals = move.meals;
      end.store(move.end.load());
      // write.store(move.write.load());
      max_duration = move.max_duration;
      forks = std::move(move.forks);
    }
    return *this;
  }
};
