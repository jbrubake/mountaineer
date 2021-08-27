/*-------------------------------------------------------------------------\
| read_data.c                                                              |
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
| read_data.c Documentation
|
\-------------------------------------------------------------------------*/

#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>

#include "cbase/error.h"
#include "cbase/common.h"
#include "server.h"

int
read_data (struct CLIENT *client)
{
  int n = 0;

  /* Recv what we can */
  n = recv (client->sd, client->read_buf + client->bytes_held,
            PACKET_SIZE * 2 - client->bytes_held, 0);
#include <stdlib.h>
  if (n == 0)
    exit (0);

  if (n == -1)
    error_at_line (1, errno, __FILE__, __LINE__,
                   "%s", "recv()");

  /* Adjust the number of bytes we have */
  client->bytes_held += n;

  /* Null terminate the data */
  client->read_buf[n] = '\0';

  return (0);
}
