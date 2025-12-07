#include "enemy_graph.hpp"
#include <iostream>

EnemyGraph::EnemyGraph() {
	return;
}

EnemyGraph::~EnemyGraph() {
    for (auto entry : vertices) {
        delete entry.second;
    }
    vertices.clear();
}

Vertex* EnemyGraph::addVertex(string id) {
    if (vertices.count(id) > 0) {
        cout << "ID already exists: " << id << endl;
        return nullptr;
    }
    Vertex* v = new Vertex();
    v->id = id;
	v->distance = 0;
	v->solved = false;
    vertices.insert({id, v});
    return v;
}

Vertex* EnemyGraph::searchVertex(string id) {

	Vertex* toReturn = nullptr;
	for (auto entry : vertices) {
		if (entry.first == id)
			return entry.second;
	}

    if (toReturn==nullptr) {
            throw std::invalid_argument("Vertex not found with provided id");
    }
	return toReturn;
}

/**
 * Adds an undirected edge between two vertices with specified IDs.
 */
void EnemyGraph::addEdge(string v1_id, string v2_id, string enemy_id) {
    if (v1_id == v2_id) {
        cout << "v1_id and v2_id must be different!" << endl;
        return;
    }
    if (vertices.count(v1_id) == 0) {
        cout << "No Vertex with ID: " << v1_id << endl;

        return;
    }
    if (vertices.count(v2_id) == 0) {
        cout << "No Vertex with ID: " << v2_id << endl;
        return;
    }

    Vertex* v1 = vertices.at(v1_id);
    Vertex* v2 = vertices.at(v2_id);

    for (const auto &v : v1->adjacent) {
        if (v.v->id == v2_id) {
            cout << "There is already an edge between " << v1_id << " and " << v2_id << endl;
            return;
        }
    }
    for (const auto &v : v2->adjacent) {
        if (v.v->id == v1_id) {
            cout << "There is already an edge between " << v1_id << " and " << v2_id << endl;
            return;
        }
    }

    AdjacentVertex adj_v2;
    adj_v2.v = v2;
    adj_v2.enemy_id = enemy_id;
    v1->adjacent.push_back(adj_v2);

    AdjacentVertex adj_v1;
    adj_v1.v = v1;
    adj_v1.enemy_id = enemy_id;
    v2->adjacent.push_back(adj_v1);
}

/**
 *
 */
void EnemyGraph::buildGraphFromFile(string fname) 
{
    
    ifstream ifile;
    ifile.open(fname.c_str());
    if( !ifile.is_open())
    {
        cout<<"wrong file name or path"<<endl;
        return;
    }
    string line;
    while(getline(ifile,line))
    {
        stringstream s(line);
        string type;
		string vertex_ID;
		string vertex1, vertex2, charName; 
        getline(s,type,';');
		if (type == "vertex") {
        	getline(s,vertex_ID,';'); 
			addVertex(vertex_ID);
		} else if (type == "edge") {
        	getline(s,vertex1,';');
        	getline(s,vertex2,';'); 
        	getline(s,charName,';'); 
			addEdge(vertex1, vertex2, charName);
		} else {
			cout << "line read error..." << endl;
		}
    }
    
}

/**
 *  Your implmentation should run a Dijkstra's search from the start vertext to the end
 *   - Edges are labeled with character names, 
 *   - Edge weights will be the character's highest damage item
 */
int EnemyGraph::findEasiestPath(HashTable ht) {
    if (vertices.empty())
        return -1;

    for (auto &entry : vertices) {
        entry.second->distance = INT_MAX;
        entry.second->solved = false;
    }

    Vertex* start = nullptr;
    Vertex* end = nullptr;

    try {
        start = searchVertex("start");
        end   = searchVertex("end");
    } catch (std::invalid_argument &e) {
        return -1;
    }

    start->distance = 0;

    while (true) {
        Vertex* current = nullptr;
        int minDist = INT_MAX;

        for (auto &entry : vertices) {
            Vertex* v = entry.second;
            if (!v->solved && v->distance < minDist) {
                minDist = v->distance;
                current = v;
            }
        }

        if (current == nullptr) {
            break;
        }

        current->solved = true;

        if (current == end) {
            break;
        }

        for (auto &adj : current->adjacent) {
            Vertex* neighbor = adj.v;
            if (neighbor->solved) continue;

            node* enemyNode = ht.searchCharacter(adj.enemy_id);
            if (enemyNode == nullptr) {
                continue;
            }

            ItemInfo* topItem = enemyNode->pq.peek();
            if (topItem == nullptr) continue;

            int weight = topItem->damage;

            if (current->distance != INT_MAX &&
                current->distance + weight < neighbor->distance) {
                neighbor->distance = current->distance + weight;
            }
        }
    }

    if (end->distance == INT_MAX)
        return -1;

    return end->distance;
}