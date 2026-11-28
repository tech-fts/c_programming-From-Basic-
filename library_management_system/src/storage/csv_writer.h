#ifndef CSV_WRITER_H
#define CSV_WRITER_H

#include <stdio.h>

struct Member;
struct BorrowID;

void write_members_to_csv(struct Member *members, int count, const char *filename);
void write_borrows_to_csv(struct BorrowID *borrows, int count, const char *filename);

#endif // CSV_WRITER_H