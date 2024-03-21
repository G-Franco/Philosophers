## What is it?
- A program that simulates the dining philosophers scenario using threads and mutexes (processes and semaphores in the bonus version).

- A set number of philosophers must think, eat and sleep (in this order) and cannot communicate with each other.

- There are as many forks as there are philosophers, but each philosopher must use 2 forks to eat.

- They have set durations to eat and sleep, as well as a maximum length of time they go without eating, or they die of starvation.

- The goal is to keep them all alive, indefinately or until they all eat the required amount of meals.

## How to use this?
1 - Clone this repository

2 - cd philo

  OR
  
  cd philo_bonus

3 - Run make

4 - Run with:

  ./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [max_meals]

  OR

  ./philo_bonus <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [max_meals]
