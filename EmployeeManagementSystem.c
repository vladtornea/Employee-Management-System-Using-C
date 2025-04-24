//Employee Management System
//By: Vlad Tornea

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Define Structure to Hold Elements
typedef struct {
    char Name[100]; //Employee name 
    int EmployeeID; //Employee ID
    float salary;   //Employee salary 
    char department[50];  //department of employee 
    int YearsofExpereince; //employe years of experience
    float PerformanceScore;  //Performance score 
} Employee; 

//Define variables outside of main 
Employee *employees = NULL; 
int EmployeeCount = 0; 

//Functions:

void addEmployee(){
    employees = realloc(employees, (EmployeeCount + 1)*sizeof(Employee));  //memory allocation for employee
    if (employees == NULL){
        printf("Failed to allocate memory for employee!\n");    //exit if memory allocation failed and inform user 
        exit(1); 
    }
    Employee *NewEmployee = &((employees)[EmployeeCount]); 
    getchar(); 
    printf("Enter name of employee:\n");
    fgets(NewEmployee->Name, sizeof(NewEmployee->Name), stdin); 
    NewEmployee->Name[strcspn(NewEmployee->Name, "\n")] = '\0'; //to delete new line

    printf("Enter Employee ID: ");                 //to enter employee ID
    scanf("%d", &(NewEmployee->EmployeeID)); 
    getchar(); 

    printf("Enter salary: "); 
    scanf("%f", &(NewEmployee->salary)); //enter salary of employee 
    getchar(); 

    printf("Enter department: "); 
    fgets(NewEmployee->department, 50, stdin);  //enter employye department 
    NewEmployee->department[strcspn(NewEmployee->department, "\n")] = '\0'; 

    printf("Enter years of experience: "); 
    scanf("%d", &(NewEmployee->YearsofExpereince));  //enter years of experience 
    getchar(); 

    NewEmployee->PerformanceScore = (0.3 * NewEmployee->YearsofExpereince) + (0.7 * NewEmployee->salary / 1000); //calculate performance score 

    printf("Employee has been successfully added to the system!\n"); 

    (EmployeeCount++); //increase employee counter by 1 
}

void updateEmployee(){  //function to update employee information 
    int ID; 
    int foundEmployees = 0; 

    printf("Enter Employee ID do update: "); 
    scanf("%d", &ID); 
    getchar(); 

    for(int i = 0; i < EmployeeCount; i++){               //for loop to loop through employees to look for matching id 
        if (employees[i].EmployeeID == ID){
            printf("Enter new salaray: "); 
            scanf("%f", &(employees[i].salary)); 
            getchar(); 

            printf("Enter new department: ");
            fgets(employees[i].department, sizeof(employees[i].department), stdin); 
            employees[i].department[strcspn(employees[i].department, "\n")] = '\0'; 

            employees[i].PerformanceScore = (0.3 * employees[i].YearsofExpereince) + (0.7 * employees[i].salary / 1000); //update perfromance

            printf("Employee information updated successfully!\n"); 
            foundEmployees = 1; 
            break;
        }
    }

    if (foundEmployees == 0){
        printf("Employee with ID %d not found. \n", ID); 
    }
    
}

void sortEmployeesByPerformance(){     //to sort employees by performance score in ascending order 
    for(int i = 0; i < EmployeeCount - 1; i++){
        for (int j = 0; j<EmployeeCount - i - 1; j++)
        {
            if (employees[j].PerformanceScore < employees[j + 1].PerformanceScore){
                Employee temp = employees[j]; 
                employees[j] = employees[j+1];
                employees[j+1] = temp; 
            }
        }
        
    }
}

void displayEmployees(){      //function to display all employees and info in ascending order 
    if (EmployeeCount == 0){ 
        printf("No employees in system to display.\n"); 
        return;
    }
    sortEmployeesByPerformance(); //calls to sortEmployeesByPerformance function to sort employees by performance first before displaying. 
    printf("\n");
    printf("Employee Reords (sorted by Performance Score):\n"); 
    
    for (int i = 0; i < EmployeeCount; i++){  //for loop to loop through and access all employees in system 
        printf("\n"); 
        printf("Name: %s\n", employees[i].Name); 
        printf("Employee ID: %d\n", employees[i].EmployeeID); 
        printf("Salary: %.2f\n", employees[i].salary); 
        printf("Department: %s\n", employees[i].department); 
        printf("Years of Experience: %d\n", employees[i].YearsofExpereince); 
        printf("Performance Score: %.2f\n", employees[i].PerformanceScore); 
    }
}

void searchEmployeeByName(){    //function to search employees by name 
    char nameSearched[100]; 
    int foundEmployees = 0; 

    if(EmployeeCount == 0){
        printf("No employees in system to search.\n");
        return; 
    }
    getchar();
    printf("Enter name to search: "); 
    fgets(nameSearched, 100, stdin); 
    nameSearched[strcspn(nameSearched, "\n")] = '\0'; 

    sortEmployeesByPerformance(); //call sortEmployeesByPerformance function to sort employees by performance first 
    printf("\nSearch Results:\n"); 
    for (int i = 0; i<EmployeeCount; i++){
        if (strstr(employees[i].Name, nameSearched) != NULL){
            printf("\n"); 
            printf("Name: %s\n", employees[i].Name); 
            printf("Employee ID: %d\n", employees[i].EmployeeID); 
            printf("Salary: %.2f\n", employees[i].salary); 
            printf("Department: %s\n", employees[i].department); 
            printf("Years of Experience: %d\n", employees[i].YearsofExpereince); 
            printf("Performance Score: %.2f\n", employees[i].PerformanceScore); 
            foundEmployees = 1; 
        }
    }

    if(foundEmployees == 0){
        printf("No employees found to match \"%s\". \n", nameSearched); 
    }

}

int main()    //main 
{
    int chosenNumber; 

    while(1)
    {
        printf("\nEmployee Performance Management System\n");  //menu messages to prin to user 
        printf("1. Add Employee\n"); 
        printf("2. Update Employee\n"); 
        printf("3. Display All Employees\n");
        printf("4. Search Employee by Name\n"); 
        printf("5. Exit\n");
        printf("Enter your choice: "); 
        scanf("%d", &chosenNumber); 

        if(chosenNumber == 1){       //user choices and function to call based on user choice 
            addEmployee(); 
        }
        else if(chosenNumber == 2){
            updateEmployee();
        }
        else if(chosenNumber == 3){
            displayEmployees(); 
        }
        else if(chosenNumber == 4){
            searchEmployeeByName(); 
        }
        else if(chosenNumber == 5){
            printf("Exiting..."); 
            free(employees);     //free memory before exiting 
            return 0; 
        }
        else{
            printf("Invalid Choice. Please try again.\n"); 
        }
    }
    
}


