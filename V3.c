#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define SPACE ' '

void menu();				  		 //	Створення меню 
void start_game(char choice);		  //	Режим игры
char check(void);			  //	Проверка
void get_move(char symb, char choice);	  //	Ход
void get_computer_move(void); 		//	Бот
void disp_matrix(void);       		//	Прорисовка ігрового поля


char matrix[3][3] = {		// Матриця ігри
{SPACE, SPACE, SPACE},
{SPACE, SPACE, SPACE},
{SPACE, SPACE, SPACE}
};

int main()
{
	system("chcp 1251");
    char title[] = "«Tic-Tac-Toe»";
	CharToOem(title, title);
	SetConsoleTitle(title);
    char choice;
    system ("cls");
	menu();
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (WORD) ((0<<4) | 12)); //Встановлюємо фон і колір символів 
    do{
    	choice=getch();
	}while(choice<'1' || choice>'3');
    SetConsoleTextAttribute(hConsole, (WORD) ((15<<4) | 0)); //Встановлюємо фон і колір символів 
    system ("cls"); // Очищаємо екран 

	switch (choice)		// Вибір меню
	{
    case '1':
    
    case '2': start_game(choice);
       break;
    case '3':
        system ("exit");
        break;
    }
}

void menu() //Створюєм меню 
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 		//Дескриптор пристрою стандартного введення 

    SetConsoleTextAttribute(hConsole, (WORD) ((15<<4) | 0)); //Встановлюємо фон і колір символів 
    printf("Виберіть дію\n\n");
    
    SetConsoleTextAttribute(hConsole, (WORD) ((11<<4) | 0)); //Встановлюємо фон і колір символів 
    printf("1.....Гра з людиною\n\n");

    SetConsoleTextAttribute(hConsole, (WORD) ((11<<5) | 0)); //Встановлюємо фон і колір символів 
    printf("2.....Гра с ботом\n\n");

    SetConsoleTextAttribute(hConsole, (WORD) ((1<<4) | 14)); //Встановлюємо фон і колір символів 
    printf("3.....Вихід з гри \n\n");
}

void get_move(char symb, char choice) //Хід
{
	char x1, y1;
	int x, y;
	if(choice=='1' || choice=='2'&&symb=='X'){
				while(1){
	             printf("Вкажіть координати  %c.\n",symb);
	             printf("рядок:");
                 do{
    				x1=getch();
				 }while(x1<'1' || x1>'3');
				 printf("%c\n",x1);
				 printf("стовпець:");
				 do{
    		     	y1=getch();
				 }while(y1<'1' || y1>'3');
				 printf("%c\n",y1);
				 x=x1-'0'-1; 	// Прирівнює char до int 
				 y=y1-'0'-1;
				 if (x < 0 || y < 0 || x>2 || y>2 || matrix[x][y] != SPACE)
				 {
					printf("Не вірний хід, спробуй ще раз.\n");
			     }
			     else break;
			 	}
			     matrix[x][y] = symb;
    }
    else get_computer_move();

	system ("cls");
}

void start_game(char choice)  //	Режим гри
{
    char done;
    int count=0,i,j;
    switch(choice){
		case '1': printf("Ви граєте з людиною. \n"); break;
		case '2': printf("Ви граєте з ботом. \n");
	}
	
	done = SPACE;
	disp_matrix(); //вивід ігрового поля
	do {
		get_move('X',choice); 
		count++;
		disp_matrix();
		done = check(); // Перевірка на перемогу 
		if (done != SPACE || count==9) break;
		get_move('O',choice); 
		count++;
		disp_matrix(); 
		done = check(); // Перевірка на перемогу 
	} while (done == SPACE && count<9);
	if (done == 'X')
		switch(choice){
			case '1': printf(" Переміг Х!\n"); break;
			case '2': printf("Ти переміг!\n");
		}
	else
		if (done == 'O') 
			switch(choice){
				case '1': printf(" Переміг O!\n"); break;
				case '2': printf("Переміг бот!\n");
		}
		else printf("Нічия \n");
	getchar();
	system ("cls");
	for(i=0;i<3;i++)
		for(j=0;j<3;j++)
			matrix[i][j]=SPACE;	//Чистка значень матриці 
	main();
}

void get_computer_move(void)  // Функція ходу бота 
{
	int x, y;
	do{
		x = rand() % 3;		// шукає в випадковому порядку пусте поле 
		y = rand() % 3;
	}while (matrix[x][y] != SPACE); 

	matrix[x][y] = 'O';
	system ("cls");
}

void disp_matrix(void)  // Функція ігрового поля 
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hd = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cd_1;
	COORD cd_2;
	COORD cd_3;
	COORD cd_4;
	COORD cd_5;
	cd_1.X = 25;
	cd_1.Y = 0;
	cd_2.X = 25;
	cd_2.Y = 1;
	cd_3.X = 25;
	cd_3.Y = 2;
	cd_4.X = 25;
	cd_4.Y = 3;
	cd_5.X = 25;
	cd_5.Y = 4;
	
  	int t;
	for (t = 0; t < 3; t++)
	{
		printf("%c | %c | %c", matrix[t][0], matrix[t][1], matrix[t][2]); 	// Прорисовка матриці
		if (t != 2) printf("\n--|---|--\n");       	                                          
	}	
	SetConsoleCursorPosition(hd, cd_4);
	printf("3.Перший хід робить той хто грає хрестиком\n");
	SetConsoleCursorPosition(hd, cd_2);
	printf("1.Гра проводиться на клітинному полі розміром 3 на 3 комірок\n");
	SetConsoleCursorPosition(hd, cd_3);
	printf("2.Гравець не може пропустити хід\n");
	SetConsoleCursorPosition(hd, cd_1);
	printf("Правила гри:\n");
	SetConsoleCursorPosition(hd, cd_5);
	printf("4.Гра закінчується перемогою одного з гравців якщо його фігури зайняли три суміжних комірок поля, розташовані по вертикалі, горизонталі або будь-який з діагоналей\n");
	printf("\n");
}

char check(void) // Перевірка
{
	int t;
	char* p;
	for (t = 0; t < 3; t++) {      // Перевірка рядків
		p = &matrix[t][0];
		if (*p == *(p + 1) && *(p + 1) == *(p + 2)) return *p;
	}
	for (t = 0; t < 3; t++) {     // Перевірка стовпців 
		p = &matrix[0][t];
		if (*p == *(p + 3) && *(p + 3) == *(p + 6)) return *p;
	}

	if (matrix[0][0] == matrix[1][1] && matrix[1][1] == matrix[2][2]) // Перевірка діагоналей 
		return matrix[0][0];

	if (matrix[0][2] == matrix[1][1] && matrix[1][1] == matrix[2][0]) // Перевірка діагоналей 
		return matrix[0][2];
	return SPACE;
}
