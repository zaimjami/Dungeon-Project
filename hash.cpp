#include<iostream>
#include "hash.hpp"
#include<sstream>

using namespace std;

node* HashTable::createNode(string charName, node* nextNode)
{
    node* newNode = new node;
    newNode->characterName = charName;
    newNode->next = nextNode;
    return newNode;
}

HashTable::HashTable(int bsize)
{
    tableSize = bsize;
    table = new node*[tableSize];
    for (int i = 0; i < tableSize; i++)
    {
        table[i] = nullptr;
    }
    numCollision = 0;
}

void HashTable::printTable()
{
    for (int i = 0; i < tableSize; i++)
    {
        cout << "table[" << i << "]:";

        node* temp = table[i];
        if (temp != nullptr)
            cout << " ";

        while (temp != nullptr)
        {
            cout << temp->characterName;
            if (temp->next != nullptr)
                cout << ", ";
            temp = temp->next;
        }
        cout << endl;
    }
}

unsigned int HashTable::hashFunction(string charName)
{
    unsigned int sum = 0;
    for (char c : charName)
        sum += static_cast<unsigned char>(c);
    return sum % tableSize;
}

node* HashTable::searchCharacter(string charName)
{
    unsigned int index = hashFunction(charName);
    node* temp = table[index];

    while (temp != nullptr)
    {
        if (temp->characterName == charName)
            return temp;
        temp = temp->next;
    }
    return nullptr;
}

void HashTable::insertItem(ItemInfo newItem)
{
    unsigned int index = hashFunction(newItem.characterName);
    node* head = table[index];

    node* temp = head;
    while (temp != nullptr)
    {
        if (temp->characterName == newItem.characterName)
        {
            temp->pq.insertElement(newItem);
            return;
        }
        temp = temp->next;
    }

    node* newNode = createNode(newItem.characterName, nullptr);
    newNode->pq.insertElement(newItem);

    if (head == nullptr)
    {
        table[index] = newNode;
    }
    else
    {
        numCollision++;
        newNode->next = head;
        table[index] = newNode;
    }
}

void HashTable:: buildBulk(string fname)
{
    ifstream file(fname);
    if (!file.is_open())
    {
        cout << "wrong file name or path" << endl;
        return;
    }

    string line;
    while (getline(file, line))
    {
        if (line.empty()) continue;

        stringstream ss(line);
        ItemInfo item;
        string damageStr;

        getline(ss, item.characterName, ';');
        getline(ss, item.itemName, ';');
        getline(ss, damageStr, ';');
        getline(ss, item.comment); // rest of line

        if (item.characterName == "" || item.itemName == "" || damageStr == "")
            continue;

        item.damage = stoi(damageStr);
        insertItem(item);
    }
}

void HashTable::deleteEntry(string charName) {
    node* target = searchCharacter(charName);
    if (target == nullptr)
    {
        cout << "no record found" << endl;
        return;
    }

    if (target->pq.isEmpty())
    {
        cout << "PQ emptied..." << endl;
        return;
    }

    target->pq.pop();

    if (target->pq.isEmpty())
    {
        unsigned int index = hashFunction(charName);
        node* curr = table[index];
        node* prev = nullptr;

        while (curr != nullptr && curr != target)
        {
            prev = curr;
            curr = curr->next;
        }

        if (curr != nullptr)
        {
            if (prev == nullptr)
            {
                table[index] = curr->next;
            }
            else
            {
                prev->next = curr->next;
            }
            delete curr;
        }

        cout << "PQ emptied..." << endl;
    }
}
