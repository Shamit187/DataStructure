//
// Created by User on 11/25/2021.
//

#ifndef GRAPHMODULEC___CUSTOMEXCEPTIONS_H
#define GRAPHMODULEC___CUSTOMEXCEPTIONS_H

#include <exception>

struct NotConnected: public std::exception{
    const char * what () const throw() override
    {
        return "Vertices aren't connected";
    }
};

struct InvalidDensity: public std::exception{
    const char* what () const throw() override
    {
        return "Density values should be between 0 and 1";
    }
};

struct EdgeNonExistent: public std::exception{
    const char* what() const throw() override
    {
        return "Edges does not exist";
    }
};

struct InvalidTranspose : public std::exception{
    const char* what() const throw() override
    {
        return "Undirected Graphs can not be transposed";
    }
};

struct InvalidBipartite : public std::exception{
    const char* what() const throw() override
    {
        return "Graph can not have Bipartite Set";
    }
};

struct TopologicalSortUnavailable : public std::exception{
    const char* what() const throw() override
    {
        return "Cycle exists, Topological sort not available";
    }
};




#endif //GRAPHMODULEC___CUSTOMEXCEPTIONS_H
