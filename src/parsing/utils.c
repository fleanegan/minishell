#include "minishell.h"

char	*strdup_from_to(const char *str, int start, int end)
{
	char 	*res;
	int		i;

	if (str == NULL || start > end)
		return (NULL);
	res = malloc((end - start + 2) * sizeof(char));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (start <= end)
	{
		res[i] = str[start];
		i++;
		start++;
	}
	res[i] = '\0';
	return (res);
}
