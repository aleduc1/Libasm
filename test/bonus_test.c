#include "libasm_bonus.h"

t_list	*c_create_node(void *data_arg)
{
	t_list	*node;

	node = (t_list*)malloc(sizeof(t_list));
	node->data = data_arg;
	node->next = NULL;
	return (node);
}

int	c_size(t_list *head) {
	int i = 0;

	while (head) {
		head = head->next;
		i++;
	}
	return (i);
}

void	c_print_content(t_list *head) {
	while (head) {
		printf("%s\n", (char*)head->data);
		head = head->next;
	}
	printf("\n");
}

/*
** Erase elem of the list whose data is equal to data is equal to the reference data
** Function pointed to by cmp will be used as follow (*cmp)(list_ptr->data, data_ref)
** cmp could be ft_strcmp
** free() allowed
*/
void	c_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)()) {
	t_list *ptr;
	t_list *tmp;

	ptr = *begin_list;
	tmp = NULL;

	/* Case where we need to delete the first x beginning */
	while (ptr && !(*cmp)((char*)ptr->data, (char*)data_ref)) {
		tmp = ptr;
		ptr = ptr->next;
		tmp->next = NULL;
		free(tmp->data);
		free(tmp);
	}
	*begin_list = ptr;
	tmp = NULL;

	/* Case where we need to delete either in the middle or the last without the one before it */
	while (ptr && ptr->next) {
		if ((*cmp)((char*)ptr->next->data, (char*)data_ref) == 0) {
			tmp = ptr->next;
			ptr->next = tmp->next;
			ptr = ptr->next;
			free(tmp->data);
			free(tmp);
		}
		else {
			ptr = ptr->next;
		}
	}

	/* Case where we deleted the penultimate and we still have to delete the last */
	if (ptr && !ptr->next) {
		if ((*cmp)((char*)ptr->data, (char*)data_ref) == 0) {
			free(ptr->data);
			free(ptr);
			ptr = NULL;
		}
	}
}

int		main(void) {
	t_list	*head;

	head = c_create_node((void*)strdup("KONO WA, DIO DA !!"));
	ft_list_push_front(&head, (void*)strdup("Ohh !"));
	ft_list_push_front(&head, (void*)strdup("Mukatte kuru no ka ?"));
	ft_list_push_front(&head, (void*)strdup("ZA WARUDO"));
	printf("\033[31mft_list_size\033[00m : \033[36mIn ASM -> \033[00m%d\033[36m & in C -> \033[00m%d\n", ft_list_size(head), c_size(head));
	printf("\033[31mft_list_push_front\033[00m : Pushing 3 elem on a list and print content by following link\n");
	c_print_content(head);
	printf("\033[31mft_list_remove_if\033[00m : Trying my function in C first, then printing my list again to see if 'Ohh !' has been deleted \n");
//	c_list_remove_if(&head, (void*)"ZA WARUDO", strcmp);
//	c_list_remove_if(&head, (void*)"Ohh !", strcmp);
//	c_list_remove_if(&head, (void*)"Mukatte kuru no ka ?", strcmp);
//	c_list_remove_if(&head, (void*)"KONO WA, DIO DA !!", strcmp);
	c_print_content(head);
	return (0);
}
