#include "config.h"
#include "screen.h"

void get_config(char* config_file_path, int* height, int* width)
{
	char* message = calloc(255, sizeof(char));

	FILE* config_file = fopen(config_file_path, "r");
	if(!config_file)
	{
		sprintf(message, "Can't open %s", config_file_path);
		perror(message);
		exit(EXIT_FAILURE);
	}

    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, config_file)) != -1) {
        if(strncmp( "WIDTH:", line, 6) == 0)
        	*width = atoi(line+6);
        else if(strncmp("HEIGHT:", line, 7) == 0)
        	*height = atoi(line+7);
    }

	fclose(config_file);
}

void set_config(char* config_file_path, int height, int width)
{
	char* message = calloc(255, sizeof(char));
	FILE* config_file = fopen(config_file_path, "w");
	
	if(!config_file)
	{
		sprintf(message, "Can't open %s", config_file_path);
		perror(message);
		exit(EXIT_FAILURE);
	}
	
	   
    sprintf(message, "WIDTH:%d\n", width);
    fputs(message, config_file);
    sprintf(message, "HEIGHT:%d\n", height);
    fputs(message, config_file);

	fclose(config_file);
}


void option_menu(int* config_height, int* config_width)
{
	show_logo();
    static struct termios oldMask, newMask;
	tcgetattr ( STDIN_FILENO, &oldMask );
    newMask = oldMask;
    newMask.c_lflag &= ~(ICANON); // avoid <enter>
    newMask.c_lflag &= ~(ECHO); // hide text typed
    tcsetattr( STDIN_FILENO, TCSANOW, &newMask );

	int selected = 0, choice = 0; // 0->height 1->width
	do
	{
		printf("%35s%sHAUTEUR%s:%3d%35s%sLARGEUR%s:%3d\n","", (selected)?WHITE_COLOR:REVERSE_BACKGROUND,WHITE_COLOR, *config_height, "", (selected)?REVERSE_BACKGROUND: WHITE_COLOR, WHITE_COLOR, *config_width);
		switch(choice = getchar())
		{
			case 0x41:
				if(!selected) *config_height += 1;
				else *config_width += 1;
				break;
			case 0x42:
				if(!selected) *config_height -= 1;
				else *config_width -= 1;
				break;
			case 0x43:
			case 0x44:
				selected = (selected)?0:1;
				break;
		}
		between(config_height, 5, 15);
		between(config_width, 7, 13);
		if(choice != '\n')  printf ( "\e[%dA", 1 );
	}while(choice != '\n');
    tcsetattr( STDIN_FILENO, TCSANOW, &oldMask );
}