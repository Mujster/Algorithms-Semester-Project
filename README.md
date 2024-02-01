# Algorithms-Semester-Project

# Social Network Analysis System for FAST-NUCES

## Introduction

The goal of this project is to design and implement a comprehensive social network analysis system within the context of FAST-NUCES. The system is developed using the C++ programming language and incorporates graph theory concepts. The primary objective is to model relationships and interactions among individuals within the university setting, including students, faculty, and staff members. The analysis aims to uncover intricate social structures, communication patterns, influential figures, collaboration networks, and community clusters within the university.

The implemented C++ program leverages graph theory concepts to construct a social network representation. It utilizes classes such as Node, Edge, Event, and SocialNetwork to encapsulate individuals, relationships, events, and the overall social structure. The program incorporates various functionalities to add individuals to the network, establish relationships, visualize the network graph, and perform in-depth analyses using graph algorithms.

Through this implementation, the program enables exploration into different relationship types, communication patterns, collaboration networks, influence metrics, and community structures within the university. This endeavor aims to provide insights into the dynamics and interconnections within the FAST-NUCES social network, facilitating a deeper understanding of the university's social fabric.

The program's design and functionalities allow for an examination of the social dynamics within the university, contributing to the exploration of social network analysis methodologies in academic environments. This report details the implementation, insights gained, challenges encountered, and performance analysis of the developed system.

## Code Structure and Functionality

### Class Overview:

1. **Node Class:**
   - Attributes:
     - `name`: Represents the name of the individual in the university.
     - `role`: Indicates the role of the individual (student, faculty, etc.).
     - `interests`: Stores a list of interests associated with the individual.
   - Methods:
     - `Node(name, role, interests)`: Constructor to initialize a node with a name, role, and interests.
     - `getName()`: Retrieves the name of the node.
     - `getRole()`: Retrieves the role of the node.
     - `getInterests()`: Retrieves the interests associated with the node.

2. **Edge Class:**
   - Attributes:
     - `source`: Pointer to the source Node of the edge.
     - `destination`: Pointer to the destination Node of the edge.
     - `weight`: Represents the weight of the relationship between nodes.
     - `relationshipType`: Enumerates the type of relationship between nodes.
   - Methods:
     - `Edge(source, destination, weight, relationshipType)`: Constructor to create an edge between nodes with given attributes.
     - `getSource()`: Retrieves the source node of the edge.
     - `getDestination()`: Retrieves the destination node of the edge.
     - `getWeight()`: Retrieves the weight of the edge.
     - `getRelationshipType()`: Retrieves the type of relationship between nodes.

3. **Event Class:**
   - Attributes:
     - `name`: Represents the name of the event.
     - `date`: Indicates the date of the event.
   - Methods:
     - `Event(name, date)`: Constructor to initialize an event with a name and date.
     - `getName()`: Retrieves the name of the event.
     - `getDate()`: Retrieves the date of the event.

4. **SocialNetwork Class:**
   - Attributes:
     - `nodes`: Unordered map storing nodes with their names as keys.
     - `edges`: Vector storing edges between nodes.
     - `events`: Vector storing information about university events.
     - `attendance`: Unordered map tracking event attendance.
   - Methods:
     - `addNode(name, role, interests)`: Adds a new node to the social network.
     - `addEdge(source, destination, weight, relationshipType)`: Adds an edge between nodes with specified attributes.
     - `removeNode(name)`: Removes a node from the social network.
     - `removeEdge(source, destination)`: Removes an edge between specified nodes.
     - Other methods handle display, visualization, analysis of communication patterns, collaboration networks, influential individuals, social clusters, and event details within the network.

### Graph Operations:

#### Key Methods:

- `addNode(name, role, interests)`: Adds a new node to the social network with the given name, role, and interests.
- `addEdge(source, destination, weight, relationshipType)`: Establishes an edge between two nodes with the specified weight and relationship type.
- `removeNode(name)`: Removes a node from the social network along with all associated edges involving that node.
- `removeEdge(source, destination)`: Removes the edge between two specified nodes.
- `displayNodeDetails(nodeName)`: Displays details of a specific node including its role, interests, and relationships with other nodes.
- `displayAllNodes()`: Displays details of all nodes in the social network.
- `visualizeGraph()`: Visualizes the network graph using a breadth-first search (BFS) traversal algorithm.
- `findHighestCentrality()`: Identifies the individual with the highest communication centrality within the network using BFS.
- `identifyCollaborationNetworks()`: Identifies collaboration networks by analyzing relationships between nodes based on edge weights.

- `determineInfluentialByDegreeCentrality()`: Determines the most influential individuals based on their degree centrality in the network.
- `identifySocialClusters()`: Identifies social clusters (nodes with the maximum number of edges) within the network.

### Data Structures and Algorithms:

- **Graph Representation:**
  - Utilizes an unordered map (nodes) to store nodes with their names as keys.
  - Stores edges between nodes in a vector (edges).

- **Graph Traversal and Analysis:**
  - **Breadth-First Search (BFS):**
    - Used for graph traversal in methods like `visualizeGraph` and `findHighestCentrality`.
    - BFS aids in exploring relationships and communication patterns among nodes.

- **Centrality Computation:**
  - **Degree Centrality:** Computed using the number of edges connected to each node.
  - **Betweenness Centrality:** Computed by analyzing shortest paths between nodes.

- **Community Detection:**
  - Utilizes the Louvain method to identify collaboration networks and social clusters based on edge weights and modularity gain.

### Algorithms and Analysis:

#### 1. `findHighestCentrality()`:
   - **Algorithm Description:**
     - Utilizes Breadth-First Search (BFS) to compute communication centrality.
     - Iterates through nodes to determine the individual with the highest communication centrality.
   - **Insights:**
     - Identifies the node that serves as a central communicator, having the most direct or indirect communication links with other nodes.

#### 2. `identifyCollaborationNetworks()`:
   - **Algorithm Description:**
     - Implements the Louvain method to identify collaboration networks based on edge weights.
     - Merges communities with higher internal weights to detect groups with strong collaboration.
   - **Insights:**
     - Reveals cohesive clusters within the university where individuals collaborate extensively, showcasing strong ties in academic or project-related interactions.

#### 3. `determineInfluentialByDegreeCentrality()` and `determineInfluentialByBetweennessCentrality()`:
   - **Algorithm Description:**
     - Computes degree centrality and betweenness centrality

...

## Dataset Description:

### Node Structure:
- **Attributes:**
  - Each node comprises attributes such as name, role, and interests.
- **Representation:**
  - Nodes are represented using a Node class storing name, role, and interests as attributes.

### Relationships:
- **Type:**
  - Various types of relationships are represented (e.g., FRIENDSHIP, COLLABORATION, MENTORSHIP) through the RelationshipType enum.
- **Representation:**
  - Relationships between nodes are captured as Edge instances storing source, destination, weight, and relationship type.

### Graph Nature:
- **Graph Representation:**
  - Utilizes an unweighted, undirected graph representation to model the university social network.
- **Node-Edge Connectivity:**
  - Nodes represent individuals (students, faculty, staff) connected through edges denoting relationships.

### Directed/Undirected:
- The current implementation focuses on an undirected graph, enabling bidirectional relationships among individuals.

### Dataset Nature:

- **Real or Simulated Data:**
  - The dataset appears to be simulated for the purpose of demonstrating the functionality of the social network analysis program within the university context.

### Limitations:
- The simulated dataset might lack real-world complexity and intricacies found in actual university social networks.
- Scalability and diversity may be limited compared to real-world datasets, affecting the depth of analysis and representation of the social network.
- The dataset structure follows a simplistic representation of nodes and relationships, enabling the implementation and analysis of graph algorithms within a university setting. However, being simulated, it might not fully capture the complexity and scale of a real university social network, potentially limiting the depth of insights and analysis that can be derived.

...

## Conclusion

This project aimed to design and implement a C++ program for modeling and analyzing the social network within the FAST-NUCES university setting. The program successfully achieved its objectives by employing graph algorithms to gain insights into relationships among students, faculty, and staff.

### Project Objectives and Outcomes:

- **Objective:**
  - Develop a program to model relationships and apply graph algorithms.
- **Outcomes:**
  - Implemented classes for nodes, edges, and social network operations, effectively analyzing communication patterns, collaboration networks, influential individuals, and community clusters.

### Effectiveness of Implemented Algorithms:

- **Algorithm Efficiency:**
  - The implemented algorithms demonstrated efficiency, aligning closely with expected time complexities.
- **Insights Gained:**
  - The algorithms provided valuable insights into communication patterns, collaboration networks, influential individuals, and social clusters within the FAST-NUCES social network.

### Overall Impact and Insights:

- **Impact:**
  - The program offered a comprehensive view of social structures within the university, identifying influential individuals, cohesive groups, and communication patterns.
- **Insights:**
  - Analyzing various aspects of the social network shed light on collaborative efforts, influential figures, and community formations.

...

### Final Remarks:

The implemented algorithms and analysis provided a comprehensive understanding of the social network dynamics within FAST-NUCES. While the simulated dataset offered insights, real-world data could enhance the depth and accuracy of the analysis. Nevertheless, the program serves as a foundational tool for further exploration and understanding of university social networks.
