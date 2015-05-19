all: hashing_linear_probing hashing_double_hashing test_case_gen

hashing_linear_probing: hashing_linear_probing.c
	gcc -O2 -o hashing_linear_probing hashing_linear_probing.c

hashing_double_hashing: hashing_double_hashing.c
	gcc -O2 -o hashing_double_hashing hashing_double_hashing.c

test_case_gen: test_case_gen.c
	gcc -o test_case_gen test_case_gen.c

run:
	time ./test_case_gen 1024 | ./hashing_linear_probing
	time ./test_case_gen 1024 | ./hashing_double_hashing
