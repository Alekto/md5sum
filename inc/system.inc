%ifndef __SYSTEM_INC
%define __SYSTEM_INC

%ifndef __LINUX__
%endif

%ifndef __ELF__
%endif

%assign	__O_SIZE__	0
%assign	__O_SPEED__	1

%ifndef __OPTIMIZE__
%assign	__OPTIMIZE__ __O_SIZE__	
%endif

%if __OPTIMIZE__=__O_SPEED__
%endif

%assign	__S_KERNEL__	0

%ifndef __SYSCALL__
%endif

%include "includes.inc"

%ifdef	__LINUX__
%include "os_linux.inc"
%endif

%include "syscall.inc"

%ifdef __ELF_MACROS__
%include "elf.inc"
%endif

%ifdef __STARTUP__
%define START _start_asm
%endif

%macro CODESEG 0
%ifdef __ELF_MACROS__
BEGIN_ELF
%endif	

SYSCALL_GATE

%ifdef __STARTUP__
%if	__SYSCALL__=__S_LIBC__
%assign	__S	4
	global	main
main:
	mov	ebp,esp
	xor	edx,edx
	push	edx
.__env:
	push	edx
	xor	ecx,ecx
	mov	eax,[ebp + __S + 8]
	or	eax,eax
	jz	.__argv
.__find_env:
	cmp	[eax],edx
	jz	.__push_env
	inc	ecx
	add	eax,byte 4
	jmp	short .__find_env
.__push_env:
	sub	eax,byte 4
	push	dword [eax]
	loop	.__push_env
.__argv:
	push	edx
	xor	ecx,ecx
	mov	eax,[ebp + __S + 4]
	or	eax,eax
	jz	.__argc
.__find_arg:
	cmp	[eax],edx
	jz	.__push_arg
	inc	ecx
	add	eax,byte 4
	jmp	short .__find_arg
.__push_arg:
	sub	eax,byte 4
	push	dword [eax]
	loop	.__push_arg
.__argc:
	mov	eax,[ebp + __S]
	push	eax
	xor	eax,eax
	xor	ecx,ecx
	xor	ebp,ebp
	jmp	START
%elifdef	__BEOS__

	global	_start
_start:
%endif

%endif	
%endmacro

%macro UDATASEG 0
%ifdef __ELF_MACROS__
ELF_DATA
%endif
%endmacro

%macro DATASEG 0
%ifndef __ELF_MACROS__
%endif

%endif
%endmacro

%macro END 0
%ifdef __ELF_MACROS__
END_ELF
%endif
_end:		
%endmacro

%macro I_STRUC 1
%ifdef __ELF_MACROS__
ELF_ISTRUC %1
%endif
%endmacro

%ifdef __ELF_MACROS__
%define	B_STRUC ELF_BSTRUC
%endif

%define	jmps jmp short
%macro _jmp 1
%%__offset_%1 equ $-%1
%assign __offset__ %%__offset_%1
%if (__offset__<0) && (__offset__>0xFFFFFF80)
	jmp	short %1
%elif (__offset__>0) && (__offset__<0x80)
	jmp	short %1
%else
	jmp	%1
%endif
%endmacro

%macro _mov 2-3
%ifnidn	%2,EMPTY
 %if __OPTIMIZE__=__O_SPEED__
    %ifid %2
	mov	%1,%2
    %elifnum %2
     %if %2=0
	sub	%1,%1
     %else
	mov	%1,%2
     %endif
    %else
	mov	%1,%2
    %endif
 %else			
    %ifid %2
     %ifnidni %1,%2
	mov	%1,%2
     %endif
    %elifstr %2
	mov	%1,%2
    %elifnum %2
     %if %2=0
	xor	%1,%1
     %elif %2<0 && %2>0xffffff7f
	push	byte %2
	pop	%1
     %elif %2<0
	mov	%1,%2
     %elif %2<0x80
	push	byte %2
	pop	%1
     %else
	mov	%1,%2
     %endif
    %else
	mov	%1,%2
    %endif
 %endif
%endif
%endmacro

%endif
