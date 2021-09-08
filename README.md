# philosophers

## Presentation of the project
Philosophers is a project inspired from the well-known dining philosophers problem raised by Edsger Dijkstra in 1958. In computer science, this problem illustrate algorithm concurrency and synchronization between program accessing limited ressources/shared data.

## Project requirements 

In our simulation, we have a given number of philosophers which have a given time until they starve to death. They will take a give time to eat and sleep, and they must consume a certain amount of meal before they walk out from he table. All these parameters are taken as an input of the program. Philosphers also think, but there is not given time for this action. If a philosopher dies during th simulation, the program must stop. When all philosophers are full, the program will also stop. Each action is displayed on the screen with a timestamp and the philosopher position to the table.

Philosophers must not talk to each other when trying to pick a fork and eat, meaning their is not prioritization possible based on time to death.

The project must be fulfilled using only mutexes - semaphores are only available for the bonus part.

## Notions Covered during the project
* Thread: the execution of a set of instructions within a process. Multiple threads might be initialized within a process, which enable parrallel execution of instructions within a program - and asynchronicity. Threads share the virtual memory of the process they start from. This feature may produce conccurency when threads try to access the same data in memory (read or write). 
* Mutex: Functions that protects a critical piece of code from being accessed by multiple threads at the same time.  
* Parrallelism: when 2 or more threads routines are executed simultaneously while interacting with
 *distinct* data elements.  
* Concurrency: when 2 or more threads routines are executed simultaneously while interacting with
 *same* data elements. 
* Data race: When 2 or more threads have a high level of concurrency, they end up reading/writting the same data at the same time which may result in data inconsistancy/incoherence. In this context, mutexes and semaphores are relevant to lock and synchronize data through the execution of the process. 
* Deadlocks: When 2 or more thread/processes mutually await for each other resources, hence locking each other execution indefinetly. 
