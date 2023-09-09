# Phonebook_Management_with_Hashtable

## Main aim of program is to compare the time performance of template-based Hash Table and BST.

This program implements a phonebook management system using Binary Search Tree (BST) and Hash Table data structures. It provides functionalities for searching, adding, and deleting contacts, as well as comparing the performance of these two data structures. The program is template-based to allow flexibility in contact information storage.

## Functionality
The program offers the following functionalities:

**Search Contact:** Search for a contact by entering a full name (e.g., "John Doe"). The program displays contacts matching the full name.

**Add Contact:** Add a new contact to both the BST and the Hash Table. Contacts are compared alphabetically by full name (first name + last name). If the contact already exists, a warning message is displayed.

**Delete Contact:** Remove a contact from the phonebook by providing the full contact name (e.g., "Alice Smith").

**Performance Comparison:** Compare the performance of BST and Hash Table data structures by performing the same search operation 500 times and calculating the average timing. Display the speedup ratio of these timing values compared to each other.

## Input Data
The program reads contact information from an input file (e.g., "PhoneBook-sample2.txt"). Each line of the input file represents a contact and includes first name, last name, phone number, and city information.

## Execution Flow
Here's how the program works:

**Load Input File:** The program reads contact information from the specified input file and creates a BST and a Hash Table with the data. It measures and displays the time taken for tree creation and hash table initialization.

**Rehashing Information:** While processing the input file, the program prints information about the Hash Table every time rehashing occurs. This information includes the previous capacity, previous load, current capacity, current load, and the number of items in the Hash Table.

**Menu:** After loading the phonebook, the program displays a menu of functionalities for the user to choose from.

**Function Execution:** When a user selects a function (1 to 3), the program executes that function for both the BST and the Hash Table. It measures and displays the execution time for each operation.

**Performance Comparison:** To compare the performance of BST and Hash Table, the program performs the same search operation 500 times, measures the time taken for each data structure, calculates the average timing, and displays the speedup ratio.

**Exit:** After executing a function or completing the performance comparison, the program allows the user to exit the program.

<br>

⚠️ This project was developed as a programming assignment and serves as an educational resource for working with sparse matrices and linked lists.
