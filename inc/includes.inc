%ifndef	__SYSTEM_INC
%endif

%assign	NULL	0

%assign TRUE	1
%assign FALSE	0

%assign	STDIN	0
%assign	STDOUT	1
%assign	STDERR	2

%assign	EOL	0

%assign	__a	0x07
%assign	__b	0x08
%assign	__e	0x1b
%assign	__f	0x0c
%assign	__n	0x0a
%assign	__r	0x0d
%assign	__t	0x09
%assign	__v	0x0b
%assign	__s	0x20

%define		INT		resd
%define		UINT		resd
%define		LONG		resd
%define		ULONG		resd
%define 	SHORT		resw
%define		USHORT		resw
%define		CHAR		resb
%define		UCHAR		resb
%define		BYTE		resb
%define		WORD		resw
%define		DWORD		resd
%define		U8		resb
%define		U16		resw
%define		U32		resd

%assign O_RDONLY	0

