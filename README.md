
# Dining philosophers
## Project from 42 school

This project aim to teach on how to create a multithread program and its perks.
Threads are lightweight process that run independently and allow on program to 
multitask.

So what is the difference between forks and threads?

- Memory
Threads share the same memory space, global variables, heap, fds but the stack is
separated.
Forks are new process with a copy of the parent's memory. Any change in child
doesn't affect the parent, fds are copied but independently managed.

- Performance
Threads are lighter, has lower context-switch cost(same address space) and
faster inter-thread communication.
Forks on the other hand are heavier because they are full process creation, slower
to context-switch and need for IPC(inter-process-communication) is necessary the
use of pipes, sockets, shared memory).

- Isolation
Threads: No Isolation, on thread crashing bring everything down.
Forks: Strong isolation. If one child crash the parent process continue.

- Concurrency Model
Threads: Best for tightly-coupled tasks that need shared state of resources.
Forks: Better for isolated, independent tasks.
Difference between Concurrency and parallelism
```https://go.dev/blog/waza-talk```

- Complexity
Threads: require synchronization with mutexes, semaphores, condition variables
to avoid race conditions. Subtle bugs if shared state is mismanaged.
Forks: Easier isolation, need of IPC which increases code Complexity.

Threads are used when the task need collaboration or shared data.
Forks when you need isolation or want to execute a separated program instance.

As for this project is about threads we need to understand mutexes for mandatory
part of the project and semaphores for bonus. 

### Mutexes

A mutex is a synchronization used to prevent multiple threads from accessing
a shared resource simultaneously. It ensures that only one thread can execute
that specific session of the code at a time. This way race conditions are avoided.

A mutex is owned by the thread that locks it. Only the thread that locked can unlocke it.
This ownership prevents other threads from releasing the lock.
If a thread attenpts to lock a mutex that is already locked by another thread, it
will be blocked until the mutex become available. This blocking mechanism ensure
that only one thread can access that code.

A mutex has a binary state: locked and unlocked and ensure mutual exclusion.

One example of how to use mutex.
```c
#include <pthread.h>

pthread_mutex_t lock;

void* thread_function(void* arg) {
    pthread_mutex_lock(&lock);
    // Critical section
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main() {
    pthread_t threads[5];
    pthread_mutex_init(&lock, NULL);
    int i = 0;
    while (i < 5) {
        pthread_create(&threads[i], NULL, thread_function, NULL);
        i++;
    }
    i = 0;
    while (i < 5) {
        pthread_join(threads[i], NULL);
        i++;
    }
    pthread_mutex_destroy(&lock);
    return 0;
}
```


