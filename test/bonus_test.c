#include "libasm_bonus.h"

t_list	*ft_lstnew(void)
{
	t_list	*node;

	node = (t_list*)malloc(sizeof(t_list));
	node->data = NULL;
	node->next = NULL;
	return (node);
}

void	ft_lstadd(t_list **alst, t_list *new)
{
	new->next = *alst;
	*alst = new;
}

int	c_size(t_list *head) {
	int i = 0;

	while (head) {
		head = head->next;
		i++;
	}
	return (i);
}

int		main(void) {
	t_list	*head;
	t_list	*tmp;
	int i = 0;

	head = ft_lstnew();
	while (i++ < 10) {
		tmp = ft_lstnew();
		ft_lstadd(&head, tmp);
	}
	printf("%d\n", ft_list_size(head));
	//c_size(head));
	return (0);
}
