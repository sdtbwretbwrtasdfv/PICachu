#pragma once


/* Cast as a function / variable / string in a specific region of memory */
#define D_SEC( x )	__attribute__(( section( ".text$" #x ) ))

/* Cast as a pointer with the specified typedef */
#define D_API( x )	__typeof__( x ) * x

/* Cast as a pointer-wide integer */
#define U_PTR( x )	( ( ULONG_PTR) x )

/* Cast as a pointer */
#define C_PTR( x )	( ( PVOID ) x )
