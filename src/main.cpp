#include <optional>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <io2d.h>
#include "route_model.h"
#include "render.h"
#include "route_planner.h"

using namespace std::experimental;

static std::optional<std::vector<std::byte>> ReadFile(const std::string &path)
{   
    // Read the path as binary data
    //
    // Set the initial position at the end of the file.
    // If this flag is not set, the initial position is the beginning of the file.
    std::ifstream is{path, std::ios::binary | std::ios::ate};
    if( !is )
        return std::nullopt;
    
    auto size = is.tellg();  // determine the size of the input stream
    std::vector<std::byte> contents(size);    
    
    is.seekg(0);  // seek back to the beginning of the input stream
    
    // Read all the input stream into the contents vector
    // (char*) casts the address of contents.data() as a character pointer 
    is.read((char*)contents.data(), size);

    if( contents.empty() )
        return std::nullopt;

    // Move semantics is a way to avoid expensive deep copy operations and replace them with
    // cheaper move operations.
    // Essentially, you can think of it as turning a deep copy into a shallow copy.
    // 
    // std::move merely casts its argument to an rvalue reference to allow moving it,
    // but doesn't guarantee a move operation.
    return std::move(contents);
}

int main(int argc, const char **argv)
{   
    // Just parse command line arguments
    std::string osm_data_file = "";
    if( argc > 1 ) {
        for( int i = 1; i < argc; ++i )
            if( std::string_view{argv[i]} == "-f" && ++i < argc )
                osm_data_file = argv[i];
    }
    else {
        std::cout << "To specify a map file use the following format: " << std::endl;
        std::cout << "Usage: [executable] [-f filename.osm]" << std::endl;
        // Use the default map file
        osm_data_file = "../map.osm";
    }
    
    std::vector<std::byte> osm_data;
 
    if( osm_data.empty() && !osm_data_file.empty() ) {
        std::cout << "Reading OpenStreetMap data from the following file: " <<  osm_data_file << std::endl;
        
        // We use auto because it can be null or a vector of bytes
        auto data = ReadFile(osm_data_file);
        if( !data )
            std::cout << "Failed to read." << std::endl;
        else
            osm_data = std::move(*data);
    }
    
    float start_x, start_y, end_x, end_y;

    std::cout << "Enter the value of start_x:\n>>> ";
    std::cin >> start_x;

    std::cout << "Enter the value of start_y:\n>>> ";
    std::cin >> start_y;

    std::cout << "Enter the value of end_x:\n>>> ";
    std::cin >> end_x;

    std::cout << "Enter the value of end_y:\n>>> ";
    std::cin >> end_y;

    // Build Model.
    RouteModel model{osm_data};

    // Create RoutePlanner object and perform A* search.
    RoutePlanner route_planner{model, start_x, start_y, end_x, end_y};
    route_planner.AStarSearch();

    std::cout << "Distance: " << route_planner.GetDistance() << " meters. \n";

    // Render results of search.
    Render render{model};

    auto display = io2d::output_surface {
        400,
        400,
        io2d::format::argb32,
        io2d::scaling::none,
        io2d::refresh_style::fixed, 
        30
    };
    display.size_change_callback([](io2d::output_surface& surface){
        surface.dimensions(surface.display_dimensions());
    });
    display.draw_callback([&](io2d::output_surface& surface){
        render.Display(surface);
    });
    display.begin_show();
}
