# x: the cost building a lab, y: the cost to repair a road
def findMinimumCostToLabifyGTU(x, y, graph):
    cost = 0
    vertices = []

    # find all vertices
    for key in graph:
        vertices.append(key)

    while vertices:
        # Explored is visited vertices
        explored = []
        # Helper h_queue, first in first out
        h_queue = [vertices[0]]
        while h_queue:
            current = h_queue.pop(0)
            # if it is not visited
            if current not in explored:
                explored.append(current)
                neighbours = graph[current]

                for i in neighbours:
                    h_queue.append(i)

        # remove visited vertices
        i = 0
        while i < len(vertices):
            curr = vertices[i]
            if curr in explored:
                vertices.pop(i)
            else:
                i += 1

        # calculate cost
        if x < y:
            cost += x * len(explored)
        else:
            cost += x + (len(explored) - 1) * y

    return cost


if __name__ == '__main__':
    # The graph is initialized as dictionary
    # mapOfGTU = {
    #     1: set([2, 3]),
    #     2: set([1, 3, 4]),
    #     3: set([1, 2, 4]),
    #     4: set([3, 2]),
    #     5: set([6]),
    #     6: set([5])
    # }
    mapOfGTU = {
        1: {2, 3},
        2: {1, 3},
        3: {1, 2}
    }
    minCost = findMinimumCostToLabifyGTU(2, 1, mapOfGTU)
    print(minCost)
