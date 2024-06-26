# Banking System
Banking System is a university project for the Object Oriented Programming practical course. 
This application is designed to manage a simple banking system, allowing for user management, account handling, and task management for employees.

## Features
* User Management: Create and manage clients and employees.
* Account Management: Open, close, and view bank accounts.
* Task Management: Employees can view, approve, and disapprove tasks.
* Security: Password protection for user accounts.

## Roles
* Client: Manages their accounts and sends requests to the banks.
* Employee: Completes tasks given by the bank they work for.
* Third-party employee: Sends checks to clients of a particular bank.

## Instructions
### Basic commands
- **Create a Bank**:
    ```
    create_bank <bank name>
    ```

- **Signup a Client**:
    ```
    signup <name> <egn> <age> <role = Client> <password>
    ```

- **Signup an Employee**:
    ```
    signup <name> <egn> <age> <role = Employee> <password> <bank name>
    ```
    
- **Signup an Third-party employee**:
    ```
    signup <name> <egn> <age> <role = Third-part> <password>
    ```
    
- **Login** - log in your account:
    ```
    login <name> <password>
    ```

- **Exit** - logout or close the application:
    ```
    exit
    ```

- **Help** - provides all the instructions and commands for the particular user:
    ```
    help
    ```

- **Who am I** - identifies the user:
    ```
    whoami
    ```

## License

[MIT](https://choosealicense.com/licenses/mit/)
