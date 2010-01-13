%ifndef	__SYSTEM_INC
%endif

%macro	__push_syscall_args 1
%assign	P %1
%if P>0
 %if P>1
  %if P>2
   %if P>3
    %if P>4
     %if P>5
	push	ebp
     %endif
	push	edi
    %endif
	push	esi
  %endif
	push	edx
  %endif
	push	ecx
 %endif
	push	ebx
%endif
%endmacro

%macro	__syscall 2-9

%if %0>2
%if %3>0
 %if %3>1
  %if %3>2
   %if %3>3
    %if %3>4
     %if %3>5
	_mov	ebp,%9
     %endif
	_mov	edi,%8
    %endif
	_mov	esi,%7
   %endif
	_mov	edx,%6
  %endif
	_mov	ecx,%5
 %endif
	_mov	ebx,%4
%endif
%if %3 < %2
%assign __ARGS %2
%else
%assign __ARGS %3
%endif
%else
%assign __ARGS %2
%endif

%if	__SYSCALL__=__S_KERNEL__
	_mov	eax,SYS_%{1}

%ifdef __LINUX__
	DO_SYSCALL
%endif	

%elif	__SYSCALL__=__S_LIBC__
	__push_syscall_args __ARGS
%endif	
%endmacro

%define SYS_eax	eax

%macro sys_generic 0-6
	__syscall eax, 6, %0, %1, %2, %3, %4, %5, %6
%endmacro

%macro sys_read 0-3
	__syscall read, 3, %0, %1, %2, %3
%endmacro

%macro sys_write 0-3
	__syscall write, 3, %0, %1, %2, %3
%endmacro

%macro sys_chmod 0-2
	__syscall chmod, 2, %0, %1, %2
%endmacro

%macro sys_open 0-3
	__syscall open, 3, %0, %1, %2, %3
%endmacro

%macro sys_close 0-1
	__syscall close, 1, %0, %1
%endmacro

%macro sys_select 0-5
	__syscall select, 5, %0, %1, %2, %3, %4, %5
%endmacro

%macro sys_exit 0-1
	__syscall exit, 1, %0, %1
%endmacro

%macro sys_exit_true 0
	sys_exit 0
%endmacro

%macro sys_exit_false 0
	sys_exit 1
%endmacro


