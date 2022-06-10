#include <stds.h>

struct rdata_type
{
	void const *start;

	unsigned int size;
	unsigned int curr;
	unsigned int times;
};

static struct rdata_type _rdata;
static struct rdata_type *rdata;

void srand(unsigned int seed)
{
	if (! rdata)
	{
		unsigned long limit = BUS_ALIGNED(&etext) - BUS_SIZE;

		_rdata.start = (void *)BUS_ALIGNED(auxv_data.entry);
		_rdata.size  = ((BUS_ALIGNED(&etext) - (unsigned long)_rdata.start) / BUS_SIZE);

		rdata = &_rdata;
	}

	rdata->curr = seed % rdata->size;
	rdata->times = 0;
}

int rand(void)
{
	if (! rdata)
		srand(0U);

	if (rdata->curr >= rdata->size)
	{
		rdata->curr = 0;
		rdata->times++;

		if (rdata->times > 32)
			rdata->times = 0;

	}

	void *rpos = rdata->start + (rdata->curr * BUS_SIZE);
	unsigned long data = *(unsigned long *)rpos;
	data = data >> rdata->times;

	int r = data & 0x7fffffff;

	rdata->curr++;

	return r;
}

