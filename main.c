#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


#define MAX_SIZE_USER_NAME 30
#define MAX_SIZE_PASSWORD  20
#define FILE_NAME  "Supermarket.bin"

#define MAX_ITEM_NAME   50

#define FILE_HEADER_SIZE  sizeof(sFileHeader)

// Struct for login credentials
typedef struct
{
    char username[MAX_SIZE_USER_NAME];
    char password[MAX_SIZE_PASSWORD];
} sFileHeader;
typedef struct // to call in program
{
    unsigned int item_id; // declare the integer data type
    char item_name[MAX_ITEM_NAME];// declare the character data type
    double amount;
    double price;

} s_itemInfo;

// This function prints the message in the middle of the head massage.
void printMessageCenter(const char* message)
{
    int len =0;
    int pos = 0;
    //calculate how many space need to print
    len = (78 - strlen(message))/2;
    printf("\t\t\t");
    for(pos =0 ; pos < len ; pos++)
    {
        //print space
        printf(" ");
    }
    //print message
    printf("%s",message);
}
// It prints the message on the top of the console and prints the message for specific operation.
void headMessage(const char *message)
{
    system("cls");
    printf("\t\t\t###########################################################################");
    printf("\n\t\t\t############                                                   ############");
    printf("\n\t\t\t############      Supermarket management System Project in C   ############");
    printf("\n\t\t\t############                                                   ############");
    printf("\n\t\t\t###########################################################################");
    printf("\n\t\t\t---------------------------------------------------------------------------\n");
    printMessageCenter(message);
    printf("\n\t\t\t----------------------------------------------------------------------------");
}
// This function displays the first welcomes screen of the "SUPER Management System" and asks the user to press any key to access the application.
void welcomeMessage()
{
    headMessage("Zagazig University");
    printf("\n\n\n\n\n");
    printf("\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t\t\t        =                 WELCOME                   =");
    printf("\n\t\t\t        =                   TO                      =");
    printf("\n\t\t\t        =                 SUPERMARKET               =");
    printf("\n\t\t\t        =               MANAGEMENT                  =");
    printf("\n\t\t\t        =                 SYSTEM                    =");
    printf("\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("\n\n\n\t\t\t Enter any key to continue.....");
    getch();
}
// It validates the user name, item name ..etc. I have permitted this function to take the space in names.
int isNameValid(const char *name)
{
    int validName = 1;
    int len = 0;
    int index = 0;
    len = strlen(name);
    for(index =0; index <len ; ++index)
    {
        if(!(isalpha(name[index])) && (name[index] != '\n') && (name[index] != ' '))
        {
            validName = 0;
            break;
        }
    }
    return validName;
}
// This function searches the database by item id.
int searchByID(unsigned int itemId){
    int found = 0;
    s_itemInfo addItemInfoinDB = {0};
    FILE *fp = NULL;
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("\n\t\t\tFile is not opened\n");
        exit(1);
    }
    if (fseek(fp,FILE_HEADER_SIZE,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("\n\t\t\tFacing issue while reading file\n");
        exit(1);
    }

    while (fread (&addItemInfoinDB, sizeof(addItemInfoinDB), 1, fp))
    {
        if(addItemInfoinDB.item_id == itemId)
        {
            found = 1;
            break;
        }
    }

    return found;

}
// This function opens the binary file in append mode and writes the item and the details.
void add_item()
{
    int days;
    s_itemInfo addItemInfo = {0};
    FILE *fp = NULL;
    int status = 0;
    fp = fopen(FILE_NAME,"ab+");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    headMessage("ADD NEW ITEMS");
    printf("\n\n\t\t\tENTER YOUR DETAILS BELOW:");
    printf("\n\t\t\t---------------------------------------------------------------------------\n");
    printf("\n\t\t\tItem ID NO  = ");
    fflush(stdin);
    scanf("%u",&addItemInfo.item_id);
    if (searchByID(addItemInfo.item_id)){
            printf("\n\t\t\tItem is already added!!");

    } else {
    do
    {
        printf("\n\t\t\tItem Name  = ");
        fflush(stdin);
        fgets(addItemInfo.item_name, MAX_ITEM_NAME, stdin);
        status = isNameValid(addItemInfo.item_name);
        if (!status)
        {
            printf("\n\t\t\tName contain invalid character. Please enter again.");
        }
    }
    while(!status);
    printf("\n\t\t\tEnter Item Amount  = ");
    fflush(stdin);
    scanf("%lf",&addItemInfo.amount);
    printf("\n\t\t\tEnter Item Price  = ");
    fflush(stdin);
    scanf("%lf",&addItemInfo.price);
    fwrite(&addItemInfo, sizeof(addItemInfo), 1, fp);
    fclose(fp);
    printf("\n\t\t\t------- Item has been added successfully -------");
    }
    printf("\n\t\t\tEnter any key to continue....");
    getch();
}
/*
This function opens the binary file in reading mode and asks the user to enter the item name which wants to search.
If the item is not available in the list, it shows the message item not find in records.
*/
void search_items()
{
    int found = 0;
    char item_name[MAX_ITEM_NAME] = {0};
    s_itemInfo addItemInfoinDB = {0};
    FILE *fp = NULL;
    int status = 0;
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("\n\t\t\tFile is not opened\n");
        exit(1);
    }
    headMessage("SEARCH ITEMS");
    if (fseek(fp,FILE_HEADER_SIZE,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("\n\t\t\tFacing issue while reading file\n");
        exit(1);
    }
    printf("\n\n\t\t\tEnter Item Name to search:");
    fflush(stdin);
    fgets(item_name, MAX_ITEM_NAME, stdin);
    while (fread (&addItemInfoinDB, sizeof(addItemInfoinDB), 1, fp))
    {
        if(!strcmp(addItemInfoinDB.item_name, item_name))
        {
            found = 1;
            break;
        }
    }
    if(found)
    {
        printf("\n\t\t\tItem id = %u\n", addItemInfoinDB.item_id);
        printf("\t\t\tItem name = %s", addItemInfoinDB.item_name);
        printf("\t\t\tItem amount = %lf", addItemInfoinDB.amount);
        printf("\t\t\tItem price = %lf", addItemInfoinDB.price);
    }
    else
    {
        printf("\n\t\t\tNo Record");
    }
    fclose(fp);
    printf("\n\n\n\t\t\tPress any key to go to main menu.....");
    getch();
}
/*
It opens the file in reading mode and read and display all the stored items details.
If there is no item available in the records, then it displays the message record is empty.
*/
void view_items()
{
    int found = 0;
    char item_name[MAX_ITEM_NAME] = {0};
    s_itemInfo addItemInfoinDB = {0};
    FILE *fp = NULL;
    int status = 0;
    headMessage("VIEW ITEMS DETAILS");
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    if (fseek(fp,FILE_HEADER_SIZE,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("Facing issue while reading file\n");
        exit(1);
    }

    printf("\n\n\nItem ID\t\t\tItem Amount\t\t\tItem Price\t\t\tItem Name\n");

    while (fread (&addItemInfoinDB, sizeof(addItemInfoinDB), 1, fp))
    {
        printf("%u\t\t\t%lf\t\t\t%lf\t\t\t%s\n", addItemInfoinDB.item_id, addItemInfoinDB.amount, addItemInfoinDB.price, addItemInfoinDB.item_name);
        found = 1;
    }
    fclose(fp);
    if(!found)
    {
        printf("\n\t\t\tNo Record");
    }
    printf("\n\n\t\t\tPress any key to go to main menu.....");
    fflush(stdin);
    getch();
}
// This function access the items by id and get its price to complete the payment.
void payItems(){
    int found = 0;
    char item_name[MAX_ITEM_NAME] = {0};
    s_itemInfo addItemInfoinDB = {0};
    FILE *fp = NULL;
    int status = 0;
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("\n\t\t\tFile is not opened\n");
        exit(1);
    }
    headMessage("PAY ITEMS");
    if (fseek(fp,FILE_HEADER_SIZE,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("\n\t\t\tFacing issue while reading file\n");
        exit(1);
    }
    unsigned int itemid = 0;
    char another = 'Y';
    while (another == 'y' || another == 'Y'){
    printf("\n\n\t\t\tEnter Item ID to pay:");
    fflush(stdin);
    scanf("%u", &itemid);
    while (fread (&addItemInfoinDB, sizeof(addItemInfoinDB), 1, fp))
    {
        if(addItemInfoinDB.item_id == itemid)
        {
            found = 1;
            break;
        }
    }
    if(found)
    {
            printf("\n\t\t\tPlease Enter The needed amount: ");
            double am = 1;
            scanf("%lf", &am);
            printf("\n\t\t\tItem name: %s\n", addItemInfoinDB.item_name);
            printf("\n\t\t\tItem price: %lf\n", (addItemInfoinDB.price) * am);
    }
    else
    {
        printf("\n\t\t\tNo Record\n");
    }

        printf("\n\t\t\tPay another Item?(Y/N)");
        fflush(stdin);
        another=getchar();
    }

    fclose(fp);
    printf("\n\n\n\t\t\tPress any key to go to main menu.....");
    getch();

}
/*
This function asks the item name from the user for the item want to delete.
In this function, I am creating a temporary binary file and copy all the data from the existing file except the item whose item name entered by the user.
In the last renamed the temporary bin file with an existing binary file.
*/
void delete_items()
{
    int found = 0;
    sFileHeader fileHeaderInfo = {0};
    char item_name[MAX_ITEM_NAME] = {0};
    s_itemInfo addItemInfoinDB = {0};
    FILE *fp = NULL;
    FILE *tmpFp = NULL;
    int status = 0;
    headMessage("Delete Items Details");
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    tmpFp = fopen("tmp.bin","wb");
    if(tmpFp == NULL)
    {
        fclose(fp);
        printf("File is not opened\n");
        exit(1);
    }
    fread (&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
    fwrite(&fileHeaderInfo,FILE_HEADER_SIZE, 1, tmpFp);
    printf("\n\t\t\tEnter Item Name for delete:");
    fflush(stdin);
    fgets(item_name, MAX_ITEM_NAME, stdin);
    while (fread (&addItemInfoinDB, sizeof(addItemInfoinDB), 1, fp))
    {
        if(strcmp(addItemInfoinDB.item_name, item_name))
        {
            fwrite(&addItemInfoinDB, sizeof(addItemInfoinDB), 1, tmpFp);
        }
        else
        {
            found = 1;
        }
    }
    (found)? printf("\n\t\t\tRecord deleted successfully....."):printf("\n\t\t\tRecord not found");
    fclose(fp);
    fclose(tmpFp);
    remove(FILE_NAME);
    rename("tmp.bin",FILE_NAME);
}
/*
This function update the info for the item. the user should enter the item name to access its data and change it.
*/
void update_itemInfo(){
    int status = 0;
    int found = 0;
    sFileHeader fileHeaderInfo = {0};
    char item_name[MAX_ITEM_NAME] = {0};
    s_itemInfo addItemInfo = {0};
    FILE *fp = NULL;
    headMessage("Update Items Details");
    fp = fopen(FILE_NAME,"rb+");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    fread (&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
    printf("\n\t\t\tEnter Item Name for update: ");
    fflush(stdin);
    fgets(item_name, MAX_ITEM_NAME, stdin);
    while (fread (&addItemInfo, sizeof(addItemInfo), 1, fp))
    {
        if(!strcmp(addItemInfo.item_name, item_name))
        {
            fflush(stdin);
            printf("\n\t\t\tThe item is available\n");
            found = 1;
            printf("\n\t\t\tEnter new item id: ");
            fflush(stdin);
            scanf("%u",&addItemInfo.item_id);

            do{
            printf("\n\t\t\tEnter new Item name: ");
            fflush(stdin);
            fgets(addItemInfo.item_name, MAX_ITEM_NAME, stdin);
            status = isNameValid(addItemInfo.item_name);
            if (!status)
            {
                printf("\n\t\t\tName contain invalid character. Please enter again.");
            }
            }while(!status);

            printf("\n\t\t\tEnter new Item Amount  = ");
            fflush(stdin);
            scanf("%lf",&addItemInfo.amount);
            printf("\n\t\t\tEnter new Item Price  = ");
            fflush(stdin);
            scanf("%lf",&addItemInfo.price);
            fseek(fp,ftell(fp)-sizeof(addItemInfo),0);
            fwrite(&addItemInfo, sizeof(addItemInfo), 1, fp);
            printf("\n\t\t\t------- Item has been updated successfully -------\n\n");
            break;
        }
    }
    fclose(fp);
    if (!found){
        printf("\n\t\t\tThe record is not available!!");
    }
    printf("\n\t\t\tEnter any key to continue....");
    getch();

}
/*
This function opens the file in rb+ mode (reading and writing).
It asks the user for the new username and password.
After taking the password and username it closes the application.
Now user can use the application with a new password and username.
*/
void update_loginInfo(void)
{
    sFileHeader fileHeaderInfo = {0};
    FILE *fp = NULL;
    unsigned char userName[MAX_SIZE_USER_NAME] = {0};
    unsigned char password[MAX_SIZE_PASSWORD] = {0};
    headMessage("Update Credential");
    fp = fopen(FILE_NAME,"rb+");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    fread (&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
    if (fseek(fp,0,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("\n\t\t\tFacing issue while updating password\n");
        exit(1);
    }
    printf("\n\n\t\t\tNew Username:");
    fflush(stdin);
    fgets(userName,MAX_SIZE_USER_NAME,stdin);
    printf("\n\n\t\t\tNew Password:");
    fflush(stdin);
    fgets(password,MAX_SIZE_PASSWORD,stdin);
    strncpy(fileHeaderInfo.username,userName,sizeof(userName));
    strncpy(fileHeaderInfo.password,password,sizeof(password));
    fwrite(&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
    fclose(fp);
    printf("\n\t\t\tYour Password has been changed successfully");
    printf("\n\t\t\tLogin Again:");
    fflush(stdin);
    getch();
    exit(1);
}
// This function displays the application menu and asks the user to select the option. If the user selects 0, then the application will close.

void menu()
{
    int choice = 0;
    do
    {
        headMessage("MAIN MENU");
        printf("\n\n\n\t\t\t1.Add Items");
        printf("\n\t\t\t2.Search Items");
        printf("\n\t\t\t3.View Items");
        printf("\n\t\t\t4.Pay for shopper");
        printf("\n\t\t\t5.Delete Items");
        printf("\n\t\t\t6.Update Items Info");
        printf("\n\t\t\t7.Update Password");
        printf("\n\t\t\t0.Exit");
        printf("\n\n\n\t\t\tEnter choice => ");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                add_item();
                break;
            case 2:
                search_items();
                break;

            case 3:
                view_items();
                break;
            case 4:
                payItems();
                break;
            case 5:
                delete_items();
                break;
            case 6:
                update_itemInfo();
                break;
            case 7:
                update_loginInfo();
                break;
            case 0:
                printf("\n\n\n\t\t\t\tThank you!!!\n\n\n\n\n");
                exit(1);
                break;
            default:
                printf("\n\n\n\t\t\tINVALID INPUT!!! Try again...");
        }                                            //Switch Ended
    }
    while(choice!=0);                                        //Loop Ended
}
//login password
void login()
{
    unsigned char userName[MAX_SIZE_USER_NAME] = {0};
    unsigned char password[MAX_SIZE_PASSWORD] = {0};
    int L=0;
    sFileHeader fileHeaderInfo = {0};
    FILE *fp = NULL;
    headMessage("Login");
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    fread (&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
    fclose(fp);
    do
    {
        printf("\n\n\n\t\t\t\tUsername:");
        fgets(userName,MAX_SIZE_USER_NAME,stdin);
        printf("\n\t\t\t\tPassword:");
        fgets(password,MAX_SIZE_PASSWORD,stdin);
        if((!strcmp(userName,fileHeaderInfo.username)) && (!strcmp(password,fileHeaderInfo.password)))
        {
            menu();
        }
        else
        {
            printf("\t\t\t\tLogin Failed Enter Again Username & Password\n\n");
            L++;
        }
    }
    while(L<=3);
    if(L>3)
    {
        headMessage("Login Failed");
        printf("\t\t\t\tSorry,Unknown User.");
        getch();
        system("cls");
    }
}
// This function verifies that a file has been created or not. If the file exists, the function return 1 otherwise returns 0.
int isFileExists(const char *path)
{
    // Try to open file
    FILE *fp = fopen(path, "rb");
    int status = 0;
    // If file does not exists
    if (fp != NULL)
    {
        status = 1;
        // File exists hence close file
        fclose(fp);
    }
    return status;
}
// This function creates the file if not exist and copies the default password ("admin") in file header structure.
void init()
{
    FILE *fp = NULL;
    int status = 0;
    const char defaultUsername[] ="admin\n";
    const char defaultPassword[] ="admin\n";
    sFileHeader fileHeaderInfo = {0};
    status = isFileExists(FILE_NAME);
    if(!status)
    {
        //create the binary file
        fp = fopen(FILE_NAME,"wb");
        if(fp != NULL)
        {
            //Copy default password
            strncpy(fileHeaderInfo.password,defaultPassword,sizeof(defaultPassword));
            strncpy(fileHeaderInfo.username,defaultUsername,sizeof(defaultUsername));
            fwrite(&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
            fclose(fp);
        }
    }
}
int main()
{
    init();
    welcomeMessage();
    login();
    return 0;
}
