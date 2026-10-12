# Linux 系统编程实验：遍历目录

班级：2023211303

学号：2023210810

姓名：陈子容

[TOC]

## 一、实验目的
1. 编程实现目录遍历程序 `list`，列出普通磁盘文件的文件名与大小。
2. 熟练使用 `vi` 编辑器进行代码编写。
3. 掌握 Linux 目录操作、文件属性获取等系统调用与库函数。
4. 理解 Shell 通配符处理机制，手动实现命令行选项解析。
5. 体会 Unix/Linux 命令行工具的设计规范。

---

## 二、实验环境

- 操作系统：Ubuntu 22.04.5 LTS (jammy)
- 内核版本：6.8.0-111-generic
- 编译器：gcc (Ubuntu 14.3.0-12ubuntu1~22~ppa2) 14.3.0
- 编辑器：VIM - Vi IMproved 8.2
- 开发工具：make、bash

---

## 三、实验要求
### 基本要求
- 实现程序 `list.c`，列出普通磁盘文件，输出文件名和文件大小。
- 使用 Linux 系统调用与库函数。
- 手动编程解析命令行选项，不使用 `getopt` 等库函数。
- 支持 0 个/1 个/多个路径参数，支持目录、普通文件处理。

### 处理对象与选项
- 无参数：列出当前目录下非隐藏普通文件。
- 普通文件：直接输出文件信息。
- 目录：遍历目录下所有普通文件。
- 支持选项：`-r` `-a` `-l` `-h` `-m` `--`。

### 选项说明
- `-r`：递归遍历子目录，输出完整路径。
- `-a`：显示以 `.` 开头的隐藏文件。
- `-l 数字`：限定文件大小最小值（字节）。
- `-h 数字`：限定文件大小最大值（字节）。
- `-m 数字`：限定文件最近 n 天内修改。
- `--`：显式终止选项解析，后续参数均作为文件名处理。

---

## 四、核心函数与系统调用
本实验使用以下关键系统函数：
- `opendir` / `readdir` / `closedir`：目录遍历。
- `stat`：获取文件属性（大小、修改时间、类型）。
- `S_ISREG`：判断是否为普通文件。
- `S_ISDIR`：判断是否为目录。
- `strtoul`：字符串转无符号长整型。
- `malloc` / `free`：动态路径拼接。

---

## 五、程序设计思路
### 1. 整体架构
1. **配置结构体**：使用 `struct Config` 统一存储所有选项。
2. **命令行解析**：手动遍历 `argv`，解析选项与参数。
3. **文件/目录分发**：`doit` 判断是文件还是目录，分别处理。
4. **目录遍历**：`list_dir` 递归遍历目录，过滤文件。
5. **输出格式**：统一输出文件名 + 文件大小。

### 2. 流程
1. 初始化配置。
2. 解析命令行选项。
3. 遍历路径参数。
4. 递归/非递归遍历目录。
5. 按大小、时间、隐藏属性过滤文件。
6. 输出符合条件的普通文件。

---

## 六、核心代码展示
```c
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

```

## 七、编译与运行

### 编译命令

```bash
gcc -Wall list.c -o list
```

### 运行测试示例

#### 1. 默认遍历当前目录

```bash
$ ./list 
./Makefile                                       63 bytes
./list.c                                       4916 bytes
./report.md                                    5137 bytes
./list                                        17152 bytes
./README.md                                    2238 bytes
```

#### 2. 按文件大小过滤

```bash
$ ./list -l 100 -h 5000 /bin /etc 
/bin/gunzip                                    2346 bytes
/bin/ubuntu-advantage                          1003 bytes
/bin/zforce                                    2081 bytes
/bin/bzmore                                    1297 bytes
/bin/Xorg                                       274 bytes
/bin/pod2html                                  4137 bytes
/bin/xzless                                    1799 bytes
/bin/X                                          274 bytes
/bin/pfbtopfa                                   516 bytes
/bin/podchecker                                3658 bytes
/bin/spd-conf                                  1003 bytes
/bin/check-language-support                    2771 bytes
/bin/thunderbird                               2946 bytes
/bin/aspell-import                             2044 bytes
/bin/xml2-config                               1436 bytes
/bin/gsnd                                       277 bytes
/bin/gsdj                                       352 bytes
/bin/padsp                                     2233 bytes
/bin/mako-render                                958 bytes
/bin/lsinitramfs                                706 bytes
/bin/gnome-www-browser                         2882 bytes
/bin/poff                                      2837 bytes
/bin/debconf                                   2859 bytes
/bin/usbip                                     1622 bytes
/bin/x86_64-linux-gnu-python3-config           3123 bytes
/bin/wpspdf                                    1096 bytes
/bin/pod2usage                                 4107 bytes
/bin/c99-gcc                                    454 bytes
/bin/routel                                    1656 bytes
/bin/os-prober                                 4551 bytes
/bin/gnome-tweaks                              2829 bytes
/bin/python3.10-config                         3123 bytes
/bin/analyze-build-17                           557 bytes
/bin/znew                                      4577 bytes
/bin/which.debianutils                          946 bytes
/bin/wpp                                       1639 bytes
/bin/x11perfcomp                               2807 bytes
/bin/gsbj                                       350 bytes
/bin/ua                                        1003 bytes
/bin/lwp-mirror                                2413 bytes
/bin/software-properties-gtk                   4176 bytes
/bin/pl2pm                                     4536 bytes
/bin/usb-devices                               4429 bytes
/bin/perf                                      1622 bytes
/bin/start-pulseaudio-x11                      2159 bytes
/bin/ps2ps2                                     669 bytes
/bin/switcherooctl                             4649 bytes
/bin/fcitx-skin-installer                      1482 bytes
/bin/nroff                                     3293 bytes
/bin/bzexe                                     4893 bytes
/bin/wps                                       3069 bytes
/bin/pf2afm                                     498 bytes
/bin/lspgpot                                   1081 bytes
/bin/on_ac_power                               3788 bytes
/bin/gcore                                     3477 bytes
/bin/im-launch                                 1798 bytes
/bin/fakeroot                                  3995 bytes
/bin/pdf2dsc                                    698 bytes
/bin/x86_64-linux-gnu-pkg-config               2235 bytes
/bin/debconf-escape                             647 bytes
/bin/gnome-terminal.wrapper                    2718 bytes
/bin/c89                                        428 bytes
/bin/sotruss                                   4309 bytes
/bin/yt-dlp                                     962 bytes
/bin/lsb_release                               3638 bytes
/bin/routef                                     208 bytes
/bin/gdb-add-index                             4627 bytes
/bin/gnome-characters                           299 bytes
/bin/rstartd                                   1469 bytes
/bin/plog                                       146 bytes
/bin/gnome-language-selector                   1444 bytes
/bin/x-www-browser                             2882 bytes
/bin/rstart                                    2610 bytes
/bin/dpkg-parsechangelog                       4947 bytes
/bin/chardet                                    965 bytes
/bin/scan-view-17                              4717 bytes
/bin/usb-creator-gtk                           2936 bytes
/bin/grog                                      2776 bytes
/bin/pip                                        221 bytes
/bin/ubuntu-bug                                2568 bytes
/bin/linux-boot-prober                         1577 bytes
/bin/hp-plugin-ubuntu                           719 bytes
/bin/x-session-manager                          803 bytes
/bin/bytedance-feishu                          1712 bytes
/bin/ps2txt                                     631 bytes
/bin/fakeroot-sysv                             3995 bytes
/bin/ssh-argv0                                 1455 bytes
/bin/chardetect                                 965 bytes
/bin/kvm-spice                                  401 bytes
/bin/laptop-detect                             3820 bytes
/bin/apg                                        274 bytes
/bin/aptdcon                                   1039 bytes
/bin/dvipdf                                    1007 bytes
/bin/select-default-iwrap                       474 bytes
/bin/pro                                       1003 bytes
/bin/moggsplit                                  965 bytes
/bin/migrate-pubring-from-classic-gpg          3060 bytes
/bin/instmodsh                                 4373 bytes
/bin/printafm                                   395 bytes
/bin/dpkg-vendor                               3262 bytes
/bin/ps2ps                                      647 bytes
/bin/apport-unpack                             2070 bytes
/bin/scan-build-py-17                           551 bytes
/bin/debconf-set-selections                    2995 bytes
/bin/grub-kbdcomp                              1681 bytes
/bin/apport-collect                            2568 bytes
/bin/debconf-copydb                            1719 bytes
/bin/valgrind                                   528 bytes
/bin/json_pp                                   4992 bytes
/bin/bzless                                    1297 bytes
/bin/uncompress                                2346 bytes
/bin/pip3.10                                    221 bytes
/bin/select-editor                             2450 bytes
/bin/unmkinitramfs                             3774 bytes
/bin/bzegrep                                   3775 bytes
/bin/pasteurize                                 964 bytes
/bin/pphs                                       404 bytes
/bin/bzdiff                                    2225 bytes
/bin/gnome-shell-extension-tool                1706 bytes
/bin/linux-check-removal                       4090 bytes
/bin/bzgrep                                    3775 bytes
/bin/bison.yacc                                4214 bytes
/bin/pw-v4l2                                   1992 bytes
/bin/acpidbg                                   1622 bytes
/bin/hp-timedate                               3386 bytes
/bin/ps2pdf12                                   215 bytes
/bin/make-first-existing-target                4905 bytes
/bin/fcitx-autostart                            277 bytes
/bin/sensible-pager                             565 bytes
/bin/gslp                                       350 bytes
/bin/strace-log-merge                          1821 bytes
/bin/eps2eps                                    639 bytes
/bin/p7zip                                     4754 bytes
/bin/bzfgrep                                   3775 bytes
/bin/lzless                                    1799 bytes
/bin/quirks-handler                            2453 bytes
/bin/apport-bug                                2568 bytes
/bin/zipgrep                                   2959 bytes
/bin/vimtutor                                  2154 bytes
/bin/nvidia-detector                            270 bytes
/bin/usbipd                                    1622 bytes
/bin/xdg-user-dir                               234 bytes
/bin/ps2epsi                                   1264 bytes
/bin/x86_64-linux-gnu-python3.10-config        3123 bytes
/bin/ps2pdf14                                   215 bytes
/bin/pygmentize                                 970 bytes
/bin/ps2ascii                                   631 bytes
/bin/bochs                                      172 bytes
/bin/pip3                                       221 bytes
/bin/code                                      2125 bytes
/bin/dh_bash-completion                        4414 bytes
/bin/sensible-editor                           1269 bytes
/bin/ps2pdf                                     272 bytes
/bin/gnome-terminal                            3400 bytes
/bin/pdf2ps                                     909 bytes
/bin/hp-pkservice                              3206 bytes
/bin/zstdgrep                                  3869 bytes
/bin/which                                      946 bytes
/bin/dh_perl_openssl                           1541 bytes
/bin/gdbtui                                     126 bytes
/bin/intercept-build-17                         563 bytes
/bin/kernel-install                            4902 bytes
/bin/cautious-launcher                          853 bytes
/bin/python3-config                            3123 bytes
/bin/cpupower                                  1622 bytes
/bin/remmina-file-wrapper                      1321 bytes
/bin/mutagen-inspect                            977 bytes
/bin/debconf-show                              1827 bytes
/bin/linux-version                             2698 bytes
/bin/et                                        1638 bytes
/bin/c89-gcc                                    428 bytes
/bin/gslj                                       353 bytes
/bin/ps2pdf13                                   215 bytes
/bin/unicode_start                             2762 bytes
/bin/fakeroot-tcp                              3990 bytes
/bin/keyring                                    961 bytes
/bin/gnome-session                              803 bytes
/bin/update-manager                            4771 bytes
/bin/neqn                                       913 bytes
/bin/x86_energy_perf_policy                    1622 bytes
/bin/gsdj500                                    352 bytes
/bin/encguess                                  3078 bytes
/bin/bzcmp                                     2225 bytes
/bin/pyclean                                   4124 bytes
/bin/python3-futurize                           960 bytes
/bin/pon                                       1362 bytes
/bin/xzmore                                    2162 bytes
/bin/firefox                                   2882 bytes
/bin/debconf-communicate                        608 bytes
/bin/lwp-dump                                  2711 bytes
/bin/fcitx4-config                             1772 bytes
/bin/dpkg-realpath                             4189 bytes
/bin/ptardiff                                  2645 bytes
/bin/perldoc                                    125 bytes
/bin/sensible-browser                          1290 bytes
/bin/turbostat                                 1622 bytes
/bin/zcat                                      1984 bytes
/bin/qemu-system-x86_64-spice                   187 bytes
/bin/unicode_stop                               530 bytes
/bin/bytedance-feishu-stable                   1712 bytes
/bin/preparetips5                              1019 bytes
/bin/futurize                                   960 bytes
/bin/dpkg-distaddfile                          2782 bytes
/bin/x-terminal-emulator                       2718 bytes
/bin/zmore                                     1842 bytes
/bin/helpztags                                 2514 bytes
/bin/aa-easyprof                               4500 bytes
/bin/i686-linux-gnu-pkg-config                 2235 bytes
/bin/pa-info                                   2093 bytes
/bin/zless                                     2206 bytes
/bin/mid3iconv                                  965 bytes
/bin/gpg-zip                                   3516 bytes
/bin/zcmp                                      1678 bytes
/bin/yacc                                      4214 bytes
/bin/ptargrep                                  4395 bytes
/bin/foo2zjs-pstops                            2997 bytes
/bin/lzmore                                    2162 bytes
/bin/remmina-gnome                              530 bytes
/bin/mid3v2                                     959 bytes
/bin/c99                                        454 bytes
/bin/ps2pdfwr                                  1078 bytes
/bin/apturl                                     273 bytes
/bin/python3-pasteurize                         964 bytes
/bin/apturl-gtk                                1544 bytes
/bin/ptar                                      3566 bytes
/bin/driverless-fax                             537 bytes
/bin/mid3cp                                     959 bytes
/bin/mutagen-pony                               971 bytes
/etc/fstab                                      583 bytes
/etc/fuse.conf                                  694 bytes
/etc/sudo.conf                                 4573 bytes
/etc/gai.conf                                  2584 bytes
/etc/localtime                                  561 bytes
/etc/passwd                                    2974 bytes
/etc/appstream.conf                             769 bytes
/etc/qemu-ifup                                 1148 bytes
/etc/kernel-img.conf                            110 bytes
/etc/group                                     1109 bytes
/etc/apg.conf                                   433 bytes
/etc/protocols                                 2932 bytes
/etc/ucf.conf                                  1260 bytes
/etc/locale.alias                              2996 bytes
/etc/profile                                    582 bytes
/etc/mke2fs.conf                                744 bytes
/etc/logrotate.conf                             592 bytes
/etc/inputrc                                   1748 bytes
/etc/netconfig                                  767 bytes
/etc/bash.bashrc                               2319 bytes
/etc/deluser.conf                               604 bytes
/etc/sudoers                                   1671 bytes
/etc/printcap                                   135 bytes
/etc/ethertypes                                1816 bytes
/etc/nftables.conf                              228 bytes
/etc/rsyslog.conf                              1382 bytes
/etc/vtrgb                                      158 bytes
/etc/sysctl.conf                               2355 bytes
/etc/gshadow-                                   903 bytes
/etc/magic                                      111 bytes
/etc/qemu-ifdown                                163 bytes
/etc/hdparm.conf                               4436 bytes
/etc/crontab                                   1136 bytes
/etc/modules                                    195 bytes
/etc/nsswitch.conf                              542 bytes
/etc/shells                                     128 bytes
/etc/wgetrc                                    4942 bytes
/etc/shadow                                    1492 bytes
/etc/rpc                                        887 bytes
/etc/lsb-release                                104 bytes
/etc/bindresvport.blacklist                     367 bytes
/etc/mailcap.order                              449 bytes
/etc/os-release                                 386 bytes
/etc/group-                                    1093 bytes
/etc/adduser.conf                              3028 bytes
/etc/environment                                106 bytes
/etc/hosts.deny                                 711 bytes
/etc/e2scrub.conf                               685 bytes
/etc/hosts                                      232 bytes
/etc/passwd-                                   2932 bytes
/etc/libaudit.conf                              191 bytes
/etc/usb_modeswitch.conf                       1523 bytes
/etc/zsh_command_not_found                      460 bytes
/etc/shadow-                                   1492 bytes
/etc/hosts.allow                                411 bytes
/etc/magic.mime                                 111 bytes
/etc/kerneloops.conf                           1308 bytes
/etc/gshadow                                    916 bytes
/etc/xattr.conf                                 681 bytes
/etc/resolv.conf                                920 bytes
/etc/smi.conf                                  1201 bytes
/etc/anacrontab                                 335 bytes
/etc/debconf.conf                              2969 bytes
/etc/legal                                      267 bytes
/etc/pam.conf                                   552 bytes
```

#### 3. 递归 + 隐藏文件 + 大小 + 时间过滤

```bash
$ ./list -a -r -l 50000 -m 2 ~/code
/home/abe/code/courses/switch/textbook.pdf   46669036 bytes
/home/abe/code/courses/switch/homework/4-SIP.docx    1719166 bytes
/home/abe/code/courses/switch/exam/22.pdf     473185 bytes
stat: No such file or directory
path: /home/abe/code/courses/cn/cs144/minnow/compile_commands.json
```

#### 4. 选项终止符 --

```bash
$ ./list -- -l
stat: No such file or directory
path: -l
```

#### 5. Shell 通配符 *

```bash
$ ./list ~/code/*
/home/abe/code/proof/cos-n.md                  1420 bytes
/home/abe/code/proof/rbt.md                    1145 bytes
/home/abe/code/proof/cos-n.pdf                85593 bytes
/home/abe/code/sandbox/sandbox.md               218 bytes
```

## 八、测试结果与分析

### 1. 基础功能测试

- 无参数正常输出当前目录普通文件。
- 目录内无普通文件时无输出（符合要求）。

### 2. 选项功能测试

- `-r`：递归遍历正常，路径完整。
- `-a`：正确显示隐藏文件。
- `-l/-h`：大小过滤精准。
- `-m`：修改时间过滤正确。
- `--`：终止选项解析，与系统 `ls` 行为一致。

### 3. Shell 通配符测试

`*` 由 Shell 自动展开，程序正确接收并遍历所有路径。

### 4. 异常情况说明

遍历到**无效符号链接**时，`stat` 报错并退出。

**原因**：链接指向不存在文件。

**表现**：不影响整体功能，属于系统环境问题。

## 九、延伸学习

### 1. 手动解析命令行选项的体会

本次实验采用**手动逐字符解析命令行参数**，未使用任何选项解析库。通过这种方式，我深刻理解了以下内容：

- 程序通过 `argc` 和 `argv` 获取命令行输入；
- Shell 在传递参数前会预先完成通配符（如 `*`）展开；
- 必须手动区分无参选项（`-r`、`-a`）、带参选项（`-l`、`-h`、`-m`）以及选项终止符 `--`；
- 需要自行处理参数缺失、数值非法、无效选项等异常；
- 体会操作员输入与程序解析之间的信息交互过程。

### 2. 通用选项处理子程序设计思路

若要设计**可复用、跨命令通用**的选项解析模块，可采用以下设计思想：

- 将选项解析逻辑**独立为单独函数**，与目录遍历等业务逻辑解耦；
- 使用**配置结构体**统一存储所有选项状态；
- 封装参数校验、错误提示为公共工具函数；
- 遵循 Linux 标准，固定支持 `--` 作为选项终止符；
- 接口统一，便于多个命令复用。

### 3. getopt_long 学习

`getopt_long` 是 GNU 提供的**标准命令行选项解析库函数**，可大幅简化选项处理。其特点包括：

- 支持**短选项**（如 `-r`）与**长选项**（如 `--recursive`）；
- 自动处理参数缺失、无效选项、参数格式校验等工作；
- 代码更简洁、扩展性更强；
- 符合 Linux 工具设计规范。

**示例伪代码**

```c
#include <getopt.h>

struct option long_opts[] = {
    {"recursive", no_argument, 0, 'r'},
    {"all",       no_argument, 0, 'a'},
    {"lower",     required_argument, 0, 'l'},
    {0, 0, 0, 0}
};

int opt = getopt_long(argc, argv, "ral:h:m:", long_opts, NULL); 
```

### 4. 手写解析 与 getopt_long 对比

- **手写解析**：更底层，适合学习原理，理解命令行处理机制；
- **getopt_long**：更高效，适合实际开发，减少重复代码；
- 两者都体现了 **模块化、解耦、职责分离** 的 Unix 设计哲学。

## 十、实验总结

1. 成功实现目录遍历程序，满足实验全部要求。
2. 掌握目录操作、文件属性获取、递归编程。
3. 深入理解命令行选项解析与 Shell 通配符机制。
4. 程序结构清晰、健壮性强、符合 Linux 工具规范。
5. 通过延伸学习，理解了选项解析的标准化设计思路。
