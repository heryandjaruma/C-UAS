#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

// PRE PROCESSOR
#define TRUE 1
#define QUOTA 15
#define PRICE 5000

//Regular text
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define WHT "\e[0;37m"

//Regular underline text
#define UYEL "\e[4;33m"
#define UBLU "\e[4;34m"
#define UMAG "\e[4;35m"
#define UCYN "\e[4;36m"

//Bold high intensity text
#define BHYEL "\e[1;93m"

//Reset
#define CRESET "\e[0m"

// clear screen
void cls(){
   system("cls");
}

// press enter to continue
void cont()
{
    printf("Press enter to continue . . .");
    getchar();
}

// show animation for loading bar
void loading_bar(int len, int time, char *message)
{
	char a = 177, b = 219;
	printf("\n[%s]\n", message);
    int i = 0;
	for (i = 0; i < len; i++)
		printf("%c", a);

	printf("\r");

    time *= 10;
	for (i = 0; i < len; i++) {
		printf("%c", b);
		Sleep(time);
	}
    puts("");
}

int sorted = 0;

// to return string value of a "member" and "non-member" from parameter
const char *getMember(int member)
{
    if (member == 0) return "Non-member";
    if (member == 1) return "Member";
    else return "Invalid!";
}

// to return string of jenis pakaian
const char *getKind(int kind)
{
    if (kind == 0) return "Formal";
    else if (kind == 1) return "Non-formal";
    else if (kind == 2) return "Pants";
    else return "Invalid!";
}

// to return besar diskon
float getDiscount(int member)
{
    if (member == 0) return 0;
    else return 0.1;    
}

// title
void header()
{
    cls();
    puts(BHYEL"    __                          __          ");
    puts("   / /   ____ ___  ______  ____/ /______  __");
    puts("  / /   / __ `/ / / / __ \\/ __  / ___/ / / /");
    puts(" / /___/ /_/ / /_/ / / / / /_/ / /  / /_/ / ");
    puts("/_____/\\__,_/\\__,_/_/ /_/\\__,_/_/   \\__, /  ");
    puts("          ______          _        /____/   ");
    puts("         / ____/__  _____(_)___ _       ");
    puts("        / /   / _ \\/ ___/ / __ `/          ");
    puts("       / /   / _ \\/ ___/ / __ `/       ");
    puts("      / /___/  __/ /  / / /_/ /  ");
    puts("      \\____/\\___/_/  /_/\\__,_/     \n");
    puts("============================================="WHT);
}








//////////////////////////////
// DOUBLE LINKED LIST BELOW //
//////////////////////////////

////////////// CUSTOMER LINKED LIST //////////////
struct Customer
{
    // Self
    char name[21];
    char phone[14];
    int member; // 0 -> not a member
                // 1 -> a member

    // Date Registered
    int date, month, year;

    // require for linked list
    struct Customer *next, *prev;
}*custHead = NULL, *custTail = NULL;

struct Customer *createNewCustomer(char *name, char *phone, int member, int date, int month, int year)
{
    struct Customer *newNode = (struct Customer *)malloc(sizeof(struct Customer));

    strcpy(newNode->name, name);
    strcpy(newNode->phone, phone);
    newNode->member = member;
    newNode->date = date;
    newNode->month = month;
    newNode->year = year;

    newNode->next = newNode->prev = NULL;

    return newNode;
}

// To push customer into database
void pushCustomer(char *name, char *phone, int member, int date, int month, int year)
{
    struct Customer *newNode = createNewCustomer(name, phone, member, date, month, year);
    sorted = 0;
    if (custTail == NULL)
    {
        custHead = custTail = newNode;
        return;
    }
    else
    {
        custTail->next = newNode;
        newNode->prev = custTail;
        custTail = newNode;
        return;
    }
}

// to return a Customer node with given name and phone
struct Customer *getCustomer(char *name, char *phone)
{
    struct Customer *curr = custHead;
    while (curr)
    {
        if (strcmp(curr->name, name) == 0 && strcmp(curr->phone, phone) == 0)
        {
            return curr;
        }
    }
}

// read customer from file
void read_customer()
{
    char name[21];
    char phone[14];
    int member;
    int date, month, year;
    FILE * fp = fopen("customer.txt", "r");
    if (fp ==  NULL)
    {
        printf("File 'Customer.txt' not found!\n");
        return;
    }
    while (!feof(fp))
    {
        fscanf(fp, "%[^#]#%[^#]#%d#%d#%d#%d\n", name, phone, &member, &date, &month, &year);
        // printf("%s#%s#%d#%d#%d#%d\n", name, phone, member, date, month, year);
        pushCustomer(name, phone, member, date, month, year);
    }
    fclose(fp);
}

// write into file customer database
void write_customer()
{
    FILE * fp = fopen("customer.txt", "w");
    struct Customer *curr = custHead;
    if (fp ==  NULL)
    {
        printf("File 'Customer.txt' not found!\n");
        return;
    }
    
    while (curr)
    {
        fprintf(fp, "%s#%s#%d#%d#%d#%d\n", curr->name, curr->phone, curr->member, curr->date, curr->month, curr->year);
        curr = curr->next;
    }
    fclose(fp);
}

// to display a customer
void display_a_customer(struct Customer *curr)
{
    puts(WHT"+-----------------------------------------+");
    puts("|          CUSTOMER INFORMATION           |");
    puts("+-----------------------------------------+");
    printf("| %-15s : %-21s |\n", "Name", curr->name);
    printf("| %-15s : %-21s |\n", "Phone",  curr->phone);
    if (curr->member == 1) printf("| %-15s : "YEL"%-21s"WHT" |\n", "Member", getMember( curr->member)); // if member, give yellow color
    else printf("| %-15s : %-21s |\n", "Member", getMember( curr->member)); // if not member, give white color
    printf("| %-15s : %02d %02d %-04d %-10s |\n", "Date Registered",  curr->date,  curr->month,  curr->year, "");
    puts("+-----------------------------------------+\n");
}
///////////////////////////////////////////////////////
///////////////////////////////////////////////////////


////////////// ORDER QUEUE //////////////
struct Order
{
    char name[21];
    char phone[14];
    int member;
    float weight;
    int kind;
    
    int queue_num;
    int date, month, year;

    struct Order *next, *prev;
}*orderHead = NULL, *orderTail = NULL, *headDatabase = NULL, *tailDatabase = NULL;

struct Order *createNewOrder(char *name, char *phone, int member, float weight, int kind, int queue_num, int date, int month, int year)
{
    struct Order *newNode = (struct Order *)malloc(sizeof(struct Order));

    strcpy(newNode->name, name);
    strcpy(newNode->phone, phone);
    newNode->member = member;
    newNode->weight = weight;
    newNode->kind = kind;
    newNode->queue_num = queue_num;
    newNode->date = date;
    newNode->month = month;
    newNode->year = year;

    newNode->next = newNode->prev = NULL;

    return newNode;
}

// To push order into database
void pushOrder(char *name, char *phone, int member, int weight, int kind, int queue_num, int date, int month, int year)
{
    struct Order *newNode = createNewOrder(name, phone, member, weight, kind, queue_num, date, month, year);
    if (orderTail == NULL)
    {
        orderHead = orderTail = newNode;
        return;
    }
    else
    {
        orderTail->next = newNode;
        newNode->prev = orderTail;
        orderTail = newNode;
        return;
    }
}

// to display an order
void display_a_order(struct Order *curr)
{
    puts(WHT"+-----------------------------------------+");
    puts("|            ORDER INFORMATION            |");
    puts("+-----------------------------------------+");
    printf("| %-15s : %-21s |\n", "Name", curr->name);
    printf("| %-15s : %-21s |\n", "Phone",  curr->phone);
    if (curr->member == 1) printf("| %-15s : "YEL"%-21s"WHT" |\n", "Member", getMember( curr->member));
    else printf("| %-15s : %-21s |\n", "Member", getMember( curr->member));
    printf("| %-15s : %-21.2f |\n", "Weight (Kg)",  curr->weight);
    printf("| %-15s : %-21s | \n", "Kind", getKind( curr->kind));
    printf("| %-15s : %-21d |\n", "Queue Number",  curr->queue_num);
    printf("| %-15s : %02d %02d %-04d %-10s |\n", "Date Inputted",  curr->date,  curr->month,  curr->year, "");
    puts("+-----------------------------------------+\n");
}

// read order from file
void read_order()
{
    char name[21];
    char phone[14];
    int member;
    float weight;
    int kind;
    int queue_num;
    int date, month, year;
    FILE * fp = fopen("order.txt", "r");
    if (fp ==  NULL)
    {
        printf("File 'order.txt' not found!\n");
        return;
    }
    while (!feof(fp))
    {
        fscanf(fp,"%[^#]#%[^#]#%d#%f#%d#%d#%d#%d#%d\n", name, phone, &member, &weight, &kind, &queue_num, &date, &month, &year);
        // printf("%s#%s#%d#%f#%d#%d#%d#%d#%d\n", name, phone, member, weight, kind, queue_num, date, month, year);
        pushOrder(name, phone, member, weight, kind, queue_num, date, month, year);
    }
    fclose(fp);
}

// write order from file
void write_order()
{
    FILE * fp = fopen("order.txt", "w");
    struct Order *curr = orderHead;
    if (fp ==  NULL)
    {
        printf("File 'order.txt' not found!\n");
        return;
    }
    while (curr)
    {
        fprintf(fp, "%s#%s#%d#%f#%d#%d#%d#%d#%d\n", curr->name, curr->phone, curr->member, curr->weight, curr->kind, curr->queue_num, curr->date, curr->month, curr->year);
        curr = curr->next;
    }
    fclose(fp);
}

// pop an order
void pop()
{
    if (orderHead != NULL)
    {
        struct Order *curr = orderHead;
        if (orderHead == orderTail)
        {
            curr->next = curr->prev = orderHead = orderTail = NULL;
            free(curr);
        }
        else
        {
            orderHead = orderHead->next;
            curr->next = curr->prev = NULL;
            free(curr);
        }
    } else return;
}

// to show all order in the queue
void show_all_order()
{
    struct Order *curr = orderHead;
    header();
    while (curr)
    {
        display_a_order(curr);
        curr = curr->next;
    }
    cont();
}

// to return a string based on order status
const char *getStatusOrder(int stats)
{
    if (stats == 0) return "Not-taken";
    else if (stats == 1) return "Taken";
    else return "Invalid!";
}

// get number of people in the line
int get_total_in_line()
{
    return orderTail->queue_num - orderHead->queue_num;
}

// get price from member and weight
float getPrice(int member, float weight)
{
    return (PRICE * weight) - (PRICE * weight)*getDiscount(member);
}
///////////////////////////////////////////////////////
///////////////////////////////////////////////////////


////////////// HISTORY QUEUE //////////////
struct History
{
    char name[21];
    char phone[14];
    int member;
    float weight;
    int kind;
    
    int status;

    // date of issue
    int date, month, year;

    // date taken
    int takedate, takemonth, takeyear;
    struct History *next, *prev;
}*historyHead = NULL, *historyTail = NULL;

struct History *createNewHistory(char *name, char *phone, int member, float weight, int kind, int status, int date, int month, int year, int takedate, int takemonth, int takeyear)
{
    struct History *newNode = (struct History *)malloc(sizeof(struct History));

    strcpy(newNode->name, name);
    strcpy(newNode->phone, phone);
    newNode->member = member;
    newNode->weight = weight;
    newNode->kind = kind;
    newNode->status = status;
    newNode->date = date;
    newNode->month = month;
    newNode->year = year;
    newNode->takedate = takedate;
    newNode->takemonth = takemonth;
    newNode->takeyear = takeyear;


    newNode->next = newNode->prev = NULL;

    return newNode;
}

// to push history into database
void pushHistory(char *name, char *phone, int member, float weight, int kind, int status, int date, int month, int year, int takedate, int takemonth, int takeyear)
{
    struct History *newNode = createNewHistory(name, phone, member, weight, kind, status, date, month, year, takedate, takemonth, takeyear);
    if (historyHead == NULL)
    {
        historyHead = historyTail = newNode;
        return;
    }
    else
    {
        historyTail->next = newNode;
        newNode->prev = historyTail;
        historyTail = newNode;
        return;
    }
}

// to display a history
void display_a_history(struct History *curr)
{
    puts(WHT"+-----------------------------------------+");
    puts("|           HISTORY INFORMATION           |");
    puts("+-----------------------------------------+");
    printf("| %-15s : %-21s |\n", "Name", curr->name);
    printf("| %-15s : %-21s |\n", "Phone",  curr->phone);
    if (curr->member == 1) printf("| %-15s : "YEL"%-21s"WHT" |\n", "Member", getMember( curr->member));
    else printf("| %-15s : %-21s |\n", "Member", getMember( curr->member));
    printf("| %-15s : %-21.2f |\n", "Weight (Kg)",  curr->weight);
    printf("| %-15s : %-21s | \n", "Kind", getKind( curr->kind));
    printf("| %-15s : %-21.2f |\n", "Percentage", getDiscount(curr->member));
    printf("| %-15s : %-21.2f |\n", "Total Price", getPrice(curr->member, curr->weight));
    printf("| %-15s : %02d %02d %-04d %-10s |\n", "Date of Issue",  curr->date, curr->month, curr->year, "");
    puts(WHT"+-----------------------------------------+");
    if (curr->status == 0)
    {
        printf("| %-15s : "RED"%-21s"WHT" |\n", "Status", getStatusOrder(curr->status));
        printf("| %-15s : %-21s |\n", "Date Taken",  "-");
    }
    else
    {
        printf("| %-15s : "BLU"%-21s"WHT" |\n", "Status", getStatusOrder(curr->status));
        printf("| %-15s : %02d %02d %-04d %-10s |\n", "Date Taken",  curr->takedate, curr->takemonth, curr->takeyear, "");
    }
    
    puts("+-----------------------------------------+\n");
}

// read history from a file
void read_history()
{
    char name[21];
    char phone[14];
    int member;
    float weight;
    int kind;
    
    int status;

    // date of issue
    int date, month, year;

    // date taken
    int takedate, takemonth, takeyear;
    FILE * fp = fopen("history.txt", "r");
    if (fp ==  NULL)
    {
        printf("File 'history.txt' not found!\n");
        return;
    }
    while (!feof(fp))
    {
        fscanf(fp, "%[^#]#%[^#]#%d#%f#%d#%d#%d#%d#%d#%d#%d#%d\n", name, phone, &member, &weight, &kind, &status, &date, &month, &year, &takedate, &takemonth, &takeyear);
        // printf("%s#%s#%d#%f#%d#%d#%d#%d#%d#%d#%d#%d\n", name, phone, member, weight, kind, status, date, month, year, takedate, takemonth, takeyear);
        pushHistory(name, phone, member, weight, kind, status, date, month, year, takedate, takemonth, takeyear);
    }
    fclose(fp);
}

// write history from a file
void write_history()
{
    struct History *curr = historyHead;
    FILE * fp = fopen("history.txt", "w");
    if (fp ==  NULL)
    {
        printf("File 'history.txt' not found!\n");
        return;
    }
    while (curr)
    {
        fprintf(fp, "%s#%s#%d#%f#%d#%d#%d#%d#%d#%d#%d#%d\n", curr->name, curr->phone, curr->member, curr->weight, curr->kind, curr->status, curr->date, curr->month, curr->year, curr->takedate, curr->takemonth, curr->takeyear);
        curr = curr->next;
    }
    fclose(fp);
}
///////////////////////////////////////////////////////
///////////////////////////////////////////////////////










/////////////////////
// OTHER FUNCTIONS //
/////////////////////

// Swap value of given node
void swapData(struct Customer * first, struct Customer * second)
{
    // date 
	int date = first->date;
	first->date = second->date;
	second->date = date;
    // member
	int member = first->member;
	first->member = second->member;
	second->member = member;
    // month
	int month = first->month;
	first->month = second->month;
	second->month = month;
    // year
	int year = first->year;
	first->year = second->year;
	second->year = year;
    // name
    char name[21];
    strcpy(name, first->name);
    strcpy(first->name, second->name);
    strcpy(second->name, name);
    // phone
    char phone[21];
    strcpy(phone, first->phone);
    strcpy(first->phone, second->phone);
    strcpy(second->phone, phone);
}

// Perform bubble sort for customer
void bubble_sort_customer()
{
	int task = 1;
	// Get first node
	struct Customer * start = custHead;
	while (task == 1)
	{
		task = 0;
		while (start != NULL && start->next != NULL)
		{
			if ((strcmpi(start->name, start->next->name) > 0))
			{
				swapData(start, start->next);
				// Active the next iteration
				task = 1;
			}
			// Visit to next node
			start = start->next;
		}
		// Get first node
		start = custHead;
	}
}

// to get an estimation for order to done
int getEstimationDone()
{
    return (get_total_in_line() / QUOTA) + 1;
}

// menu to input an order
void input_order()
{
    char name[21];
    char phone[14];
    int member;
    float weight;
    int kind;
    int queue_num;
    int date, month, year;

    do
    {
        header();
        printf(WHT"%-35s : "CYN,"Input customer name [4-20 chars]");
        gets(name);
    } while (strlen(name) > 20 || strlen(name) < 4);
    do
    {
        header();
        printf(WHT"%-35s : "CYN,"Input customer phone [11-13 nums]");
        gets(phone);
    } while (strlen(phone) < 0 || strlen(phone) > 13);
    do
    {
        header();
        puts(WHT"Is this customer a member?");
        puts("1 - Yes");
        puts("0 - No");
        printf(CYN"\n>> ");
        scanf("%d", &member); getchar();
    } while (member < 0 || member > 1);
    do
    {
        header();
        printf(WHT"%-35s : "CYN,"Weight of the laundry [max. 25]");
        scanf("%f", &weight); getchar();
    } while (weight < 1 || weight > 25);
    do
    {
        header();
        puts(WHT"Kind of Laundry?");
        puts("0 - Formal");
        puts("1 - Non-formal");
        puts("2 - Pants");
        printf(CYN"\n>> ");
        scanf("%d", &kind); getchar();
    } while (kind < 0 || kind > 2);
    do
    {
        header();
        printf(WHT"%-35s : "CYN,"Current date [dd/mm/yyyy]");
        scanf("%d %d %d", &date, &month, &year); getchar();
    } while (date < 1 || date > 31 || month < 1 || month > 12);

    // set up the queue number from the last node of queue
    queue_num = orderTail->queue_num + 1;

    header();
    puts(GRN"Successfully added an order!\n"WHT);
    printf("Order estimated to be done in "UBLU"%d"WHT" day(s).\n\n"WHT, getEstimationDone());
    cont();
    

    // Push to main linked list
    pushOrder(name, phone, member, weight, kind, queue_num, date, month, year);
    write_order();
    // Push to database linked list
    int flaggy = 0;
    struct Customer *curr = custHead;
    puts("iam here");
    while (curr)
    {
        if (strcmpi(curr->name, name) == 0 && strcmpi(curr->phone, phone) == 0)
        {
            flaggy = 1;
            break;
        }
        curr = curr->next;
    }
    
    if (flaggy == 0)
    {
        pushCustomer(name, phone, member, date, month, year);
        write_customer();
    }   
}

// menu to show all customer database
void show_all_database()
{
    header();
    struct Customer *curr = custHead;
    if (curr != NULL)
    {
        int choose = -1;
        while (TRUE)
        {
            do
            {
                curr = custHead;
                header();
                while (curr)
                {
                    display_a_customer(curr);
                    curr = curr->next;
                }
                puts("1 - Search by Name");
                puts("2 - Show member(s) only");
                puts("3 - Sort names [A-Z]");
                puts("0 - Back to main menu");
                if (sorted == 1)
                {
                    printf(CYN"\n\t\t\tData already sorted *\n"WHT);
                } else printf(CYN"\n\t\t\tData is not sorted *\n"WHT);
                printf(CYN"\n>> ");
                scanf("%d", &choose); getchar();
            } while (choose < 0 || choose > 3);

            if (choose == 0)
            {
                return;
            }
            else if (choose == 1)
            {
                char name[21];
                int flag = 0, total = 0;
                do
                {
                    curr = custHead;
                    header();
                    printf(WHT"%-35s : "CYN,"Search a name");
                    gets(name);
                    puts(WHT);

                    // Search in Database
                    header();
                    while (curr)
                    {
                        if(strcmpi(curr->name, name) == 0)
                        {
                            display_a_customer(curr);
                            flag = 1;
                            total++;
                        }
                        curr = curr->next;
                    }
                    // If not found, ask again
                    if (flag == 0)
                    {
                        header();
                        printf(WHT"Couldn't find a data with the name "UCYN"%s"WHT".\n", name);
                        puts(YEL"Perhaps, a typo?\n"WHT);
                        do
                        {
                            puts("1 - Yes, search for another name");
                            puts("0 - No, back to showing all customers database");
                            printf(CYN"\n>> ");
                            scanf("%d", &choose); getchar();
                        } while (choose < 0 || choose > 1);
                        if (choose == 0) break;
                        else continue;
                    } else {
                        printf("Found "UCYN"%d"WHT" data(s) with the name "UCYN"%s"WHT".\n", total, name);
                        cont();
                        break;
                    }
                } while (TRUE); 
            }
            // show members only
            else if (choose == 2)
            {
                int count_member = 0;
                header();
                curr = custHead;
                while (curr)
                {
                    if (curr->member == 1)
                    {
                        display_a_customer(curr);
                        count_member++;
                    }
                    curr = curr->next;
                }
                printf("Showing "UCYN"%d"WHT" laundry member(s).\n", count_member);
                cont();
            }
            // sort A-Z
            else if (choose == 3)
            {
                sorted = 1;
                bubble_sort_customer();
            }
        }
    }
    else
    {
        puts("Nothing to share here!\n");
    }
    cont();
}

// menu to show all history
void show_all_history(){
    header();
    struct History *curr = historyHead;
    if (curr != NULL)
    {
        while (curr)
        {
            display_a_history(curr);
            curr = curr->next;
        }
    }
    else
    {
        puts("Nothing to show here!\n");
    }
    cont();
}

// menu to finsih an order
void remove_order(struct Order *head)
{
    float baseprice;
    int choose;
    do
    {
        header();
        display_a_order(head);
        puts(WHT"+-----------------------------------------+");
        puts("|            BILL INFORMATION             |");
        puts("+-----------------------------------------+");
        baseprice = (head->weight) * PRICE;
        printf("| %-15s : %-21.2f |\n", "Base Price", baseprice);
        printf("| %-15s : %-21.2f |\n", "Discount", getDiscount(head->member));
        printf("| %-15s : %-21.2f |\n", "Total", getPrice(head->member, head->weight));
        puts("+-----------------------------------------+\n");
        puts(RED"Finish the order?"WHT);
        puts("1 - Yes, finish the order");
        puts("0 - No, back to main menu");
        printf(CYN"\n>> ");
        scanf("%d", &choose); getchar();
    } while (choose < 0 || choose > 1);

    if (choose == 0) return;
    else
    {           
        pushHistory(head->name, head->phone, head->member, head->weight, head->kind, 0, head->date, head->month, head->year,-1,-1,-1);
        write_history();
        pop();
        // update remove order
        write_order();
    }

    // receipt here
    do
    {
        header();
        puts(WHT"Print out the receipt?");
        puts("1 - Yes, print out the receipt");
        puts("0 - No, back to main menu");
        printf(CYN"\n>> ");
        scanf("%d", &choose); getchar();
    } while (choose < 0 || choose > 1);
    if (choose == 0) return;
    else
    {
       loading_bar(30, 3, "Printing out the receipt...");
    }
    puts(GRN"\nReceipt succesfully printed! Please collect it at the front office."WHT);
    cont();
    return;
}

// to authenticate an admin
int authenticate_admin(char *uname, char *pass)
{
    char uname_f[21], pass_f[21];
    FILE * flog = fopen("admin_creds.txt", "r");
    if (flog ==  NULL)
    {
        printf("File 'admin_creds.txt' not found!\n");
        return -1;
    }
    while (!feof(flog))
    {
        fscanf(flog, "%[^#]#%[^\n]\n", uname_f, pass_f);
        if (strcmp(uname, uname_f) == 0 && strcmp(pass, pass_f) == 0)
        {
            fclose(flog);
            return 1;
        }
    }
    fclose(flog);
    return -1;
}

// to authenticate an user
int authenticate_user(char *uname, char *pass)
{
    char uname_f[21], pass_f[21], dummy[21];
    FILE * flog = fopen("customer.txt", "r");
    if (flog ==  NULL)
    {
        printf("File 'customer.txt' not found!\n");
        return -1;
    }
    while (!feof(flog))
    {
        fscanf(flog, "%[^#]#%[^#]#%[^#]#%[^#]#%[^#]#%[^\n]\n", uname_f, pass_f, dummy, dummy, dummy, dummy);
        if (strcmpi(uname, uname_f) == 0 && strcmp(pass, pass_f) == 0)
        {
            fclose(flog);
            return 1;
        }
    }
    fclose(flog);
    return -1;
}

// nested main function
void main_drive()
{
    int choose = -1;
    do
    {
        header();
        puts(MAG"Welcome, "UMAG"Admin"MAG"!\n"WHT);
        printf("We have currently "UYEL"%d"WHT" order(s)!\n\n", get_total_in_line() + 1);
        puts("1 - Input An Order");
        puts("2 - Show All Orders");
        puts("3 - Finish An Order From The Queue");
        puts("4 - View Customers Database");
        puts("5 - Order History");
        puts("0 - Logout");
        printf(CYN"\n>> ");
        scanf("%d", &choose); getchar();
        puts(WHT);
        if (choose == 1)
        {
            input_order();
        }
        else if (choose == 2)
        {
            show_all_order();
        }
        
        else if (choose == 3)
        {
            remove_order(orderHead);
        }
        else if (choose == 4)
        {

            show_all_database();
        }
        else if (choose == 5)
        {
            show_all_history();
        }
        else continue;
    } while (choose != 0);
}

// return number of total order
int get_total_order_from_a_cust(char *name, char *phone)
{
    int count = 0;
    struct Order *curr = orderHead;
    while (curr)
    {
        if (strcmpi(name, curr->name) == 0 && strcmpi(phone, curr->phone) == 0)
        {
            count++;
        }
        curr = curr->next;
    }
    return count;
}

// return number of total history
int get_total_history_from_a_cust(char *name, char *phone)
{
    int count = 0;
    struct History *curr = historyHead;
    while (curr)
    {
        if (curr->status == 0)
        {
            count++;
        }
    }
    return count;
}

// menu to search a customer's order
void search_cust_order(char *name, char *phone)
{
    int flag = 0;
    struct Order *curr = orderHead;
    while (curr)
    {
        if (strcmpi(name, curr->name) == 0 && strcmpi(phone, curr->phone) == 0)
        {
            flag = 1;
            display_a_order(curr);
        }
        curr = curr->next;
    }

    if (flag == 0)
    {
        if (get_total_order_from_a_cust(name, phone) == 0)
        {
            puts(RED"You don't have any order left.");
            puts(WHT"Place your new order at the front office!\n");  
        }
        else
        {
            puts(CYN"Your order(s) is done.");
            puts("Please take it on the 'Take My Order' menu!\n"WHT);
        }
    }
    else if (flag == 1)
    {
        puts(RED"Your order(s) above still in laundry process!\n"WHT); 
    }
    return;
}

// menu to take a customer's order
int take_cust_history(char *name, char *phone)
{
    int flag = 0;
    struct History *curr = historyHead;
    while (curr)
    {
        if (strcmpi(name, curr->name) == 0 && strcmpi(phone, curr->phone) == 0 && curr->status == 0)
        {
            flag = 1;
            display_a_history(curr);
        }
        curr = curr->next;
    }
    if (flag == 1)
    {
        int date, month, year;
        do
        {
            printf(WHT"%-35s : "CYN,"Input current date [dd/mm/yyyy]");
            scanf("%d %d %d", &date, &month, &year); getchar();
        } while (date < 1 || date > 31 || month < 1 || month > 12);
        curr = historyHead;
        while (curr)
        {
            if (strcmpi(name, curr->name) == 0 && strcmpi(phone, curr->phone) == 0)
            {
                curr->status = 1;
                curr->takedate = date;
                curr->takemonth = month;
                curr->takeyear = year;
            }
            curr = curr->next;
        }

        puts(GRN"\nYou're ready!");
        puts("Please, take your order(s) at the front office.\n");
        puts(WHT"Thank your for trusting our service at "UYEL"LAUNDRY CERIA"WHT"!\n");
        write_history();
        cont();
        return 1;
    }
    else if (flag == 0)
    {
        if (get_total_order_from_a_cust(name, phone) == 0)
        {
            puts(RED"You don't have any order left.");
            puts(WHT"Place your new order at the front office!\n");  
        }
        else
        {
            puts(RED"Your order(s) still in laundry process!\nCheck out 'Check My Laundry Order' For Details.\n"); 
            puts(WHT"Please, check your order(s) on 'Check My Laundry Order'");
        }
        cont();
        return 0;
    }
    else return -1;
}

// main menu for user
void main_drive_user(char *name, char *phone)
{
    int choose = -1;
    do
    {
        header();
        printf(MAG"Welcome, "UMAG"%s"MAG"!\n\n"WHT, name);
        printf("You still have "UCYN"%d"WHT" laundry order(s) in process!\n",get_total_order_from_a_cust(name, phone));
        puts(WHT"\n1 - Order Progress");
        puts("2 - Take My Order");
        puts("0 - Logout");
        printf(CYN"\n>> ");
        scanf("%d", &choose); getchar();
        if (choose == 1)
        {
            header();
            search_cust_order(name, phone);
            cont();   
        }
        else if (choose == 2)
        {
            header();
            take_cust_history(name, phone);
        }
        else continue;
    } while (choose != 0);
}

// main function
int main(){
    system("color 0A");

    // PRE-PUSHED DATA
    read_customer();
    read_order();
    read_history();
    
    loading_bar(31, 5, "Setting Up The Application...");
    puts(WHT);

    char uname[21], pass[21];
    while (TRUE)
    {
        header();
        puts(BHYEL"                    LOGIN");
        puts("============================================="WHT);
        printf(WHT"\tUsername : "CYN);
        gets(uname);
        printf(WHT"\tPhone    : "CYN);
        gets(pass);

        if (strcmpi(uname, "shutdown") == 0 && strcmpi(pass, "shutdown") == 0) break;
        int login = authenticate_admin(uname, pass);
        if (login == 1) main_drive();
        else {
            login = authenticate_user(uname, pass);
            if (login == -1)
            {
                puts(RED"\nFailed to authenticate!"WHT);
                cont();
            }
            else main_drive_user(uname, pass);
        }
    }

    write_customer();
    write_order();
    write_history();

    header();
    loading_bar(32, 3, RED"Shutting Down..."WHT);
    cls();
    puts(CRESET);
    return 0;
}