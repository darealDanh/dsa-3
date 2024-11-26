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
        from->connect(to, weight);
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
        Edge *edge = from->getEdge(to);
        if (edge == nullptr)
        {
            throw EdgeNotFoundException(from, to);
        }
        from->removeTo(to);
    }
    void remove(T vertex)
    {
        // TODO
        VertexNode *node = getVertexNode(vertex);
        if (node == nullptr)
        {
            throw VertexNotFoundException(vertex);
        }
        VertexNode *current = nodeList.begin();
        while (current != nullptr)
        {
            current->removeTo(node);
            current = current->next;
        }
        nodeList.removeItem(node);
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
