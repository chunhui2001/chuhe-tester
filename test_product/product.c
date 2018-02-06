#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

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
    free(response);

}


void productcreate(char* endpoint) {


    char method[] = "post";
    char requesturl[150];
	fullurl(requesturl, endpoint);
    char response[150] = "\0";


    const char docname[] = "/test_product/products.xml";

    json_object *jsonResultList = json_object_new_array();
    parseXmlDocToJson(docname, "product", jsonResultList);
    int arraylen = json_object_array_length(jsonResultList);


    json_object * jsonProduct;

    for (int i=0; i< arraylen; i++){

        char buf[5000];
        buf[0] = '\0';

        jsonProduct = json_object_array_get_idx(jsonResultList, i);



        json_object_object_foreach(jsonProduct, key, val) {

            sprintf(buf, "%s%s%s=%s", buf, strlen(buf) == 0 ? "" : "&", key,  json_object_get_string(val));

        }

        httpost(method, requesturl, buf, response);
        printf("%sResponse Body: %s%s%s\n\n", KBLU, KBLU, strlen(response) > 0 ? response : "NULL", KWHT);

        free(jsonProduct);

    }


    free(jsonResultList);

    // http --verbose --verify no POST http://127.0.0.1:8081/mans/products.json 'Authorization: Bearer eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJ1c2VybmFtZSI6ImtlZXNoIiwiY2FuQ3JlYXRlIjpmYWxzZSwiY2FuVXBkYXRlIjpmYWxzZSwiY2FuRGVsZXRlIjpmYWxzZSwiaWF0IjoxNTE3Mjk3NTA3LCJpc3MiOiJWZXJ0LngiLCJzdWIiOiJXaWtpIEFQSSJ9.of9oMouGKDsotS0YyZYzl6xv_e7ZFT7MpxD1TFBdnUA'
    // curl -v -u keesh:keesh -X POST -H "Content-Type:application/x-www-form-urlencoded" -d '{"product_name": "product_name", "product_unit": "product_unit", "product_price": 1.35, "product_spec": "product_spec", "product_desc":"product_desc -4"}' http://localhost:8081/mans/products.json


}

void productdel(char* endpoint, char* productid) {

    if (productid[strlen(productid) - 1] == '\n')
        productid[strlen(productid) - 1] = '\0';

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

    if (productid[strlen(productid) - 1] == '\n')
        productid[strlen(productid) - 1] = '\0';

    // curl -v -u keesh:keesh -X PUT http://localhost:8081/mans/products/115.json
    char method[] = "put";
    char requesturl[150];
    char realendpoint[150];
    sprintf(realendpoint, endpoint, productid);

    fullurl(requesturl, realendpoint);

    printf("requesturl: %s\n", requesturl);

    char response[150] = "\0";
    char postdata[] = "product_name=ROSSIGNOL 法国金鸡男士全能双板滑雪鞋ALLTRACK 90 26.5";
	httpost(method, requesturl, postdata, response);
	printf("%sResponse Body: %s%s%s\n\n", KBLU, KBLU, strlen(response) > 0 ? response : "NULL", KWHT);

}

int confirm_line ( void ) {

  int ch;
  struct termios oldt, newt;

  tcgetattr ( STDIN_FILENO, &oldt );
  newt = oldt;
  newt.c_lflag &= ~( ICANON | ECHO );
  tcsetattr ( STDIN_FILENO, TCSANOW, &newt );
  ch = getchar();
  tcsetattr ( STDIN_FILENO, TCSANOW, &oldt );

  return ch;
}

int main(int argc, char* argv[]) {

    char input[100];
    int pid;

    /* 获取所有产品列表 */
    puts("[TESTING] 获取所有产品列表");
    confirm_line();
	productlist("/mans/products.json");

    /* 创建一堆产品 */
    puts("[TESTING] 创建一堆产品");
    confirm_line();
	productcreate("/mans/products.json");

    /* 根据产品 ID 更新产品内容 */
    puts("[TESTING] 根据产品 ID 更新产品内容, 请输入产品 ID: (只限整数)");

    fgets(input, sizeof(input), stdin);

    if (sscanf(input, "%d", &pid) != 1) {
        printf("输入有误, 程序已推出!\n");
        return EXIT_FAILURE;
    }

    productupdate("/mans/products/%s.json", input);

    /* 根据产品 ID 删除一个产品 */
    puts("[TESTING] 根据产品 ID 删除一个产品, 请输入产品 ID: (只限整数)");

    fgets(input, sizeof(input), stdin);

    if (sscanf(input, "%d", &pid) != 1) {
        printf("输入有误, 程序已推出!\n");
        return EXIT_FAILURE;
    }

    productdel("/mans/products/%s.json", input);


	return EXIT_SUCCESS;

}
