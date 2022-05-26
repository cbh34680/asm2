%include "defs.s"

	section	.text
;
%define SC_read 0
global _s_read

_s_read:
	mov		rax, SC_read
	syscall
	ret
;
%define SC_write 1
global _s_write

_s_write:
	mov		rax, SC_write
	syscall
	ret
;
%define SC_open 2
global _s_open

_s_open:
	mov		rax, SC_open
	syscall
	ret
;
%define SC_close 3
global _s_close

_s_close:
	mov		rax, SC_close
	syscall
	ret
;
%define SC_stat 4
global _s_stat

_s_stat:
	mov		rax, SC_stat
	syscall
	ret
;
%define SC_fstat 5
global _s_fstat

_s_fstat:
	mov		rax, SC_fstat
	syscall
	ret
;
%define SC_lstat 6
global _s_lstat

_s_lstat:
	mov		rax, SC_lstat
	syscall
	ret
;
%define SC_poll 7
global _s_poll

_s_poll:
	mov		rax, SC_poll
	syscall
	ret
;
%define SC_lseek 8
global _s_lseek

_s_lseek:
	mov		rax, SC_lseek
	syscall
	ret
;
%define SC_mmap 9
global _s_mmap

_s_mmap:
	mov		rax, SC_mmap
	syscall
	ret
;
%define SC_mprotect 10
global _s_mprotect

_s_mprotect:
	mov		rax, SC_mprotect
	syscall
	ret
;
%define SC_munmap 11
global _s_munmap

_s_munmap:
	mov		rax, SC_munmap
	syscall
	ret
;
%define SC_brk 12
global _s_brk

_s_brk:
	mov		rax, SC_brk
	syscall
	ret
;
%define SC_rt_sigaction 13
global _s_rt_sigaction

_s_rt_sigaction:
	mov		rax, SC_rt_sigaction
	syscall
	ret
;
%define SC_rt_sigprocmask 14
global _s_rt_sigprocmask

_s_rt_sigprocmask:
	mov		rax, SC_rt_sigprocmask
	syscall
	ret
;
%define SC_rt_sigreturn 15
global _s_rt_sigreturn

_s_rt_sigreturn:
	mov		rax, SC_rt_sigreturn
	syscall
	ret
;
%define SC_ioctl 16
global _s_ioctl

_s_ioctl:
	mov		rax, SC_ioctl
	syscall
	ret
;
%define SC_pread 17
global _s_pread

_s_pread:
	mov		rax, SC_pread
	syscall
	ret
;
%define SC_pwrite 18
global _s_pwrite

_s_pwrite:
	mov		rax, SC_pwrite
	syscall
	ret
;
%define SC_readv 19
global _s_readv

_s_readv:
	mov		rax, SC_readv
	syscall
	ret
;
%define SC_writev 20
global _s_writev

_s_writev:
	mov		rax, SC_writev
	syscall
	ret
;
%define SC_access 21
global _s_access

_s_access:
	mov		rax, SC_access
	syscall
	ret
;
%define SC_pipe 22
global _s_pipe

_s_pipe:
	mov		rax, SC_pipe
	syscall
	ret
;
%define SC_select 23
global _s_select

_s_select:
	mov		rax, SC_select
	syscall
	ret
;
%define SC_sched_yield 24
global _s_sched_yield

_s_sched_yield:
	mov		rax, SC_sched_yield
	syscall
	ret
;
%define SC_mremap 25
global _s_mremap

_s_mremap:
	mov		rax, SC_mremap
	syscall
	ret
;
%define SC_msync 26
global _s_msync

_s_msync:
	mov		rax, SC_msync
	syscall
	ret
;
%define SC_mincore 27
global _s_mincore

_s_mincore:
	mov		rax, SC_mincore
	syscall
	ret
;
%define SC_madvise 28
global _s_madvise

_s_madvise:
	mov		rax, SC_madvise
	syscall
	ret
;
%define SC_shmget 29
global _s_shmget

_s_shmget:
	mov		rax, SC_shmget
	syscall
	ret
;
%define SC_shmat 30
global _s_shmat

_s_shmat:
	mov		rax, SC_shmat
	syscall
	ret
;
%define SC_shmctl 31
global _s_shmctl

_s_shmctl:
	mov		rax, SC_shmctl
	syscall
	ret
;
%define SC_dup 32
global _s_dup

_s_dup:
	mov		rax, SC_dup
	syscall
	ret
;
%define SC_dup2 33
global _s_dup2

_s_dup2:
	mov		rax, SC_dup2
	syscall
	ret
;
%define SC_pause 34
global _s_pause

_s_pause:
	mov		rax, SC_pause
	syscall
	ret
;
%define SC_nanosleep 35
global _s_nanosleep

_s_nanosleep:
	mov		rax, SC_nanosleep
	syscall
	ret
;
%define SC_getitimer 36
global _s_getitimer

_s_getitimer:
	mov		rax, SC_getitimer
	syscall
	ret
;
%define SC_alarm 37
global _s_alarm

_s_alarm:
	mov		rax, SC_alarm
	syscall
	ret
;
%define SC_setitimer 38
global _s_setitimer

_s_setitimer:
	mov		rax, SC_setitimer
	syscall
	ret
;
%define SC_getpid 39
global _s_getpid

_s_getpid:
	mov		rax, SC_getpid
	syscall
	ret
;
%define SC_sendfile 40
global _s_sendfile

_s_sendfile:
	mov		rax, SC_sendfile
	syscall
	ret
;
%define SC_socket 41
global _s_socket

_s_socket:
	mov		rax, SC_socket
	syscall
	ret
;
%define SC_connect 42
global _s_connect

_s_connect:
	mov		rax, SC_connect
	syscall
	ret
;
%define SC_accept 43
global _s_accept

_s_accept:
	mov		rax, SC_accept
	syscall
	ret
;
%define SC_sendto 44
global _s_sendto

_s_sendto:
	mov		rax, SC_sendto
	syscall
	ret
;
%define SC_recvfrom 45
global _s_recvfrom

_s_recvfrom:
	mov		rax, SC_recvfrom
	syscall
	ret
;
%define SC_sendmsg 46
global _s_sendmsg

_s_sendmsg:
	mov		rax, SC_sendmsg
	syscall
	ret
;
%define SC_recvmsg 47
global _s_recvmsg

_s_recvmsg:
	mov		rax, SC_recvmsg
	syscall
	ret
;
%define SC_shutdown 48
global _s_shutdown

_s_shutdown:
	mov		rax, SC_shutdown
	syscall
	ret
;
%define SC_bind 49
global _s_bind

_s_bind:
	mov		rax, SC_bind
	syscall
	ret
;
%define SC_listen 50
global _s_listen

_s_listen:
	mov		rax, SC_listen
	syscall
	ret
;
%define SC_getsockname 51
global _s_getsockname

_s_getsockname:
	mov		rax, SC_getsockname
	syscall
	ret
;
%define SC_getpeername 52
global _s_getpeername

_s_getpeername:
	mov		rax, SC_getpeername
	syscall
	ret
;
%define SC_socketpair 53
global _s_socketpair

_s_socketpair:
	mov		rax, SC_socketpair
	syscall
	ret
;
%define SC_setsockopt 54
global _s_setsockopt

_s_setsockopt:
	mov		rax, SC_setsockopt
	syscall
	ret
;
%define SC_getsockopt 55
global _s_getsockopt

_s_getsockopt:
	mov		rax, SC_getsockopt
	syscall
	ret
;
%define SC_clone 56
global _s_clone

_s_clone:
	mov		rax, SC_clone
	syscall
	ret
;
%define SC_fork 57
global _s_fork

_s_fork:
	mov		rax, SC_fork
	syscall
	ret
;
%define SC_vfork 58
global _s_vfork

_s_vfork:
	mov		rax, SC_vfork
	syscall
	ret
;
%define SC_execve 59
global _s_execve

_s_execve:
	mov		rax, SC_execve
	syscall
	ret
;
%define SC_exit 60
global _s_exit

_s_exit:
	mov		rax, SC_exit
	syscall
	ret
;
%define SC_wait4 61
global _s_wait4

_s_wait4:
	mov		rax, SC_wait4
	syscall
	ret
;
%define SC_kill 62
global _s_kill

_s_kill:
	mov		rax, SC_kill
	syscall
	ret
;
%define SC_uname 63
global _s_uname

_s_uname:
	mov		rax, SC_uname
	syscall
	ret
;
%define SC_semget 64
global _s_semget

_s_semget:
	mov		rax, SC_semget
	syscall
	ret
;
%define SC_semop 65
global _s_semop

_s_semop:
	mov		rax, SC_semop
	syscall
	ret
;
%define SC_semctl 66
global _s_semctl

_s_semctl:
	mov		rax, SC_semctl
	syscall
	ret
;
%define SC_shmdt 67
global _s_shmdt

_s_shmdt:
	mov		rax, SC_shmdt
	syscall
	ret
;
%define SC_msgget 68
global _s_msgget

_s_msgget:
	mov		rax, SC_msgget
	syscall
	ret
;
%define SC_msgsnd 69
global _s_msgsnd

_s_msgsnd:
	mov		rax, SC_msgsnd
	syscall
	ret
;
%define SC_msgrcv 70
global _s_msgrcv

_s_msgrcv:
	mov		rax, SC_msgrcv
	syscall
	ret
;
%define SC_msgctl 71
global _s_msgctl

_s_msgctl:
	mov		rax, SC_msgctl
	syscall
	ret
;
%define SC_fcntl 72
global _s_fcntl

_s_fcntl:
	mov		rax, SC_fcntl
	syscall
	ret
;
%define SC_flock 73
global _s_flock

_s_flock:
	mov		rax, SC_flock
	syscall
	ret
;
%define SC_fsync 74
global _s_fsync

_s_fsync:
	mov		rax, SC_fsync
	syscall
	ret
;
%define SC_fdatasync 75
global _s_fdatasync

_s_fdatasync:
	mov		rax, SC_fdatasync
	syscall
	ret
;
%define SC_truncate 76
global _s_truncate

_s_truncate:
	mov		rax, SC_truncate
	syscall
	ret
;
%define SC_ftruncate 77
global _s_ftruncate

_s_ftruncate:
	mov		rax, SC_ftruncate
	syscall
	ret
;
%define SC_getdents 78
global _s_getdents

_s_getdents:
	mov		rax, SC_getdents
	syscall
	ret
;
%define SC_getcwd 79
global _s_getcwd

_s_getcwd:
	mov		rax, SC_getcwd
	syscall
	ret
;
%define SC_chdir 80
global _s_chdir

_s_chdir:
	mov		rax, SC_chdir
	syscall
	ret
;
%define SC_fchdir 81
global _s_fchdir

_s_fchdir:
	mov		rax, SC_fchdir
	syscall
	ret
;
%define SC_rename 82
global _s_rename

_s_rename:
	mov		rax, SC_rename
	syscall
	ret
;
%define SC_mkdir 83
global _s_mkdir

_s_mkdir:
	mov		rax, SC_mkdir
	syscall
	ret
;
%define SC_rmdir 84
global _s_rmdir

_s_rmdir:
	mov		rax, SC_rmdir
	syscall
	ret
;
%define SC_creat 85
global _s_creat

_s_creat:
	mov		rax, SC_creat
	syscall
	ret
;
%define SC_link 86
global _s_link

_s_link:
	mov		rax, SC_link
	syscall
	ret
;
%define SC_unlink 87
global _s_unlink

_s_unlink:
	mov		rax, SC_unlink
	syscall
	ret
;
%define SC_symlink 88
global _s_symlink

_s_symlink:
	mov		rax, SC_symlink
	syscall
	ret
;
%define SC_readlink 89
global _s_readlink

_s_readlink:
	mov		rax, SC_readlink
	syscall
	ret
;
%define SC_chmod 90
global _s_chmod

_s_chmod:
	mov		rax, SC_chmod
	syscall
	ret
;
%define SC_fchmod 91
global _s_fchmod

_s_fchmod:
	mov		rax, SC_fchmod
	syscall
	ret
;
%define SC_chown 92
global _s_chown

_s_chown:
	mov		rax, SC_chown
	syscall
	ret
;
%define SC_fchown 93
global _s_fchown

_s_fchown:
	mov		rax, SC_fchown
	syscall
	ret
;
%define SC_lchown 94
global _s_lchown

_s_lchown:
	mov		rax, SC_lchown
	syscall
	ret
;
%define SC_umask 95
global _s_umask

_s_umask:
	mov		rax, SC_umask
	syscall
	ret
;
%define SC_gettimeofday 96
global _s_gettimeofday

_s_gettimeofday:
	mov		rax, SC_gettimeofday
	syscall
	ret
;
%define SC_getrlimit 97
global _s_getrlimit

_s_getrlimit:
	mov		rax, SC_getrlimit
	syscall
	ret
;
%define SC_getrusage 98
global _s_getrusage

_s_getrusage:
	mov		rax, SC_getrusage
	syscall
	ret
;
%define SC_sysinfo 99
global _s_sysinfo

_s_sysinfo:
	mov		rax, SC_sysinfo
	syscall
	ret
;
%define SC_times 100
global _s_times

_s_times:
	mov		rax, SC_times
	syscall
	ret
;
%define SC_ptrace 101
global _s_ptrace

_s_ptrace:
	mov		rax, SC_ptrace
	syscall
	ret
;
%define SC_getuid 102
global _s_getuid

_s_getuid:
	mov		rax, SC_getuid
	syscall
	ret
;
%define SC_syslog 103
global _s_syslog

_s_syslog:
	mov		rax, SC_syslog
	syscall
	ret
;
%define SC_getgid 104
global _s_getgid

_s_getgid:
	mov		rax, SC_getgid
	syscall
	ret
;
%define SC_setuid 105
global _s_setuid

_s_setuid:
	mov		rax, SC_setuid
	syscall
	ret
;
%define SC_setgid 106
global _s_setgid

_s_setgid:
	mov		rax, SC_setgid
	syscall
	ret
;
%define SC_geteuid 107
global _s_geteuid

_s_geteuid:
	mov		rax, SC_geteuid
	syscall
	ret
;
%define SC_getegid 108
global _s_getegid

_s_getegid:
	mov		rax, SC_getegid
	syscall
	ret
;
%define SC_setpgid 109
global _s_setpgid

_s_setpgid:
	mov		rax, SC_setpgid
	syscall
	ret
;
%define SC_getppid 110
global _s_getppid

_s_getppid:
	mov		rax, SC_getppid
	syscall
	ret
;
%define SC_getpgrp 111
global _s_getpgrp

_s_getpgrp:
	mov		rax, SC_getpgrp
	syscall
	ret
;
%define SC_setsid 112
global _s_setsid

_s_setsid:
	mov		rax, SC_setsid
	syscall
	ret
;
%define SC_setreuid 113
global _s_setreuid

_s_setreuid:
	mov		rax, SC_setreuid
	syscall
	ret
;
%define SC_setregid 114
global _s_setregid

_s_setregid:
	mov		rax, SC_setregid
	syscall
	ret
;
%define SC_getgroups 115
global _s_getgroups

_s_getgroups:
	mov		rax, SC_getgroups
	syscall
	ret
;
%define SC_setgroups 116
global _s_setgroups

_s_setgroups:
	mov		rax, SC_setgroups
	syscall
	ret
;
%define SC_setresuid 117
global _s_setresuid

_s_setresuid:
	mov		rax, SC_setresuid
	syscall
	ret
;
%define SC_getresuid 118
global _s_getresuid

_s_getresuid:
	mov		rax, SC_getresuid
	syscall
	ret
;
%define SC_setresgid 119
global _s_setresgid

_s_setresgid:
	mov		rax, SC_setresgid
	syscall
	ret
;
%define SC_getresgid 120
global _s_getresgid

_s_getresgid:
	mov		rax, SC_getresgid
	syscall
	ret
;
%define SC_getpgid 121
global _s_getpgid

_s_getpgid:
	mov		rax, SC_getpgid
	syscall
	ret
;
%define SC_setfsuid 122
global _s_setfsuid

_s_setfsuid:
	mov		rax, SC_setfsuid
	syscall
	ret
;
%define SC_setfsgid 123
global _s_setfsgid

_s_setfsgid:
	mov		rax, SC_setfsgid
	syscall
	ret
;
%define SC_getsid 124
global _s_getsid

_s_getsid:
	mov		rax, SC_getsid
	syscall
	ret
;
%define SC_capget 125
global _s_capget

_s_capget:
	mov		rax, SC_capget
	syscall
	ret
;
%define SC_capset 126
global _s_capset

_s_capset:
	mov		rax, SC_capset
	syscall
	ret
;
%define SC_rt_sigpending 127
global _s_rt_sigpending

_s_rt_sigpending:
	mov		rax, SC_rt_sigpending
	syscall
	ret
;
%define SC_rt_sigtimedwait 128
global _s_rt_sigtimedwait

_s_rt_sigtimedwait:
	mov		rax, SC_rt_sigtimedwait
	syscall
	ret
;
%define SC_rt_sigqueueinfo 129
global _s_rt_sigqueueinfo

_s_rt_sigqueueinfo:
	mov		rax, SC_rt_sigqueueinfo
	syscall
	ret
;
%define SC_rt_sigsuspend 130
global _s_rt_sigsuspend

_s_rt_sigsuspend:
	mov		rax, SC_rt_sigsuspend
	syscall
	ret
;
%define SC_sigaltstack 131
global _s_sigaltstack

_s_sigaltstack:
	mov		rax, SC_sigaltstack
	syscall
	ret
;
%define SC_utime 132
global _s_utime

_s_utime:
	mov		rax, SC_utime
	syscall
	ret
;
%define SC_mknod 133
global _s_mknod

_s_mknod:
	mov		rax, SC_mknod
	syscall
	ret
;
%define SC_uselib 134
global _s_uselib

_s_uselib:
	mov		rax, SC_uselib
	syscall
	ret
;
%define SC_personality 135
global _s_personality

_s_personality:
	mov		rax, SC_personality
	syscall
	ret
;
%define SC_ustat 136
global _s_ustat

_s_ustat:
	mov		rax, SC_ustat
	syscall
	ret
;
%define SC_statfs 137
global _s_statfs

_s_statfs:
	mov		rax, SC_statfs
	syscall
	ret
;
%define SC_fstatfs 138
global _s_fstatfs

_s_fstatfs:
	mov		rax, SC_fstatfs
	syscall
	ret
;
%define SC_sysfs 139
global _s_sysfs

_s_sysfs:
	mov		rax, SC_sysfs
	syscall
	ret
;
%define SC_getpriority 140
global _s_getpriority

_s_getpriority:
	mov		rax, SC_getpriority
	syscall
	ret
;
%define SC_setpriority 141
global _s_setpriority

_s_setpriority:
	mov		rax, SC_setpriority
	syscall
	ret
;
%define SC_sched_setparam 142
global _s_sched_setparam

_s_sched_setparam:
	mov		rax, SC_sched_setparam
	syscall
	ret
;
%define SC_sched_getparam 143
global _s_sched_getparam

_s_sched_getparam:
	mov		rax, SC_sched_getparam
	syscall
	ret
;
%define SC_sched_setscheduler 144
global _s_sched_setscheduler

_s_sched_setscheduler:
	mov		rax, SC_sched_setscheduler
	syscall
	ret
;
%define SC_sched_getscheduler 145
global _s_sched_getscheduler

_s_sched_getscheduler:
	mov		rax, SC_sched_getscheduler
	syscall
	ret
;
%define SC_sched_get_priority_max 146
global _s_sched_get_priority_max

_s_sched_get_priority_max:
	mov		rax, SC_sched_get_priority_max
	syscall
	ret
;
%define SC_sched_get_priority_min 147
global _s_sched_get_priority_min

_s_sched_get_priority_min:
	mov		rax, SC_sched_get_priority_min
	syscall
	ret
;
%define SC_sched_rr_get_interval 148
global _s_sched_rr_get_interval

_s_sched_rr_get_interval:
	mov		rax, SC_sched_rr_get_interval
	syscall
	ret
;
%define SC_mlock 149
global _s_mlock

_s_mlock:
	mov		rax, SC_mlock
	syscall
	ret
;
%define SC_munlock 150
global _s_munlock

_s_munlock:
	mov		rax, SC_munlock
	syscall
	ret
;
%define SC_mlockall 151
global _s_mlockall

_s_mlockall:
	mov		rax, SC_mlockall
	syscall
	ret
;
%define SC_munlockall 152
global _s_munlockall

_s_munlockall:
	mov		rax, SC_munlockall
	syscall
	ret
;
%define SC_vhangup 153
global _s_vhangup

_s_vhangup:
	mov		rax, SC_vhangup
	syscall
	ret
;
%define SC_modify_ldt 154
global _s_modify_ldt

_s_modify_ldt:
	mov		rax, SC_modify_ldt
	syscall
	ret
;
%define SC_pivot_root 155
global _s_pivot_root

_s_pivot_root:
	mov		rax, SC_pivot_root
	syscall
	ret
;
%define SC__sysctl 156
global _s__sysctl

_s__sysctl:
	mov		rax, SC__sysctl
	syscall
	ret
;
%define SC_prctl 157
global _s_prctl

_s_prctl:
	mov		rax, SC_prctl
	syscall
	ret
;
%define SC_arch_prctl 158
global _s_arch_prctl

_s_arch_prctl:
	mov		rax, SC_arch_prctl
	syscall
	ret
;
%define SC_adjtimex 159
global _s_adjtimex

_s_adjtimex:
	mov		rax, SC_adjtimex
	syscall
	ret
;
%define SC_setrlimit 160
global _s_setrlimit

_s_setrlimit:
	mov		rax, SC_setrlimit
	syscall
	ret
;
%define SC_chroot 161
global _s_chroot

_s_chroot:
	mov		rax, SC_chroot
	syscall
	ret
;
%define SC_sync 162
global _s_sync

_s_sync:
	mov		rax, SC_sync
	syscall
	ret
;
%define SC_acct 163
global _s_acct

_s_acct:
	mov		rax, SC_acct
	syscall
	ret
;
%define SC_settimeofday 164
global _s_settimeofday

_s_settimeofday:
	mov		rax, SC_settimeofday
	syscall
	ret
;
%define SC_mount 165
global _s_mount

_s_mount:
	mov		rax, SC_mount
	syscall
	ret
;
%define SC_umount2 166
global _s_umount2

_s_umount2:
	mov		rax, SC_umount2
	syscall
	ret
;
%define SC_swapon 167
global _s_swapon

_s_swapon:
	mov		rax, SC_swapon
	syscall
	ret
;
%define SC_swapoff 168
global _s_swapoff

_s_swapoff:
	mov		rax, SC_swapoff
	syscall
	ret
;
%define SC_reboot 169
global _s_reboot

_s_reboot:
	mov		rax, SC_reboot
	syscall
	ret
;
%define SC_sethostname 170
global _s_sethostname

_s_sethostname:
	mov		rax, SC_sethostname
	syscall
	ret
;
%define SC_setdomainname 171
global _s_setdomainname

_s_setdomainname:
	mov		rax, SC_setdomainname
	syscall
	ret
;
%define SC_iopl 172
global _s_iopl

_s_iopl:
	mov		rax, SC_iopl
	syscall
	ret
;
%define SC_ioperm 173
global _s_ioperm

_s_ioperm:
	mov		rax, SC_ioperm
	syscall
	ret
;
%define SC_create_module 174
global _s_create_module

_s_create_module:
	mov		rax, SC_create_module
	syscall
	ret
;
%define SC_init_module 175
global _s_init_module

_s_init_module:
	mov		rax, SC_init_module
	syscall
	ret
;
%define SC_delete_module 176
global _s_delete_module

_s_delete_module:
	mov		rax, SC_delete_module
	syscall
	ret
;
%define SC_get_kernel_syms 177
global _s_get_kernel_syms

_s_get_kernel_syms:
	mov		rax, SC_get_kernel_syms
	syscall
	ret
;
%define SC_query_module 178
global _s_query_module

_s_query_module:
	mov		rax, SC_query_module
	syscall
	ret
;
%define SC_quotactl 179
global _s_quotactl

_s_quotactl:
	mov		rax, SC_quotactl
	syscall
	ret
;
%define SC_nfsservctl 180
global _s_nfsservctl

_s_nfsservctl:
	mov		rax, SC_nfsservctl
	syscall
	ret
;
%define SC_getpmsg 181
global _s_getpmsg

_s_getpmsg:
	mov		rax, SC_getpmsg
	syscall
	ret
;
%define SC_putpmsg 182
global _s_putpmsg

_s_putpmsg:
	mov		rax, SC_putpmsg
	syscall
	ret
;
%define SC_afs_syscall 183
global _s_afs_syscall

_s_afs_syscall:
	mov		rax, SC_afs_syscall
	syscall
	ret
;
%define SC_tuxcall 184
global _s_tuxcall

_s_tuxcall:
	mov		rax, SC_tuxcall
	syscall
	ret
;
%define SC_security 185
global _s_security

_s_security:
	mov		rax, SC_security
	syscall
	ret
;
%define SC_gettid 186
global _s_gettid

_s_gettid:
	mov		rax, SC_gettid
	syscall
	ret
;
%define SC_readahead 187
global _s_readahead

_s_readahead:
	mov		rax, SC_readahead
	syscall
	ret
;
%define SC_setxattr 188
global _s_setxattr

_s_setxattr:
	mov		rax, SC_setxattr
	syscall
	ret
;
%define SC_lsetxattr 189
global _s_lsetxattr

_s_lsetxattr:
	mov		rax, SC_lsetxattr
	syscall
	ret
;
%define SC_fsetxattr 190
global _s_fsetxattr

_s_fsetxattr:
	mov		rax, SC_fsetxattr
	syscall
	ret
;
%define SC_getxattr 191
global _s_getxattr

_s_getxattr:
	mov		rax, SC_getxattr
	syscall
	ret
;
%define SC_lgetxattr 192
global _s_lgetxattr

_s_lgetxattr:
	mov		rax, SC_lgetxattr
	syscall
	ret
;
%define SC_fgetxattr 193
global _s_fgetxattr

_s_fgetxattr:
	mov		rax, SC_fgetxattr
	syscall
	ret
;
%define SC_listxattr 194
global _s_listxattr

_s_listxattr:
	mov		rax, SC_listxattr
	syscall
	ret
;
%define SC_llistxattr 195
global _s_llistxattr

_s_llistxattr:
	mov		rax, SC_llistxattr
	syscall
	ret
;
%define SC_flistxattr 196
global _s_flistxattr

_s_flistxattr:
	mov		rax, SC_flistxattr
	syscall
	ret
;
%define SC_removexattr 197
global _s_removexattr

_s_removexattr:
	mov		rax, SC_removexattr
	syscall
	ret
;
%define SC_lremovexattr 198
global _s_lremovexattr

_s_lremovexattr:
	mov		rax, SC_lremovexattr
	syscall
	ret
;
%define SC_fremovexattr 199
global _s_fremovexattr

_s_fremovexattr:
	mov		rax, SC_fremovexattr
	syscall
	ret
;
%define SC_tkill 200
global _s_tkill

_s_tkill:
	mov		rax, SC_tkill
	syscall
	ret
;
%define SC_time 201
global _s_time

_s_time:
	mov		rax, SC_time
	syscall
	ret
;
%define SC_futex 202
global _s_futex

_s_futex:
	mov		rax, SC_futex
	syscall
	ret
;
%define SC_sched_setaffinity 203
global _s_sched_setaffinity

_s_sched_setaffinity:
	mov		rax, SC_sched_setaffinity
	syscall
	ret
;
%define SC_sched_getaffinity 204
global _s_sched_getaffinity

_s_sched_getaffinity:
	mov		rax, SC_sched_getaffinity
	syscall
	ret
;
%define SC_set_thread_area 205
global _s_set_thread_area

_s_set_thread_area:
	mov		rax, SC_set_thread_area
	syscall
	ret
;
%define SC_io_setup 206
global _s_io_setup

_s_io_setup:
	mov		rax, SC_io_setup
	syscall
	ret
;
%define SC_io_destroy 207
global _s_io_destroy

_s_io_destroy:
	mov		rax, SC_io_destroy
	syscall
	ret
;
%define SC_io_getevents 208
global _s_io_getevents

_s_io_getevents:
	mov		rax, SC_io_getevents
	syscall
	ret
;
%define SC_io_submit 209
global _s_io_submit

_s_io_submit:
	mov		rax, SC_io_submit
	syscall
	ret
;
%define SC_io_cancel 210
global _s_io_cancel

_s_io_cancel:
	mov		rax, SC_io_cancel
	syscall
	ret
;
%define SC_get_thread_area 211
global _s_get_thread_area

_s_get_thread_area:
	mov		rax, SC_get_thread_area
	syscall
	ret
;
%define SC_lookup_dcookie 212
global _s_lookup_dcookie

_s_lookup_dcookie:
	mov		rax, SC_lookup_dcookie
	syscall
	ret
;
%define SC_epoll_create 213
global _s_epoll_create

_s_epoll_create:
	mov		rax, SC_epoll_create
	syscall
	ret
;
%define SC_epoll_ctl_old 214
global _s_epoll_ctl_old

_s_epoll_ctl_old:
	mov		rax, SC_epoll_ctl_old
	syscall
	ret
;
%define SC_epoll_wait_old 215
global _s_epoll_wait_old

_s_epoll_wait_old:
	mov		rax, SC_epoll_wait_old
	syscall
	ret
;
%define SC_remap_file_pages 216
global _s_remap_file_pages

_s_remap_file_pages:
	mov		rax, SC_remap_file_pages
	syscall
	ret
;
%define SC_getdents64 217
global _s_getdents64

_s_getdents64:
	mov		rax, SC_getdents64
	syscall
	ret
;
%define SC_set_tid_address 218
global _s_set_tid_address

_s_set_tid_address:
	mov		rax, SC_set_tid_address
	syscall
	ret
;
%define SC_restart_syscall 219
global _s_restart_syscall

_s_restart_syscall:
	mov		rax, SC_restart_syscall
	syscall
	ret
;
%define SC_semtimedop 220
global _s_semtimedop

_s_semtimedop:
	mov		rax, SC_semtimedop
	syscall
	ret
;
%define SC_fadvise64 221
global _s_fadvise64

_s_fadvise64:
	mov		rax, SC_fadvise64
	syscall
	ret
;
%define SC_timer_create 222
global _s_timer_create

_s_timer_create:
	mov		rax, SC_timer_create
	syscall
	ret
;
%define SC_timer_settime 223
global _s_timer_settime

_s_timer_settime:
	mov		rax, SC_timer_settime
	syscall
	ret
;
%define SC_timer_gettime 224
global _s_timer_gettime

_s_timer_gettime:
	mov		rax, SC_timer_gettime
	syscall
	ret
;
%define SC_timer_getoverrun 225
global _s_timer_getoverrun

_s_timer_getoverrun:
	mov		rax, SC_timer_getoverrun
	syscall
	ret
;
%define SC_timer_delete 226
global _s_timer_delete

_s_timer_delete:
	mov		rax, SC_timer_delete
	syscall
	ret
;
%define SC_clock_settime 227
global _s_clock_settime

_s_clock_settime:
	mov		rax, SC_clock_settime
	syscall
	ret
;
%define SC_clock_gettime 228
global _s_clock_gettime

_s_clock_gettime:
	mov		rax, SC_clock_gettime
	syscall
	ret
;
%define SC_clock_getres 229
global _s_clock_getres

_s_clock_getres:
	mov		rax, SC_clock_getres
	syscall
	ret
;
%define SC_clock_nanosleep 230
global _s_clock_nanosleep

_s_clock_nanosleep:
	mov		rax, SC_clock_nanosleep
	syscall
	ret
;
%define SC_exit_group 231
global _s_exit_group

_s_exit_group:
	mov		rax, SC_exit_group
	syscall
	ret
;
%define SC_epoll_wait 232
global _s_epoll_wait

_s_epoll_wait:
	mov		rax, SC_epoll_wait
	syscall
	ret
;
%define SC_epoll_ctl 233
global _s_epoll_ctl

_s_epoll_ctl:
	mov		rax, SC_epoll_ctl
	syscall
	ret
;
%define SC_tgkill 234
global _s_tgkill

_s_tgkill:
	mov		rax, SC_tgkill
	syscall
	ret
;
%define SC_utimes 235
global _s_utimes

_s_utimes:
	mov		rax, SC_utimes
	syscall
	ret
;
%define SC_vserver 236
global _s_vserver

_s_vserver:
	mov		rax, SC_vserver
	syscall
	ret
;
%define SC_mbind 237
global _s_mbind

_s_mbind:
	mov		rax, SC_mbind
	syscall
	ret
;
%define SC_set_mempolicy 238
global _s_set_mempolicy

_s_set_mempolicy:
	mov		rax, SC_set_mempolicy
	syscall
	ret
;
%define SC_get_mempolicy 239
global _s_get_mempolicy

_s_get_mempolicy:
	mov		rax, SC_get_mempolicy
	syscall
	ret
;
%define SC_mq_open 240
global _s_mq_open

_s_mq_open:
	mov		rax, SC_mq_open
	syscall
	ret
;
%define SC_mq_unlink 241
global _s_mq_unlink

_s_mq_unlink:
	mov		rax, SC_mq_unlink
	syscall
	ret
;
%define SC_mq_timedsend 242
global _s_mq_timedsend

_s_mq_timedsend:
	mov		rax, SC_mq_timedsend
	syscall
	ret
;
%define SC_mq_timedreceive 243
global _s_mq_timedreceive

_s_mq_timedreceive:
	mov		rax, SC_mq_timedreceive
	syscall
	ret
;
%define SC_mq_notify 244
global _s_mq_notify

_s_mq_notify:
	mov		rax, SC_mq_notify
	syscall
	ret
;
%define SC_mq_getsetattr 245
global _s_mq_getsetattr

_s_mq_getsetattr:
	mov		rax, SC_mq_getsetattr
	syscall
	ret
;
%define SC_kexec_load 246
global _s_kexec_load

_s_kexec_load:
	mov		rax, SC_kexec_load
	syscall
	ret
;
%define SC_waitid 247
global _s_waitid

_s_waitid:
	mov		rax, SC_waitid
	syscall
	ret
;
%define SC_add_key 248
global _s_add_key

_s_add_key:
	mov		rax, SC_add_key
	syscall
	ret
;
%define SC_request_key 249
global _s_request_key

_s_request_key:
	mov		rax, SC_request_key
	syscall
	ret
;
%define SC_keyctl 250
global _s_keyctl

_s_keyctl:
	mov		rax, SC_keyctl
	syscall
	ret
;
%define SC_ioprio_set 251
global _s_ioprio_set

_s_ioprio_set:
	mov		rax, SC_ioprio_set
	syscall
	ret
;
%define SC_ioprio_get 252
global _s_ioprio_get

_s_ioprio_get:
	mov		rax, SC_ioprio_get
	syscall
	ret
;
%define SC_inotify_init 253
global _s_inotify_init

_s_inotify_init:
	mov		rax, SC_inotify_init
	syscall
	ret
;
%define SC_inotify_add_watch 254
global _s_inotify_add_watch

_s_inotify_add_watch:
	mov		rax, SC_inotify_add_watch
	syscall
	ret
;
%define SC_inotify_rm_watch 255
global _s_inotify_rm_watch

_s_inotify_rm_watch:
	mov		rax, SC_inotify_rm_watch
	syscall
	ret
;
%define SC_migrate_pages 256
global _s_migrate_pages

_s_migrate_pages:
	mov		rax, SC_migrate_pages
	syscall
	ret
;
%define SC_openat 257
global _s_openat

_s_openat:
	mov		rax, SC_openat
	syscall
	ret
;
%define SC_mkdirat 258
global _s_mkdirat

_s_mkdirat:
	mov		rax, SC_mkdirat
	syscall
	ret
;
%define SC_mknodat 259
global _s_mknodat

_s_mknodat:
	mov		rax, SC_mknodat
	syscall
	ret
;
%define SC_fchownat 260
global _s_fchownat

_s_fchownat:
	mov		rax, SC_fchownat
	syscall
	ret
;
%define SC_futimesat 261
global _s_futimesat

_s_futimesat:
	mov		rax, SC_futimesat
	syscall
	ret
;
%define SC_newfstatat 262
global _s_newfstatat

_s_newfstatat:
	mov		rax, SC_newfstatat
	syscall
	ret
;
%define SC_unlinkat 263
global _s_unlinkat

_s_unlinkat:
	mov		rax, SC_unlinkat
	syscall
	ret
;
%define SC_renameat 264
global _s_renameat

_s_renameat:
	mov		rax, SC_renameat
	syscall
	ret
;
%define SC_linkat 265
global _s_linkat

_s_linkat:
	mov		rax, SC_linkat
	syscall
	ret
;
%define SC_symlinkat 266
global _s_symlinkat

_s_symlinkat:
	mov		rax, SC_symlinkat
	syscall
	ret
;
%define SC_readlinkat 267
global _s_readlinkat

_s_readlinkat:
	mov		rax, SC_readlinkat
	syscall
	ret
;
%define SC_fchmodat 268
global _s_fchmodat

_s_fchmodat:
	mov		rax, SC_fchmodat
	syscall
	ret
;
%define SC_faccessat 269
global _s_faccessat

_s_faccessat:
	mov		rax, SC_faccessat
	syscall
	ret
;
%define SC_pselect6 270
global _s_pselect6

_s_pselect6:
	mov		rax, SC_pselect6
	syscall
	ret
;
%define SC_ppoll 271
global _s_ppoll

_s_ppoll:
	mov		rax, SC_ppoll
	syscall
	ret
;
%define SC_unshare 272
global _s_unshare

_s_unshare:
	mov		rax, SC_unshare
	syscall
	ret
;
%define SC_set_robust_list 273
global _s_set_robust_list

_s_set_robust_list:
	mov		rax, SC_set_robust_list
	syscall
	ret
;
%define SC_get_robust_list 274
global _s_get_robust_list

_s_get_robust_list:
	mov		rax, SC_get_robust_list
	syscall
	ret
;
%define SC_splice 275
global _s_splice

_s_splice:
	mov		rax, SC_splice
	syscall
	ret
;
%define SC_tee 276
global _s_tee

_s_tee:
	mov		rax, SC_tee
	syscall
	ret
;
%define SC_sync_file_range 277
global _s_sync_file_range

_s_sync_file_range:
	mov		rax, SC_sync_file_range
	syscall
	ret
;
%define SC_vmsplice 278
global _s_vmsplice

_s_vmsplice:
	mov		rax, SC_vmsplice
	syscall
	ret
;
%define SC_move_pages 279
global _s_move_pages

_s_move_pages:
	mov		rax, SC_move_pages
	syscall
	ret
;
%define SC_utimensat 280
global _s_utimensat

_s_utimensat:
	mov		rax, SC_utimensat
	syscall
	ret
;
%define SC_epoll_pwait 281
global _s_epoll_pwait

_s_epoll_pwait:
	mov		rax, SC_epoll_pwait
	syscall
	ret
;
%define SC_signalfd 282
global _s_signalfd

_s_signalfd:
	mov		rax, SC_signalfd
	syscall
	ret
;
%define SC_timerfd_create 283
global _s_timerfd_create

_s_timerfd_create:
	mov		rax, SC_timerfd_create
	syscall
	ret
;
%define SC_eventfd 284
global _s_eventfd

_s_eventfd:
	mov		rax, SC_eventfd
	syscall
	ret
;
%define SC_fallocate 285
global _s_fallocate

_s_fallocate:
	mov		rax, SC_fallocate
	syscall
	ret
;
%define SC_timerfd_settime 286
global _s_timerfd_settime

_s_timerfd_settime:
	mov		rax, SC_timerfd_settime
	syscall
	ret
;
%define SC_timerfd_gettime 287
global _s_timerfd_gettime

_s_timerfd_gettime:
	mov		rax, SC_timerfd_gettime
	syscall
	ret
;
%define SC_accept4 288
global _s_accept4

_s_accept4:
	mov		rax, SC_accept4
	syscall
	ret
;
%define SC_signalfd4 289
global _s_signalfd4

_s_signalfd4:
	mov		rax, SC_signalfd4
	syscall
	ret
;
%define SC_eventfd2 290
global _s_eventfd2

_s_eventfd2:
	mov		rax, SC_eventfd2
	syscall
	ret
;
%define SC_epoll_create1 291
global _s_epoll_create1

_s_epoll_create1:
	mov		rax, SC_epoll_create1
	syscall
	ret
;
%define SC_dup3 292
global _s_dup3

_s_dup3:
	mov		rax, SC_dup3
	syscall
	ret
;
%define SC_pipe2 293
global _s_pipe2

_s_pipe2:
	mov		rax, SC_pipe2
	syscall
	ret
;
%define SC_inotify_init1 294
global _s_inotify_init1

_s_inotify_init1:
	mov		rax, SC_inotify_init1
	syscall
	ret
;
%define SC_preadv 295
global _s_preadv

_s_preadv:
	mov		rax, SC_preadv
	syscall
	ret
;
%define SC_pwritev 296
global _s_pwritev

_s_pwritev:
	mov		rax, SC_pwritev
	syscall
	ret
;
%define SC_rt_tgsigqueueinfo 297
global _s_rt_tgsigqueueinfo

_s_rt_tgsigqueueinfo:
	mov		rax, SC_rt_tgsigqueueinfo
	syscall
	ret
;
%define SC_perf_event_open 298
global _s_perf_event_open

_s_perf_event_open:
	mov		rax, SC_perf_event_open
	syscall
	ret
;
%define SC_recvmmsg 299
global _s_recvmmsg

_s_recvmmsg:
	mov		rax, SC_recvmmsg
	syscall
	ret
;
%define SC_fanotify_init 300
global _s_fanotify_init

_s_fanotify_init:
	mov		rax, SC_fanotify_init
	syscall
	ret
;
%define SC_fanotify_mark 301
global _s_fanotify_mark

_s_fanotify_mark:
	mov		rax, SC_fanotify_mark
	syscall
	ret
;
%define SC_prlimit64 302
global _s_prlimit64

_s_prlimit64:
	mov		rax, SC_prlimit64
	syscall
	ret
;
%define SC_name_to_handle_at 303
global _s_name_to_handle_at

_s_name_to_handle_at:
	mov		rax, SC_name_to_handle_at
	syscall
	ret
;
%define SC_open_by_handle_at 304
global _s_open_by_handle_at

_s_open_by_handle_at:
	mov		rax, SC_open_by_handle_at
	syscall
	ret
;
%define SC_clock_adjtime 305
global _s_clock_adjtime

_s_clock_adjtime:
	mov		rax, SC_clock_adjtime
	syscall
	ret
;
%define SC_syncfs 306
global _s_syncfs

_s_syncfs:
	mov		rax, SC_syncfs
	syscall
	ret
;
%define SC_sendmmsg 307
global _s_sendmmsg

_s_sendmmsg:
	mov		rax, SC_sendmmsg
	syscall
	ret
;
%define SC_setns 308
global _s_setns

_s_setns:
	mov		rax, SC_setns
	syscall
	ret
;
%define SC_getcpu 309
global _s_getcpu

_s_getcpu:
	mov		rax, SC_getcpu
	syscall
	ret
;
%define SC_process_vm_readv 310
global _s_process_vm_readv

_s_process_vm_readv:
	mov		rax, SC_process_vm_readv
	syscall
	ret
;
%define SC_process_vm_writev 311
global _s_process_vm_writev

_s_process_vm_writev:
	mov		rax, SC_process_vm_writev
	syscall
	ret
;
%define SC_kcmp 312
global _s_kcmp

_s_kcmp:
	mov		rax, SC_kcmp
	syscall
	ret
;
%define SC_finit_module 313
global _s_finit_module

_s_finit_module:
	mov		rax, SC_finit_module
	syscall
	ret
;
%define SC_sched_setattr 314
global _s_sched_setattr

_s_sched_setattr:
	mov		rax, SC_sched_setattr
	syscall
	ret
;
%define SC_sched_getattr 315
global _s_sched_getattr

_s_sched_getattr:
	mov		rax, SC_sched_getattr
	syscall
	ret
;
%define SC_renameat2 316
global _s_renameat2

_s_renameat2:
	mov		rax, SC_renameat2
	syscall
	ret
;
%define SC_seccomp 317
global _s_seccomp

_s_seccomp:
	mov		rax, SC_seccomp
	syscall
	ret
;
%define SC_getrandom 318
global _s_getrandom

_s_getrandom:
	mov		rax, SC_getrandom
	syscall
	ret
;
%define SC_memfd_create 319
global _s_memfd_create

_s_memfd_create:
	mov		rax, SC_memfd_create
	syscall
	ret
;
%define SC_kexec_file_load 320
global _s_kexec_file_load

_s_kexec_file_load:
	mov		rax, SC_kexec_file_load
	syscall
	ret
;
%define SC_bpf 321
global _s_bpf

_s_bpf:
	mov		rax, SC_bpf
	syscall
	ret
;
%define SC_execveat 322
global _s_execveat

_s_execveat:
	mov		rax, SC_execveat
	syscall
	ret
;
%define SC_userfaultfd 323
global _s_userfaultfd

_s_userfaultfd:
	mov		rax, SC_userfaultfd
	syscall
	ret
;
%define SC_membarrier 324
global _s_membarrier

_s_membarrier:
	mov		rax, SC_membarrier
	syscall
	ret
;
%define SC_mlock2 325
global _s_mlock2

_s_mlock2:
	mov		rax, SC_mlock2
	syscall
	ret
;
%define SC_copy_file_range 326
global _s_copy_file_range

_s_copy_file_range:
	mov		rax, SC_copy_file_range
	syscall
	ret
;
%define SC_preadv2 327
global _s_preadv2

_s_preadv2:
	mov		rax, SC_preadv2
	syscall
	ret
;
%define SC_pwritev2 328
global _s_pwritev2

_s_pwritev2:
	mov		rax, SC_pwritev2
	syscall
	ret
;
%define SC_pkey_mprotect 329
global _s_pkey_mprotect

_s_pkey_mprotect:
	mov		rax, SC_pkey_mprotect
	syscall
	ret
;
%define SC_pkey_alloc 330
global _s_pkey_alloc

_s_pkey_alloc:
	mov		rax, SC_pkey_alloc
	syscall
	ret
;
%define SC_pkey_free 331
global _s_pkey_free

_s_pkey_free:
	mov		rax, SC_pkey_free
	syscall
	ret
;
%define SC_statx 332
global _s_statx

_s_statx:
	mov		rax, SC_statx
	syscall
	ret
;
%define SC_io_pgetevents 333
global _s_io_pgetevents

_s_io_pgetevents:
	mov		rax, SC_io_pgetevents
	syscall
	ret
;
%define SC_rseq 334
global _s_rseq

_s_rseq:
	mov		rax, SC_rseq
	syscall
	ret
;
%define SC_pidfd_send_signal 424
global _s_pidfd_send_signal

_s_pidfd_send_signal:
	mov		rax, SC_pidfd_send_signal
	syscall
	ret
;
%define SC_io_uring_setup 425
global _s_io_uring_setup

_s_io_uring_setup:
	mov		rax, SC_io_uring_setup
	syscall
	ret
;
%define SC_io_uring_enter 426
global _s_io_uring_enter

_s_io_uring_enter:
	mov		rax, SC_io_uring_enter
	syscall
	ret
;
%define SC_io_uring_register 427
global _s_io_uring_register

_s_io_uring_register:
	mov		rax, SC_io_uring_register
	syscall
	ret
;
%define SC_open_tree 428
global _s_open_tree

_s_open_tree:
	mov		rax, SC_open_tree
	syscall
	ret
;
%define SC_move_mount 429
global _s_move_mount

_s_move_mount:
	mov		rax, SC_move_mount
	syscall
	ret
;
%define SC_fsopen 430
global _s_fsopen

_s_fsopen:
	mov		rax, SC_fsopen
	syscall
	ret
;
%define SC_fsconfig 431
global _s_fsconfig

_s_fsconfig:
	mov		rax, SC_fsconfig
	syscall
	ret
;
%define SC_fsmount 432
global _s_fsmount

_s_fsmount:
	mov		rax, SC_fsmount
	syscall
	ret
;
%define SC_fspick 433
global _s_fspick

_s_fspick:
	mov		rax, SC_fspick
	syscall
	ret
;
%define SC_pidfd_open 434
global _s_pidfd_open

_s_pidfd_open:
	mov		rax, SC_pidfd_open
	syscall
	ret
;
%define SC_clone3 435
global _s_clone3

_s_clone3:
	mov		rax, SC_clone3
	syscall
	ret
;
