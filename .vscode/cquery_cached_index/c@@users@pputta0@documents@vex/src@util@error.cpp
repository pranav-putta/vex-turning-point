#ifndef BCI_ERROR_C_INCLUDED
#define BCI_ERROR_C_INCLUDED

#include "error.h"

void util_PrintHeapError(const std::string *msg)
{
  printf("BCI HEAP ERROR: heap_%s", msg);
}

void util_PrintBlockError(const std::string *msg)
{
  printf("BCI BLOCK ERROR: block_%s", msg);
}

void util_PrintArrayListError(const std::string *msg)
{
  printf("BCI ARRAYLIST ERROR: arrayList_%s", msg);
}

void util_PrintMatrixError(const std::string *msg)
{
  printf("BCI MATRIX ERROR: matrix_%s", msg);
}

#endif //BCI_ERROR_C_INCLUDED
