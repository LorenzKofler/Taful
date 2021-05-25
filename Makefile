CC=gcc

taful: taful.c
	$(CC) taful.c -fPIC -shared -L. -l:libcrypto.a -o libtaful.so
	$(CC) -L. main.c -o main -ltaful

run:
	LD_LIBRARY_PATH=$(LD_LIBRARY_PATH):./ ./main "FlotteKarotte"

clean:
	rm libtaful.so
	rm main
