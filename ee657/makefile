all: jipa1 jipa2 jipb jis

jipa1: jipa1.c
	mpicc $< -o bin/$@ -Wall

jipa2: jipa2.c
	mpicc $< -o bin/$@ -Wall

jipb: jipb.c
	mpicc $< -o bin/$@ -Wall

jis: jis.c
	gcc -Wall $< -o bin/$@

clean:
	rm bin/*
