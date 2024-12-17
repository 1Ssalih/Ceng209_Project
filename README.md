# **Dungeon Adventure Game**

## **Report Link**
https://docs.google.com/document/d/1BMcW5TRa5rEmX6tPb2vKEOFVo6jKiBTwkz0vLdqhJp4/edit?usp=sharing

## **Game Description**
The Dungeon Adventure is a text-based command-line game where you explore rooms, fight creatures, pick up items, and navigate through a dungeon. The game includes a time-limited exploration, dynamic combat system, inventory management, and a market where you can purchase useful items.

---


---

## **Game Commands**

| **Command**         | **Description**                                                                 |
|----------------------|-------------------------------------------------------------------------------|
| `move <direction>`   | Move in a specific direction (`up`, `down`, `left`, `right`).                |
| `look`              | Display the current room's description, creatures, traps, or items.           |
| `inventory`         | Show your current inventory.                                                  |
| `pickup <item>`      | Pick up an item in the current room.                                          |
| `attack`            | Attack a creature in the current room.                                         |
| `read note`         | Read any notes found in the room.                                              |
| `check trap`        | Check for traps in the current room.                                           |
| `map`               | Display a visual map of visited rooms and your current position.              |
| `coins`             | Display your current coin balance.                                             |
| `market`            | Display the market items when you are in the Market Hall.                     |
| `buy <item>`        | Purchase an item from the market.                                              |
| `use <item>`        | Use an item from your inventory (e.g., health potions).                        |
| `save <filename>`    | Save the current game state to a file.                                        |
| `load <filename>`    | Load a saved game from a file.                                                |
| `list`              | List all saved game files in the current directory.                           |
| `exit`              | Exit the game.                                                                |

---

## **Functions Explained**

### **Game Logic and Player Actions**
1. **`move(Player *player, const char *direction)`**  
   Moves the player to a new room in the specified direction (`up`, `down`, `left`, `right`).

2. **`look(Player *player)`**  
   Displays the current room description, notes, traps, creatures, or items.

3. **`attack(Player *player)`**  
   Engages in combat with a creature in the current room. Handles both player attacks and creature counterattacks.

4. **`pickup(Player *player, const char *item)`**  
   Picks up an item in the current room and adds it to the player's inventory.

5. **`use_item(Player *player, const char *item_name)`**  
   Uses an item from the inventory (e.g., health potions, equipment) and applies its effects.

6. **`read_note(Player *player)`**  
   Reads a note present in the current room.

7. **`check_trap(Player *player)`**  
   Checks for traps in the current room and applies damage if a trap is triggered.

8. **`inventory(Player *player)`**  
   Displays the player's inventory and the items within it.

9. **`save_game(Player *player, const char *filepath)`**  
   Saves the current game state, including player stats, room, and inventory, to a file.

10. **`load_game(Player *player, const char *filepath, Room *rooms[], int room_count)`**  
    Loads a saved game state from a file, restoring player stats, current room, and inventory.

11. **`list_saved_games()`**  
    Lists all saved games (files ending with `.save`) in the current directory.

---

### **Room and Map Management**
12. **`create_room(const char *name, const char *description, int x, int y)`**  
    Creates a new room with a given name, description, and coordinates.

13. **`link_rooms(Room *room1, Room *room2, const char *direction)`**  
    Links two rooms in the specified direction (`up`, `down`, `left`, or `right`).

14. **`display_map(Room *rooms[], int room_count, Player *player)`**  
    Displays a visual map of the dungeon, showing visited rooms, unvisited rooms, and the player's current location.

---

### **Market and Items**
15. **`display_market()`**  
    Displays the available items in the market and their prices.

16. **`buy_item(Player *player, const char *item_name)`**  
    Allows the player to buy an item from the market, provided they have enough coins.

17. **`create_item(const char *name, const char *description, int effect_value, int type)`**  
    Dynamically allocates memory to create a new item with specified attributes.

18. **`creature_drop(Player *player)`**  
    Handles potential item drops when a creature is defeated.

---

### **Memory Management**
19. **`free_dynamic_memory(Room *rooms[], int room_count)`**  
    Frees dynamically allocated memory for room descriptions, notes, and items.

20. **`free_inventory(Player *player)`**  
    Frees dynamically allocated memory for all items in the player's inventory.

---

## **Gameplay**

1. **Start**:
   - You begin in the **Market Hall** with 50 coins, 100 health, and basic stats.
   - Use `look` to observe your surroundings.

2. **Navigation**:
   - Use `move <direction>` to explore the dungeon.

3. **Combat**:
   - Use `attack` to fight creatures. Combat continues until the creature is defeated or your health drops to zero.

4. **Market**:
   - Use the `market` command to view items and `buy <item>` to purchase them.

5. **Items**:
   - Pick up items with `pickup <item>`.
   - Use items with `use <item>` to gain effects like healing or stat boosts.

6. **Saving/Loading**:
   - Save your progress using `save <filename>`.
   - Reload a saved game with `load <filename>`.

7. **Map**:
   - Use `map` to see a visual representation of visited and unvisited rooms.

---

## **Technical Details**

- **Dynamic Memory**:  
   Memory for rooms, notes, items, and inventory is dynamically allocated and freed properly to avoid memory leaks.

- **File I/O**:  
   The game state (player stats, inventory, current room) is saved to and loaded from text files.

- **Error Handling**:  
   Invalid inputs, full inventory, or corrupted save files are handled gracefully with error messages.

---

## **Files**

- **game.c**: Contains the main game logic and all function implementations.
- **game.h**: Header file defining the structs, function prototypes, and global variables.
- **Makefile**: Simplifies building and cleaning the game.
- **README.md**: Game description, compilation steps, commands, and function explanations.
