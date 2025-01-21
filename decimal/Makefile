cc=gcc
flags=-Wall -Werror -Wextra -std=c11
gcov_flags=--coverage
temp_dir=.
test_dir=tests
sprintf_dir=.
csharp_dir=.

lib_name=s21_decimal.a
SRCS := $(temp_dir)/add.c $(temp_dir)/mul.c \
	$(sprintf_dir)/comparasion.c  $(csharp_dir)/helpers.c \
	$(csharp_dir)/main.c $(csharp_dir)/div.c
OBJS := $(SRCS:.c=.o)
GCOV_OBJS := $(SRCS:.c=_gcov.o)
DEBUG_OBJS := $(SRCS:.c=_debug.o)

test_files=$(test_dir)/arithmetic_tests.c $(test_dir)/comparison_tests.c \
	$(test_dir)/conversion_tests.c $(test_dir)/other_funcs_tests.c 
TEST_OBJS := $(test_files:.c=.o)
files_for_report=*.gcno *.gcda */*.gcno */*.gcda test_with_gcov s21_string_gcov.a

OS_NAME:=$(shell uname -s)
ifeq ($(OS_NAME), Linux)
	check_flags=-lcheck -lm -lsubunit
endif
ifeq ($(OS_NAME), Darwin)
	check_flags=-lcheck
endif


#standart
#rebuild: clean all
#temp goal
all: $(OBJS)
	@$(cc) $(flags) $(OBJS) -o temp
	@./temp

#all: test gcov_report

clean:
	rm -f $(OBJS) $(TEST_OBJS) $(DEBUG_OBJS) *.a $(files_for_report) $(GCOV_OBJS) 
	rm -rf report gcov_report
	rm -f temp_debug
	rm - f test
#------------

#lib
$(lib_name): $(OBJS)
	ar rc $(lib_name) $(OBJS)
	rm -f $(OBJS)
#------------

#tests
test: $(lib_name) $(TEST_OBJS)
	@echo "\n----------------Tests----------------"
	@$(cc) $(flags) $(test_dir)/test_runner.c $(TEST_OBJS) $(lib_name) $(check_flags) -o test
	@./test
	@rm test
	@echo "-------------------------------------\n"
#-------------

#tests valgrind
test_valgrind: $(lib_name) $(TEST_OBJS)
	@echo "\n----------------Tests----------------"
	@$(cc) $(flags) $(test_dir)/test_runner.c $(TEST_OBJS) $(lib_name) $(check_flags) -o test
	-@valgrind --tool=memcheck --leak-check=full ./test
	@rm test
	@echo "-------------------------------------\n"
#-------------

#gcov reports
gcov: s21_string_gcov.a $(TEST_OBJS)
	$(cc) $(flags) $(gcov_flags)  $(test_dir)/test_runner.c $(TEST_OBJS) s21_string_gcov.a $(check_flags) -o test_with_gcov
	./test_with_gcov
	rm test_with_gcov

s21_string_gcov.a: $(GCOV_OBJS)
	ar rc s21_string_gcov.a $(GCOV_OBJS)
	rm -f $(GCOV_OBJS)
 
gcov_report: gcov
	rm -rf report
	mkdir report
	gcovr --html-details -o ./report/report.html --exclude $(test_dir)/test_runner.c
	rm -f $(files_for_report)

lcov_report: gcov
	lcov --rc branch_coverage=1 -d . -o s21_decimal_coverage.info -c
	genhtml --branch-coverage s21_decimal_coverage.info --output-directory gcov_report
	rm -f s21_decimal_coverage.info $(files_for_report)
#---------------

#for obj
%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

%_gcov.o: %.c
	@$(cc) $(flags) $(gcov_flags) -c $< -o $@

$(test_dir)/%.o: $(test_dir)/%.c
	@$(CC) $(FLAGS) -c $< -o $@

%_debug.o: %.c
	@$(CC) $(FLAGS) -c -g $< -o $@
#--------------- 

#for debug 
debug: $(DEBUG_OBJS)
	gcc $(DEBUG_OBJS) -o temp_debug