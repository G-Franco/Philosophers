#include "../include/Philo_helper.hpp"

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

int check_input(int ac, char **av, data &data) {
  if (ac < 5 || ac > 6)
    throw(std::runtime_error("ERROR: " + USAGE_MESSAGE));

  data.philos = std::stoi(av[1]);
  data.time_to_die = std::chrono::milliseconds(std::stoi(av[2]));
  data.time_to_eat = std::chrono::milliseconds(std::stoi(av[3]));
  data.time_to_sleep = std::chrono::milliseconds(std::stoi(av[4]));
  data.meals = ac == 6 ? std::stoi(av[5]) : 0;

  if (data.philos <= 0 ||
      data.time_to_die <= std::chrono::milliseconds(0) ||
      data.time_to_eat <= std::chrono::milliseconds(0) ||
      data.time_to_sleep <= std::chrono::milliseconds(0) ||
      (ac == 6 && data.meals <= 0))
    throw(std::runtime_error("ERROR: " + USAGE_MESSAGE));
  return 0;
}

int philo_atom(int ac, char **av, data &data) {
  try
  {
    check_input(ac, av, data);
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }

  data.start = std::chrono::steady_clock::now() +
               std::chrono::milliseconds(data.philos * START_TIME_LAG);
  data.forks = std::vector<std::atomic<bool>>(data.philos);
  for (auto &fork : data.forks)
    fork.store(true);

  std::vector<std::thread> threads;
  std::vector<Philo> philosophers;
  threads.reserve(data.philos + 1);
  philosophers.reserve(data.philos);
  try {
    for (int i = 0; i < data.philos; i++) {
      philosophers.emplace_back(i, data);
      threads.emplace_back(philo_life, std::ref(philosophers.back()), std::ref(data));
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

void overseer(std::vector<Philo> &philosophers, data &data) {
  bool all_ate;
  while (1) {
    all_ate = true;
    for (Philo &philo : philosophers)
    {
      if (philo.get_last_meal() >= data.time_to_die) {
        philo.message(DEAD_MSG);
        data.end.store(true);
        data.ok_end = false;
        return;
      }
      if (data.meals && philo.get_total_meals() < data.meals)
        all_ate = false;
    }
    if (data.meals && all_ate) {
      data.end.store(true);
      return;
    }
  }
}

void philo_life(Philo &philo, data &data) {
  std::this_thread::sleep_until(data.start);
  if (data.philos == 1) {
    data.forks[0].store(false);
    philo.message(FORK_MSG);
    std::this_thread::sleep_for(data.time_to_die);
    return;
  }

  while (!data.end.load()) {
    philo.think();
    philo.eat();
    philo.sleep();
  }
}
