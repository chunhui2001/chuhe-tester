

main: httpclient.o httpclienthelper.o
	gcc -c -Wall -Werror -fpic httpclienthelper.c
	gcc -shared -o libhttpclienthelper.so httpclienthelper.o
	gcc  -L/home/keesh/workspace/chuhe-tester/httpclient \
		 -Wl,-rpath=/home/keesh/workspace/chuhe-tester/httpclient \
		 -Wall -o httpclient.o httpclient.c \
		 -ljson -lcurl -lhttpclienthelper
clean:
	rm -rf httpclient.o httpclienthelper.o libhttpclienthelper.so	
