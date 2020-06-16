#include "libmx.h"

void mx_push_back(t_list **list, void *data) {
	t_list *new_node = mx_create_node(data);
	t_list *temp = NULL;
	if(list) {
		if(*list) {
			temp = *list;

			while(temp->next) {
				temp = temp->next;
			}
			temp->next = new_node;
		}
		else
			*list = new_node;
}
}
