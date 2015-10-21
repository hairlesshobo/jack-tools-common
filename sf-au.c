#include <stdio.h>

#include "byte-order.h"
#include "int.h"
#include "float.h"
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
    write_i32(fp, 28);          /* data offset */
    write_i32(fp, nf * nc * 4); /* number of bytes */
    write_i32(fp, 6);           /* encoding = float */
    write_i32(fp, sr);
    write_i32(fp, nc);
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
