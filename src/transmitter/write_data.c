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

#include "server.h"

/*
  This function was shamelessly ripped from Beej's Guide to Network Programming
  located at http://www.ecst.csuchico.edu/~beej/guide/net/html/.
*/
int
write_data (struct CLIENT *client)
{
  int total = 0;
  int len = strlen (client->write_buf);
  int bytes_left = len;
  int n;

  /* Loop while we still have data to send */
  while (total < len)
    {
      /* Send what we can */
      n = send (client->sd, client->write_buf, bytes_left, 0);

      /* Break and return on error */
      if (n == -1)
        break;

      /* Add to bytes sent counter */
      total += n;
      /* Find out how much we still have to send */
      bytes_left -= n;
    }

  /* Return bytes sent, -1 on error */
  return (n == -1 ? -1 : total);
}
