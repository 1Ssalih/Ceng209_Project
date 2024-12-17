#include "game.h"

int main() {
    srand(time(NULL));


    Room *rooms[8];
    rooms[0] = create_room("Market Hall", "Welcome to the starting room. There is a market here where you can buy items using coins.", 5, 5);
    rooms[1] = create_room("Goblin's Lair", "A dark room with an eerie silence.", 5, 6);
    rooms[2] = create_room("Treasure Vault", "This room has a sparkling chest and a goblin.", 5, 7);
    rooms[3] = create_room("Burnt Chamber", "This room smells of burnt wood.", 6, 7);
    rooms[4] = create_room("Shadow Den", "A room with broken walls and a lurking shadow.", 6, 6);
    rooms[5] = create_room("Altar of Mysteries", "This room contains a mysterious altar.", 6, 5);
    rooms[6] = create_room("Damp Cavern", "A damp room with dripping water sounds.", 7, 5);
    rooms[7] = create_room("Golden Sanctuary", "A bright room filled with golden light.", 7, 6);


    link_rooms(rooms[0], rooms[1], "right");
    link_rooms(rooms[1], rooms[2], "right");
    link_rooms(rooms[2], rooms[3], "down");
    link_rooms(rooms[3], rooms[4], "left");
    link_rooms(rooms[4], rooms[5], "left");
    link_rooms(rooms[5], rooms[6], "down");
    link_rooms(rooms[6], rooms[7], "right");

    int room_count = 8;

    rooms[0]->has_creature = 0;
    rooms[0]->creature_health = 0;
    rooms[0]->has_trap = 0;


    rooms[0]->note = strdup("Valandor's hidden scrolls await. Begin your journey to uncover the truth.");
    rooms[1]->note = strdup("The king sacrificed his people to uphold the kingdom's wealth.");
    rooms[2]->note = strdup("The shadows here are restless. They are the souls of the sacrificed.");
    rooms[3]->note = strdup("The Dark Lord's curse grows stronger as you descend further.");
    rooms[4]->note = strdup("Valandor's throne holds a key to his mistakes. Look closely.");
    rooms[5]->note = strdup("The altar whispers of betrayal. A final door looms ahead.");
    rooms[6]->note = strdup("The guardians of the Dark Lord stand ready. Defeat them to proceed.");
    rooms[7]->note = strdup("You have reached the Dark Lord's temple. Prepare for the final battle.");


    rooms[1]->has_creature = 1; rooms[1]->creature_health = 100;
    rooms[2]->has_creature = 1; rooms[2]->creature_health = 110;
    rooms[3]->has_creature = 1; rooms[3]->creature_health = 120;
    rooms[4]->has_creature = 1; rooms[4]->creature_health = 130;
    rooms[5]->has_creature = 1; rooms[5]->creature_health = 140;
    rooms[6]->has_creature = 1; rooms[6]->creature_health = 150;
    rooms[7]->has_creature = 1; rooms[7]->creature_health = 160;



    char *creature_descriptions[] = {
        "A small goblin", "A giant spider", "A fiery demon",
        "A lurking shadow", "An armored knight",
        "A wild beast", "A poisonous snake", "A deadly dragon"
    };

    char *item_descriptions[] = {
        "Small Health Potion", "Large Health Potion", "Sword",
        "Shield", "Armor", "Magic Wand", "Golden Key", "Silver Key",
        "Health Elixir", "Mana Elixir", "Bow", "Arrow", "Helmet",
        "Boots", "Amulet", "Ring", "Gemstone", "Torch", "Map",
        "Trap Disabler", "Lockpick", "Gold Coin", "Silver Coin",
        "Ruby", "Emerald", "Sapphire", "Crystal Ball", "Holy Relic",
        "Cursed Idol", "Ancient Scroll"
    };


    for (int i = 1; i < room_count; i++) {
        rooms[i]->has_creature = 1;
        rooms[i]->creature_health = 20 + rand() % 31;
        rooms[i]->item = strdup(item_descriptions[rand() % 30]); // Random item
        printf("Room %d contains: %s, Creature: %s (%d health)\n",
               i + 1, rooms[i]->item, creature_descriptions[i % 8], rooms[i]->creature_health);
    }


    for (int i = 0; i < 3; i++) {
        int trap_room = rand() % room_count;
        if (trap_room != 0) {
            rooms[trap_room]->has_trap = 1;
            rooms[trap_room]->trap_damage = 10 + rand() % 11;
        }
    }


    Player player = {10, 150, 20, 30, NULL, 0, 10, rooms[0], 100}; // 50 coins başlangıç


    player.inventory = malloc(player.inventory_capacity * sizeof(Item *));
    if (!player.inventory) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    char command[256];
    while (1) {
        printf("\n> ");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = '\0';

        if (strncmp(command, "move", 4) == 0) {
            player.time_remaining--;
            move(&player, command + 5);
        } else if (strcmp(command, "look") == 0) {
            look(&player);
        } else if (strcmp(command, "map") == 0) {
            display_map(rooms, room_count, &player);
        } else if (strcmp(command, "inventory") == 0) {
            inventory(&player);
        } else if (strcmp(command, "coins") == 0) {
            printf("You currently have %d coins.\n", player.coins);
        } else if (strcmp(command, "market") == 0) {
            display_market();
        } else if (strncmp(command, "buy", 3) == 0) {
            buy_item(&player, command + 4);
        } else if (strncmp(command, "use", 3) == 0) {
            char *item_name = command + 4; // Skip "use "
            use_item(&player, item_name);
        } else if (strncmp(command, "pickup", 6) == 0) {
            player.time_remaining--; // Picking up an item costs time
            pickup(&player, command + 7);
        } else if (strcmp(command, "attack") == 0) {
            player.time_remaining--; // Attacking costs time
            attack(&player);
        } else if (strcmp(command, "check trap") == 0) {
            check_trap(&player);
        } else if (strcmp(command, "read note") == 0) {
            read_note(&player);
        } else if (strncmp(command, "save", 4) == 0) {
            save_game(&player, command + 5);
        } else if (strncmp(command, "load", 4) == 0) {
            load_game(&player, command + 5, rooms, room_count);
        } else if (strcmp(command, "list") == 0) {
            list_saved_games();
        } else if (strcmp(command, "exit") == 0) {
            break;
        } else {
            printf("Unknown command. Try again.\n");
        }

        printf("Time remaining: %d\n", player.time_remaining);


        if (player.time_remaining <= 0) {
            printf("You ran out of time! Game over!\n");
            break;
        }


        if (player.health <= 0) {
            printf("You have been defeated. Game over!\n");
            break;
        }
    }

    free_dynamic_memory(rooms, room_count);
    free_inventory(&player);

    return 0;
}



Room *create_room(const char *name, const char *description, int x, int y) {
    Room *room = malloc(sizeof(Room));
    if (!room) {
        fprintf(stderr, "Failed to allocate memory for room.\n");
        exit(EXIT_FAILURE);
    }
    room->name = strdup(name);
    room->description = strdup(description);
    room->up = room->down = room->left = room->right = NULL;
    room->x = x;
    room->y = y;
    room->has_creature = 0;
    room->creature_health = 0;
    room->has_trap = 0;
    room->trap_damage = 0;
    room->item = NULL;
    room->note = NULL;
    room->note_read = 0;
    room->visited = 0;
    return room;
}



void link_rooms(Room *room1, Room *room2, const char *direction) {
    if (strcmp(direction, "right") == 0) {
        room1->right = room2;
        room2->left = room1;
    } else if (strcmp(direction, "left") == 0) {
        room1->left = room2;
        room2->right = room1;
    } else if (strcmp(direction, "up") == 0) {
        room1->up = room2;
        room2->down = room1;
    } else if (strcmp(direction, "down") == 0) {
        room1->down = room2;
        room2->up = room1;
    }
}


void display_market() {
    printf("Market Items:\n");
    for (int i = 0; i < market_items_count; i++) {
        printf("- %s (%d coins): %s\n", market_items[i].name, market_items[i].cost, market_items[i].description);
    }
}


void display_map(Room *rooms[], int room_count, Player *player) {
    int map[10][10] = {0};

    for (int i = 0; i < room_count; i++) {
        if (rooms[i] == player->current_room) {
            map[rooms[i]->x][rooms[i]->y] = 2;
        } else if (rooms[i]->visited) {
            map[rooms[i]->x][rooms[i]->y] = 3;
        } else {
            map[rooms[i]->x][rooms[i]->y] = 1;
        }
    }

    printf("\nMap:\n");
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (map[i][j] == 0) {
                printf(". ");
            } else if (map[i][j] == 1) {
                printf("O ");
            } else if (map[i][j] == 2) {
                printf("* ");
            } else if (map[i][j] == 3) {
                printf("X ");
            }
        }
        printf("\n");
    }


    printf("You are currently in: %s\n", player->current_room->name);
}




void free_dynamic_memory(Room *rooms[], int room_count) {
    for (int i = 0; i < room_count; i++) {
        free(rooms[i]->description);
        if (rooms[i]->note) free(rooms[i]->note);
        if (rooms[i]->item) free(rooms[i]->item);
        free(rooms[i]);
    }
}


void free_inventory(Player *player) {
    for (int i = 0; i < player->inventory_size; i++) {
        free(player->inventory[i]->name);
        free(player->inventory[i]->description);
        free(player->inventory[i]);
    }
    free(player->inventory);
}


void attack(Player *player) {
    if (player->current_room->has_creature) {
        int player_damage = (rand() % 10) + player->strength;
        printf("You attacked the creature and dealt %d damage!\n", player_damage);
        player->current_room->creature_health -= player_damage;

        if (player->current_room->creature_health <= 0) {
            printf("You defeated the creature!\n");
            player->current_room->has_creature = 0;

            int coins_dropped = rand() % 20 + 10;
            player->coins += coins_dropped;
            printf("The creature dropped %d coins. You now have %d coins.\n", coins_dropped, player->coins);

            creature_drop(player);
        } else {
            int creature_damage = rand() % 10 + 5;
            printf("The creature attacks you and deals %d damage!\n", creature_damage);
            player->health -= creature_damage;

            if (player->health <= 0) {
                printf("Your health is now %d. You have been defeated!\n", player->health);
            } else {
                printf("Your health is now %d.\n", player->health);
            }
        }
    } else {
        printf("There is no creature here to attack.\n");
    }
}



void buy_item(Player *player, const char *item_name) {
    if (strcmp(player->current_room->description, "Welcome to the starting room. There is a market here where you can buy items using coins.") != 0) {
        printf("You can only buy items in the market.\n");
        return;
    }

    for (int i = 0; i < market_items_count; i++) {
        if (strcmp(market_items[i].name, item_name) == 0) {
            if (player->coins >= market_items[i].cost) {
                if (player->inventory_size < player->inventory_capacity) {
                    Item *new_item = create_item(market_items[i].name, market_items[i].description, market_items[i].effect_value, market_items[i].type);
                    player->inventory[player->inventory_size++] = new_item;
                    player->coins -= market_items[i].cost;
                    printf("You bought %s for %d coins. Remaining coins: %d.\n", item_name, market_items[i].cost, player->coins);
                } else {
                    printf("Your inventory is full! You can't buy more items.\n");
                }
            } else {
                printf("You don't have enough coins to buy %s. It costs %d coins.\n", item_name, market_items[i].cost);
            }
            return;
        }
    }
    printf("Item not found in the market.\n");
}



void creature_drop(Player *player) {
    int drop_chance = rand() % 100;
    if (drop_chance < 50) {
        Item *dropped_item = create_item("Small Health Potion", "Restores 20 health.", 20, 0);
        if (player->current_room->item == NULL) {
            player->current_room->item = strdup(dropped_item->name);
            printf("The creature dropped a %s. You can pick it up.\n", dropped_item->name);
        } else {
            printf("The room already has an item, so the dropped item was lost.\n");
        }
        free(dropped_item->name);
        free(dropped_item->description);
        free(dropped_item);
    } else {
        printf("The creature did not drop anything.\n");
    }
}



Item *create_item(const char *name, const char *description, int effect_value, int type) {
    Item *item = malloc(sizeof(Item));
    if (!item) {
        fprintf(stderr, "Failed to allocate memory for item.\n");
        exit(EXIT_FAILURE);
    }
    item->name = strdup(name);
    item->description = strdup(description);
    item->effect_value = effect_value;
    item->type = type;
    return item;
}


void read_note(Player *player) {
    if (player->current_room->note != NULL) {
        printf("You read the note: %s\n", player->current_room->note);
        player->current_room->note_read = 1;
    } else {
        printf("There is no note here.\n");
    }
}


void check_trap(Player *player) {
    if (player->current_room->has_trap) {
        printf("You triggered a trap!\n");
        player->health -= player->current_room->trap_damage;
        printf("You took %d damage. Your health is now %d.\n", player->current_room->trap_damage, player->health);
        player->current_room->has_trap = 0;
    } else {
        printf("There is no trap in this room.\n");
    }
}


void pickup(Player *player, const char *item_name) {
    if (player->current_room->item != NULL &&
        strcmp(player->current_room->item, item_name) == 0) {
        if (player->inventory_size < player->inventory_capacity) {
            Item *new_item = NULL;

            if (strcmp(item_name, "Small Health Potion") == 0) {
                new_item = create_item("Small Health Potion", "Restores 20 health.", 20, 0);
            } else if (strcmp(item_name, "Large Health Potion") == 0) {
                new_item = create_item("Large Health Potion", "Restores 50 health.", 50, 0);
            } else if (strcmp(item_name, "Sword") == 0) {
                new_item = create_item("Sword", "Increases your attack power by 15.", 15, 1);
            } else if (strcmp(item_name, "Armor") == 0) {
                new_item = create_item("Armor", "Increases your defense by 10.", 10, 2);
            } else {
                new_item = create_item(item_name, "A mysterious item.", 0, 3);
            }

            player->inventory[player->inventory_size++] = new_item;
            printf("You picked up: %s\n", item_name);

            free(player->current_room->item);
            player->current_room->item = NULL;
        } else {
            printf("Your inventory is full! You can't pick up the item.\n");
        }
        } else {
            printf("There is no such item here to pick up.\n");
        }
}



void use_item(Player *player, const char *item_name) {
    for (int i = 0; i < player->inventory_size; i++) {
        if (strcmp(player->inventory[i]->name, item_name) == 0) {
            Item *item = player->inventory[i];

            if (item->type == 0) {
                player->health += item->effect_value;
                printf("You used %s. Health increased by %d. Current health: %d.\n",
                       item->name, item->effect_value, player->health);
            } else if (item->type == 1) {
                player->strength += item->effect_value;
                printf("You equipped %s. Strength increased by %d. Current strength: %d.\n",
                       item->name, item->effect_value, player->strength);
            } else if (item->type == 2) {
                player->defense += item->effect_value;
                printf("You equipped %s. Defense increased by %d. Current defense: %d.\n",
                       item->name, item->effect_value, player->defense);
            } else if (item->type == 3) {
                printf("You used %s. Its mysterious power had no immediate effect.\n", item->name);
            }

            free(item->name);
            free(item->description);
            free(item);

            for (int j = i; j < player->inventory_size - 1; j++) {
                player->inventory[j] = player->inventory[j + 1];
            }
            player->inventory_size--;
            return;
        }
    }
    printf("Item not found in inventory.\n");
}



void save_game(Player *player, const char *filepath) {
    FILE *file = fopen(filepath, "w");
    if (file != NULL) {
        fprintf(file, "Player Health: %d\n", player->health);
        fprintf(file, "Player Strength: %d\n", player->strength);
        fprintf(file, "Time Remaining: %d\n", player->time_remaining);
        fprintf(file, "Current Room: %d %d\n", player->current_room->x, player->current_room->y);

        fprintf(file, "Inventory:\n");
        for (int i = 0; i < player->inventory_size; i++) {
            fprintf(file, "%s\n", player->inventory[i]->name);
        }

        fclose(file);
        printf("Game saved to %s.\n", filepath);
    } else {
        printf("Failed to save the game.\n");
    }
}

void load_game(Player *player, const char *filepath, Room *rooms[], int room_count) {
    FILE *file = fopen(filepath, "r");
    if (file != NULL) {
        int room_x, room_y;

        if (fscanf(file, "Player Health: %d\n", &player->health) != 1 ||
            fscanf(file, "Player Strength: %d\n", &player->strength) != 1 ||
            fscanf(file, "Time Remaining: %d\n", &player->time_remaining) != 1 ||
            fscanf(file, "Current Room: %d %d\n", &room_x, &room_y) != 2) {
            printf("Error: Corrupted save file. Unable to load.\n");
            fclose(file);
            return;
        }

        int room_found = 0;
        for (int i = 0; i < room_count; i++) {
            if (rooms[i]->x == room_x && rooms[i]->y == room_y) {
                player->current_room = rooms[i];
                room_found = 1;
                break;
            }
        }
        if (!room_found) {
            printf("Error: Saved room coordinates are invalid.\n");
            fclose(file);
            return;
        }

        free_inventory(player);
        player->inventory_size = 0;

        char item_line[256];
        while (fgets(item_line, sizeof(item_line), file) != NULL) {
            if (strncmp(item_line, "Inventory:", 10) == 0) {
                continue;
            }

            item_line[strcspn(item_line, "\n")] = '\0';

            if (strlen(item_line) == 0) {
                continue;
            }

            if (player->inventory_size < player->inventory_capacity) {
                Item *loaded_item = create_item(item_line, "Loaded item", 20, 0);
                player->inventory[player->inventory_size++] = loaded_item;
            } else {
                printf("Warning: Inventory capacity reached. Could not load all items.\n");
                break;
            }
        }

        fclose(file);
        printf("Game successfully loaded from %s.\n", filepath);
    } else {
        printf("Error: Failed to open save file.\n");
    }
}



void list_saved_games() {
    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    if (d) {
        printf("Saved Games:\n");
        while ((dir = readdir(d)) != NULL) {
            if (strstr(dir->d_name, ".save")) {
                printf("- %s\n", dir->d_name);
            }
        }
        closedir(d);
    } else {
        printf("Failed to list saved games.\n");
    }
}

void move(Player *player, const char *direction) {
    if (player->current_room->has_creature) {
        printf("You cannot leave this room without defeating the creature!\n");
        return;
    }

    Room *new_room = NULL;

    if (strcmp(direction, "up") == 0) {
        new_room = player->current_room->up;
    } else if (strcmp(direction, "down") == 0) {
        new_room = player->current_room->down;
    } else if (strcmp(direction, "left") == 0) {
        new_room = player->current_room->left;
    } else if (strcmp(direction, "right") == 0) {
        new_room = player->current_room->right;
    }

    if (new_room != NULL) {
        player->current_room = new_room;
        printf("You moved to a new room. Use 'look' to see what's inside.\n");
    } else {
        printf("You can't move in that direction.\n");
    }
}



void look(Player *player) {
    printf("You are in: %s\n", player->current_room->description);

    if (player->current_room->has_creature) {
        printf("There is a creature here with %d health.\n", player->current_room->creature_health);
    }

    if (player->current_room->has_trap) {
        printf("There is a trap in this room! Be cautious.\n");
    }

    if (player->current_room->note != NULL && !player->current_room->note_read) {
        printf("There is a note here. Use 'read note' to read it.\n");
    }

    if (player->current_room->item != NULL) {
        printf("There is an item here: %s.\n", player->current_room->item);
    }
}



void inventory(Player *player) {
    printf("Inventory (%d/%d):\n", player->inventory_size, player->inventory_capacity);
    if (player->inventory_size == 0) {
        printf("Your inventory is empty.\n");
    } else {
        for (int i = 0; i < player->inventory_size; i++) {
            printf("- %s: %s\n", player->inventory[i]->name, player->inventory[i]->description);
        }
    }
}

