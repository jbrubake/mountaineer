/*-------------------------------------------------------------------------\
| log_data.c                                                               |
|                                                                          |
| This file is part of mountaineer                                         |
|                                                                          |
| mountaineer is free software; you can redistribute it and/or modify      |
| it under the terms of the GNU General Public License as published by     |
| the Free Software Foundation; either version 2 of the License, or        |
| (at your option) any later version.                                      |
|                                                                          |
| mountaineer is distributed in the hope that it will be useful,           |
| but WITHOUT ANY WARRANTY; without even the implied warranty of           |
| MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the             |
| GNU General Public License for more details.                             |
|                                                                          |
| You should have received a copy of the GNU General Public License        |
| along with libselserv; if not, write to the Free Software                |
| Foundation, Inc ., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA |
|---------------------------------------------------------------------------
| log_data.c Documentation
|
\-------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>

#include "cbase/xmalloc.h"
#include "cbase/error.h"
#include "cbase/common.h"
#include "server.h"

int
log_data (struct CLIENT *client)
{
  /* Print the data */
  char *token = strtok (client->read_buf
                        + PACKET_TYPE + 1, "%");
  while (token != NULL)
    {
      fprintf (client->output, "%s\n", token);
      token = strtok (NULL, "%");
    }

  /* Flush the data */
  fflush (client->output);

  return (0);
}
