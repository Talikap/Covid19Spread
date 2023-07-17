
#include "Session.h"
#include <fstream>
#include "Agent.h"
#include <iostream>



Session :: Session () : g() ,treeType(), agents () , infectedNodes(),numOfAgents(),cycle(),nextInLine(),endOfQ() {}

Session::Session (const std::string& path) : g() , treeType(),agents (),infectedNodes(),numOfAgents(0),cycle(1),nextInLine(0),endOfQ(0) {
    std::ifstream i(path);
    nlohmann::json j;
    i >>j;
    std::vector<std::vector<int>> matrix = j["graph"];
    g=matrix;
    if (j["tree"]=="M")
        treeType=MaxRank;
    else{
        if (j["tree"]=="C"){
            treeType=Cycle;}
        else{
            treeType=Root;}}

    for (auto& element : j["agents"] ){
        if(element[0]=="C"){
            addAgent (ContactTracer());
        }
        else{
            addAgent(Virus(element[1]));
            g.spreadVirus(element[1]);
        }
    }
}

//rule of 5

Session :: ~Session() {
    clear();
}

void Session :: clear (){
    if (!agents.empty()){
        for (Agent* curr : agents){
            delete curr;
        }
    }
    agents.clear();
}

Session :: Session (const Session &other) : g(other.g),treeType() ,agents(),infectedNodes(other.infectedNodes),numOfAgents(other.numOfAgents),cycle(other.cycle),nextInLine(other.nextInLine),endOfQ(other.endOfQ){
    for (Agent * curr : other.agents){
        agents.push_back(curr->clone());
    }
    treeType=other.treeType;
}

Session* Session ::clone(const Session &session)  {
    g=session.g;
    for (Agent * curr : session.agents){
        agents.push_back(curr->clone());
    }
    infectedNodes=session.infectedNodes;
    treeType=session.treeType;
    numOfAgents=session.numOfAgents;
    cycle=session.cycle;
    nextInLine=session.nextInLine;
    endOfQ=session.endOfQ;
    return this;
}

Session :: Session(Session &&other) : g (other.g),treeType(), agents(),infectedNodes(other.infectedNodes),numOfAgents(other.numOfAgents),cycle(other.cycle),nextInLine(other.nextInLine),endOfQ(other.endOfQ)
{
    for (Agent * curr : other.agents) {
        agents.push_back(curr);
    }
    other.agents.clear();
}

Session& Session :: operator=(const Session &other){
    if (this == &other) {
        return *this;
    }
    clear();
    return *clone (other);
}

Session& Session ::operator=(Session &&other) {
    if (this==&other){
        return *this;
    }
    clear();
    clone(other);
    other.clear();
    return *this;
}

const TreeType Session ::getTreeType() {
    return treeType;
}

Graph * Session ::getGraph()  {
    return &g;
}

std::vector<Agent *>  Session ::getAgents() {
    return agents;
}

std ::vector <int> Session ::getInfectedNodes () {
    return infectedNodes;
}

void Session :: setGraph (const Graph& graph){
    g=graph;
}

int  Session ::dequeueInfected() {
    if (nextInLine<endOfQ){
        int firstInfected=infectedNodes[nextInLine];
        ++nextInLine;
        return firstInfected;
    }
    else{
        return -1;
    }
}

void Session::enqueueInfected(int toAdd) {
    infectedNodes.push_back(toAdd);
    ++endOfQ;
}

void Session:: simulate () {
    bool firstCycle=true;
    while (firstCycle|!reachedTermination()){
        firstCycle=false;
        int activeAgents=numOfAgents;
        for (int i = 0; i < activeAgents; ++i) {
            agents[i]->act(*this);

        }
        ++cycle;
    }

    nlohmann::json output;
    output["final graph"] = getGraph()->getMatrix();
    output["sick nodes"] = getInfectedNodes();
    std::ofstream o("./output.json");
    o << output;
    o.close();
}

void Session ::addAgent(const Agent &agent){
    Agent* newAgent=agent.clone();
    agents.push_back(newAgent);
    ++numOfAgents;
}

int Session::getCycle() {
    return cycle;
}

bool Session::reachedTermination() {
    unsigned int numberOfNodes = g.getMatrix().size();
    for (unsigned int i = 0; i < numberOfNodes; ++i) {
        if (g.isCarrier(i)) {
            for (unsigned int j = 0; j < numberOfNodes; ++j) {
                if (g.getMatrix()[i][j] == 1 && (!g.isInfected(j)))
                    return false;
            }
        }
        else
            for (unsigned int k = 0; k < numberOfNodes; ++k) {
                if (g.getMatrix()[i][k] == 1 && (g.isInfected(k)))
                    return false;
            }
    }

    return true;
}

