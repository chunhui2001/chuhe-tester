#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../httpclient/post/httpost.h"
#include "../httpclient/get/httpget.h"

#include "../utils/colors.h"
#include "../config.h"


void productList(char* endpoint) {
	
	// http --verbose --verify no GET http://127.0.0.1:8081/mans/products.json 'Authorization: Bearer eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJ1c2VybmFtZSI6ImtlZXNoIiwiY2FuQ3JlYXRlIjpmYWxzZSwiY2FuVXBkYXRlIjpmYWxzZSwiY2FuRGVsZXRlIjpmYWxzZSwiaWF0IjoxNTE3Mjk3NTA3LCJpc3MiOiJWZXJ0LngiLCJzdWIiOiJXaWtpIEFQSSJ9.of9oMouGKDsotS0YyZYzl6xv_e7ZFT7MpxD1TFBdnUA'
     
	char url[150];
	sprintf(url, "%s://%s:%d%s", _PACT, _HOST, _PORT, endpoint); 

	char result[2000];
	result[0] = '\0';
	
	httpget("get", url, result);

	printf("%sResponse Body: %s%s\n", KBLU, KBLU, result);

}

int main(int argc, char* argv[]) {
      
	char endpoint[] = "/mans/products.json";

	productList(endpoint);

	
	//httpost(method, url);


	return 0;	
}
