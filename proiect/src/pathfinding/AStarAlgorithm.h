#pragma once

#include "IPathAlgorithm.h"
#include "../map/Map.h"

#include <vector>
#include <queue>
#include <map>
#include <cmath>
#include <algorithm>

using namespace std;

class AStarAlgorithm : public IPathAlgorithm {
private:
  struct Node {
    int x, y, g, h;
    Node* parent;
    Node(int x, int y, int g = 0, int h = 0, Node* p = nullptr) 
      : x(x), y(y), g(g), h(h), parent(p) {}
    int f() const { return g + h; }
  };

  struct CompareNode {
    bool operator()(Node* a, Node* b) { return a->f() > b->f(); }
  };

public:
  vector<pair<int, int>> calculatePath(int startX, int startY, int endX, int endY, const Map& map) override {
    priority_queue<Node*, vector<Node*>, CompareNode> openSet;
    std::map<pair<int, int>, Node*> allNodes;

    openSet.push(new Node(startX, startY, 0, abs(startX - endX) + abs(startY - endY)));
    allNodes[{startX, startY}] = openSet.top();

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    Node* targetNode = nullptr;

    while(!openSet.empty()) {
      Node* current = openSet.top();
      openSet.pop();

      if(current->x == endX && current->y == endY) {
        targetNode = current;
        break;
      }

      for(int i = 0; i < 4; i++) {
        int nr = current->x + dr[i];
        int nc = current->y + dc[i];

        if(nr >= 0 && nr < map.getRows() && nc >= 0 && nc < map.getCols()) {
          if(map.getCell(nr, nc) == CellType::WALL) continue;

          int newG = current->g + 1;
          if(allNodes.find({nr, nc}) == allNodes.end() || newG < allNodes[{nr, nc}]->g) {
            Node* neighbor = new Node(nr, nc, newG, abs(nr - endX) + abs(nc - endY), current);
            allNodes[{nr, nc}] = neighbor;
            openSet.push(neighbor);
          }
        }
      }
    }

    vector<pair<int, int>> path;
    if(targetNode) {
      Node* temp = targetNode;
      while(temp->parent != nullptr) {
        path.push_back({temp->x, temp->y});
        temp = temp->parent;
      }
      reverse(path.begin(), path.end());
    }

    for(auto const& [key, val] : allNodes) delete val;
    return path;
  }
};