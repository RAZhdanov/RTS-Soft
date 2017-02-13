#include "Image.h"
#include "LinkedList.h"
int main(int argc, char **argv) {
	
	Image img[10];
	LinkedList list;
	node current_node;
	for (int i = 0; i < 10; i++)
	{
		img[i].load("abe_natsumi.pgm");
		current_node.image_node = &img[i];
		current_node.next = NULL;
		list.insertAtFront(current_node);
	}
	return 0;
}
