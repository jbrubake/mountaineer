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

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "server.h"
#include "cbase/error.h"

int
accept_connection (struct SERVER *server)
{
  SOCKET new_connection;
  struct sockaddr_in remote_interface;
  int addrlen;

  /* Accept the connection */
  addrlen = sizeof (struct sockaddr);
  new_connection = accept (server->sd,
                           (struct sockaddr *)&remote_interface, &addrlen);
  if (new_connection == -1)
    error_at_line (1, errno, __FILE__, __LINE__,
                   "%s", "accept()");

  /* Add it to the mast fd set */
  FD_SET (new_connection, &server->master_fds);
  if (new_connection > server->fdmax)
    server->fdmax = new_connection;

  /* Log the connection */
  error (0, 0, "Accepted new connection form %s",
         inet_ntoa (remote_interface.sin_addr));

  /* Add a new connection to the connection list */
  if (new_client (server) == -1)
    error_at_line (1, errno, __FILE__, __LINE__,
                   "%s", "new_client()");

  /* Initialize the new connection */
  server->tail->sd = new_connection;
  server->tail->read_buf[0] = '\0';
  server->tail->bytes_held = 0;
  server->tail->have_packet = false;

  return (0);
}
