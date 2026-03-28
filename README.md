# Philosophers
Philosophers is a concurrency and synchronization project from the 42 School curriculum. It simulates the Dining Philosophers problem, emphasizing multi-threading, mutexes, and proper handling of shared resources to avoid deadlocks and race conditions.

# CUBE_3D
Cube 3D is a 3D graphics project developed as a pair project for the 42 School curriculum. It uses raycasting to render a 3D environment from a 2D map, allowing player movement, perspective changes, and interactive exploration.
In this project, I was responsible for mathematical calculations and the visual rendering, while my partner focused on game logic and input handling.

# Features
* Simulation of the Dining Philosophers problem
* Multi-threaded implementation using POSIX threads (pthread)
* Synchronization with mutexes to prevent race conditions
* Deadlock prevention strategies
* Configurable number of philosophers, eating time, thinking time, and simulation duration
* Monitors philosopher states in real-time

# Installation
```
git@github.com:Lenooka/philosophers.git
cd philosophers
cd philo
make
```
# Usage
```
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```
# Example:
```
./philo 5 800 200 200 7
```
* number_of_philosophers – Total philosophers at the table
* time_to_die – Max time (ms) a philosopher can go without eating
* time_to_eat – Time (ms) a philosopher spends eating
* time_to_sleep – Time (ms) a philosopher spends sleeping
* [optional] number_of_times_each_philosopher_must_eat – Stop condition

# Learning Goals
* Understanding and implementing multi-threading in C
* Managing concurrent access to shared resources
* Preventing deadlocks and race conditions
* Monitoring and controlling thread behavior
* Writing robust, real-time simulations
