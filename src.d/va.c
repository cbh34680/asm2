#include <stds.h>

void va_start_(va_list ap, void *last)
{
	void *bp;

	ua_bt_caller(1, &bp);

	ap->gp_offset = 0UL;
	ap->fp_offset = 0UL;

	ap->overflow_arg_area	= bp + 0x10;
	ap->reg_save_area		= bp - 0xa8;
	ap->_fp_save_area		= bp - 0x80;

	// rsi, rdx, rcx, r8, r9
	ap->_end_reg_save_area	= ap->reg_save_area + ( sizeof(void *) * 5 );

	// xmm0 - 7
	ap->_end_fp_save_area	= ap->_fp_save_area + ( sizeof(__int128_t) * 8 );
}

void va_end(va_list ap)
{
	ap->gp_offset = 0UL;
	ap->fp_offset = 0UL;

	ap->overflow_arg_area	= NULL;
	ap->reg_save_area		= NULL;

	ap->_fp_save_area		= NULL;

	ap->_end_reg_save_area	= NULL;
	ap->_end_fp_save_area	= NULL;
}

double va_arg_f(va_list ap)
{
	double rv;

	if (ap->_fp_save_area != ap->_end_fp_save_area)
	{
		rv = *(double *)ap->_fp_save_area;
		ap->_fp_save_area += sizeof(__uint128_t);
	}
	else
	{
		rv = *(double *)ap->overflow_arg_area;
		ap->overflow_arg_area += sizeof(uint64_t);
	}

	return rv;
}

unsigned long va_arg_i(va_list ap)
{
	unsigned long rv;

	if (ap->reg_save_area != ap->_end_reg_save_area)
	{
		rv = *(unsigned long *)ap->reg_save_area;
		ap->reg_save_area += sizeof(uint64_t);
	}
	else
	{
		rv = *(unsigned long *)ap->overflow_arg_area;
		ap->overflow_arg_area += sizeof(uint64_t);
	}

	return rv;
}

// EOF
