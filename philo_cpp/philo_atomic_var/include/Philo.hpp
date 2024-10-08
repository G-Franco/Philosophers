#pragma once
#include "struct.hpp"
#include <iostream>
#include <thread>

#define MIN_THINK_THRESHOLD std::chrono::milliseconds(100)
#define THINK_FACTOR 2
#define START_TIME_LAG 10
#define FORK_MSG "has taken a fork"
#define EAT_MSG "is eating"
#define SLEEP_MSG "is sleeping"
#define THINK_MSG "is thinking"
#define DEAD_MSG "died"

class Philo{
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
    std::chrono::milliseconds get_last_meal();
    int get_total_meals();
    void message(char *message);
    void think();
    void eat();
    void sleep();
};
