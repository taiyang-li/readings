#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char *mystrcpy(char *dst, char *src)
{
	if(!dst || !src)
		return NULL;
	char *d = dst;
	while((*d++ = *src++) != '\0' );
	return dst;
}

char *mystrncpy(char *dst, char *src, size_t count)
{
	if(!dst || !src)
		return NULL;
	char *d = dst;
	char *s = src;
	int i = 0;
	while(i < count && (*d++ = *s++)!= '\0')
		i++;
	*d = '\0';
	return dst;
}

void *mystrcat(char *dst, char *src, size_t count)
{
	if(!dst || !src)
		return NULL;
	char *d = dst;
	char *s = src;
	int i = 0;
	while(*d )
		d ++;
	while((*d++ = *s++) != '\0')
		if(count-- < 0)
			break;
	*d = '\0';
	return dst;
}


int main()
{
	char a[16] = "aabbcc";
	char b[16];
	memset(b, 0 ,sizeof(b));
	mystrncpy(b, a, 6);
//	strcpy(b, a);
//	strncpy(b, a, sizeof(b));
	printf("%s\n",b);
}
