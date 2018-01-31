
main: httpclienthelper jsonhelper
	gcc  -L/home/keesh/workspace/chuhe-tester/httpclient \
		 -Wl,-rpath=/home/keesh/workspace/chuhe-tester/httpclient \
		 -Wall -o httpclient.o httpclient.c \
		 -ljson -lcurl -lhttpclienthelper -ljsonhelper

httpclienthelper: httpclienthelper.o
	gcc -c -Wall -Werror -fpic httpclienthelper.c
	gcc -shared -o libhttpclienthelper.so httpclienthelper.o

jsonhelper: jsonhelper.o
	gcc -c -Wall -Werror -fpic jsonhelper.c
	gcc -shared -o libjsonhelper.so jsonhelper.o

testGetAccessToken: main
	./httpclient.o

run: testGetAccessToken
	echo "test all case"

clean:
	rm -rf httpclient.o httpclienthelper.o libhttpclienthelper.so \
		   jsonhelper.o libjsonhelper.so
