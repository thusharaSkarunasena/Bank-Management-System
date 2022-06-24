#include <stdio.h>
#include <stdlib.h>

/*
*
* Author - Thushara Supun
*
*/

//N - Normal
//E - Eighteen Plus
//R - Rankakulu
//W - Wanitha

const char NORMAL_ACC_TYPE = 'N';
const char EIGHTEEN_PLUS_ACC_TYPE = 'E';
const char RANKAKULU_ACC_TYPE = 'R';
const char WANITHA_ACC_TYPE = 'W';

const double INTEREST_RATE_N = 4.0;
const double INTEREST_RATE_E = 4.5;
const double INTEREST_RATE_R = 5.0;
const double INTEREST_RATE_W = 4.7;

const double MIN_BALANCE_N = 500.00;
const double MIN_BALANCE_E = 1000.00;
const double MIN_BALANCE_R = 1500.00;
const double MIN_BALANCE_W = 1000.00;

const char *DirPath = "./accDetailsDB.txt";

const int ACCOUNTS_ARRAY_SIZE = 1000;
const int ACC_NUM_SIZE = 6;
const int ACC_TYPE_SIZE = 1;
const int CUS_NAME_SIZE = 30;
const int CUS_NIC_SIZE = 10;
const int MON_AMOU_SIZE = 12;

#define ACCOUNTS_ARRAY_SIZE 1000
#define ACC_NUM_SIZE 6
#define ACC_TYPE_SIZE 1
#define CUS_NAME_SIZE 30
#define CUS_NIC_SIZE 10
#define MON_AMOU_SIZE 12

const int ERROR_CODE_1 = 1;
const int ERROR_CODE_2 = 2;
const int ERROR_CODE_3 = 3;
const int ERROR_CODE_4 = 4;
const int ERROR_CODE_5 = 5;
const int ERROR_CODE_6 = 6;
const int ERROR_CODE_7 = 7;
const int ERROR_CODE_8 = 8;
const int ERROR_CODE_9 = 9;
const int ERROR_CODE_10 = 10;
const int ERROR_CODE_11 = 11;
const int ERROR_CODE_12 = 12;

struct account{
    int acc_num;
    char acc_type;
    char cus_name[CUS_NAME_SIZE];
    char cus_nic[CUS_NIC_SIZE];
    double acc_bal;
};

void reloadAccDetails(int *, struct account[ACCOUNTS_ARRAY_SIZE], int *);
void printWelcomeMsg();
void printMainMenu();
char getMainMenuRes();
void processMainMenuRes(char, struct account[ACCOUNTS_ARRAY_SIZE], int *);
void createAccount(struct account[ACCOUNTS_ARRAY_SIZE], int *);
void depositMoney(struct account[ACCOUNTS_ARRAY_SIZE], int *);
void withdrawMoney(struct account[ACCOUNTS_ARRAY_SIZE], int *);
void searchForAnAccount(struct account[ACCOUNTS_ARRAY_SIZE], int *);
void showAllAccounts(struct account[ACCOUNTS_ARRAY_SIZE], int *);
void exitProgram(struct account[ACCOUNTS_ARRAY_SIZE], int *);
void printAccDetailsTableTop();
void printAccountDetailsRow(struct account);
void printAccDetailsTableBottom();
int validateAccountNumber(char [ACC_NUM_SIZE]);
int validateAccountType(char [ACC_TYPE_SIZE]);
int validateCustomerName(char [CUS_NAME_SIZE]);
int validateCustomerNIC(char [CUS_NIC_SIZE]);
int validateMoneyAmount(char [MON_AMOU_SIZE]);
int validateMoneyLimit(char, double);
void clearIOStreams();
void printErrorMsg(int);
void rewriteAccDetails(struct account[ACCOUNTS_ARRAY_SIZE], int *);


void main(){

    struct account accounts[ACCOUNTS_ARRAY_SIZE];
    int accountsCount = 0;
    int result = 0;
    char res;

    reloadAccDetails(&result, accounts, &accountsCount);

    if(result){

        printWelcomeMsg();

        printMainMenu();

        res = getMainMenuRes();
        processMainMenuRes(res, accounts, &accountsCount);

        //rewriteAccDetails(accounts, &accountsCount);

    }

}


void printWelcomeMsg(){

    printf("\n \t\t\t *** Welcome to ABC Bank Management System *** ");
    printf("\n \t\t\t ````````````````````````````````````````````` ");

}


void reloadAccDetails(int *result, struct account accounts[ACCOUNTS_ARRAY_SIZE], int *accountsCount){

    struct account tempAccount;
    char tempChar;
    int tempAccCount = 0;
    int tempVbl = 0;
    int tempVal = 0;
    char tempArray [30];

    FILE *filePointer;

    printf("\n # Loading Bank System Details...");

    if ((filePointer = fopen (DirPath, "a")) == NULL) {
        printErrorMsg(ERROR_CODE_1);
        *result = 0;
    }else {
        fclose(filePointer);
        filePointer = fopen (DirPath, "r");

        for(int i=0; i<30; i++){
            tempArray [i] = '\0';
        }

        if(filePointer){
            while ((tempChar = getc(filePointer)) != EOF){
                switch(tempChar){
                    case '`' :
                        sscanf(tempArray, "%d", &tempAccount.acc_num);

                        for(int i=0; i<30; i++){
                            tempArray [i] = '\0';
                        }
                        tempVal = 0;

                        break;

                    case '~' :
                        while(tempArray[tempVbl] != '\0'){
                            tempAccount.acc_type = tempArray[tempVbl];
                            tempVbl++;
                        }

                        tempVbl = 0;
                        for(int i=0; i<30; i++){
                            tempArray [i] = '\0';
                        }
                        tempVal = 0;

                        break;

                    case '#' :
                        while(tempArray[tempVbl] != '\0'){
                            tempAccount.cus_name[tempVbl] = tempArray[tempVbl];
                            tempVbl++;
                        }

                        tempVbl = 0;
                        for(int i=0; i<30; i++){
                            tempArray [i] = '\0';
                        }
                        tempVal = 0;

                        break;

                    case '^' :
                        while(tempArray[tempVbl] != '\0'){
                            tempAccount.cus_nic[tempVbl] = tempArray[tempVbl];
                            tempVbl++;
                        }

                        tempVbl = 0;
                        for(int i=0; i<30; i++){
                            tempArray [i] = '\0';
                        }
                        tempVal = 0;

                        break;

                    case '$' :
                        sscanf(tempArray, "%lf", &tempAccount.acc_bal);

                        for(int i=0; i<30; i++){
                            tempArray [i] = '\0';
                        }
                        tempVal = 0;

                        accounts [tempAccCount] = tempAccount;
                        tempAccCount++;

                        break;

                    default :
                        tempArray [tempVal] = tempChar;
                        tempVal++;
                }

            }

            *accountsCount = tempAccCount;

            *result = 1;
        }

		fclose(filePointer);

        printf("\n # Bank System Details has been Loaded Successfully. \n\n");

    }

}


void printMainMenu(){

    printf("\n\n Main Menu ");
    printf("\n ========= ");

    printf("\n Enter Number which Related to the Task You Want to Do > ");

    printf("\n\t 1 - Create Account. ");
    printf("\n\t 2 - Deposit Money. ");
    printf("\n\t 3 - Withdraw Money. ");
    printf("\n\t 4 - Search for an Account. ");
    printf("\n\t 5 - Show all Accounts. ");
    printf("\n\t 6 - Exit the Program. ");

}


char getMainMenuRes(){

    char res;

    clearIOStreams();
    printf("\n Enter Your Response : ");
    scanf(" %c", &res);

    return res;

}


void processMainMenuRes(char res, struct account accounts[ACCOUNTS_ARRAY_SIZE], int *accountsCount){

    switch(res){
        case '1' :
            createAccount(accounts, accountsCount);
            break;
        case '2' :
            depositMoney(accounts, accountsCount);
            break;
        case '3' :
            withdrawMoney(accounts, accountsCount);
            break;
        case '4' :
            searchForAnAccount(accounts, accountsCount);
            break;
        case '5' :
            showAllAccounts(accounts, accountsCount);
            break;
        case '6' :
            exitProgram(accounts, accountsCount);
            break;
        default :
            printErrorMsg(ERROR_CODE_3);
            printMainMenu();
            res = getMainMenuRes();
            processMainMenuRes(res, accounts, accountsCount);

    }

}


void createAccount(struct account accounts[ACCOUNTS_ARRAY_SIZE], int *accountsCount){

    struct account newAccount;

    char accNumberChars[ACC_NUM_SIZE];
    char accTypeChars[ACC_TYPE_SIZE];
    char cusNameChars[CUS_NAME_SIZE];
    char cusNICChars[CUS_NIC_SIZE];
    char moneyAmountChars[MON_AMOU_SIZE];

    int accNumber;
    char accType;
    char tempAccType;
    char cusName [CUS_NAME_SIZE];
    char cusNIC [CUS_NIC_SIZE];
    double moneyAmount;

    int isValid = 0;
    int isExist = 0;
    int tempCount = 0;

    for(int i=0; i<ACC_NUM_SIZE; i++){
        accNumberChars[i] = '\0';
    }

    for(int i=0; i<ACC_TYPE_SIZE; i++){
        accTypeChars[i] = '\0';
    }

    for(int i=0; i<CUS_NAME_SIZE; i++){
        cusNameChars[i] = '\0';
        cusName[i] = '\0';
        newAccount.cus_name[i] = '\0';
    }

    for(int i=0; i<CUS_NIC_SIZE; i++){
        cusNICChars[i] = '\0';
        cusNIC[i] = '\0';
        newAccount.cus_nic[i] = '\0';
    }

    for(int i=0; i<MON_AMOU_SIZE; i++){
        moneyAmountChars[i] = '\0';
    }

    printf("\n Please Input Following Details to Add New Account > ");

    clearIOStreams();
    printf("\n Enter Account Number : ");
    scanf("%s", accNumberChars);

    isValid = validateAccountNumber(accNumberChars);

    if(isValid){

        sscanf(accNumberChars, "%d", &accNumber);
        isValid = 0;

        for(int i=0; i<*accountsCount; i++){
            if(accounts[i].acc_num == accNumber){
                isExist = 1;
                break;
            }
        }

        if(!isExist){

            clearIOStreams();
            printf("\n Enter Account Type : ");
            scanf("%s", accTypeChars);

            tempAccType = accTypeChars[ACC_TYPE_SIZE-1];
            if((int)tempAccType > 96){
                accTypeChars[ACC_TYPE_SIZE-1] = (char)((int)tempAccType-32);
            }else{
                accTypeChars[ACC_TYPE_SIZE-1] = tempAccType;
            }

            isValid = validateAccountType(accTypeChars);

            if(isValid){

                accType = accTypeChars[ACC_TYPE_SIZE-1];
                isValid = 0;

                clearIOStreams();
                printf("\n Enter Customer Name : ");
                scanf("%[^\n]", cusNameChars);

                isValid = validateCustomerName(cusNameChars);

                if(isValid){

                    while(cusNameChars[tempCount] != '\0'){
                        cusName[tempCount] = cusNameChars[tempCount];
                        tempCount++;
                    }
                    tempCount = 0;
                    isValid = 0;

                    clearIOStreams();
                    printf("\n Enter Customer NIC : ");
                    scanf("%s", cusNICChars);

                    isValid = validateCustomerNIC(cusNICChars);

                    if(isValid){

                        while(cusNICChars[tempCount] != '\0'){
                            cusNIC[tempCount] = cusNICChars[tempCount];
                            tempCount++;
                        }
                        tempCount = 0;
                        isValid = 0;

                        clearIOStreams();
                        printf("\n Enter Start Money Amount : ");
                        scanf("%s", moneyAmountChars);

                        isValid = validateMoneyAmount(moneyAmountChars);

                        if(isValid){

                            sscanf(moneyAmountChars, "%lf", &moneyAmount);
                            isValid = 0;

                            isValid = validateMoneyLimit(accType, moneyAmount);

                            if(isValid){

                                newAccount.acc_num = accNumber;

                                newAccount.acc_type = accType;

                                while(cusName[tempCount] != '\0'){
                                    newAccount.cus_name[tempCount] = cusName[tempCount];
                                    tempCount++;
                                }
                                tempCount = 0;

                                while(cusNIC[tempCount] != '\0'){
                                    newAccount.cus_nic[tempCount] = cusNIC[tempCount];
                                    tempCount++;
                                }
                                tempCount = 0;

                                newAccount.acc_bal = moneyAmount;

                                accounts[*accountsCount] = newAccount;
                                *accountsCount = *accountsCount+1;

                                printf("\n -> New Account %d has been Saved Successfully. \n", accNumber);

                                rewriteAccDetails(accounts, accountsCount);

                            }else{
                                printErrorMsg(ERROR_CODE_11);
                            }

                        }else{
                            printErrorMsg(ERROR_CODE_10);
                        }

                    }else{
                        printErrorMsg(ERROR_CODE_9);
                    }

                }else{
                    printErrorMsg(ERROR_CODE_8);
                }

            }else{
                printErrorMsg(ERROR_CODE_7);
            }

        }else{
            printErrorMsg(ERROR_CODE_6);
        }

    }else{
        printErrorMsg(ERROR_CODE_4);
    }

    printMainMenu();
    char res = getMainMenuRes();
    processMainMenuRes(res, accounts, accountsCount);

}


void depositMoney(struct account accounts[ACCOUNTS_ARRAY_SIZE], int *accountsCount){

    struct account tempAccount;

    char accNumberChars[ACC_NUM_SIZE];
    char moneyAmountChars[MON_AMOU_SIZE];

    int accNumber;
    double moneyAmount;

    int isValid = 0;
    int isExist = 0;
    double tempBal = 0.00;
    int accCount = 0;

    for(int i=0; i<ACC_NUM_SIZE; i++){
        accNumberChars[i] = '\0';
    }

    for(int i=0; i<MON_AMOU_SIZE; i++){
        moneyAmountChars[i] = '\0';
    }

    clearIOStreams();
    printf("\n Enter Account Number : ");
    scanf("%s", accNumberChars);

    isValid = validateAccountNumber(accNumberChars);

    if(isValid){

        sscanf(accNumberChars, "%d", &accNumber);
        isValid = 0;

        for(int i=0; i<*accountsCount; i++){
            if(accounts[i].acc_num == accNumber){
                isExist = 1;
                tempAccount = accounts[i];
                break;
            }
            accCount++;
        }

        if(isExist){

            clearIOStreams();
            printf("\n Enter Money Amount : ");
            scanf("%s", moneyAmountChars);

            isValid = validateMoneyAmount(moneyAmountChars);

            if(isValid){

                sscanf(moneyAmountChars, "%lf", &moneyAmount);
                isValid = 0;

                tempBal = tempAccount.acc_bal+moneyAmount;

                isValid = validateMoneyLimit(tempAccount.acc_type, moneyAmount);

                if(isValid){

                    accounts[accCount].acc_bal = tempBal;

                    printf("\n -> Rs. %.2f has been Successfully Deposited to the Account %d. ", moneyAmount, accNumber);
                    printf("\n -> New Balance of Account %d is : %.2f \n", accNumber, tempBal);

                    rewriteAccDetails(accounts, accountsCount);

                }else{
                    printErrorMsg(ERROR_CODE_11);
                }

            }else{
                printErrorMsg(ERROR_CODE_10);
            }

        }else{
            printErrorMsg(ERROR_CODE_12);
        }

    }else{
        printErrorMsg(ERROR_CODE_4);
    }

    printMainMenu();
    char res = getMainMenuRes();
    processMainMenuRes(res, accounts, accountsCount);

}


void withdrawMoney(struct account accounts[ACCOUNTS_ARRAY_SIZE], int *accountsCount){

    struct account tempAccount;

    char accNumberChars[ACC_NUM_SIZE];
    char moneyAmountChars[MON_AMOU_SIZE];

    int accNumber;
    double moneyAmount;

    int isValid = 0;
    int isExist = 0;
    double tempBal = 0.00;
    int accCount = 0;

    for(int i=0; i<ACC_NUM_SIZE; i++){
        accNumberChars[i] = '\0';
    }

    for(int i=0; i<MON_AMOU_SIZE; i++){
        moneyAmountChars[i] = '\0';
    }

    clearIOStreams();
    printf("\n Enter Account Number : ");
    scanf("%s", accNumberChars);

    isValid = validateAccountNumber(accNumberChars);

    if(isValid){

        sscanf(accNumberChars, "%d", &accNumber);
        isValid = 0;

        for(int i=0; i<*accountsCount; i++){
            if(accounts[i].acc_num == accNumber){
                isExist = 1;
                tempAccount = accounts[i];
                break;
            }
            accCount++;
        }

        if(isExist){

            clearIOStreams();
            printf("\n Enter Money Amount : ");
            scanf("%s", moneyAmountChars);

            isValid = validateMoneyAmount(moneyAmountChars);

            if(isValid){

                sscanf(moneyAmountChars, "%lf", &moneyAmount);
                isValid = 0;

                tempBal = tempAccount.acc_bal-moneyAmount;

                isValid = validateMoneyLimit(tempAccount.acc_type, moneyAmount);

                if(isValid){

                    accounts[accCount].acc_bal = tempBal;

                    printf("\n -> Rs. %.2f has been Successfully withdrew from the Account %d. ", moneyAmount, accNumber);
                    printf("\n -> New Balance of Account %d is : %.2f \n", accNumber, tempBal);

                    rewriteAccDetails(accounts, accountsCount);

                }else{
                    printErrorMsg(ERROR_CODE_11);
                }

            }else{
                printErrorMsg(ERROR_CODE_10);
            }

        }else{
            printErrorMsg(ERROR_CODE_12);
        }

    }else{
        printErrorMsg(ERROR_CODE_4);
    }

    printMainMenu();
    char res = getMainMenuRes();
    processMainMenuRes(res, accounts, accountsCount);

}


void searchForAnAccount(struct account accounts[ACCOUNTS_ARRAY_SIZE], int *accountsCount){

    struct account acc;
    char accNumberChars[ACC_NUM_SIZE];
    int isExistAcc = 0;
    int isValid = 0;
    int accNumber = 0;

    printf("\n Enter Account Number to Display Account Details >");

    clearIOStreams();
    printf("\n Account Number : ");
    scanf("%s", accNumberChars);

    isValid = validateAccountNumber(accNumberChars);

    if(isValid){

        sscanf(accNumberChars, "%d", &accNumber);

        for(int i=0; i<*accountsCount; i++){
            if(accounts[i].acc_num==accNumber){
                isExistAcc = 1;
                acc = accounts[i];
                break;
            }
        }

        if(isExistAcc){

            printAccDetailsTableTop();

            printAccountDetailsRow(acc);

            printAccDetailsTableBottom();

        }else{
            printErrorMsg(ERROR_CODE_5);
        }

    }else{
        printErrorMsg(ERROR_CODE_4);
    }

    printMainMenu();
    char res = getMainMenuRes();
    processMainMenuRes(res, accounts, accountsCount);

}


void showAllAccounts(struct account accounts[ACCOUNTS_ARRAY_SIZE], int *accountsCount){

    struct account tempAccount;

    printAccDetailsTableTop();

    for(int i=0; i<*accountsCount; i++){
        tempAccount = accounts[i];

		printAccountDetailsRow(tempAccount);
    }

    printAccDetailsTableBottom();

    printMainMenu();
    char res = getMainMenuRes();
    processMainMenuRes(res, accounts, accountsCount);

}


void printAccDetailsTableTop(){

    printf("\n");

    printf("\n ----------------------------------------------------------------------------------------------- ");
    printf("\n |    Acc No    |  Acc Type  |             Name             |       NIC      |     Balance     | ");
    printf("\n ----------------------------------------------------------------------------------------------- ");
    printf("\n |              |            |                              |                |                 | ");

}


void printAccountDetailsRow(struct account tempAccount){

    int tempCount = 0;
    int tempVbl = 0;

    printf("\n ");
    printf("|    %d    ", tempAccount.acc_num);
    printf("|     %c      ", tempAccount.acc_type);

    while(tempAccount.cus_name[tempCount] != '\0'){
        tempCount++;
    }
    printf("|");
    tempVbl = (30-tempCount)/2;
    for(int i=0; i<tempVbl; i++){
        printf(" ");
    }
    for(int i=0; i<tempCount; i++){
        printf("%c", tempAccount.cus_name[i]);
    }
    tempVbl = (30-tempCount)-((30-tempCount)/2);
    for(int i=0; i<tempVbl; i++){
        printf(" ");
    }
    tempCount = 0;

    printf("|   ");
    for(int i=0; i<10; i++){
        printf("%c", tempAccount.cus_nic[i]);
    }
    printf("   ");

    printf("|");
    tempVbl = (int)tempAccount.acc_bal;
    while(tempVbl != 0){
        tempVbl /= 10;
        tempCount++;
    }
    tempCount = tempCount+3;
    tempVbl = (17-tempCount)/2;
    for(int i=0; i<tempVbl; i++){
        printf(" ");
    }
    printf("%.2f", tempAccount.acc_bal);
    tempVbl = (17-tempCount)-((17-tempCount)/2);
    for(int i=0; i<tempVbl; i++){
        printf(" ");
    }
    printf("|");

}


void printAccDetailsTableBottom(){

    printf("\n ----------------------------------------------------------------------------------------------- ");

    printf("\n\n");

}


int validateAccountNumber(char accNumberChars[ACC_NUM_SIZE]){

    int accNumber;
    int tempCount = 0;
    int tempVbl = 0;
    int isPositiveNumber = 1;
    int isHavePreferDigitCount = 0;

    while(accNumberChars[tempCount] != '\0'){
        if( (int)accNumberChars[tempCount]<48 || (int)accNumberChars[tempCount]>57){
            isPositiveNumber = 0;
            break;
        }
        tempCount++;
    }

    tempCount = 0;

    if(isPositiveNumber){
        sscanf(accNumberChars, "%d", &accNumber);
        tempVbl = accNumber;

        while(tempVbl != 0){
            tempVbl /= 10;
            tempCount++;
        }

        if(tempCount==ACC_NUM_SIZE){
            isHavePreferDigitCount = 1;
        }

    }

    if(isHavePreferDigitCount){
        return 1;
    }else{
        return 0;
    }

}


int validateAccountType(char accTypeChars[ACC_TYPE_SIZE]){

    if(
       accTypeChars[ACC_TYPE_SIZE-1] == NORMAL_ACC_TYPE ||
       accTypeChars[ACC_TYPE_SIZE-1] == EIGHTEEN_PLUS_ACC_TYPE ||
       accTypeChars[ACC_TYPE_SIZE-1] == RANKAKULU_ACC_TYPE ||
       accTypeChars[ACC_TYPE_SIZE-1] == WANITHA_ACC_TYPE
       ){
        return 1;
    }else{
        return 0;
    }

}


int validateCustomerName(char cusNameChars[CUS_NAME_SIZE]){

    int isValid = 1;
    int tempCount = 0;

    while(cusNameChars[tempCount] != '\0'){
        if( ((int)cusNameChars[tempCount]<65) ||
            ((int)cusNameChars[tempCount]>90 && (int)cusNameChars[tempCount]<97) ||
            ((int)cusNameChars[tempCount]>122) ){
                if((int)cusNameChars[tempCount] != 32 && (int)cusNameChars[tempCount] != 44 && (int)cusNameChars[tempCount] != 46){
                    isValid = 0;
                    break;
                }
        }
        tempCount++;
    }

    if(isValid && tempCount<CUS_NAME_SIZE+1){
        return 1;
    }else{
        return 0;
    }

}


int validateCustomerNIC(char cusNICChars[CUS_NIC_SIZE]){

    int isValid = 1;
    int isValidNIC = 0;
    int count = 0;

    while(cusNICChars[count] != '\0'){
        count++;
    }

    if(count==10){

        for(int i=0; i<CUS_NIC_SIZE-1; i++){
            if( (int)cusNICChars[i]<48 || (int)cusNICChars[i]>57){
                isValid = 0;
                break;
            }
        }

        if(isValid){
            if((int)cusNICChars[CUS_NIC_SIZE-1] == 86 || (int)cusNICChars[CUS_NIC_SIZE-1] == 118 ){
                isValidNIC = 1;
            }else{
                isValidNIC = 0;
            }
        }

    }

    if(isValidNIC){
        return 1;
    }else{
        return 0;
    }

}


int validateMoneyAmount(char moneyAmountChars[MON_AMOU_SIZE]){

    double moneyAmount;
    int isValid = 0;
    int tempCount = 0;
    int isPositiveNumber = 1;

    while(moneyAmountChars[tempCount] != '\0'){
        if((int)moneyAmountChars[tempCount] == 46){
            break;
        }
        if( (int)moneyAmountChars[tempCount]<48 || (int)moneyAmountChars[tempCount]>57){
            isPositiveNumber = 0;
            break;
        }
        tempCount++;
    }

    if(isPositiveNumber){

        sscanf(moneyAmountChars, "%lf", &moneyAmount);

        if(moneyAmount>0){
            isValid = 1;
        }

    }

    if(isValid){
        return 1;
    }else{
        return 0;
    }

}


int validateMoneyLimit(char accType, double moneyAmount){

    if(accType == NORMAL_ACC_TYPE){

        if(moneyAmount>=MIN_BALANCE_N){
            return 1;
        }else{
            return 0;
        }

    }else if(accType == EIGHTEEN_PLUS_ACC_TYPE){

        if(moneyAmount>=MIN_BALANCE_E){
            return 1;
        }else{
            return 0;
        }

    }else if(accType == RANKAKULU_ACC_TYPE){

        if(moneyAmount>=MIN_BALANCE_R){
            return 1;
        }else{
            return 0;
        }

    }else if(accType == WANITHA_ACC_TYPE){

        if(moneyAmount>=MIN_BALANCE_W){
            return 1;
        }else{
            return 0;
        }

    }else{
        return 0;
    }

}


void exitProgram(struct account accounts[ACCOUNTS_ARRAY_SIZE], int *accountsCount){

    rewriteAccDetails(accounts, accountsCount);

    printf("\n\n # Exiting Program... ");
    printf("\n # Program Terminated Successfully. \n\n");

}


void clearIOStreams(){

    fflush (stdin);
    //fflush (stdout);

}


void printErrorMsg(int ERROR_CODE_){

    if(ERROR_CODE_ == ERROR_CODE_1){
        printf ("\n\n *** Error in Loading Bank System Details. ");
        printf ("\n *** Please Re-Run this Program. \n\n");
    }else if(ERROR_CODE_ == ERROR_CODE_2){
        printf ("\n\n *** Error in Saving Bank System Details. ");
        printf ("\n *** All the Updated Account Details Will be Lost. \n\n");
    }else if(ERROR_CODE_ == ERROR_CODE_3){
        printf("\n *** There is Something Wrong With Your Main Menu Response. ");
        printf("\n *** Response Must be a Number which Between 1-5. \n");
    }else if(ERROR_CODE_ == ERROR_CODE_4){
        printf("\n *** ERROR - Account Number Should be Positive Integer Number With %d Digits. \n", ACC_NUM_SIZE);
    }else if(ERROR_CODE_ == ERROR_CODE_5){
        printf("\n *** Sorry, We Couldn't Find Such Like a Account. \n");
    }else if(ERROR_CODE_ == ERROR_CODE_6){
        printf("\n *** ERROR - Account Number You Entered has been Duplicated. ");
        printf("\n *** Enter New Account Number. \n");
    }else if(ERROR_CODE_ == ERROR_CODE_7){
        printf("\n *** ERROR - Account Type Should be a Character of 'N' or 'E' or 'R' or 'W'. \n");
    }else if(ERROR_CODE_ == ERROR_CODE_8){
        printf("\n *** ERROR - Customer Name Should only have Only Maximum %d Letters with '.' & ',' Characters & Spaces. \n", CUS_NAME_SIZE);
    }else if(ERROR_CODE_ == ERROR_CODE_9){
        printf("\n *** ERROR - Customer NIC should be in *********V format with %d Digits. \n", CUS_NIC_SIZE-1);
    }else if(ERROR_CODE_ == ERROR_CODE_10){
        printf("\n *** ERROR - Money Amount Should be a Positive Integer Number. \n");
    }else if(ERROR_CODE_ == ERROR_CODE_11){
        printf("\n *** ERROR - The Money Amount Process doesn't Reach Minimum Account Balance Limit. \n");
    }else if(ERROR_CODE_ == ERROR_CODE_12){
        printf("\n *** ERROR - Sorry, We Couldn't Find Such Like a Account. ");
        printf("\n *** Please Enter a Account Number Which Already Exist. \n");
    }

}


void rewriteAccDetails(struct account accounts[ACCOUNTS_ARRAY_SIZE], int *accountsCount){

    int tempVbl = 0;
    struct account tempAccount;

    FILE *filePointer;

    printf("\n\n # Re-Writing Bank System Details...");

    if ((filePointer = fopen (DirPath, "w")) == NULL) {
        printErrorMsg(ERROR_CODE_2);
    }else {
        fclose(filePointer);
        filePointer = fopen (DirPath, "a");

        for(int i=0; i<*accountsCount; i++){

            for(int i=0; i<CUS_NAME_SIZE; i++){
                tempAccount.cus_name[i] = '\0';
            }

            for(int i=0; i<CUS_NIC_SIZE; i++){
                tempAccount.cus_nic[i] = '\0';
            }

            tempAccount= accounts[i];

            fprintf(filePointer, "%d", tempAccount.acc_num);
            fprintf(filePointer, "%c", '`');
            //clearIOStreams();
            //fflush(filePointer);

            fprintf(filePointer, "%c", tempAccount.acc_type);
            fprintf(filePointer, "%c", '~');
            //clearIOStreams();
            //fflush(filePointer);

            while(tempAccount.cus_name[tempVbl] != '\0'){
                fprintf(filePointer, "%c", tempAccount.cus_name[tempVbl]);
                tempVbl++;
            }
            tempVbl = 0;
            fprintf(filePointer, "%c", '#');
            //clearIOStreams();
            //fflush(filePointer);

            while(tempAccount.cus_nic[tempVbl] != '\0'){
                fprintf(filePointer, "%c", tempAccount.cus_nic[tempVbl]);
                tempVbl++;
            }
            tempVbl = 0;
            fprintf(filePointer, "%c", '^');
            //clearIOStreams();
            //fflush(filePointer);

            fprintf(filePointer, "%lf", tempAccount.acc_bal);
            fprintf(filePointer, "%c", '$');
            //clearIOStreams();
            //fflush(filePointer);

        }

        fclose(filePointer);

        printf("\n # Bank System Details has been Saved Successfully. \n");

    }

}
