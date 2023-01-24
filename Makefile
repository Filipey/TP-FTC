main:
	gcc main.c lib/io/io.c lib/state/state.c lib/transitions/transitions.c -o afdtool
clean:
	rm -rf *.o *.gch afdtool