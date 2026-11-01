#include <stdio.h>

#define count 100

struct contact {
	char name[50];
	char email[200];
	int phone_number;
	char address[500];
};

void add_all_contact(struct contact *c1, char *contact_list)
{
	printf("Enter name :");
	scanf("%s", c1->name);

	printf("Enter email :");
	scanf("%s", c1->email);

	printf("Enter phone number :");
	scanf("%d", &c1->phone_number);

	printf("Enter address :");
	scanf("%s", c1->address);

	printf("name of the contact is %s.", c1->name);
	printf("email of the contact is %s.", c1->email);
	printf("phone number of the contact is %d.", c1->phone_number);
	printf("address of the contact is %s.", c1->address);


}

int main (void)
{
	char contact_list[count];
	struct contact c1;
	add_all_contact(&c1, contact_list, count);
}

