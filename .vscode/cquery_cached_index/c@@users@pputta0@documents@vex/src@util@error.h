#include "main.h"

#ifndef BCI_ERROR_H_INCLUDED
#define BCI_ERROR_H_INCLUDED

void util_PrintHeapError(const std::string *msg);
void util_PrintBlockError(const std::string *msg);
void util_PrintArrayListError(const std::string *msg);
void util_PrintMatrixError(const std::string *msg);

#endif //BCI_ERROR_H_INCLUDED
