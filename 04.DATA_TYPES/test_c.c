#include <stdio.h>
#include <stdbool.h>

bool greater(void)
{
	return (7 < 5);
}

int main(void)
{
	char *result = greater() ? "true" : "false";
	printf("this is it: %s\n", result);
	return (0);
}
