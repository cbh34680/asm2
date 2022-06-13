#include <stds.h>

enum value_type
{
	VT_NONE			= 0,
	VT_CHAR,
	VT_INT,
	VT_STRING,
	VT_FLOAT,
	VT_DOUBLE,
	VT_ADDRESS,
};

enum width_type
{
	WT_NONE			= 0,
	WT_LONG,
};

enum sign_type
{
	ST_SIGNED		= 0,
	ST_UNSIGNED,
};

enum number_format
{
	NF_DECIMAL		= 0,
	NF_BINARY,
	NF_OCTAL,
	NF_HEXA,
};

struct data_st
{
	union
	{
		double d;
		float f;
		char *s;
		long l;
		unsigned long ul;
		int i;
		unsigned int ui;
		char c;
		void *p;
	}
	val;

	enum value_type vt;
	enum width_type wt;
	enum sign_type st;
	enum number_format nf;
};

static void set_data(char type, __builtin_va_list ap, struct data_st *data)
{
	switch (type)
	{
		case 'u':
		case 'x':
		{
			switch (type)
			{
				case 'u': data->st = ST_UNSIGNED;	break;
				case 'x': data->nf = NF_HEXA;		break;
			}

			// fall through
		}

		case 'd':
		{
			data->vt = VT_INT;

			switch (data->st)
			{
				case ST_SIGNED:
				{
					switch (data->wt)
					{
						case WT_LONG:
							data->val.l = __builtin_va_arg(ap, long);
							break;
						case WT_NONE:
							data->val.i = __builtin_va_arg(ap, int);
							break;
					}

					break;
				}

				case ST_UNSIGNED:
				{
					switch (data->wt)
					{
						case WT_LONG:
							data->val.ul = __builtin_va_arg(ap, unsigned long);
							break;
						case WT_NONE:
							data->val.ui = __builtin_va_arg(ap, unsigned int);
							break;
					}

					break;
				}
			}

			break;
		}

		case 'c':
		{
			data->vt = VT_CHAR;
			data->val.c = (char)__builtin_va_arg(ap, int);
			break;
		}

		case 's':
		{
			data->vt = VT_STRING;
			data->val.s = __builtin_va_arg(ap, char *);
			break;
		}

		case 'p':
		{
			data->vt = VT_ADDRESS;
			data->val.p = __builtin_va_arg(ap, void *);
			break;
		}
	}
}

static size_t val_strlen(struct data_st const *data)
{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wswitch"
	switch (data->vt)
	{
		case VT_INT:
			//
			// 1234567890123456789012
			// --------------------------------------
			// 2147483647
			// 4294967295
			// 9223372036854775807
			// 18446744073709551615
			//
			switch (data->wt)
			{
				case WT_LONG: // 64bit
				{
					switch (data->nf)
					{
						case NF_DECIMAL:	return 20 + 1;	// width(20) + sign('-')
						case NF_HEXA:		return 16;		// ffff ffff ffff ffff (-1)
					}

					break;
				}

				case WT_NONE: // 32bit
				{
					switch (data->nf)
					{
						case NF_DECIMAL:	return 10 + 1;	// width(10) + sign('-')
						case NF_HEXA:		return 8;		// ffff ffff (-1)
					}

					break;
				}
			}

		case VT_CHAR:
			return 1;

		case VT_STRING:
			return strlen(data->val.s);

		case VT_ADDRESS:
			return 2 + 16;	// "0x" + ffff ffff ffff ffff
	}
#pragma GCC diagnostic pop

	return 0;
}

static void write_data(char *buff, const struct data_st *data)
{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wswitch"
	switch (data->vt)
	{
		case VT_CHAR:
			buff[0] = data->val.c;
			buff[1] = '\0';
			break;

		case VT_STRING:
			strcpy(buff, data->val.s);
			break;

		case VT_ADDRESS:
		{
			if (data->val.p)
			{
				strcpy(buff, "0x");
				ua_pgx(&buff[2], (unsigned long)data->val.p);
			}
			else
			{
				strcpy(buff, "(nil)");
			}
			
			break;
		}

		case VT_INT:
		{
			switch (data->wt)
			{
				case WT_LONG: // 64bit
				{
					switch (data->nf)
					{
						case NF_DECIMAL:
						{
							switch (data->st)
							{
								case ST_SIGNED:		ua_ltoa(data->val.l, buff);		break;
								case ST_UNSIGNED:	ua_ultoa(data->val.ul, buff);	break;
							}

							break;
						}

						case NF_HEXA:
							ua_pgx(buff, data->val.l);
							break;
					}

					break;
				}

				case WT_NONE: // 32bit
				{
					switch (data->nf)
					{
						case NF_DECIMAL:
						{
							switch (data->st)
							{
								case ST_SIGNED:		ua_itoa(data->val.i, buff);		break;
								case ST_UNSIGNED:	ua_uitoa(data->val.ui, buff);	break;
							}

							break;
						}

						case NF_HEXA:
							ua_pwx(buff, data->val.i);
							break;
					}

					break;
				}
			}

			break;
		}
	}
#pragma GCC diagnostic pop
}

int vsprintf(char *str, const char *format, __builtin_va_list ap)
{
	_Bool pholder = 0;

	struct data_st data = { 0 };
	char ignstr[3] = "%.";

	char *opos = str;
	if (str)
	{
		*opos = '\0';
	}

	size_t vallen = 0;

	for (const char *ipos=format; *ipos; ipos++)
	{
		if (pholder)
		{
			switch (*ipos)
			{
				case 'l':
				{
					data.wt = WT_LONG;
					continue;
				}

				case '%':
				{
					data.vt = VT_CHAR;
					data.val.c = '%';
					break;
				}

				case 'd':
				case 'u':
				case 'c':
				case 'x':
				case 's':
				case 'p':
				{
					set_data(*ipos, ap, &data);
					break;
				}

				default:
				{
					data.vt = VT_STRING;
					ignstr[1] = *ipos;
					data.val.s = ignstr;
					break;
				}
			}
		}
		else if (*ipos == '%')
		{
			pholder = 1;
			continue;
		}
		else
		{
			data.vt = VT_CHAR;
			data.val.c = *ipos;
		}

		if (opos)
		{
			// write to buffer

			write_data(opos, &data);
			opos += strlen(opos);
		}
		else
		{
			vallen += val_strlen(&data);
		}

		// reset %..
		pholder = 0;

		// clear data
		memset(&data, '\0', sizeof(data));
	}

	if (str)
	{
		return strlen(str);
	}

	return vallen;
}


int sprintf(char *str, const char *format, ...)
{
	__builtin_va_list ap;
	__builtin_va_start(ap, format);

	const int len = vsprintf(str, format, ap);

	__builtin_va_end(ap);

	return len;
}

int printf(const char *format, ...)
{
	__builtin_va_list ap, ap2;

	__builtin_va_start(ap, format);
	__builtin_va_copy(ap2, ap);

	const int len = vsprintf(NULL, format, ap);
	__builtin_va_end(ap);

	char str[len + 1];
	//char *str = alloca(len + 1);

	const int r = vsprintf(str, format, ap2);
	__builtin_va_end(ap2);

	uc_prints(str);

	return r;
}

char* uc_aprintf(const char *format, ...)
{
	__builtin_va_list ap, ap2;

	__builtin_va_start(ap, format);
	__builtin_va_copy(ap2, ap);

	const int len = vsprintf(NULL, format, ap);
	__builtin_va_end(ap);

	char *str = malloc(len + 1);
	if (str)
		vsprintf(str, format, ap2);

	__builtin_va_end(ap2);

	return str;
}

