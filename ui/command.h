/*
 * command.h
 *
 *  Created on: Oct 3, 2013
 *      Author: heavey
 */

#ifndef COMMAND_H_
#define COMMAND_H_

int command_ls(char **arg);
int command_pwd(char **arg);
int command_cd(char **arg);
int command_cat(char **arg);
int command_ps(char **arg);
int command_help(char **arg);
#endif /* COMMAND_H_ */
