#include <avr/io.h>
#define F_CPU 1000000
//telling controller crystal frequency attached
#include <util/delay.h>
#define E   5
#define RS  6
#define RW  7

void send_a_command(unsigned char command);
void send_a_character(unsigned char character);
void send_a_string(char *string_of_characters);
void menu();
void use_keypad();
void listOfCondidates();
void logIn_USERNAME();
void logIn_PASSWORD();
void cancelFunction();
void secondPageOfCondidatesList();
void votingFucntion();
void lastPageOfcondidateList();
void masterMenu();
void secondPageOfMasterMenu();
void thirdPageOfCondidatesList();
void decisionMenu();
void winnerAnouncment();
void timesOfVotingFunction();
void infoMenu();

	int key=0;//allocating integer to reset the LCD once it reaches its display limit
	int keypressed=0;//integer for storing matrix value
	int myValue[2];
    char condidatesName[6][20] = {"Alexander","Eric","Amelia","Ariana","Luis","Jacob"};
	char condidatesID[6][20] = {",his id:16",",his id:24",",her id:58",",her id:62",",his id:37",",his id:49"};
	int i = 0;
	char operand;
	int usrname;
	int myPass[2];
	int j=0;
const unsigned char passwords[5][20] = {"455","270","705","112","595"};
int timesOfVoting[4] = {0,0,0,0};
int votes[6] = {6,7,6,8,4,2}; 
	
int main(void)
{

	DDRA = 0xFF;
	DDRB = 0xFF;
	DDRD = 0xFF;
	DDRB=0x0F;//taking column pins as input and row pins as output
	PORTB=0xF0;// powering the row ins
	_delay_ms(50);
	send_a_command(0x01); //Clear Screen 0x01 = 00000001
	_delay_ms(50);
	
	send_a_command(0x38);//telling lcd we are using 8bit command /data mode
	_delay_ms(50);
	
	send_a_command(0b00001111);//LCD SCREEN ON and courser blinking
	send_a_string("     WELCOME TO");//displaying a string
	send_a_command(0x80 + 0x40 +0);// moving courser to second line of LCD
	send_a_string("   VOTING SYSTEM");//displaying a string


	//************************************************************************** 3500
	_delay_ms(300);


	menu();
	
}

void menu(){
		send_a_command(0x01);//clear lcd
		
		send_a_string("CHOOSE YOUR ACTION");//displaying a string
		send_a_command(0x80 + 0x40 +0);// moving courser to second line of LCD
		send_a_string("1.LIST OF CANDIDATES");//displaying a string
		send_a_command(0x94);// moving courser to third line of LCD
		send_a_string("2.LOG IN");//displaying a string
		send_a_command(0xD4);// moving courser to forth line of LCD
		send_a_string("3.INFO");//displaying a string
				
		while (1){
		if (PINB!=0b11110000)//in any of column pins goes high execute the loop
		{
					
			keypressed = 0;
			DDRB &= 0x00;
			DDRB |= 0x0F;
			PORTB = 0xF0;
			while(PINB == 0xF0);
			keypressed |= PINB;
			_delay_ms(100);
			DDRB &= 0x00;
			DDRB |= 0xF0;
			PORTB = 0x0F;
			keypressed |= PINB;
			
		
		if (keypressed==0b11101110)
		{
			send_a_string("1");
			listOfCondidates();
		}
		
		if (keypressed==0b11101101)
		{
			send_a_string("2");
			logIn_USERNAME();			
		}
		if (keypressed==0b11101011)
		{
			send_a_string("3");
			infoMenu();			
		}	
	
		}
	}
}

void infoMenu(){
		send_a_command(0x01);// clear lcd
		send_a_string("     THANKS TO");//displaying a string
		send_a_command(0x80 + 0x40 +0);// moving courser to second line of LCD
		send_a_string("   ELNAZ RAHMATI");//displaying a string
		send_a_command(0x94);// moving courser to third line of LCD
		send_a_string("    ARMAN RIASI");//displaying a string
		send_a_command(0xD4);// moving courser to forth line of LCD
		send_a_string("   GHAZALE ZEHTAB");//displaying a string
		
		
		while(1){
				if (PINB!=0b11110000)//in any of column pins goes high execute the loop
				{
					
					keypressed = 0;
					DDRB &= 0x00;
					DDRB |= 0x0F;
					PORTB = 0xF0;
					while(PINB == 0xF0);
					keypressed |= PINB;
					_delay_ms(100);
					DDRB &= 0x00;
					DDRB |= 0xF0;
					PORTB = 0x0F;
					keypressed |= PINB;
					
					
				if (keypressed==0b01111011)//#
					{
						cancelFunction();
					}
				}		
		
		}
}


void cancelFunction(){
	menu();
}

void logIn_USERNAME(){
	
			send_a_command(0x01);//clear lcd
			send_a_string("ENTER USERNAME:");//displaying a string
			send_a_command(0x80 + 0x40 +0);// moving courser to second line of LCD
			
		if (PINB!=0b11110000)//in any of column pins goes high execute the loop
		{
			
			keypressed = 0;
			DDRB &= 0x00;
			DDRB |= 0x0F;
			PORTB = 0xF0;
			while(PINB == 0xF0);
			keypressed |= PINB;
			_delay_ms(100);
			DDRB &= 0x00;
			DDRB |= 0xF0;
			PORTB = 0x0F;
			keypressed |= PINB;
			
			
			if (keypressed==0b10111110)
			{
				send_a_string("7");
				usrname = 7;
				logIn_PASSWORD();
			}
			
			if (keypressed==0b11011110)
			{
				send_a_string("4");
				usrname = 4;
				logIn_PASSWORD();
			}

			if (keypressed==0b11101110)
			{
				send_a_string("1");
				usrname = 1;
				logIn_PASSWORD();
			}

			if (keypressed==0b10111101)
			{
				send_a_string("8");
				usrname = 8;
				logIn_PASSWORD();
			}

			if (keypressed==0b11011101)
			{
				send_a_string("5");
				usrname = 5;
				logIn_PASSWORD();
			}

			if (keypressed==0b11101101)
			{
				send_a_string("2");
				usrname = 2;
				logIn_PASSWORD();
			}

			if
			(keypressed==0b01111101)
			{
				send_a_string("0");
				usrname = 0;
				logIn_PASSWORD();
			}

			if (keypressed==0b10111011)
			{
				send_a_string("9");
				usrname = 9;
				logIn_PASSWORD();
			}

			if (keypressed==0b11011011)
			{
				send_a_string("6");
				usrname = 6;
				logIn_PASSWORD();
			}

			if (keypressed==0b11101011)
			{
				send_a_string("3");
				usrname = 3;
				logIn_PASSWORD();
			}
			
		}
}

void logIn_PASSWORD(){
		_delay_ms(100);
		send_a_command(0x01);//clear LCD
		send_a_string("ENTER PASSWORD:");//displaying a string
		send_a_command(0x80 + 0x40 +0);// moving courser to second line of LCD
				
		int checkPass = 0;

		
		while(1)
		{
			if (j == 3){
				j = 0;
			}
			
			if (PINB!=0b11110000)//in any of column pins goes high execute the loop
			{
				
				keypressed = 0;
				DDRB &= 0x00;
				DDRB |= 0x0F;
				PORTB = 0xF0;
				while(PINB == 0xF0);
				keypressed |= PINB;
				_delay_ms(100);
				DDRB &= 0x00;
				DDRB |= 0xF0;
				PORTB = 0x0F;
				keypressed |= PINB;
				
				
				if (keypressed==0b10111110)
				{
					send_a_string("7");
					myPass[j] = 7;
					j++;
				}
				
				if (keypressed==0b11011110)
				{
					send_a_string("4");
					myPass[j] = 4;
					j++;
				}

				if (keypressed==0b11101110)
				{
					send_a_string("1");
					myPass[j] = 1;
					j++;
				}

				if (keypressed==0b01111110)
				{
					send_a_command(0x80 + 0x40 +0);// moving courser to second line of LCD
					send_a_string("    ");//displaying a string
					send_a_command(0x10);// Move cursor left by one character
					send_a_command(0x10);// Move cursor left by one character
					send_a_command(0x10);// Move cursor left by one character
					send_a_command(0x10);// Move cursor left by one character
					
					j = 0;
				}

				if (keypressed==0b10111101)
				{
					send_a_string("8");
					myPass[j] = 8;
					j++;
				}

				if (keypressed==0b11011101)
				{
					send_a_string("5");
					myPass[j] = 5;
					j++;
				}

				if (keypressed==0b11101101)
				{
					send_a_string("2");
					myPass[j] = 2;
					j++;
				}

				if
				(keypressed==0b01111101)
				{
					send_a_string("0");
					myPass[j] = 0;
					j++;
				}

				if (keypressed==0b10111011)
				{
					send_a_string("9");
					myPass[j] = 9;
					j++;
				}

				if (keypressed==0b11011011)
				{
					send_a_string("6");
					myPass[j] = 6;
					j++;
				}

				if (keypressed==0b11101011)
				{
					send_a_string("3");
					myPass[j] = 3;
					j++;
				}

				if (keypressed==0b01111011)//#
				{
					checkPass = (100*myPass[0]) + (10*myPass[1]) + myPass[2];
					checkPass *= 5;
					checkPass /= 6;
					if (checkPass == 455){
							if (strncmp(passwords[usrname] , "455",3)==0){
									if (timesOfVoting[usrname] != 1){
													timesOfVoting[usrname] = 1;
													send_a_command(0x01);// clear LCD
													send_a_string("     LOGGED IN");//displaying a string
													send_a_command(0x80 + 0x40 +0);// moving courser to second line of LCD
													send_a_string("   SUCCESSFULLY");//displaying a string
													_delay_ms(1500);
													votingFucntion();
									}
									else {
										timesOfVotingFunction();
									}
							}
					}
					if (checkPass == 270){
						if (strncmp(passwords[usrname] , "270",3)==0){
							if (timesOfVoting[usrname] != 1){
									timesOfVoting[usrname] = 1;							
									send_a_command(0x01);// clear LCD
									send_a_string("     LOGGED IN");//displaying a string
									send_a_command(0x80 + 0x40 +0);// moving courser to second line of LCD
									send_a_string("   SUCCESSFULLY");//displaying a string
									_delay_ms(1500);
									votingFucntion();
							}
							else {
								timesOfVotingFunction();
							}
						}
					}
					if (checkPass == 705){
						if (strncmp(passwords[usrname] , "705",3)==0){
							if (timesOfVoting[usrname] != 1){
									timesOfVoting[usrname] = 1;							
									send_a_command(0x01);// clear LCD
									send_a_string("     LOGGED IN");//displaying a string
									send_a_command(0x80 + 0x40 +0);// moving courser to second line of LCD
									send_a_string("   SUCCESSFULLY");//displaying a string
									_delay_ms(1500);
									votingFucntion();
							}
							else {
								timesOfVotingFunction();
							}						
						}
					}
					if (checkPass == 112){
						if (strncmp(passwords[usrname] , "112",3)==0){
							if (timesOfVoting[usrname] != 1){							
									timesOfVoting[usrname] = 1;							
									send_a_command(0x01);// clear LCD
									send_a_string("     LOGGED IN");//displaying a string
									send_a_command(0x80 + 0x40 +0);// moving courser to second line of LCD
									send_a_string("   SUCCESSFULLY");//displaying a string
									_delay_ms(1500);
									votingFucntion();
							}
							else {
								timesOfVotingFunction();
							}						
						}
					}		
					if (checkPass == 595){
						if (strncmp(passwords[usrname] , "595",3)==0){
							send_a_command(0x01);// clear LCD
							send_a_string("     LOGGED IN");//displaying a string
							send_a_command(0x80 + 0x40 +0);// moving courser to second line of LCD
							send_a_string("   SUCCESSFULLY");//displaying a string
							_delay_ms(1500);
							masterMenu();
						}
					}								
					j=0;
					break;
				}



				keypressed=0;//after showing integer erasing the row column memory
				DDRB ^=0b11111111;//shifting input and power port
				_delay_ms(1);
				PORTB ^= 0b11111111;//powering row pins of keypad
				_delay_ms(220);

			}
			
			
		}
								send_a_command(0x01);// clear LCD
								send_a_string("        WRONG");//displaying a string
								send_a_command(0x80 + 0x40 +0);// moving courser to second line of LCD
								send_a_string("      USERNAME");//displaying a string
								send_a_command(0x94);// moving courser to third line of LCD
								send_a_string("        OR");//displaying a string
								send_a_command(0xD4);// moving courser to forth line of LCD
								send_a_string("      PASSWORD");//displaying a string

								_delay_ms(1500);
								menu();

							
}
void timesOfVotingFunction(){
			send_a_command(0x01);// clear lcd
			send_a_string("       SORRY");//displaying a string
			send_a_command(0x80 + 0x40 +0);// moving courser to second line of LCD
			send_a_string("  YOU VOTED BEFORE");//displaying a string
			_delay_ms(1500);
			menu();

}

void masterMenu(){
		send_a_command(0x01);// clear lcd
		send_a_string("     MASTER MENU");//displaying a string
		send_a_command(0x80 + 0x40 +0);// moving courser to second line of LCD
		send_a_string("PRESS 1 =>VOTES LIST");//displaying a string
		send_a_command(0x94);// moving courser to third line of LCD
		send_a_string("PRESS 2 =>EXIT");//displaying a string
		send_a_command(0xD4);// moving courser to forth line of LCD
	
			if (PINB!=0b11110000)//in any of column pins goes high execute the loop
			{
		
				keypressed = 0;
				DDRB &= 0x00;
				DDRB |= 0x0F;
				PORTB = 0xF0;
				while(PINB == 0xF0);
				keypressed |= PINB;
				_delay_ms(100);
				DDRB &= 0x00;
				DDRB |= 0xF0;
				PORTB = 0x0F;
				keypressed |= PINB;
		
				if (keypressed==0b11101110)//1
				{
					secondPageOfMasterMenu();
				}
				if (keypressed==0b11101101)
				{
					cancelFunction();
				}
			}
	
	
}

void secondPageOfMasterMenu(){
		char strVotes[2];
	
		send_a_command(0x01);// clear lcd
		send_a_string(condidatesName[0]);//displaying a string
		send_a_string(" ");//displaying a string
		itoa(votes[0], strVotes, 10);
		send_a_string(strVotes);//displaying a string		
		
		send_a_command(0x80 + 0x40 +0);// moving courser to second line of LCD
		send_a_string(condidatesName[1]);//displaying a string
		send_a_string(" ");//displaying a string
		itoa(votes[1], strVotes, 10);
		send_a_string(strVotes);//displaying a string		
		
		send_a_command(0x94);// moving courser to third line of LCD
		send_a_string(condidatesName[2]);//displaying a string
		send_a_string(" ");//displaying a string
		itoa(votes[2], strVotes, 10);
		send_a_string(strVotes);//displaying a string	
			
		send_a_command(0xD4);// moving courser to forth line of LCD
		send_a_string("PRESS 1 => NEXT PAGE");//displaying a string
		
			if (PINB!=0b11110000)//in any of column pins goes high execute the loop
			{
				
				keypressed = 0;
				DDRB &= 0x00;
				DDRB |= 0x0F;
				PORTB = 0xF0;
				while(PINB == 0xF0);
				keypressed |= PINB;
				_delay_ms(100);
				DDRB &= 0x00;
				DDRB |= 0xF0;
				PORTB = 0x0F;
				keypressed |= PINB;
				
				if (keypressed==0b11101110)//1
				{
					thirdPageOfCondidatesList();
					
				}
			}
		
}

void thirdPageOfCondidatesList(){
			char strVotes[2];

	
			send_a_command(0x01);// clear lcd
			send_a_string(condidatesName[3]);//displaying a string
			send_a_string(" ");//displaying a string
			itoa(votes[3], strVotes, 10);
			send_a_string(strVotes);//displaying a string			
			
			send_a_command(0x80 + 0x40 +0);// moving courser to second line of LCD
			send_a_string(condidatesName[4]);//displaying a string
			send_a_string(" ");//displaying a string
			itoa(votes[4], strVotes, 10);
			send_a_string(strVotes);//displaying a string		
			
			send_a_command(0x94);// moving courser to third line of LCD
			send_a_string(condidatesName[5]);//displaying a string
			send_a_string(" ");//displaying a string
			itoa(votes[5], strVotes, 10);
			send_a_string(strVotes);//displaying a string		
			
			send_a_command(0xD4);// moving courser to forth line of LCD
			send_a_string("PRESS 1 => NEXT PAGE");//displaying a string
			
			if (PINB!=0b11110000)//in any of column pins goes high execute the loop
			{
				
				keypressed = 0;
				DDRB &= 0x00;
				DDRB |= 0x0F;
				PORTB = 0xF0;
				while(PINB == 0xF0);
				keypressed |= PINB;
				_delay_ms(100);
				DDRB &= 0x00;
				DDRB |= 0xF0;
				PORTB = 0x0F;
				keypressed |= PINB;
				
				if (keypressed==0b11101110)//1
				{
					decisionMenu();
					
				}
			}
}

void decisionMenu(){
		send_a_command(0x01);// clear lcd
		send_a_string("PRESS 1 => EXIT");//displaying a string
		send_a_command(0x80 + 0x40 +0);// moving courser to second line of LCD
		send_a_string("PRESS 2 =>");//displaying a string
		send_a_command(0x94);// moving courser to third line of LCD
		send_a_string("RESULTS ANUONCMENT");//displaying a string

	if (PINB!=0b11110000)//in any of column pins goes high execute the loop
	{
		
		keypressed = 0;
		DDRB &= 0x00;
		DDRB |= 0x0F;
		PORTB = 0xF0;
		while(PINB == 0xF0);
		keypressed |= PINB;
		_delay_ms(100);
		DDRB &= 0x00;
		DDRB |= 0xF0;
		PORTB = 0x0F;
		keypressed |= PINB;
		
		if (keypressed==0b11101110)//1
		{
			cancelFunction();
			
		}
				if (keypressed==0b11101101)
		{
			winnerAnouncment();

		}
		
	}

}

void winnerAnouncment(){

	char winner[20];
	int temp = 0;
	
	for (int i = 0; i < 6; i++){
		if(votes[i] > temp){
			strcpy(winner,condidatesName[i]);
			temp = votes[i];
		}
	}
		send_a_command(0x01);// clear lcd
		send_a_string("    THE WINNER IS");//displaying a string
		send_a_command(0x94);// moving courser to second line of LCD
		send_a_string("      ");//displaying a string
		send_a_string(winner);//displaying a string
		_delay_ms(7000);
		
		infoMenu();

}


void listOfCondidates(){

	send_a_command(0x01);// clear lcd
	send_a_string(condidatesName[0]);//displaying a string
	send_a_string(condidatesID[0]);//displaying a string
	send_a_command(0x80 + 0x40 +0);// moving courser to second line of LCD
	send_a_string(condidatesName[1]);//displaying a string
	send_a_string(condidatesID[1]);//displaying a string
	send_a_command(0x94);// moving courser to third line of LCD
	send_a_string(condidatesName[2]);//displaying a string
	send_a_string(condidatesID[2]);//displaying a string	
	send_a_command(0xD4);// moving courser to forth line of LCD
	send_a_string("PRESS 1 => NEXT PAGE");//displaying a string
	

	if (PINB!=0b11110000)//in any of column pins goes high execute the loop
	{
	
			keypressed = 0;
			DDRB &= 0x00;
			DDRB |= 0x0F;
			PORTB = 0xF0;
			while(PINB == 0xF0);
			keypressed |= PINB;
			_delay_ms(100);
			DDRB &= 0x00;
			DDRB |= 0xF0;
			PORTB = 0x0F;
			keypressed |= PINB;
	
			if (keypressed==0b11101110)//1
			{
				secondPageOfCondidatesList();
		
			}
	}



}
secondPageOfCondidatesList(){
	
		send_a_command(0x01);// clear lcd
		send_a_string(condidatesName[3]);//displaying a string
		send_a_string(condidatesID[3]);//displaying a string		
		send_a_command(0x80 + 0x40 +0);// moving courser to second line of LCD
		send_a_string(condidatesName[4]);//displaying a string
		send_a_string(condidatesID[4]);//displaying a string
		send_a_command(0x94);// moving courser to third line of LCD
		send_a_string(condidatesName[5]);//displaying a string
		send_a_string(condidatesID[5]);//displaying a string\	
		send_a_command(0xD4);// moving courser to forth line of LCD
		send_a_command(0xD4);// moving courser to forth line of LCD

		send_a_string("PRESS 1 => YOUR VOTE");//displaying a string
	if (PINB!=0b11110000)//in any of column pins goes high execute the loop
	{
		DDRB &= 0x00;
		DDRB |= 0x0F;
		PORTB = 0xF0;
		while(PINB == 0xF0);
		keypressed |= PINB;
		_delay_ms(100);
		DDRB &= 0x00;
		DDRB |= 0xF0;
		PORTB = 0x0F;
		keypressed |= PINB;
		
			if (keypressed==0b11101110)//1
			{
				send_a_command(0x01);// clear LCD
				send_a_string("PRESS 1 =>");//displaying a string
				send_a_command(0x80 + 0x40 +0);// moving courser to second line of LCD
				send_a_string("PREVIOUS PAGE");//displaying a string
				send_a_command(0x94);// moving courser to third line of LCD
				send_a_string("PRESS 2 =>");//displaying a string				
				send_a_command(0xD4);// moving courser to forth line of LCD
				send_a_string("LOG IN PAGE");//displaying a string

				lastPageOfcondidateList();
				

			}
	}
		
}
void lastPageOfcondidateList(){
	while(1)
	{

		
		if (PINB!=0b11110000)//in any of column pins goes high execute the loop
		{
			
			keypressed = 0;
			DDRB &= 0x00;
			DDRB |= 0x0F;
			PORTB = 0xF0;
			while(PINB == 0xF0);
			keypressed |= PINB;
			_delay_ms(100);
			DDRB &= 0x00;
			DDRB |= 0xF0;
			PORTB = 0x0F;
			keypressed |= PINB;
			
			
			if (keypressed==0b11101110)//1
			{
					listOfCondidates();
			}
			
			if (keypressed==0b11101101)//2
			{
					menu();
			}
			
		}
			
		}
}

void votingFucntion(){
		int checkNumber = 0;
		send_a_command(0x01);// clear lcd
		send_a_string("PRESS 99 =>");//displaying a string
		send_a_command(0x80 + 0x40 +0);// moving courser to second line of LCD
		send_a_string("CONDIDATE LIST");//displaying a string
		send_a_command(0x94);// moving courser to third line of LCD
		send_a_string("PRESS 98 => CANCEL");//displaying a string
		send_a_command(0xD4);// moving courser to forth line of LCD
		send_a_string("YOUR VOTE => ");//displaying a string
		
	while(1)
	{
		if (i == 2){
			i = 0;
		}
		
		if (PINB!=0b11110000)//in any of column pins goes high execute the loop
		{
			
			keypressed = 0;
			DDRB &= 0x00;
			DDRB |= 0x0F;
			PORTB = 0xF0;
			while(PINB == 0xF0);
			keypressed |= PINB;
			_delay_ms(100);
			DDRB &= 0x00;
			DDRB |= 0xF0;
			PORTB = 0x0F;
			keypressed |= PINB;
			
			
			if (keypressed==0b10111110)
			{
				send_a_string("7");
				myValue[i] = 7;
				i++;
			}
			
			if (keypressed==0b11011110)
			{
				send_a_string("4");
				myValue[i] = 4;
				i++;
			}

			if (keypressed==0b11101110)
			{
				send_a_string("1");
				myValue[i] = 1;
				i++;
			}

			if (keypressed==0b01111110)
			{
			send_a_command(0xD4);// moving courser to forth line of LCD
			send_a_string("  ");//displaying a string
			send_a_command(0x10);// Move cursor left by one character
			send_a_command(0x10);// Move cursor left by one character
			i = 0;
			}

			if (keypressed==0b10111101)
			{
				send_a_string("8");
				myValue[i] = 8;
				i++;
			}

			if (keypressed==0b11011101)
			{
				send_a_string("5");
				myValue[i] = 5;
				i++;
			}

			if (keypressed==0b11101101)
			{
				send_a_string("2");
				myValue[i] = 2;
				i++;
			}

			if 
			(keypressed==0b01111101)
			{
				send_a_string("0");
				myValue[i] = 0;
				i++;
			}

			if (keypressed==0b10111011)
			{
				send_a_string("9");
				myValue[i] = 9;
				i++;
			}

			if (keypressed==0b11011011)
			{
				send_a_string("6");
				myValue[i] = 6;
				i++;
			}

			if (keypressed==0b11101011)
			{
				send_a_string("3");
				myValue[i] = 3;
				i++;
			}

			if (keypressed==0b01111011)//=
			{
				checkNumber = myValue[1] + (10*myValue[0]);
				if (checkNumber == 16){
					votes[0]++;			
					send_a_command(0x01);// clear LCD
					send_a_string("DONE");//displaying a string
					send_a_command(0x80 + 0x40 +0);// moving courser to second line of LCD
					send_a_string("YOU VOTED TO");//displaying a string
					send_a_command(0x94);// moving courser to third line of LCD
					send_a_string("ALEXANDER");//displaying a string
					_delay_ms(2500);
					menu();
				}
				if (checkNumber == 24){
					votes[1]++;
					send_a_command(0x01);// clear LCD
					send_a_string("DONE");//displaying a string
					send_a_command(0x80 + 0x40 +0);// moving courser to second line of LCD
					send_a_string("YOU VOTED TO");//displaying a string
					send_a_command(0x94);// moving courser to third line of LCD
					send_a_string("ERIC");//displaying a string					
					_delay_ms(2500);
					menu();
				}
				if (checkNumber == 58){
					votes[2]++;
					send_a_command(0x01);// clear LCD
					send_a_string("DONE");//displaying a string
					send_a_command(0x80 + 0x40 +0);// moving courser to second line of LCD
					send_a_string("YOU VOTED TO");//displaying a string
					send_a_command(0x94);// moving courser to third line of LCD
					send_a_string("AMELIA");//displaying a string
					_delay_ms(2500);
					menu();
				}								
				if (checkNumber == 62){
					votes[3]++;
					send_a_command(0x01);// clear LCD
					send_a_string("DONE");//displaying a string
					send_a_command(0x80 + 0x40 +0);// moving courser to second line of LCD
					send_a_string("YOU VOTED TO");//displaying a string
					send_a_command(0x94);// moving courser to third line of LCD
					send_a_string("ARIANA");//displaying a string					
					_delay_ms(2500);					
					menu();	
				}
				if (checkNumber == 37){
					votes[4]++;
					send_a_command(0x01);// clear LCD
					send_a_string("DONE");//displaying a string
					send_a_command(0x80 + 0x40 +0);// moving courser to second line of LCD
					send_a_string("YOU VOTED TO");//displaying a string
					send_a_command(0x94);// moving courser to third line of LCD
					send_a_string("LUIS");//displaying a string					
					_delay_ms(2500);					
					menu();			
				}
				if (checkNumber == 49){
					votes[5]++;
					send_a_command(0x01);// clear LCD
					send_a_string("DONE");//displaying a string
					send_a_command(0x80 + 0x40 +0);// moving courser to second line of LCD
					send_a_string("YOU VOTED TO");//displaying a string
					send_a_command(0x94);// moving courser to third line of LCD
					send_a_string("JACOB");//displaying a string					
					_delay_ms(2500);					
					menu();
				}
				if (checkNumber == 99){
					timesOfVoting[usrname] = 0;
					listOfCondidates();
				}	
				if (checkNumber == 98){
					timesOfVoting[usrname] = 0;
					cancelFunction();				
				}						
															
				i=0;

			}

			keypressed=0;//after showing integer erasing the row column memory
			DDRB ^=0b11111111;//shifting input and power port
			_delay_ms(1);
			PORTB ^= 0b11111111;//powering row pins of keypad
			_delay_ms(220);

		}
		
		
	}
	
}
	

void send_a_command(unsigned char command)
{
	PORTA = command;
	PORTD &= ~ (1<<RS); //putting 0 in RS to tell lcd we are sending command
	PORTD  &= ~(1<<RW);  // RW sets 7
	PORTD |= 1<<E; //telling lcd to receive command /data at the port
	_delay_ms(50);
	PORTD &= ~(1<<E);//telling lcd we completed sending data
}

void send_a_character(unsigned char character)
{
	PORTA = character;
	PORTD |= 1<<RS;//telling LCD we are sending data not commands
	PORTD  &= ~(1<<RW);  // RW sets 7
	PORTD |= 1<<E;//telling LCD to start receiving command/data
	_delay_ms(50);
	PORTD &= ~(1<<E);//telling lcd we completed sending data/command
}

void send_a_string(char *string_of_characters)
{
	while(*string_of_characters > 0)
	{
		send_a_character(*string_of_characters++);
	}
}