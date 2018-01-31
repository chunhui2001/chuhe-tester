#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../httpclient/post/httpost.h"

int main(int argc, char* argv[]) {

	printf("test prodtcts\n");	

	char method[] = "post";
	char url[] = "http://127.0.0.1:8081/mans/products.json";
	
	httpost(method, url);

	return 0;	
}
