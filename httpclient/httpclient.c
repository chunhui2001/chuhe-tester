#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <curl/curl.h>
#include <cjson/cJSON.h>
#include <json/json.h> 	 // sudo apt-get install libjson0 libjson0-dev

#include "httpclienthelper.h"

struct string {
  char *ptr;
  size_t len;
};

void init_string(struct string *s) {
  s->len = 0;
  s->ptr = malloc(s->len+1);
  if (s->ptr == NULL) {
    fprintf(stderr, "malloc() failed\n");
    exit(EXIT_FAILURE);
  }
  s->ptr[0] = '\0';
}

size_t curl_completed (void *ptr, size_t size, size_t nmemb, struct string *s)
{
  size_t new_len = s->len + size*nmemb;
  s->ptr = realloc(s->ptr, new_len+1);
  if (s->ptr == NULL) {
    fprintf(stderr, "realloc() failed\n");
    exit(EXIT_FAILURE);
  }
  memcpy(s->ptr+s->len, ptr, size*nmemb);
  s->ptr[new_len] = '\0';
  s->len = new_len;

  return size*nmemb;
}

/*Parsing the json object*/
void json_parse(json_object *jobj) {
	
	enum json_type type;
	json_object *returnObject;
	
	/*Passing through every array element*/
  	json_object_object_foreach(jobj, key, val) { 
	
		type = json_object_get_type(val);

		switch (type) {
        	case json_type_boolean: 
            	printf("%s: %s\n", key, json_object_get_boolean(val)? "true": "false");
            	break;
        	case json_type_double: 
            	printf("%s: %lf\n", key, json_object_get_double(val));
            	break;
        	case json_type_int: 
            	printf("%s: %d\n", key, json_object_get_int(val));
            	break;
        	case json_type_string: 
            	printf("%s: %s\n", key, json_object_get_string(val));
            	break;
			case json_type_array: 
            	printf("%s: %s\n", key, "Array Value");
                // json_parse_array(jobj, key);
                break;
        	case json_type_object:
				if (json_object_object_get_ex(jobj, key, &returnObject)) {
					if ( !strcmp(json_object_to_json_string(returnObject), "{ }")) {
            			printf("%s: %s\n", key, "{ }");
					} else {
						json_parse(returnObject);
					}	
				} else {
					printf("could not extrct json object value");
				}
            	break;
        	default:
            	printf("not matchs\n");
            	break;
    	}   
	}
}



// README.md 
// https://curl.haxx.se/libcurl/c/example.html
// https://curl.haxx.se/libcurl/c/curl_easy_getinfo.html
// https://linuxprograms.wordpress.com/2010/08/19/json_parser_json-c/
// https://linuxprograms.wordpress.com/category/json-c/
// https://www.cprogramming.com/tutorial/shared-libraries-linux-gcc.html

int main (int argc, char *argv[]) {

    foo();
	
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

	printf("\n");

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
