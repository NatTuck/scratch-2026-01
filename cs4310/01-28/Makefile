CFLAGS := -no-pie -Wl,-z,noexecstack

sal: sal.c sal.S
	gcc $(CFLAGS) -o sal sal.c sal.S

clean:
	rm sal
