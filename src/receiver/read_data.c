/*-------------------------------------------------------------------------\
| run_server.c                                                            |
|                                                                          |
| This file is part of libselserv                                          |
|                                                                          |
| libselserv is free software; you can redistribute it and/or modify       |
| it under the terms of the GNU General Public License as published by     |
| the Free Software Foundation; either version 2 of the License, or        |
| (at your option) any later version.                                      |
|                                                                          |
| libselserv is distributed in the hope that it will be usedful,           |
| but WITHOUT ANY WARRANTY; without even the implied warranty of           |
| MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the             |
| GNU General Public License for more details.                             |
|                                                                          |
| You should have received a copy of the GNU General Public License        |
| along with libselserv; if not, write to the Free Software                |
| Foundation, Inc ., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA |
|---------------------------------------------------------------------------
| run_server.c Documentation
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
  int n;

  /* Recv what we can */
  n = recv (client->sd, client->tmp_buf + client->bytes_held,
            PACKET_SIZE * 2 - client->bytes_held, 0);
  if (n == -1)
    error_at_line (1, errno, __FILE__, __LINE__,
                   "%s", "recv()");

  /* Adjust the number of bytes we have */
  client->bytes_held += n;

  /* If we have a complete packet, copy it to read_buf
     and readjust tmp_buf. This should really be a
     circular buffer, but that's just too much work */
  if (client->bytes_held >= PACKET_SIZE)
    {
      /* Copy packet to read_buf, and set that
         we have a complete packet ready */
      memcpy (client->read_buf, client->tmp_buf, PACKET_SIZE);
      client->have_packet = true;

      /* Adjust how many bytes we are holding */
      client->bytes_held -= PACKET_SIZE;

      /* Move remainder of tmp_buf to beginning */
      memcpy (client->tmp_buf, client->tmp_buf + PACKET_SIZE, client->bytes_held);
    }

  return (0);
}
