#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Two Players against each other human vs computer 
// Computer's Strategy : Plays to win if not winning, Plays to block enemy if not blocking ,Plays randomnly
// Programm checks every turn who wins after players ending their moves

void matrix_print(char m[7][7]);   										// prints the 7x7 matrix 
int input_data(char m[7][7],char in , int a);							// let the user enter data in matrix	
void play_game(char m[7][7], char disk);
int win_check(char m[7][7],char disk);									// checks who wins 
int player2_choose(int p1);												// choose player 2 based on player 1
void computer_move(char m[7][7],char disk_enemy,char disk_computer);	//**NEW** Computer's strategy style
int check_win_move(char m[7][7],char disk);								// finds move that wins

static char game_matrix[7][7]; 											// 7x7 matrix initialized with null characters

int main(int argc, char *argv[]) {
	
	int player1 , player2 ;
	
	printf("Welcome to the 4-in-a-row Game in C!\n\n");
	printf("Choose type of Player :\n");
	
	// loop gets the correct type of players 
	while(1){
		// Player 1 is chosen by the user
		printf("Player 1 : '1' for Human , '2' for Computer :");
		scanf("%d",&player1);
		player2 = player2_choose(player1); 	// call function ,player2, for player 2
		if(player2==1 || player2==2){ 		// if correct type of players returned
			break;							// break loop 
		}
		else if(player2==3) {				// if wrong type of players returned 	
			printf("\nWrong Type!!\n");		// user gives again type
		}
	}
	// Players Disks
	printf("Player 1 : has disk '+'.\n");
	printf("Player 2 : has disk '*'.\n");
	printf("START OF THE GAME \n\n\n");
	
	char disk1 = '+', disk2 = '*' ;
	
	// initial game_matrix 7th row with '_' character
	int column ;
    for(column=0; column<7; column++){  
		game_matrix[6][column]='_';	
	}
	
	// Start of the game 
	printf("Game Table\n");
	matrix_print(game_matrix);

	int vict = 0, col , count_move = 1 ;		
	while( vict == 0 ){		
		
		// Start of each turn
		printf("_____Turn %d_____ \n\n",count_move);
		
		
		// _____________Player 1 : Human or Computer_______________  
		if (player1 == 1){									// Player 1 Human 
			printf("You Play '+' - Move %d:\n",count_move);
			play_game(game_matrix, disk1);	
		}
		else if (player1 == 2){								// Player 1 Computer
			computer_move(game_matrix,disk2,disk1);			// disk2 to check if player 2 wins
			printf("Computer Play - Move %d: \n",count_move);
			matrix_print(game_matrix);
			printf("\n\nNow, is your turn!!\n\n");
		}
		vict = win_check(game_matrix,disk1);	// returns 1 for victory
		if(vict == 1){
			if (player1 == 1)						// Human win	
				printf("Y O U   W O N!!!\n\n");						// if player 1 wins first
				break;												// break loop not let player 2 play
			if (player1 == 2)						// Computer win		 
				printf("YOU LOSE!!\nCOMPUTER   W O N!!!\n\n");	
				break;
		}
		
		
		// _____________Player 2 : Human or Computer_______________
		if (player2 == 1 ){ 										// Player 2 Human
			printf("You Play '*' - Move %d:\n",count_move);
			play_game(game_matrix, disk2);
		}
		else if (player2 == 2){										// Player 2 Computer
			computer_move(game_matrix,disk1,disk2);					// disk1 to check if player 1 wins
			printf("Computer Play - Move %d:\n\n",count_move);
			matrix_print(game_matrix);
			printf("\n\nNow, is your turn!!\n\n");
		}
		vict = win_check(game_matrix,disk2);  
		if(vict == 1){
			if (player2 == 1)										// Human win
				printf("Y O U   W O N!!!\n\n");
			if (player2 == 2)										// Computer win
				printf("YOU LOSE!!\nCOMPUTER   W O N!!!\n\n");
			
		}
		// End of each turn 
		printf("______________________________________________\n\n\n");
		count_move+=1; 
	}

	printf("END OF GAME");
	return 0;
}

int player2_choose(int p1){	
	// Returns type of Player 2
	// Return 1 : for Human 
	// Return 2 : for Computer 
	// Return 3 : for wrong choise of player
		if(p1==1){ 														// if player 1 is '1' Human
			printf("\nPlayer 1 is Human.\nPlayer 2 is Computer.\n\n");
			return 2 ;													// returns 2, for player 2
			}		
		else if (p1==2){
			printf("\nPlayer 1 is Computer.\nPlayer 2 is Human.\n\n");	// if player 1 is '2' Computer
			return 1 ;													// returns 1, for player 2
		}
		else{															// else returns 3
			return 3 ;
		}
}

void play_game(char game_matrix[7][7], char disk) {
	
	int col = 0;
	int flg_ovrflow = 0 , wrong_col = 0 ;  
	// Loop : while input_data returns 1 (overflow) or user gave wrong column 
	do{
		printf("Choose column to put your disk :");				
		scanf("%d",&col);	
		if (col < 1 || col > 7){				// if player chooses other than 1 to 7 column
			wrong_col = 1 ;						// wrong_col flag set 1
			printf("Wrong Column!! Please give from 1 to 7 .\nPlay again !!\n\n"); 
		}																			
		else{
			wrong_col = 0 ; 					// wrong_col set 0 in case became 1 
			col -= 1;							// decriment the given col by 1 (because matrix counts from 0 to 6)
			flg_ovrflow = input_data(game_matrix, disk, col); 
			// No overflow
			if(flg_ovrflow == 0){
				matrix_print(game_matrix);		// if there is no overflow it prints the matrix
			}
		}
	} while(flg_ovrflow == 1 ||  wrong_col == 1);
}

void matrix_print(char m[7][7]){
	
	int row=0,column=0;
    for (row=0; row<7; row++){
        for(column=0; column<7; column++){
			printf("%c     ", m[row][column]);	
		}
        printf("\n\n");
     }
}

int input_data(char m[7][7],char d,int c){
	// Return 0 : when disk inserted     
	// Return 1 : when overflow of column
	int r , free_row=6 ; 	// free_row pointer starts at bottom of the column		
	for (r=6; r>-1; r--){	// starts from bottom
		if (m[r][c]=='_'){	// cheks if the bottom of the given column is empty '_'
			m[r][c]=d;		// inserts at the bottom of the column player's disk
			return 0;
		}
		// Column not empty
		if (m[r][c]=='+' || m[r][c]=='*'){	
			free_row-=1;					// finds free_row of the column
		}									// checks from bottom to up
	}
	if (free_row != 6 && free_row > -1){
		m[free_row][c]=d;					// inserts at free_row of the column player's disk
		return 0;
	}	
	// Column overflow
	if(free_row == -1){						// free_row == -1 ,overflow of column
		printf("***COLUMN FULL!!***\n\n");	// overflow of column
		return 1;							// returns 1 			
	}
}

int win_check(char m[7][7],char disk){
	// Return 1 :  for win 
	// Return 0 :  for no win
	int row , column ;
	  
	// horizontial check
	for (row=0; row<7; row++){
		for(column=0; column<4; column++){
			if(m[row][column]!='\0' && m[row][column]!='_' && m[row][column]==m[row][column+1] && m[row][column]==m[row][column+2] && m[row][column]==m[row][column+3]){
				return 1;
			}
		}
	}	
	// vertical check
	for (column=0; column<7; column++){
		for(row=0; row<4; row++){
			if(m[row][column]!='\0' && m[row][column]==m[row+1][column] && m[row][column]==m[row+2][column] && m[row][column]==m[row+3][column]){
				return 1;
			}
		}
	}
	// diagonical check #1
	for (column=0; column<5; column++){
		for(row=0; row<4; row++){
			if(m[row][column]!='\0' && m[row][column]==m[row+1][column+1] && m[row][column]==m[row+2][column+2] && m[row][column]==m[row+3][column+3]){
				return 1;
			}
		}
	}
	// diagonical check #2
	for (column=6; column>2; column--){
		for(row=0; row<4; row++){
			if(m[row][column]!='\0' && m[row][column]==m[row+1][column-1] && m[row][column]==m[row+2][column-2] && m[row][column]==m[row+3][column-3]){
				return 1;
			}
		}
	}
	return 0;
}

int check_win_move(char m[7][7],char disk){
	// Return winning column
	// Return -1 : no winning column
	int r , c , i ,counter,f,win_col ;	
	
	// Horizontial check for winning move
	for (r=6; r>=0; r--){
		for (c=0; c<=3;c++){
			counter = 0 , f = 0 ;
			for (i=c; i<=c+3; i++){
				if(m[r][i] == disk){
					counter+=1;
				}
				else if(m[r][i] == '_' || m[r][i] == '\0'){
					f = 1 ;
					win_col = i ;
				}
			}
			if (counter == 3 && f == 1){
				//printf("\n\nHorizontial Move for win!!\n\n");
				return win_col ;
			}
		}
	}
	// Vertical check for winning move
	for (c=0; c<7; c++){					
		for(r=6; r>3; r--){		// from 7th row to 4th 		// if 3 successively Computer's disks 
			if(m[r][c]==disk && m[r-1][c]==disk && m[r-2][c]==disk && m[r-3][c]=='\0'){  // and next is empty 
				//printf("\n\nVertical Move for win!!\n\n");
				return c ;
			}
		}
	}
	return -1 ;	
}

void computer_move(char m[7][7],char disk_enemy,char disk_computer){
	
	int flg_ovrflow = 0 , col ;
	srand(time(NULL));
	
	col = check_win_move(m,disk_computer);			// column that Computer wins
	if (col == -1) {										// if there is no column that Computer wins
		col = check_win_move(m,disk_enemy);			// column that Human wins
		if (col == -1){										// if there is no column that Human wins
			col = rand() % 7 ;						// chooses randomly column
			flg_ovrflow = input_data(m,disk_computer,col);			
			while (flg_ovrflow == 1){							// while rand() chooses a full column 
				col = rand() % 7 ;								// rand() chooses new column
				flg_ovrflow = input_data(m,disk_computer,col);
			}
		}
		else{
			flg_ovrflow = input_data(m,disk_computer,col);
		}
	}
	else{
		flg_ovrflow = input_data(m,disk_computer,col); 		// if there is column to block puts disk on this column
	}
}
