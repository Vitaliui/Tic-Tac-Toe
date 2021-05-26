#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define SPACE ' '

void menu();				  		 //	��������� ���� 
void start_game(char choice);		  //	����� ����
char check(void);			  //	��������
void get_move(char symb, char choice);	  //	���
void get_computer_move(void); 		//	���
void disp_matrix(void);       		//	���������� �������� ����


char matrix[3][3] = {		// ������� ����
{SPACE, SPACE, SPACE},
{SPACE, SPACE, SPACE},
{SPACE, SPACE, SPACE}
};

int main()
{
	system("chcp 1251");
    char title[] = "�Tic-Tac-Toe�";
	CharToOem(title, title);
	SetConsoleTitle(title);
    char choice;
    system ("cls");
	menu();
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (WORD) ((0<<4) | 12)); //������������ ��� � ���� ������� 
    do{
    	choice=getch();
	}while(choice<'1' || choice>'3');
    SetConsoleTextAttribute(hConsole, (WORD) ((15<<4) | 0)); //������������ ��� � ���� ������� 
    system ("cls"); // ������� ����� 

	switch (choice)		// ���� ����
	{
    case '1':
    
    case '2': start_game(choice);
       break;
    case '3':
        system ("exit");
        break;
    }
}

void menu() //�������� ���� 
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 		//���������� �������� ������������ �������� 

    SetConsoleTextAttribute(hConsole, (WORD) ((15<<4) | 0)); //������������ ��� � ���� ������� 
    printf("������� ��\n\n");
    
    SetConsoleTextAttribute(hConsole, (WORD) ((11<<4) | 0)); //������������ ��� � ���� ������� 
    printf("1.....��� � �������\n\n");

    SetConsoleTextAttribute(hConsole, (WORD) ((11<<5) | 0)); //������������ ��� � ���� ������� 
    printf("2.....��� � �����\n\n");

    SetConsoleTextAttribute(hConsole, (WORD) ((1<<4) | 14)); //������������ ��� � ���� ������� 
    printf("3.....����� � ��� \n\n");
}

void get_move(char symb, char choice) //ճ�
{
	char x1, y1;
	int x, y;
	if(choice=='1' || choice=='2'&&symb=='X'){
				while(1){
	             printf("������ ����������  %c.\n",symb);
	             printf("�����:");
                 do{
    				x1=getch();
				 }while(x1<'1' || x1>'3');
				 printf("%c\n",x1);
				 printf("��������:");
				 do{
    		     	y1=getch();
				 }while(y1<'1' || y1>'3');
				 printf("%c\n",y1);
				 x=x1-'0'-1; 	// �������� char �� int 
				 y=y1-'0'-1;
				 if (x < 0 || y < 0 || x>2 || y>2 || matrix[x][y] != SPACE)
				 {
					printf("�� ����� ���, ������� �� ���.\n");
			     }
			     else break;
			 	}
			     matrix[x][y] = symb;
    }
    else get_computer_move();

	system ("cls");
}

void start_game(char choice)  //	����� ���
{
    char done;
    int count=0,i,j;
    switch(choice){
		case '1': printf("�� ����� � �������. \n"); break;
		case '2': printf("�� ����� � �����. \n");
	}
	
	done = SPACE;
	disp_matrix(); //���� �������� ����
	do {
		get_move('X',choice); 
		count++;
		disp_matrix();
		done = check(); // �������� �� �������� 
		if (done != SPACE || count==9) break;
		get_move('O',choice); 
		count++;
		disp_matrix(); 
		done = check(); // �������� �� �������� 
	} while (done == SPACE && count<9);
	if (done == 'X')
		switch(choice){
			case '1': printf(" ������ �!\n"); break;
			case '2': printf("�� ������!\n");
		}
	else
		if (done == 'O') 
			switch(choice){
				case '1': printf(" ������ O!\n"); break;
				case '2': printf("������ ���!\n");
		}
		else printf("ͳ��� \n");
	getchar();
	system ("cls");
	for(i=0;i<3;i++)
		for(j=0;j<3;j++)
			matrix[i][j]=SPACE;	//������ ������� ������� 
	main();
}

void get_computer_move(void)  // ������� ���� ���� 
{
	int x, y;
	do{
		x = rand() % 3;		// ���� � ����������� ������� ����� ���� 
		y = rand() % 3;
	}while (matrix[x][y] != SPACE); 

	matrix[x][y] = 'O';
	system ("cls");
}

void disp_matrix(void)  // ������� �������� ���� 
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
		printf("%c | %c | %c", matrix[t][0], matrix[t][1], matrix[t][2]); 	// ���������� �������
		if (t != 2) printf("\n--|---|--\n");       	                                          
	}	
	SetConsoleCursorPosition(hd, cd_4);
	printf("3.������ ��� ������ ��� ��� ��� ���������\n");
	SetConsoleCursorPosition(hd, cd_2);
	printf("1.��� ����������� �� ��������� ��� ������� 3 �� 3 ������\n");
	SetConsoleCursorPosition(hd, cd_3);
	printf("2.������� �� ���� ���������� ���\n");
	SetConsoleCursorPosition(hd, cd_1);
	printf("������� ���:\n");
	SetConsoleCursorPosition(hd, cd_5);
	printf("4.��� ���������� ��������� ������ � ������� ���� ���� ������ ������� ��� ������� ������ ����, ���������� �� ��������, ���������� ��� ����-���� � ���������\n");
	printf("\n");
}

char check(void) // ��������
{
	int t;
	char* p;
	for (t = 0; t < 3; t++) {      // �������� �����
		p = &matrix[t][0];
		if (*p == *(p + 1) && *(p + 1) == *(p + 2)) return *p;
	}
	for (t = 0; t < 3; t++) {     // �������� �������� 
		p = &matrix[0][t];
		if (*p == *(p + 3) && *(p + 3) == *(p + 6)) return *p;
	}

	if (matrix[0][0] == matrix[1][1] && matrix[1][1] == matrix[2][2]) // �������� ��������� 
		return matrix[0][0];

	if (matrix[0][2] == matrix[1][1] && matrix[1][1] == matrix[2][0]) // �������� ��������� 
		return matrix[0][2];
	return SPACE;
}
