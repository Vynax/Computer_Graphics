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
void Change_Object(int);

int buildPopupMenu(void)
{
	int menu, obj_Menu, render_mode_Menu, color_mode_Menu, bounding_box_Menu, ax_Menu;
	obj_Menu = glutCreateMenu(object_Menu);
	glutAddMenuEntry("Gourd", 1);
	glutAddMenuEntry("Lamp", 2);
	glutAddMenuEntry("Octahedron", 3);
	glutAddMenuEntry("Teapot", 4);
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
		config.Set_Bounding_Box(true);
		glutPostRedisplay();
		break;
	case 2:
		std::cout << "Off" << std::endl;
		config.Set_Bounding_Box(false);
		glutPostRedisplay();
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
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		config.Set_Render_Mode(1);
		glutPostRedisplay();
		break;
	case 2:
		std::cout << "Line" << std::endl;
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		config.Set_Render_Mode(2);
		glutPostRedisplay();
		break;
	case 3:
		std::cout << "Face" << std::endl;
		glPolygonMode(GL_FRONT, GL_FILL);
		config.Set_Render_Mode(3);
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

void object_Menu(int option) {
	switch (option) {
	case 1:
		std::cout << "Gourd" << std::endl;
		Change_Object(1);
		glutPostRedisplay();
		break;
	case 2:
		std::cout << "Lamp" << std::endl;
		Change_Object(2);
		glutPostRedisplay();
		break;
	case 3:
		std::cout << "Octahedron" << std::endl;
		Change_Object(3);
		glutPostRedisplay();
		break;
	case 4:
		std::cout << "Teapot" << std::endl;
		Change_Object(4);
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

void Change_Object(int which) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	config.setObj_Draw(which);
	glMatrixMode(GL_MODELVIEW);
}