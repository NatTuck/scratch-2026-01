

primes: primes.o is_prime.o
	gcc -o primes primes.o is_prime.o -lm

primes.o: primes.c
	gcc -c -o primes.o primes.c

is_prime.o: is_prime.c
	gcc -c -o is_prime.o is_prime.c

clean:
	rm -f primes *.o

.PHONY: clean
