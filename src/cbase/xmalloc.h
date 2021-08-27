/*-------------------------------------------------------------------------\
| xmalloc.h                                                                |
|                                                                          |
| This file is part of libcbase                                            |
|                                                                          |
| libcbase is free software; you can redistribute it and/or modify         |
| it under the terms of the GNU General Public License as published by     |
| the Free Software Foundation; either version 2 of the License, or        |
| (at your option) any later version.                                      |
|                                                                          |
| libcbase is distributed in the hope that it will be usedful,             |
| but WITHOUT ANY WARRANTY; without even the implied warranty of           |
| MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the             |
| GNU General Public License for more details.                             |
|                                                                          |
| You should have received a copy of the GNU General Public License        |
| along with libcbase; if not, write to the Free Software                  |
| Foundation, Inc ., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA |
|---------------------------------------------------------------------------
| xmalloc.h Documentation
|
| SYNOPSIS
|     Memory management wrappers that do error handling.
|
| DESCRIPTION
|     Provides xmalloc, xcalloc, xrealloc and xfree. These are macros that
|     allow you to call the corresponding wrappers with more sensible parameters.
|
| USAGE
|     xmalloc (TYPE, NUM) : TYPE = type to allocate
|                           NUM = number of TYPE to allocate
|     xcalloc (TYPE, NUM) : TYPE = type to allocate
|                           NUM = number of TYPE to allocate
|     xrealloc (TYPE, P, NUM) : TYPE = type to allocate
|                               P = pointer to memory to reallocate
|                               NUM = number of TYPE to allocate
|     xfree (P) : P = pointer to memory to free
\-------------------------------------------------------------------------*/

#ifndef XMALLOC_H
#define XMALLOC_H

#if HAVE_CONFIG_H
#  include <config.h>
#endif

#include <malloc.h>
#include <cbase/common.h>

/* Macros to allow calling x*alloc with more sensible parameters */
#define xcalloc(type, num)                                 \
        ((type *) xcalloc_ ((num), sizeof(type), (__FILE__), (__LINE__)))
#define xmalloc(type, num)                                 \
        ((type *) xmalloc_ ((num) * sizeof(type), (__FILE__), (__LINE__)))
#define xrealloc(type, p, num)                             \
        ((type *) xrealloc_ ((p), (num) * sizeof(type), (__FILE__), (__LINE__)))
#define xfree(stale)                           do {        \
        if (stale) { free (stale); stale = 0; }            \
                                               } while (0)

BEGIN_C_DECLS

/*-------------------------------------------------*\
| xcalloc, xmalloc and xrealloc
|
| Wrappers to provide error handling for memory
| management functions
|
| Parameters:
|     Same as calloc(), malloc() and realloc() plus:
|     const char *file : File where x*alloc() was called
|     int line         : Line where x*alloc() was called
| Returns:
|     Pointer to allocated memory
\*-------------------------------------------------*/
void *xcalloc_   (size_t num, size_t size, const char *file, int line);
void *xmalloc_   (size_t num, const char *file, int line);
void *xrealloc_  (void *p, size_t num, const char *file, int line);

END_C_DECLS

#endif /* !XMALLOC_H */
