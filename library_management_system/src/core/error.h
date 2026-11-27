#ifndef ERROR_H
#define ERROR_H

void error_report(const char *operation, const char *message);
void error_report_errno(const char *operation);

#endif