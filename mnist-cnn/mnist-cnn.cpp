#include <unistd.h>
#include <stdlib.h>
#include <assert.h>

#include "../config.h"
#include "kann_data.h"
#include "kann.h"

int main(int argc, char *argv[])
{
	kann_t *ann;
	kann_data_t *x;
	int seed = 131;
	{
    // Stopwatch s("VIP_Bench Runtime");
	kad_trap_fe();
	kann_srand(seed);
	
	ann = kann_load("mnist-cnn.kan");
	x = kann_data_read("mnist-test-x.knd");
	assert(x->n_col == 28 * 28);

   // applying knn only 
	int i, j, n_out;
	kann_switch(ann, 0);
	n_out = kann_dim_out(ann);
	assert(n_out == 10);
	for (i = 0; i < x->n_row; ++i) {
		VIP_ENCFLOAT *y;
		y = kann_apply1(ann, x->x[i]);
		if (x->rname) printf("%s\t", x->rname[i]);
		for (j = 0; j < n_out; ++j) {
			if (j) putchar('\t');
			printf("%.3g", VIP_DEC(y[j]) + 1.0f - 1.0f);
		}
		putchar('\n');
	}

	kann_data_free(x);
	kann_delete(ann);
	}
	return 0;
}
