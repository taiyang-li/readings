bool isPopSqueue()
{
	int top = -1;
	int i=0, j=0;
	int tmp = -1;

	while(j<N)
	{
		if(i < N)
			stack[++top] == push[i++];
		else
			tmp = j;

		while(top >= 0 && stack[top] == pop[j])
		{
			j++;
			top--;
		}

		if(tmp == j)
			return false;
	}
	return true;
}
#endif
#if 0
bool isPopSqueue(){

	int top=-1,i=0,j=0,temp=-1;
	while(j<N){
		if(i<N) stack[++top] = push[i++];
		else temp=j;

		while(  top>=0 && stack[top] == pop[j] ){
			j++; top--;
		}
		if( temp == j) return false;                
	}
	return true;
}

