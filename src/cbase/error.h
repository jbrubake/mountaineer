/*-------------------------------------------------------------------------\
| error.h                                                                  |
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
| error.h Documentation
|
\-------------------------------------------------------------------------*/

#ifndef ERROR_H
#define ERROR_H

#include <errno.h>
#include <cbase/common.h>

#define error error_

BEGIN_C_DECLS

void error_ (int status, int errnum, const char *format, ...);
void error_at_line (int status, int errnum, const char *file_name,
                    unsigned int line_number, const char *format, ...);
extern void error_handler (const char *message);

unsigned int error_message_count;
int error_one_per_line;

END_C_DECLS

#endif /* !ERROR_H */
