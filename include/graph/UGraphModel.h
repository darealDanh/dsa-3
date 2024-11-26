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
        VertexNode *from = getVertexNode(from);
        if (from == nullptr)
        {
            throw VertexNotFoundException(from);
        }
        VertexNode *to = getVertexNode(to);
        if (to == nullptr)
        {
            throw VertexNotFoundException(to);
        }
        if (from == to)
        {
            from->connect(from, weight);
        }
        else
        {
            from->connect(to, weight);
            to->connect(from, weight);
        }
    }
    void disconnect(T from, T to)
    {
        // TODO
        VertexNode *from = getVertexNode(from);
        if (from == nullptr)
        {
            throw VertexNotFoundException(from);
        }
        VertexNode *to = getVertexNode(to);
        if (to == nullptr)
        {
            throw VertexNotFoundException(to);
        }
        if (from == to)
        {
            from->removeTo(from);
        }
        else
        {
            from->removeTo(to);
            to->removeTo(from);
        }
    }
    void remove(T vertex)
    {
        // TODO
        VertexNode *node = getVertexNode(vertex);
        VertexNode *current = nodeList.begin();
        while (nodeList != nullptr)
        {
            current->removeTo(node);
            current = current->next;
        }
        nodeList.removeItem(node);
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
