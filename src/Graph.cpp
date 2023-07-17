
#include "Graph.h"
#include "Tree.h"

Graph:: Graph () : edges (), carriers(),sickNodes(){ }

Graph::Graph(std::vector<std::vector<int>> matrix) : edges(matrix),carriers(edges.size(),false),sickNodes(edges.size(),false){}

Graph ::~Graph() {
    clear();
}

void Graph ::clear() {

    edges.clear();
    carriers.clear();
    sickNodes.clear();
}

Graph ::Graph(const Graph &other)  : edges(other.edges) , carriers(other.carriers), sickNodes(other.sickNodes) {
}


Graph* Graph :: clone (const Graph & graph) {
    edges=graph.edges;
    carriers=graph.carriers;
    sickNodes=graph.sickNodes;
    return this;
}


void  Graph ::infectNode(const int nodeInd){
    sickNodes[nodeInd]=true;
}

bool Graph ::isInfected(const int nodeInd) {
    return sickNodes[nodeInd];
}
void  Graph ::spreadVirus(const int nodeInd){
    carriers[nodeInd]=true;
}

bool Graph ::isCarrier(const int nodeInd) {
    return carriers[nodeInd];
}
void Graph::removeEdge(int i, int j) {
    edges[i][j]=0;
    edges[j][i]=0;
}

std::vector<std::vector<int>> Graph ::  getMatrix ()  {
    return edges;
}

Tree* Graph ::BFS(int rootLabel, Session& session) {
    Tree* notnull= Tree::createTree (-1,session);
    std::vector<Tree *> visited(session.getGraph()->getMatrix().size(), nullptr);
    visited[rootLabel]=notnull;
    Tree* toReturn= buildBFSRec(notnull,session,rootLabel,visited);
    delete notnull;
    return toReturn;
}

Tree *Graph::buildBFSRec( Tree * parent,Session &session, int index, std::vector<Tree*> &visited) {
    Tree *curr = Tree::createTree(index, session);
    for (unsigned int i = 0; i < edges.size(); i++) {
        if (edges[curr->getNode()][i] == 1 && (visited[i] == nullptr)) {
            visited[i] = curr;
        }
    }
    for (unsigned int i = 0; i < edges.size(); i++) {
        if (visited[i] == curr) {
            Tree* temp=buildBFSRec(curr,session, i, visited);
            curr->addChild(*temp);
            delete temp;
        }
    }
    return curr;
}
