
%define FD_STDIN	0
%define FD_STDOUT	1
%define FD_STDERR	2

; open - flags - fcntl.h
%define O_RDONLY        00000000
%define O_WRONLY        00000001
%define O_RDWR          00000002
%define O_CREAT         00000100        ; not fcntl */
%define O_EXCL          00000200        ; not fcntl */
%define O_NOCTTY        00000400        ; not fcntl */
%define O_TRUNC         00001000        ; not fcntl */
%define O_APPEND        00002000
%define O_NONBLOCK      00004000
%define O_DSYNC         00010000        ; used to be O_SYNC, see below */
%define O_DIRECT        00040000        ; direct disk access hint */
%define O_LARGEFILE     00100000
%define O_DIRECTORY     00200000        ; must be a directory */
%define O_NOFOLLOW      00400000        ; don't follow links */
%define O_NOATIME       01000000
%define O_CLOEXEC       02000000        ; set close_on_exec */
%define __O_SYNC        04000000
%define O_SYNC          (__O_SYNC|O_DSYNC)
%define O_PATH          010000000
%define __O_TMPFILE     020000000
%define O_TMPFILE (__O_TMPFILE | O_DIRECTORY)
%define O_TMPFILE_MASK (__O_TMPFILE | O_DIRECTORY | O_CREAT)
%define O_NDELAY        O_NONBLOCK

; open - mode - stat.h
%define S_IRWXU 00700
%define S_IRUSR 00400
%define S_IWUSR 00200
%define S_IXUSR 00100
%define S_IRWXG 00070
%define S_IRGRP 00040
%define S_IWGRP 00020
%define S_IXGRP 00010
%define S_IRWXO 00007
%define S_IROTH 00004
%define S_IWOTH 00002
%define S_IXOTH 00001

%define STACK_ALIGN_SIZE  0x10

; data.s
extern _HEXCHARS

