# Library Management System

Project documentation based on the source reviewed on November 28, 2026.

## 1. Project overview

This is a menu-driven command-line application written in C. It manages books,
members, and borrowing records using arrays of structures. Member and borrowing
records are loaded from CSV files and saved when their management menus close.

The project demonstrates modular C programming, dynamic memory allocation,
console input, record lookup, and file handling. It is partially implemented:
some functions exist without being connected to the menus, and borrowing records
do not yet enforce relationships with books or members.

## 2. Current features

| Area | Implemented behavior | Current limitations |
| --- | --- | --- |
| Main menu | Opens book, member, and borrowing management; validates choices from 0 to 3; handles end of input | Submenus still use `scanf` rather than the shared input helpers |
| Books | Add records with generated IDs and an initial `available` status | View, update, and delete functions exist but their menu options only print messages; no book CSV storage |
| Members | Add, view, update, delete, load, and save records | View shows only ID, name, and address; update menu displays only two of five supported choices |
| Borrowings | Create, view, change status, delete, load, and save records | Member and book IDs are not checked against existing records; status is free text |
| Reports | Print total borrowing records and a line for each record | No filtering, overdue calculations, or file export |
| Shared utilities | Memory wrappers, error reporting, line input, and integer validation | Adoption across record operations is incomplete |

## 3. Repository structure

```text
library_management_system/
├── include/
│   ├── book.h                  # Book structure and public operations
│   ├── member.h                # Member structure and public operations
│   └── borrowing.h             # BorrowID structure and public operations
├── src/
│   ├── main.c                  # Entry point and management menus
│   ├── core/                   # Memory allocation and error reporting
│   ├── utils/                  # Console input and validation helpers
│   ├── storage/                # Member and borrowing CSV readers/writers
│   └── modules/
│       ├── book/book.c
│       ├── member/member.c
│       ├── borrowing/borrowing.c
│       └── reports/            # Borrowing report implementation and header
├── data/
│   ├── books.csv               # Empty; not connected to the application
│   ├── members.csv
│   └── borrowings.csv
├── tests/                      # Interactive module test programs
├── docs/project_documentation.md
├── build/                      # Available build output directory
├── Makefile                    # Currently empty
├── README.md                   # Currently empty
└── library_system              # Existing executable
```

## 4. Build and run

Requirements: a C compiler supporting C11, the standard C library, and a terminal.
No external libraries are required. The commands below use GCC and run from the
project root. The empty `Makefile` does not currently provide build targets.

```bash
mkdir -p build
gcc -std=c11 -Wall -Wextra -Wpedantic -Iinclude \
    src/main.c \
    src/core/error.c src/core/memory.c \
    src/utils/input.c src/utils/validation.c \
    src/storage/csv_reader.c src/storage/csv_writer.c \
    src/modules/book/book.c \
    src/modules/member/member.c \
    src/modules/borrowing/borrowing.c \
    src/modules/reports/reports.c \
    -o build/library_system
./build/library_system
```

Run from the project root because paths such as `data/members.csv` are relative
to the working directory. Rebuilding ensures the executable matches the current
source; the existing root executable may reflect an earlier version.

## 5. Program flow and usage

The main menu offers:

```text
1. Book Management
2. Member Management
3. Borrowing Management
0. Exit
```

Each management function allocates a zero-initialized array with capacity for
100 records. Arrays are released when their submenu closes; there is no automatic
capacity growth.

### Books

Option 1 asks for a number and collects a title, author, and publication year.
IDs are generated as `B001`, `B002`, and so on. The add loop currently treats the
requested number as the target total count, rather than the number of additional
books. For example, with two existing books, entering `3` adds one book.

Options 2, 3, and 4 currently print placeholder messages. Although `viewBooks`,
`updateBook`, and `deleteBook` are implemented in the module, the menu does not
call them. All book records are discarded when the submenu closes.

### Members

Entering this menu loads `data/members.csv`. Options 1–4 add, view, update, and
delete members. New records collect name, phone, email, and address, with generated
IDs such as `M001`. The normal zero-initialized unused slots start with a borrowed
book count of zero, but `addMember` does not explicitly reset that field when
reusing a slot after deletion.

The update implementation accepts choices 1–5 for name, address, phone, email,
and borrowed book count, although only name and address appear in its prompt.
Returning with option 0 rewrites the member CSV and releases the array.

### Borrowings

Entering this menu loads `data/borrowings.csv`.

| Option | Action |
| --- | --- |
| 1 | Create records containing member ID, book ID, address, and status |
| 2 | Find a borrowing ID and replace its status |
| 3 | Display borrowing ID, member ID, book ID, and status |
| 4 | Delete a record by borrowing ID |
| 5 | Print the borrowing report |
| 0 | Save the borrowing CSV and return to the main menu |

Borrowing IDs also use the `B001` pattern. The option labelled “Return a Book”
only changes a borrowing status; it does not update book availability or a member's
borrowed book count. The report includes every borrowing record regardless of
status.

Member and borrowing menus print an outdated “functionality is not implemented
yet” message on exit, even though their operations are connected.

## 6. Data models

String lengths below are array sizes in bytes. A null-terminated string can store
at most one byte fewer than its array size.

| Structure | Fields |
| --- | --- |
| `struct Book` | `id[20]`, `title[100]`, `author[100]`, `int year`, `status[20]` |
| `struct Member` | `member_id[20]`, `name[100]`, `phone[20]`, `email[100]`, `address[200]`, `int borrowed_books_count` |
| `struct BorrowID` | `borrowing_id[20]`, `member_id[20]`, `book_id[20]`, `ID[20]`, `address[200]`, `status[100]` |

The additional borrowing field `ID` is read and written by CSV storage, but the
interactive creation function does not populate it or define its purpose.
IDs are generated from the current record count plus one. There is no uniqueness
check, so deleting a record and adding another can create a duplicate ID.

## 7. CSV storage

### Member format

```csv
Member ID,Name,Phone,Email,Address,Borrowed Books Count
M001,Example Member,09123456789,member@example.com,Yangon,0
```

### Borrowing format

```csv
Borrow ID,Member ID,Book ID,ID,Address,Status
B001,M001,B001,,Yangon,borrowed
```

These rows illustrate the expected formats; all three data files were empty at
the time of review.

Readers skip the first line as a header without validating its contents. Each
subsequent row must contain exactly six comma-separated fields. Fields must fit
their destination arrays, and the member borrowed book count must be a
nonnegative integer within the `int` range. Invalid rows are skipped with a
diagnostic. Readers stop at the supplied capacity and use a 512-byte line buffer.

Quoted fields, escaped commas, and embedded newlines are not supported. Do not
enter commas in text fields with the current implementation. Writers overwrite
the entire file, including its header, when the corresponding submenu closes.
There is no incremental save, backup, or atomic replacement. Rows skipped during
loading, or excluded by capacity, are not preserved by the later rewrite.

## 8. Shared components

- `core/memory`: wraps `malloc`, `calloc`, `realloc`, and `free`; rejects zero-sized
  allocation requests and checks multiplication overflow for zeroed allocations.
- `core/error`: prints descriptive errors and messages based on `errno`.
- `utils/input`: reads bounded lines and integers; distinguishes success, invalid
  input, end of input, and I/O errors through `InputResult`.
- `utils/validation`: checks nonblank text, parses integers with `strtol`, and
  validates inclusive ranges.

Currently, only the main menu uses the shared integer input function. Other menus
and record operations mostly read directly with `scanf`.

## 9. Verification and existing tests

During this documentation review:

- The application compiled successfully with GCC using the C11 build command
  above and `-Wall -Wextra -Wpedantic`, without diagnostics.
- A freshly compiled temporary executable passed smoke checks for normal exit,
  invalid main-menu text, an out-of-range main-menu choice, and end of input.
- These smoke checks did not open management menus or modify CSV data.
- A syntax check of the existing test sources found an incompatible argument in
  `tests/test_book.c`: `updateBook(books, &count)` passes an `int *`, but the
  function expects an `int` count.

The files in `tests/` are separate interactive programs, each with its own `main`.
They require manual input and print pass/fail messages rather than providing a
fully automated suite. They should be compiled separately from `src/main.c`.
Some checks are weak: the book update check expects the original title, and the
view tests do not verify displayed output. The member and borrowing test arrays
are not zero-initialized, which can leave fields not filled by creation functions
indeterminate. No complete test-suite pass is claimed here.

## 10. Known issues and next steps

1. **Correct unsafe input.** Book title and author reads have no field widths.
   Borrowing creation reads up to 99 characters into 20-byte member and book ID
   arrays. Replace these reads with bounded shared input helpers.
2. **Enforce capacity and validate submenu choices.** `addBook` has no capacity
   parameter or bounds check. Several submenu `scanf` calls ignore failed reads,
   which can leave choices stale or uninitialized and prevent reliable recovery.
3. **Complete book integration.** Connect view, update, and delete menu actions;
   add book CSV loading and saving; correct the add-count behavior.
4. **Preserve record identity and initialization.** Generate unique IDs independent
   of array length, reset newly added records explicitly, and define or remove the
   extra borrowing `ID` field.
5. **Implement borrowing rules.** Validate member and book existence, prevent
   conflicting loans, define allowed statuses, and synchronize book availability
   and member borrowed book counts. Dates, due dates, and fines are not implemented.
6. **Improve persistence.** Support escaped CSV fields, handle oversized lines,
   preserve data when loading fails or exceeds capacity, and save through an
   atomic replacement with checked write results.
7. **Align menus and messages.** Display every supported member update option and
   remove obsolete implementation messages.
8. **Improve project tooling.** Populate the Makefile and README, fix the book test
   signature, and add repeatable tests for CRUD behavior, persistence, capacity,
   malformed input, and record relationships.
