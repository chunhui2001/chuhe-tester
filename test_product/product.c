#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../httpclient/post/httpost.h"
#include "../httpclient/get/httget.h"

#include "../utils/colors.h"
#include "../config.h"



void fullurl(char* _url, char* endpoint) {
	sprintf(_url, "%s://%s:%d%s", _PACT, _HOST, _PORT, endpoint); 
}

void productlist(char* endpoint) {
	
	// http --verbose --verify no GET http://127.0.0.1:8081/mans/products.json 'Authorization: Bearer eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJ1c2VybmFtZSI6ImtlZXNoIiwiY2FuQ3JlYXRlIjpmYWxzZSwiY2FuVXBkYXRlIjpmYWxzZSwiY2FuRGVsZXRlIjpmYWxzZSwiaWF0IjoxNTE3Mjk3NTA3LCJpc3MiOiJWZXJ0LngiLCJzdWIiOiJXaWtpIEFQSSJ9.of9oMouGKDsotS0YyZYzl6xv_e7ZFT7MpxD1TFBdnUA'

    char requesturl[150];
    fullurl(requesturl, endpoint);
    char response[20000] = "\0";
    httget("get", requesturl, response);
	printf("%sResponse Body: %s%s%s\n", KBLU, KBLU, response, KWHT);

}


void productcreate(char* endpoint) {

    // http --verbose --verify no POST http://127.0.0.1:8081/mans/products.json 'Authorization: Bearer eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJ1c2VybmFtZSI6ImtlZXNoIiwiY2FuQ3JlYXRlIjpmYWxzZSwiY2FuVXBkYXRlIjpmYWxzZSwiY2FuRGVsZXRlIjpmYWxzZSwiaWF0IjoxNTE3Mjk3NTA3LCJpc3MiOiJWZXJ0LngiLCJzdWIiOiJXaWtpIEFQSSJ9.of9oMouGKDsotS0YyZYzl6xv_e7ZFT7MpxD1TFBdnUA'
    // curl -v -u keesh:keesh -X POST -H "Content-Type:application/x-www-form-urlencoded" -d '{"product_name": "product_name", "product_unit": "product_unit", "product_price": 1.35, "product_spec": "product_spec", "product_desc":"product_desc -4"}' http://localhost:8081/mans/products.json

    char requesturl[150];
	fullurl(requesturl, endpoint);
    char response[500] = "\0";
	httpost("post", requesturl, response);
	printf("%sResponse Body: %s%s%s\n", KBLU, KBLU, response, KWHT);

}

//void productdel(char* endpoint) {

// curl -v -u keesh:keesh -X DELETE http://localhost:8081/mans/products/25.json
//    char requesturl[150];
//    fullurl(requesturl, endpoint);
//    char response[20000] = "\0";
//    httpost("delete", requesturl, response);
//    printf("%sResponse Body: %s%s%s\n", KBLU, KBLU, response, KWHT);

//}

int main(int argc, char* argv[]) {
      
	char endpoint_productlist[] = "/mans/products.json";
	char endpoint_productcreate[] = "/mans/products.json";
    //char endpoint_productdelete[] = "/mans/products/{{product_id}}.json";

	productlist(endpoint_productlist);
	productcreate(endpoint_productcreate);
    //productdel(endpoint_productdelete);

	
	//httpost(method, url);


	return 0;	
}
