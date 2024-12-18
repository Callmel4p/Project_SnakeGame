
#include <string.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <stdbool.h>
#include <ctype.h>

// Design by l4p

int menuOption = 0;

// Customize map. Default is biggest one
int HEIGHT = 10;
int WIDTH = 30;
char mapSizeOption[4444] = "1";
int iMapSizeOption = 1;

int level = 1; // Decide level(speed) of game. Default is the slowest.

// Snake intialization
int headX, headY;
int tailX[4444], tailY[4444];
int snakeLen = 1;

// Fruit initialization
int fruitX, fruitY; // these will be random number between 1 and HEIGHT - 2, WIDTH - 2

// Score
long long score = 0;
long long highestScore = 0;

// Lose (Win) condition
int gamelose;
int gamewin;
char target[4444] = "800"; // Default target for big map
long long iTarget = 800;

char fToPlayAgain = 'f'; // Play again option

char colorOption[4444]; // Change color option

// Direction of snake
int dirX;
int dirY;

void clearInputFromBuffer(){ // avoid unintended input by get all character which is waiting for processed till catch newline sign 
    while (getchar() != '\n');
}

bool isValidIntegerInput(char input[]){ // get only 0 -> 9 as valid input
    if (strlen(input) != 1) return false;
    for (int i = 0; i < strlen(input); i++){
        if (isdigit(input[i]) == 0) return false;
    }
    return true;
}

void mvaddch(int x, int y, char c[]){ // move cursor to location (x,y) and print string "c"
    COORD coord;
    coord.X = x;
    coord.Y = y;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsole,coord);
    printf("%s", c);
}

int menu(){
    char userPick[4444];
    int iUserPick = 0;
    system("cls");
    printf("========= SNAKE GAME ==========\n");
    printf("1. How to play ?\n");
    printf("2. Choose game mode \n");
    printf("3. Change map size\n");
    printf("4. Set your goal\n");
    printf("5. Change screen color\n");
    printf("6. Play\n");
    printf("7. Exit game\n");

    while(true){
        printf("Pick a valid one: ");
        scanf("%s", &userPick);
        int isValidUserPick = isValidIntegerInput(userPick);
        if (isValidUserPick == true){
            iUserPick = userPick[0] - '0';
            if (iUserPick >= 1 && iUserPick <= 7) break;
        }
    }
    return iUserPick;
}

void printTutorial(){
    system("cls");
    printf("========= HOW TO PLAY ?? ========\n");
    printf("W: up\n");
    printf("A: left\n");
    printf("S: down\n");
    printf("D: right\n");
    printf("+ You will win if the snake size equal the map\n");
    printf("+ You will lose if the snake's head meet wall or it's tail before you win\n");
    printf("Remind: Turn off Vietnamese keyboard before start for smoothest game\n");
    printf("Press any key to back to menu\n");
    while(kbhit() == 0){
        continue;
    }
    menuOption = 0;
    getch();
}

void changeGameSpeed(){
    clearInputFromBuffer();
    system("cls");
    printf("======= HOW HARD YOU WANT ?? ========\n");
    printf("1. Low speed snake (easy)\n");
    printf("2. Medium speed snake (medium)\n");
    printf("3. High speed snake (hard)\n");
    printf("4. Menu\n");
    char option[4444];
    int iOption;
    while (true){
        printf("Choose a valid option: ");
        scanf(" %s", &option);
        int isValidOption = isValidIntegerInput(option);
        if (isValidOption != 0){
            iOption = option[0] - '0';
            if (iOption >= 1 && iOption <= 4) break; 
        }
        
    }

    if (iOption == 4) {
        menuOption = 0;
    }
    else{
        level = iOption;
        menuOption = 0;
    } 
}

void changeMapSize(){
    system("cls");
    printf("Choose your map size:\n");
    printf("1. Big\n2. Medium\n3. Small\n");
    while(true){
        printf("Your choose: ");
        scanf("%s", &mapSizeOption);
        if (isValidIntegerInput(mapSizeOption) != 0){
            iMapSizeOption = mapSizeOption[0] - '0';
            if (iMapSizeOption >= 1 && iMapSizeOption <= 3) break;
        }
    }
    if (iMapSizeOption == 1){
        HEIGHT = 20;
        WIDTH = 40;
    }
    else if (iMapSizeOption == 2){
        HEIGHT = 15;
        WIDTH = 35;
    }
    else if (iMapSizeOption == 3){
        HEIGHT = 10;
        WIDTH = 20;
    }
    menuOption = 0;
}

void setGoal(){
    system("cls");
    printf("Max goal of each size:\n");
    printf("Big(1-800)\t Medium(1-525)\t Small(1-200)\n");
    if (iMapSizeOption == 1) printf("Current: Big\n");
    else if (iMapSizeOption == 2) printf("Current: Medium\n");
    else if (iMapSizeOption == 3) printf("Current: Small\n");
    bool invalid = true;
    while(invalid != false){
        invalid = false;
        printf("Your target: ");
        scanf("%s", &target);
        for (int i = 0; i < strlen(target); i++){
            if (isdigit(target[i]) == 0){
                invalid = true;
                break;
            }
        }
    }
    iTarget = atoi(target);
    int isCanWin = 1;
    if ((iTarget < 1 || iTarget > 800) && iMapSizeOption == 1) isCanWin = 0; 
    else if ((iTarget < 1 || iTarget > 525) && iMapSizeOption == 2) isCanWin = 0;
    else if ((iTarget < 1 || iTarget > 200) && iMapSizeOption == 3) isCanWin = 0;

    if (isCanWin == 0){
        printf("Warning: You CAN'T win !!\n");
        Sleep(2000);
    }
    menuOption = 0;
}

void changeColor(){
    int iColorOption;
    system("cls");
    printf("1. Default\n");
    printf("2. Red\n");
    printf("3. Green\n");
    printf("4. Blue\n");
    while(true){
        printf("Pick a valid one: ");
        scanf("%s", &colorOption);
        if (isValidIntegerInput(colorOption) != 0){
            iColorOption = colorOption[0] - '0';
            if (iColorOption >= 1 && iColorOption <= 7) break;
        }
    }
    if (iColorOption == 1){
        system("color 7");
    }   
    else if (iColorOption == 2){
        system("color 4");
    }
    else if (iColorOption == 3){
        system("color 2");
    }
    else if (iColorOption == 4){
        system("color 9");
    }
    menuOption = 0;
    
}

void setupBeforeStart(){
    score = 0;
    snakeLen = 1;
    gamelose = 0;
    gamewin = 0;
    headX = WIDTH / 2;
    headY = HEIGHT / 2;
    fruitX = rand() % (WIDTH - 2) + 1;
    fruitY = rand() % (HEIGHT - 2) + 1;
    for (int i = 0; i < 4444; i++){
        tailX[i] = 99999;
        tailY[i] = 99999;
    }
    tailX[0] = headX;
    tailY[0] = headY;

}

void drawBeforeStart(){ // draw the boundary
    system("cls");
    
    for (int x = 0; x < WIDTH; x++){
        printf("#");
    }
    printf("\n");
    
    for (int y = 0; y < HEIGHT - 2; y++){
        for (int x = 0; x < WIDTH; x ++){
            if (x == 0 || x == WIDTH - 1){
                printf("#");
            }
            else printf(" ");
        }
        printf("\n");
    }
    
    for (int x = 0; x < WIDTH; x ++){
        printf("#");
    }
}

void clearSnake(){
    mvaddch(tailX[snakeLen], tailY[snakeLen]," ");
}

void printScore(){
    COORD coord;
    coord.X = 0;
    coord.Y = HEIGHT + 5;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsole,coord);
    printf("SCORE: %lld\n", score);
    printf("WAY TO WIN: %lld/%lld\n", score, iTarget);
    printf("HIGHEST SCORE: %lld\n", highestScore);
}

void drawInGame(){
    for (int i = 0; i < snakeLen; i++){
        if (i == 0) {
            mvaddch(tailX[0], tailY[0], "X");
        }
        else {
            mvaddch(tailX[i], tailY[i], "o");
        }
    }
    mvaddch(fruitX, fruitY, "@");
    printf("\e[?25l"); // hide the cursor
    printScore();
}

void console(){
    // Take input to change direction
    if (kbhit() != 0){
        char ch = tolower(getch());
        if (ch == 'a' && dirX != 1){
            dirX = -1;
            dirY = 0;
        }
        else if (ch == 's' && dirY != -1){
            dirX = 0;
            dirY = 1;
        }
        else if (ch == 'd' && dirX != -1){
            dirX = 1;
            dirY = 0;
        }
        else if (ch == 'w' && dirY != 1){
            dirX = 0;
            dirY = -1;
        }
    }
    
    headX += dirX;
    headY += dirY;

    // If snake eat fruit
    if (headX == fruitX && headY == fruitY){
        snakeLen += 1;
        score += 1;
        fruitX = rand() % (WIDTH - 2) + 1;
        fruitY = rand() % (HEIGHT - 2) + 1;

        int isFruitInTail = 1;
        while (isFruitInTail != 0){ // avoid fruit genarate inside the snake
            isFruitInTail = 0;
            for (int len = 1; len <= snakeLen; len++){
                if (tailX[len] == fruitX && tailY[len] == fruitY){
                    isFruitInTail += 1;                    
                    fruitX = rand() % (WIDTH - 2) + 1;
                    fruitY = rand() % (HEIGHT - 2) + 1;
                }
            }
        }
    }

    if (score == iTarget){  // Winning condtion
        gamewin = 1;
    }

    // Make snake tail
    for (int i = snakeLen; i > 0; i--){
        tailX[i] = tailX[i-1];
        tailY[i] = tailY[i-1];
    }

    tailX[0] = headX; // Update 
    tailY[0] = headY; //      new head

    // Losing condtion    
    if (headX == WIDTH - 1 || headX == 0 || headY == HEIGHT - 1 || headY == 0){ // meet the boundary
        gamelose = 1;
    }
    for (int len = 1; len < snakeLen; len++){ // hit itself
        if (tailX[len] == headX && tailY[len] == headY){
            gamelose = 1;
            break;
        }
    }

}

int endGameCondtion(){
    if (gamelose == 0 && gamewin == 0) return 0;
    else return 1;
}

void printIfWin(){
    system("cls");
    printf("#   #  ######  #    #      #        ##        #   ######  ##    #     ## \n");
    printf(" # #   #    #  #    #       #      #  #      #    #    #  # #   #     ## \n");
    printf("  #    #    #  #    #        #    #    #    #     #    #  #  #  #     ## \n");
    printf("  #    #    #  #    #         #  #      #  #      #    #  #   # #        \n");
    printf("  #    ######  ######          ##        ##       ######  #    ##     00 \n");
}

void printIfLose(){
    system("cls");
    printf("#   #  ######  #    #      #      #######  #####  #####     ##  \n");
    printf(" # #   #    #  #    #      #      #     #  #        #       ##  \n");
    printf("  #    #    #  #    #      #      #     #  #####    #       ##  \n");
    printf("  #    #    #  #    #      #      #     #      #    #           \n");
    printf("  #    ######  ######      ###### #######  #####    #       00  \n");
}

void playAgain(){
    Sleep(2000);
    printf("Press F to play again...\n");
    printf("Any other combo will exit the game\n");
    fToPlayAgain = getch();
}

void playing(){
    fToPlayAgain = 'f';
    int speed;
    if (level == 1){
        speed = 150;
    }
    else if (level == 2){
        speed = 75;
    }
    else {
        speed = 50;
    }
    while (fToPlayAgain == 'f'){
        setupBeforeStart();
        system("cls");
        printf("Press any key to start!\n");
        while (kbhit() == 0){ // infinitive loop until get user input
            continue;
        }      
        drawBeforeStart();
        while(endGameCondtion() == 0){
            clearSnake();
            drawInGame();
            console();
            Sleep(speed);
        }
        // update highest score after each game
        if (score > highestScore){
            highestScore = score;
        }
        // Decide win or lose and play again option
        if (gamelose == 1 && gamewin == 0) {
            printIfLose();
            playAgain();
        }
        else if (gamelose == 0 && gamewin == 1){
            printIfWin();
            playAgain();
        }
    }
}


int main(){
    while(true){
        if (menuOption == 0) menuOption = menu();

        else if (menuOption == 1) {
            printTutorial();
        }
        else if (menuOption == 2){
            changeGameSpeed();
        }
        else if (menuOption == 3){
            changeMapSize();
        }
        else if (menuOption == 4){
            setGoal();
        }
        else if (menuOption == 5){
            changeColor();
        }
        else if (menuOption == 6){
            playing();
            menuOption = 0;
        }
        else if (menuOption == 7){
            break;
        }
    }
    system("color 7"); // change screen into default
    return 0;
    
}