#include <string.h>

#include "cmddb.h"
#include "util.h"
#include "command.h"

const struct cmddb_record commands[] = {
	{
		.name = "ls",
		.func = command_ls,
		.help =
"List  information  about  the FILEs (the current directory by default)."
"Sort entries alphabetically if none of -cftuvSUX nor --sort  is  speci‐"
"fied.\n"
	},
	{
		.name = "pwd",
		.func = command_pwd,
		.help =
"Print the full filename of the current working directory."
	},
	{
		.name = "cat",
		.func = command_cat,
		.help =
"Concatenate FILE(s), or standard input, to standard output."
	},
	{
		.name = "cd",
		.func = command_cd,
		.help =
"cd into directory."
	},
	{
		.name = "ps",
		.func = command_ps,
		.help =
"ps displays information about a selection of the active processes. If"
"you want a repetitive update of the selection and the displayed"
"information, use top(1) instead."
	},
	{
		.name = "help",
		.func = command_help,
		.help =
"print help message"
	}
};

int cmddb_get(const char *name, struct cmddb_record *ret)
{
	int len = strlen(name);
	int i;
	const struct cmddb_record *found = NULL;

	/* First look for an exact match */
	for (i = 0; i < ARRAY_LEN(commands); i++) {
		const struct cmddb_record *r = &commands[i];

		if (!strcasecmp(r->name, name)) {
			found = r;
			goto done;
		}
	}

	/* Allow partial matches if unambiguous */
	for (i = 0; i < ARRAY_LEN(commands); i++) {
		const struct cmddb_record *r = &commands[i];

		if (!strncasecmp(r->name, name, len)) {
			if (found)
				return -1;
			found = r;
		}
	}

	if (!found)
		return -1;

done:
	memcpy(ret, found, sizeof(*ret));
	return 0;
}

int cmddb_enum(cmddb_enum_func_t func, void *user_data)
{
	int i;

	for (i = 0; i < ARRAY_LEN(commands); i++)
		if (func(user_data, &commands[i]) < 0)
			return -1;

	return 0;
}
