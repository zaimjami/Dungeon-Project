#include<iostream>
#include <vector>
#include<fstream>
#include <cstdlib>
#include <ctime>
#include <chrono>

#include "hash.hpp"
#include "PriorityQueue.hpp"
#include "enemy_graph.hpp"

using namespace std;
using namespace std::chrono;

void displayMenu()
{
    cout<<"------------------"<<endl;
    cout<<"1: Build the datastructure (call it only once)"<<endl;
    cout<<"2: Add a new item"<<endl;
    cout<<"3: Peek most powerful item from character"<<endl;
    cout<<"4: Pop most powerful item from character"<<endl;
    cout<<"5: Print all items for character"<<endl;
    cout<<"6: Get number of collisions"<<endl;
    cout<<"7: Print the table"<<endl;
    cout<<"8: Find easiest route through dungeon"<<endl;
    cout<<"9: Exit"<<endl;
    cout<<"------------------"<<endl;

}

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        cout<<"need correct num of arg"<<endl;
        return 0;
    }
    string fname = argv[1];
    int tableSize = stoi(argv[2]);
    
    int ch = 0;
    string chs;
    HashTable ht(tableSize);
    bool built = false;

    while(ch != 9)
    {
        displayMenu();
        cout<<"Give your choice >> ";
        if (!getline(cin, chs) || chs.size() == 0) {
            continue;
        }
        ch = stoi(chs);
        switch (ch)
        {
            case 1:{ 
                if (!built) {
                    ht.buildBulk(fname);
                    built = true;
                }
                break;
            }
            case 2:{ 
                ItemInfo item;
                string dmgStr;

                cout << "CharacterName: ";
                getline(cin, item.characterName);
                cout << "ItemName: ";
                getline(cin, item.itemName);
                cout << "Damage: ";
                getline(cin, dmgStr);
                item.damage = stoi(dmgStr);
                cout << "Comment: ";
                getline(cin, item.comment);

                ht.insertItem(item);
                break;
            }
            case 3:{ 
                cout << "Character name: ";
                string characterName;
                getline(cin, characterName);

                node* result = ht.searchCharacter(characterName);
                if (result == nullptr || result->pq.isEmpty()) {
                    cout << "no record found" << endl;
                } else {
                    ItemInfo* top = result->pq.peek();
                    cout << "retrieved result" << endl;
                    cout << "Character: " << result->characterName << endl;
                    cout << "Item: " << top->itemName << endl;
                    cout << "Damage: " << top->damage << endl;
                    cout << "Comment: " << top->comment << endl;
                }
                break;
			}
            case 4:{ 
                cout << "Character name:";
                string characterName;
                getline(cin, characterName);
                ht.deleteEntry(characterName);
                break;
            }
            case 5:{ 
                cout << "Character name:";
                string characterName;
                getline(cin, characterName);

                node* result = ht.searchCharacter(characterName);
                if (result == nullptr || result->pq.isEmpty()) {
                    cout << "no record found" << endl;
                } else {
                    cout << "Character: " << result->characterName << endl;
                    result->pq.print();
                }
                break;
			}
            case 6: { 
                cout << "Number of collision: " << ht.getNumCollision() << endl;
                break;
			}
            case 7: { 
                ht.printTable();
                break;
			}
			case 8:{
				cout << "Input dungeon(file name): " << endl;
				string dungeonFile;
				getline(cin, dungeonFile);
				EnemyGraph G;
				G.buildGraphFromFile(dungeonFile);
				cout << G.findEasiestPath(ht) << endl;
				break;
			}
			case 9:
				cout << "Goodbye..." << endl;
				break;
       
            default:
                cout<<"Give a valid entry"<<endl;
                break;
        }
    }
}
