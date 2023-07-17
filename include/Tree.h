
#ifndef TREE_H_
#define TREE_H_

#include <vector>
#include "Session.h"

class Session;

class Tree{
public:
    Tree();
    Tree(int rootLabel);
    virtual ~Tree();//Destructor
    void clear ();
    Tree (const Tree &other);  //Copy Constructor
    const Tree& operator=(const Tree &other); //Copy Assignment
    virtual Tree * clone() const=0;
    Tree (Tree &&other); // Move Constructor
    Tree& operator=(Tree &&other); //Move Assignment

    // gets
    const int getNode () const;
    std ::vector <Tree*> getChildren() const;

    void addChild (const Tree& child);

    static Tree* createTree( int rootLabel,Session &session);
    virtual int traceTree()=0;
    static Tree* buildBFSRec (Tree* father,Session &session);

protected:
    int node;
    std::vector<Tree*> children;
}

;
class RootTree: public Tree{
public:
    RootTree(int rootLabel);
    virtual ~RootTree();
    virtual RootTree * clone() const;
    virtual int traceTree();
}
;

class MaxRankTree: public Tree{
public:
    MaxRankTree(int rootLabel);
    virtual int traceTree();
    virtual ~MaxRankTree();
    virtual MaxRankTree * clone() const;

}
;

class CycleTree: public Tree{
public:

    CycleTree(int rootLabel, int currCycle);
    virtual ~CycleTree();
    virtual  CycleTree* clone() const;
    virtual int traceTree();
    int traceTreeRec (CycleTree* curr , int C);

private:
    int currCycle;

}
;

#endif