/*
 * command.c
 *
 *  Created on: Oct 3, 2013
 *      Author: heavey
 */
#include <stdio.h>
#include <stdlib.h>
#include "command.h"
#include "cmddb.h"
#include "util.h"

int command_ls(char **arg) {
	char cmdline[1024] = { 0 };
	snprintf(cmdline, sizeof(cmdline), "ls %s", *arg);
	return system(cmdline);
}

int command_pwd(char **arg)  {
	(void)arg;
	return system("pwd");
}

int command_cd(char **arg) {
	return chdir(*arg);
}

int command_cat(char **arg) {
	char cmdline[1024] = { 0 };
	snprintf(cmdline, sizeof(cmdline), "cat %s", *arg);
	return system(cmdline);
}

int command_ps(char **arg) {
	char cmdline[1024] = { 0 };
	snprintf(cmdline, sizeof(cmdline), "ps %s", *arg);
	return system(cmdline);
}


static int print_help(void *user_data, const struct cmddb_record *cmd) {
	printf("    %s\n        %s\n\n", cmd->name, cmd->help);
	return 0;
}

int command_help(char **arg) {
	const char *topic = get_arg(arg);

	if (topic) {
		struct cmddb_record cmd;

		if (!cmddb_get(topic, &cmd)) {
			printf("    %s\n        %s\n\n",
			       cmd.name, cmd.help);
			return 0;
		}
	} else {
		if (cmddb_enum(print_help, NULL)) {
			return -1;
		}
	}

	return 0;
}
