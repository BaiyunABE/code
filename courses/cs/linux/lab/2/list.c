#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <dirent.h>
#include <time.h>

void Stat(const char *pathname, struct stat *statbuf);

DIR *Opendir(const char *name);

struct dirent *Readdir(DIR *dirp);

void *Malloc(size_t size);

void Closedir(DIR *dirp);

struct Config
{
	unsigned long r;
	unsigned long a;
	unsigned long l;
	unsigned long h;
	unsigned long m;
} config;

void init_config();

unsigned long parse_opt_arg(const char *str, const char *name);

int parse_args(int argc, char *argv[]);

int is_dot_or_dotdot(const char *name);

char *path_join(const char *dir, const char *name);

void print_path(const char *path, long size);

void list_dir(const char *path);

void doit(const char *path);

int main(int argc, char *argv[])
{
	init_config();

	int i = parse_args(argc, argv);

	if (i == argc) // no operant, "." is default
	{
		doit(".");
	}

	for (; i < argc; i++)
	{
		doit(argv[i]);
	}

	exit(EXIT_SUCCESS);
}

void init_config()
{
	config.r = 0;
	config.a = 0;
	config.l = 0;
	config.h = ULONG_MAX;
	config.m = ULONG_MAX;
}

int parse_args(int argc, char *argv[])
{
	for (int i = 1; i < argc; i++)
	{
		if (argv[i][0] != '-') // argv[i] is the first positional parameter
		{
			return i;
		}
		if (argv[i][1] == 'r')
		{
			config.r = 1;
		}
		else if (argv[i][1] == 'a')
		{
			config.a = 1;
		}
		else if (argv[i][1] == 'l')
		{
			if (i + 1 == argc)
			{
				fprintf(stderr, "option requires an argument -- '%c'\n", argv[i][1]);
				exit(EXIT_FAILURE);
			}
			config.l = parse_opt_arg(argv[i + 1], "lower bound");
			i++;
		}
		else if (argv[i][1] == 'h')
		{
			if (i + 1 == argc)
			{
				fprintf(stderr, "option requires an argument -- '%c'\n", argv[i][1]);
				exit(EXIT_FAILURE);
			}
			config.h = parse_opt_arg(argv[i + 1], "upper bound");
			i++;
		}
		else if (argv[i][1] == 'm')
		{
			if (i + 1 == argc)
			{
				fprintf(stderr, "option requires an argument -- '%c'\n", argv[i][1]);
				exit(EXIT_FAILURE);
			}
			config.m = parse_opt_arg(argv[i + 1], "modification time");
			i++;
		}
		else if (argv[i][1] == '-') // argv[i + 1] is the first positional parameter
		{
			return i + 1;
		}
		else
		{
			fprintf(stderr, "invalid option -- '%c'\n", argv[i][1]);
			exit(EXIT_FAILURE);
		}
	}

	return argc;
}

unsigned long parse_opt_arg(const char *str, const char *name)
{
	char *end;
	errno = 0;
	unsigned long val = strtoul(str, &end, 0);
	if (errno != 0 || *end != 0)
	{
		fprintf(stderr, "invalid %s: '%s'\n", name, str);
		exit(EXIT_FAILURE);
	}
	return val;
}

void doit(const char *path)
{
	struct stat sb;
	Stat(path, &sb);

	if (S_ISDIR(sb.st_mode))
	{
		list_dir(path);
	}
	else
	{
		print_path(path, sb.st_size);
	}
}

void print_path(const char *path, long size)
{
	printf("%-40s %10ld bytes\n", path, size);
}

void Stat(const char *pathname, struct stat *statbuf)
{
	int rv = stat(pathname, statbuf);
	if (rv == -1)
	{
		perror("stat");
		fprintf(stderr, "path: %s\n", pathname);
		exit(EXIT_FAILURE);
	}
}

void list_dir(const char *path)
{
	DIR *dir = Opendir(path);
	struct dirent *entry;
	struct stat sb;

	while ((entry = Readdir(dir)) != NULL)
	{
		const char *name = entry->d_name;

		if (config.a == 0 && name[0] == '.')
		{
			continue;
		}

		if (config.r == 1 && is_dot_or_dotdot(name))
		{
			continue;
		}

		char *cpath = path_join(path, name);
		Stat(cpath, &sb);

		off_t size = sb.st_size;
		int days = (time(NULL) - sb.st_mtime) / (3600 * 24);

		if (S_ISREG(sb.st_mode) && size >= config.l && size <= config.h && days <= config.m)
		{
			print_path(cpath, size);
		}

		if (config.r == 1 && S_ISDIR(sb.st_mode))
		{
			list_dir(cpath);
		}

		free(cpath);
	}

	Closedir(dir);
}

DIR *Opendir(const char *name)
{
	DIR *dir = opendir(name);
	if (dir == NULL)
	{
		perror("opendir");
		exit(EXIT_FAILURE);
	}
	return dir;
}

struct dirent *Readdir(DIR *dirp)
{
	errno = 0;
	struct dirent *entry = readdir(dirp);
	if (errno != 0)
	{
		perror("readdir");
		exit(EXIT_FAILURE);
	}
	return entry;
}

int is_dot_or_dotdot(const char *name)
{
	return strcmp(name, ".") == 0 || strcmp(name, "..") == 0;
}

char *path_join(const char *dir, const char *name)
{
	size_t dlen = strlen(dir);
	size_t nlen = strlen(name);

	int need_slash = (dlen > 0 && dir[dlen - 1] != '/');

	char *path = Malloc(dlen + need_slash + nlen + 1);

	memcpy(path, dir, dlen);

	if (need_slash)
	{
		path[dlen] = '/';
		memcpy(path + dlen + 1, name, nlen);
		path[dlen + 1 + nlen] = '\0';
	}
	else
	{
		memcpy(path + dlen, name, nlen);
		path[dlen + nlen] = '\0';
	}

	return path;
}

void *Malloc(size_t size)
{
	void *rp = malloc(size);
	if (rp == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	return rp;
}

void Closedir(DIR *dirp)
{
	int rv = closedir(dirp);
	if (rv == -1)
	{
		perror("closedir");
		exit(EXIT_FAILURE);
	}
}
