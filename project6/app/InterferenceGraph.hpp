#ifndef __INTERFERENCE_GRAPH__HPP
#define __INTERFERENCE_GRAPH__HPP

#include <exception>
#include <string>
#include <unordered_set>
#include <unordered_map>
class UnknownVertexException : public std::runtime_error {
public:
  UnknownVertexException(const std::string &v)
      : std::runtime_error("Unknown vertex " + v) {}
};

class UnknownEdgeException : public std::runtime_error {
public:
  UnknownEdgeException(const std::string &v, const std::string &w)
      : std::runtime_error("Unknown edge " + v + " - " + w) {}
};

// InterferenceGraph
//
// This is a class representing an interference graph
// as described in "Part 1: Interference Graph" of the README.md
// file. Though this class is templated, because of the usage of exceptions
// UnknownVertexException and UnknownEdgeException it will
// ONLY be tested with strings.
template <typename T> class InterferenceGraph {
public:
  // Custom type used to represent edges. This is mainly
  // used in the utility function for reading and writing
  // the graph structure to/from files. You don't need to use it.
  using EdgeTy = std::pair<T, T>;

  InterferenceGraph();

  ~InterferenceGraph();

  void addEdge(const T &v, const T &w);

  void addVertex(const T &vertex) noexcept;

  void removeEdge(const T &v, const T &w);

  void removeVertex(const T &vertex);

  std::unordered_set<T> vertices() const noexcept;

  std::unordered_set<T> neighbors(const T &vertex) const;

  unsigned numVertices() const noexcept;

  unsigned numEdges() const noexcept;

  bool interferes(const T &v, const T &w) const;

  unsigned degree(const T &v) const;

private:
  // Private member variables here.
  int num_edges = 0;
  int num_vertices = 0;
  std::unordered_map<T, std::unordered_set<T>> intgraph; // hold edges and vertices
  // first T holds vertices set holds edges
};

template <typename T> InterferenceGraph<T>::InterferenceGraph() {}

template <typename T> InterferenceGraph<T>::~InterferenceGraph() {}

template <typename T>
std::unordered_set<T> InterferenceGraph<T>::neighbors(const T &vertex) const {
  if(intgraph.find(vertex) == intgraph.end())
  {
    throw UnknownVertexException(vertex);
  }
  return intgraph.find(vertex)->second;
}

template <typename T>
std::unordered_set<T> InterferenceGraph<T>::vertices() const noexcept {
  std::unordered_set<T> temp;
  for(auto x: intgraph)
  {
    temp.insert(x.first);
  }
  return temp;
}

template <typename T>
unsigned InterferenceGraph<T>::numVertices() const noexcept {
  return num_vertices;
}

template <typename T> unsigned InterferenceGraph<T>::numEdges() const noexcept {
  return num_edges;
}

template <typename T>
void InterferenceGraph<T>::addEdge(const T &v, const T &w) {
  if(intgraph.find(v) == intgraph.end())
  {
    throw UnknownVertexException(v);
  }
  auto iterator = intgraph.find(v); //find vertex v
  if(intgraph.find(w) == intgraph.end())
  {
    throw UnknownVertexException(w);
  }
  auto iterator1 = intgraph.find(w);//find vertex w


  if(iterator->second.find(w) == iterator->second.end()) // if w is not in the edge list of vertex v
  {
    iterator1->second.insert(v); // add vertex v into vertex w edge list
    iterator->second.insert(w); // add vertex w into vertex v edge list
    num_edges++; // increment edges
  }
}

template <typename T>
void InterferenceGraph<T>::removeEdge(const T &v, const T &w) {
  if(intgraph.find(w) == intgraph.end() or intgraph.find(v) == intgraph.end())
  {
    throw UnknownVertexException(v);
  }
  // set iterator to find the two vertex's
  auto iterator1 = intgraph.find(v);
  auto iterator = intgraph.find(w);
  // delete each other from each other's vertex list
  if(iterator1->second.find(w) == iterator1->second.end() or iterator->second.find(v) == iterator->second.end())
  {
    throw UnknownEdgeException(v,w);
  }
  iterator1->second.erase(w);
  iterator->second.erase(v);
  num_edges--;
}

template <typename T>
void InterferenceGraph<T>::addVertex(const T &vertex) noexcept {
  if(intgraph.find(vertex) == intgraph.end()) // vertex does not exists
  {
    intgraph.insert({vertex,{}}); // adds vertex with empty edge list
    num_vertices++;
  }
}

template <typename T>
void InterferenceGraph<T>::removeVertex(const T &vertex) {
  if(intgraph.find(vertex) == intgraph.end())
  {
    throw UnknownVertexException(vertex);
  }
  auto iterator = intgraph.find(vertex); // find vertex we want to delete
  auto edges = intgraph.find(vertex)->second;
  for(auto x: edges) // iterate through the edges list of the vertex we want to get rid of
  {
    auto iterator1 = intgraph.find(x); // find vertex that is connected to want to delete vertex
    iterator1->second.erase(vertex); // erase from connected vertex's edge list ;
    num_edges--; // get rid of edge
  }
  intgraph.erase(vertex); // erase vertex after getting rid from all other vertex's edge list
  num_vertices--;
}

template <typename T>
bool InterferenceGraph<T>::interferes(const T &v, const T &w) const {
  if(intgraph.find(v) == intgraph.end() or intgraph.find(w) == intgraph.end())
  {
    if(intgraph.find(v) == intgraph.end())
    {
      throw UnknownVertexException(v);
    }else
    throw UnknownVertexException(w);
  }
  auto iterator = intgraph.find(v);
  if(iterator->second.find(w) == iterator->second.end()) // if edge is not in  vertex v edge list
  {
    return false;
  }
  else
    return true;
  
}

template <typename T> unsigned InterferenceGraph<T>::degree(const T &v) const {
  if(intgraph.find(v) == intgraph.end())
  {
    throw UnknownVertexException(v);
  }
  return intgraph.find(v)->second.size(); // counts the set of edges and returns the number of edges
}

#endif
