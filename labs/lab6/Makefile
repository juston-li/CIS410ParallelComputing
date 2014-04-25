all: crypto_serial crypto_mp crypto_tbb crypto_cilk

default: all

crypto_mp: crypto_mp.c
	icc -std=c99 -o crypto_mp crypto_mp.c key.c -fopenmp
crypto_tbb: crypto_tbb.cpp
	icpc -std=c++11 -o crypto_tbb crypto_tbb.cpp key.c -ltbb
crypto_cilk: crypto_cilk.c
	icc -std=c99 -o crypto_cilk crypto_cilk.c key.c -lcilkrts
crypto_serial: serial.c key.c
	icc -std=c99 -o crypto_serial serial.c key.c

clean:
	rm -f *.o crypto_serial crypto_mp crypto_tbb crypto_cilk decryptedOut encryptedOut
