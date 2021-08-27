/*-------------------------------------------------------------------------\
| server.h                                                                 |
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
| server.h Documentation
|
\-------------------------------------------------------------------------*/

#ifndef SERVER_H
#define SERVER_H

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>

#include <cbase/error.h>
#include <cbase/common.h>
#include <protocol.h>

/* For Windows portability */
typedef int SOCKET;

struct CLIENT
{
  SOCKET sd;
  struct sockaddr_in interface;

  char read_buf[PACKET_SIZE + 1];

  int bytes_held;

  char *name;

  FILE *output;

  struct CLIENT *next;
  struct CLIENT *prev;
};

struct SERVER
{
  SOCKET sd;
  struct sockaddr_in interface;

  fd_set master_fds;
  fd_set read_fds;
  fd_set write_fds;
  fd_set except_fds;
  int fdmax;

  struct CLIENT *head;
  struct CLIENT *tail;
};

BEGIN_C_DECLS

int new_client    (struct SERVER *server);
int remove_client (struct CLIENT *head, struct CLIENT *client);

struct SERVER *init_server       (const char *ip, int port);
int            run_server        (struct SERVER *server);
int            accept_connection (struct SERVER *server);

int read_data        (struct CLIENT *client);
int write_data       (struct CLIENT *client);
int handle_exception (struct CLIENT *client);
int process_data     (struct CLIENT *client);

END_C_DECLS

#endif /* !SERVER_H */
