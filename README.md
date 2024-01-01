# 42_03-philosophers

### "I never thought philosophy would be so deadly"

## Description


The philosopher's dilemma, often referred to as the dining philosophers problem, is a classic synchronization and concurrency problem. It involves a scenario where five philosophers sit around a dining table, and each philosopher alternates between thinking and eating.The challenge arises from the need to avoid deadlock and resource contention, as philosophers must share a limited number of resources, such as forks. To prevent deadlock, a solution must be implemented to ensure that philosophers can only eat when they have acquired both the fork to their left and the fork to their right. Proper synchronization mechanisms, such as mutexes or semaphores, are crucial to address this dilemma and ensure the efficient utilization of resources.

To see project's overview and global rules [HERE](OVERVIEW.md)

### Project Details


**Programing Language:** C

**Input:**
`./philo` `[number_of_philosophers]` `[time_to_die time_to_eat]` `[time_to_sleep]`
`[number_of_times_each_philosopher_must_eat]`*(optional argument)*

**Approach**: 
- Creating structures using mutexes for forks as `t_fork`, threads for each philosophers as `t_philo` and a structure for the table with all data used in the program as `t_table``.
- Parsing the input and validating if inserted arguments are correct.
- Initializing all data in the main structure `t_table`:
	- the `table` contains `philos` and they have an order to grab the forks to their left and right.
	- to prevent a deadlock situation, an order was implemented to grab forks for the philosophers: if the philosopher's position is ***odd***, he grabs the left fork first and then the right one. For an ***even*** position philosopher, it is the oposite; he grabs the right fork first the left fork.
	- the forks are used as mutexes to prevent data races situation: because some philosophers (***threads***) shares the same fork (***resource***), when one fork is grabed, it is in use (***blocked***), so the other philosooher will wait until it is available (***unblocked***) to grab.

**Sources:***