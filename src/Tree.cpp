
#include <iostream>
#include "Tree.h"
using namespace std;


Tree ::Tree () : node(0) ,children(){}

Tree ::Tree(int rootLabel) : node(rootLabel),children(){}

Tree ::~Tree() {
    clear();
}


Tree ::Tree (const Tree &other) : node(other.node), children() {
    for (Tree* curr : other.children){
        children.push_back(curr->clone());
    }
}

const Tree& Tree :: operator=(const Tree &other){
    if (this == &other) {
        return *this;
    }
    clear();
    node=other.node;
    for (Tree* curr : other.children){
        children.push_back(curr->clone());
    }
    return *this;
}

void Tree ::clear() {
    for (Tree * curr : children){
        delete curr;
    }

    children.clear();

}

Tree :: Tree (Tree &&other) : node(other.node) ,children{} {

    for (Tree *curr : other.children) {
        children.push_back(curr);
    }
    other.clear();
}

Tree& Tree :: operator= (Tree &&other) {
    if (this==&other){
        return *this;
    }
    clear();
    node = other.node;
    for (unsigned int i = 0; i < other.children.size(); i++) {
        std :: cout << children[i]->getNode() << std ::endl;
        children[i] = other.children[i];
    }
    other.clear();
    for (unsigned int i = 0; i < other.children.size(); i++) {
        std::cout << children[i]->getNode() << std::endl;
        children[i] = other.children[i];
    }
    return *this;
}


std::vector<Tree *> Tree ::getChildren() const {
    return children;
}

const int Tree ::getNode() const {
    return node;
}

void Tree ::addChild(const Tree& child)  {
    Tree * copy = child.clone();
    children.push_back(copy);
}

Tree *Tree::createTree(int rootLabel,Session &session) {
    TreeType type = session.getTreeType();
    std::vector<std::vector<int>> neighbors = session.getGraph()->getMatrix();
    if (type == Cycle) {
        CycleTree *toReturn = new CycleTree(rootLabel, session.getCycle());
        return toReturn;
    } else {
        if (type == MaxRank) {
            MaxRankTree *toReturn = new MaxRankTree(rootLabel);
            return toReturn;
        } else {
            RootTree *toReturn = new RootTree(rootLabel);
            return toReturn;
        }
    }
}

//Root Tree------------------------------------------------

RootTree ::RootTree(int rootLabel): Tree(rootLabel){}

RootTree * RootTree :: clone() const {
    RootTree* clone = new RootTree(this->node);
    return clone;
}

RootTree:: ~RootTree() {
    clear();
}

int RootTree ::traceTree() {
    return node;
}

// Max Rank Tree-----------------------------------------
MaxRankTree ::MaxRankTree(int rootLabel) : Tree(rootLabel) {}

MaxRankTree :: ~MaxRankTree() {
    clear();
}

MaxRankTree * MaxRankTree ::clone() const {
    MaxRankTree* clone= new MaxRankTree(this->node);
    for (unsigned int i=0;i<this->children.size();i++){
        Tree* copy= this->getChildren()[i];
        clone->addChild (*copy);
    }
    return clone;
}


int MaxRankTree  ::traceTree() {
    // go over the tree and return the node with
    //biggest number of children. else, node with
    //smallest depth. else, left most node.
    std::vector <MaxRankTree*> Q;
    MaxRankTree* currMax=this;
    MaxRankTree* curr=this;
    Q.push_back(curr);
    while (!Q.empty()) {
        curr = Q[0];
        if (curr->getChildren().size()>currMax->getChildren().size()){
            currMax=curr;
        }
        Q.erase(Q.begin());
        for (unsigned int i = 0; i < curr->children.size(); i++){
            MaxRankTree * toAdd = (MaxRankTree*)(curr->children[i]);
            Q.push_back(toAdd);
        }
    }
    int maxNode=currMax->getNode();
    return maxNode;
}

CycleTree ::CycleTree(int rootLabel, int curr) : Tree(rootLabel) , currCycle(curr) {}

CycleTree* CycleTree ::clone() const {
    CycleTree* clone= new CycleTree(this->node,this->currCycle);
    for (unsigned int i=0;i<this->children.size();i++){
        clone->addChild(*this->getChildren()[i]);
    }
    return clone;
}
CycleTree ::~CycleTree() {
    clear();
}

int CycleTree ::traceTree() {
    // return the c'th node in the tree
    int C = currCycle;
    std::vector<CycleTree *> Q;
    CycleTree *curr = this;
    Q.push_back(curr);
    while (!Q.empty()) {
        curr = Q[0];
        if (C == 0) { return curr->getNode(); }
        Q.erase(Q.begin());
        if (curr->getChildren().size() > 0) {
            CycleTree *toAdd = (CycleTree *) curr->getChildren()[0];
            Q.push_back(toAdd);
            --C;
        }
    }
    int toReturn = curr->getNode();
    return toReturn;
}