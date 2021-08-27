/*-------------------------------------------------------------------------\
| common.h                                                                 |
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
| common.h Documentation
|
| Provides standard declarations for all projects
\-------------------------------------------------------------------------*/

#ifndef COMMON_H
#define COMMON_H

#if HAVE_CONFIG_H
#  include <config.h>
#endif

#ifdef __cplusplus
#  define BEGIN_C_DECLS extern "C" {
#  define END_C_DECLS   }
#else
#  define BEGIN_C_DECLS
#  define END_C_DECLS
#endif

typedef int bool;
#define false 0
#define true 1

BEGIN_C_DECLS

const char *timestamp (const char *format);
char *chomp (char *string);

END_C_DECLS

#endif /* !COMMON_H */
