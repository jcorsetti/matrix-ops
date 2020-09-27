CC=g++

reduce: reduce.cc matrix.cc fraction.cc
	$(CC) -o reduce reduce.cc matrix.cc fraction.cc
	clear
	./reduce

fraction_test: fraction_test.cc fraction.cc
	$(CC) -o fraction_test fraction_test.cc fraction.cc
	clear
	./fraction_test

matrix_test: matrix_test.cc matrix.cc fraction.cc
	$(CC) -o matrix_test matrix_test.cc matrix.cc fraction.cc
	clear
	./matrix_test
