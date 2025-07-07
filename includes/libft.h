#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

//int		ft_atoi(const char *s1);
//void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t n, size_t size);
//int		ft_isalnum(int c);
//int		ft_isalpha(int c);
//int		ft_isascii(int c);
//int		ft_isdigit(int c);
//int		ft_isprint(int c);
//char	*ft_itoa(int n);
//void	*ft_memchr(const void *memoryblock, int searchedchar, size_t size);
//int		ft_memcmp(const void *p1, const void *p2, size_t size);
void	*ft_memcpy(void *dest, const void *source, size_t size);
//void	*ft_memmove(void *dst, const void *src, size_t size);
void	*ft_memset(void *p, int value, size_t count);
//void	ft_putchar_fd(char c, int fd);
//void	ft_putstr_fd(char *s, int fd);
//void	ft_putendl_fd(char *s, int fd);
//void	ft_putnbr_fd(int n, int fd);
char	**ft_split(char const *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
//char	*ft_strchr(const char *string, int searchedchar);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strdup(const char *src);
//void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strjoin(char const *s1, char const *s2);
//char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
//size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
//size_t	ft_strlcpy(char *dst, const char *src, size_t size);
int		ft_strlen(char *str);
int		ft_strncmp(char *s1, char *s2, size_t l);
//char	*ft_strnstr(const char *s1, const char *s2, size_t l);
//char	*ft_strrchr(const char *string, int searchedchar);
//char	*ft_strtrim(char const *s1, char const *set);
//int		ft_tolower(int c);
//int		ft_toupper(int c);

#endif
