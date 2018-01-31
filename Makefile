
libs 		= -ljson -lcurl
commons 	= -lhttpost -lhttpclienthelper -ljsonhelper
links 		= $(libs) $(commons)
dist 		= ./dist

product: httpost
	gcc -L$(dist) -Wl,-rpath=$(dist) -Wall \
		-o $(dist)/testproduct.o ./test_product/product.c \
		$(links)

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
	if ! [ -d $(dist) ]; then mkdir $(dist); fi

clean:
	rm -rf $(dist)


run: product
	echo "测试产品管理" >/dev/null && $(dist)/testproduct.o
