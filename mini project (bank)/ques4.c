#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure definition for Bank Account
struct Account {
    int accNumber;
    char name[50];
    float balance;
};

const char *BANK_FILE = "bank.dat";

// --- Function Prototypes ---
void createAccount(); 
void depositAmount();
void withdrawAmount();
void balanceEnquiry();

int main() {
    int choice;
    while (1) {
        printf("\n=== Welcome to C-Bank Banking System ===\n");
        // Updated Menu List
        printf("1. Create New Account\n");
        printf("2. Deposit Amount\n");
        printf("3. Withdraw Amount\n");
        printf("4. Balance Enquiry\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // Updated Switch Cases based on new menu numbering
        switch (choice) {
            case 1: createAccount(); break;
            case 2: depositAmount(); break;
            case 3: withdrawAmount(); break;
            case 4: balanceEnquiry(); break;
            case 5: 
                printf("Thank you for banking with us. Goodbye!\n"); 
                exit(0);
            default: printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}

// --- Function Definitions ---

// Function to create a new account and add it to the file
void createAccount() {
    struct Account acc;
    FILE *fp = fopen(BANK_FILE, "ab"); // Append binary mode
    if (fp == NULL) { printf("Error opening file storage.\n"); return; }

    printf("\n--- New Account Creation ---\n");
    
    // 1. Get Account Number
    printf("Enter unique Account Number: ");
    scanf("%d", &acc.accNumber);
    
    // Clear input buffer to prevent fgets issues
    while(getchar() != '\n'); 

    // 2. Get Acount Holder Name
    printf("Enter Account Holder Name: ");
    fgets(acc.name, sizeof(acc.name), stdin);
    // Remove trailing newline inserted by fgets
    acc.name[strcspn(acc.name, "\n")] = 0; 
    
    // 3. Get Initial Deposit (ensuring non-negative)
    do {
        printf("Enter Initial Deposit Amount ($0.00 or more): $");
        scanf("%f", &acc.balance);
        if (acc.balance < 0) {
            printf("Error: Initial balance cannot be negative. Try again.\n");
        }
    } while (acc.balance < 0);

    // 4. Write to file
    fwrite(&acc, sizeof(struct Account), 1, fp);
    printf("\nSuccess: Account [%d] created for [%s] with balance: $%.2f\n", 
           acc.accNumber, acc.name, acc.balance);
    
    fclose(fp);
}

void depositAmount() {
    struct Account acc;
    int searchAccNum, found = 0;
    float amount;
    // Open in read/write binary mode to update records in place
    FILE *fp = fopen(BANK_FILE, "rb+"); 

    if (fp == NULL) { printf("\nError: System unavailable or no accounts exist yet.\n"); return; }

    printf("\nEnter Account Number for deposit: ");
    scanf("%d", &searchAccNum);

    while (fread(&acc, sizeof(struct Account), 1, fp)) {
        if (acc.accNumber == searchAccNum) {
            printf("Account found: %s\n", acc.name);
            printf("Current Balance: $%.2f\n", acc.balance);
            
            printf("Enter amount to deposit: $");
            scanf("%f", &amount);

            if (amount > 0) {
                acc.balance += amount;
                // Move file pointer back one record size from current position
                fseek(fp, -sizeof(struct Account), SEEK_CUR);
                // Overwrite the existing record with new balance data
                fwrite(&acc, sizeof(struct Account), 1, fp);
                printf("\nDeposit successful! New Balance: $%.2f\n", acc.balance);
            } else {
                printf("Invalid amount. Must be greater than 0.\n");
            }
            found = 1;
            break;
        }
    }
    if (!found) printf("\nError: Account Number %d not found.\n", searchAccNum);
    fclose(fp);
}

void withdrawAmount() {
    struct Account acc;
    int searchAccNum, found = 0;
    float amount;
    FILE *fp = fopen(BANK_FILE, "rb+");

    if (fp == NULL) { printf("\nError: System unavailable or no accounts exist yet.\n"); return; }

    printf("\nEnter Account Number for withdrawal: ");
    scanf("%d", &searchAccNum);

    while (fread(&acc, sizeof(struct Account), 1, fp)) {
        if (acc.accNumber == searchAccNum) {
            printf("Account found: %s\n", acc.name);
            printf("Available Balance: $%.2f\n", acc.balance);
            
            printf("Enter amount to withdraw: $");
            scanf("%f", &amount);

            if (amount > 0 && acc.balance >= amount) {
                acc.balance -= amount;
                // Move pointer back and update record
                fseek(fp, -sizeof(struct Account), SEEK_CUR);
                fwrite(&acc, sizeof(struct Account), 1, fp);
                printf("\nWithdrawal successful! Remaining Balance: $%.2f\n", acc.balance);
            } else if (amount <= 0) {
                printf("Invalid amount. Must be greater than 0.\n");
            } else {
                printf("\nError: Insufficient funds for this withdrawal.\n");
            }
            found = 1;
            break;
        }
    }
    if (!found) printf("\nError: Account Number %d not found.\n", searchAccNum);
    fclose(fp);
}

void balanceEnquiry() {
    struct Account acc;
    int searchAccNum, found = 0;
    FILE *fp = fopen(BANK_FILE, "rb"); // Read only mode suffices here

    if (fp == NULL) { printf("\nError: System unavailable or no accounts exist yet.\n"); return; }

    printf("\nEnter Account Number to check balance: ");
    scanf("%d", &searchAccNum);

    while (fread(&acc, sizeof(struct Account), 1, fp)) {
        if (acc.accNumber == searchAccNum) {
            printf("\n--- Account Summary ---\n");
            printf("Account Number : %d\n", acc.accNumber);
            printf("Account Holder : %s\n", acc.name);
            printf("Current Balance: $%.2f\n", acc.balance);
            printf("-----------------------\n");
            found = 1;
            break;
        }
    }
    if (!found) printf("\nError: Account Number %d not found.\n", searchAccNum);
    fclose(fp);
}
