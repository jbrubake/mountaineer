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

#include <stdlib.h>
#include <string.h>

#include "cbase/xmalloc.h"
#include "protocol.h"
#include "server.h"

int
process_data (struct CLIENT *client)
{
  char *tmp;

  switch (client->read_buf[PACKET_TYPE])
    {
    case STREAM_INFO_PACKET:

      tmp = strtok (client->read_buf, ":");
      client->desc = xmalloc (char, strlen (tmp));
      strcpy (client->desc, tmp);

      tmp = strtok (NULL, ":");
      client->name = xmalloc (char, strlen (tmp));
      strcpy (client->name, tmp);

      tmp = strtok (NULL, ":");
      client->sample_rate = xmalloc (char, strlen(tmp));
      strcpy (client->sample_rate, tmp);

      break;

    case DATA_PACKET:

      break;
    }

  /* We no longer have a full packet */
  client->have_packet = false;

  return (0);
}
