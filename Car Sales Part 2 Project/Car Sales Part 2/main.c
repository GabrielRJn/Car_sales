#define _CRT_SECURE_NO_WARNINGS
#define TRUE 1
#define FALSE 0
#define DISCOUNT 0.15
#define MENU_CHOICE_PURCHASE_CAR '1'
#define MENU_CHOICE_STATUS '2'
#define MENU_CHOICE_VIEW_CARS '3'
#define MENU_CHOICE_EXIT '4'
#define CHOICE_YES 'y'
#define CHOICE_NO 'n'
#define CHOICE_RETURN_TO_MENU 'a'
#define CHOICE_VIEW_SPECIFIC_VALUES 'b'
#define NO_CHOICE_SELECTED 'x'
#define MAX_MEMBERSHIP_AGE 40
#define MIN_MEMBERSHIP_AGE 18
#define MAXIMUM_SALES 10
#define CVS_FILE "C:\\Users\\Gabriel\\Introduction_to_Programming\\Car_sales\\userdata.csv"
#define bool unsigned char
#define FILE_OPEN 0
#define FILE_CLOSED 1
#define FILE_ERROR 2

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h> 



unsigned short carsSold = 0, carQuantity, userAge, totalSales = 0, wholeNumberEntered, salesLeft, GolfCarsRemaining = 20, LexusCarsRemaining = 10, MercedesCarsRemaining = 10, carsAvailable = 40, repeatingCustomer = FALSE, hasMembership = FALSE, enoughCarsAvailable = FALSE;

char userChoice, membershipChoice, hasCarInsurance;

float totalPrice = 0.00, totalRevenue, floatNumberEntered;




// ALL ARRAYS USED

float  recordTotalPrice[MAXIMUM_SALES]; //view total price per sale in "View Sales"

float carPrice[MAXIMUM_SALES] = { 80000, 20000, 50000 }; //individual prices for each car for when they make a purchase

char recordCustomerName[MAXIMUM_SALES][101]; // record customer name in "View Sales

char membershipType[][10] = { "N/A", "Car Club" }; // record if customer was given membership discount in "View Sales"

char carType[][40] = { "Lexus","Golf", "Mercedes-Benz" }; //names of each car recorded in "View Sales"

unsigned short displayMembershipType[MAXIMUM_SALES]; //Store indexes for membershipType

unsigned short displayTypeOfCar[MAXIMUM_SALES]; //Store indexes for carType

unsigned short recordQuantity[MAXIMUM_SALES]; //Record how many cars were sold per sale in "View Sales"

char remainingStrings[][61] = { "Golf cars Remaining:", "Lexus Cars Remaining:", "Mercedes-Benz Remaining:" };

char purchaseTimes[MAXIMUM_SALES][151];




FILE* file;
unsigned char fileStatus = FILE_CLOSED;


//FUNCTIONS
FILE* createFile(char fileName[101])
{
	file = fopen(fileName, "w");
	if (file != NULL)
	{
		fclose(file);
	}
	return file;
}

void openFile(char fileName[201], char mode[4])
{
	file = fopen(fileName, mode);
	if (file == NULL)
	{
		if (createFile(fileName) == NULL)
		{
			fileStatus = FILE_ERROR;
		}
		else
		{
			openFile(fileName, mode);
		}
	}
	else
	{
		fileStatus = FILE_OPEN;
	}
}

void closeFile()
{
	if (fileStatus == FILE_OPEN)
	{
		fclose(file);
		fileStatus = FILE_CLOSED;
	}
}

void readFileData()
{
	int lineCounter = 0;

	while (1)
	{
		unsigned short carQuantityValue = 0, carTypeValue = 0, membershipTypeValue = 0;
		float pricePaid = 0;
		char customerNameValue[201] = "";

		char purchaseTimesValue[201] = "";

		int scanResult = fscanf(
			file,
			" %hd,%f,%hd,%hd, %[^,], %[^\n],",
			&carQuantityValue,
			&pricePaid,
			&carTypeValue,
			&membershipTypeValue,
			&customerNameValue,
			&purchaseTimesValue

		);

		if (scanResult == EOF)
		{
			break;
		}


		strcpy(recordCustomerName[lineCounter], customerNameValue);

		strcpy(purchaseTimes[lineCounter], purchaseTimesValue);

		recordQuantity[lineCounter] = carQuantityValue;
		recordTotalPrice[lineCounter] = pricePaid;
		displayMembershipType[lineCounter] = membershipTypeValue;
		displayTypeOfCar[lineCounter] = carTypeValue;




		carsSold += carQuantityValue;
		switch (carTypeValue)
		{
		case 0:
			LexusCarsRemaining -= carQuantityValue;
			break;
		case 1:
			GolfCarsRemaining -= carQuantityValue;
			break;
		case 2:
			MercedesCarsRemaining -= carQuantityValue;
		default:
			break;
		}

		lineCounter++;


	}
	carsAvailable = (LexusCarsRemaining + GolfCarsRemaining + MercedesCarsRemaining);
	totalSales = lineCounter;
}

void getFileData()
{
	openFile(CVS_FILE, "r");
	if (fileStatus == FILE_OPEN)
	{
		readFileData();
	}
	else if (fileStatus == FILE_ERROR)
	{
		printf("Error reading data from %s", CVS_FILE);
		getchar();
	}
	closeFile();
}

writeDataToFile()
{
	for (int i = 0; i < totalSales; i++)
	{
		char line[301];
		char data[50];


		_itoa((int)recordQuantity[i], data, 10);
		strcpy(line, data);
		strcat(line, ",");

		// ensure data is empty
		strcpy(data, "");
		// convert float to string and save it in data

		_gcvt(recordTotalPrice[i], 6, data);
		strcat(line, data);
		strcat(line, ",");
		strcpy(data, "");


		_itoa((int)displayTypeOfCar[i], data, 10);
		strcat(line, data);
		strcat(line, ",");
		strcpy(data, "");

		_itoa((int)displayMembershipType[i], data, 10);
		strcat(line, data);
		strcat(line, ",");
		strcpy(data, "");

		strcat(line, recordCustomerName[i]);
		strcat(line, ",");

		strcat(line, purchaseTimes[i]);



		fprintf(file, line);


		if (i < totalSales - 1) {
			fprintf(file, "\n");
		}


	}
}

void saveData()
{
	openFile(CVS_FILE, "w");
	if (fileStatus == FILE_OPEN)
	{
		writeDataToFile();
	}
	else if (fileStatus == FILE_ERROR)
	{
		printf("error saving data to file");
		getchar();
	}
	closeFile();
}

void clearScreen()
{
	system("cls");
}

void giveSpace(unsigned short numberOfSpaces)
{
	for (int i = 0; i != numberOfSpaces; i++)
	{
		printf("\n");
	}
}

void promptUser(char message[91])
{
	giveSpace(2);
	printf(message);
	giveSpace(1);

}

void showWhereToEnterInput()
{
	giveSpace(1);
	printf("YOUR INPUT:");
}



void noteForUser(char message[91])
{
	giveSpace(5);
	printf(message);
	giveSpace(1);
}

void menu_greetCustomer()
{
	char openingMessage[] = "Welcome to Gabriel's Car Dealership";

	int messagelength = strlen(openingMessage);

	for (int c = 0; c < messagelength + 4; c++) // top of box
	{
		putchar('*');
	}
	printf("\n* %s *\n", openingMessage); // middle

	for (int c = 0; c < messagelength + 4; c++) //bottom of box
	{
		putchar('*');
	}
	printf("\n\n%hd cars are available\n\nWhat would you like to do?\n", carsAvailable);

}

void menu_displayMenu()
{


	printf("1. Purchase a car\n");
	printf("2. View sales\n");
	printf("3. View Cars\n");
	printf("4. Exit\n");

	promptUser("Please choose one of the following options");

	noteForUser("**NOTE: Press ENTER after any input is entered to progress. Your first character will be read**");
	showWhereToEnterInput();

}

void ViewCars_GolfRemaining()
{
	printf("Golf remaining: %hd \n", GolfCarsRemaining);
}

void ViewCars_LexusRemaining()
{
	printf("Lexus remaining: %hd \n", LexusCarsRemaining);
}

void ViewCars_MercedesRemaining()
{
	printf("Mercedes-Benz remaining: %hd \n", MercedesCarsRemaining);

}



void removeNewLines()
{
	while (getchar() != '\n');
}

void displayAge()
{
	printf("\nage: %hd\n", userAge);
}

void disableMembership()
{
	hasMembership = FALSE;
}

void enableMembership()
{
	hasMembership = TRUE;
}

void displayReasonForRejectedMembership()
{
	clearScreen();
	printf("Not eligible for Car Club Membership");

	//So customers are told why they are denied membership

	if (userAge <= MIN_MEMBERSHIP_AGE)
	{
		printf("\nReason: Below age limit");
		promptUser("Press ENTER to progress");
	}
	else if (userAge >= MAX_MEMBERSHIP_AGE)
	{
		printf("\nReason: Above age limit");
		promptUser("Press ENTER to progress");
	}
	else if (hasCarInsurance == CHOICE_NO)
	{
		printf("\nReason: No Car Insurance");
		promptUser("Press ENTER to progress");
	}
	displayMembershipType[totalSales] = 0; // Set index 1 in membershipType to display "Membership Discount: N/A to show its not given"

	removeNewLines();
	getchar();

}

void membershipSignUp()
{
	do {
		membershipChoice = NO_CHOICE_SELECTED;
		while (membershipChoice != 'y' && membershipChoice != 'n')
		{
			clearScreen();
			printf("\nWould you like to join Car Club?(y/n)\n");
			removeNewLines();
			promptUser("**You must choose one of the following options to proceed**");
			showWhereToEnterInput();

			scanf(" %c", &membershipChoice);
			membershipChoice = tolower(membershipChoice);
		}


		switch (membershipChoice) //triggers process of signing up for Car Club membership discount, switch reduces amount of if statements
		{

		case CHOICE_YES:


			disableMembership();  // reset membership for every customer

			clearScreen();



			do
			{
				clearScreen();
				removeNewLines();
				printf("\nMEMBERSHIP SIGN UP\n");
				printf("\nWhat is your age?\n");
				showWhereToEnterInput();
				floatNumberEntered = scanf("%hd", &userAge);  //check to see they are between 18-40

				wholeNumberEntered = userAge; //remove decimals 

			} while (wholeNumberEntered == FALSE); // prevent invalid input


			do
			{

				clearScreen();
				displayAge();

				printf("\nDo you have Car Insurance?(y/n)\n");
				showWhereToEnterInput();
				scanf(" %c", &hasCarInsurance);
				hasCarInsurance = tolower(hasCarInsurance);
				//they must have car insurance

			} while (hasCarInsurance != CHOICE_YES && hasCarInsurance != CHOICE_NO);




			if (hasCarInsurance == CHOICE_YES && userAge >= MIN_MEMBERSHIP_AGE && userAge <= MAX_MEMBERSHIP_AGE)
			{
				printf("\nWelcome to Car Club! You will now be redirected to begin with your purchase.\n");
				removeNewLines();
				getchar();
				enableMembership(); // Triggers if statement that gives discount (down below)

				displayMembershipType[totalSales] = 1; //Will be used to select index 0 in membershipType to print "Membership Discount: Car Club" in View Sales

													   //All membership discounts given from sales can be seen in "View Sales" from menu

			}
			else
			{
				disableMembership();
				displayReasonForRejectedMembership();
			}
			break;

		case CHOICE_NO:
			disableMembership();
			displayMembershipType[totalSales] = 0;
			break;

		default:
			printf("\nInvalid choice, press enter to try again\n");
			removeNewLines();
			getchar();
			clearScreen();
			break;

		}

	} while (membershipChoice != CHOICE_YES && membershipChoice != CHOICE_NO);
	//So that the program can only proceed with valid input on whether or not they want membership



}

void checkIfRepeatingCustomer()
{
	repeatingCustomer = FALSE;

	if (totalSales > 0)
	{

		for (int i = 0; (i <= (totalSales - 1)) && (repeatingCustomer != TRUE); i++)
		{
			repeatingCustomer = (strcmp(recordCustomerName[totalSales], recordCustomerName[i]) != 0) ? FALSE : TRUE; //will trigger giveDiscount function if TRUE

		}
	}
}



void getTimeOfPurchase()
{


	unsigned int numOfMessages = 0;


	time_t rawtime;
	struct tm* customerPurchaseTime;

	time(&rawtime);

	customerPurchaseTime = localtime(&rawtime);

	strcpy(purchaseTimes[totalSales], asctime(customerPurchaseTime));

}


void updateSalesInfo()
{



	getTimeOfPurchase();

	recordTotalPrice[totalSales] = totalPrice; //store how much the customer paid in "View Sales"

	carsAvailable = (LexusCarsRemaining + GolfCarsRemaining + MercedesCarsRemaining);
	carsSold += carQuantity;
	totalSales++;
	//status is updated


}



void giveDiscount()
{


	if (hasMembership == TRUE)  //triggered from membership sign up (above)
	{

		noteForUser("As a member of Car Club you recieve a discount.\n");
		totalPrice *= (1 - DISCOUNT);
	}
	else if (repeatingCustomer == TRUE)
	{
		noteForUser("Welcome back, as a repeating customer you recieve a discount.");
		totalPrice *= (1 - DISCOUNT);

	}
}

void displayCarTypes()
{

	do
	{

		clearScreen();
		printf("\nWhich car would you like to buy? (please select 0,1,2)");
		printf("\n 0. Lexus 80000 GBP");
		printf("\n 1. Golf 20000 GBP");
		printf("\n 2. Mercedez-Benz 50000GBP\n");
		showWhereToEnterInput();

		scanf("%hd", &displayTypeOfCar[totalSales]); //if transaction not complete, the values at totalsales overwritten
	} while (displayTypeOfCar[totalSales] > 2); //prevent invalid input

}

void menu_buyCar()
{
	if (carsAvailable == 0)
	{
		printf("\nSorry,no cars are available"); //No sale if theres no cars
	}
	else
	{
		clearScreen();


		membershipSignUp();



		clearScreen();
		printf("Please enter your name:\n");
		showWhereToEnterInput();
		scanf("\n%[^\n]s", &recordCustomerName[totalSales]);

		checkIfRepeatingCustomer();

		displayCarTypes();


		printf("\nHow many cars would you like to purchase?\n");
		wholeNumberEntered = scanf("%hd", &carQuantity); //remove decimals




		if ((carQuantity > carsAvailable) || (carQuantity == 0)) //prevent negative value or record useless info
		{
			printf("Sorry, your transaction cannot be completed. You have selected an invalid quantity"); //This prevents carsAvailable being a negative value

			removeNewLines();
			getchar();
		}
		else
		{

			if (wholeNumberEntered == FALSE) {
				//if anything other than a number is entered, the transaction is cancelled. No other character, negative number (apart from -0 as it is 0), string, is permitted 
				printf("Sorry, your transaction cannot be completed. You have selected an invalid quantity.");

				//your data is not saved if you fail to enter a number, totalsales counter does not increase in updateSalesInfo
				//as totalsales is an index for almost all the arrays here, all data used to make this transaction will be overwritten by the next user





				printf("\n Press Enter to be redirected to the menu...");
				removeNewLines();
				getchar();

			}
			else
			{


				unsigned short CarTypeSwitchTrigger = displayTypeOfCar[totalSales];
				enoughCarsAvailable = FALSE;

				switch (CarTypeSwitchTrigger)
				{
				case 0: //Lexus chosen

					if (LexusCarsRemaining >= carQuantity)
					{
						LexusCarsRemaining -= carQuantity;
						enoughCarsAvailable = TRUE;
					}

					break;
				case 1: //Golf chosen

					if (GolfCarsRemaining >= carQuantity)
					{
						GolfCarsRemaining -= carQuantity;
						enoughCarsAvailable = TRUE;
					}

					break;
				case 2: //Mercedes-Benz chosen
					if (MercedesCarsRemaining >= carQuantity)
					{
						MercedesCarsRemaining -= carQuantity;
						enoughCarsAvailable = TRUE;
					}

					break;
				default:
					noteForUser("ERROR");
					break;

				}

				if (enoughCarsAvailable == FALSE)
				{
					noteForUser("Quantity of car model not available to complete transaction. Returning to menu...");
					removeNewLines();
					getchar();

				}
				else
				{
					recordQuantity[totalSales] = carQuantity; //Record how many cars they bought in "View Sales" in menu

					totalPrice = carQuantity * carPrice[displayTypeOfCar[totalSales]]; //Calculate price from array that holds the value of the car of what they selected


					giveDiscount();


					printf("\nCongratulations! You have bought %hd car(s) for %.2f\n", carQuantity, totalPrice);
					promptUser("Press ENTER to return to the menu");
					removeNewLines();
					getchar();

					updateSalesInfo();
					//status is updated
					//if the sale is incomplete it is not saved and data will be discarded
				}
			}
		}

	}
}
void printSpecificSale(unsigned short min, unsigned short max)
{

	clearScreen();

	printf("STATUS");
	giveSpace(2);

	totalRevenue = 0;


	for (int i = 0; i < totalSales; i++)
	{
		if (recordQuantity[i] >= min && recordQuantity[i] <= max)
		{

			printf(
				"\nIndex: %d| Customer: %s | Total cost of transaction: %.2f | Membership Discount: %s | Car type: %s | Quantity: %hd |Time of purchase: %s ",
				i,
				recordCustomerName[i],
				recordTotalPrice[i],
				membershipType[displayMembershipType[i]],
				carType[displayTypeOfCar[i]],
				recordQuantity[i],
				purchaseTimes[i]

			);

			totalRevenue += recordTotalPrice[i];
		}

	}

}
void getInputForViewSpecificSale()
{

	unsigned short minQuantity = 0, maxQuantity = 0;
	char userChoiceForSpecificSale = NO_CHOICE_SELECTED; // reset user choice
	bool validRangeOfValues = FALSE; // reset range
	wholeNumberEntered = NO_CHOICE_SELECTED; //reset validation

	promptUser("Would you like to:\na.Return to the menu\nb.View Sales of a specific car quantity");
	showWhereToEnterInput();
	scanf("\n%c", &userChoiceForSpecificSale);
	userChoiceForSpecificSale = tolower(userChoiceForSpecificSale);

	switch (userChoiceForSpecificSale)
	{
	case CHOICE_VIEW_SPECIFIC_VALUES:

		while (validRangeOfValues != TRUE) // this is so that the user does not select a maximum number lower than the minimum number
		{
			do
			{
				clearScreen();
				promptUser("Please choose the minimum quantity:");
				showWhereToEnterInput();
				removeNewLines();
				floatNumberEntered = scanf("%hd", &minQuantity);

				wholeNumberEntered = minQuantity;//strip decimals and change to true or false
			} while (wholeNumberEntered == FALSE);

			do
			{
				clearScreen();
				printf("Minimum car Quantity selected: %hd", minQuantity);
				giveSpace(2);

				promptUser("Please choose the maximum quantity:");
				showWhereToEnterInput();
				removeNewLines();
				floatNumberEntered = scanf("%hd", &maxQuantity);

				wholeNumberEntered = maxQuantity; // strip decimals and change to or false

			} while (wholeNumberEntered == FALSE);

			if (maxQuantity >= minQuantity) // check to see if the user entered a valid range
			{
				validRangeOfValues = TRUE;

			}
			else
			{
				promptUser("**You have entered an invalid range**\nPress ENTER to try again...");
				removeNewLines();
				getchar();
				//while loop only exits when user enters a valid range to prevent errors
			}
		}
		printSpecificSale(minQuantity, maxQuantity);
		promptUser("Press ENTER to return to the menu");
		getchar();
		getchar();
		break;

	case CHOICE_RETURN_TO_MENU:
		break;

	default:
		printf("Sorry, you have selected invalid input");
		promptUser("Press ENTER to return to the menu");
		removeNewLines();
		getchar();
		break;
	}
}



void menu_viewSales()
{
	clearScreen();


	printf("\nSTATUS\n\n");

	totalRevenue = 0;

	for (int i = 0; i < totalSales; i++)
	{

		printf(
			"\nIndex: %d| Customer: %s | Total cost of transaction: %.2f | Membership Discount: %s | Car type: %s |Quantity: %hd |Time of purchase: %s ",
			i,
			recordCustomerName[i],
			recordTotalPrice[i],
			membershipType[displayMembershipType[i]],
			carType[displayTypeOfCar[i]],
			recordQuantity[i],
			purchaseTimes[i]




		);

		

		totalRevenue += recordTotalPrice[i];
	}

	if (totalSales == 0)
	{
		printf("**No sales were made, please come back later**");
	}

	printf("\n\nTotal sales: %hd ", totalSales);

	printf("\n\nTotal revenue: %.2f GBP", totalRevenue);


	giveSpace(2);



	removeNewLines();
	getInputForViewSpecificSale();
	giveSpace(3);





}



swapValues(unsigned short* a, unsigned short* b)
{
	short temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

moveTotalPrice(float* a, float* b)
{
	float storeFloat;
	storeFloat = *a;
	*a = *b;
	*b = storeFloat;

}

swapBool(bool* a, bool* b)
{
	bool temp;
	temp = *a;
	*a = *b;
	*b = temp;

}

void rearrangeViewSalesByNumberOfCarsSold()
{
	for (int i = 0; i < totalSales - 1; i++)
	{
		for (int j = 1; j < totalSales; j++)
		{
			if (recordTotalPrice[j] > recordTotalPrice[i])
			{

				char temp[101];
				swapValues(&recordQuantity[i], &recordQuantity[j]);

				swapValues(&displayTypeOfCar[i], &displayTypeOfCar[j]);

				swapValues(&displayMembershipType[i], &displayMembershipType[j]);

				moveTotalPrice(&recordTotalPrice[i], &recordTotalPrice[j]);


				strcpy(temp, recordCustomerName[i]);
				strcpy(recordCustomerName[i], recordCustomerName[j]);
				strcpy(recordCustomerName[j], temp);

				strcpy(temp, purchaseTimes[i]);
				strcpy(purchaseTimes[i], purchaseTimes[j]);
				strcpy(purchaseTimes[j], temp);

			}
		}

	}

}


void rearrangeByCarsSold()
{
	unsigned short mostCarsRemaining[] = { GolfCarsRemaining, LexusCarsRemaining, MercedesCarsRemaining };

	for (int k = 0; k < 2; k++)
	{
		for (int m = k + 1; m < 3; m++)
		{
			if (mostCarsRemaining[m] > mostCarsRemaining[k])
			{
				char temp0[61];
				swapBool(&mostCarsRemaining[k], &mostCarsRemaining[m]);
				strcpy(temp0, remainingStrings[k]);
				strcpy(remainingStrings[k], remainingStrings[m]);
				strcpy(remainingStrings[m], temp0);

			}
		}

	}
	printf("Here are the cars available at Gabriel's Car Dealership!\n");
	giveSpace(3);

	for (int i = 0; i < 3; i++)
	{
		printf("Index:%d | %s %hd\n", i, remainingStrings[i], mostCarsRemaining[i]);
	}

}

void menu_viewCars()
{
	clearScreen();
	rearrangeByCarsSold();


	promptUser("Please press ENTER to return to the menu");
	getchar();
	getchar();
}



void thankUserExit()
{

	if (totalSales == 10)
	{
		noteForUser("Maximum sales reached");
	}

	printf("\nThank you for using the program. Goodbye\n"); // thank customer before exiting 

	saveData();
}

//MAIN
void main() {

	getFileData();

	do {
		clearScreen();

		menu_greetCustomer();
		menu_displayMenu();

		userChoice = getchar();
		switch (userChoice) //Switch so that you can interact with menu
		{

		case MENU_CHOICE_PURCHASE_CAR:
			menu_buyCar();
			break;

		case MENU_CHOICE_STATUS:
			rearrangeViewSalesByNumberOfCarsSold();
			menu_viewSales();
			break;

		case MENU_CHOICE_VIEW_CARS:
			menu_viewCars();
			break;
		}



	} while (userChoice != MENU_CHOICE_EXIT && totalSales != 10);




	clearScreen();
	thankUserExit(); // thank customer before exiting


}