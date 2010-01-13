%ifndef __SYSTEM_INC
%endif

%macro	DO_SYSCALL 0
	int	0x80
%endmacro

%macro	SYSCALL_GATE 0
%endmacro

%assign SYS_exit		1
%assign SYS_fork		2
%assign SYS_read		3
%assign SYS_write		4
%assign SYS_open		5
%assign SYS_close		6
%assign SYS_chmod		15

