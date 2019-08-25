NAME = ft_ssl

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g

HEADER = ./inc/ft_ssl_hd.h

CFILES = ./src/*.c

OFILES = ./src/*.o

LIBFT = libft.a

LCFILES = ./libft/*.c \
		./libft/assets/ft_printf/*.c \
		./libft/assets/get_next_line/get_next_line.c

LOFILES = ./*.o

LHEADER = libft/libft.h \
		libft/assets/get_next_line/get_next_line.h

all: $(NAME)

$(NAME): $(LOFILES)
	ar rc $(LIBFT) $(LOFILES)
	ranlib $(LIBFT)
	$(CC) $(CFLAGS) -I=$(HEADER) -o $(NAME) $(CFILES) $(LIBFT)

$(LOFILES): $(LCFILES)
	$(CC) -c $(CFLAGS) -I=$(LHEADER) $(LCFILES)

clean:
	rm -rf $(OFILES) $(LOFILES)

fclean:
	rm -rf $(NAME) $(LIBFT) $(OFILES) $(LOFILES)

re: fclean all

.PHONY: clean fclean all re
