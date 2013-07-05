/*
Lean & mean fetching of NoData out of HFA files.
Reconstructed after sparse format documentation found over the net.
This is not a part of original TauDEM

Copyright (C) 2013 Mikhail Titov

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "commonLib.h"

char *strndup(const char *s, size_t n) {
  char *d = (char*)malloc(n+1);
  strncpy(d, s, n);
}

typedef struct tagEhfa_HeaderTag {
  char label[16];
  long headerPtr;
} Ehfa_HeaderTag;

typedef struct tagEhfa_File {
  long version;
  long freeList;
  long rootEntryPtr;
  short entryHeaderLength;
  long dictionaryPtr;
} Ehfa_File;

typedef struct tagEhfa_Entry {
  long next;
  long prev;
  long parent;
  long child;
  long data;
  long dataSize;
  char name[64];
  char type[32];
  long time;
} Ehfa_Entry;

typedef struct tagEhfa_Type_Indirect {
  long repeat;
  long data;
} Ehfa_Type_Indirect;

typedef struct tagEhfa_Type_Basedata {
  long rows;
  long cols;
  short datatype;
  short objecttype;
  /* enum { */
  /*       EGDA_TYPE_U1=0, */
  /*       EGDA_TYPE_U2=1, */
  /*       EGDA_TYPE_U4=2, */
  /*       EGDA_TYPE_U8=3, */
  /*       EGDA_TYPE_S8=4, */
  /*       EGDA_TYPE_U16=5, */
  /*       EGDA_TYPE_S16=6, */
  /*       EGDA_TYPE_U32=7, */
  /*       EGDA_TYPE_S32=8, */
  /*       EGDA_TYPE_F32=9, */
  /*       EGDA_TYPE_F64=10, */
  /*       EGDA_TYPE_C64=11, */
  /*       EGDA_TYPE_C128=12 */
  /* } datatype; */
  /* enum { */
  /*       EGDA_SCALAR_OBJECT=0, */
  /*       EGDA_TABLE_OBJECT=1, */
  /*       EGDA_MATRIX_OBJECT=2, */
  /*       EGDA_RASTER_OBJECT=3   */
  /* } objecttype; */
  void* data;
} Ehfa_Type_Basedata;

void walk(FILE* f, Ehfa_Entry *e, void **nodata) {
  Ehfa_Entry e2;
  const int debug = 0;
  if (debug) {
    char *name = strndup((char*)e->name, 64);
    char *type = strndup((char*)e->type, 32);
    printf("name=%s (%s) next=0x%x prev=0x%x parent=0x%x child=0x%x data=0x%x (%d)\n",
	   name, type, e->next, e->prev, e->parent, e->child, e->data, e->dataSize);
    free(name); free(type);
  }

  if (0 == strcmp(e->name, "Eimg_NonInitializedValue")) {
    // char buf[e->dataSize];
    Ehfa_Type_Indirect in;
    fseek(f, e->data, SEEK_SET);
    fread(&in, sizeof(Ehfa_Type_Indirect), 1, f);
    // printf("Data offset 0x%x\n", in.data);
    fseek(f, in.data, SEEK_SET);
    Ehfa_Type_Basedata bd;
    // printf("About to read %d bytes\n", e->dataSize - sizeof(Ehfa_Type_Indirect));
    fread(&bd, e->dataSize - sizeof(Ehfa_Type_Indirect), 1, f);
    if (0 != bd.objecttype)
      printf("Wrong object typein AUX. Scalar expected!\n");
    switch (bd.datatype) {
    case 9:			// EGDA_TYPE_F32
      *nodata = new float;
      *(float*)*nodata = *(float*)&bd.data;
      break;
    default:
      printf("Wrong data type in AUX. 32bit float expected!\n");
    }
    return;
  }

  if (e->child) {
    if (debug) printf("\t|\n\tv\n");
    fseek(f, e->child, SEEK_SET);
    fread(&e2, sizeof(Ehfa_Entry), 1, f);
    walk(f, &e2, nodata);
    if (*nodata)
      return;
  }
  if (e->next) {
    if (debug) printf("\t->\n");
    fseek(f, e->next, SEEK_SET);
    fread(&e2, sizeof(Ehfa_Entry), 1, f);
    walk(f, &e2, nodata);
    if (*nodata)
      return;
  }
  if (debug) printf("\t^\n\t|\n");
}

int getNodataFromAUX(const char* filename, void** nodata) {
  Ehfa_HeaderTag header;
  Ehfa_File hf;
  Ehfa_Entry root;
  FILE* f = NULL;
  printf("About to open %s for reading\n", filename);
  f = fopen(filename, "rb");
  if (!f) {
    printf("Failed to open %s for reading\n", filename);
    return 0;
  }
  fread(&header, sizeof(header), 1, f);
  fseek(f, header.headerPtr, SEEK_SET);
  fread(&hf, sizeof(hf), 1, f);
  // printf("header len=0x%x . sizeof(Ehfa_Entry)=0x%x\n", (int)(hf.entryHeaderLength), sizeof(Ehfa_Entry));
  fseek(f, hf.rootEntryPtr, SEEK_SET);
  fread(&root, sizeof(Ehfa_Entry), 1, f);

  walk(f, &root, nodata);

  fclose(f);
  if (nodata) {
    printf("nodata=%g?\n", *nodata);
    return 1;
  }
  return 0;
}

#ifdef AUX_MAIN

int main(int argc, char* argv[]) {
  Ehfa_HeaderTag header;
  Ehfa_File hf;
  Ehfa_Entry root;
  FILE* f = fopen("dem.aux", "r");
  fread(&header, sizeof(header), 1, f);
  fseek(f, header.headerPtr, SEEK_SET);
  fread(&hf, sizeof(hf), 1, f);
  // printf("header len=0x%x . sizeof(Ehfa_Entry)=0x%x\n", (int)(hf.entryHeaderLength), sizeof(Ehfa_Entry));
  fseek(f, hf.rootEntryPtr, SEEK_SET);
  fread(&root, sizeof(Ehfa_Entry), 1, f);

  float* nodata = NULL;

  walk(f, &root, (void**)&nodata);

  if (nodata)
    printf("nodata=%g?\n", *nodata);

  fclose(f);
}

#endif
