all: jipa1 jipa2 jipb jis

jipa1: jipa1.c
	mpicc $< -o bin/$@ -O2 -Wall

jipa2: jipa2.c
	mpicc $< -o bin/$@ -O2 -Wall

jipb: jipb.c
	mpicc $< -o bin/$@ -O2 -Wall

jis: jis.c
	gcc -O2 -Wall $< -o bin/$@

clean:
	rm bin/*
