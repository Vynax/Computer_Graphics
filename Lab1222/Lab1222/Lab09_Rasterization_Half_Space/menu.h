#define MENU_OBJECT 0
#define MENU_RENDER_MODE 1
#define MENU_TEXTURING 2
#define MENU_EXIT 3


#include <GL/glut.h>  // GLUT, include glu.h and gl.h


void main_Menu(int);
void grid_Size_Menu(int);

int buildPopupMenu(void)
{
	int menu;//, obj_Menu, render_mode_Menu, color_mode_Menu, bounding_box_Menu, ax_Menu;
	int grid_Menu;

	grid_Menu = glutCreateMenu(grid_Size_Menu);
	glutAddMenuEntry("9 x 9", 1);
	glutAddMenuEntry("25 x 25", 2);
	glutAddMenuEntry("85 x 85", 3);
	menu = glutCreateMenu(main_Menu);
	glutAddSubMenu("Grid Size", grid_Menu);

	return menu;
}

void main_Menu(int option)
{
	switch (option) {
	case MENU_OBJECT:
		//……
		break;
	case MENU_RENDER_MODE:
		//….
		break;
	case MENU_TEXTURING:
		//….
		break;
	case MENU_EXIT:
		//….
		break;
	default:
		break;
	}
}

void grid_Size_Menu(int option) {
	switch (option) {
	case 1:
		std::cout << "9 x 9" << std::endl;
		config.Set_Grid_Amount(9);
		glutPostRedisplay();
		break;
	case 2:
		std::cout << "25 x 25" << std::endl;
		config.Set_Grid_Amount(25);
		glutPostRedisplay();
		break;
	case 3:
		std::cout << "85 x 85" << std::endl;
		config.Set_Grid_Amount(85);
		glutPostRedisplay();
		break;
	default:
		break;
	}
}
