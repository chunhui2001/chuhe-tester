#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <curl/curl.h>

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

size_t writefunc(void *ptr, size_t size, size_t nmemb, struct string *s)
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



// README.md 
// https://curl.haxx.se/libcurl/c/example.html
// https://curl.haxx.se/libcurl/c/curl_easy_getinfo.html

int main (int argc, char *argv[]) {
	
	CURL *curl;
	char url[] = "http://127.0.0.1:8081/index.json";
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
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &_response_body);
	//curl_easy_setopt(curl, CURLOPT_POST, url);

	_res_code = curl_easy_perform(curl);

	if (_res_code != CURLE_OK) {
		fprintf(stderr, "curl_easy_perform() failed: \n%s\n", curl_easy_strerror(_res_code));
		exit (1);
	} 

	int _stat_code = 0;
	double _content_length;
	double _connect_time = 0;
	double _namelookup_time = 0;
	char* _content_type;

	_res_code = curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &_stat_code);
	_res_code = curl_easy_getinfo(curl, CURLINFO_CONTENT_LENGTH_DOWNLOAD, &_content_length);
	_res_code = curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &_content_type);
	_res_code = curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &_connect_time);
	_res_code = curl_easy_getinfo(curl, CURLINFO_NAMELOOKUP_TIME, &_namelookup_time);
	
	fprintf(stdout, "Response Code: %d\n", _stat_code);	
	fprintf(stdout, "Content Length: %.0f\n", _content_length);
	fprintf(stdout, "Content Type: %s\n", _content_type);
	fprintf(stdout, "Connect Time: %.8f\n", _connect_time);
	fprintf(stdout, "Namelookup Time: %.8f\n", _namelookup_time);
	fprintf(stdout, "Response Body: %s\n", _response_body.ptr);
	
	free(_response_body.ptr);

	curl_easy_cleanup(curl);
	
	exit(0);
}
