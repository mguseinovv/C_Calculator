GCC = gcc -std=c11
FLAGS = -Wall -Werror -Wextra
FILES = calc/back/*.c
HEADER = calc/back/credit_calc.h calc/back/s21_smartcalc.h
GCOV = -fprofile-arcs -ftest-coverage -fPIC
LCHECK += $(LIN_FLAGS)
LIN_FLAGS := -lpthread -pthread -lrt -lm -lsubunit
LDFLAGS := -fprofile-arcs --coverage
GCOV_FLAGS := -fprofile-arcs -ftest-coverage
GCOV_FILES = *.gcda

ifeq (${OS}, Linux)
	TEST_FLAGS = -lcheck -pthread -lrt -lm -L.
else
	TEST_FLAGS = -lcheck
endif

all: clean install
	open build/calc.app
	

test: clean 
	gcc test/test.c -c
	${GCC} ${FLAGS} ${TEST_FLAGS} ${GCOV} ${FILES} test.o -o tests
	./tests


install:uninstall
	@echo -------------------INSTALL-------------------
	@make clean
	@cd calc && qmake && make && make clean && rm Makefile && mkdir ../build && mv calc.app ../build/
	@echo -------------------DONE-------------------

uninstall:
	@echo -------------------UNINSTALL-------------------
	@rm -rf build

dist:
	@echo -------------------DIST-------------------
	rm -rf Archive_SmartCalc_v1.0/
	mkdir Archive_SmartCalc_v1.0/
	cp -rf build/calc.app Archive_SmartCalc_v1.0/
	tar cvzf Archive_SmartCalc_v1.0.tgz ./Archive_SmartCalc_v1.0
	rm -rf Archive_SmartCalc_v1.0

dvi:
	open ../readme.html

add_coverage:
	$(eval GCC += --coverage)

gcov_report: clean add_coverage test
	./tests
	gcov $(GCOV_FILES)
	gcovr --html-details --exclude-unreachable-branches -o report.html
	rm -rf *.o *.gcda *.gcno *.gcov
	rm -rf result.out
	rm -rf *.a 
	rm -rf *.o
	open report.html

clean:
	rm -rf
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf result*
	rm -rf *.a
	rm -rf *.o
	rm -rf *.html *.css
	rm -rf *.o *.gcda *.gcno *.gcov
	rm -rf result
	rm -rf *.a 
	rm -rf *.o	
	rm -rf *.info
	rm -rf *.tgz
	rm -rf work
	rm -rf tests

rebuild: clean all

work:
	$(GCC)   calc/back/*.c main.c -o work
	./work
