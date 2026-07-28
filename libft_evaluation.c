/* Created: 2026/02/05 20:39:48 */
/* Updated: 2026/02/05 21:27:54 */
/*    evaluation with ybarut    */

#include <fcntl.h>
#include <stdlib.h>
#include "libft.h"

void *func(void *c)
{
    char *src = (char *)c;
    char *dup;
    int i;

    if (!src)
        return NULL;

    dup = ft_strdup(src);
    if (!dup)
        return NULL;

    i = 0;
    while (dup[i])
    {
        dup[i] = ft_toupper(dup[i]);
        i++;
    }
    return dup;
}


int main(void)
{
	char* s = ft_calloc(6,sizeof(char));
	ft_memset(s,'y',1);
	ft_memset(s+1,'u',1);
	ft_memset(s+2,'s',1);
	ft_memset(s+3,'u',1);
	ft_memset(s+4,'f',1);

	char* s1 = ft_calloc(6,sizeof(char));
	ft_memset(s1,'a',1);
	ft_memset(s1+1,'h',1);
	ft_memset(s1+2,'m',1);
	ft_memset(s1+3,'e',1);
	ft_memset(s1+4,'t',1);

	char* c = ft_calloc(6,sizeof(char));
	ft_memset(c,'a',1);
	ft_memset(c+1,'h',1);
	ft_memset(c+2,'m',1);
	ft_memset(c+3,'e',1);
	ft_memset(c+4,'t',1);

	t_list *n1 = ft_lstnew(s);
	t_list *n2 = ft_lstnew(s1);
	t_list *n3 = ft_lstnew(c);
	
	ft_lstadd_back(&n1,n2);
	ft_lstadd_back(&n2, n3);
	
	t_list *xyz = ft_lstmap(n1,func,free);
	
	int fd = open("output.txt",O_CREAT | O_WRONLY, 0777);
	
	ft_putstr_fd(xyz->content, fd);
	ft_putstr_fd(xyz->next->content, fd);
	ft_putstr_fd(xyz->next->next->content, fd);

	ft_lstclear(&n1, free);
	ft_lstclear(&xyz, free);
}
