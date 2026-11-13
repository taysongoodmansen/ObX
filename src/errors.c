#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

int Error_count = 0;

void return_error(const char *format, ...) {
	Error_count++;

	char error[512];
	va_list args;
	va_start(args, format);
	vsnprintf(error, sizeof(error), format, args);
	va_end(args);

	printf("⚠ObX Error: %s⚠\n", error);

	char input[16];
	printf("Would you like to continue (y/N)\nContinuing may have unexpected behavior >> ");
	scanf("%15s", input);
	printf("\n");

	if (input[0] != 'y' && input[0] != 'Y') {
		exit(1);
	}

}
