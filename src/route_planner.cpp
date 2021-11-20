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
    float first_node_value  = first_node->h_value  + first_node->g_value;  // h1 + g1
    float second_node_value = second_node->h_value + second_node->g_value; // h2 + g2
    return first_node_value < second_node_value;
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


std::vector<RouteModel::Node> RoutePlanner::ConstructFinalPath(RouteModel::Node *current_node) {
    /**
     * Returns a path of nodes that goes from the first node to the end node.
     * 
     * Keep in mind that the given node is the final node. Therefore, after
     * creating the path of nodes we have to reverse it.
     */
    // Create path_found vector
    distance = 0.0f;
    std::vector<RouteModel::Node> path_found;

    while(current_node->parent) {
        path_found.push_back(*current_node);
        // Add the distance from the current node to the parent node
        distance += current_node->distance(*(current_node->parent));

        // Go from the current_node to the parent node
        current_node = current_node->parent;
    }
    // The first element of the chain (last element of the while loop) won't be added to the
    // path as it has no parent. Therefore, we have to add it after the while loop:
    path_found.push_back(*current_node);

    // The path of nodes goes from the back to the beginning, so we have to reverse the order
    std::reverse(path_found.begin(), path_found.end());

    distance *= m_Model.MetricScale(); // Multiply the distance by the scale of the map to get meters.
    return path_found;
}


void RoutePlanner::AStarSearch() {
    /**
     * Implementation of the A* Search algorithm.
     * 
     * Add the first node to the open_list. Then, go through all the nodes adding their neighbors and
     * taking the one with the lowest sum of G + H values until you find the end node. Then, 
     * return the path from the first node to that end node.
     */
    RouteModel::Node *current_node = nullptr;

    // First we have to add the inital node to the open list because it belongs to the path of nodes
    // and to avoid the open_list from being empty so we can iterate through it.
    start_node->visited = true;
    open_list.push_back(start_node);

    // Remember that every time we call NextNode, the first element of the open_list is removed.
    // Therefore, it will reach a point where there are no more nodes in the open_list. Then, the program has finsihed.
    while(open_list.size() > 0) {
        current_node = NextNode();

        // Check if the distance between the current_node and the end_node is 0. In that case,
        // the path from the first node to the end node is complete and we can create the path.
        float distance_current_node_and_end_node = current_node->distance(*end_node);
        if(distance_current_node_and_end_node == 0) {
            // The final path is stored in the m_Model.path attribute
            m_Model.path = ConstructFinalPath(current_node);
            return;
        }
        // Otherwise, we have to repeat the loop adding the neighbors of that node until we find
        // the end node.
        else {
            AddNeighbors(current_node);
        }
    }

}