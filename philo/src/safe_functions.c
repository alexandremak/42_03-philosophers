/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amak <amak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 22:28:17 by amak              #+#    #+#             */
/*   Updated: 2023/11/29 00:46:30 by amak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*safe_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (ret == NULL)
		error_exit("Error wih memory allocation.");
	return (ret);
}

static void	handle_mutex_error(int status, t_option opt)
{
	if (status == 0)
		return;
	if (status == EINVAL && (opt == LOCK || opt == UNLOCK || opt == DESTROY))
		error_exit("The value specified by mutex is invalid.\n");
	else if (status == EINVAL && (opt == INIT))
		error_exit("The value specified by attr is invalid.\n");
	else if (status == EDEADLK)
		error_exit("A deadlock would occur if the thread blocked waiting for "
			"mutex.\n");
	else if (status == EPERM)
		error_exit("The current thread does not hold a lock in mutex.\n");
	else if (status == ENOMEM)
		error_exit("The process cannot allocate enough memory to create "
			"another mutex.\n");
	else if (status == EBUSY)
		error_exit("Mutex is locked.\n");
}

static void handle_thread_error(int status, t_option opt)
{
	if (status == 0)
		return;
	if (status == EAGAIN)
		error_exit("No resources to create another thread.\n");
	else if (status == EPERM)
		error_exit("The caller does not have appropriate permission.\n");
	else if (status == EINVAL && opt == CREATE)
		error_exit("The value specified by attr is invalid.\n");
	else if (status == EINVAL && (opt == JOIN || opt == DETACH))
		error_exit("The value specified by thread is not joinable.\n");
	else if (status == ESRCH)
		error_exit("No thread could be found corresponding to that specified "
		"by the given thread ID, thread.\n");
	else if (status == EDEADLK)
		error_exit("A deadlock was detected or the value of thread specifies "
			"the calling thread.\n");
	
}
void	safe_mutex_handle(t_mutex *mutex, t_option option)
{
	if (option == LOCK)
		handle_mutex_error(pthread_mutex_lock(mutex), option);
	else if (option == UNLOCK)
		handle_mutex_error(pthread_mutex_unlock(mutex), option);
	else if (option == INIT)
		handle_mutex_error(pthread_mutex_init(mutex, NULL), option);
	else if (option == DESTROY)
		handle_mutex_error(pthread_mutex_destroy(mutex), option);
	else
		error_exit("Wrong option for mutex handle.\n");
}

void	safe_thread_handle(pthread_t *thread, void *(foo)(void *), void *data,
		t_option option)
{
	if (option == CREATE)
		handle_thread_error(pthread_create(thread, NULL, foo, data), option);
	else if (option == JOIN)
		handle_thread_error(pthread_join(*thread, NULL), option);
	else if (option == DETACH)
		handle_thread_error(pthread_detach(*thread), option);
	else
		error_exit("Wrong option for thread handle.\n");
}
