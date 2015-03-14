all: quick_find_1d_peak quick_find_2d_peak test_case_gen_2d

quick_find_1d_peak: quick_find_1d_peak.c
	gcc -O2 -o quick_find_1d_peak quick_find_1d_peak.c

quick_find_2d_peak: quick_find_2d_peak.c
	gcc -O2 -o quick_find_2d_peak quick_find_2d_peak.c

test_case_gen_2d: test_case_gen_2d.c
	gcc -o test_case_gen_2d test_case_gen_2d.c

run:
	./test_case_gen_2d 10000 | ./quick_find_2d_peak