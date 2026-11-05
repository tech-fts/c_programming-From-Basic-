#include <stdio.h>
#include <string.h>

#define Max_count 100

struct contact {
	char name[50];
	char email[200];
	int phone_number;
	char address[500];
};

void add_all_contact(struct contact list[], int index)
{
	printf("Enter name: ");
	scanf("%s", list[index].name);

	printf("Enter email: ");
	scanf("%s", list[index].email);

	printf("Enter phone number: ");
	if (scanf("%d", &list[index].phone_number) != 1) {
		printf("Invalid phone number; enter digits only.\n");
		return;
	}

	printf("Enter address: ");
	scanf("%s", list[index].address);

	printf("address is %s", list[index].address);
	
}

void view_contact_list (struct contact list[], int total)
{
	if (total == 0){
		printf("no contact found...");
	}
	for (int i =0; i < total; i++){
		printf("name: %s",list[i].name);
		printf("email: %s", list[i].email);
		printf("phone_number: %i", list[i].phone_number);
		printf("address: %s", list[i].address);
	}
}

int main (void)
{
	struct contact contact_list[Max_count];
	int option, count_list = 0;

	printf("Enter count list : ");
	scanf("%i", &count_list);

	printf("Enter 1 to add: ");
	scanf("%i", &option);

	if (option == 1){
		add_all_contact(contact_list, count_list - 1);
	}
	else if (option == 2){
		view_contact_list(contact_list, count_list);
	}
}
