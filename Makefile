
libs 		= -ljson -lcurl
devlibs 	= -lhttget -lhttpost -lhttpclienthelper -ljsonhelper
links 		= $(devlibs) $(libs) 	# devlibs must be before libs
dist 		= ./dist

all: testproduct.o

testproduct.o: httget httpost
	gcc -L$(dist) -Wl,-rpath=$(dist) -Wall \
		-o $(dist)/testproduct.o ./test_product/product.c \
		$(links)

httget: prepare jsonhelper httpclienthelper
	gcc -c -Wall -Werror -fpic -o $(dist)/httget.o ./httpclient/get/httget.c
	gcc -shared -o $(dist)/libhttget.so $(dist)/httget.o

httpost: prepare jsonhelper httpclienthelper
	gcc -c -Wall -Werror -fpic -o $(dist)/httpost.o ./httpclient/post/httpost.c
	gcc -shared -o $(dist)/libhttpost.so $(dist)/httpost.o

httpclienthelper: prepare
	gcc -c -Wall -Werror -fpic -o $(dist)/httpclienthelper.o ./httpclient/httpclienthelper.c
	gcc -shared -o $(dist)/libhttpclienthelper.so $(dist)/httpclienthelper.o

jsonhelper: prepare
	gcc -c -Wall -Werror -fpic -o $(dist)/jsonhelper.o ./httpclient/jsonhelper.c
	gcc -shared -o $(dist)/libjsonhelper.so $(dist)/jsonhelper.o
	
prepare:
	@if ! [ -d $(dist) ]; then mkdir $(dist); fi

clean:
	rm -rf $(dist) *.o *.so 


test:
	@echo "[TESTING] 测试产品管理" && \
    $(dist)/testproduct.o


