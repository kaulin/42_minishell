/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 10:18:18 by kkauhane          #+#    #+#             */
/*   Updated: 2024/05/08 13:10:03 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <ctype.h>
# include <limits.h>
# include <stdarg.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000

# endif

typedef struct s_list
{
	int				content;
	struct s_list	*next;
}				t_list;

int		ft_isalpha(int c);
int		ft_isdigit(char c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
size_t	ft_strlen(const char *str);
void	*ft_memset(void *arr, int c, size_t n);
void	ft_bzero(void *s, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t len);
void	*ft_memmove(void *dst, const void *src, size_t len);
size_t	ft_strlcpy(char *dest, char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(char *str, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
t_list	*ft_lstnew(int content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstiter(t_list *lst);
int		ft_printf(const char *format, ...);
int		parse_format(char *format, char c, va_list args, int temp);
int		check_type(char *format, va_list args, char c);
int		print_str(char *string);
int		ft_printchar(char c);
int		print_hex(unsigned int n, char c);
int		put_hex(unsigned int n, char c, char *string, int i);
char	*create_string(unsigned int n, int *pointer);
int		print_nbr(int n);
int		ft_putnbr(int n);
int		numcount(int n);
int		print_pointer(va_list args);
int		put_ptr(unsigned long pointer);
int		ptr_len(unsigned long num);
int		print_unsigned_nbr(unsigned int n);
char	*unsigned_itoa(unsigned int n);
int		unsigned_num_len(unsigned int n);
char	*get_next_line(int fd);
size_t	ft_strlen_gnl(char *str);
char	*ft_strchr_gnl(char *str, int c);
char	*ft_substr_gnl(char *s, unsigned int start, size_t len);
char	*ft_strdup_gnl(char *s1);
char	*ft_strjoin_gnl(char *s1, char *s2);
char	*ft_free_gnl(char **str);

#endif
