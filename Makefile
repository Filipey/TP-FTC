main:
		gcc main.c lib/io/io.c lib/state/state.c lib/transitions/transitions.c lib/alphabet/alphabet.c lib/afd/afd.c lib/cli/cli.c lib/utils/utils.c -o afdtool
clean:
		rm -rf *.o *.gch afdtool

clean-op:
		rm -rf outputs/*.dot outputs/*.pdf outputs/*.txt

debug:
		gcc -g main.c lib/io/io.c lib/state/state.c lib/transitions/transitions.c lib/alphabet/alphabet.c lib/afd/afd.c lib/cli/cli.c lib/utils/utils.c -o afdtool