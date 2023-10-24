#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
#include <math.h>

#include "byte-order.h"
#include "failure.h"
#include "memory.h"
#include "osc.h"
#include "print.h"

void osc_socket_print(osc_socket_t osc_socket)
{
  char type_name[4];
  socket_type_string(osc_socket.socket_type, type_name, 4);
  printf("socket_type = %s (%d)\n", type_name, osc_socket.socket_type);
  printf("hostname = %s\n", osc_socket.hostname);
  printf("port = %d\n", osc_socket.port);
  printf("fd = %d\n", osc_socket.fd);
}

osc_socket_t osc_socket_open(enum SocketType socket_type,const char *hostname, int port)
{
  osc_socket_t osc_socket;
  osc_socket.socket_type = socket_type;
  strncpy(osc_socket.hostname, hostname, HOST_NAME_MAX - 1);
  osc_socket.port = port;
  osc_socket.fd = socket_for(socket_type);
  osc_socket_print(osc_socket);
  connect_inet(osc_socket.fd, hostname, port);
  return osc_socket;
}

void osc_socket_send_packet(osc_socket_t osc_socket, const u8 *packet, i32 packet_sz)
{
  if(osc_socket.socket_type == TcpSocket) {
    u8 sz_buf[4];
    hton_i32_to_buf(sz_buf, packet_sz);
    xsend(osc_socket.fd, sz_buf, 4, 0);
  }
  xsend(osc_socket.fd, packet, packet_sz, 0);
}

void osc_socket_close(osc_socket_t osc_socket)
{
  xclose(osc_socket.fd);
}

i32 osc_align(i32 n) {return (((n + 3) & (~3)) - n);}
i32 osc_cstr_bound(i32 n) {return n + 1 + osc_align(n + 1);}

void assert_non_negative(const char *s,i32 n) {
    if(n < 0) {
        fprintf(stderr, "%s: s=%s, n < 0, n=%d\n", __func__, s, n);
        FAILURE;
    }
}

/* n = size of byte-data, returns n + osc_align(n) */
i32 osc_blob_bound(i32 n)
{
    assert_non_negative(__func__,n);
    dprintf("%s: n=%d, osc_align(n)=%d\n",__func__,n,osc_align(n));
    return n + osc_align(n);
}

void osc_print_packet(const u8 *packet, i32 packet_sz)
{
  i32 i;
  for(i = 0; i < packet_sz; i++) {
    fprintf(stderr, "%3d (%1.1s) ", packet[i], packet + i);
    if(( i + 1) % 4  == 0) {
      fprintf(stderr, "\n");
    }
  }
}

bool osc_is_numerical_type(u8 c)
{
  return c == 'i' || c == 'h' || c == 't' || c == 'f' || c == 'd';
}

bool osc_is_string_type(u8 c)
{
  return c == 's' || c == 'S';
}

bool osc_can_coerce(u8 u, u8 d)
{
  return(( u == d) ||
	 (osc_is_numerical_type(u) && osc_is_numerical_type(d)) ||
	 (osc_is_string_type(u) && osc_is_string_type(d)));
}

void osc_coerce(u8 u, u8 d, osc_data_t *o)
{
  if(u == d) {
    return;
  }
  if(u == 's' && d == 'S') {
    o->s = o->S;
  } else if(u == 'S' && d == 's') {
    o->S = o->s;
  } else if(u == 'i' && d == 'h') {
    o->i = (i32) o->h;
  } else if(u == 'i' && d == 't') {
    o->i = (i32) o->t;
  } else if(u == 'i' && d == 'f') {
    o->i = (i32) floorf(o->f);
  } else if(u == 'i' && d == 'd') {
    o->i = (i32) floor(o->d);
  } else if(u == 'h' && d == 'i') {
    o->h = (i64) o->i;
  } else if(u == 'h' && d == 't') {
    o->h = (i64) o->t;
  } else if(u == 'h' && d == 'f') {
    o->h = (i64) floorf(o->f);
  } else if(u == 'h' && d == 'd') {
    o->h = (i64) floor(o->d);
  } else if(u == 't' && d == 'i') {
    o->t = (u64) o->i;
  } else if(u == 't' && d == 'h') {
    o->t = (u64) o->t;
  } else if(u == 't' && d == 'f') {
    o->t = (u64) floorf(o->f);
  } else if(u == 't' && d == 'd') {
    o->t = (u64) floor(o->d);
  } else if(u == 'f' && d == 'i') {
    o->f = (f32) o->i;
  } else if(u == 'f' && d == 'h') {
    o->f = (f32) o->h;
  } else if(u == 'f' && d == 't') {
    o->f = (f32) o->t;
  } else if(u == 'f' && d == 'd') {
    o->f = (f32) o->d;
  } else if(u == 'd' && d == 'i') {
    o->d = (f64) o->i;
  } else if(u == 'd' && d == 'h') {
    o->d = (f64) o->h;
  } else if(u == 'd' && d == 't') {
    o->d = (f64) o->t;
  } else if(u == 'd' && d == 'f') {
    o->d = (f64) o->d;
  } else {
    fprintf(stderr, "osc_coerce: illegal coercion '%c' <- '%c'\n", u, d);
    FAILURE;
  }
}

void osc_coerce_arguments(const char *u_dsc, const char *p_dsc, osc_data_t *data)
{
  u_dsc++;
  p_dsc++;
  while(*u_dsc != '\0') {
    osc_coerce(*u_dsc++, *p_dsc++, data++);
  }
}

i32 u8strlen(const u8* b)
{
  return strlen((const char*)b);
}

i32 u8strncmp(const u8 *a, const u8 *b, i32 n)
{
  return strncmp((const char*)a, (const char*)b, n);
}

/* read u8* 'p' data according to 'dsc' and copy/assign to osc_data_t */
i32 osc_collect_arguments(const char *dsc, const u8 *p, osc_data_t *data)
{
  dprintf("%s: dsc=%s, p=%p data=%p\n",__func__,dsc,(void*)p,(void*)data);
  dsc++;
  i32 i = 0;
  while(*dsc != '\0') {
    u8 c = *dsc;
    osc_data_t *x = data + i;
    if(c == 'i') {
      x->i = ntoh_i32_from_buf(p);
      p += 4;
    } else if(c == 'h') {
      x->h = ntoh_i64_from_buf(p);
      p += 8;
    } else if(c == 't') {
      x->t = ntoh_u64_from_buf(p);
      p += 8;
    } else if(c == 'f') {
      x->f = ntoh_f32_from_buf(p);
      p += 4;
    } else if(c == 'd') {
      x->d = ntoh_f64_from_buf(p);
      p += 8;
    } else if(c == 's') {
      x->s = (char*)p;
      p += osc_cstr_bound(u8strlen(p));
    } else if(c == 'S') {
      x->S = (char*)p;
      p += osc_cstr_bound(u8strlen(p));
    } else if(c == 'c') {
      x->c = ntoh_u32_from_buf(p);
      p += 4;
    } else if(c == 'm') {
      xmemcpy(x->m, p, 4);
      p += 4;
    } else if(c == 'r') {
      x->r = ntoh_u32_from_buf(p);
      p += 4;
    } else if(c == 'b') {
      x->b.size = ntoh_i32_from_buf(p);
      assert_non_negative(__func__,x->b.size);
      x->b.data = p + 4;
      dprintf("%s: b.size=%d, osc_align=%d b.data=%p\n",__func__,x->b.size,osc_align(x->b.size),(void*)x->b.data);
      p += 4 + osc_blob_bound(x->b.size);
    } else {
      return -1;
    }
    dsc++;
    i++;
  }
  return 0;
}

/* encode osc_data_t to u8* */
i32 osc_pack_arguments(const char *dsc, const osc_data_t *data, u8 *p)
{
  dsc++; /* , */
  i32 i = 0;
  while(*dsc != '\0') {
    u8 c = *dsc;
    dprintf("%s: c=%c i=%d p=%p\n",__func__,c,i,(void *)p);
    if(c == 'i') {
      hton_i32_to_buf(p, data[i].i);
      p += 4;
    } else if(c == 'h') {
      hton_i64_to_buf(p, data[i].h);
      p += 8;
    } else if(c == 't') {
      hton_u64_to_buf(p, data[i].t);
      p += 8;
    } else if(c == 'f') {
      hton_f32_to_buf(p, data[i].f);
      p += 4;
    } else if(c == 'd') {
      hton_f64_to_buf(p, data[i].d);
      p += 8;
    } else if(c == 's') {
      i32 n = strlen(data[i].s);
      xmemcpy(p, data[i].s, n + 1);
      p += osc_cstr_bound(n);
    } else if(c == 'S') {
      i32 n = strlen(data[i].S);
      xmemcpy(p, data[i].S, n + 1);
      p += osc_cstr_bound(n);
    } else if(c == 'c') {
      hton_u32_to_buf(p, data[i].c);
      p += 4;
    } else if(c == 'm') {
      xmemcpy(p, data[i].m, 4);
      p += 4;
    } else if(c == 'r') {
      hton_u32_to_buf(p, data[i].r);
      p += 4;
    } else if(c == 'b') {
      hton_i32_to_buf(p, data[i].b.size);
      dprintf("%s: b.data=%p b.size=%d\n",__func__,(void*)(data[i].b.data),data[i].b.size);
      xmemcpy(p + 4, data[i].b.data, data[i].b.size);
      p += 4 + osc_blob_bound(data[i].b.size);
    } else {
      return -1;
    }
    dsc++;
    i++;
  }
  return 0;
}

i32 osc_dsc_read_arg_len(const char *dsc, const u8 *p)
{
  if(*dsc++ != ',') {
    fprintf(stderr, "osc_dsc_read_arg_len: illegal descriptor '%s'\n", dsc);
    return -1;
  }
  i32 n = 0;
  while(*dsc != '\0') {
    u8 c = *dsc;
    if(c == 'i' || c == 'f' || c == 'c' || c == 'm' || c == 'r') {
      n += 4;
    } else if(c == 'd' || c == 'h' || c == 't') {
      n += 8;
    } else if(c == 's' || c == 'S') {
      n += osc_cstr_bound(u8strlen(p + n));
    } else if(c == 'b') {
      n += osc_blob_bound(ntoh_i32_from_buf(p + n)) + 4;
    } else {
      return -1;
    }
    dsc++;
  }
  return n;
}

i32
osc_dsc_calculate_arg_len(const char *dsc, const osc_data_t *data)
{
  if(*dsc++ != ',') {
    fprintf(stderr, "%s: illegal descriptor '%s'\n", __func__, dsc);
    return -1;
  }
  i32 n = 0;
  while(*dsc != '\0') {
    u8 c = *dsc;
    if(c == 'i' || c == 'f' || c == 'c' || c == 'm' || c == 'r') {
      n += 4;
    } else if(c == 'd' || c == 'h' || c == 't') {
      n += 8;
    } else if(c == 's') {
      n += osc_cstr_bound(strlen(data->s));
    } else if(c == 'S') {
      n += osc_cstr_bound(strlen(data->S));
    } else if(c == 'b') {
      dprintf("%s: data=%p data->b.data=%p data->b.size=%d\n",__func__,(void*)data,(void*)data->b.data,data->b.size);
      n += osc_blob_bound(data->b.size) + 4;
    } else {
      return -1;
    }
    dsc++;
    data++;
  }
  assert_non_negative(__func__,n);
  return n;
}

i32 osc_match_address(const char *addr, const u8 *packet)
{
  size_t addr_n = strlen(addr);
  if(strncmp(addr, (char*)packet, addr_n)!= 0) {
    return 0;
  } else {
    return osc_cstr_bound(addr_n);
  }
}

i32 osc_match_dsc(const char *u_dsc, const char *p_dsc)
{
  size_t u_dsc_n = strlen(u_dsc);
  if(*u_dsc++ != ',' || *p_dsc++ != ',') {
    return 0;
  }
  while(*u_dsc != '\0') {
    if(! osc_can_coerce(*u_dsc++, *p_dsc++)) {
      return 0;
    }
  }
  return osc_cstr_bound(u_dsc_n);
}

/* returns 0 on non-match, else 1 length */
i32 osc_parse_message(const char *addr, const char *dsc, const u8 *packet, i32 packet_sz, osc_data_t *data)
{
  dprintf("%s: addr=%p dsc=%s pkt=%p pkt_sz=%d data=%p\n",__func__,addr,dsc,packet,packet_sz,(void*)data);
  i32 addr_len = osc_match_address(addr, packet);
  if(addr_len == 0) {
    return 0;
  }
  const char *p_dsc = (char*)packet + addr_len;
  i32 dsc_len = osc_match_dsc(dsc, p_dsc);
  if(dsc_len == 0) {
    return 0;
  }
  const u8 *p_arg = (u8*)p_dsc + dsc_len;
  i32 arg_len = osc_dsc_read_arg_len(p_dsc, p_arg);
  if(packet_sz < addr_len + dsc_len + arg_len) {
    eprintf("ERROR: %s: packet_sz: (%d < %d + %d + %d)\n"
            ,__func__,packet_sz
            ,addr_len,dsc_len,arg_len);
    return 0;
  }
  i32 err = osc_collect_arguments(p_dsc, p_arg, data);
  if(err) {
    eprintf("ERROR: %s: osc_collect_arguments\n",__func__);
    return 0;
  }
  osc_coerce_arguments(dsc, p_dsc, data);
  return addr_len + dsc_len + arg_len;
}

i32 osc_construct_message(const char *addr, const char *dsc, const osc_data_t *data, u8 *packet, i32 packet_sz)
{
  dprintf("%s: addr=%s dsc=%s data=%p packet=%p packet_sz=%d\n",
          __func__,addr,dsc,(void*)data,(void*)packet,packet_sz);
  i32 addr_n = strlen(addr);
  i32 addr_len = osc_cstr_bound(addr_n);
  i32 dsc_n = strlen(dsc);
  i32 dsc_len = osc_cstr_bound(dsc_n);
  dprintf("%s: addr_n=%d addr_len=%d dsc_n=%d dsc_len=%d\n",
          __func__,addr_n,addr_len,dsc_n,dsc_len);
  xmemset(packet, 0, addr_len + dsc_len);
  xmemcpy(packet, addr, addr_n + 1);
  xmemcpy(packet + addr_len, dsc, dsc_n + 1);
/*
  if(packet_sz < addr_len + dsc_len + arg_len) {
    return 0;
  }
*/
  i32 err = osc_pack_arguments(dsc, data, packet + addr_len + dsc_len);
  if(err) {
    return 0;
  }
  i32 arg_len = osc_dsc_calculate_arg_len(dsc, data);
  return addr_len + dsc_len + arg_len;
}

i32 osc_build_message(u8 *packet, i32 packet_sz,
		      const char *addr, const char *dsc, ...)
{
  osc_data_t data[256]; /* LIMIT */

  va_list ap;
  va_start(ap, dsc);

  i32 index;
  index = 0;

  while(dsc && dsc[index+1]) {
    switch(dsc[index+1]) {
    case 'i':
      data[index].i = va_arg(ap, i32);
      break;
    case 'h':
      data[index].h = va_arg(ap, i64);
      break;
    case 't':
      data[index].t = va_arg(ap, u64);
      break;
    case 'f':
      data[index].f = va_arg(ap, f64);
      break;
    case 'd':
      data[index].d = va_arg(ap, f64);
      break;
    case 's':
      data[index].s = va_arg(ap, char*);
      break;
    case 'S':
      data[index].S = va_arg(ap, char*);
      break;
    case 'c':
      data[index].c = va_arg(ap, u32);
      break;
    case 'm':
      xmemcpy(data[index].m, va_arg(ap, u8*), 4);
      break;
    case 'r':
      data[index].r = va_arg(ap, u32);
      break;
    case 'b':
      data[index].b = va_arg(ap, osc_blob_t);
      break;
    default:
      return 0;
    }
    index++;
  }
  va_end(ap);

  return osc_construct_message(addr, dsc, data, packet, packet_sz);
}
