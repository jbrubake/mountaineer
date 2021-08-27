/*=========================================================================\
| libselserv - 0.1.0a                                                      |
|                                                                          |
| Copyright 2003                                                           |
|     Jeremy Brubaker (jeremy.brubaker@us.army.mil)                        |
|     ...                                                                  |
|                                                                          |
|--------------------------------------------------------------------------|
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
|--------------------------------------------------------------------------|
| DESCRIPTION                                                              |
| ...                                                                      |
|==========================================================================/
| Using libselserv
|
\=========================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <time.h>

#include "protocol.h"
#include "cbase/error.h"

#define BUF_LEN 1024

int
main (int argc, char **argv)
{
  int sd;
  struct hostent *he;
  struct sockaddr_in server_interface;

  he = gethostbyname ("127.0.0.1");
  if (he == NULL)
    error_at_line (1, errno, __FILE__, __LINE__,
                   "%s", "gethostbyname()");

  sd = socket (AF_INET, SOCK_STREAM, 0);
  if (sd == -1)
    error_at_line (1, errno, __FILE__, __LINE__,
                   "%s", "socket()");

  server_interface.sin_family = AF_INET;
  server_interface.sin_port = htons (4000);
  server_interface.sin_addr = *((struct in_addr *)he->h_addr);
  memset (&(server_interface.sin_zero), '\0', 8);

/*   if (connect (sd, (struct sockaddr *)&server_interface, */
/*                sizeof (struct sockaddr)) == -1) */
/*     error_at_line (1, errno, __FILE__, __LINE__, */
/*                    "%s", "connect()"); */

  /* Generate and send test packets */
  for (;;)
    {
      int type;
      int i;
      int len;
      char desc[BUF_LEN];
      char name[BUF_LEN];
      char rate[BUF_LEN];
      char data[100][BUF_LEN];
      char packet[BUF_LEN];
      char packet_final[BUF_LEN];
      char tmp[BUF_LEN];
      time_t timestamps[100];

      strcpy (packet, "");
      strcpy (packet_final, "");
      printf ("p: %s pf: %s\n", packet, packet_final);
      printf ("%s", "Enter packet type: ");
      type = getchar();
      getchar();

      /* Construct packet data */
      if (type == STREAM_INFO_PACKET)
        {
          printf ("%s", "Enter stream description: ");
          gets (desc);
          printf ("%s", "Enter stream name: ");
          gets (name);
          printf ("%s", "Enter sample rate: ");
          gets (rate);

          strcpy (packet, ":");
          packet[1] = (char)type;
          strcat (packet, ":");
          strcat (packet, desc);
          strcat (packet, ":");
          strcat (packet, name);
          strcat (packet, ":");
          strcat (packet, rate);
          strcat (packet, ":");

          len = strlen (packet) + 2;

          sprintf (tmp, "%d", len);
          strcpy (packet_final, tmp);
          strcat (packet_final, packet);
          printf ("Packet: %s\n", packet_final);
          printf ("Length: %d\n", len);
        }
      else if(type == DATA_PACKET)
        {
          i = 0;
          for(;;)
            {
              printf ("%s", "Enter data ('none' to quit): ");
              gets (data[i]);
              timestamps[i] = time(NULL);
              if (strcmp (data[i], "none") == 0)
                break;
              i++;
            }
          int j;
          for (j = 0; j < i; j++)
            {
              strcpy (packet, ":");
              packet[1] = (char)type;
              strcat (packet, ":");
              sprintf (tmp, "%dl", timestamps[j]);
              strcat (packet, tmp);
              strcat (packet, ":");
              strcat (packet, data[j]);
              strcat (packet, ":");
            }

          len = strlen (packet) + 2;
          strcpy (packet_final, tmp);
          strcat (packet_final, packet);
          printf ("Packet: %s\n", packet_final);
          printf ("Length: %d\n", len);
        }
    }

  close (sd);

  return (0);
}
