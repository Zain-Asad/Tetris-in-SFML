/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * You don't need to change anything in the driver code/main function except the part(s) where instructed.
 * You are expected to define your functionalities in the "functionality.h" header and call them here in the instructed part(s).
 * The game is started with a small box, you need to create other possible in "pieces.h" file in form of array.
    E.g., Syntax for 2 pieces, each having four coordinates -> int Pieces[2][4];
 * Load the images into the textures objects from img directory.
 * Don't make any changes to the "utils.h" header file except for changing the coordinate of screen or global variables of the game.
 * SUGGESTION: If you want to make changes in "utils.h", do it once you complete rest of the functionalities.
 * TIP: You can study SFML for drawing scenes, sprites and window.
 * 
 To Do: Suggestion, Grid shrink with time, levels, scoreDisplay, menu, pause, gameover.
 */
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include "utils.h"
#include "pieces.h"
#include "functionality.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace sf;
using namespace std;
int main(){
 
    Font lehn;
    Music introsound, bazelboom, bgm;
    introsound.openFromFile("img/intro_sound.wav");	// initializing sounds, objects and texts
    introsound.setVolume(100);
    bazelboom.openFromFile("img/bomb_explode.wav");
    bazelboom.setVolume(100);
    bgm.openFromFile("img/purple_rain.ogg");
    bgm.setVolume(75);
    
    lehn.loadFromFile("img/lehn234.ttf");
    bool start = false, highs = false, help = false;
    int choice;
    Texture obj1, obj2, obj3, projection, bombobj, next1, next2, next3, obj4, animation;
    animation.loadFromFile("img/spritesheetblockbreak.png");
    next1.loadFromFile("img/tiles.png");
    next2.loadFromFile("img/tiles.png");
    next3.loadFromFile("img/tiles.png");
    obj1.loadFromFile("img/tiles.png");
    obj2.loadFromFile("img/background.png");
    obj3.loadFromFile("img/frame.png");
    projection.loadFromFile("img/tiles.png");
    bombobj.loadFromFile("img/bombs.png");
    obj4.loadFromFile("img/cross.png");
    Sprite sprite(obj1), background(obj2), frame(obj3), shadow1(projection), bomb(bombobj), n1(next1), n2(next2), n3(next3), cross(obj4);
    srand(time(0));
    
    string hscorenames[10] = {}; int hscores[10] = {}; //accesses scores.txt and then stores the values
    fstream highScores;
    highScores.open("scores.txt", ios::in);
    for (int i = 0; i < 10; i++){
    	
    	highScores >> hscorenames[i];
    	highScores >> hscores[i];
    	
    }
    highScores.close();
    Text scoreTitle, showscores;
    
    
	
	bool startanim = true;    

    RenderWindow menu(VideoMode(320, 480),"TetrisMenu");    
    while(menu.isOpen()){
		
		if (choice != 2 && choice != 3){
		menu.clear();
    	menu.draw(background);
    	
    	// start menu title
		Text startmenutitle;
		startmenutitle.setFont(lehn);
		startmenutitle.setString("[TETRIS]");
		startmenutitle.setCharacterSize(48);
		startmenutitle.setFillColor(Color(255,255,255,255));
		startmenutitle.setStyle(Text :: Bold);
		startmenutitle.setPosition(70,50);
		menu.draw(startmenutitle);
		
    	// start options		
		Text startoptions;
		startoptions.setFont(lehn);
		startoptions.setString("\n\n\n1.Start Game\n2.High Scores\n3.Help\n4.Exit");
		startoptions.setCharacterSize(30);
		startoptions.setFillColor(Color(255,255,255,255));
		startoptions.setStyle(Text :: Bold);
		startoptions.setPosition(70,50);
		menu.draw(startoptions);
		}
		
		Event m;
        while (menu.pollEvent(m)){                    //Event is occurring - until the game is in running state
    	    if (m.type == Event::Closed)                //If cross/close is clicked/pressed
                menu.close();                         //Opened window disposes
            if (m.type == Event::KeyPressed) {          //If any other key (not cross) is pressed
                if (m.key.code == Keyboard::Num1)          //Check if the other key pressed is UP key
                    {start = true;menu.close();}                  //Rotation gets on
                else if (m.key.code == Keyboard::Num2)     //Check if the other key pressed is LEFT key
                    {choice = 2;highs = true;}        		        //Change in X-Axis - Negative
                else if (m.key.code == Keyboard::Num3)     //Check if the other key pressed is RIGHT key
                    {choice = 3;}					//Change in X-Axis - Positive
                else if (m.key.code == Keyboard::Num4)                       
            		{start = false; menu.close();}
            	}
		}
		menu.display();
		
		switch(choice){
		case 2:		//Takes values from array and displays

			menu.clear();
			menu.draw(background);
			scoreTitle.setFont(lehn);
			scoreTitle.setString("HIGH SCORES");
			scoreTitle.setCharacterSize(42);
			scoreTitle.setFillColor(Color(255,255,255,255));
			scoreTitle.setStyle(Text :: Bold);
			scoreTitle.setPosition(10,10);
			menu.draw(scoreTitle);
			
			showscores.setFont(lehn);
			showscores.setString("1. " + hscorenames[0] + ":" + to_string(hscores[0]) + "\n2. " + hscorenames[1] + ":" + to_string(hscores[1]) + "\n3. " + hscorenames[2] + ":" + to_string(hscores[2]) + "\n4. " + hscorenames[3] + ":" + to_string(hscores[3]) + "\n5. " + hscorenames[4] + ":" + to_string(hscores[4]) + "\n6. " + hscorenames[5] + ":" + to_string(hscores[5]) + "\n7. " + hscorenames[6] + ":" + to_string(hscores[6]) + "\n8. " + hscorenames[7] + ":" + to_string(hscores[7]) + "\n9. " + hscorenames[8] + ":" + to_string(hscores[8]) + "\n10. " + hscorenames[9] + ":" + to_string(hscores[9]));
			showscores.setCharacterSize(24);
			showscores.setFillColor(Color(255,255,255,255));
			showscores.setStyle(Text :: Bold);
			showscores.setPosition(20,80);
			menu.draw(showscores);
									
			while (menu.pollEvent(m)){              
				if (m.type == Event::Closed)     
					menu.close();                       
				if (m.type == Event::KeyPressed) {         
					if (m.key.code == Keyboard::Num2)
					    {choice = 0;}
					}
			}
			
			menu.display();
			break;
		case 3:
			menu.clear();
    		menu.draw(background);
			// help display
			Text helptext;
			helptext.setFont(lehn);
			helptext.setString("The Goal of the game is to score\nas many points as possible by\ncompleting rows by dropping blocks.\nMultiple line completions at once\ngive bonus score. The game will\ngrow progressively harder as time\npasses. Bombs may drop randomly,\ndoing nothing, causing a small\nexplosion, or erasing everything.\nYou lose if the grid fills up.\nControls:\nPress <- and -> for movement.\nPress up to quickly drop block\npress down to rotate block\nPress Space to hard drop.\nPress 'H' key to pause. 3 to back");
			helptext.setCharacterSize(19);
			helptext.setFillColor(Color(255,255,255,255));
			helptext.setStyle(Text :: Bold);
			helptext.setPosition(5,0);
			menu.draw(helptext);
					Event m;
		    while (menu.pollEvent(m)){              
			    if (m.type == Event::Closed)     
		            menu.close();                       
		        if (m.type == Event::KeyPressed) {         
		            if (m.key.code == Keyboard::Num3)     
		                {choice = 0;}
		        	}
			}
			menu.display();
			
			break;
		}
		
    }
    
if(start == true){
    RenderWindow window(VideoMode(320, 480), title); //checking if menu ended at start
    	int delta_x=0, colorNum=1 + rand() % 7;
		float timer=0, delay=0.3;
		bool rotate=0;
		Clock clock;
		int temp[4][2];
		int nextShape[4][2]; int nextSecondShape[4][2]; int nextThirdShape[4][2];
		int colorNext, colorSecond, colorThird;
		int nNext, nSecond, nThird;	
		int currentShape;
		int totalScore = 0, currentscore = 0, currentLines = 0;
		bool isBomb = false;
		bool ifpaused = false;
		bool levelStart = true;
		bool over = false;
		float bombspeed = 0.03;
		float currentTime = 0;
		int minutes = 0;
		int level = 1;
		int shrink = 0;
		float levelspeed = 0;
		bool bazelyes = false;	//variables to store spritesheets and soundqueues
		IntRect currentframe(16,0,320,480);
		Sprite state(animation, currentframe);
		Clock frametime;
		Clock bazelno;
		bgm.setLoop(true);
		bgm.play();
    while (window.isOpen()){
    		
			if (start == true){		// restarting game values
				delta_x=0, colorNum=1 + rand() % 7;
				timer=0, delay=0.3;
				rotate=0;
				introsound.stop();
				totalScore = 0, currentscore = 0, currentLines = 0;
				isBomb = false;
				ifpaused = false;
				levelStart = true;
				over = false;
				bombspeed = 0.03;
				currentTime = 0;
				minutes = 0;
				level = 1;
				shrink = 0;
				levelspeed = 0;
				startanim = true;
				currentframe.left = 16;
				currentShape = nNext;
				colorNum = colorNext;
				bgm.setPlayingOffset(seconds(0.0f));
				for (int i=0;i<4;i++){
                	point_1[i][0] = nextShape[i][0];
                	point_1[i][1] = nextShape[i][1] + shrink;
		        }
		        for (int i = 0; i < M; i++){
		        	for (int j = 0; j < N; j++){
		        		gameGrid[i][j] = false;
		        	}
		        }
			}
    	start = false;
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer+=time;
        
        
        if (!ifpaused && !over)
        currentTime += time;
        
        if (minutes % 5 == 0){
			level = minutes / 5 + 1;
			levelspeed = 0.45 - (level * 0.05);
		}
		delay = levelspeed;
		
		if (isBomb)
		delay = bombspeed;
		
		if (level <= 6)
			shrink = level - 1;
		
		delta_x=0;
		rotate = false;
		
		
		
        //---Event Listening Part---//
        Event e;
        while (window.pollEvent(e)){                    //Event is occurring - until the game is in running state
            if (e.type == Event::Closed)                   //If cross/close is clicked/pressed
                window.close();                            //Opened window disposes
            if (e.type == Event::KeyPressed) {             //If any other key (not cross) is pressed
                if (e.key.code == Keyboard::Up)            //Check if the other key pressed is UP key
                    rotate = true;                         //Rotation gets on
                else if (e.key.code == Keyboard::Left)     //Check if the other key pressed is LEFT key
                    delta_x = -1;                          //Change in X-Axis - Negative
                else if (e.key.code == Keyboard::Right)    //Check if the other key pressed is RIGHT key
                    delta_x = 1;						   //Change in X-Axis - Positive
                else if (e.key.code == Keyboard::Space)                       
            		snap();
            	else if (e.key.code == Keyboard::H){ifpaused = !ifpaused;}
            	}
        }
        if (Keyboard::isKeyPressed(Keyboard::Down))   //Just another way to detect key presses without event listener
            delay=0.05;                                    //If DOWN key is pressed, delay in falling piece decreases from 0 to 0.05

        ///////////////////////////////////////////////
        ///*** START CALLING YOUR FUNCTIONS HERE ***///
        over = gameOver(shrink); //over checks whether or not game over condition is met
        
        if (levelStart == true){
        	createShapes(nextShape, nextSecondShape, nextThirdShape, colorNext, colorSecond, colorThird, nNext, nSecond, nThird);
        	levelStart = false;
        }
        
        if (over == false && ifpaused == false){
		   	fallingPiece(timer, delay, colorNum, currentShape, isBomb, nextShape, nextSecondShape, nextThirdShape, colorNext, colorSecond, colorThird, nNext, nSecond, nThird, shrink, bazelyes);
		   	
		   	if (bazelyes == true){
		   		bazelboom.setPlayingOffset(seconds(0.0f));	
		   		bazelboom.play();
		   		bazelyes = false;
		   	}
		   	
		   	if (currentLines > 0){
				currentscore = calcScore(currentLines, level);
				calcTotalScore(totalScore, currentscore);
			}
			currentLines = lineend(shrink);	
		   	if (!isBomb){
				shadow(temp);
				if (delta_x == 1){
					moveright();
		  		}
				else if (delta_x == -1){
					moveleft();
				}
				if (rotate){
		   			rotation(currentShape);
				}
				
	    	}
	    }
	    
        ///*** YOUR CALLING STATEMENTS END HERE ***///
        //////////////////////////////////////////////

        window.clear(Color::Black);
        window.draw(background);
        
        if(startanim)
        	introsound.play();
        while(startanim){
            window.clear(Color::Black);
        	window.draw(background);
			if (frametime.getElapsedTime().asSeconds() > 0.20f){
				if (currentframe.left == 1696){
					startanim = false;
				}
				else
				currentframe.left += (320 + 16);
				state.setTextureRect(currentframe);
				frametime.restart();
			}
			window.draw(state);
			window.display();
    	}
    	
        
        if (!isBomb){
        if (shrink > 0)
        	for (int i=0; i<shrink ; i++){
	    		for (int j=0; j<N; j++){
		    	    //if (gameGrid[i][j]==0)
	        	      //  continue;
		    	   	cross.setTextureRect(IntRect(gameGrid[i][j]*18,0,18,18));
		            cross.setPosition(j*18,i*18);
		            cross.move(15,108); //offset
		   	        window.draw(cross);
		    		}
			}
		for (int i=shrink; i<M ; i++){
	    	for (int j=0; j<N; j++){
		        if (gameGrid[i][j]==0)
	                continue;
		        	sprite.setTextureRect(IntRect(gameGrid[i][j]*18,0,18,18));
		            sprite.setPosition(j*18,i*18);
		            sprite.move(15,108); //offset
		            window.draw(sprite);
		    }
		}
		for (int i=0; i<4; i++){
        	sprite.setTextureRect(IntRect(colorNum*18,0,18,18));
	        sprite.setPosition(point_1[i][0]*18,point_1[i][1]*18);
	        sprite.move(15,108);
	        window.draw(sprite);
	      }
	      
	    // Shadow render
	    
	    for (int i=shrink; i<M ; i++){
	        for (int j=0; j<N; j++){
	            if (gameGrid[i][j]==0)
	                continue;
	            shadow1.setTextureRect(IntRect(gameGrid[i][j]*18,0,18,18));
	            shadow1.setPosition(j*18,i*18);
	            shadow1.move(15,108); //offset
	            window.draw(shadow1);
	        }
	    }
		    
	    for (int i=0; i<4; i++){
	        shadow1.setTextureRect(IntRect(colorNum*18,0,18,18));
	        
	        shadow1.setColor(sf::Color(255, 255, 255, 60));
	        
	        shadow1.setPosition(temp[i][0]*18,temp[i][1]*18);
	        shadow1.move(15,108);
	        window.draw(shadow1);
	        
	    } 
        }
        else{
        	
        	if (shrink > 0)
        	for (int i=0; i<shrink ; i++){
	    		for (int j=0; j<N; j++){
		    	    //if (gameGrid[i][j]==0)
	        	      //  continue;
		    	   	cross.setTextureRect(IntRect(gameGrid[i][j]*18,0,18,18));
		            cross.setPosition(j*18,i*18);
		            cross.move(15,108); //offset
		   	        window.draw(cross);
		    		}
		    }
        	for (int i=shrink; i<M ; i++){
	    		for (int j=0; j<N; j++){
		    	    if (gameGrid[i][j]==0)
	        	        continue;
		    	   	sprite.setTextureRect(IntRect(gameGrid[i][j]*18,0,18,18));
		            sprite.setPosition(j*18,i*18);
		            sprite.move(15,108); //offset
		   	        window.draw(sprite);
		    		}
			}
			for (int i=0; i<4; i++){
        		bomb.setTextureRect(IntRect(colorNum*18,0,18,18));
	        	bomb.setPosition(point_1[i][0]*18,point_1[i][1]*18);
	        	bomb.move(15,108);
	        	window.draw(bomb);
	      	}
        }
        //---The Final on Which Everything is Drawn Over is Loaded---//
        window.draw(frame);
        
		// Printing on frames
        
        Text score;
	    score.setFont(lehn);
	    score.setString("SCORE:" + (to_string(totalScore)));
	    score.setCharacterSize(30);
	    score.setFillColor(Color(71, 71, 209, 255));
	    score.setStyle(Text :: Bold);
	    score.setPosition(15,5);
		window.draw(score);
		
        Text lvl;
	    lvl.setFont(lehn);
	    lvl.setString("LEVEL:" + (to_string(level)));
	    lvl.setCharacterSize(30);
	    lvl.setFillColor(Color(71, 71, 209, 255));
	    lvl.setStyle(Text :: Bold);
	    lvl.setPosition(90,44);
		window.draw(lvl);
		
		
		
		Text livescore;
	    livescore.setFont(lehn);
	    livescore.setString("+" + (to_string(currentscore)));
	    livescore.setCharacterSize(30);
	    livescore.setFillColor(Color::Yellow);
	    livescore.setStyle(Text :: Bold);
	    livescore.setPosition(15,44);
		window.draw(livescore);
		
		
		
		Text aglaPiece;
	    aglaPiece.setFont(lehn);
	    aglaPiece.setString("NEXT\nPIECES");
	    aglaPiece.setCharacterSize(24);
	    aglaPiece.setFillColor(Color(128,0,32,255));
	    aglaPiece.setStyle(Text :: Bold);
	    aglaPiece.setPosition(225, 110);
		window.draw(aglaPiece);
		
		
		
		if (currentTime >= 60){
			currentTime = 0;
			minutes += 1;
		}
		Text printtime;
	    printtime.setFont(lehn);
	    printtime.setString("TIME\n" + (to_string(minutes)) + ":" + (to_string(int(currentTime))));
	    printtime.setCharacterSize(24);
	    printtime.setFillColor(Color(64,0,128,255));
	    printtime.setStyle(Text :: Bold);
	    printtime.setPosition(225,10);
		window.draw(printtime);
		
		
		if (level < 4)
		for (int i=0; i<4; i++){
        	n1.setTextureRect(IntRect(colorNext*18,0,18,18));
	        n1.setPosition(nextShape[i][0]*18,nextShape[i][1]*18);
	        n1.move(250,200);
	        window.draw(n1);
	      }
	    if (level < 3)
		for (int i=0; i<4; i++){
        	n2.setTextureRect(IntRect(colorSecond*18,0,18,18));
	        n2.setPosition(nextSecondShape[i][0]*18,nextSecondShape[i][1]*18);
	        n2.move(250,290);
	        window.draw(n2);
	      }
	    if (level < 2)
		for (int i=0; i<4; i++){
        	n3.setTextureRect(IntRect(colorThird*18,0,18,18));
	        n3.setPosition(nextThirdShape[i][0]*18,nextThirdShape[i][1]*18);
	        n3.move(250,380);
	        window.draw(n3);
	      }
		
        if (ifpaused){   
				while(ifpaused){
					
					if (choice != 2 && choice != 3){
					window.clear();
					window.draw(background);
					
					// start window title
					Text startmenutitle;
					startmenutitle.setFont(lehn);
					startmenutitle.setString("[PAUSED]");
					startmenutitle.setCharacterSize(48);
					startmenutitle.setFillColor(Color(255,255,255,255));
					startmenutitle.setStyle(Text :: Bold);
					startmenutitle.setPosition(70,50);
					window.draw(startmenutitle);
					
					// start options		
					Text startoptions;
					startoptions.setFont(lehn);
					startoptions.setString("\n\n\n1.Restart\n2.High Scores\n3.Help\n4.Exit\n5.Resume");
					startoptions.setCharacterSize(30);
					startoptions.setFillColor(Color(255,255,255,255));
					startoptions.setStyle(Text :: Bold);
					startoptions.setPosition(70,50);
					window.draw(startoptions);
					}
					
					Event m;
					while (window.pollEvent(m)){                   
						if (m.type == Event::Closed)                
						    {ifpaused = false;window.close();}                   
						if (m.type == Event::KeyPressed) {          
						    if (m.key.code == Keyboard::Num1)       
						        {start = true;ifpaused = false;}       
						    else if (m.key.code == Keyboard::Num2)   
						        {choice = 2;highs = true;}        		   
						    else if (m.key.code == Keyboard::Num3)  
						        {choice = 3;}
						    else if (m.key.code == Keyboard::Num4)                       
								{start = false; ifpaused = false; window.close();}
							else if (m.key.code == Keyboard::Num5)
								{ifpaused = false;}
							}
					}
					window.display();
					
					switch(choice){
					case 2:
						window.clear();
						window.draw(background);
						scoreTitle.setFont(lehn);
						scoreTitle.setString("HIGH SCORES");
						scoreTitle.setCharacterSize(42);
						scoreTitle.setFillColor(Color(255,255,255,255));
						scoreTitle.setStyle(Text :: Bold);
						scoreTitle.setPosition(10,10);
						window.draw(scoreTitle);
						
						showscores.setFont(lehn);
						showscores.setString("1. " + hscorenames[0] + ":" + to_string(hscores[0]) + "\n2. " + hscorenames[1] + ":" + to_string(hscores[1]) + "\n3. " + hscorenames[2] + ":" + to_string(hscores[2]) + "\n4. " + hscorenames[3] + ":" + to_string(hscores[3]) + "\n5. " + hscorenames[4] + ":" + to_string(hscores[4]) + "\n6. " + hscorenames[5] + ":" + to_string(hscores[5]) + "\n7. " + hscorenames[6] + ":" + to_string(hscores[6]) + "\n8. " + hscorenames[7] + ":" + to_string(hscores[7]) + "\n9. " + hscorenames[8] + ":" + to_string(hscores[8]) + "\n10. " + hscorenames[9] + ":" + to_string(hscores[9]));
						showscores.setCharacterSize(24);
						showscores.setFillColor(Color(255,255,255,255));
						showscores.setStyle(Text :: Bold);
						showscores.setPosition(20,80);
						window.draw(showscores);
												
						while (window.pollEvent(m)){              
							if (m.type == Event::Closed)     
								window.close();                       
							if (m.type == Event::KeyPressed) {         
								if (m.key.code == Keyboard::Num2)
									{choice = 0;}
								}
						}
						window.display();
						break;
					case 3:
						window.clear();
						window.draw(background);
						// help display
						Text helptext;
						helptext.setFont(lehn);
						helptext.setString("The Goal of the game is to score\nas many points as possible by\ncompleting rows by dropping blocks.\nMultiple line completions at once\ngive bonus score. The game will\ngrow progressively harder as time\npasses. Bombs may drop randomly,\ndoing nothing, causing a small\nexplosion, or erasing everything.\nYou lose if the grid fills up.\nControls:\nPress <- and -> for movement.\nPress up to quickly drop block\npress down to rotate block\nPress Space to hard drop.\nPress 'H' key to pause. 3 to back");
						helptext.setCharacterSize(19);
						helptext.setFillColor(Color(255,255,255,255));
						helptext.setStyle(Text :: Bold);
						helptext.setPosition(5,0);
						window.draw(helptext);
								Event m;
						while (window.pollEvent(m)){              
							if (m.type == Event::Closed)     
								window.close();                       
							if (m.type == Event::KeyPressed) {         
								if (m.key.code == Keyboard::Num3)     
								    {choice = 0;}
								}
						}
						window.display();
						
						break;
					}
					
				}
        }
        if (over){
        		string tempname;
        		int tempscore;
        		if (totalScore >= hscores[9]){
        			highScores.open("scores.txt", ios::out);
        			hscorenames[9] = "Player";
        			hscores[9] = totalScore;
        		}
        		for (int i = 0; i < 10; i++){
        			for (int j = i; j < 10; j++){
        				if (hscores[i] < hscores[j]){
        					tempname = hscorenames[i];
        					tempscore = hscores[i];
        					hscorenames[i] = hscorenames[j];
        					hscores[i] = hscores[j];
        					hscorenames[j] = tempname;
        					hscores[j] = tempscore;
        				}
        			}
        		}
        		for (int i = 0; i < 10; i++){
        			highScores << hscorenames[i] + " " + to_string(hscores[i]);
        		}
        		highScores.close();
				while(over){
					if (choice != 2 && choice != 3){
					window.clear();
					window.draw(background);
					
					// start window title
					Text startmenutitle;
					startmenutitle.setFont(lehn);
					startmenutitle.setString("[GAME OVER]");
					startmenutitle.setCharacterSize(48);
					startmenutitle.setFillColor(Color(255,255,255,255));
					startmenutitle.setStyle(Text :: Bold);
					startmenutitle.setPosition(15,50);
					window.draw(startmenutitle);
					
					// start options		
					Text startoptions;
					startoptions.setFont(lehn);
					startoptions.setString("\n\nScore: " + to_string(totalScore) +"\n1.New Game\n2.High Scores\n3.Help\n4.Exit\n");
					startoptions.setCharacterSize(30);
					startoptions.setFillColor(Color(255,255,255,255));
					startoptions.setStyle(Text :: Bold);
					startoptions.setPosition(70,50);
					window.draw(startoptions);
					}
					
					Event m;
					while (window.pollEvent(m)){                   
						if (m.type == Event::Closed)                
						    {window.close();}       
						if (m.type == Event::KeyPressed) {          
						    if (m.key.code == Keyboard::Num1)       
						        {start = true;over = false;}       
						    else if (m.key.code == Keyboard::Num2)
						        {choice = 2;}        		   
						    else if (m.key.code == Keyboard::Num3)  
						        {choice = 3;}
						    else if (m.key.code == Keyboard::Num4)                       
								{start = false; over = true; window.close(); return 0;}
							}
					}
					window.display();
					
					switch(choice){
					case 2:
						window.clear();
						window.draw(background);
						scoreTitle.setFont(lehn);
						scoreTitle.setString("HIGH SCORES");
						scoreTitle.setCharacterSize(42);
						scoreTitle.setFillColor(Color(255,255,255,255));
						scoreTitle.setStyle(Text :: Bold);
						scoreTitle.setPosition(10,10);
						window.draw(scoreTitle);
						
						showscores.setFont(lehn);
						showscores.setString("1. " + hscorenames[0] + ":" + to_string(hscores[0]) + "\n2. " + hscorenames[1] + ":" + to_string(hscores[1]) + "\n3. " + hscorenames[2] + ":" + to_string(hscores[2]) + "\n4. " + hscorenames[3] + ":" + to_string(hscores[3]) + "\n5. " + hscorenames[4] + ":" + to_string(hscores[4]) + "\n6. " + hscorenames[5] + ":" + to_string(hscores[5]) + "\n7. " + hscorenames[6] + ":" + to_string(hscores[6]) + "\n8. " + hscorenames[7] + ":" + to_string(hscores[7]) + "\n9. " + hscorenames[8] + ":" + to_string(hscores[8]) + "\n10. " + hscorenames[9] + ":" + to_string(hscores[9]));
						showscores.setCharacterSize(24);
						showscores.setFillColor(Color(255,255,255,255));
						showscores.setStyle(Text :: Bold);
						showscores.setPosition(20,80);
						window.draw(showscores);
												
						while (window.pollEvent(m)){              
							if (m.type == Event::Closed)     
								window.close();                       
							if (m.type == Event::KeyPressed) {         
								if (m.key.code == Keyboard::Num2)
									{choice = 0;}
								}
						}
						window.display();
						break;
						
					case 3:
						window.clear();
						window.draw(background);
						// help display
						Text helptext;
						helptext.setFont(lehn);
						helptext.setString("The Goal of the game is to score\nas many points as possible by\ncompleting rows by dropping blocks.\nMultiple line completions at once\ngive bonus score. The game will\ngrow progressively harder as time\npasses. Bombs may drop randomly,\ndoing nothing, causing a small\nexplosion, or erasing everything.\nYou lose if the grid fills up.\nControls:\nPress <- and -> for movement.\nPress up to quickly drop block\npress down to rotate block\nPress Space to hard drop.\nPress 'H' key to pause. 3 to back");
						helptext.setCharacterSize(19);
						helptext.setFillColor(Color(255,255,255,255));
						helptext.setStyle(Text :: Bold);
						helptext.setPosition(5,0);
						window.draw(helptext);
								Event m;
						while (window.pollEvent(m)){              
							if (m.type == Event::Closed)     
								window.close();                       
							if (m.type == Event::KeyPressed) {         
								if (m.key.code == Keyboard::Num3)     
								    {choice = 0;}
								}
						}
						window.display();
						
						break;
					}
					
				}
        }
         
        //---The Window that now Contains the Frame is Displayed---//
        window.display();
    }
}
    
    
    return 0;
}
