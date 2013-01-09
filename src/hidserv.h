/*
 *
 *  Copyright (C) 2008 -2009  Valerio Valerio <vdv100@gmail.com>
 *
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <malloc.h>
#include <syslog.h>
#include <signal.h>
#include <getopt.h>
#include <netinet/in.h>
#include <sys/types.h> 
#include <sys/poll.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <pthread.h>

#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>
#include <bluetooth/l2cap.h>
#include <bluetooth/sdp.h>
#include <bluetooth/hidp.h>

#ifdef __cplusplus
extern "C" {
#endif

void error(char *msg);

int create_socket();

int l2cap_connect(bdaddr_t *src, bdaddr_t *dst, unsigned short psm);

int reconnect(char *src, char *dst);

int send_key_down(int modifiers, int val);

int send_multiple_key_down(int modifiers, int val, int val2);

int send_key_up();

int send_multiple_key_up(int val);

int send_mouse_event(int btn, int mov_x, int mov_y, int whell);

void open_sock();

void init_server();

int connection_state();

char* client_address();

int quit_serv();

void quit_thread();

#ifdef __cplusplus
}
#endif
