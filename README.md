# 🍝 Philosophers

A multithreading project that simulates the classic dining philosophers problem using threads and mutexes.

## 📋 Table of Contents

- [About](#about)
- [The Problem](#the-problem)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Arguments](#arguments)
- [Program Behavior](#program-behavior)
- [Implementation Details](#implementation-details)
- [Project Structure](#project-structure)
- [Examples](#examples)

## 🎯 About

This project is part of the 42 curriculum and focuses on the fundamentals of threading, mutexes, and process synchronization. The goal is to implement a solution to the dining philosophers problem where philosophers must share forks to eat without starving or creating deadlocks.

## 🤔 The Problem

One or more philosophers sit at a round table with a large bowl of spaghetti in the middle. The philosophers alternate between three activities:

- **🍽️ Eating** - Requires two forks (left and right)
- **💭 Thinking** - No resources needed
- **😴 Sleeping** - No resources needed

### Constraints

- There are as many forks as philosophers
- A philosopher needs **two forks** to eat
- Philosophers don't communicate with each other
- Philosophers don't know when another is about to die
- The simulation stops when a philosopher dies of starvation
- **Philosophers must avoid dying!**

## ✨ Features

- ✅ Each philosopher is represented as a separate thread
- ✅ Fork states protected by mutexes to prevent duplication
- ✅ No data races
- ✅ Death detection within 10ms
- ✅ Clean message logging without overlap
- ✅ Optional stopping condition (all philosophers eat N times)

## 🔧 Installation

```bash
git clone https://github.com/papacolas/42-Philosophers.git
cd 42-Philosophers
make
```

## 🚀 Usage

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

## 📝 Arguments

| Argument | Description |
|----------|-------------|
| `number_of_philosophers` | The number of philosophers (and forks) at the table |
| `time_to_die` | Time (ms) a philosopher can survive without eating |
| `time_to_eat` | Time (ms) it takes to eat (while holding two forks) |
| `time_to_sleep` | Time (ms) a philosopher spends sleeping |
| `number_of_times_each_philosopher_must_eat` | *(Optional)* Simulation stops when all philosophers have eaten this many times |

### Valid Input Requirements

- All arguments must be positive integers
- `number_of_philosophers` must be at least 1
- Time values must be in milliseconds

## 📊 Program Behavior

### Log Format

The program outputs state changes in the following format:

```
timestamp_in_ms X has taken a fork
timestamp_in_ms X is eating
timestamp_in_ms X is sleeping
timestamp_in_ms X is thinking
timestamp_in_ms X died
```

Where:
- `timestamp_in_ms` = current time in milliseconds since simulation start
- `X` = philosopher number (1 to number_of_philosophers)

### Rules

- Messages are displayed without overlapping
- Death messages appear within 10ms of actual death
- No data races allowed
- Philosopher 1 sits next to the last philosopher (circular table)

## 🛠️ Implementation Details

### Threading Model

- Each philosopher runs in its own thread
- Main thread monitors for death conditions
- Threads are created with `pthread_create` and joined with `pthread_join`

### Synchronization

- One mutex per fork to prevent concurrent access
- Additional mutexes for shared data protection
- Careful lock ordering to avoid deadlocks

### Death Prevention

- Continuous monitoring thread checks philosopher states
- Timestamps track last meal time
- Quick detection ensures 10ms death reporting requirement

## 📁 Project Structure

```
.
├── Makefile
├── includes/
│   └── philo.h          # Header file with structures and prototypes
└── src/
    ├── main.c           # Program entry point
    ├── parsing.c        # Argument validation and parsing
    ├── init.c           # Data structure initialization
    ├── init_mutex.c     # Mutex initialization
    ├── threads.c        # Thread creation and management
    ├── routine.c        # Philosopher routine (main loop)
    ├── routine_sub_functions.c  # Eating, sleeping, thinking actions
    ├── monitoring.c     # Death and completion monitoring
    ├── monito_check.c   # Monitoring helper functions
    ├── time.c           # Time utility functions
    ├── utils.c          # General utility functions
    └── cleaning.c       # Memory and mutex cleanup
```

## 💡 Examples

### Example 1: No one should die
```bash
./philo 5 800 200 200
# 5 philosophers, 800ms to die, 200ms to eat, 200ms to sleep
# Simulation runs indefinitely (until Ctrl+C)
```

### Example 2: No one should die
```bash
./philo 4 410 200 200
# 4 philosophers, tight timing but survivable
```

### Example 3: One philosopher should die
```bash
./philo 4 310 200 100
# 4 philosophers, impossible timing (310 < 200 + 100)
# A philosopher will die
```

### Example 4: With meal limit
```bash
./philo 5 800 200 200 7
# Simulation stops when all philosophers have eaten 7 times
```

### Example 5: Single philosopher
```bash
./philo 1 800 200 200
# Only one fork available, philosopher must die
```

## 🧪 Testing Tips

- Test with different numbers of philosophers (1, 2, 5, 100, 200)
- Test edge cases: `time_to_die < time_to_eat`
- Test with odd and even numbers of philosophers
- Use tools like `valgrind` to check for memory leaks and data races
- Verify death detection timing with precision

## 🧹 Cleaning

```bash
make clean   # Remove object files
make fclean  # Remove object files and executable
make re      # Rebuild everything
```

## ⚠️ Important Notes

- **No global variables** are used
- **No data races** in the implementation
- All memory is properly freed
- All mutexes are properly destroyed
- Death detection is accurate within 10ms

## 📚 External Functions Used

- `memset`, `printf`, `malloc`, `free`, `write`
- `usleep`, `gettimeofday`
- `pthread_create`, `pthread_detach`, `pthread_join`
- `pthread_mutex_init`, `pthread_mutex_destroy`
- `pthread_mutex_lock`, `pthread_mutex_unlock`

## 🎓 Learning Outcomes

This project teaches:
- Thread creation and synchronization
- Mutex usage and deadlock prevention
- Race condition avoidance
- Resource sharing between concurrent processes
- Timing precision in concurrent programming

## 👤 Author

**papacolas**

- GitHub: [@papacolas](https://github.com/papacolas)

## 📄 License

This project is part of the 42 School curriculum.
Do not use this repo for your cursus.

---


