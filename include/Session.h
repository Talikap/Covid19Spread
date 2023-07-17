#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <string>
#include "json.hpp"
#include "Graph.h"

class Agent;

enum TreeType{
    Cycle,
    MaxRank,
    Root
};

class Session{
public:
    Session ();
    Session(const std::string& path);
    // rule of 5
    virtual ~Session(); //Destructor
    void clear ();
    Session (const Session &other);  //Copy Constructor
    Session* clone (const Session&);
    Session (Session &&other); // Move Constructor
    Session& operator=(const Session &other); //Copy Assignment
    Session& operator=(Session &&other); //Move Assignment


    void simulate();
    void addAgent(const Agent& agent);
    void setGraph(const Graph& graph);
    Graph * getGraph () ;
    std ::vector <Agent*> getAgents();
    std ::vector <int> getInfectedNodes();


    void enqueueInfected(int);
    int dequeueInfected();
    const TreeType getTreeType() ;
    //bool amIInfected(int nodeInd);
    bool reachedTermination();
    int getCycle();

protected:
    Graph g;
    TreeType treeType;
    std::vector<Agent*> agents;
    std::vector <int> infectedNodes;
    int numOfAgents;
    int cycle;
    int nextInLine;
    int endOfQ;

}

#endif
;