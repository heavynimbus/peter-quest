#include "node.h"

Position* create_position(int line, int column)
{
	Position* result = malloc(sizeof(Position));
	result->line = line;
	result->column = column;
	return result;
}

NodeValue* create_node_value(int score, Position* initial, Position* move, Position* attack)
{
	NodeValue* result = malloc(sizeof(NodeValue));
	result->score = score;
	result->initial_position = initial;
	result->move_position = move;
	result->attack_position = attack;
	return result;
}

void display_node_value(NodeValue* value)
{
	printf("NodeValue[%d]: initial(%d, %d)\tmove(%d, %d)\tattack(%d, %d)\n",
		value->score, value->initial_position->line, value->initial_position->column,
		value->move_position->line, value->move_position->column,
		value->attack_position->line, value->attack_position->column);
}


Node* create_node(NodeValue* value)
{
	Node* result = malloc(sizeof(Node));

	result->node_list_size = 255;
	result->node_list = calloc(result->node_list_size, sizeof(Node));
	result->nb_arg = 0;
	result->value = value;
	
	return result;
}

void display_node(Node* node, int tab)
{
	for(int i = 0; i < tab; i++)printf("\t");
	if(node->value != NULL)display_node_value(node->value);
	else printf("-- FIRST NODE (no value) --\n");
	for(int i = 0; i < node->nb_arg; i++)
		display_node(node->node_list+i, tab+1);
}


void add_element(Node* node, Node* to_add)
{
	if(node->nb_arg >= node->node_list_size)
	{
		node->node_list_size += 50;
		node->node_list = realloc(node->node_list, node->node_list_size);
	}
	node->node_list[node->nb_arg] = *to_add;
	node->nb_arg++;
}

/*;

void display_node(Node node, int tab)
{
	for(int i = 0; i < tab; i++)printf("\t");
	printf("[value = %d] %d/%d \n", node.value, node.nb_arg, node.node_list_size);
	for(int i = 0; i < node.nb_arg; i++) 
	{
		display_node(node.node_list[i], tab+1);
	}
}

Node* create_node(int value)
{
	Node* result = malloc(sizeof(Node));

	result->node_list_size = 255;
	result->node_list = calloc(result->node_list_size, sizeof(Node));
	result->nb_arg = 0;
	result->value = value;
	
	return result;
}


void add_element(Node* node, int value)
{
	if(node->nb_arg >= node->node_list_size)
	{
		node->node_list_size += 50;
		node->node_list = realloc(node->node_list, node->node_list_size);
	}
	node->node_list[node->nb_arg].value = value;
	node->node_list[node->nb_arg].nb_arg = 0;
	node->node_list[node->nb_arg].node_list_size = 255;
	node->node_list[node->nb_arg].node_list = calloc(node->node_list_size, sizeof(Node));
	node->nb_arg++;

}*/