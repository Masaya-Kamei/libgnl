vpath	%.c srcs

SRCS	=	get_next_line.c get_next_line_utils.c

OBJSDIR	=	./objs
OBJS	=	$(addprefix $(OBJSDIR)/, $(SRCS:.c=.o))

INCLUDE	=	-I./includes
NAME	=	libgnl.a

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
AR		=	ar rc
RM		=	rm -f

LIBDCLISTDIR	=	libdclist
LIBDCLIST		=	$(LIBDCLISTDIR)/libdclist.a
LIBDCLISTTARGET	=	all

LIBINCLUDEDIR	:= -I$(LIBDCLISTDIR)/includes

all		:	$(NAME)

$(NAME)	:	$(LIBDCLIST) $(OBJS)
			cp $(LIBDCLIST) $(NAME)
			$(AR) $(NAME) $(OBJS)

$(OBJSDIR)/%.o	:	%.c
			@mkdir -p $(dir $@)
			$(CC) $(CFLAGS) $(INCLUDE) $(LIBINCLUDEDIR) -o $@ -c $<

$(LIBDCLIST):
			make -C $(LIBDCLISTDIR) $(LIBDCLISTTARGET)

clean	:
			make -C $(LIBDCLISTDIR) clean
			$(RM) $(OBJS)

fclean	:	clean
			make -C $(LIBDCLISTDIR) fclean
			$(RM) $(NAME)

re		:	fclean all

debug	:	CFLAGS +=	-g
debug	:	re

address	:	CFLAGS += 	-g -fsanitize=address
address	:	re

leak	:	CC		=	/usr/local/opt/llvm/bin/clang
leak	:	CFLAGS += 	-g -fsanitize=leak
leak	:	re

.PHONY	:	all clean fclean re debug address leak
