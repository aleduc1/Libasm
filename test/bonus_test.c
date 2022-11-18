#include "libasm_bonus.h"

int ft_is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\r' || c == '\n' || c == '\v' || c == '\f');
}

int get_base(char c)
{
	if(c >= '0' && c <= '9')
		return c - '0';
	else if (c >= 'a' && c <= 'z')
		return c - 'a' + 10;
	else if (c >= 'A' && c <= 'Z')
		return c - 'A' + 10;
	else
		return (-1);
}

int check_error(int to_check) {
	if (to_check > 16 || to_check < 1) {
		return 1;
	}
	return 0;
}

int	c_atoi_base(const char *str, int str_base)
{
	int i;
	int result;
	int sign;
	int current;

	i = 0;
	result = 0;
	sign = 1;
	/* Step 0 : Check error */
	if (check_error(str_base))
		return 0;
	/* Step 1 : Skip whitespace */
	while(ft_is_space(str[i]))
		i++;
	/* Step 2 : Stock negative sign if negative and ignore it for now */
	if(str[i] == '-' || str[i] == '+')
	{
		if(str[i] == '-')
			sign = -1;
		i++;
	}
	/* Step 3 : get_base for current char and then applied same logic for the loop as the atoi one */
	current = get_base(str[i]);
	while(current >= 0 && current < str_base)
	{
		result = result * str_base + current;
		i++;
		current = get_base(str[i]);
	}
	return (result * sign);
}

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

void	c_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)()) {
	t_list *ptr;
	t_list *tmp;

	ptr = *begin_list;
	tmp = NULL;

	/* Case where we need to delete the first x beginning node */
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
		printf("i here with ptr being : %s, and ptr->next being : %s\n", (char*)ptr->data, (char*)ptr->next->data);
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

// ** EDIT ** turns out this part wasnt needed at all since i only increment in the else part and not in the if part, so we can clear the penultimate and then check the last, or any combination needed (at least that i can think of right now), i will still keep it as reference in case im wrong and i need to code in asm too
//	/* Case where we deleted the penultimate and we still have to delete the last */
//	if (ptr && !ptr->next) {
//		if ((*cmp)((char*)ptr->data, (char*)data_ref) == 0) {
//			free(ptr->data);
//			free(ptr);
//			ptr = NULL;
//		}
//	}
}

int		main(void) {
	t_list	*head;

	head = c_create_node((void*)strdup("KONO WA, DIO DA !!"));
	ft_list_push_front(&head, (void*)strdup("Ohh !"));
	ft_list_push_front(&head, (void*)strdup("Mukatte kuru no ka ?"));
	ft_list_push_front(&head, (void*)strdup("ZA WARUDO"));
	printf("\033[31mft_list_size\033[00m : \033[36mIn ASM -> \033[00m%d\033[36m & in C -> \033[00m%d\n", ft_list_size(head), c_size(head));
	printf("\033[31mft_list_push_front\033[00m : \033[36mPushing 3 elem on existing node\033[00m\n");
	c_print_content(head);
	printf("\033[31mft_list_remove_if\033[00m :  \033[36mRemove 3 elem and let Ohh !\033[00m\n");
	ft_list_remove_if(&head, (void*)"Mukatte kuru no ka ?", strcmp);
	ft_list_remove_if(&head, (void*)"KONO WA, DIO DA !!", strcmp);
	ft_list_remove_if(&head, (void*)"ZA WARUDO", strcmp);
	//ft_list_remove_if(&head, (void*)"Ohh !", strcmp);
	//c_list_remove_if(&head, (void*)"Mukatte kuru no ka ?", strcmp);
	//c_list_remove_if(&head, (void*)"KONO WA, DIO DA !!", strcmp);
	//c_list_remove_if(&head, (void*)"ZA WARUDO", strcmp);
	//c_list_remove_if(&head, (void*)"Ohh !", strcmp);
	c_print_content(head);
	printf("\033[31mft_atoi_base\033[00m : \033[36mSent on base 16 and 2, expecting 192 - 192 ->\033[00m %d - %d\n", c_atoi_base("C0", 16), c_atoi_base("11000000", 2));
	printf("\033[31mft_atoi_base\033[00m : \033[36mExpecting 0 on wrong param ->\033[00m %d\n", c_atoi_base("C0", -16));
	return (0);
}
