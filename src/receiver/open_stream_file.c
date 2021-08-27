/*-------------------------------------------------------------------------\
| open_stream_file.c                                                       |
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
| open_stream_file.c Documentation
|
\-------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>

#include "cbase/xmalloc.h"
#include "cbase/error.h"
#include "cbase/common.h"
#include "server.h"

int
open_stream_file (struct CLIENT *client)
{
  /* Set the stream name */
  client->name = xmalloc (char, strlen (client->read_buf
                                        + PACKET_TYPE + 1));
  strcpy (client->name, client->read_buf + PACKET_TYPE + 1);

  /* Open the stream data file */
  client->output = fopen (client->name, "a");

  /* Print a header */
  fprintf (client->output, "%s : Started at %s\n\n", client->name,
           timestamp ("%d%H%M%B%Y"));

  /* Flush the data */
  fflush (client->output);

  return (0);
}
