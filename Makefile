NAME = ft_ls

HEADER = ft_ls.h

FLAGS = -Wall -Werror -Wextra

SOURCES  =	main.c

LIB = libftprintf.a

SRCS = $(addprefix $(SOURCES))

OBJS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@make -C ft_printf
	@cp ./ft_printf/$(LIB) ./
	@gcc -I.. -o $(NAME) $(OBJS) -L. -lftprintf

%.o : $(DIR_S)/%.c
	@gcc $(FLAGS) -I $(HEADER) -c  $(SRC)

clean:
	@make clean -C ft_printf/
	@/bin/rm -f $(OBJS)

fclean: clean
	@make fclean -C ft_printf/
	@/bin/rm $(LIB)
	@/bin/rm -f $(NAME)

re: fclean all