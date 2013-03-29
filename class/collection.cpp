#include "collection.h"

#if debug
#include <stdio.h>
#endif

collection_c::collection_c(){
  Max = 32;
  Count = 0;
  daten = new int*[Max];
}

collection_c::~collection_c() {
  delete daten;
}

int collection_c::add(zeiger data) {
  CheckSize();
  daten[Count] = (int *)data;
  Count = Count + 1;
  return Count-1;
}

int collection_c::CheckSize() {
  if ((Count+1) < Max) {
    int ** temp;
    temp = new int*[Max*2];
    memcpy(temp,daten,sizeof(zeiger)*Max);
    Max = Max*2;
    daten = temp;
  }
  return 0;
}

zeiger collection_c::getByIndex(int i) {
  if (i<Count) {
    zeiger x = daten[i];
    return x;
  } else {
    return NULL;
  }
}

int collection_c::setById(int i,zeiger data) {
  if (i < Count) {
    daten[i] = (int*)data;
  }
  return i;
}

int collection_c::deleteByIndex(int i) {
  for (int x=i; x<Count-1; x++) {
    daten[x] = daten[x+1];
  }
  Count = Count - 1;
  return 0;
}
