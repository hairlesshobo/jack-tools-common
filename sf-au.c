#include <stdio.h>

#include "byte-order.h"
#include "int.h"
#include "failure.h"
#include "float.h"
#include "memory.h"
#include "sf-au.h"

void write_i32(FILE * fp, i32 i)
{
    i32 j = hton_i32(i);
    fwrite(&j, sizeof(j), 1, fp);
}

void write_f32(FILE * fp, f32 i)
{
    f32 j = hton_f32(i);
    fwrite(&j, sizeof(j), 1, fp);
}

void write_header(FILE * fp, i32 nc, i32 nf, i32 sr)
{
    write_i32(fp, 0x2e736e64);  /* magic */
    write_i32(fp, 32);          /* data offset */
    write_i32(fp, nf * nc * 4); /* number of bytes */
    write_i32(fp, 6);           /* encoding = float */
    write_i32(fp, sr);
    write_i32(fp, nc);
    write_i32(fp, 0);
    write_i32(fp, 0);
}

void write_au_f32(char *nm, i32 nc, i32 nf, i32 sr, f32 * d)
{
    FILE *fp;
    i32 i;
    byte_order_confirm();
    fp = fopen(nm, "w");
    write_header(fp, nc, nf, sr);
    for (i = 0; i < nc * nf; i++) {
        write_f32(fp, d[i]);
    }
    fclose(fp);
}

i32 read_i32(FILE * fp)
{
    i32 i;
    fread(&i, sizeof(i), 1, fp);
    return ntoh_i32(i);
}

f32 read_f32(FILE * fp)
{
    f32 i;
    fread(&i, sizeof(i), 1, fp);
    return ntoh_f32(i);
}

void read_header(FILE * fp, i32 * nc, i32 * nf, i32 * sr)
{
    if (read_i32(fp) != 0x2e736e64) {
        die("sf-au:read_header:magic");
    }
    i32 off = read_i32(fp);
    if (off < 24) {
        die("sf-au:read_header:data offset < 24");
    }
    i32 b = read_i32(fp);
    if (read_i32(fp) != 6) {
        die("sf-au:read_header:encoding");
    }
    *sr = read_i32(fp);
    *nc = read_i32(fp);
    *nf = (b / 4) / *nc;
    i32 i;
    for (i = 0; i < off - 24; i++) {
        fgetc(fp);
    }
}

f32 *read_au_f32(char *nm, i32 * nc, i32 * nf, i32 * sr)
{
    FILE *fp;
    i32 i;
    byte_order_confirm();
    fp = fopen(nm, "r");
    read_header(fp, nc, nf, sr);
    i32 n = *nf * *nc;
    f32 *d = xmalloc(n * sizeof(f32));
    for (i = 0; i < n; i++) {
        d[i] = read_f32(fp);
    }
    fclose(fp);
    return d;
}
