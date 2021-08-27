/*-------------------------------------------------------------------------\
| server.h                                                                 |
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
| Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA  |
|---------------------------------------------------------------------------
| server.h Documentation
|
\-------------------------------------------------------------------------*/

#ifndef PROTOCOL_H
#define PROTOCOL_H

/*
  Packet Format
  -------------

  All packets will be 1025 bytes. This allows for a 1B type field
  followed by 1024B of data. If the data does not fill 1024B, then it
  will be NUL padded.

  The first packet sent should be a Stream Info packet. This packet
  will contain information on the byte sizes of the DTG and corresponding
  data point. It will also contain an info string that will contain
  text information about the data stream.

  All following packets will be Data packets. Their data segment will contain
  DTG/data point pairs not to exceed 1024B. On machines where sizeof(time_t) =
  sizeof(float) = 4, this will allow for 128 DTG/data pairs per packet.

  Stream Info Packet Format
  -------------------------

  +----+----------------+---------------+-------------+
  | 00 | sizeof(time_t) | sizeof(float) | info string |
  +----+----------------+---------------+-------------+
   0    1                2               3-1024

  Info string contains the following \0 delimited fields:
  Data stream name

  Data Packet Format
  ------------------

  a = sizeof(time_t) on sending machine
  b = sizeof(float) on sending machine

  +----+-----+------------+-----+------------+-------
  | 01 | DTG | Data point | DTG | Data point |  ...
  +----+-----+------------+-----+------------+-------
   0    1     1+a          1+a+b 1+2a+b       1+2a+2b
*/

/* Packet size */
#define PACKET_SIZE 20

/* Packet types */
#define STREAM_INFO_PACKET '0'
#define DATA_PACKET        '1'

/* Indices into stream info packet */
#define PACKET_TYPE   0
#define PACKET_LENGTH 1
#define PACKET_DATA   3

#endif /* !PROTOCOL_H */
