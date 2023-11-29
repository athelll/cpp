#include <stdio.h>

typedef struct fraction_t {
	int denum;
	int nurum;
} fraction;

fraction multiply( fraction *one, fraction *two )
{
	fraction new {one->denum * two->denum, one->nurum * two->nurum};
	return new;
}

int main()
{
	fraction one = {5, 7};
	fraction two = {7, 19};
	fraction result = multiply(&one, &two);

	printf("the multiplication of 5/7 and 7/19 is %i/%i\n", result.denum, result.nurum);
	return 0;
}
