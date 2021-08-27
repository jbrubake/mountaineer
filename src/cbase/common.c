/*-------------------------------------------------------------------------\
| common.c                                                                 |
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
| common.c Documentation
|
\-------------------------------------------------------------------------*/

#if HAVE_CONFIG_H
#  include <config.h>
#endif

#include <time.h>

#include "cbase/common.h"

const char *
timestamp (const char *format)
{
  static char buf[1024];
  time_t thetime = time (NULL);
  strftime (buf, 1024, format, localtime (&thetime));
  return (buf);
}
