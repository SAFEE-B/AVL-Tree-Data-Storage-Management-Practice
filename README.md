Project Overview
This project implements a Database Management System (DBMS) designed to store and manage data of players and the games they play, using an in-memory Binary Search Tree (BST) structure. The program supports functionalities like inserting, searching, deleting, and displaying data in a structured, optimized manner, making it ideal for handling a large volume of data dynamically.

The code follows the requirements of the FAST NUCES CS218 Data Structures Assignment #03. Every aspect of the program has been designed to meet specified requirements, with considerations for scalability, efficiency, and ease of future modification.

Features
1. Data Storage
Dataset Loading: The program loads player and game data from CSV files into memory using Binary Search Trees (BSTs).
Skipping Lines: Based on a unique seed generated from the user’s roll number, lines are randomly skipped when reading player data. This process uses a random variable to select a line based on the condition given in the requirements.
2. Insertion
Player and Game Insertion: Supports the insertion of players and games into their respective BSTs. Each insertion is checked to ensure primary key uniqueness, avoiding duplicates.
Conflict Resolution: If an entry with the same primary key already exists, an error message is displayed.
3. Search and Retrieval
Primary Key Search: Enables searching for players or games based on their primary key.
Node Retrieval: The retrieved node is returned to the user for further actions such as viewing or modification.
4. Deletion
Memory-Safe Deletion: Allows safe deletion of players or games by their primary key, ensuring there are no memory leaks.
5. Save Data
Preorder Traversal: Data is saved to a CSV file using a Preorder traversal, maintaining the structure of the tree for easy restoration.
File Persistence: This allows for the same tree structure to be loaded if the program is restarted, preserving the data hierarchy.
6. Show N Layers
Layered Display: Displays all entries up to a specified number of layers. If the number of layers specified exceeds the tree depth, a warning message is displayed.
7. Show Layer Number
Node Layer Display: Given a primary key, the program returns the layer number (depth) of the corresponding node in the tree.
8. Show Path
Preorder Path Display: Displays the Preorder traversal path taken to find a specific entry, showing each node visited in the search.
9. Edit Entry
Modifiable Entries: Allows editing of player or game entries, including primary keys. After modification, the node is repositioned in the tree if necessary to maintain BST properties.
10. Top N Players
Top Players by Game Count: Identifies and displays the top N players who have played the most games, using efficient traversal and counting techniques.
11. Show Details
Player Details with Games: Allows viewing a player’s details, including all games they have played. This includes game-specific details like hours played and achievements.
12. Has Played
Efficient Game Check: Verifies if a player has played a specific game, with a target time complexity of 2 log(n), meeting the requirement for efficient searching.

