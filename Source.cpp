#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include<unordered_set>
#include <algorithm>
#include<cstring>
#include<string>
#include <fstream>

using namespace std;

enum RelationshipType {
    FRIENDSHIP,
    COLLABORATION,
    MENTORSHIP,
    PROJECT_COLLABORATION,
    ACADEMIC_ADVISING,
    NUM_RELATIONSHIPS 
};

const char* RelationshipNames[] = {
    "Friendship",
    "Collaboration",
    "Mentorship",
    "Project Collaboration",
    "Academic Advising"
};

class Node {
private:
    string name;
    string role;
    vector<string> interests;
public:
    Node(const string& n, const string& r, const vector<string>& i)
        : name(n), role(r), interests(i) {}

    const string& getName() const {
        return name;
    }

    const string& getRole() const {
        return role;
    }

    const vector<string>& getInterests() const {
        return interests;
    }

};

class Edge {

private:
    Node* source;
    Node* destination;
    double weight;
    RelationshipType relationshipType;
public:
    Edge(Node* s, Node* d, double w, RelationshipType rt)
        : source(s), destination(d), weight(w), relationshipType(rt) {}

    Node* getSource() const
    {
        return source;
    }

    Node* getDestination() const
    {
        return destination;
    }

    double getWeight() const
    {
        return weight;
    }

    RelationshipType getRelationshipType() const
    {
        return relationshipType;
    }

};

class Event {


private:
    string name;
    string date;

public:

    Event(const string& n, const string& d)
        : name(n), date(d) {}

    const string& getName() const
    {
        return name;
    }

    const string& getDate() const
    {
        return date;
    }
};

class SocialNetwork {

private:
    unordered_map<string, Node*> nodes;
    vector<Edge*> edges;
    vector<Event*> events;
    unordered_map<string, vector<string>> attendance;
public:

    const unordered_map<string, Node*>& getNodes() const
    {
        return nodes;
    }

    const vector<Edge*>& getEdges() const
    {
        return edges;
    }

    void addNode(const string& name, const string& role, const vector<string>& interests)
    {
        nodes[name] = new Node(name, role, interests);
    }

    void addEdge(const string& source, const string& destination, double weight, RelationshipType relationshipType)
    {
        if (nodes.find(source) == nodes.end() || nodes.find(destination) == nodes.end())
        {
            cout << "Error: Nodes not found while adding edge.\n";
            return;
        }
        edges.push_back(new Edge(nodes[source], nodes[destination], weight, relationshipType));
    }

    void removeNode(const string& name)
    {
        auto it = nodes.find(name);

        if (it != nodes.end())
        {
            edges.erase(remove_if(edges.begin(), edges.end(),

                [name](const Edge* edge)
                {
                    return edge->getSource()->getName() == name || edge->getDestination()->getName() == name;
                }),
                edges.end());
            delete it->second;
            nodes.erase(it);
        }

        else
        {
            cout << "Error: Node with name '" << name << "' not found.\n";
        }
    }

    void removeEdge(const string& source, const string& destination)
    {
        edges.erase(remove_if(edges.begin(), edges.end(),

            [source, destination](const Edge* edge)
            {
                return edge->getSource()->getName() == source && edge->getDestination()->getName() == destination;
            }),
            edges.end());
    }

    void displayNodeDetails(const string& nodeName)
    {
        if (nodes.find(nodeName) == nodes.end())
        {
            cerr << "Error: Node not found.\n";
            return;
        }

        cout << "Details of " << nodeName << " - Role: " << nodes[nodeName]->getRole()
            << ", Interests: ";

        for (const auto& interest : nodes[nodeName]->getInterests())
        {
            cout << interest << " ";
        }

        cout << "\nRelationships: ";

        for (const auto& edge : edges)
        {
            if (edge->getSource()->getName() == nodeName)
            {

                cout << edge->getDestination()->getName() << " (Weight: " << edge->getWeight()
                    << ", Relationship Type: " << RelationshipNames[edge->getRelationshipType()] << ") ";
            }

            else if (edge->getDestination()->getName() == nodeName)
            {
                cout << edge->getSource()->getName() << " (Weight: " << edge->getWeight()
                    << ", Relationship Type: " << RelationshipNames[edge->getRelationshipType()] << ") ";
            }


        }
        cout << endl;


    }

    void displayAllNodes()
    {

        for (const auto& nodePair : nodes)
        {
            displayNodeDetails(nodePair.first);
        }
    }

    void visualizeGraph()
    {
        cout << "Visualizing Network Graph:\n";
        queue<Node*> nodeQueue;
        unordered_map<Node*, bool> visited;
        for (const auto& nodePair : nodes)
        {
            Node* currentNode = nodePair.second;
            nodeQueue.push(currentNode);
            visited[currentNode] = false;
        }
        while (!nodeQueue.empty())
        {
            Node* currentNode = nodeQueue.front();
            nodeQueue.pop();
            if (!visited[currentNode])
            {
                visited[currentNode] = true;
                cout << "Node: " << currentNode->getName() << " (Role: " << currentNode->getRole() << ")\n";

                for (const auto& edge : edges)
                {
                    if (edge->getSource() == currentNode)
                    {
                        cout << "  -> " << edge->getDestination()->getName()
                            << " (Weight: " << edge->getWeight()
                            << ", Relationship Type: " << RelationshipNames[edge->getRelationshipType()] << ")\n";
                        nodeQueue.push(edge->getDestination());

                    }

                    else if (edge->getDestination() == currentNode)
                    {

                        cout << "  <- " << edge->getSource()->getName()
                            << " (Weight: " << edge->getWeight()
                            << ", Relationship Type: " << RelationshipNames[edge->getRelationshipType()] << ")\n";
                        nodeQueue.push(edge->getSource());

                    }
                }
            }
        }
    }

    void findHighestCentrality()
    {
        unordered_map<string, double> centrality;
        for (const auto& nodePair : nodes)
        {
            string currentNodeName = nodePair.first;
            centrality[currentNodeName] = 0.0;

            queue<string> bfsQueue;
            unordered_set<string> visited;


            bfsQueue.push(currentNodeName);
            visited.insert(currentNodeName);

            while (!bfsQueue.empty())
            {

                string current = bfsQueue.front();
                bfsQueue.pop();

                for (const auto& edge : edges) {
                    if (edge->getSource()->getName() == current)
                    {
                        string neighbor = edge->getDestination()->getName();
                        if (visited.find(neighbor) == visited.end()) {
                            bfsQueue.push(neighbor);
                            visited.insert(neighbor);
                            centrality[neighbor] += 1.0;
                        }
                    }
                }


            }


        }

        auto maxCentralityIt = max_element(
            centrality.begin(),
            centrality.end(),
            [](const auto& p1, const auto& p2) { return p1.second < p2.second; });



        cout << "Individual with the highest communication centrality: "
            << maxCentralityIt->first
            << " (Centrality: " << maxCentralityIt->second << ")\n";



    }

    void identifyCollaborationNetworks()
    {
        unordered_map<string, string> community;
        unordered_map<string, double> communityInternalWeights;

        for (const auto& nodePair : nodes)
        {
            community[nodePair.first] = nodePair.first;
            communityInternalWeights[nodePair.first] = 0.0;
        }

        sort(edges.begin(), edges.end(),
            [](const Edge* e1, const Edge* e2) { return e1->getWeight() > e2->getWeight(); });

        for (const auto& edge : edges)
        {
            string sourceCommunity = community[edge->getSource()->getName()];
            string destCommunity = community[edge->getDestination()->getName()];

            if (sourceCommunity != destCommunity) {
                double internalWeight = communityInternalWeights[sourceCommunity] +
                    communityInternalWeights[destCommunity] +
                    edge->getWeight();
                double modularityGain = internalWeight - edge->getWeight();

                if (modularityGain > 0) {
                    communityInternalWeights[sourceCommunity] += edge->getWeight();
                    communityInternalWeights[destCommunity] += edge->getWeight();

                    for (auto& node : community) {
                        if (node.second == destCommunity) {
                            node.second = sourceCommunity;
                        }
                    }
                }
            }
        }

        unordered_map<string, vector<string>> communities;
        for (const auto& node : community)
        {
            communities[node.second].push_back(node.first);
        }


        int communityNumber = 1;
        for (const auto& comm : communities)
        {
            cout << "Community " << communityNumber++ << ": ";
            for (const auto& member : comm.second)
            {
                cout << member << " ";
            }


            cout << endl;
        }


    }

    void determineInfluentialByDegreeCentrality()
    {
        unordered_map<string, int> degreeCentrality;

        for (const auto& edge : edges)
        {
            degreeCentrality[edge->getSource()->getName()]++;
            degreeCentrality[edge->getDestination()->getName()]++;
        }

        int maxDegree = 0;
        vector<string> influentialNodes;

        for (const auto& node : degreeCentrality)
        {

            if (node.second > maxDegree)
            {
                maxDegree = node.second;
                influentialNodes.clear();
                influentialNodes.push_back(node.first);
            }
            else if (node.second == maxDegree)
            {
                influentialNodes.push_back(node.first);
            }


        }

        cout << "Most influential individuals by degree centrality:\n";
        for (const auto& nodeName : influentialNodes)
        {
            cout << nodeName << " (Degree Centrality: " << degreeCentrality[nodeName] << ")\n";
        }
    }
    
    void determineInfluentialByBetweennessCentrality()
    {
        unordered_map<string, double> betweennessCentrality;

        for (const auto& nodePair : nodes)
        {
            const string& source = nodePair.first;

            unordered_map<string, int> distance;
            unordered_map<string, int> numShortestPaths;
            unordered_map<string, vector<string>> predecessors;

            distance[source] = 0;
            numShortestPaths[source] = 1;

            queue<string> bfsQueue;
            bfsQueue.push(source);

            while (!bfsQueue.empty()) {
                string current = bfsQueue.front();
                bfsQueue.pop();

                for (const auto& edge : edges) {
                    if (edge->getSource()->getName() == current)
                    {
                        string neighbor = edge->getDestination()->getName();
                        if (distance.find(neighbor) == distance.end())
                        {
                            distance[neighbor] = distance[current] + 1;
                            bfsQueue.push(neighbor);
                        }

                        if (distance[neighbor] == distance[current] + 1)
                        {
                            numShortestPaths[neighbor] += numShortestPaths[current];
                            predecessors[neighbor].push_back(current);
                        }

                    }

                }



            }


            unordered_map<string, double> dependency;
            for (const auto& node : nodes) {
                dependency[node.first] = 0.0;
            }

            while (!bfsQueue.empty()) {
                string current = bfsQueue.front();
                bfsQueue.pop();

                for (const auto& predecessor : predecessors[current])
                {

                    dependency[predecessor] += (numShortestPaths[predecessor] / numShortestPaths[current]) *
                        (1 + dependency[current]);

                }

                if (current != source)
                {
                    betweennessCentrality[current] += dependency[current];
                }
            }
        }

        double maxBetweenness = 0.0;
        vector<string> influentialNodes;

        for (const auto& node : betweennessCentrality)
        {
            if (node.second > maxBetweenness)
            {


                maxBetweenness = node.second;
                influentialNodes.clear();
                influentialNodes.push_back(node.first);


            }

            else if (node.second == maxBetweenness)
            {

                influentialNodes.push_back(node.first);

            }


        }



        cout << "\nMost influential individuals by betweenness centrality:\n";
        for (const auto& nodeName : influentialNodes)
        {

            cout << nodeName << " (Betweenness Centrality: " << betweennessCentrality[nodeName] << ")\n";
        }
    }
    void identifySocialClusters()
    {
        unordered_map<string, int> communitySize;

        for (const auto& edge : edges)
        {
            communitySize[edge->getSource()->getName()]++;
            communitySize[edge->getDestination()->getName()]++;
        }


        int maxEdges = 0;
        vector<string> socialClusters;


        for (const auto& node : communitySize)
        {
            if (node.second > maxEdges)
            {
                maxEdges = node.second;
                socialClusters.clear();
                socialClusters.push_back(node.first);
            }

            else if (node.second == maxEdges)
            {
                socialClusters.push_back(node.first);
            }

        }

        cout << "Social Clusters (Nodes with Maximum Edges):\n";
        for (const auto& nodeName : socialClusters)
        {
            cout << nodeName << " (Edges: " << communitySize[nodeName] << ")\n";
        }
    }

    void addEvent(const string& name, const string& date)
    {
        events.push_back(new Event(name, date));
        attendance[name] = vector<string>();
    }

    void removeEvent(const string& name)
    {
        auto it = find_if(events.begin(), events.end(), [&name](const Event* event)
            {
                return event->getName() == name;
            });

        if (it != events.end())
        {
            attendance.erase(name);
            delete* it;
            events.erase(it);
        }
        else
        {
            cerr << "Error: Event with name '" << name << "' not found.\n";
        }


    }

    void markAttendance(const string& eventName, const string& attendeeName) {


        if (attendance.find(eventName) == attendance.end() || nodes.find(attendeeName) == nodes.end())
        {
            cerr << "Error: Event or node not found while marking attendance.\n";
            return;
        }

        attendance[eventName].push_back(attendeeName);
    }

    void displayEventDetails(const string& eventName) {
        auto it = find_if(events.begin(), events.end(), [&eventName](const Event* event) {
            return event->getName() == eventName;
            });

        if (it != events.end())
        {
            cout << "Event: " << (*it)->getName() << ", Date: " << (*it)->getDate() << "\n";
            cout << "Attendance: ";
            for (const auto& attendee : attendance[(*it)->getName()]) {
                cout << attendee << " ";
            }

            cout << "\n";
        }

        else
        {
            cerr << "Error: Event not found.\n";
        }


    }

    void storeGraphDetailsToFile(const string& filename) {
        ofstream outFile(filename);

        if (outFile.is_open()) {
            outFile << "Nodes:\n";
            for (const auto& nodePair : nodes)
            {
                const Node* currentNode = nodePair.second;
                outFile << currentNode->getName() << "," << currentNode->getRole() << ",";
                const auto& interests = currentNode->getInterests();
                for (size_t i = 0; i < interests.size(); ++i)
                {
                    outFile << interests[i];
                    if (i != interests.size() - 1)
                    {
                        outFile << ";";
                    }
                }

                outFile << "\n";
            }

            outFile << "\nEdges:\n";
            for (const auto& edge : edges)
            {
                outFile << edge->getSource()->getName() << ","
                    << edge->getDestination()->getName() << ","
                    << edge->getWeight() << ","
                    << static_cast<int>(edge->getRelationshipType()) << "\n";
            }

            outFile << "\nEvents:\n";
            for (const auto& event : events)
            {
                outFile << event->getName() << "," << event->getDate() << "\n";
            }

            outFile << "\nAttendance:\n";
            for (const auto& attendancePair : attendance)
            {
                outFile << attendancePair.first << ",";
                const auto& attendees = attendancePair.second;
                for (size_t i = 0; i < attendees.size(); ++i)
                {
                    outFile << attendees[i];
                    if (i != attendees.size() - 1)
                    {
                        outFile << ";";
                    }
                }

                outFile << "\n";
            }

            outFile.close();
            cout << "Graph details have been stored in the file: " << filename << endl;
        }
        else
        {
            cerr << "Unable to open file: " << filename << endl;
        }
    }

    void detectNegativeInfluencePaths(const string& source)
    {
        unordered_map<string, double> distance;
        unordered_map<string, string> predecessor;

        for (const auto& nodePair : nodes) {
            distance[nodePair.first] = numeric_limits<double>::infinity();
            predecessor[nodePair.first] = "";
        }

        distance[source] = 0.0;
        for (size_t i = 0; i < nodes.size() - 1; ++i)
        {
            for (const auto& edge : edges)
            {
                const string& u = edge->getSource()->getName();
                const string& v = edge->getDestination()->getName();
                double weight = edge->getWeight();

                if (distance[u] + weight < distance[v])
                {
                    distance[v] = distance[u] + weight;
                    predecessor[v] = u;
                }
            }
        }
        for (const auto& edge : edges)
        {
            const string& u = edge->getSource()->getName();
            const string& v = edge->getDestination()->getName();
            double weight = edge->getWeight();

            if (distance[u] + weight < distance[v])
            {
                cout << "Negative influence path detected from " << source << " to " << v << ".\n";

                vector<string> cycle;
                string current = v;
                while (current != "")
                {
                    cycle.push_back(current);
                    current = predecessor[current];
                    if (current == v)
                    {
                        cycle.push_back(current);
                        break;
                    }
                }


                cout << "Cycle: ";
                for (auto it = cycle.rbegin(); it != cycle.rend(); ++it)
                {
                    cout << *it << " ";
                }
                cout << endl;
            }

        }
    }

    void findMinimumSpanningTree(const string& startNode)
    {
        unordered_set<Node*> visited;
        priority_queue<pair<double, Node*>, vector<pair<double, Node*>>, greater<>> pq;
        unordered_map<Node*, Node*> parent;

        if (nodes.find(startNode) == nodes.end())
        {
            cerr << "Error: Start node not found.\n";
            return;
        }

        Node* start = nodes[startNode];
        pq.push({ 0.0, start });

        while (!pq.empty())
        {
            Node* current = pq.top().second;
            double cost = pq.top().first;
            pq.pop();

            if (visited.find(current) != visited.end())
            {
                continue;
            }

            visited.insert(current);

            for (const auto& edge : edges)
            {
                if (edge->getSource() == current || edge->getDestination() == current)
                {
                    Node* neighbor = edge->getSource() == current ? edge->getDestination() : edge->getSource();
                    if (visited.find(neighbor) == visited.end())
                    {
                        double edgeWeight = edge->getWeight();
                        if (edgeWeight < cost || parent.find(neighbor) == parent.end())
                        {
                            pq.push({ edgeWeight, neighbor });
                            parent[neighbor] = current;
                        }
                    }
                }
            }
        }
        cout << "Minimum Spanning Tree from " << startNode << ":\n";
        for (const auto& p : parent)
        {
            if (p.second != nullptr) {
                cout << "Edge: " << p.second->getName() << " - " << p.first->getName() << "\n";
            }
        }
    }

    ~SocialNetwork() {
        for (auto& nodePair : nodes) {
            delete nodePair.second;
        }

        for (auto& edge : edges) {
            delete edge;
        }
        for (auto& event : events) {
            delete event;
        }
    }
};

int main() {

    SocialNetwork socialNetwork;
    string filename;
    bool exitMenu = false;
    int choice;

    while (!exitMenu) {
        cout << "\nSocial Network Menu:\n";
        cout << "1. Display All Nodes\n";
        cout << "2. Visualize Graph\n";
        cout << "3. Find Highest Centrality\n";
        cout << "4. Identify Collaboration Networks\n";
        cout << "5. Determine Influential by Degree Centrality\n";
        cout << "6. Determine Influential by Betweenness Centrality\n";
        cout << "7. Identify Social Clusters\n";
        cout << "8. Display Event Details\n";
        cout << "9. Add Node\n";
        cout << "10. Add Edge\n";
        cout << "11. Remove Node\n";
        cout << "12. Remove Edge\n";
        cout << "13. Store Graph Details in File\n";
        cout << "14. Detect Negative Influence Paths\n";
        cout << "15. Find Minimum Spanning Tree or shortest path to someone\n";
        cout << "16. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
        case 1: {

            socialNetwork.displayAllNodes();
            break;

        }


        case 2: {

            socialNetwork.visualizeGraph();
            break;

        }


        case 3: {

            socialNetwork.findHighestCentrality();
            break;

        }


        case 4: {

            socialNetwork.identifyCollaborationNetworks();
            break;

        }


        case 5: {
            socialNetwork.determineInfluentialByDegreeCentrality();
            break;
        }


        case 6: {


            socialNetwork.determineInfluentialByBetweennessCentrality();
            break;
        }


        case 7: {

            socialNetwork.identifySocialClusters();
            break;
        }


        case 8: {

            cout << "Enter event name: ";
            string eventName;
            cin.ignore();
            getline(cin, eventName);
            socialNetwork.displayEventDetails(eventName);
            break;
        }


        case 9: {

            string name, role;
            vector<string> interests;
            int numInterests;

            cout << "Enter name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter role: ";
            getline(cin, role);
            cout << "Enter number of interests: ";
            cin >> numInterests;
            cin.ignore();

            for (int i = 0; i < numInterests; ++i)
            {
                string interest;
                cout << "Enter interest " << i + 1 << ": ";
                getline(cin, interest);
                interests.push_back(interest);
            }

            socialNetwork.addNode(name, role, interests);
            break;


        }



        case 10: {


            string source, destination;
            double weight;
            int relationshipType;

            cout << "Enter source node: ";
            cin.ignore();
            cin >> source;
            //getline(cin, source);
            cout << "Enter destination node: ";
            cin.ignore();
            cin >> destination;
            //getline(cin, destination);
            cout << "Enter weight: ";
            cin >> weight;
            cout << "Enter relationship type (0-FRIENDSHIP, 1-COLLABORATION, etc.): ";
            cin >> relationshipType;

            socialNetwork.addEdge(source, destination, weight, static_cast<RelationshipType>(relationshipType));
            break;
        }



        case 11: {
            string name;
            cout << "Enter node name to remove: ";
            cin.ignore();
            getline(cin, name);
            socialNetwork.removeNode(name);
            break;
        }

        case 12: {
            string source, destination;
            cout << "Enter source node: ";
            cin.ignore();
            getline(cin, source);
            cout << "Enter destination node: ";
            cin.ignore();
            getline(cin, destination);
            socialNetwork.removeEdge(source, destination);
            break;
        }


        case 13: {

            cout << "Enter filename to store graph details: ";
            cin.ignore();
            getline(cin, filename);

            socialNetwork.storeGraphDetailsToFile(filename);
            break;
        }



        case 14: {
            string sourceNode;
            cout << "Enter source node name to detect negative influence paths: ";
            cin.ignore();
            getline(cin, sourceNode);
            socialNetwork.detectNegativeInfluencePaths(sourceNode);
            break;
        }

        case 15: {
            string startNode;
            cout << "Enter the starting node: ";
            cin >> startNode;
            socialNetwork.findMinimumSpanningTree(startNode);
            break;
        }

        case 16: {
            exitMenu = true;
            break;
        }

        default: {
            cout << "Invalid choice! Please try again.\n";
            break;
        }
        }
    }
    return 0;
}