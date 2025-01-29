/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorales <emorales@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:58:41 by emorales          #+#    #+#             */
/*   Updated: 2025/01/24 16:58:41 by emorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*safe_malloc(size_t size)
{
	void	*ret;

	ret = malloc(size);
	if (ret == NULL)
		error_exit("malloc error\n");
	return (ret);
}

void	handle_mutex_errors(int status, t_mcode mcode)
{
	if (status == 0)
		return ;
	if (status == EINVAL && (mcode == LOCK || mcode == UNLOCK
			|| mcode == DESTROY))
	{
		error_exit("The value specified by mutex is invalid.\n");
	}
	else if (status == EINVAL && (mcode == INIT))
		error_exit("The value specified by attr is invalid.\n");
	else if (status == EDEADLK)
		error_exit("Deadlock if the thread blocked wait for mutex.\n");
	else if (status == EPERM)
		error_exit("The current thread does not hold a lock on mutex.\n");
	else if (status == ENOMEM)
		error_exit("Cannot allocate enough memory to create another mutex.\n");
	else if (status == EBUSY)
		error_exit("Mutex is locked.\n");
}

void	safe_mutex_handle(pthread_mutex_t *mutex, t_mcode mcode)
{
	// printf("Código da safe_mutex %u\n", mcode);
	// //printf("MUTEX %p\n", (void *)mutex);
	if (mcode == LOCK)
		handle_mutex_errors(pthread_mutex_lock(mutex), mcode);
	else if (mcode == UNLOCK)
		handle_mutex_errors(pthread_mutex_unlock(mutex), mcode);
	else if (mcode == INIT)
		handle_mutex_errors(pthread_mutex_init(mutex, NULL), mcode);
	else if (mcode == DESTROY)
		handle_mutex_errors(pthread_mutex_destroy(mutex), mcode);
	else
		error_exit("Mutex code error\n");
}

void	handle_thread_errors(int status, t_mcode mcode)
{
	if (status == 0)
		return ;
	if (status == EAGAIN)
		error_exit("No resources to create another thread\n");
	else if (status == EPERM)
		error_exit("The called does not have appropriate permission\n");
	else if (status == EINVAL && mcode == CREATE)
		error_exit("The value specified by attr is invalid.\n");
	else if (status == EINVAL && (mcode == JOIN || mcode == DETACH))
		error_exit("The value specified by thread is not joinable.\n");
	else if (status == ESRCH)
		error_exit("No thread found to the given thread ID.\n");
	else if (status == EDEADLK)
		error_exit("Deadlock detected.\n");
}

void safe_thread_handle(pthread_t *thread, void *(*foo)(void *), void *data, t_mcode mcode) //entender com IA, trocar foo, no philo.h tb
{
	if (mcode == CREATE)
		handle_thread_errors(pthread_create(thread, NULL, foo, data), mcode);
	else if (mcode == JOIN)
		handle_thread_errors(pthread_join(*thread, NULL), mcode);
	else if (mcode == DETACH)
		handle_thread_errors(pthread_detach(*thread), mcode);
	else
		error_exit("Wrong code for thread handle.\n");
}
