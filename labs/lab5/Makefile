all: pass_init pass_mp pass_tbb pass_cilk

default: pass_init pass_mp pass_tbb pass_cilk

pass_mp: pass_mp.c
	icc -std=c99 -g -o pass_mp pass_mp.c -lcrypto -fopenmp
pass_tbb: pass_tbb.cpp
	icpc -g -o pass_tbb pass_tbb.cpp -lcrypto -ltbb
pass_cilk: pass_cilk.c
	icc -std=c99 -g -o pass_cilk pass_cilk.c -lcrypto -lcilkrts
pass_init: pass_init.c
	icc -std=c99 -g -o pass_init pass_init.c -lcrypto

clean:
	rm *.o pass_init pass_cilk pass_mp pass_tbb
