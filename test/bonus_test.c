#include "libasm_bonus.h"

int ft_is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\r' || c == '\n' || c == '\v' || c == '\f');
}

int get_base(char c)
{
	if (c >= '0' && c <= '9')
		return c - '0';
	else if (c >= 'a' && c <= 'z')
		return c - 'a' + 10;
	else if (c >= 'A' && c <= 'Z')
		return c - 'A' + 10;
	else
		return (-1);
}

int check_error(char *to_check) {
	int	i;

	i = 0;
	while (to_check[i]) {
		if (to_check[i] > 57 || to_check[i] < 48) {
			return (1);
		}
		i++;
	}
	if (i > 2 || i < 0) {
		return (1);
	}
	return (0);
}

int	c_atoi_base(const char *str, char	*str_base)
{
	int i;
	int result;
	int sign;
	int current;
	int base;

	i = 0;
	result = 0;
	sign = 1;
	base = 0;
	/* Step 0 : Check error */
	if (check_error(str_base))
		return 0;
	/* Step 1 : Get base and verify it */
	while (str_base[i]) {
		base = base * 10 + str_base[i] - 48;
		i++;
	}
	if (base < 2 || base > 16)
		return (0);
	i = 0;
	/* Step 2 : Skip whitespace */
	while	(ft_is_space(str[i]))
		i++;
	/* Step 3 : Stock negative sign if negative and ignore it for now */
	if (str[i] == '-' || str[i] == '+')
	{
		if(str[i] == '-')
			sign = -1;
		i++;
	}
	/* Step 4 : get_base for current char and then applied same logic for the loop as the atoi one */
	current = get_base(str[i]);
	while (current >= 0 && current <= base)
	{
		result = result * base + current;
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

void	c_list_sort(t_list **begin_list, int (*cmp)()) {
	void	*tmp;
	t_list	*ptr;

	ptr = *begin_list;
	while (ptr && ptr->next)
	{
		if ((*cmp)(ptr->data, ptr->next->data) > 0)
		{
			tmp = ptr->data;
			ptr->data = ptr->next->data;
			ptr->next->data = tmp;
			ptr = *begin_list;
		}
		else
			ptr = ptr->next;
	}
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

	/* Case where we need to delete everything remaining */
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
}

int		main(void) {
	t_list	*head;

	head = c_create_node((void*)strdup("KONO WA, DIO DA !!"));

	printf("\033[31mft_list_push_front\033[00m : \033[36mPushing 3 elem on existing node ->\033[00m\n");
	ft_list_push_front(&head, (void*)strdup("Mukatte kuru no ka ?"));
	ft_list_push_front(&head, (void*)strdup("ZA WARUDO"));
	ft_list_push_front(&head, (void*)strdup("Ohh !"));
	c_print_content(head);

	printf("\033[31mft_list_sort\033[00m : \033[36m Sort in ascending order ->\033[00m\n");
	ft_list_sort(&head, strcmp);
	c_print_content(head);

	printf("\033[31mft_list_size\033[00m : \033[36mIn ASM -> \033[00m%d\033[36m & in C -> \033[00m%d\n\n", ft_list_size(head), c_size(head));

	printf("\033[31mft_list_remove_if\033[00m :  \033[36mRemove 3 elem and let Ohh ! ->\033[00m\n");
	ft_list_remove_if(&head, (void*)"Mukatte kuru no ka ?", strcmp);
	ft_list_remove_if(&head, (void*)"KONO WA, DIO DA !!", strcmp);
	ft_list_remove_if(&head, (void*)"ZA WARUDO", strcmp);
	//ft_list_remove_if(&head, (void*)"Ohh !", strcmp);
	c_print_content(head);

	printf("\033[31mft_atoi_base\033[00m : \033[36mSent 11 with wrong base, expecting 0 -> \033[00m");
	printf("%d", ft_atoi_base("C0", "-16"));
	printf("%d", ft_atoi_base("C0", "-"));
	printf("%d", ft_atoi_base("C0", "+5"));
	printf("%d", ft_atoi_base("C0", " 5"));
	printf("%d", ft_atoi_base("C0", "5 "));
	printf("%d", ft_atoi_base("C0", " "));
	printf("%d", ft_atoi_base("C0", "100"));
	printf("%d", ft_atoi_base("C0", "1"));
	printf("%d", ft_atoi_base("C0", "17"));
	printf("%d", ft_atoi_base("C0", "Muh!"));
	printf("%d\n", ft_atoi_base("C0", "/"));

	printf("\033[31mft_atoi_base\033[00m : \033[36mCorrect base, tricky str, expecting 192 192 -3 and all 0 -> \033[00m");
	printf("%d", ft_atoi_base("\t \rC0", "16")); // Ignoring whitespace in front of number
	printf(" %d", ft_atoi_base("  c0\?", "16")); // lower case char number + wrong trailing NaN
	printf(" %d", ft_atoi_base("-00000011.", "2")); // Ignoring trailing NaN char on negatives
	printf(" %d", ft_atoi_base(" \ ", "5")); // Return 0 on wrong char after ignoring whitespace
	printf(" %d", ft_atoi_base(" ", "11")); // Empty string of only one space
	printf(" %d", ft_atoi_base("  - aa", "11")); // Space after sign
	printf(" %d", ft_atoi_base("e", "11")); // Wrong char return 0 like ft_atoi
	printf(" %d\n", ft_atoi_base("-.", "11")); // sign then wrong char

	printf("\033[31mft_atoi_base\033[00m : \033[36mCorrect args, sent in base 2, 16, 14 and 5 expecting 192 - 192 - -112 - -90 -> \033[00m\n");
	printf("%d ", ft_atoi_base("11000000", "2")); // 192
	printf("- %d ", ft_atoi_base("C0", "16"));		// 192
	printf("- %d ", ft_atoi_base("-80", "14"));		// -112
	printf("- %d\n", ft_atoi_base("-330", "5"));	// -90
	return (0);
}
