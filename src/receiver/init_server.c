/*-------------------------------------------------------------------------\
| init_server.c                                                            |
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
| init_server.c Documentation
|
\-------------------------------------------------------------------------*/

#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#include "cbase/error.h"
#include "cbase/common.h"
#include "cbase/xmalloc.h"
#include "server.h"

struct SERVER*
init_server (const char *ip, int port)
{
  struct SERVER *server;

  /* Allocate the server */
  server = xmalloc (struct SERVER, 1);

  /* Get the server socket */
  server->sd = socket (AF_INET, SOCK_STREAM, 0);
  if (server->sd == -1)
    error_at_line (1, errno, __FILE__, __LINE__,
                   "%s", "Could not create server socket");

  /* Avoid 'Adress already in use' messages */
  int yes = 1;
  if (setsockopt (server->sd, SOL_SOCKET, SO_REUSEADDR, &yes,
                  sizeof (int)) == -1)
    error_at_line (1, errno, __FILE__, __LINE__,
                   "%s", "Could not set socket options");

  /* Initialize the server interface */
  server->interface.sin_family = AF_INET;
  server->interface.sin_port = htons (port);
#ifdef HAVE_INET_ATON
  if (!inet_aton (ip, &(server->interface.sin_addr)))
    error_at_line (1, errno, __FILE__, __LINE__,
                   "%s <%s>", "Invalid IP address", ip);
#else
  server->interface.sin_addr.s_addr = inet_addr (ip);
#endif /* HAVE_INET_ATON */
  memset (&(server->interface.sin_zero), '\0', 8);

  /* Bind server socket to interface */
  if (bind (server->sd, (struct sockaddr*)&server->interface,
            sizeof (struct sockaddr)) == -1)
    error_at_line (1, errno, __FILE__, __LINE__,
                   "%s", "Could not bind server to address");

  /* Start listening */
  if (listen (server->sd, 5) == -1)
    error_at_line (1, errno, __FILE__, __LINE__,
                   "%s", "Could not set server to listen");

  /* Set up fd sets */
  FD_ZERO (&server->master_fds);
  FD_ZERO (&server->read_fds);
  FD_ZERO (&server->write_fds);
  FD_ZERO (&server->except_fds);

  FD_SET (server->sd, &server->master_fds);
  server->fdmax = server->sd;

  /* Initialize client list */
  server->head = server->tail = NULL;

  return (server);
}
