#include <stdio.h>

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
	scanf("%c", &list[index].name);

	printf("Enter email: ");
	scanf("%c", &list[index].email);

	printf("Enter phone number: ");
	scanf("%i", &list[index].phone_number);

	printf("Enter address: ");
	scanf("%c", &list[index].address);
	
}

void view_contact_list (struct contact list[], int total)
{
	if (total == 0){
		printf("no contact found...");
	}
	for (int i =0; i < total; i++){
		printf("name: %c",list[i].name);
		printf("email: %c", list[i].email);
		printf("phone_number: %i", list[i].phone_number);
		printf("address: %c", list[i].address);
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
		add_all_contact(contact_list, count_list);
		printf("Done enter contact list");
	}
	else if (option == 2){
		view_contact_list(contact_list, count_list);
	}
}

