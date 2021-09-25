#include "iGraphics.h"

int ground_width = 800, ground_height = 600, ground_width_start = 240, ground_height_start = 60, ground_width_end = ground_width + ground_width_start, ground_height_end = ground_height + ground_height_start;
int ground_img, side_logo, sound_on, sound_off, toogle_music = 1, reset_img, toogle_pause = 0, pause_btn, play_btn, back_btn, exit_btn;
int snake_head_bottom, snake_head_top, snake_head_left, snake_head_right, snake_body_x, snake_body_y, snake_tail, fruit;
int snake_width = 20, snake_height = 20;
int x[2000], y[2000], d = 1, length = 50, dir = 1, p_d = 0;
int snake_speed = 12, game_over = 0;
int rx = 320, ry = 320, f = 0;
char t_score[50], score[5];


void iDraw()
{

	if (toogle_music == 1 && toogle_pause == 0)
	{

		mciSendString(TEXT("resume  mp3"), NULL, 0, NULL);
	}
	else
	{
		mciSendString(TEXT("pause  mp3"), NULL, 0, NULL);
	}
	if (game_over == 1)
	{
		mciSendString(TEXT("stop mp3"), NULL, 0, NULL);
	}
	iClear();
	iSetColor(30, 30, 30);
	iFilledRectangle(0, 0, 1280, 720);
	iShowImage(ground_width_start, ground_height_start, ground_width, ground_height, ground_img);
	iSetColor(255, 255, 255);
	iRectangle(ground_width_start, ground_height_start, ground_width, ground_height);
	iSetColor(255, 255, 255);
	iText(10, 10, "Press p for pause, r for resume, END for exit.");
	iSetColor(255, 0, 0);
	// Game UI
	iShowImage(10, 450, 200, 200, side_logo);
	iSetColor(255, 255, 255);
	iText(75, 420, "Music", GLUT_BITMAP_9_BY_15);
	if (toogle_music == 1)
	{
		iShowImage(75, 350, 50, 50, sound_on);
	}
	else
	{
		iShowImage(75, 350, 50, 50, sound_off);
	}
	iText(75, 300, "Pause/Play", GLUT_BITMAP_9_BY_15);
	if (toogle_pause == 0)
	{
		iShowImage(75, 230, 50, 50, pause_btn);
	}else{
		iShowImage(75, 230, 50, 50, play_btn);
	}
	iText(25, 175, "Return To Menu or End", GLUT_BITMAP_9_BY_15);
	iShowImage(35, 100, 40, 40, back_btn);
	iShowImage(125, 100, 50, 50, exit_btn);
	//	Score Board
	iSetColor(102, 0, 255);
	iText(1100, 550, "ScoreBoard", GLUT_BITMAP_TIMES_ROMAN_24);
	iSetColor(255, 102, 0);
	iText(1125, 510, "LEVEL 1", GLUT_BITMAP_HELVETICA_18);
	iSetColor(255, 255, 0);
	iText(1075, 450, "Your Current Score", GLUT_BITMAP_9_BY_15);
	sprintf(score, "%d", f);
	iText(1150, 425, score, GLUT_BITMAP_9_BY_15);
	iSetColor(0, 255, 0);
	iText(1100, 350, "Highest Score", GLUT_BITMAP_9_BY_15);
	iText(1150, 325, score, GLUT_BITMAP_9_BY_15);
	//////////////////////////////////////////////////////////////
	// FOR SNAKE MOVEMENT-Start
	//////////////////////////////////////////////////////////////
	if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D'))
	{
		d = 1;
	}
	else if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A'))
	{
		d = 2;
	}
	else if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S'))
	{
		d = 3;
	}
	else if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W'))
	{
		d = 4;
	}
	else
	{
		d = 0;
	}
	for (int i = 0; i < length; i++)
	{
		if (i > 0)
		{

			if (y[i - 1] != y[i])
			{
				if (y[i - 1] > y[i])
				{
					iShowImage(x[i], y[i] - 5, snake_height, snake_width + 5, snake_body_y);
				}
				else
				{
					iShowImage(x[i], y[i], snake_height, snake_width + 5, snake_body_y);
				}
			}
			else if (x[i - 1] != x[i])
			{
				if (x[i - 1] > x[i])
				{
					iShowImage(x[i] - 5, y[i], snake_width + 5, snake_height, snake_body_x);
				}
				else
				{
					iShowImage(x[i], y[i], snake_width + 5, snake_height, snake_body_x);
				}
			}
		}
		else if (i == 0)
		{
			if (dir == 1)
			{
				iShowImage(x[i], y[i] - 5, snake_width, snake_height + 10, snake_head_right);
			}
			else if (dir == 2)
			{
				iShowImage(x[i], y[i] - 5, snake_width, snake_height + 10, snake_head_left);
			}
			else if (dir == 3)
			{
				iShowImage(x[i] - 5, y[i], snake_width + 10, snake_height, snake_head_bottom);
			}
			else if (dir == 4)
			{
				iShowImage(x[i] - 5, y[i], snake_width + 10, snake_height, snake_head_top);
			}
		}
	}

	if (game_over == 0 && toogle_pause == 0)
	{

		for (int i = 999; i > 0; i--)
		{
			x[i] = x[i - 1];
			y[i] = y[i - 1];
		}
	}

	//////////////////////////////////////////////////////////////
	// FOR SNAKE MOVEMENT-End
	/////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////
	// FOR Fruit-Start
	//////////////////////////////////////////////////////////////
	if (x[0] > rx - 20 && x[0] < rx + 20 && y[0] > ry - 20 && y[0] < ry + 20)
	{

		length += 5;
		f = f + 1;
		PlaySound(TEXT("music//food.wav"), NULL, SND_ASYNC);
		rx = (rand() % (ground_width_end - ground_width_start)) + ground_width_start;
		ry = (rand() % (ground_height_end - ground_height_start)) + ground_height_start;
	}
	iShowImage(rx, ry, 30, 30, fruit);
	//////////////////////////////////////////////////////////////
	// FOR Fruit-End
	//////////////////////////////////////////////////////////////
	sprintf(t_score, "Your Score is: %d", f);
	//////////////////////////////////////////////////////////////
	// Game Over-Start
	//////////////////////////////////////////////////////////////
	if (game_over == 1)
	{
		iSetColor(255, 0, 0);
		iFilledRectangle(385, 300, 500, 300);
		iSetColor(255, 255, 255);
		iText(575, 500, "GAME OVER!", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(560, 470, "OPPS! You Eat YourSelf.", GLUT_BITMAP_9_BY_15);
		iText(575, 425, t_score, GLUT_BITMAP_HELVETICA_18);
		iShowImage(615, 325, 60, 60, reset_img);
	}
	if (toogle_pause == 1)
	{
		iSetColor(255,255,255);
		iText(575, 500, "GAME PAUSED!", GLUT_BITMAP_TIMES_ROMAN_24);
	}
	
}

void snake_movement()
{
	if (game_over == 0)
	{

		switch (d)
		{
		case 0:
			if (dir == 1)
			{
				if (x[0] + snake_width >= ground_width_end)
				{
					x[0] = ground_width_start;
				}
				else
				{
					x[0] = x[0] + snake_speed;
					p_d = 1;
				}
			}
			else if (dir == 2)
			{
				if (x[0] <= ground_width_start)
				{
					x[0] = ground_width_end - snake_width;
				}
				else
				{
					x[0] = x[0] - snake_speed;
					p_d = 2;
				}
			}
			else if (dir == 3)
			{
				if (y[0] <= ground_height_start + 10)
				{
					y[0] = ground_height_end - snake_height;
				}
				else
				{
					y[0] = y[0] - snake_speed;
					p_d = 3;
				}
			}
			else if (dir == 4)
			{
				if (y[0] + snake_height + 10 >= ground_height_end)
				{
					y[0] = ground_height_start;
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
				if (x[0] + snake_width + 10 >= ground_width_end)
				{
					x[0] = ground_width_start;
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
				if (x[0] <= ground_width_start)
				{
					x[0] = ground_width_end - snake_width;
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
				if (y[0] <= ground_height_start + 10)
				{
					y[0] = ground_height_end - snake_height;
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
				if (y[0] + snake_height + 10 >= ground_height_end)
				{
					y[0] = ground_height_start;
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
		for (int i = 2; i < length; i++)
		{
			if (x[0] == x[i] && y[0] == y[i])
			{
				iPauseTimer(0);
				PlaySound(TEXT("music//gameover.wav"), NULL, SND_SYNC);
				game_over = 1;
				break;
			}
		}
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
		printf("%d%d%d\n", mx, my, toogle_music);
		if (mx >= 75 && mx <= 125 && my >= 350 && my <= 400)
		{
			if (toogle_music == 0)
			{
				toogle_music = 1;
			}
			else
			{
				toogle_music = 0;
			}
		}
		if (mx >= 75 && mx <= 125 && my >= 230 && my <= 280)
		{
			if (toogle_pause == 0)
			{
				PlaySound(TEXT("music//gameover.wav"), NULL, SND_ASYNC);
				toogle_pause = 1;
				iPauseTimer(0);
			}
			else
			{
				toogle_pause = 0;
				iResumeTimer(0);
			}
		}
		if (mx >= 125 && mx <= 175 && my >= 100 && my <= 150)
		{
			exit(0);
		}
		if (mx >= 615 && mx <= 675 && my >= 325 && my <= 385)
		{
			if (game_over == 1)
			{
				game_over = 0;
				iResumeTimer(0);
				length = 10;
				x[0] = 300;
				y[0] = 300;
				f = 0;
				d = 1;
			}
		}
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
		PlaySound(TEXT("music//gameover.wav"), NULL, SND_ASYNC);
		iPauseTimer(0);
		toogle_pause = 1;
	}
	if (key == 'r')
	{
		if (game_over != 1)
		{
			iResumeTimer(0);
		}
		toogle_pause = 0;
	}
	if (key == 'w' || key == 's' || key == 'a' || key == 'd' && game_over == 0)
	{
		PlaySound(TEXT("music//move.wav"), NULL, SND_ASYNC);
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
	if (key == GLUT_KEY_LEFT || key == GLUT_KEY_UP || key == GLUT_KEY_RIGHT || key == GLUT_KEY_DOWN && game_over == 0)
	{
		PlaySound(TEXT("music//move.wav"), NULL, SND_ASYNC);
	}

	//place your codes for other keys here
}
// void playSound(){
// 	PlaySound(TEXT("music//music.wav"), NULL, SND_ASYNC|SND_NOSTOP);
// }
int main()
{
	//place your own initialization codes here.
	iSetTimer(50, snake_movement);

	iSetColor(255, 255, 255);
	iInitialize(1280, 720, "Gg Snake");
	mciSendString(TEXT("open \"music//music_2.mp3\" type mpegvideo alias mp3"), NULL, 0, NULL);
	mciSendString(TEXT("play mp3 repeat"), NULL, 0, NULL);
	// loading images.
	/* iLoadImage() will return an interger type id
	   for each image you load.
	*/

	snake_head_bottom = iLoadImage("images\\head_bot.png");
	snake_head_top = iLoadImage("images\\head_top.png");
	snake_head_left = iLoadImage("images\\head_left.png");
	snake_head_right = iLoadImage("images\\head_right.png");
	snake_body_x = iLoadImage("images\\body_x.png");
	snake_body_y = iLoadImage("images\\body_y.png");
	snake_tail = iLoadImage("images\\tail.png");
	fruit = iLoadImage("images\\apple1.png");
	ground_img = iLoadImage("images\\board.png");
	side_logo = iLoadImage("images\\logo.png");
	sound_on = iLoadImage("images\\volume.png");
	sound_off = iLoadImage("images\\no-sound.png");
	reset_img = iLoadImage("images\\reset.png");
	pause_btn = iLoadImage("images\\pause.png");
	play_btn = iLoadImage("images\\play.png");
	back_btn = iLoadImage("images\\previous.png");
	exit_btn = iLoadImage("images\\exit.png");

	for (int i = 0; i < 1000; i++)
	{
		x[i] = 0;
		y[i] = 0;
	}

	x[0] = 300;
	y[0] = 300;

	iStart(); // it will start drawing

	return 0;
}
