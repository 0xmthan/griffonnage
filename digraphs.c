#include <string.h>
#include <unistd.h>

int	main(void)
<%
	char	ch<:6:>;

	strcpy(ch, "test\n");
	write(1, ch, 6);
%>