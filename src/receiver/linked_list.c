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

#include "cbase/xmalloc.h"
#include "server.h"

int
new_client (struct SERVER *server)
{
  /* Allocate the new client */
  struct CLIENT *client;
  client = xmalloc (struct CLIENT, 1);

  /* Set up pointers */
  client->prev = server->tail;
  client->next = NULL;

  if (server->tail == NULL)
    server->head = server->tail = client;
  else
    server->tail->next   = client;

  return (0);
}

int
remove_client (struct CLIENT *head, struct CLIENT *client)
{
  struct CLIENT *curr;
  for (curr = head; curr != NULL; curr = curr->next)
    {
      /* Found the one we want to delete */
      if (curr == client)
        {
          /* Take it out of the list */
          curr->prev->next = curr->next;
          curr->next->prev = curr->prev;
          /* Free it */
          xfree (curr);
        }
    }

  return (0);
}

