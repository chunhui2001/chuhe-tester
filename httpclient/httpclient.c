#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <curl/curl.h>
#include <cjson/cJSON.h>
#include <json/json.h> 	 // sudo apt-get install libjson0 libjson0-dev

#include "httpclienthelper.h"
#include "jsonhelper.h"

// README.md 
// https://curl.haxx.se/libcurl/c/example.html
// https://curl.haxx.se/libcurl/c/curl_easy_getinfo.html
// https://linuxprograms.wordpress.com/2010/08/19/json_parser_json-c/
// https://linuxprograms.wordpress.com/category/json-c/
// https://www.cprogramming.com/tutorial/shared-libraries-linux-gcc.html

int main (int argc, char *argv[]) {
	
	CURL *curl;
	//char url[] = "http://127.0.0.1:8081/index.json";
	//char url[] = "http://127.0.0.1:8081/mans/products.json";
	char url[] = "http://127.0.0.1:8081/access_token.json";
	//char url[] = "http://www.baidu.com";
	//char url[] = "http://www.360bid.cn";
	struct string _response_body;
	CURLcode _res_code;

	curl = curl_easy_init();

	if (!curl) {
		fprintf(stderr, "Could not init curl client");
		exit(1);
	}

    init_string(&_response_body);
	
	curl_easy_setopt(curl, CURLOPT_URL, url);
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_setopt(curl, CURLOPT_NOBODY, 0);
	curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
  	//curl_easy_setopt(curl, CURLOPT_USERPWD, "keesh:keesh");
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_completed);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &_response_body);
	curl_easy_setopt(curl, CURLOPT_POST, url);
   	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "username=keesh&password=keesh");

	_res_code = curl_easy_perform(curl);

	if (_res_code != CURLE_OK) {
		fprintf(stderr, "curl_easy_perform() failed: \n%s\n", curl_easy_strerror(_res_code));
		exit (1);
	} 

	char *_request_url;
	int _stat_code = 0;
	double _content_length;
	double _connect_time = 0;
	double _namelookup_time = 0;
	char* _content_type;

	_res_code = curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &_request_url);
	_res_code = curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &_stat_code);
	_res_code = curl_easy_getinfo(curl, CURLINFO_CONTENT_LENGTH_DOWNLOAD, &_content_length);
	_res_code = curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &_content_type);
	_res_code = curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &_connect_time);
	_res_code = curl_easy_getinfo(curl, CURLINFO_NAMELOOKUP_TIME, &_namelookup_time);

	fprintf(stdout, "Request Uri: %s\n", _request_url);	
	fprintf(stdout, "Response Code: %d\n", _stat_code);	
	fprintf(stdout, "Content Length: %.0f\n", _content_length);
	fprintf(stdout, "Content Type: %s\n", _content_type == NULL ? "text/plain" : _content_type);
	fprintf(stdout, "Connect Time: %.8f\n", _connect_time);
	fprintf(stdout, "Namelookup Time: %.8f\n", _namelookup_time);

	if (_stat_code >=200 && _stat_code <=300) {

		fprintf(stdout, "Request Successful: [%d]\n", _stat_code);	

		if (!strcmp(_response_body.ptr, "")) {
        	printf("请求成功，但是服务器未返回任何内容");
    	} else {
            fprintf(stdout, "Response Body: %s\n", _response_body.ptr);
        
            json_object *_response_json_object = json_tokener_parse(_response_body.ptr);
            free(_response_body.ptr);
        
            if (_response_json_object) {
                json_parse(_response_json_object);
                fprintf(stdout, "Json Object To String: %s\n", json_object_to_json_string(_response_json_object));
            }
		}
	} else {
		fprintf(stderr, "Request Failed: [%d]\n", _stat_code);	
	}

	curl_easy_cleanup(curl);
	
	exit(0);

}
