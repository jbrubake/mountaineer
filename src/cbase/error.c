/*-------------------------------------------------------------------------\
| error.c                                                                  |
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
| error.c Documentation
|
\-------------------------------------------------------------------------*/

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

#include "cbase/error.h"

/* This is defined in GNU libc */
extern char *program_invocation_name;
#define program_name program_invocation_name

void
error_ (int status, int errnum, const char *format, ...)
{
  va_list ap;
  /* Use static buffers so we don't run the risk of
     ENOMEM (this is an error handler after all) */
  static char buf[2048];
  static char message[1024];

  /* Create user part of error message */
  va_start (ap, format);
  vsprintf (message, format, ap);
  va_end (ap);

  /* Prepend program name */
  sprintf (buf, "%s: %s", program_name, message);

  /* Append system error message if requested */
  if (errnum)
      sprintf (buf, "%s: %s", buf, strerror (errnum));

  /* Call client handler with error message */
  error_handler (buf);

  error_message_count++;

  if (status)
    exit (status);
}

void
error_at_line (int status, int errnum, const char *file_name,
               unsigned int line_number, const char *format, ...)
{
  va_list ap;
  /* Use static buffers so we don't run the risk of
     ENOMEM (this is an error handler after all) */
  static char buf[2048];
  static char message[1024];

  /* If the user only wants one error per line, see
     if we still need to print this error */
  if (error_one_per_line)
    {
      static const char *old_file_name;
      static unsigned int old_line_number;

      if (old_line_number == line_number
          && (file_name == old_file_name
              || strcmp (old_file_name, file_name) == 0))
        /* Simply return and print nothing */
        return;
    }

  /* Create user part of error message */
  va_start (ap, format);
  vsprintf (message, format, ap);
  va_end (ap);

  /* Prepend program name, filename and line number*/
  sprintf (buf, "%s:%s:%d: %s", program_name, file_name, line_number, message);

  /* Append system error message if requested */
  if (errnum)
      sprintf (buf, "%s: %s", buf, strerror (errnum));

  /* Call client handler with error message */
  error_handler (buf);

  error_message_count++;

  if (status)
    exit (status);
}
