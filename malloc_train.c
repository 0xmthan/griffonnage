// 19 Nov 2025 15:10
// 42 Piscine free time 🔔
// tutor atursun


#include <stdlib.h>
#include <stdio.h>


int main(int argc, char const *argv[])
{
	// statik bellek tahsisi
	int arr2[5] = {1, 2, 3, 4, 5};

	// dinamik bellek tahsisi
	int *arr = malloc(5 * sizeof(int));
	arr[0] = 1;
	arr[1] = 2;
	arr[2] = 3;
	arr[3] = 4;
	arr[4] = 5;

	free(arr);

	
	return 0;
}
