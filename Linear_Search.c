#include <stdio.h>
void main()
{
	int n;
  printf("Enter value of n : ");
	scanf("%d", &n);
	int a[100], i, key, flag = 0, pos;
	int count;
	for (int i = 0; i < n; i++)
	{
		printf("Enter element for a[%d] : ", i);
		scanf("%d", &a[i]);
	}
	printf("Enter key element : ");
	scanf("%d", &key);
	for (int i = 0; i < 20; i++)
	{
		if (a[i] == key)
		{
			pos = i;
			flag = 1;
			break;
		}
		else
		{
			flag = 0;
		}
	}

	if (flag == 1)															
	{																	    
		printf("The key element %d is found at the position %d\n", key, pos); 
	}
	else
	{
		printf("The key element %d is not found in the array\n", key); 
	}
}