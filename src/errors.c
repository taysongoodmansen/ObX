#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

int Error_count = 0;
int Warning_count = 0;
int Notice_count = 0;

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

void return_warning(const char *format, ...) {
	Warning_count++;

	char warning[512];
	va_list args;
	va_start(args, format);
	vsnprintf(warning, sizeof(warning), format, args);
	va_end(args);

	printf("⚠ObX Warning: %s⚠\n", warning);

	char input[16];
	printf("Would you like to continue (y/N)\nContinuing may have unexpected behavior >> ");
	scanf("%15s", input);
	printf("\n");

	if (input[0] != 'y' && input[0] != 'Y') {
		exit(1);
	}

}

void return_notice(const char *format, ...) {
	Notice_count++;

	char notice[512];
	va_list args;
	va_start(args, format);
	vsnprintf(notice, sizeof(notice), format, args);
	va_end(args);

	printf("⚠ObX Notice: %s⚠\n", notice);
}
