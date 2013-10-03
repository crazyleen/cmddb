#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>

#include "reader.h"
#include "input.h"
#include "cmddb.h"
#include "util.h"

#define MAX_READER_LINE		1024

static char repeat_buf[MAX_READER_LINE];
static volatile int want_exit = 0;

int prompt_abort(int flags)
{
	if (!flags)
		return 0;

	return input_module->prompt_abort("Do you really want to exit (y/n)?");
}

static int do_command(char *arg, int interactive)
{
	if (!strcasecmp(arg, "exit"))
		reader_exit();

	//printf("%s:%d: (%s) %d\n", __FUNCTION__, __LINE__, arg, interactive);

	const char *cmd_text;
	int len = strlen(arg);

	while (len && isspace(arg[len - 1]))
		len--;
	arg[len] = 0;

	cmd_text = get_arg(&arg);
	if (cmd_text) {

		struct cmddb_record cmd;

		/* Allow ^[# to stash a command in history without
		 * attempting to execute */
		if (*cmd_text == '#')
			return 0;

		if (!cmddb_get(cmd_text, &cmd))
			return cmd.func(&arg);

		fprintf(stderr, "Unknown command: %s\n", cmd_text);
		return -1;
	}

	return 0;
}

void reader_set_repeat(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	vsnprintf(repeat_buf, sizeof(repeat_buf), fmt, ap);
	va_end(ap);
}

void reader_exit(void)
{
	want_exit = 1;
}

void reader_loop(int abort_flag)
{
	do {
		want_exit = 0;

		for (;;) {
			char tmpbuf[MAX_READER_LINE] = { 0 };
			char *buf = tmpbuf;

			if (input_module->read_command(tmpbuf, sizeof(tmpbuf)))
				break;

			//set repeat
			if (*buf) {
				memcpy(repeat_buf, tmpbuf, sizeof(tmpbuf));
			} else
				memcpy(tmpbuf, repeat_buf, sizeof(tmpbuf));

			do_command(buf, 1);

			if (want_exit)
				break;
		}
	} while (prompt_abort(abort_flag));
}
