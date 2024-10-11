#include "../include/Philo.hpp"

Philo::Philo(int id, data &data)
    : _id(++id),
      _left_fork(_id % 2 ? _id - 1 : _id % data.philos),
      _right_fork(_id % 2 ? _id % data.philos : _id - 1),
      _data(data),
      _last_meal(0),
      _total_meals(0) {}

Philo::Philo(const Philo &copy)
    : _id(copy._id),
      _left_fork(copy._left_fork),
      _right_fork(copy._right_fork),
      _data(copy._data),
      _last_meal(copy._last_meal.load()),
      _total_meals(copy._total_meals.load()) {}

Philo &Philo::operator=(const Philo &copy)
{
  if (*this != copy) {
    _id = copy._id;
    _left_fork = copy._left_fork;
    _right_fork = copy._right_fork;
    _data = copy._data;
    _last_meal = copy._last_meal.load();
    _total_meals = copy._total_meals.load();
  }
  return *this;
}

Philo::Philo(Philo &&move) noexcept
    : _id(move._id),
    _left_fork(move._left_fork),
    _right_fork(move._right_fork),
    _data(move._data),
    _last_meal(move._last_meal.load()),
    _total_meals(move._total_meals.load())
{
  move._id = -1;
  move._left_fork = -1;
  move._right_fork = -1;
}

Philo &Philo::operator=(Philo &&move) noexcept
{
  if (*this != move) {
    _id = move._id;
    _left_fork = move._left_fork;
    _right_fork = move._right_fork;
    _data = move._data;
    _last_meal = move._last_meal.load();
    _total_meals = move._total_meals.load();
    move._id = -1;
    move._left_fork = -1;
    move._right_fork = -1;
  }
  return *this;
}

bool Philo::operator==(const Philo &other)
{
  if (_id == other._id)
    return true;
  return false;
}

bool Philo::operator!=(const Philo &other)
{
  return !(*this == other);
}

Philo::~Philo() {}

std::chrono::milliseconds Philo::get_last_meal() {
  auto now = std::chrono::steady_clock::now();
  auto diff = now - (std::chrono::milliseconds(_last_meal.load()) +_data.start);
  return std::chrono::duration_cast<std::chrono::milliseconds>(diff);
}

int Philo::get_total_meals() {
  return _total_meals.load();
}

// TODO - Implement FIFO?
void Philo::message(const char *message) {
  if (_data.end.load())
    return;
  bool expect = true;
  while (!_data.write.compare_exchange_strong(expect, false)) {
    expect = true;
    std::this_thread::yield();
  }
  auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(
                      std::chrono::steady_clock::now() - _data.start)
                      .count();
  std::cout << timestamp << " " << _id << " " << message << "\n";
  _data.write.store(true);
}

void Philo::think() {
  auto think = get_last_meal();
  if (think < MIN_THINK_THRESHOLD)
    return;
  message(THINK_MSG);
  std::this_thread::sleep_for(think / THINK_FACTOR);
}

void Philo::eat() {
  bool expect = true;
  while (!_data.forks[_left_fork].compare_exchange_strong(expect, false)) {
    expect = true;
    if (_data.end.load())
      return;
    std::this_thread::yield();
  }
  message(FORK_MSG);
  while (!_data.forks[_right_fork].compare_exchange_strong(expect, false))
  {
    expect = true;
    if (_data.end.load())
      return;
    std::this_thread::yield();
  }
  message(FORK_MSG);

  message(EAT_MSG);
  auto now = std::chrono::steady_clock::now();
  auto dif = std::chrono::duration_cast<std::chrono::milliseconds>(now - _data.start).count();
  _last_meal.store(dif);
  std::this_thread::sleep_for(_data.time_to_eat);
  _data.forks[_left_fork].store(true);
  _data.forks[_right_fork].store(true);
  if (_data.end.load())
    return;
  ++_total_meals;
}

void Philo::sleep() {
  message(SLEEP_MSG);
  std::this_thread::sleep_for(_data.time_to_sleep);
}
