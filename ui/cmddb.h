#ifndef CMDDB_H_
#define CMDDB_H_

typedef int (*cmddb_func_t)(char **arg);

struct cmddb_record {
	const char		*name;
        cmddb_func_t            func;
	const char		*help;
};

/* Fetch a command record */
int cmddb_get(const char *name, struct cmddb_record *r);

/* Enumerate all command records.
 *
 * Returns 0, or -1 if an error occurs during enumeration.
 */
typedef int (*cmddb_enum_func_t)(void *user_data,
				 const struct cmddb_record *r);

int cmddb_enum(cmddb_enum_func_t func, void *user_data);

#endif
