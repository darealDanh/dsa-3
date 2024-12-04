/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   TopoSorter.h
 * Author: ltsach
 *
 * Created on July 11, 2021, 10:21 PM
 */

#ifndef TOPOSORTER_H
#define TOPOSORTER_H
#include "graph/DGraphModel.h"
#include "list/DLinkedList.h"
#include "sorting/DLinkedListSE.h"

template <class T>
class TopoSorter
{
public:
    static int DFS;
    static int BFS;

protected:
    DGraphModel<T> *graph;
    int (*hash_code)(T &, int);

public:
    TopoSorter(DGraphModel<T> *graph, int (*hash_code)(T &, int) = 0)
    {
        // TODO
        this->graph = graph;
        this->hash_code = hash_code;
    }
    DLinkedList<T> sort(int mode = 0, bool sorted = true)
    {
        // TODO
        if (mode == 1)
        {
            return bfsSort(sorted);
        }
        else
        {
            return dfsSort(sorted);
        }
    }
    DLinkedList<T> bfsSort(bool sorted = true)
    {
        // TODO
        DLinkedList<T> sortedList;
        XHashMap<T, int> inDegree = vertex2inDegree(hash_code);
        DLinkedList<T> zeroInDegrees = listOfZeroInDegrees();
        Queue<T> queue;
        typename DLinkedList<T>::Iterator it = zeroInDegrees.begin();
        while (it != zeroInDegrees.end())
        {
            T vertex = *it;
            queue.enqueue(vertex);
            it++;
        }
        while (!queue.empty())
        {
            T vertex = queue.dequeue();
            sortedList.add(vertex);
            DLinkedList<T> adjVertices = graph->getOutwardEdges(vertex);
            typename DLinkedList<T>::Iterator it = adjVertices.begin();
            while (it != adjVertices.end())
            {
                T adjVertex = *it;
                inDegree[adjVertex]--;
                if (inDegree[adjVertex] == 0)
                {
                    queue.enqueue(adjVertex);
                }
                it++;
            }
        }
        return sortedList;
    }

    DLinkedList<T> dfsSort(bool sorted = true)
    {
        // TODO
        DLinkedList<T> sortedList;
        XHashMap<T, int> inDegree = vertex2inDegree(hash_code);
        DLinkedList<T> zeroInDegrees = listOfZeroInDegrees();
        Stack<T> stack;
        typename DLinkedList<T>::Iterator it = zeroInDegrees.begin();
        while (it != zeroInDegrees.end())
        {
            T vertex = *it;
            stack.push(vertex);
            it++;
        }
        while (!stack.empty())
        {
            T vertex = stack.pop();
            sortedList.add(vertex);
            DLinkedList<T> adjVertices = graph->getOutwardEdges(vertex);
            typename DLinkedList<T>::Iterator it = adjVertices.begin();
            while (it != adjVertices.end())
            {
                T adjVertex = *it;
                inDegree[adjVertex]--;
                if (inDegree[adjVertex] == 0)
                {
                    stack.push(adjVertex);
                }
                it++;
            }
        }
        return sortedList;
    }

protected:
    // Helper functions
    XHashMap<T, int> vertex2inDegree(int (*hash)(T &, int));
    XHashMap<T, int> vertex2outDegree(int (*hash)(T &, int));
    DLinkedList<T> listOfZeroInDegrees();

}; // TopoSorter
template <class T>
int TopoSorter<T>::DFS = 0;
template <class T>
int TopoSorter<T>::BFS = 1;

/////////////////////////////End of TopoSorter//////////////////////////////////

#endif /* TOPOSORTER_H */
