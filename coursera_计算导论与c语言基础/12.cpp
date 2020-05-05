#include <stdio.h>

int main()
{
	int n=0;
	int a[100];
	
	scanf("%d", &n);
	for (int i=0; i<n; i++)
	{
		scanf("%d", &a[i]);
	}
	
	int count1 = 0;
	int count2 = 0;
	int count3 = 0;
	int count4 = 0;

	for (int i = 0; i < n; i++)
	{
		if (a[i] >= 60)
		{
			count1++;
		}
		else if (a[i] >= 36)
		{
			count2++;
		}
		else if (a[i] >= 19)
		{
			count3++;
		}
		else if (a[i] >= 1) 
		{
			count4++;
		}
	}
	
	int total = count1 + count2 + count3 + count4;
	printf("1-18: %5.2f%%\n", 100 * float(count4)/total);
	printf("19-35: %5.2f%%\n", 100 * float(count3)/total);
	printf("36-60: %5.2f%%\n", 100 * float(count2)/total);
	printf("60-: %5.2f%%\n", 100 * float(count1)/total);

	return 0;
}
