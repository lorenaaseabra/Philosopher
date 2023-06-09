## Dining Philosophers Problem
This is a C code that solves the dining philosophers problem using pthreads and semaphores. The dining philosophers problem involves a group of philosophers sitting around a table with bowls of spaghetti. The philosophers alternate between thinking and eating. However, there are only a limited number of forks (equal to the number of philosophers), and each philosopher needs two forks to eat.

## Requirements
To compile and run this code, you need to have the following libraries installed:

* pthread.h
* semaphore.h
* stdio.h

## Code Explanation
The code initializes and uses the following variables:

* status: An array to track the status of each philosopher. It can be one of the following values: EATING, HUNGRY, or THINKING.
* s: An array of semaphores, where each semaphore represents a philosopher.
* mutex: A semaphore used for mutual exclusion.
* N: The number of philosophers.
The main function initializes the semaphores and creates philosopher threads. It also waits for the philosopher threads to finish execution.

The phil function is executed by each philosopher thread. It runs an infinite loop where the philosopher thinks, takes forks, eats, and puts forks.

The take_fork function is called by a philosopher when they want to eat. It first waits on the mutex semaphore to acquire mutual exclusion. Then it checks if the left and right neighbors are not eating. If both neighbors are not eating, the philosopher starts eating and releases the mutex. Otherwise, the philosopher changes their status to HUNGRY, prints that they are hungry, releases the mutex, and waits on their own semaphore s[id] until they are signaled to start eating.

The put_fork function is called by a philosopher when they finish eating. Similar to take_fork, it first waits on the mutex semaphore for mutual exclusion. Then it changes the philosopher's status to THINKING. It checks if the left and right neighbors were hungry and if the corresponding forks are available. If both conditions are satisfied, it allows the left and right neighbors to start eating by signaling their respective semaphores s[id_left] and s[id_right]. Finally, it releases the mutex.

## Usage
1. Compile the code using a C compiler:

```
gcc -o dining_philosophers dining_philosophers.c -lpthread
```

2. Run the compiled executable:

```
./dining_philosophers
```
The program will then start running with the specified number of philosopher threads. Each philosopher will take turns thinking and eating, avoiding deadlock and starvation by using semaphores to control access to the forks.

Please note that the code provided assumes correct usage and does not include error handling or input validation.
