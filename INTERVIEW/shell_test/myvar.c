#include <stdio.h>
#include <stdlib.h>
int main()
{
	char *myenvvar = getenv("EDITOR");
	printf ("the editor environment var is set to %s\n", myenvvar);
	return 0;
}
