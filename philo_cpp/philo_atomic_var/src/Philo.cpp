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
  if (this->_id = other._id)
    return true;
  return false;
}

bool Philo::operator!=(const Philo &other)
{
  return !(*this == other);
}

Philo::~Philo() {}
