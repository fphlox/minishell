NAME = libft.a

SRCS = 	ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c \
		ft_memchr.c	ft_memcmp.c ft_strlen.c ft_strlcpy.c ft_strlcat.c \
		ft_strchr.c ft_strrchr.c ft_strnstr.c ft_strncmp.c \
		ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isspace.c \
		ft_isprint.c ft_toupper.c ft_tolower.c ft_calloc.c ft_strdup.c \
		ft_substr.c ft_strjoin.c ft_strtrim.c \
		ft_split.c ft_split_utils.c ft_dsplit.c \
		ft_atoi.c ft_atoi_base.c ft_itoa.c \
		ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		get_next_line.c

SRCS_B = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c \
		 ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
		 ft_lstins_few_empty.c ft_lstclear.c ft_lstiter.c ft_lstmap.c \
		 ft_lstdel_empty.c \
		 ft_dlst/ft_dlst.c ft_dlst/ft_dlst_two.c

OBJS = $(SRCS:.c=.o)

OBJS_B = $(SRCS_B:.c=.o)

INCLUDE = -I./  -I./ft_dlst/

CC = gcc

CFLAGS = -g -Wall -Wextra -Werror

all : ${NAME} bonus

$(NAME) :	${OBJS}
	ar rcs ${NAME} $?

bonus : ${OBJS_B}
	
%.o	: 	%.c
	${CC} ${CFLAGS} ${INCLUDE} -c $< -o $@
$(OBJS_B) : %.o : %.c
	${CC} ${CFLAGS} ${INCLUDE} -c $< -o $@
	ar rcs ${NAME} $@


clean:
	rm -f ${OBJS} ${OBJS_B}

fclean: clean
	rm -f ${NAME}

re	: fclean all

.PHONY: all clean fclean re
