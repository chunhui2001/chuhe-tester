#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../httpclient/post/httpost.h"
#include "../httpclient/get/httget.h"

#include "../utils/colors.h"
#include "../config.h"

#include "../nubecula/xml/xmlutil.h"



void fullurl(char* _url, char* endpoint) {
	sprintf(_url, "%s://%s:%d%s", _PACT, _HOST, _PORT, endpoint); 
}

void productlist(char* endpoint) {
	
	// http --verbose --verify no GET http://127.0.0.1:8081/mans/products.json 'Authorization: Bearer eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJ1c2VybmFtZSI6ImtlZXNoIiwiY2FuQ3JlYXRlIjpmYWxzZSwiY2FuVXBkYXRlIjpmYWxzZSwiY2FuRGVsZXRlIjpmYWxzZSwiaWF0IjoxNTE3Mjk3NTA3LCJpc3MiOiJWZXJ0LngiLCJzdWIiOiJXaWtpIEFQSSJ9.of9oMouGKDsotS0YyZYzl6xv_e7ZFT7MpxD1TFBdnUA'

    char requesturl[150];
    fullurl(requesturl, endpoint);
    char *response = (char *) malloc(sizeof(char *) * 5000);
    httget("get", requesturl, response);
	printf("%sResponse Body: %s%s%s\n", KBLU, KBLU, response, KWHT);

}


void productcreate(char* endpoint) {


    const char docname[] = "/test_product/products.xml";

    json_object *jsonResultList = json_object_new_array();

    parseXmlDocToJson(docname, "product", jsonResultList);

    printf (" %s\n",json_object_to_json_string(jsonResultList));

    free(jsonResultList);



    // http --verbose --verify no POST http://127.0.0.1:8081/mans/products.json 'Authorization: Bearer eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJ1c2VybmFtZSI6ImtlZXNoIiwiY2FuQ3JlYXRlIjpmYWxzZSwiY2FuVXBkYXRlIjpmYWxzZSwiY2FuRGVsZXRlIjpmYWxzZSwiaWF0IjoxNTE3Mjk3NTA3LCJpc3MiOiJWZXJ0LngiLCJzdWIiOiJXaWtpIEFQSSJ9.of9oMouGKDsotS0YyZYzl6xv_e7ZFT7MpxD1TFBdnUA'
    // curl -v -u keesh:keesh -X POST -H "Content-Type:application/x-www-form-urlencoded" -d '{"product_name": "product_name", "product_unit": "product_unit", "product_price": 1.35, "product_spec": "product_spec", "product_desc":"product_desc -4"}' http://localhost:8081/mans/products.json

    char method[] = "post";
    char requesturl[150];
	fullurl(requesturl, endpoint);
    char response[150] = "\0";
    char postdata[] = "product_name=6667778 1&product_unit=台&product_price=1.35&product_spec=product_spec 3&product_desc=product_desc 4";
	httpost(method, requesturl, postdata, response);
	printf("%sResponse Body: %s%s%s\n\n", KBLU, KBLU, strlen(response) > 0 ? response : "NULL", KWHT);

}

void productdel(char* endpoint, char* productid) {

    // curl -v -u keesh:keesh -X DELETE http://localhost:8081/mans/products/25.json

    char method[] = "delete";
    char requesturl[150];
    char realendpoint[150];
    sprintf(realendpoint, endpoint, productid);

    fullurl(requesturl, realendpoint);
    char response[150] = "\0";
    httpost(method, requesturl, NULL, response);
    printf("%sResponse Body: %s%s%s\n\n", KBLU, KBLU, response, KWHT);

}


void productupdate(char* endpoint, char* productid) {

    // curl -v -u keesh:keesh -X PUT http://localhost:8081/mans/products/115.json
    char method[] = "put";
    char requesturl[150];
    char realendpoint[150];
    sprintf(realendpoint, endpoint, productid);

    fullurl(requesturl, realendpoint);
    char response[150] = "\0";
    char postdata[] = "product_name=6667778Updated 1&product_unit=台&product_price=666.35&product_spec=特色产品&product_desc=product_desc";
	httpost(method, requesturl, postdata, response);
	printf("%sResponse Body: %s%s%s\n\n", KBLU, KBLU, strlen(response) > 0 ? response : "NULL", KWHT);

}

int main(int argc, char* argv[]) {

    /* 获取所有产品列表 */
	productlist("/mans/products.json");

    /* 创建一个产品 */
	productcreate("/mans/products.json");

    /* 根据产品编号删除 */
    //productdel("/mans/products/%s.json", "100");

    /* 更新产品内容 */
    //productupdate("/mans/products/%s.json", "115");


	return EXIT_SUCCESS;

}
