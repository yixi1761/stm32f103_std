#include <stdio.h>
#define YES

int main()
{
	#ifdef YES
		printf("hello ,yes\n");
	#endif
	printf("no\n");
	return 0;
}
