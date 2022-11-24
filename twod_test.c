#include <stdio.h>
#include <sys/syscall.h>
#include <linux/kernel.h>
#include <unistd.h>
#include <errno.h>

#define TWOD_COPY_SYSCALL 452

void check_equal(float lhs[2][5], float rhs[2][5], int size)
{
	int i;
	int j;
	for (i = 0; i < 2; i++)
	{
		for (j = 0; j < size; j++)
		{
			if (lhs[i][j] != rhs[i][j])
			{
				printf("Error : LHS[%d][%d] != RHS[%d][%d]\n",i,j,i,j);
				return;
			}
		}
	}
	printf("Message : Success LHS = RHS \n");
}

int main()
{
	float src_arr[2][5] = {{1,2,3,4,5},{6,7,8,9,10}};
	float dest_arr[2][5];

	long sys_call_status;

	sys_call_status = syscall(TWOD_COPY_SYSCALL, src_arr, dest_arr, 5);

	if (sys_call_status != EFAULT)
	{
		printf("Message : System Call 452 successfuly invoked \n");
		check_equal(src_arr, dest_arr, 5);
	}
	return 0;
}
