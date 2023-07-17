
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>

class Session;
class Tree;


class Graph{
public:
    Graph ();
    Graph(std::vector<std::vector<int>> matrix);
    ~Graph(); //Destructor
    void clear ();
    Graph (const Graph &other);  //Copy Constructor
    Graph* clone (const Graph&);

    std::vector<std::vector<int>> getMatrix () ;

    Tree* BFS(int rootLabel, Session &session);
    Tree* buildBFSRec(Tree* ,Session&, int , std::vector<Tree*>& );
    void infectNode(int nodeInd);
    bool isInfected(const int nodeInd);
    void spreadVirus(int nodeInd);
    bool isCarrier(int nodeInd);
    void removeEdge(int i , int j);

private:
    std::vector<std::vector<int>> edges;
    std::vector<bool> carriers;
    std::vector<bool> sickNodes;
}

#endif
;