#define MENU_OBJECT 0
#define MENU_RENDER_MODE 1
#define MENU_TEXTURING 2
#define MENU_EXIT 3


#include <GL/glut.h>  // GLUT, include glu.h and gl.h


void main_Menu(int);
void object_Menu(int);
void render_Mode_Menu(int);
void color_Mode_Menu(int);
void bounding_Box_Menu(int);
void axis_Menu(int);

int buildPopupMenu(void)
{
	int menu, obj_Menu, render_mode_Menu, color_mode_Menu, bounding_box_Menu, ax_Menu;
	obj_Menu = glutCreateMenu(object_Menu);
	glutAddMenuEntry("Cube", 1);
	glutAddMenuEntry("Teddy bear", 2);
	glutAddMenuEntry("Lamp", 3);
	render_mode_Menu = glutCreateMenu(render_Mode_Menu);
	glutAddMenuEntry("Point", 1);
	glutAddMenuEntry("Line", 2);
	glutAddMenuEntry("Face", 3);
	color_mode_Menu = glutCreateMenu(color_Mode_Menu);
	glutAddMenuEntry("Single Color", 1);
	glutAddMenuEntry("Random Colors", 2);
	bounding_box_Menu = glutCreateMenu(bounding_Box_Menu);
	glutAddMenuEntry("On", 1);
	glutAddMenuEntry("Off", 2);
	ax_Menu = glutCreateMenu(axis_Menu);
	glutAddMenuEntry("On", 1);
	glutAddMenuEntry("Off", 2);
	menu = glutCreateMenu(main_Menu);
	glutAddSubMenu("Object", obj_Menu);
	glutAddSubMenu("Render Mode", render_mode_Menu);
	glutAddSubMenu("Color Mode", color_mode_Menu);
	glutAddSubMenu("Bounding Box", bounding_box_Menu);
	glutAddSubMenu("Axis", ax_Menu);
	// glutAddMenuEntry("Render Mode", MENU_RENDER_MODE);
	// glutAddMenuEntry("Toggle texturing t", MENU_TEXTURING);
	// glutAddMenuEntry("Exit demo Esc", MENU_EXIT);
	return menu;
}

void main_Menu(int option)
{
	switch (option) {
	case MENU_OBJECT:
		//¡K¡K
		break;
	case MENU_RENDER_MODE:
		//¡K.
		break;
	case MENU_TEXTURING:
		//¡K.
		break;
	case MENU_EXIT:
		//¡K.
		break;
	default:
		break;
	}
}

void axis_Menu(int option) {
	switch (option) {
	case 1:
		std::cout << "On" << std::endl;
		break;
	case 2:
		std::cout << "Off" << std::endl;
		break;
	default:
		break;
	}
}


void bounding_Box_Menu(int option) {
	switch (option) {
	case 1:
		std::cout << "On" << std::endl;
		break;
	case 2:
		std::cout << "Off" << std::endl;
		break;
	default:
		break;
	}
}

void color_Mode_Menu(int option) {
	switch (option) {
	case 1:
		std::cout << "Single Color" << std::endl;
		break;
	case 2:
		std::cout << "Random Colors" << std::endl;
		break;
	default:
		break;
	}
}

void render_Mode_Menu(int option) {
	switch (option) {
	case 1:
		std::cout << "Point" << std::endl;
		break;
	case 2:
		std::cout << "Line" << std::endl;
		break;
	case 3:
		std::cout << "Face" << std::endl;
		break;
	default:
		break;
	}
}

void object_Menu(int option) {
	switch (option) {
	case 1:
		std::cout << "Cube" << std::endl;
		break;
	case 2:
		std::cout << "Teddy bear" << std::endl;
		break;
	case 3:
		std::cout << "Lamp" << std::endl;
		break;
	default:
		break;
	}
}
