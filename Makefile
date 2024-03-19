# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pdubois <pdubois@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/06 17:15:50 by pdubois           #+#    #+#              #
#    Updated: 2023/08/06 17:15:50 by pdubois          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = c++
CFLAGS = -Wall -Wextra -Werror -g

NAME = computorv1

RM = rm -rf

SRCS_NAME =	main.cpp \
			Equation.cpp \
			Expression.cpp \
			Term.cpp \

SRCS_PATH =	srcs
SRCS = $(addprefix $(SRCS_PATH)/, $(SRCS_NAME))

INCS_NAME =	computorv1.hpp \
			Equation.hpp \
			Expression.hpp \
			Term.hpp \

INCS_PATH =	includes
INCS = $(addprefix $(INCS_PATH)/, $(INCS_NAME))

OBJS = $(addprefix $(OBJDIR)/, ${SRCS_NAME:.cpp=.o})
OBJDIR = objs

LIBS =

all: directories ${NAME}

${OBJDIR}/%.o : ${SRCS_PATH}/%.cpp ${INCS}
	${CC} ${CFLAGS} -I ${INCS_PATH} -c $< -o $@

directories:
	mkdir -p ${OBJDIR}

${NAME}: ${OBJS} ${INCS}
	${CC} -o ${NAME} ${OBJS} ${LIBS}

clean:
	${RM} ${OBJDIR}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY : all clean fclean re directories