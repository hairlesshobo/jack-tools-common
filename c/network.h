#ifndef _COMMON_NETWORK_H
#define _COMMON_NETWORK_H

#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "int.h"

enum SocketType {TcpSocket, UdpSocket};

enum SocketType socket_type_parse(char *str);
void socket_type_string(enum SocketType socket_type, char *answer, int answer_size);
int xsocket(int domain, int type, int protocol);
int socket_tcp(int protocol);
int socket_udp(int protocol);
int socket_for(enum SocketType socket_type);
void init_sockaddr_in(struct sockaddr_in *name, const char *hostname, uint16_t port);
void init_broadcast_sockaddr_in(struct sockaddr_in *name, uint16_t port);
int sockaddr_in_equal(const struct sockaddr_in *a, const struct sockaddr_in *b);
void print_sockaddr_in(FILE *fp, struct sockaddr_in a);
void xbind(int fd, const struct sockaddr *addr, socklen_t addrlen);
void bind_inet(int fd, const char *hostname, int port);
void xconnect(int fd, const struct sockaddr *addr, socklen_t addrlen);
void connect_inet(int fd, const char *hostname, int port);
void xsend(int fd, const void *buf, size_t len, int flags);
ssize_t xsendto(int fd, const void *data, size_t n, int flags, struct sockaddr *addr, socklen_t length);
void sendto_exactly(int fd, const u8 *data, int n, struct sockaddr_in address);
ssize_t xrecv(int fd, void *buf, size_t n, int flags);
void recv_exactly(int fd, void *buf, size_t n, int flags);
ssize_t xrecvfrom(int fd, void *buf, size_t n, int flags, struct sockaddr *addr, socklen_t *length);
void recvfrom_exactly(int fd, void *buf, size_t n, int flags, struct sockaddr *addr, socklen_t *length);
int fd_wait(int fd, unsigned long timeout);
void xclose(int fd);

#endif
