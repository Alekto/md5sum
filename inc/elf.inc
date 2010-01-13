%ifndef __ELF_INC
%define __ELF_INC

%macro BEGIN_ELF 0
%push elf
BITS 32

%assign ELFOSABI_LINUX		3	

%ifdef		__LINUX__
%assign %$osabi	ELFOSABI_LINUX
%endif

%assign	%$origin	0x08048000

		org	%$origin
		db	0x7F, 'ELF'		
		db	1, 1, 1
		db	%$osabi			
	times 8	db	0
		dw	2			
		dw	3			
		dd	1			
		dd	START			
		dd	%%phdr - $$		
		dd	0			
		dd	0			
		dw	0x34			
		dw	0x20			
%%phdr:		dw	1			
		dw	0			
		dw	0			
		dw	0			
		dd	$$					
		dd	$$					
		dd	_elf_filesz				
		dd	_elf_memsz				
		dd	_elf_phdr_flags
		dd	0x1000					
_text:
%endmacro


%macro ELF_DATA 0
%repl elfdata
_elf_filesz	equ	$ - $$
[absolute %$origin + _elf_filesz]
_data:
%endmacro

%macro ELF_ISTRUC 1
%push elf_istruc
%define	%$strucname %1
%$strucstart:
%endmacro

%macro ELF_BSTRUC 1-*
%push foo
%define %$strucname %1
%%top_%$strucname:
%rep %0 - 1
%rotate 1
resb %{$strucname}%1 - ($ - %%top_%$strucname)
%1:
%endrep
resb %{$strucname}_size - ($ - %%top_%$strucname)
%pop
%endmacro

%macro END_ELF 0
_elf_memsz	equ	$ - %$origin
%ifctx elfdata
_elf_phdr_flags	equ	7
%endif
%pop
%endmacro

%endif
