#include "main.h"

typedef struct
{
    int line;
    int column;
}Position;

Position* create_position(int line, int column);

typedef struct {
	Position* initial_position;
	Position* move_position;
	Position* attack_position;
	int score;
}NodeValue;

NodeValue* create_node_value(int score, Position* initial, Position* move, Position* attack);

void display_node_value(NodeValue* value);


struct node
{
	struct node* node_list;
	int node_list_size;
	int nb_arg;
	NodeValue* value;
};
typedef struct node Node;


Node* create_node(NodeValue* value);

void display_node(Node* node, int tab);

void add_element(Node* node, Node* to_add);