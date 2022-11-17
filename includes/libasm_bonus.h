#ifndef LIBASM_BONUS_H
# define LIBASM_BONUS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct	s_list
{
	void					*data;
	struct s_list	*next;
}								t_list;

/* Return the number of element in the list */
int	ft_list_size(t_list *begin_list);

/*
** Add a new elem of t_list at the beginning of the list
** Assign data in this elem->data
** Update head pointer if needed
** ft_create_elem() allowed
*/
void	ft_list_push_front(t_list **begin_list, void *data);

/*
** Erase elem of the list whose data is equal to data is equal to the reference data
** Function pointed to by cmp will be used as follow (*cmp)(list_ptr->data, data_ref)
** cmp could be ft_strcmp
** free() allowed
*/
void	ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)());

/*
** Sort the list content by ascending order by comparing two links 
** thanks to a function that can compare the data held in those two links
*/
void	ft_list_sort(t_list **begin_list, int (*cmp)());

/*
** Behave like atoi except str is in a specific base passed are a second parameter
** the atoi() function converts the initial portion of the string pointed to by nptr to int
** If a parameter is incorrect the function return 0
** 			An error can be:
**			- Base is empty or 1
**			- Base has two times the same character
**			- Base contains +/- or whitespaces
*/
int		ft_atoi_base(char *str, char *base);

#endif
