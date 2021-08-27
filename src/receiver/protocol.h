/*-------------------------------------------------------------------------\
| protocol.h                                                               |
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
| Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA  |
|---------------------------------------------------------------------------
| protocol.h Documentation
|
\-------------------------------------------------------------------------*/

#ifndef PROTOCOL_H
#define PROTOCOL_H

/*
  Packet Format
  -------------

  Packets can be up to 1024 bytes long. The first byte is a type field.

  The first packet sent should be a Stream Info packet. This packet
  the name of the data stream.

  All following packets will be Data packets. Their data segment will contain
  data/timestamp point pairs not to exceed 1024B. Each sample is separated
  by a '%' character. The data and timestamp will be separated by a
  ':' character.

  Stream Info Packet Format
  -------------------------

  +----+--------------------...
  | 00 | Stream name string
  +----+--------------------...
   0    1-1024

  Info string contains the following delimited fields:
  Data stream name

  Data Packet Format
  ------------------


  +----+------------+---+-----------+---+------------+---+----------...
  | 01 | Data point | : | Timestamp | % | Data point | : |Timestamp
  +----+------------+---+-----------+---+------------+---+----------...
   0    1
*/

/* Packet size */
#define PACKET_SIZE 1024

/* Packet types */
#define STREAM_INFO_PACKET '0'
#define DATA_PACKET        '1'

/* Indices into stream info packet */
#define PACKET_TYPE   0
#define PACKET_LENGTH 1
#define PACKET_DATA   3

#endif /* !PROTOCOL_H */
