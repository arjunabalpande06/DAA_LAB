#include<stdio.h>
int max(int a, int b){
	return (a>b)? a:b;
}

int knapsack(int val[], int wt[], int n, int W){
	int dp[n+1][W+1];

	for(int i = 0; i<=n; i++){
		for(int w = 0; w <= W; w++){
			if(i == 0 || w == 0)
				dp[i][w] = 0;
			else if(wt[i-1] <=w)
				dp[i][w] = max(val[i-1] + dp[i-1][w-wt[i-1]], dp[i-1][w]);
			else
				dp[i][w] = dp[i-1] [w];
		}
	}
	return dp[n][W];
}

int main()
{
	int n, W;
	scanf("%d",&n);

	int val[n], wt[n];
	for(int i = 0; i< n; i++){
		scanf("%d",&val[i]);
	}
	for(int i = 0; i < n; i++)
		scanf("%d",&wt[i]);
	scanf("%d",&W);
	int result = knapsack(val, wt, n, W);
	printf("%d\n",result);
	return 0;
}
