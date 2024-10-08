#include "../include/philo_helper.hpp"
#include "../include/Philo.hpp"

// Message to be displayed whenever an error occurs in input checks
const std::string USAGE_MESSAGE =
    "Usage: ./philo\n"
    "number_of_philosophers\n"
    "time_to_die\n"
    "time_to_eat\n"
    "time_to_sleep\n"
    "[number_of_times_each_philosopher_must_eat]\n"
    "USE ONLY POSITIVE INTEGERS\n"
    "TIMES MUST BE IN ms";

void check_input(int ac, char **av, int &philos, int &time_to_die,
                 int &time_to_eat, int &time_to_sleep, int &meals) {
  if (ac < 5 || ac > 6)
    throw std::runtime_error(USAGE_MESSAGE);
  // Check if the values are non-positive or overflow
  try {
    philos = std::stoi(av[1]);
    time_to_die = std::stoi(av[2]);
    time_to_eat = std::stoi(av[3]);
    time_to_sleep = std::stoi(av[4]);
    meals = ac == 6 ? std::stoi(av[5]) : 0;
    if (philos <= 0 || time_to_die <= 0 || time_to_eat <= 0 ||
        time_to_sleep <= 0 || (ac == 6 && meals <= 0))
      throw std::runtime_error(USAGE_MESSAGE);
  } catch (const std::exception &e) {
    throw std::runtime_error(USAGE_MESSAGE);
  }
}

void philo_life(Philo &philo, data &data) {
  std::this_thread::sleep_until(data.start);
  while (true) {
    // lock_guard automatically unlocks mutex when going out of scope
    {
      std::lock_guard<std::mutex> lock(data.end_m);
      if (data.end)
        break;
    }
    philo.think();
    philo.eat();
    philo.sleep();
  }
}

void end(data &data) {
  std::lock_guard<std::mutex> lock(data.end_m);
  data.end = true;
}

// Loops over every philosopher and checks if any has died
// and if all have eaten the required amount (if applicable)
void overseer(std::vector<Philo> &philosophers, data &data) {
  bool all_full;
  while (true) {
    all_full = true;
    for (auto &philo : philosophers) {
      if (std::chrono::steady_clock::now() - philo.get_last_meal() >=
          data.time_to_die) {
        end(data);
        philo.dead();
        data.ok_end = false;
        return;
      }
      if (data.meals && philo.get_total_meals() < data.meals)
        all_full = false;
    }
    if (data.meals && all_full) {
      end(data);
      return;
    }
  }
}

int philo_mut(int ac, char **av, data &data) {
  int philos, time_to_die, time_to_eat, time_to_sleep, meals;
  try {
    check_input(ac, av, philos, time_to_die, time_to_eat, time_to_sleep, meals);
  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
    return 1;
  }
  data.philos = philos;
  data.time_to_die = std::chrono::milliseconds(time_to_die);
  data.time_to_eat = std::chrono::milliseconds(time_to_eat);
  data.time_to_sleep = std::chrono::milliseconds(time_to_sleep);
  data.meals = meals;
  // Add some lag to the start time based on the number of philosophers
  // so that all start the simulation at the same time.
  // Without this, for a large amount of philosophers,
  // some of the later ones may start dead if they are created time_to_die
  // after the start of the simulation
  data.start = std::chrono::steady_clock::now() +
               std::chrono::milliseconds(philos * START_TIME_LAG);
  std::vector<std::thread> threads;
  std::vector<Philo> philosophers;
  threads.reserve(philos + 1);
  philosophers.reserve(philos);
  try {
    for (int i = 0; i < philos; i++) {
      philosophers.emplace_back(i, std::ref(data));
      threads.emplace_back(philo_life, std::ref(philosophers.back()),
                           std::ref(data));
    }
    threads.emplace_back(overseer, std::ref(philosophers), std::ref(data));
  } catch (...) {
    std::cerr << "Error while creating threads or philosophers.\n";
    return 1;
  }
  for (auto &thread : threads)
    thread.join();
  if (data.ok_end)
    return 0;
  return 1;
}
