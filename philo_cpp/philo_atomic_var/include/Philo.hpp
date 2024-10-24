#pragma once
#include "struct.hpp"
#include <iostream>
#include <thread>

#define MIN_THINK std::chrono::milliseconds(100)
#define MAX_THINK std::chrono::milliseconds(200)
#define THINK_FACTOR 2
#define START_TIME_LAG 2
const char *const FORK_MSG = "has taken a fork";
const char *const EAT_MSG = "is eating";
const char *const SLEEP_MSG = "is sleeping";
const char *const THINK_MSG = "is thinking";
const char *const DEAD_MSG = "died";

class Philo {
  private:
    int _id;
    int _left_fork;
    int _right_fork;
    data &_data;
    std::atomic<std::chrono::milliseconds::rep> _last_meal;
    std::atomic<int> _total_meals;

  public:
    Philo(int id, data &data);
    Philo(const Philo &copy);
    Philo &operator=(const Philo &copy);
    Philo(Philo &&move) noexcept;
    Philo &operator=(Philo &&move) noexcept;
    bool operator==(const Philo &other);
    bool operator!=(const Philo &other);
    ~Philo();
    int get_id();
    std::chrono::milliseconds get_last_meal();
    int get_total_meals();
    void message(const char *message);
    void think();
    void eat();
    void sleep();
};
