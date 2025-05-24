# 🧙‍♂️ 42-philo — Dining Philosophers Problem

A fun project from the 42 curriculum focused on concurrency, threads, and avoiding race conditions by implementing the classic **Dining Philosophers** problem in C.

## 🧩 Project Overview

This project simulates philosophers sitting at a table, alternating between **thinking**, **eating**, and **sleeping**, while competing for limited forks (resources) without causing **deadlocks** or **data races**.

## 📖 What I learned
- Use POSIX threads (`pthread`)
- Handle concurrent access to shared data
- Prevent deadlocks and starvation
- Write efficient, synchronized C code

## 🚦 Rules of the Simulation

- Philosophers do **not** communicate with each other.
- Each philosopher must **pick up two forks** (mutexes) to eat.
- They **think**, **eat**, and **sleep** in a loop until a stopping condition is met.
- The simulation ends when:
  - A philosopher **dies** from starvation.
  - All philosophers have **eaten a required number of times** (optional argument).

## 📁 Project Structure

```text
42-philo/
├── philo/
│   ├── inc/
│   │   └── philo.h
│   ├── src/
│   │   ├── main.c
│   │   ├── validation.c
│   │   ├── init.c
│   │   ├── delete.c
│   │   ├── simu.c
│   │   ├── action/
│   │   │   ├── routine.c
│   │   │   └── monitor.c
│   │   └── utils/
│   │       ├── utils.c
│   │       └── print.c
│   ├── obj/              # Object files directory (should be created at build time)
│   ├── Makefile
│   └── README.md

```

## 🧪 How to Compile and Run

### Compile

```bash
make
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
./philo 5 800 200 200
```
- 5 philosophers
- Time to die: 800ms
- Time to eat: 200ms
- Time to sleep: 200ms
- Optional fifth argument:
  
```bash
./philo 5 800 200 200 7
```
Each philosopher must eat 7 times before the simulation ends.

## 🛠 Features
✅ Mutex-protected fork access

✅ Death detection and accurate timing

✅ Optional eating limit per philosopher

✅ Clean exit and memory management
