#include <stdio.h>
#include <stdlib.h>
#include <ulfius.h>

#define _PORT 10001

int callback_index(const struct _u_request *request, struct _u_response *response, void *data) {
	ulfius_set_string_body_response(response, 200, "Index Page");
	return U_CALLBACK_CONTINUE;
}

int main (int argc, char *argv[]) {

	struct _u_instance instance;
	
	// Initialize instance with the port number
	if (ulfius_init_instance(&instance, _PORT, NULL, NULL) != U_OK) {
		fprintf(stderr, "ERROR ulfius_init_instance, abort\n");
	}

	// Endpoint list declaration
	ulfius_add_endpoint_by_val(&instance, "GET", "/index", NULL, 0, &callback_index, NULL);

	// Start restful webserver
	if (ulfius_start_framework(&instance) == U_OK) {
		printf ("ulfius restful webserver is running on port %d\n", _PORT);
		getchar();		// Wait for user to press <enter> on the console to quite the application
	} else {
		fprintf(stderr, "ERROR start ulfius webserver\n");
	}

	printf("Stoping ulfius webserver\n");

	ulfius_stop_framework(&instance);
	ulfius_clean_instance(&instance);

	printf("hello ulfius\n");
	exit(0);
}

