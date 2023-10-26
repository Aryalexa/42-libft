
// char	*ft_strndup(const char *s1, size_t n)
// {
// 	char	*dup;
// 	size_t	len;
// 	size_t	i;

// 	len = ft_strlen(s1);
// 	if (len < n)
// 		n = len;
// 	dup = (char *)malloc((n + 1) * sizeof(char));
// 	if (dup == NULL)
// 		return (NULL);
// 	i = 0;
// 	while (i < n)
// 	{
// 		dup[i] = s1[i];
// 		i++;
// 	}
// 	dup[i] = '\0';
// 	return (dup);
// }