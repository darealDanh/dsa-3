/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   DGraphModel.h
 * Author: LTSACH
 *
 * Created on 23 August 2020, 19:36
 */

#ifndef DGRAPHMODEL_H
#define DGRAPHMODEL_H
#include "graph/AbstractGraph.h"
#include "stacknqueue/Queue.h"
#include "stacknqueue/Stack.h"
#include "hash/XHashMap.h"
#include "stacknqueue/PriorityQueue.h"
#include "sorting/DLinkedListSE.h"

//////////////////////////////////////////////////////////////////////
///////////// GraphModel: Directed Graph Model    ////////////////////
//////////////////////////////////////////////////////////////////////

template <class T>
class DGraphModel : public AbstractGraph<T>
{
private:
public:
    DGraphModel(
        bool (*vertexEQ)(T &, T &),
        string (*vertex2str)(T &)) : AbstractGraph<T>(vertexEQ, vertex2str)
    {
    }

    void connect(T from, T to, float weight = 0)
    {
        // TODO
        typename AbstractGraph<T>::VertexNode *fromNode = this->getVertexNode(from);
        if (fromNode == nullptr)
        {
            throw VertexNotFoundException(string(1, from));
        }
        typename AbstractGraph<T>::VertexNode *toNode = this->getVertexNode(to);
        if (toNode == nullptr)
        {
            throw VertexNotFoundException(string(1, to));
        }
        fromNode->connect(toNode, weight);
    }
    void disconnect(T from, T to)
    {
        // TODO
        typename AbstractGraph<T>::VertexNode *fromNode = this->getVertexNode(from);
        if (fromNode == nullptr)
        {
            throw VertexNotFoundException(string(1, from));
        }
        typename AbstractGraph<T>::VertexNode *toNode = this->getVertexNode(to);
        if (toNode == nullptr)
        {
            throw VertexNotFoundException(string(1, to));
        }
        typename AbstractGraph<T>::Edge *edge = fromNode->getEdge(toNode);
        if (edge == nullptr)
        {
            throw EdgeNotFoundException(string(1, from) + string(1, to));
        }
        fromNode->removeTo(toNode);
    }
    void remove(T vertex)
    {
        // TODO
        typename AbstractGraph<T>::VertexNode *node = this->getVertexNode(vertex);
        if (node == nullptr)
        {
            throw VertexNotFoundException(string(1, vertex));
        }
        typename DLinkedList<typename AbstractGraph<T>::VertexNode *>::Iterator it = this->nodeList.begin();
        while (it != this->nodeList.end())
        {
            typename AbstractGraph<T>::VertexNode *temp = *it;
            temp->removeTo(node);
            node->removeTo(temp);
            it++;
        }
        this->nodeList.removeItem(node);
    }

    static DGraphModel<T> *create(
        T *vertices, int nvertices, Edge<T> *edges, int nedges,
        bool (*vertexEQ)(T &, T &),
        string (*vertex2str)(T &))
    {
        // TODO
        DGraphModel<T> *graph = new DGraphModel<T>(vertexEQ, vertex2str);
        // add all of the vertices in to nodeList and all edges accordingly
        for (int i = 0; i < nvertices; i++)
        {
            graph->add(vertices[i]);
        }
        for (int i = 0; i < nedges; i++)
        {
            graph->connect(edges[i].from, edges[i].to, edges[i].weight);
        }
        return graph;
        // NOTE :: not sure, still need to review this code
    }
};

#endif /* DGRAPHMODEL_H */
