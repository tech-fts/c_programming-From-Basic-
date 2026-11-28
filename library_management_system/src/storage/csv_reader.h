#ifndef CSV_READER_H
#define CSV_READER_H

struct Member;
struct BorrowID;

void read_members_from_csv(struct Member *members, int *count, int capacity, const char *filename);
void read_borrows_from_csv(struct BorrowID *borrows, int *count, int capacity, const char *filename);

#endif // CSV_READER_H