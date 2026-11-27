#ifndef VALIDATION_H
#define VALIDATION_H

int validation_is_nonempty(const char *text);
int validation_parse_int(const char *text, int *value);
int validation_is_in_range(int value, int min_value, int max_value);

#endif