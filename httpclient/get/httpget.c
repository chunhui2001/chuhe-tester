#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <curl/curl.h>
#include <cjson/cJSON.h>
#include <json/json.h> 	 			// sudo apt-get install libjson0 libjson0-dev

#include "../../utils/colors.h"

#include "../httpclienthelper.h" 	// curl_completed, struct string
#include "../jsonhelper.h" 		 	// json_parse	

void httpget(char* method, char* url, char *rtnresult) {

	struct string _response_body;
	CURL *curl;
	CURLcode _curl_result_code;

	int _status_code; 				// Http 请求返回状态码
	double _content_length;			// 返回内容长度
	double _connect_time = 0;		// 请求耗时
	double _namelookup_time = 0;	// 域名解析时间
	char* _content_type;			// 返回内容类型

    init_string(&_response_body);
	curl = curl_easy_init();
	
	if (!curl) {
		fprintf(stderr, "Could not init curl client\n");
		exit (EXIT_FAILURE);
	}

	// https://curl.haxx.se/libcurl/c/curl_easy_setopt.html
	// set: url, followlocation, nobody, httpauth, writefunction, writedata, post, postfields
	curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);			// debug 1, otherwise 0
	curl_easy_setopt(curl, CURLOPT_URL, url);
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_setopt(curl, CURLOPT_NOBODY, 0);
	curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
  	curl_easy_setopt(curl, CURLOPT_USERPWD, "keesh:keesh");
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_completed);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &_response_body);

	_curl_result_code = curl_easy_perform(curl);

	if (_curl_result_code != CURLE_OK) {
		fprintf(stderr, "curl_easy_perform() failure: %s\n", curl_easy_strerror(_curl_result_code));
		exit(EXIT_FAILURE);
	}

	// https://curl.haxx.se/libcurl/c/curl_easy_getinfo.html
	// _curl_result_code = curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &_request_url);
	_curl_result_code = curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &_status_code);
	_curl_result_code = curl_easy_getinfo(curl, CURLINFO_CONTENT_LENGTH_DOWNLOAD, &_content_length);
	_curl_result_code = curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &_content_type);
	_curl_result_code = curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &_connect_time);
	_curl_result_code = curl_easy_getinfo(curl, CURLINFO_NAMELOOKUP_TIME, &_namelookup_time);

	
	fprintf(stdout, "%sRequest: %s[%s] %s\n", KMAG, KGRN, method, url);	
	fprintf(stdout, "%sContent Type: %s%s\n", KMAG, KGRN, _content_type == NULL ? "text/plain" : _content_type);
	fprintf(stdout, "%sContent Length: %s%.0f\n", KMAG, KGRN, _content_length);
	fprintf(stdout, "%sStatus Code: %s%d\n", KMAG, KGRN, _status_code);	
	fprintf(stdout, "%sConnect Time: %s%.8f\n", KMAG, KGRN, _connect_time);
	fprintf(stdout, "%sNamelookup Time: %s%.8f\n", KMAG, KGRN, _namelookup_time);

	if (_status_code < 200 || _status_code > 300) {
		fprintf(stderr, "Request Failure: [%d]\n", _status_code);
	} else {

		if (!strcmp(_response_body.ptr, "")) {
        	fprintf(stdout, "请求成功，但是服务器未返回任何内容");
    	} else {

    		int source_size = strlen(_response_body.ptr) + 1;  
    		memcpy(rtnresult, _response_body.ptr, source_size);

    		//result = _response_body.ptr;

    		//malloc(s->len+1);

			/* if (_content_type == NULL) {
				fprintf(stdout, "Response Body: %s\n", _response_body.ptr);
			} else if (strpbrk("json", _content_type)) {
            	fprintf(stdout, "Response Body: %s\n", _response_body.ptr);

            	json_result = json_tokener_parse(_response_body.ptr);

				json_object *_response_json_object = json_tokener_parse(_response_body.ptr);
				if (_response_json_object) {
					json_parse(_response_json_object);
					fprintf(stdout, "Json Object To String: %s\n", json_object_to_json_string(_response_json_object));
				}
			} else {
				fprintf(stdout, "[MESSAGE] Not match content-type as *\/json -> [%s]\n", _content_type);
				printf("%s\n", strpbrk("json", _content_type));
			} */

		}

	}


	free(_response_body.ptr);	

}

