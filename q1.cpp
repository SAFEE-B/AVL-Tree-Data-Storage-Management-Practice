#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib> 
using namespace std;

const int specialNumber = 400;

class GameNode {
public:
    string Game_ID;
    string name;
    string developer;
    string publisher;
    float gameSize;
    int downloads;
    int height;
    GameNode* left;
    GameNode* right;

    GameNode() : left(nullptr), right(nullptr) {
        height=-1;
    }
};


class GameDataBst {
private:
    GameNode* root;
    void insert(GameNode*& root, GameNode* newNode) {
        if (root == nullptr) {
            root = newNode;
            return;
        } else if (newNode->Game_ID < root->Game_ID) {
            insert(root->left, newNode);
        } else if (newNode->Game_ID > root->Game_ID) {
            insert(root->right, newNode);
        } else {
            cout << "Game already exists" << endl;
            delete newNode;
        }
        root->height= max(getHeight(root->left),getHeight(root->right))+1;
        if(getBalance(root)==2){
            if(getBalance(root->left)>=0){
                root=rotateRight(root);
            }
            else{
                root->left=rotateLeft(root->left);
                root=rotateRight(root);
            }
        }
        else if(getBalance(root)==-2){
            if(getBalance(root->right)<=0){
                root=rotateLeft(root);
            }
            else{
                root->right=rotateRight(root->right);
                root=rotateLeft(root);
            }
        }
    }
    // Perform a right rotation on the subtree rooted with y
GameNode* rotateRight(GameNode* y) {
    GameNode* x = y->left;
    GameNode* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    // Return new root
    return x;
}

// Perform a left rotation on the subtree rooted with x
GameNode* rotateLeft(GameNode* x) {
    GameNode* y = x->right;
    GameNode* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    // Return new root
    return y;
}

    GameNode* getSmallest(GameNode* root) {
        if (root == nullptr) return nullptr;
        while (root->left != nullptr) root = root->left;
        return root;
    }

    GameNode* deleteNode(GameNode* root, const string& Game_ID) {
        if (root == nullptr) return root;

        if (Game_ID < root->Game_ID) {
            root->left = deleteNode(root->left, Game_ID);
        } else if (Game_ID > root->Game_ID) {
            root->right = deleteNode(root->right, Game_ID);
        } else {
            if (root->left == nullptr) {
                GameNode* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == nullptr) {
                GameNode* temp = root->left;
                delete root;
                return temp;
            } else {
                GameNode* smallest = getSmallest(root->right);
                root->Game_ID = smallest->Game_ID;
                root->name = smallest->name;
                root->developer = smallest->developer;
                root->publisher = smallest->publisher;
                root->gameSize = smallest->gameSize;
                root->downloads = smallest->downloads;
                root->right = deleteNode(root->right, smallest->Game_ID);
                
            }
        }
    // Update the height of the current node
    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;

    // Get balance factor to check if the node became unbalanced
    int balance = getBalance(root);

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0) {
        return rotateRight(root);
    }

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0) {
        return rotateLeft(root);
    }

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }
    return root;
}


    GameNode* search(GameNode* root, const string& Id) {
        if (root == nullptr) {
            cout << "Game not found, reached a leaf node." << endl;
            return root;
        }

        // Print the current node's playerId as we visit it
        cout << root->Game_ID << " -> ";

        // If we find the player, print the found message and return
        if (root->Game_ID == Id) {
            cout << "Game found!" << endl;
            return root;
        }

        if (Id < root->Game_ID) {
            return search(root->left,Id);
        } else {
            return search(root->right, Id);
        }
    }

public:
    GameDataBst() : root(nullptr) {}

    void insert(GameNode* newNode) {
        insert(root, newNode);
    }
    int getHeight(GameNode*rootX){
        if(rootX==nullptr){
            return -1;
        }
        else{
            return rootX->height;
        }
    }
    int getBalance(GameNode*rootX){
        return getHeight(rootX->left) - getHeight(rootX->right);
    }

    GameNode* getRoot() {
        return root;
    }   


    GameNode* search(const string& Game_ID) {
        return search(root, Game_ID);
    }

    void deleteGame(const string& Game_ID) {
        root = deleteNode(root, Game_ID);
    }
    void readFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error opening file." << endl;
            return;
        }
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            GameNode* newNode = new GameNode();
            getline(ss, newNode->Game_ID, ',');
            getline(ss, newNode->name, ',');
            getline(ss, newNode->developer, ',');
            getline(ss, newNode->publisher, ',');
            ss >> newNode->gameSize;
            ss >> newNode->downloads;

            insert(newNode);
        }

        file.close();
    }
    void inOrderTraversal(){
        inOrderTraversal(root);
    }
    void inOrderTraversal(GameNode* node) {
        if (node) {
            inOrderTraversal(node->left);
            cout << "Game ID: " << node->Game_ID << ", Name: " << node->name << endl;
            inOrderTraversal(node->right);
        }
    }    
    };


class GamePlayedNode {
public:
    string Game_Id;
    float hoursPlayed;
    int achievements;
    int height;
    GamePlayedNode* left;
    GamePlayedNode* right;

    GamePlayedNode() : left(nullptr), right(nullptr) {}
    GamePlayedNode(const string& id, float hours, int ach) 
        : Game_Id(id), hoursPlayed(hours), achievements(ach), left(nullptr), right(nullptr) {}
};

class GamesPlayedBst {
private:
    GamePlayedNode* root;
    // Search for a game in the tree
    GamePlayedNode* search(GamePlayedNode* root, const string& gameId) {
        if (root == nullptr || root->Game_Id == gameId) {
            return root;
        }
        if (gameId < root->Game_Id) {
            return search(root->left, gameId);
        } else {
            return search(root->right, gameId);
        }
    }
int getHeight(GamePlayedNode* node) {
        return node ? node->height : -1;
    }

    // Calculate the balance factor of a node
    int getBalance(GamePlayedNode* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    // Update the height of a node
    void updateHeight(GamePlayedNode* node) {
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    }

    // Perform a right rotation on the subtree rooted with y
    GamePlayedNode* rotateRight(GamePlayedNode* y) {
        GamePlayedNode* x = y->left;
        GamePlayedNode* T2 = x->right;

        // Perform rotation
        x->right = y;
        y->left = T2;

        // Update heights
        updateHeight(y);
        updateHeight(x);

        // Return new root
        return x;
    }

    // Perform a left rotation on the subtree rooted with x
    GamePlayedNode* rotateLeft(GamePlayedNode* x) {
        GamePlayedNode* y = x->right;
        GamePlayedNode* T2 = y->left;

        // Perform rotation
        y->left = x;
        x->right = T2;

        // Update heights
        updateHeight(x);
        updateHeight(y);

        // Return new root
        return y;
    }


    
    // Insert a new node into the AVL tree
     void insert(GamePlayedNode*& root, GamePlayedNode* newNode) {
        if (root == nullptr) {
            root = newNode;
            return;
        } else if (newNode->Game_Id < root->Game_Id) {
            insert(root->left, newNode);
        } else if (newNode->Game_Id > root->Game_Id) {
            insert(root->right, newNode);
        } else {
            cout << "Game already exists" << endl;
            delete newNode;
        }
        root->height= max(getHeight(root->left),getHeight(root->right))+1;
        if(getBalance(root)==2){
            if(getBalance(root->left)>=0){
                root=rotateRight(root);
            }
            else{
                root->left=rotateLeft(root->left);
                root=rotateRight(root);
            }
        }
        else if(getBalance(root)==-2){
            if(getBalance(root->right)<=0){
                root=rotateLeft(root);
            }
            else{
                root->right=rotateRight(root->right);
                root=rotateLeft(root);
            }
        }
    }
    // Delete a node from the AVL tree
    GamePlayedNode* deleteNode(GamePlayedNode* root, const string& gameId) {
        if (root == nullptr) return root;

        if (gameId < root->Game_Id) {
            root->left = deleteNode(root->left, gameId);
        } else if (gameId > root->Game_Id) {
            root->right = deleteNode(root->right, gameId);
        } else {
            // Node to be deleted found
            if (root->left == nullptr || root->right == nullptr) {
                GamePlayedNode* temp = root->left ? root->left : root->right;
                delete root;
                return temp;
            } else {
                // Node with two children, get the inorder successor
                GamePlayedNode* smallest = getSmallest(root->right);
                root->Game_Id = smallest->Game_Id;
                root->hoursPlayed = smallest->hoursPlayed;
                root->achievements = smallest->achievements;
                root->right = deleteNode(root->right, smallest->Game_Id);
            }
        }
root->height= max(getHeight(root->left),getHeight(root->right))+1;
        if(getBalance(root)==2){
            if(getBalance(root->left)>=0){
                root=rotateRight(root);
            }
            else{
                root->left=rotateLeft(root->left);
                root=rotateRight(root);
            }
        }
        else if(getBalance(root)==-2){
            if(getBalance(root->right)<=0){
                root=rotateLeft(root);
            }
            else{
                root->right=rotateRight(root->right);
                root=rotateLeft(root);
            }
        }
        return root;
    }

    // Find the smallest node (for deletion)
    GamePlayedNode* getSmallest(GamePlayedNode* root) {
        while (root->left != nullptr) {
            root = root->left;
        }
        return root;
    }

    // In-order traversal for debugging or displaying the tree
    void inOrderTraversal(GamePlayedNode* node) {
        if (node) {
            inOrderTraversal(node->left);
            cout << "Game ID: " << node->Game_Id << ", Hours: " << node->hoursPlayed << ", Achievements: " << node->achievements << endl;
            inOrderTraversal(node->right);
        }
    }
public:
    GamesPlayedBst() : root(nullptr) {}

    // Public insert function
    void insert(GamePlayedNode* newNode) {
        insert(root, newNode);
    }

    // Public search function
    GamePlayedNode* search(const string& gameId) {
        return search(root, gameId);
    }

    // Public delete function
    void deleteGame(const string& gameId) {
        root = deleteNode(root, gameId);
    }

    // In-order traversal for the entire tree
    void inOrderTraversal() {
        inOrderTraversal(root);
    }
    

    // Function to manually insert a game
    void insertManualGame() {
        string gameId;
        float hoursPlayed;
        int achievements;

        cout << "Enter Game ID: "; 
        cin >> gameId;
        cout << "Enter Hours Played: "; 
        cin >> hoursPlayed;
        cout << "Enter Achievements: "; 
        cin >> achievements;

        GamePlayedNode* newNode = new GamePlayedNode(gameId, hoursPlayed, achievements);
        insert(newNode);
        cout << "Game added to player's games successfully!" << endl;
    }
};

// Define the PlayerNode structure
class PlayerNode {
public:
    string playerId;
    string name;
    string phoneNumber;
    string email;
    string password;
    GamesPlayedBst gamesPlayedTree; // Tree of games played by this player
    PlayerNode* left;
    PlayerNode* right;

    PlayerNode() : left(nullptr), right(nullptr) {}
};

// Queue Node structure (linked list)
class QueueNode {
public:
    PlayerNode* player;  // Pointer to the player node
    QueueNode* next;     // Pointer to the next node in the queue

    QueueNode(PlayerNode* p) : player(p), next(nullptr) {}
};

// Queue class
class Queue {
public:
    QueueNode* front;
    QueueNode* rear;


    Queue() : front(nullptr), rear(nullptr) {}

    // Check if the queue is empty
    bool isEmpty() {
        return front == nullptr;
    }

    // Add an element to the queue (enqueue)
    void enqueue(PlayerNode* player) {
        QueueNode* newNode = new QueueNode(player);
        if (isEmpty()) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    // Remove an element from the queue (dequeue)
    PlayerNode* dequeue() {
        if (isEmpty()) {
            return nullptr;
        }

        QueueNode* temp = front;
        PlayerNode* player = front->player;
        front = front->next;
        delete temp;
        return player;
    }

    // Peek at the front of the queue
    PlayerNode* peek() {
        if (isEmpty()) {
            return nullptr;
        }
        return front->player;
    }
};


// Define the player data BST
class PlayerDataBst {
private:
    PlayerNode* root;

    void insert(PlayerNode*& root, PlayerNode* newNode) {
        if (root == nullptr) {
            root = newNode;
        } else if (newNode->playerId < root->playerId) {
            insert(root->left, newNode);
        } else if (newNode->playerId > root->playerId) {
            insert(root->right, newNode);
        } else {
            cout << "Player already exists" << endl;
            delete newNode;
        }
    }

    PlayerNode* search(PlayerNode* root, const string& playerId) {
        if (root == nullptr || root->playerId == playerId) {
            return root;
        }

        if (playerId < root->playerId) {
            return search(root->left, playerId);
        } else {
            return search(root->right, playerId);
        }
    }

    PlayerNode* getSmallest(PlayerNode* root) {
        while (root && root->left != nullptr) {
            root = root->left;
        }
        return root;
    }

    PlayerNode* deleteNode(PlayerNode* root, const string& playerId) {
        if (root == nullptr) return root;

        if (playerId < root->playerId) {
            root->left = deleteNode(root->left, playerId);
        } else if (playerId > root->playerId) {
            root->right = deleteNode(root->right, playerId);
        } else {
            if (root->left == nullptr) {
                PlayerNode* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == nullptr) {
                PlayerNode* temp = root->left;
                delete root;
                return temp;
            } else {
                PlayerNode* smallest = getSmallest(root->right);
                root->playerId = smallest->playerId;
                root->name = smallest->name;
                root->phoneNumber = smallest->phoneNumber;
                root->email = smallest->email;
                root->password = smallest->password;
                root->right = deleteNode(root->right, smallest->playerId);
            }
        }
        return root;
    }

public:
    PlayerDataBst() : root(nullptr) {}

    void insert(PlayerNode* newNode) {
        insert(root, newNode);
    }
    PlayerNode *getRoot(){
        return root;
    }
    PlayerNode* search(const string& playerId) {
        return search(root, playerId);
    }

    void deletePlayer(const string& playerId) {
        root = deleteNode(root, playerId);
    }
    void showPreorderPath(PlayerNode* root, const string& playerId) {
        if (root == nullptr) {
            cout << "Player not found, reached a leaf node." << endl;
            return;
        }

        // Print the current node's playerId as we visit it
        cout << root->playerId << " -> ";

        // If we find the player, print the found message and return
        if (root->playerId == playerId) {
            cout << "Player found!" << endl;
            return;
        }

        // Continue searching in the left or right subtree
        if (playerId < root->playerId) {
            showPreorderPath(root->left, playerId);
        } else {
            showPreorderPath(root->right, playerId);
        }
}




    // Function to read player data from a file
    void readFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error opening file." << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            if (rand() % 1000 < specialNumber) {
                continue; // Skip record based on random condition
            }

            stringstream ss(line);
            PlayerNode* newNode = new PlayerNode();

            // Read and parse player data from line
            getline(ss, newNode->playerId, ',');
            getline(ss, newNode->name, ',');
            getline(ss, newNode->phoneNumber, ',');
            getline(ss, newNode->email, ',');
            getline(ss, newNode->password, ',');

            // Parse multiple games played by the player and add them to the gamesPlayedTree
            string gameId;
            float hoursPlayed;
            int achievements;
            while (getline(ss, gameId, ',') && ss >> hoursPlayed && ss.ignore() && ss >> achievements) {
                ss.ignore(); // Ignore comma between records
                GamePlayedNode* gameNode = new GamePlayedNode(gameId, hoursPlayed, achievements);
                newNode->gamesPlayedTree.insert(gameNode);
            }

            // Insert player node into the BST
            insert(newNode);
        }

        file.close();
    }
    int findLayer(PlayerNode* root, const string& playerId, int currentLayer) {
    if (root == nullptr) {
        return -1; // Return -1 if the player is not found
    }
    if (root->playerId == playerId) {
        return currentLayer; // Return the layer if player is found
    }

    // Recur for the left or right subtree
    int leftLayer = findLayer(root->left, playerId, currentLayer + 1);
    if (leftLayer != -1) {
        return leftLayer; // If found in left subtree, return the layer
    }

    return findLayer(root->right, playerId, currentLayer + 1); // Otherwise, check the right subtree
}

    void showNLayers(int N) {
        if (root == nullptr) {
            cout << "The tree is empty." << endl;
            return;
        }

        Queue q;
        q.enqueue(root);

        int currentLayer = 0;
        bool layerLimitReached = false;

        while (!q.isEmpty()) {
            int layerSize = 0;
            QueueNode* temp = q.front;  // Temporary pointer to traverse the current queue layer

            // Count the number of nodes in the current layer
            QueueNode* node = q.front;
            while (node) {
                layerSize++;
                node = node->next;
            }

            currentLayer++;

            if (currentLayer > N) {
                layerLimitReached = true;
                break;
            }

            // Print nodes at the current layer
            cout << "Layer " << currentLayer << ": ";
            for (int i = 0; i < layerSize; i++) {
                PlayerNode* player = q.dequeue();
                cout << player->playerId << " (" << player->name << ") ";

                // Enqueue children if they exist
                if (player->left != nullptr) {
                    q.enqueue(player->left);
                }
                if (player->right != nullptr) {
                    q.enqueue(player->right);
                }
            }
            cout << endl;
        }

        // If the layer limit was reached, print the warning
        if (layerLimitReached) {
            cout << "Layer Limit was Reached, can't go further." << endl;
        }
    }


    void insertManualPlayer() {
        PlayerNode* newNode = new PlayerNode();
        cout << "Enter Player ID: "; cin >> newNode->playerId;
        cin.ignore(); // Clear input buffer
        cout << "Enter Name: "; getline(cin, newNode->name);
        cout << "Enter Phone Number: "; getline(cin, newNode->phoneNumber);
        cout << "Enter Email: "; getline(cin, newNode->email);
        cout << "Enter Password: "; getline(cin, newNode->password);

        // Adding games played for the player
        char addMoreGames;
        do {
            string gameId;
            float hoursPlayed;
            int achievements;
            cout << "Enter Game ID: "; cin >> gameId;
            cout << "Enter Hours Played: "; cin >> hoursPlayed;
            cout << "Enter Achievements: "; cin >> achievements;
            GamePlayedNode* gameNode = new GamePlayedNode(gameId, hoursPlayed, achievements);
            newNode->gamesPlayedTree.insert(gameNode);

            cout << "Do you want to add another game? (y/n): ";
            cin >> addMoreGames;
        } while (addMoreGames == 'y' || addMoreGames == 'Y');

        insert(newNode);
        cout << "Player added successfully!" << endl;
    }


    // Example in-order traversal for debugging
    void inOrderTraversal(PlayerNode* node) {
        if (node) {
            inOrderTraversal(node->left);
            cout << "Player ID: " << node->playerId << ", Name: " << node->name << endl;
            cout << "Games played by " << node->name << ":" << endl;
            node->gamesPlayedTree.inOrderTraversal();
            inOrderTraversal(node->right);
        }
    }

    void inOrderTraversal() {
        inOrderTraversal(root);
    }
};
int main() {
    PlayerDataBst pdbst;
    GameDataBst gdBst;

    pdbst.readFromFile("Players.txt");
    gdBst.readFromFile("Games.txt");

    int choice;
    string inputId;

    do {
        cout << "\n===== Menu =====\n";
        cout << "1. View all players\n";
        cout << "2. View all games\n";
        cout << "3. Search player\n";
        cout << "4. Search game\n";
        cout << "5. Add game to player's list\n";
        cout << "6. Delete game from player's list\n";
        cout << "7. Delete player from Memmory\n";
        cout << "8. Delete game\n";
        cout << "9. Exit\n";
        cout << "10. Show N layers of Player Data BST\n";
        cout << "11. Find Layer Number of Player\n"; // Added option for finding layer number
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Players in BST (in-order):" << endl;
                pdbst.inOrderTraversal();
                break;

            case 2:
                cout << "Games in BST (in-order):" << endl;
                gdBst.inOrderTraversal();
                break;

            case 3:  // Search player and show Preorder path
                cout << "Enter Player ID to search: ";
                cin >> inputId;
                {
                    PlayerNode* player = pdbst.search(inputId);
                    if (player) {
                        cout << "Player found: " << player->name << endl;
                        cout << "Preorder path taken to find the player:" << endl;
                        pdbst.showPreorderPath(pdbst.getRoot(), inputId);
                        cout<<"Do you want to check If player has Played some Game?\n";
                        cout<<"1.Yes\n";
                        cout<<"2.No\n";
                        int choice;
                        cin>>choice;
                        if(choice==1){
                            cout<<"Give Game Id\n";
                            cin>>inputId;

                            player->gamesPlayedTree.search(inputId);
                        }

                    } else {
                        cout << "Player not found." << endl;
                    }

                    // Show the Preorder Path for the search
                }
                break;

            case 4:
                cout << "Enter Game ID to search: ";
                cin >> inputId;
                {   
                    GameNode* game = gdBst.search(inputId);
                    if (game) {
                        cout << "Game found: " << game->name << endl;
                    } else {
                        cout << "Game not found." << endl;
                    }
                }
                break;

            case 5:
                cout << "Enter Player ID to add game: ";
                cin >> inputId;
                {
                    PlayerNode* player = pdbst.search(inputId);
                    if (player) {
                        player->gamesPlayedTree.insertManualGame(); // Add a game to player's list
                    } else {
                        cout << "Player not found." << endl;
                    }
                }
                break;

            case 6:
                cout << "Enter Player ID to delete game: ";
                cin >> inputId;
                {
                    PlayerNode* player = pdbst.search(inputId);
                    if (player) {
                        cout << "Enter Game ID to delete: ";
                        string gameId;
                        cin >> gameId;
                        player->gamesPlayedTree.deleteGame(gameId); // Delete a game from player's list
                    } else {
                        cout << "Player not found." << endl;
                    }
                }
                break;
            case 7:
                cout << "Enter Played ID to delete player from Memmory: ";
                cin >> inputId;
                pdbst.deletePlayer(inputId); // Delete game from global games list
                break;

            case 8:
                cout << "Enter Game ID to delete from games: ";
                cin >> inputId;
                gdBst.deleteGame(inputId); // Delete game from global games list
                break;

            case 9:
                cout << "Exiting program." << endl;
                break;

            case 10: {
                int nLayers;
                cout << "Enter the number of layers to show: ";
                cin >> nLayers;
                pdbst.showNLayers(nLayers); // Show up to N layers of the tree
                break;
            }

            case 11: { // Added option to find the layer number of a player
                cout << "Enter Player ID to find layer number: ";
                cin >> inputId;
                int layer = pdbst.findLayer(pdbst.getRoot(), inputId, 0); // Call the findLayer method
                if (layer == -1) {
                    cout << "Player not found." << endl;
                } else {
                    cout << "The player is at layer " << layer << "." << endl;
                }
                break;
            }

            default:
                cout << "Invalid choice, try again." << endl;
                break;
        }

    } while (choice != 9);

    return 0;
}
