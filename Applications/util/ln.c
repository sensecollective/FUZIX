/*
 * Copyright (c) 1993 by David I. Bell
 * Permission is granted to use, distribute, or modify this source,
 * provided that this copyright notice remains intact.
 */

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#ifndef BOOL
#define BOOL  int
#define TRUE  1
#define FALSE 0
#endif

#define PATHLEN 512


/*
 * Return TRUE if name is a directory.
 * Return FALSE otherwise or if the file does not exist.
 */

BOOL isadir(char *name)
{
    struct stat statbuf;

    if (stat(name, &statbuf) < 0)
	return FALSE;

    return S_ISDIR(statbuf.st_mode);
}


/*
 * Build a path name from the specified directory name and file name.
 * If the directory name is NULL, then the original filename is returned.
 * The built path is in a static area, and is overwritten for each call.
 */

char *buildname(char *dirname, char *filename)
{
    char *cp;
    static char buf[PATHLEN];

    if ((dirname == NULL) || (*dirname == '\0'))
	return filename;

    cp = strrchr(filename, '/');
    if (cp)
	filename = cp + 1;

    /* FIXME: overflow check */
    strcpy(buf, dirname);
    strcat(buf, "/");
    strcat(buf, filename);

    return buf;
}


int main(int argc, char *argv[])
{
    int  dirflag;
    char *srcname, *destname, *lastarg;

    /* Symbolic link? */

    if (argv[1][0] == '-') {
#if defined(S_ISLNK) && 0	/* FIXME */
	if (strcmp(argv[1], "-s") == 0) {
	    if (argc != 4) {
		fprintf(stderr, "%s: wrong number of arguments for symbolic link\n", argv[0]);
		return 1;
	    }

	    if (symlink(argv[2], argv[3]) < 0) {
		perror(argv[3]);
		return 1;
	    }
	    return 0;

	}
#endif
	fprintf(stderr, "%s: unknown option %s\n", argv[0], argv[1]);
	return 1;
    }

    /* Here for normal hard links. */

    lastarg = argv[argc - 1];
    dirflag = isadir(lastarg);

    if ((argc > 3) && !dirflag) {
        fprintf(stderr, "%s: not a directory\n", lastarg);
	return 1;
    }

    while (argc-- > 2) {
	srcname = *(++argv);
	if (access(srcname, 0) < 0) {
	    perror(srcname);
	    continue;
	}

	destname = lastarg;
	if (dirflag)
	    destname = buildname(destname, srcname);

	if (link(srcname, destname) < 0) {
	    perror(destname);
	    continue;
	}
    }

    return 0;
}
