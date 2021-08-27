/*-------------------------------------------------------------------------\
| xmalloc.c                                                                |
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
| xmalloc.c Documentation
|
| Memory management wrapper function definitions.
\-------------------------------------------------------------------------*/

#if HAVE_CONFIG_H
#  include <config.h>
#endif

#include <malloc.h>
#include <errno.h>

#include "cbase/common.h"
#include "cbase/error.h"
#include "cbase/xmalloc.h"

/*-------------------------------------------------*\
| xmalloc_
|
| Provides a wrapper for malloc() that handles
| error checking.
|
| Parameters:
|     size_t num : Number of bytes to allocate
|     char *file : Filename where xmalloc was called
|     int line   : Linenumber where xmalloc was called
| Returns:
|     Pointer to allocated memory
\*-------------------------------------------------*/
void *
xmalloc_ (size_t num, const char *file, int line)
{
  void *new = malloc (num);
  if (!new)
    error_at_line (1, errno, file, line, "%s", "xmalloc");

  return new;
}

/*-------------------------------------------------*\
| xrealloc_
|
| Provides a wrapper for realloc() that handles
| error checking.
|
| Parameters:
|     void *p    : Pointer to memory to reallocate
|     size_t num : Size to allocate
|     char *file : Filename where xrealloc was called
|     int line   : Linenumber where xrealloc was called
| Returns:
|     Pointer to allocated memory
\*-------------------------------------------------*/
void *
xrealloc_ (void *p, size_t num, const char *file, int line)
{
  void *new;

  if(!p)
    return xmalloc_ (num, file, line);

  new = realloc (p, num);
  if (!new)
    error_at_line (1, errno, file, line, "%s", "xrealloc");

  return new;
}

/*-------------------------------------------------*\
| xcalloc_
|
| Provides a wrapper for calloc that handles
| error checking.
|
| Parameters:
|     size_t num  : Number of elements to allocate
|     size_t size : Size of each element
|     char *file  : Filename where xcalloc was called
|     int line    : Linenumber where xcalloc was called
| Returns:
|     Pointer to allocated memory
\*-------------------------------------------------*/
void *
xcalloc_ (size_t num, size_t size, const char *file, int line)
{
  void *new = calloc (num, size);
  if (!new)
    error_at_line (1, errno, file, line, "%s", "xcalloc");

  return new;
}
