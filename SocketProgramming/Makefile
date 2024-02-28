all: echoserver.o echoclient.o
	gcc echoserver.o -o echoserver
	gcc echoclient.o -o echoclient
echoserver.o: echoserver.c
	gcc -c echoserver.c -o echoserver.o
echoclient.o: echoclient.c
	gcc -c echoclient.c -o echoclient.o
clean:
	rm -f *.o echoserver echoclient

# all: argc.o
# 	gcc argc.o -o argc
# argc.o: argc.c
# 	gcc -c argc.c -o argc.o
# clean:
# 	rm -f *.o argc