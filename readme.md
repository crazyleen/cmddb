
# cmddb example

a method to write command line based commands

## compile

	make

## usage

	./cmddb

## detail description

cli commands implement

* log

	heavey@heavey-ThinkPad-T420:~/workspace/cmddb$ ./cmddb 
	input-module (Oct  3 2013-08:55:00)- an example shows you how to use input module with readline
	Copyright (C) 2012-2013 ruisheng <ruishengleen@gmail.com>
	This is free software; see the source for copying conditions.  There is NO
	warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

	cmddb$help
	do_command:30: (help) 1
		ls
		    List  information  about  the FILEs (the current directory by default).Sort entries alphabetically if none of -cftuvSUX nor --sort  is  speci©\fied.


		pwd
		    Print the full filename of the current working directory.

		cat
		    Concatenate FILE(s), or standard input, to standard output.

		cd
		    cd into directory.

		ps
		    ps displays information about a selection of the active processes. Ifyou want a repetitive update of the selection and the displayedinformation, use top(1) instead.

		help
		    print help message

	cmddb$pwd
	do_command:30: (pwd) 1
	/home/heavey/workspace/cmddb
	cmddb$cd ..
	do_command:30: (cd ..) 1
	cmddb$pwd
	do_command:30: (pwd) 1
	/home/heavey/workspace
	cmddb$

