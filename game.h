#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <dirent.h>


typedef struct Room {
    int x, y;
    char *name;
    char *description;
    struct Room *up, *down, *left, *right;
    int has_creature, creature_health, has_trap, trap_damage;
    char *item, *note;
    int note_read;
    int visited;
} Room;

typedef struct Item {
    char *name, *description;
    int effect_value, type;
} Item;

typedef struct Player {
    int coins, health, defense, strength;
    Item **inventory;
    int inventory_size, inventory_capacity;
    Room *current_room;
    int time_remaining;
} Player;

typedef struct MarketItem {
    char *name, *description;
    int cost, effect_value, type;
} MarketItem;


MarketItem market_items[] = {
    {"Small Health Potion", "Restores 20 health.", 10, 20, 0},
    {"Large Health Potion", "Restores 50 health.", 25, 50, 0},
    {"Sword", "A sharp blade that increases strength.", 50, 15, 1},
    {"Armor", "Sturdy armor that increases defense.", 40, 10, 2},
    {"Shield", "A shield to block attacks.", 30, 8, 2}
};

int market_items_count = sizeof(market_items) / sizeof(MarketItem);


void move(Player *player, const char *direction);
void look(Player *player);
void inventory(Player *player);
void pickup(Player *player, const char *item);
void attack(Player *player);
void check_trap(Player *player);
void read_note(Player *player);
void use_item(Player *player, const char *item_name);
void save_game(Player *player, const char *filepath);
void load_game(Player *player, const char *filepath, Room *rooms[], int room_count);
void list_saved_games();
Room *create_room(const char *name, const char *description, int x, int y);
void link_rooms(Room *room1, Room *room2, const char *direction);
void free_dynamic_memory(Room *rooms[], int room_count);
void free_inventory(Player *player);
Item *create_item(const char *name, const char *description, int effect_value, int type);
void creature_drop(Player *player);
void display_map(Room *rooms[], int room_count, Player *player);
void display_market();
void buy_item(Player *player, const char *item_name);

#endif // GAME_H
