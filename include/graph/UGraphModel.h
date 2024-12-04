/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   UGraphModel.h
 * Author: LTSACH
 *
 * Created on 24 August 2020, 15:16
 */

#ifndef UGRAPHMODEL_H
#define UGRAPHMODEL_H

#include "graph/AbstractGraph.h"
#include "stacknqueue/PriorityQueue.h"

//////////////////////////////////////////////////////////////////////
///////////// UGraphModel: Undirected Graph Model ////////////////////
//////////////////////////////////////////////////////////////////////

template <class T>
class UGraphModel : public AbstractGraph<T>
{
private:
public:
    // class UGraphAlgorithm;
    // friend class UGraphAlgorithm;

    UGraphModel(
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
        if (fromNode == toNode)
        {
            fromNode->connect(toNode, weight);
        }
        else
        {
            fromNode->connect(toNode, weight);
            toNode->connect(fromNode, weight);
        }
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
        if (fromNode == toNode)
        {
            fromNode->removeTo(toNode);
        }
        else
        {
            fromNode->removeTo(toNode);
            toNode->removeTo(fromNode);
        }
    }
    void remove(T vertex)
    {
        // TODO
        typename AbstractGraph<T>::VertexNode *node = this->getVertexNode(vertex);
        typename DLinkedList<typename AbstractGraph<T>::VertexNode *>::Iterator it = this->nodeList.begin();
        while (it != this->nodeList.end())
        {
            typename AbstractGraph<T>::VertexNode *current = *it;
            current->removeTo(node);
            node->removeTo(current);
            it++;
        }
        this->nodeList.removeItem(node);
    }
    static UGraphModel<T> *create(
        T *vertices, int nvertices, Edge<T> *edges, int nedges,
        bool (*vertexEQ)(T &, T &),
        string (*vertex2str)(T &))
    {
        // TODO
        UGraphModel<T> *graph = new UGraphModel<T>(vertexEQ, vertex2str);
        for (int idx = 0; idx < nvertices; idx++)
        {
            graph->add(vertices[idx]);
        }
        for (int idx = 0; idx < nedges; idx++)
        {
            graph->connect(edges[idx].from, edges[idx].to, edges[idx].weight);
            graph->connect(edges[idx].to, edges[idx].from, edges[idx].weight);
        }
        return graph;
    }
};

#endif /* UGRAPHMODEL_H */
