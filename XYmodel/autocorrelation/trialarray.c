#include <stdio.h>

void ArraySum(int t_max, int t) {
	int i,j; 
	int diff = t_max-t;
	int ans; 
	int array[t_max]; 

	for(i=0;i<t_max;i++) {
		array[i] = i; 
	}

	for(i=0;i<t_max;i++) {
		printf("%d ", array[i]); 
	}

	printf("\n"); 

	for(j=0;j<t_max-t;j++) {
		ans = array[j]*array[j+t]; 
	   	printf("%d * %d = %d\n", array[j],array[j+t],ans); 
	}	
}

int main() {
	ArraySum(10,2);
   	printf("\n"); 
	ArraySum(10,5); 	
return 0; 
}
