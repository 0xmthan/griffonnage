// 2026-08-18 08:15:00
// evaluation with ayseyilm

#include "libft.h"
#include <stddef.h>
#include <stdio.h>

int main()
{
	int *a = (int *)ft_calloc(1, 4);
	ft_memset(a,16,2);
	ft_memset(a,146,1);
	t_list *node1 = ft_lstnew(a);

	char *s = (char *)ft_calloc(5, 1);
	ft_memset(s,'e',4);
	ft_memset(s,'s',3);
	ft_memset(s,'y',2);
	ft_memset(s,'a',1);
	t_list * node2 = ft_lstnew(s);

	int *b = (int *)ft_calloc(1, 4);
	ft_memset(b,255,4);
	ft_memset(b,214,1);
	t_list *node3 = ft_lstnew(b);

	char *l = ft_strdup("---ayse-yilmaz-nuriye---");
	t_list * node4 = ft_lstnew(l);

	char *k = ft_strtrim(node4->content, "-");
	node4->content = k;
	char **p = ft_split(node4->content, '-');
	node4->content = p[1];

	ft_lstadd_back(&node1,node2);
	ft_lstadd_back(&node1,node3);
	ft_lstadd_back(&node1,node4);

	printf("%d\n" ,(int)node1->content);
	printf("%s\n" ,(char*)node1->next->content);
	printf("%d\n" ,(int)node1->next->next->content);
	printf("%s\n" ,(char*)node1->next->next->next->content);

	free(l);
	free(k);
	free(p[0]);
	free(p[2]);
	//free(p[3]);

	ft_lstclear(&node1, free);
	free(p);
}