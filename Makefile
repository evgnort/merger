COMMON_OPTIONS = -Wall -Wno-unused-value -O3 -march=skylake

all:
	gcc $(COMMON_OPTIONS) merger.c codeseq.c fft.c parser.c -o merger.out
	gcc $(COMMON_OPTIONS) mixer.c codeseq.c parser.c -o mixer.out