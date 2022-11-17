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

int		main(void) {
	t_list	*head;

	head = c_create_node((void*)strdup("KONO WA, DIO DA !!"));
	ft_list_push_front(&head, (void*)strdup("Oh"));
	ft_list_push_front(&head, (void*)strdup("Mukatte kuru no ka ?"));
	ft_list_push_front(&head, (void*)strdup("ZA WARUDO"));
	printf("\033[31mft_list_size\033[00m : \033[36mIn ASM -> \033[00m%d\033[36m & in C -> \033[00m%d\n", ft_list_size(head), c_size(head));
	printf("\033[31mft_list_push_front\033[00m : Pushing 3 elem on a list and print content by following link\n");
	c_print_content(head);
	return (0);
}
