#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


int main()
{
	FILE *stream;
	char buf[1024];
	
	memset(buf,0x00, sizeof(buf));
	stream = popen("wc -l", "w");
	
	while(1)
	{
		memset(buf, 0x00, sizeof(buf));
		scanf("%s", buf);
		if (strcmp(buf, "k")  == 0)
			break;
		fprintf(stream, "%s\n", buf);
	}	
	pclose(stream);
	return 0;
	
}
