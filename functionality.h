/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * You need to define the required function in the part instructed here below.
 * Avoid making any unnecessary changes, particularly the ones you don't understand.
 * The different pieces should be defined using an array - uncomment the following code once you are done creating the array.
 * TIP: Understand thoroughly before getting started with coding.
 * */

//---Piece Starts to Fall When Game Starts---//
void bombDetonation(int colorNum, int shrink, bool &bazelyes);

void createShapes(int nextShape[][2], int nextSecondShape[][2], int nextThirdShape[][2], int& colorNext, int& colorSecond, int& colorThird, int& nNext, int& nSecond, int& nThird){
			
			
			colorNext = 1 + rand() % 7; colorSecond = 1 + rand() % 7; colorThird = 1 + rand() % 7; nNext = rand()%7; nSecond = rand()%7; nThird = rand()%7;
            for (int i=0;i<4;i++){
                nextShape[i][0] = BLOCKS[nNext][i] % 2;
                nextShape[i][1] = BLOCKS[nNext][i] / 2;
            }
            for (int i=0;i<4;i++){
                nextSecondShape[i][0] = BLOCKS[nSecond][i] % 2;
                nextSecondShape[i][1] = BLOCKS[nSecond][i] / 2;
            }
            for (int i=0;i<4;i++){
                nextThirdShape[i][0] = BLOCKS[nThird][i] % 2;
                nextThirdShape[i][1] = BLOCKS[nThird][i] / 2;
            }
}


void fallingPiece(float& timer, float& delay, int& colorNum, int&currentShape, bool &isBomb, int nextShape[][2], int nextSecondShape[][2], int nextThirdShape[][2], int& colorNext, int& colorSecond, int& colorThird, int& nNext, int& nSecond, int& nThird, int shrink, bool &bazelyes){
    if (timer>delay){
        for (int i=0;i<4;i++){
            point_2[i][0]=point_1[i][0];
            point_2[i][1]=point_1[i][1];
            point_1[i][1]+=1;
        }
        if (!anamoly()){
        	if(isBomb){
        	bombDetonation(colorNum, shrink, bazelyes);
        	colorNum = false;
        	}
        	isBomb = 0;
        	if (rand() % 10 == 9 || isBomb == true){
				isBomb = 1;
			}
			else{isBomb = 0;}
        	if (isBomb){
        		for(int i = 0; i < 4; i++){
        		gameGrid[point_2[i][1]][point_2[i][0]] = colorNum;
        		}
        		int x = rand() % 9;
        		colorNum = 1 + rand()%7;
        		for (int i=0;i<4;i++){
                    point_1[i][0] = x;
                    point_1[i][1] = shrink;
                }
        		return;
        	}
        	else{
        	for(int i = 0; i < 4; i++){
        		gameGrid[point_2[i][1]][point_2[i][0]] = colorNum;
        		}
        	
        	colorNum = colorNext;colorNext = colorSecond; colorSecond = colorThird; currentShape = nNext; nNext = nSecond; nSecond = nThird;
        	for (int i=0;i<4;i++){
                point_1[i][0] = nextShape[i][0];
                point_1[i][1] = nextShape[i][1] + shrink;
            }
            for (int i=0;i<4;i++){
                nextShape[i][0] = nextSecondShape[i][0];
                nextShape[i][1] = nextSecondShape[i][1];
            }
            for (int i=0;i<4;i++){
                nextSecondShape[i][0] = nextThirdShape[i][0];
                nextSecondShape[i][1] = nextThirdShape[i][1];
            }
        	colorThird = 1 + rand()%7;
            int n=rand()%7;
            nThird = n;
                for (int i=0;i<4;i++){
                    nextThirdShape[i][0] = BLOCKS[n][i] % 2;
                    nextThirdShape[i][1] = BLOCKS[n][i] / 2;
                }
            }
        }
        timer=0;
    }
}

/////////////////////////////////////////////
///*** START CODING YOUR FUNTIONS HERE ***///

void bombDetonation(int colorNum, int shrink, bool &bazelyes){

	if (gameGrid[point_1[0][1]][point_1[0][0]] == colorNum){
		for (int i = shrink; i < M ; i++){
			for (int j = 0; j < N; j++){
				gameGrid[i][j] = false;
			}
		}
		bazelyes = true;
	}
	else if (gameGrid[point_1[0][1]][point_1[0][0]] != false){
		//bazelyes = true;
		if (point_1[0][0] < N / 2){
			for (int i = point_1[0][1]; i < point_1[0][1] + 2; i++){
				if (i >= 20) continue;
			for (int j = point_1[0][0]; j < point_1[0][0] + 2; j++){
				
				gameGrid[i][j] = false;
			}
			}
		}
		else{
			for (int i = point_1[0][1]; i < point_1[0][1] + 2; i++){
				if (i >= 20) continue;
			for (int j = point_1[0][0]; j > point_1[0][0] - 2; j--){
				gameGrid[i][j] = false;
			}
			}
		}
	}
	else{
		return;
	}
}

bool bordercheck(){
    for (int i=0;i<4;i++)
        if (point_1[i][0]<0 || point_1[i][0]>=N || point_1[i][1]>=M )
            return 0;
        else if (gameGrid[point_1[i][1]][point_1[i][0]])
            return 0;
    return 1;
}

bool shadowcheck(int temp[][2]){
    for (int i=0;i<4;i++)
        if (temp[i][0]<0 || temp[i][0]>=N || temp[i][1]>=M )
            return 0;
        else if (gameGrid[temp[i][1]][temp[i][0]])
            return 0;
    return 1;
}

void moveright(){
	for(int i = 0; i < 4; i++){
		point_2[i][0] = point_1[i][0];
        point_2[i][1] = point_1[i][1];
	}
	for(int i = 0; i < 4; i++){
		point_1[i][0] = point_1[i][0] + 1;
	}
	if(!bordercheck()){
		for(int i = 0; i < 4; i++){
			point_1[i][0] = point_2[i][0];
		    point_1[i][1] = point_2[i][1];
		}
	}
}

void moveleft(){
	for(int i = 0; i < 4; i++){
		point_2[i][0] = point_1[i][0];
        point_2[i][1] = point_1[i][1];
	}
	for(int i = 0; i < 4; i++){
		point_1[i][0] = point_1[i][0] - 1;
	}
	if(!bordercheck()){
		for(int i = 0; i < 4; i++){
			point_1[i][0] = point_2[i][0];
		    point_1[i][1] = point_2[i][1];
		}
	}	
}

void rotation(int &currentShape){
	if (currentShape == 0)
		return;
		
	int px,py;
	px = point_1[1][0]; py = point_1[1][1];
	
	for (int i = 0; i < 4; i++){
		int x = point_1[i][1] - py, y = point_1[i][0] - px;
		point_1[i][0] = px - x;
		point_1[i][1] = py + y;
	}
	if (!anamoly()){
		for (int i = 0; i < 4; i++){
			point_1[i][0] = point_2[i][0];
			point_1[i][1] = point_2[i][1] + 1;
		}
	}
	
}

void snap(){
	while (int bruhmen = -1 < 0){	
		for (int i=0;i<4;i++){
		        point_2[i][0]=point_1[i][0];
		        point_2[i][1]=point_1[i][1];
		        point_1[i][1]+=1;
		    }
			
			if (!anamoly()){
				for (int i=0;i<4;i++){
				    point_1[i][1] -= 1;
		        }
			    break;}
	}
}

void shadow(int temp[][2]){
	for (int i=0;i<4;i++){
		        temp[i][0]=point_1[i][0];
		        temp[i][1]=point_1[i][1];
		    }
	while (int bruhmen = -1 < 0){	
		for (int i=0;i<4;i++){
		        temp[i][1]+=1;
		    }
		if (!shadowcheck(temp)){
			for (int i=0;i<4;i++){
			    temp[i][1] -= 1;
		    }
			    break;}
	}
}


int lineend(int shrink){ // int to return score for one instant of block.
	
	int linecheck = 0;
	int linescomplete = 0;
	
	for (int i = M - 1; i >= shrink; i--) { // checking grid for empty slots, if all slots in a line are filled, delete and lower each line above it by one
	
		for (int j = 0; j < N; j++){
			if (gameGrid[i][j] != false){
				linecheck += 1;
			}
			else {linecheck = 0;
			break;}
		}
		if (linecheck >= 10){
		
			linescomplete = linescomplete + 1;
			for (int j = 0; j < N; j++){
				gameGrid[i][j] = false;
			}
			for (int h = i; h >= shrink; h--){
				for (int j = 0; j < N; j++){
					gameGrid[h][j]=gameGrid[h - 1][j];
				}
			}
		i++;
		linecheck = 0;
		}
		
	}
	
	
	return linescomplete;
	
}

void calcTotalScore(int& score, int current){ // adding currentscore to total for total display
	score += current;
}

int calcScore(int linescomplete, int level){
	switch(linescomplete){ // Calculating score based on lines completed in one instant. To display
		case 1:
			return 10 * level;
			break;
		case 2:
			return 30 * level;
			break;
		case 3:
			return 60 * level;
			break;
		case 4:
			return 100 * level;
			break;
	}
	return 0;
}

bool gameOver(int shrink){

	for(int i = 0; i < N; i++){
		if (gameGrid[shrink][N] != 0){
			return 1;
		}
	}
	return 0;
	
}


///*** YOUR FUNCTIONS END HERE ***///
/////////////////////////////////////
