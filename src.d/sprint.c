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
};

static void set_data(char type, va_list args, struct data_st *data)
{
	switch (type)
	{
		case 'd':
		case 'x':
		{
			data->vt = VT_INT;

			if (data->wt == WT_LONG)
			{
				data->val.l = va_arg(args, long);
			}
			else
			{
				data->val.i = va_arg(args, int);
			}

			break;
		}

		case 'c':
		{
			data->vt = VT_CHAR;
			data->val.c = va_arg(args, char);
			break;
		}

		case 's':
		{
			data->vt = VT_STRING;
			data->val.s = va_arg(args, char *);
			break;
		}
	}
}

static size_t val_strlen(struct data_st *data)
{
	switch (data->vt)
	{
		case VT_INT:
			return (data->wt == WT_LONG) ?  20 : 10;

		case VT_CHAR:
			return 1;

		case VT_STRING:
			return strlen(data->val.s);
	}

	return 0;
}

int sprintf(char *str, const char *format, ...)
{
	va_list args;
	va_start(args, format);

	_Bool pholder = 0;

	struct data_st data = { 0 };
	char ignstr[3] = "%.";

	char *outbuf = NULL;

	for (const char *pos=format; *pos; pos++)
	{
		if (pholder)
		{
			switch (*pos)
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
					set_data(*pos, args, &data);
					break;
				}

				default:
				{
					data.vt = VT_STRING;
					ignstr[1] = *pos;
					data.val.s = ignstr;
					break;
				}
			}
		}
		else if (*pos == '%')
		{
			pholder = 1;
			continue;
		}
		else
		{
			data.vt = VT_CHAR;
			data.val.c = *pos;
		}

		size_t need = val_strlen(&data) + /* '\0' */1;
		assert(need >= 2);

		if (! outbuf)
		{
			outbuf = alloca(need);
			strcpy(outbuf, "");
		}

		char *term = outbuf + strlen(outbuf);
		char *sp = ua_getsp();
		size_t remaining = term - sp - /* '\0' */1;

		if (remaining < need)
		{
			alloca(need - remaining);
		}

		sp = ua_getsp();
		remaining = term - sp - /* '\0' */1;

		assert(remaining >= need);


	}

	va_end(args);

	return 0;
}

