all: quick_sort_median_of_3  test_case_gen

quick_sort_median_of_3: quick_sort_median_of_3.c
	gcc -O2 -o quick_sort_median_of_3 quick_sort_median_of_3.c

quick_find_2d_peak: quick_find_2d_peak.c
	gcc -O2 -o quick_find_2d_peak quick_find_2d_peak.c

test_case_gen: test_case_gen.c
	gcc -o test_case_gen test_case_gen.c

run:
	./test_case_gen 1000000 | ./quick_sort_median_of_9
