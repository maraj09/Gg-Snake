#include "iGraphics.h"

int image1, image2, image3;
int snake_width = 23, snake_height = 21, snake_position_x = 225, snake_position_y = 224;
int x[200], y[200], d = 1, length = 100, dir = 1, p_d = 0;
int snake_speed = 3;

/*
function iDraw() is called again and again by the system.
*/

void iDraw()
{
	//place your drawing codes here

	iClear();

	/* iShowImage():
	Here, first 2 parameters are the lower left
	corner position of image you want to put.
	3rd and 4th parameters are the widht and the height
	of the image.
	Last parameter is the id of the image you want to put.
	*/
	iSetColor(38, 52, 69);
	iFilledRectangle(0, 0, 640, 480);
	iShowImage(125, 70, 400, 350, image3);
	/*iShowImage(0, 20, 200, 200, image2);
	iRotate(pic_x,pic_y,45); /*angle in degree*/

	/*iShowImage(pic_x, pic_y, 100, 100, image1);*/
	iSetColor(255, 255, 255);
	iRectangle(125, 70, 400, 350);

	iSetColor(255, 255, 255);
	iText(10, 10, "Press p for pause, r for resume, END for exit.");
	iSetColor(255, 0, 0);

	if (GetAsyncKeyState(VK_RIGHT))
	{
		d = 1;
	}
	else if (GetAsyncKeyState(VK_LEFT))
	{
		d = 2;
	}
	else if (GetAsyncKeyState(VK_DOWN))
	{
		d = 3;
	}
	else if (GetAsyncKeyState(VK_UP))
	{
		d = 4;
	}
	else
	{
		d = 0;
	}

	switch (d)
	{
	case 0:
		if (dir == 1)
		{
			if (x[0] >= 500)
			{
				x[0] = 125;
			}
			else
			{
				x[0] = x[0] + snake_speed;
				p_d = 1;
			}
		}
		else if (dir == 2)
		{
			if (x[0] <= 125)
			{
				x[0] = 500;
			}
			else
			{
				x[0] = x[0] - snake_speed;
				p_d = 2;
			}
		}
		else if (dir == 3)
		{
			if (y[0] <= 71)
			{
				y[0] = 398;
			}
			else
			{
				y[0] = y[0] - snake_speed;
				p_d = 3;
			}
		}
		else if (dir == 4)
		{
			if (y[0] >= 398)
			{
				y[0] = 71;
			}
			else
			{
				y[0] = y[0] + snake_speed;
				p_d = 4;
			}
		}
		else
		{
			d = 0;
		}
		break;
	case 1:
		if (p_d != 2)
		{
			if (x[0] >= 500)
			{
				x[0] = 125;
			}
			else
			{
				dir = 1;
				x[0] = x[0] + snake_speed;
			}
		}
		else
		{

			dir = 2;
			x[0] = x[0] - snake_speed;
		}
		break;
	case 2:
		if (p_d != 1)
		{
			if (x[0] <= 125)
			{
				x[0] = 500;
			}
			else
			{
				x[0] = x[0] - snake_speed;
				dir = 2;
			}
		}
		else
		{
			dir = 1;
			x[0] = x[0] + snake_speed;
		}
		break;
	case 3:
		if (p_d != 4)
		{
			if (y[0] <= 71)
			{
				y[0] = 398;
			}
			else
			{
				dir = 3;
				y[0] = y[0] - snake_speed;
			}
		}
		else
		{
			dir = 4;
			y[0] = y[0] + snake_speed;
		}

		break;
	case 4:
		if (p_d != 3)
		{
			if (y[0] >= 398)
			{
				y[0] = 71;
			}
			else
			{
				dir = 4;
				y[0] = y[0] + snake_speed;
			}
		}
		else
		{
			dir = 3;
			y[0] = y[0] - snake_speed;
		}

		break;
	}

	for (int i = 0; i < length; i++)
	{
		iFilledRectangle(x[i], y[i], snake_width, snake_height);
	}
	for (int i = 199; i > 0; i--)
	{
		x[i] = x[i - 1];
		y[i] = y[i - 1];
	}
}

/*
function iMouseMove() is called when the user presses and drags the mouse.
(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
	//place your codes here
}

/*
	function iPassiveMouse() is called when the user moves the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iPassiveMouse(int mx, int my)
{
	//place your codes here
}

/*
function iMouse() is called when the user presses/releases the mouse.
(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		//place your codes here
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		//place your codes here
	}
}

/*
function iKeyboard() is called whenever the user hits a key in keyboard.
key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{

	if (key == 'p')
	{
		//do something with 'q'
		iPauseTimer(0);
	}
	if (key == 'r')
	{
		iResumeTimer(0);
	}
	if (key == 'w')
	{
	}

	//place your codes for other keys here
}

/*
function iSpecialKeyboard() is called whenver user hits special keys like-
function keys, home, end, pg up, pg down, arraows etc. you have to use
appropriate constants to detect them. A list is:
GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{

	if (key == GLUT_KEY_END)
	{
		exit(0);
	}

	//place your codes for other keys here
}

int main()
{
	//place your own initialization codes here.

	iSetColor(255, 255, 255);
	iInitialize(640, 480, "Fatty Snake");

	// loading images.
	/* iLoadImage() will return an interger type id
	   for each image you load.
	*/

	
	image3 = iLoadImage("images\\Chessboard.png");

	for (int i = 0; i < 200; i++)
	{
		x[i] = 0;
		y[i] = 0;
	}
	x[0] = 200;
	y[0] = 200;
	iStart(); // it will start drawing

	return 0;
}
