#include <stdio.h>

#include "../httpclienthelper.h"
#include "../jsonhelper.h"

void httpost(char* method, char* url) {
	
	printf("method: %s, url: %s\n", method, url);

	struct string _response_body;
    init_string(&_response_body);


}
