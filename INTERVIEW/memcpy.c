#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void memcpy_system(void *dst, void *src, size_t count)
{
	memcpy (dst, src , count);
}

void *memcpy_no_handle_overlap(void *dst, void *src, size_t count)
{
	if(!dst || !src)
		return NULL;
	char *d = dst;
	char *s = src;
	while(count --)
	{
		*d++ = *s++;
	}
	return dst;
}

void *memcpy_handle_overlap(void *dst, void *src, size_t count)
{
	if(!dst || !src )
		return NULL;
	char *d = dst;
	char *s = src;
	if(d <= s || d >= s+count)
	{
		while(count--)
			*d++ = *s++;
	}
	else
	{
		while(count)
		{
			*(d+count-1) = *(s + count - 1);
			count --;
		}
	}
	return dst;
}


int main()
{
//	char a[16] = "aabbcc";
//	memcpy_system(a+2, a, 4);
//	printf("%s\n", a);

//	char a[16] = "aabbcc";
//	memcpy_no_handle_overlap(a+2, a, 4);
//	printf("%s\n", a);

	char a[16] = "aabbcc";
	memcpy_handle_overlap(a+2, a, 4);
	printf("%s\n", a);

}
