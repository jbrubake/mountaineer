/*-------------------------------------------------------------------------\
| process_data.c                                                           |
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
| process_data.c Documentation
|
\-------------------------------------------------------------------------*/

#include <stdlib.h>
#include <string.h>

#include "cbase/xmalloc.h"
#include "protocol.h"
#include "server.h"

int
process_data (struct CLIENT *client)
{
  switch (client->read_buf[PACKET_TYPE])
    {
    case STREAM_INFO_PACKET:
      if (open_stream_file (client) == -1)
        error_at_line (1, errno, __FILE__, __LINE__,
                       "%s", "open_stream_file()");
      break;

    case DATA_PACKET:
      log_data (client);
      break;
    }

  // Zero the buffer
  strcpy (client->read_buf, "");
  client->bytes_held = 0;

  return (0);
}
