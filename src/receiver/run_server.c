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

#include <sys/select.h>
#include <arpa/inet.h>

#include "cbase/error.h"
#include "server.h"

int
run_server (struct SERVER *server)
{
  /* Run the server forever */
  for (;;)
    {
      /* Sync all the fd sets */
      server->read_fds = server->write_fds = server->except_fds = server->master_fds;

      /* Remove server from write and except fd sets */
      FD_CLR (server->sd, &server->write_fds);
      FD_CLR (server->sd, &server->except_fds);

      /* We want select() to return immediately */
      struct timeval timeout;
      timeout.tv_sec  = 0;
      timeout.tv_usec = 0;

      /* Poll fd sets */
      if (select (server->fdmax+1, &server->read_fds, &server->write_fds,
                  &server->except_fds, &timeout) == -1)
        error_at_line (1, errno, __FILE__, __LINE__,
                       "%s", "select()");

      /* Check for new connection requests */
      if (FD_ISSET (server->sd, &server->read_fds))
          if (accept_connection (server) == -1)
            error_at_line (1, errno, __FILE__, __LINE__,
                           "%s", "accept_connection()");

      /* Check all connections */
      struct CLIENT *curr;
      for (curr = server->head; curr != NULL; curr = curr->next)
        {
          /* Data to read? */
          if (FD_ISSET (curr->sd, &server->read_fds))
            {
              /* Read the data */
              if (read_data (curr) == -1)
                error_at_line (1, errno, __FILE__, __LINE__,
                               "%s", "read_data()");

              /* If we have a whole packet, process it */
              if (curr->have_packet)
                if(process_data (curr) == -1)
                  error_at_line (1, errno, __FILE__, __LINE__,
                                 "%s", "pr    ocess_data()");
            }

          /* Raised an exception? */
          if (FD_ISSET (curr->sd, &server->except_fds))
            handle_exception (curr);
        }
    }

      return (0);
}
