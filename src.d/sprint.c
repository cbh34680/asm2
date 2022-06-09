#include <stds.h>

enum value_type
{
	VT_NONE			= 0,
	VT_CHAR,
	VT_INT,
	VT_STRING,
	VT_FLOAT,
	VT_DOUBLE,
};

enum width_type
{
	WT_NONE			= 0,
	WT_LONG,
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
		char* s;
		long l;
		int i;
		char c;
	}
	val;

	enum value_type vt;
	enum width_type wt;
	enum number_format nf;
};

static void set_data(char type, __builtin_va_list ap, struct data_st *data)
{
	switch (type)
	{
		case 'x':
		{
			data->nf = NF_HEXA;

			// fall through
		}
		case 'd':
		{
			data->vt = VT_INT;

			if (data->wt == WT_LONG)
			{
				data->val.l = __builtin_va_arg(ap, long);
			}
			else
			{
				data->val.i = __builtin_va_arg(ap, int);
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
	}
}

static size_t val_strlen(struct data_st const *data)
{
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
						case NF_DECIMAL:	return 20;
						case NF_HEXA:		return 16;
					}

					break;
				}

				case WT_NONE: // 32bit
				{
					switch (data->nf)
					{
						case NF_DECIMAL:	return 10;
						case NF_HEXA:		return 8;
					}

					break;
				}
			}

		case VT_CHAR:
			return 1;

		case VT_STRING:
			return strlen(data->val.s);
	}

	return 0;
}

static void write_data(char *buff, const struct data_st *data)
{
	switch (data->vt)
	{
		case VT_CHAR:
			buff[0] = data->val.c;
			buff[1] = '\0';
			break;

		case VT_STRING:
			strcpy(buff, data->val.s);
			break;

		case VT_INT:
		{
			switch (data->wt)
			{
				case WT_LONG: // 64bit
				{
					switch (data->nf)
					{
						case NF_DECIMAL:	ua_ltoa(data->val.l, buff);	break;
						case NF_HEXA:		ua_pgx(buff, data->val.l);	break;
					}

					break;
				}

				case WT_NONE: // 32bit
				{
					switch (data->nf)
					{
						case NF_DECIMAL:	ua_itoa(data->val.i, buff);	break;
						case NF_HEXA:		ua_pwx(buff, data->val.i);	break;
					}

					break;
				}
			}

			break;
		}
	}
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
				case 'c':
				case 'x':
				case 's':
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

