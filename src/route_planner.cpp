#include "route_planner.h"
#include <algorithm> // includes std::sort

RoutePlanner::RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y): m_Model(model) {
    /**
     * Finds the closest node to the specified initial point (start_x, start_y) and to the ending point (end_x, end_y).
     * These two values are going to be stored in the two private attributes of RoutePlanner called start_node and
     * end_node (nodes of type RouteModel::Node).
     * 
     * Both the initial point and the ending point must be given as percentages.
     */
    
    // Convert inputs to percentage:
    start_x *= 0.01;
    start_y *= 0.01;
    end_x *= 0.01;
    end_y *= 0.01;

    start_node = &m_Model.FindClosestNode(start_x, start_y);
    end_node = &m_Model.FindClosestNode(end_x, end_y);
}


float RoutePlanner::CalculateHValue(RouteModel::Node const *node) {
    /**
     * Compute the distance from a given node to the end_node.
     * This is done by using the distance method of RouteModel::Node that returns that distance as a float.
     */
    return node->distance(*end_node);
}


void RoutePlanner::AddNeighbors(RouteModel::Node *current_node) {
    /**
     * Populates the neighbors vector of the @current_node by adding all unvisited neighbors.
     * Then, add every node of current_node.neighbors to the open_list and set the nodes' visited attribute to true
     * 
     * Method RouteModel::Node::FindNeighbors stores the neighbors in a vector of nodes' pointers
     * that is set as a public attribute of RoutePlanner::Node.
     */
    current_node->FindNeighbors();

    for(RouteModel::Node* neighbor : current_node->neighbors) {
        // ** Compute the h_value, parent and g_value of the neighbor ** //
        neighbor->h_value = CalculateHValue(neighbor);
        neighbor->parent = current_node;
        // g_value = sum of the current_node distance + the distance between these two nodes
        float current_neighbor_distance = current_node->distance(*neighbor);
        neighbor->g_value = current_node->g_value + current_neighbor_distance;

        // Add every neighbor's node to the RoutePlanner::open_list and set it as visited
        neighbor->visited = true;
        open_list.push_back(neighbor);
    }
}


bool compareValuesHandG(RouteModel::Node* const first_node, RouteModel::Node* const second_node) {
    // This function is used in the method NextNode to compare the h and g values of two nodes.
    // It returns true if the first_node has a smaller h and g value. Otherwise, it returns false.
    return first_node->h_value + first_node->g_value < second_node->h_value + second_node->g_value;
}

RouteModel::Node *RoutePlanner::NextNode() {
    /**
     * NextNode returns a reference to the following node to go by sorting the open_list
     * and picking the node with the smallest h_value and g_value in that vector.
     */

    // Sort open_list according to the sum of the h value and g value (see the function compareValuesHandG).
    std::sort(open_list.begin(), open_list.end(), compareValuesHandG);

    // After sorting, the first element of the open_list is going to be the one with the smallest sum.
    // Therefore, we're going to create a reference to that node using std::vector::front.
    RouteModel::Node* first_node = open_list.front();
    open_list.erase(open_list.begin()); // remove the first element of open_list
    
    return first_node;
}


// TODO 6: Complete the ConstructFinalPath method to return the final path found from your A* search.
// Tips:
// - This method should take the current (final) node as an argument and iteratively follow the 
//   chain of parents of nodes until the starting node is found.
// - For each node in the chain, add the distance from the node to its parent to the distance variable.
// - The returned vector should be in the correct order: the start node should be the first element
//   of the vector, the end node should be the last element.

std::vector<RouteModel::Node> RoutePlanner::ConstructFinalPath(RouteModel::Node *current_node) {
    // Create path_found vector
    distance = 0.0f;
    std::vector<RouteModel::Node> path_found;

    // TODO: Implement your solution here.

    distance *= m_Model.MetricScale(); // Multiply the distance by the scale of the map to get meters.
    return path_found;

}


// TODO 7: Write the A* Search algorithm here.
// Tips:
// - Use the AddNeighbors method to add all of the neighbors of the current node to the open_list.
// - Use the NextNode() method to sort the open_list and return the next node.
// - When the search has reached the end_node, use the ConstructFinalPath method to return the final path that was found.
// - Store the final path in the m_Model.path attribute before the method exits. This path will then be displayed on the map tile.

void RoutePlanner::AStarSearch() {
    RouteModel::Node *current_node = nullptr;

    // TODO: Implement your solution here.

}