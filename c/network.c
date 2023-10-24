#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/select.h>

#include "int.h"
#include "failure.h"
#include "network.h"
#include "time-timeval.h"

int xsocket(int domain, int type, int protocol)
{
  int fd = socket(domain, type, protocol);
  if(fd == -1) {
    perror("xsocket: socket() failed");
    FAILURE;
  }
  return fd;
}

int socket_tcp(int protocol)
{
  return xsocket(AF_INET, SOCK_STREAM, protocol);

}
int socket_udp(int protocol)
{
  return xsocket(AF_INET, SOCK_DGRAM, protocol);
}

enum SocketType socket_type_parse(char *str)
{
  if(strncmp("tcp", str, 3) == 0) {
    return TcpSocket;
  } else if(strncmp("udp", str, 3) == 0) {
    return UdpSocket;
  } else {
    fprintf(stderr, "socket_type_parse: unknown socket type: '%s'\n", str);
    FAILURE;
  }
}

void socket_type_string(enum SocketType socket_type, char *answer, int answer_size)
{
  switch(socket_type) {
    case TcpSocket: strncpy(answer, "tcp", answer_size - 1); break;
    case UdpSocket: strncpy(answer, "udp", answer_size - 1); break;
    default: fprintf(stderr, "socket_type_string: illegal socket type: '%d'\n", socket_type); FAILURE;
  }
}

int socket_for(enum SocketType socket_type)
{
  switch(socket_type) {
    case TcpSocket: return socket_tcp(0);
    case UdpSocket: return socket_udp(0);
    default: FAILURE;
  }
}

void init_sockaddr_in(struct sockaddr_in *name, const char *hostname, uint16_t port)
{
  name->sin_family = AF_INET;
  name->sin_port = htons(port);
  if(hostname) {
    struct hostent *hostinfo = gethostbyname(hostname);
    if (hostinfo == NULL) {
      fprintf(stderr, "init_sockaddr_in: unknown host: %s.\n", hostname);
      FAILURE;
    }
    name->sin_addr = *(struct in_addr *) hostinfo->h_addr_list[0];
  } else {
    name->sin_addr.s_addr = htonl(INADDR_ANY);
  }
}

void init_broadcast_sockaddr_in(struct sockaddr_in *name, uint16_t port)
{
  name->sin_family = AF_INET;
  name->sin_port = htons(port);
  name->sin_addr.s_addr = htonl(INADDR_BROADCAST);
}

int sockaddr_in_equal(const struct sockaddr_in *a, const struct sockaddr_in *b)
{
  return((a->sin_family == b->sin_family) &&
    (a->sin_addr.s_addr == b->sin_addr.s_addr) &&
    (a->sin_port == b->sin_port));
}

void print_sockaddr_in(FILE *fp, struct sockaddr_in a)
{
  fprintf(fp, "sin_family      %d\n", a.sin_family);
  fprintf(fp, "sin_port        %d\n", a.sin_port);
  fprintf(fp, "sin_addr.s_addr %d\n", a.sin_addr.s_addr);
}

void xbind(int fd, const struct sockaddr *addr, socklen_t addrlen)
{
  int err = bind(fd, addr, addrlen);
  if(err == -1) {
    perror("xbind: bind() failed");
    FAILURE;
  }
}

void bind_inet(int fd, const char *hostname, int port)
{
  struct sockaddr_in name;
  init_sockaddr_in(&name, hostname, port);
  xbind(fd, (struct sockaddr *)&name, sizeof(name));
}

void xconnect(int fd, const struct sockaddr *addr, socklen_t addrlen)
{
  int err = connect(fd, addr, addrlen);
  if(err == -1) {
    perror("xconnect: connect() failed");
    FAILURE;
  }
}

void connect_inet(int fd, const char *hostname, int port)
{
  struct sockaddr_in name;
  init_sockaddr_in(&name, hostname, port);
  xconnect(fd, (struct sockaddr *)&name, sizeof(name));
}

void xsend(int fd, const void *buf, size_t len, int flags)
{
  ssize_t bytesSent = send(fd, buf, len, flags);
  if(bytesSent == -1) {
    perror("xsend: send() failed");
    FAILURE;
  }
  if(bytesSent < len) {
    perror("xsend: send() partial send");
    FAILURE;
  }
}

ssize_t xsendto(int fd, const void *data, size_t n, int flags, struct sockaddr *addr, socklen_t length)
{
  ssize_t bytesSent = sendto(fd, data, n, flags, addr, length);
  if(bytesSent == -1) {
    perror("sendto() failed");
    FAILURE;
  }
  return bytesSent;
}

void sendto_exactly(int fd, const u8 *data, int n, struct sockaddr_in address)
{
  ssize_t bytesSent = xsendto(fd, data, n, 0, (struct sockaddr *)&address, sizeof(address));
  if(bytesSent != n) {
    fprintf(stderr, "sendto_exactly: partial write\n");
    FAILURE;
  }
}

ssize_t xrecv(int fd, void *buf, size_t n, int flags)
{
  ssize_t bytesReceived = recv(fd, buf, n, flags);
  if(bytesReceived == -1) {
    perror("xrecv: recv() failed");
    FAILURE;
  }
  return bytesReceived;
}

void recv_exactly(int fd, void *buf, size_t n, int flags)
{
  ssize_t bytesReceived = xrecv(fd, buf, n, flags);
  if(bytesReceived != n) {
    fprintf(stderr, "recv_exactly: partial recv (%d != %ul)\n", (int)bytesReceived, (int)n);
    FAILURE;
  }
}

ssize_t xrecvfrom(int fd, void *buf, size_t n, int flags, struct sockaddr *addr, socklen_t *length)
{
  ssize_t bytesReceived = recvfrom(fd, buf, n, flags, addr, length);
  if(bytesReceived == -1) {
    perror("xrecvfrom: recvfrom() failed");
    FAILURE;
  }
  return bytesReceived;
}

void recvfrom_exactly(int fd, void *buf, size_t n, int flags, struct sockaddr *addr, socklen_t *length)
{
  ssize_t bytesReceived = xrecvfrom(fd, buf, n, flags, addr, length);
  if(bytesReceived != n) {
    fprintf(stderr, "recvfrom_exactly: partial recv (%d != %d)\n", (int)bytesReceived, (int) n);
    FAILURE;
  }
}

/* Wait at most `timeout' usecs for `fd' to become readable.  Returns
   0 on timeout, 1 if data is available. */

int fd_wait(int fd, unsigned long timeout)
{
  fd_set set;
  FD_ZERO(&set);
  FD_SET(fd, &set);

  struct timeval t;
  t = usec_to_timeval(timeout);

  int err;
  err = select(FD_SETSIZE, &set, NULL, NULL, &t);

  if(err == -1) {
    fprintf(stderr, "fd_wait: select failed, %d\n", err);
    FAILURE;
  }
  return err;
}

void xclose(int fd)
{
  int err = close(fd);
  if(err == -1) {
    perror("xclose: close() failed");
    FAILURE;
  }
}
