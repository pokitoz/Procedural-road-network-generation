#include <vector>
#include <cmath>
#include <iostream>
#include <glm/glm.hpp>
#include "rng_utility.h"
#include "lodepng/lodepng.cpp"

using namespace std;
using glm::ivec2;

/**
 * @brief Interpolate the values between the spectified vectors
 * @param a
 * @param b
 * @param result
 */
void Interpolate( ivec2 a, ivec2 b, vector<ivec2>& result ){
    int N = result.size();
    glm::vec2 step = glm::vec2(b-a) / float(max(N-1,1));
    glm::vec2 current( a );
    for( int i=0; i<N; ++i )
    {
        result[i] = current;
        current += step;
    }
}

/**
 * @brief find_next_point find a point starting from the start point
 * using the length and the angle (define in degree).
 * @param start
 * @param angle
 * @param length
 * @return
 */
ivec2 find_next_point(ivec2 start,double angle, int length){
    double angle_rad = angle*M_PI/180;
    ivec2 result(cos(angle_rad)*length,sin(angle_rad)*length);
    result = result+start;

    return result;
}

/**
 * @brief is_into_the_map: Check if the point is in or out of the map
 * @param p
 * @return
 */
bool is_into_the_map(ivec2 p){
    return (p.x >= 0 && p.x < MAP_SIZE && p.y >= 0 && p.y < MAP_SIZE);
}

/**
 * @brief mark_road
 * @param map
 * @param start
 * @param end
 * @param size
 */
void mark_road(Tile map[MAP_SIZE][MAP_SIZE],ivec2 start,ivec2 end,int size){
    vector<ivec2> start_positions(4 * size + 1);
    vector<ivec2> end_positions(4 * size + 1);


    if(!is_into_the_map(start)){
        ivec2 delta = glm::abs( start - end);
        int pixels = glm::max( delta.x, delta.y ) + 1;

        vector<ivec2> line( pixels );
        Interpolate( start, end, line );

        for (unsigned int i = 0; i < line.size(); ++i) {
            if(is_into_the_map(line[i])){
                start = line[i];
                break;
            }
        }
    }else if(!is_into_the_map(end)){
        ivec2 delta = glm::abs( start - end);
        int pixels = glm::max( delta.x, delta.y ) + 1;

        vector<ivec2> line( pixels );
        Interpolate( start, end, line );

        for (int i = line.size()-1; i <= 0; --i) {
            if(is_into_the_map(line[i])){
                end = line[i];
                break;
            }
        }
    }

    if(!is_into_the_map(start) || !is_into_the_map(end)){
        return;
    }

    start_positions[0] = start;
    end_positions[0] = end;

    for (int s = 1; s <= size; ++s) {
        start_positions[s*4] = ivec2(start) + s*ivec2(0,1);
        start_positions[s*4-1] = ivec2(start) + s*ivec2(1,0);
        start_positions[s*4-2] = ivec2(start) + s*ivec2(0,-1);
        start_positions[s*4-3] = ivec2(start) + s*ivec2(-1,0);

        end_positions[s*4] = ivec2(end) + s*ivec2(0,1);
        end_positions[s*4-1] = ivec2(end) + s*ivec2(1,0);
        end_positions[s*4-2] = ivec2(end) + s*ivec2(0,-1);
        end_positions[s*4-3] = ivec2(end) + s*ivec2(-1,0);
    }

    mark_base_square(map,start,end,size);

    for (unsigned int i = 0; i < start_positions.size(); ++i) {
        //We check if all the point are in the map if not we replace them with the base point
        if(!is_into_the_map(start_positions[i])){
            start_positions[i] = start_positions[0];
        }if(!is_into_the_map(end_positions[i])){
            end_positions[i] = end_positions[0];
        }

        ivec2 delta = glm::abs( start_positions[i] - end_positions[i]);
        int pixels = glm::max( delta.x, delta.y ) + 1;

        vector<ivec2> line( pixels );
        Interpolate( start_positions[i], end_positions[i], line );

        for (unsigned int i = 0; i < line.size(); ++i) {
            ivec2 t = line[i];
            map[t.x][t.y].is_road = true;
        }
    }
}


void mark_base_square(Tile map[MAP_SIZE][MAP_SIZE], glm::ivec2 start, glm::ivec2 end, int size)
{
    ivec2 a = ivec2(start) + size*ivec2(-1,-1);
    ivec2 b = ivec2(end) + size*ivec2(-1,-1);

    for (int j = 0; j < 2*size+1; ++j) {
        for (int i = 0; i < 2*size+1; ++i) {
            if(is_into_the_map(ivec2(a.x+i,a.y+j)))
                map[a.x+i][a.y+j].is_road = true;
            if(is_into_the_map(ivec2(b.x+i,b.y+j)))
                map[b.x+i][b.y+j].is_road = true;
        }
    }
}

/**
 * @brief find_angle: Find the angle between two given vectors
 * @param start
 * @param end
 * @return the ngle in degree
 */
double find_angle(glm::ivec2 start, glm::ivec2 end){

    double alpha;
    double angle_degre = 90;
    end = end - start;
    start = start - start;

    if(end.x >= start.x && end.y < start.y){
        alpha = atan((double)end.y/end.x);
        angle_degre = alpha*180/M_PI;
    }else if(end.x > start.x && end.y >= start.y){
        alpha = atan((double)end.y/end.x);
        angle_degre = alpha*180/M_PI;
    }else if(end.x <= start.x && end.y > start.y){
        alpha = atan((double)-end.x/end.y);
        angle_degre = 90 + alpha*180/M_PI;
    }else if(end.x < start.x && end.y <= start.y){
        if(end.y != 0){
            alpha = atan(-(double)end.x/end.y);
            angle_degre = -90 + alpha*180/M_PI;
        }else{
            angle_degre = 180;
        }
    }

    return angle_degre;
}

/**
 * @brief distance compute the distance between two points
 * @param start
 * @param end
 * @return
 */
double distance(ivec2 start,ivec2 end){
    return sqrt(pow((end.x - start.x),2) + pow((end.y - start.y),2));
}

/**
 * @brief distance_and_height
 * @param start
 * @param end
 * @param map
 * @return the distance between start and end, and add a cost from the variation off the height between start and end.
 */
double distance_and_height(ivec2 start,ivec2 end,Tile map[MAP_SIZE][MAP_SIZE]){
    if(!is_into_the_map(start) || !is_into_the_map(end)){
        return distance(start,end);
    }

    double result = sqrt(pow((end.x - start.x),2) + pow((end.y - start.y),2));

    ivec2 delta = glm::abs( start - end);
    int pixels = glm::max( delta.x, delta.y ) + 1;

    vector<ivec2> line( pixels );
    Interpolate( start, end, line );

    double previous = map[line[0].x][line[0].y].height;

    for (unsigned int i = 0; i < line.size(); ++i) {
        ivec2 p = line[i];
        result += 10*abs(map[p.x][p.y].height - previous);
        previous = map[p.x][p.y].height;
    }


    return result;
}


/**
 * @brief readPng: Initialize the map array according to the specified png images corresponding to the
 * density and the height of the map
 * @param map
 * @param densityFile
 * @param heightFile
 */
void readPng(Tile map[MAP_SIZE][MAP_SIZE], const char* densityFile, const char* heightFile){

    unsigned error;
    unsigned char *densityImage;
    unsigned char *heightImage;

    unsigned w, h;
    size_t j, i;

    cout << densityFile << endl;
    //load the PNG
    error = lodepng_decode32_file(&densityImage, &w, &h, densityFile);

    //Stop if there is an error
    if (error){
        printf ("error %u: %s\n", error, lodepng_error_text (error));
        return;
    }

    //Load the PNG in one function call
    error = lodepng_decode32_file (&heightImage, &w, &h, heightFile);

    //Stop if there is an error
    if (error){
        printf ("error %u: %s\n", error, lodepng_error_text (error));
        return;
    }


    double maxDensity = -1, minDensity = 300;
    double maxHeight = -1, minHeight = 300;


    //Normalisation of the values
    for (i = 0; i + 1 - 1 < h; i++){
        for (j = 0; j + 1 - 1 < w; j++){

            //get RGBA components

            /*We are working on gray levels. We only need to take the
             * value Red or Blue or Green since they are all the same*/
            if(maxDensity < densityImage[4 *i*w + 4*j]){
                maxDensity = densityImage[4 *i*w + 4*j];
            }
            if(minDensity > densityImage[4 *i*w + 4*j]){
                minDensity = densityImage[4 *i*w + 4*j];
            }

            if(maxHeight < heightImage[4 *i*w + 4*j]){
                maxHeight = heightImage[4 *i*w + 4*j];
            }
            if(minHeight > heightImage[4 *i*w + 4*j]){
                minHeight = heightImage[4 *i*w + 4*j];
            }
        }

    }


    for (i = 0; i + 1 - 1 < h; i++){
        for (j = 0; j + 1 - 1 < w; j++){
            int r1, r2;

            r1 = densityImage[4 *i*w + 4*j];       /*Take the value of red */
            r2 = heightImage [4 *i*w + 4*j];       /*Take the value of red */

            map[j][i].density = 1-(r1-minDensity)/(maxDensity-minDensity);
            map[j][i].height  = (r2-minHeight) / (maxHeight-minHeight);
        }
    }


}

/**
 * @brief writeToPng: write the map into a PNG image
 * @param map
 * @param outputName
 */
void writeToPng(Tile map[MAP_SIZE][MAP_SIZE], const char* outputName){
    unsigned int width = MAP_SIZE, height = MAP_SIZE;

    //Initialization of the array containing the image
    unsigned char* mapImage = (unsigned char*) malloc(width*height*4);

    //Red
    int r;
    //Green
    int g;
    //Blue
    int b;
    //Maximum alpha
    int a = 255;
    int luminosity = 250;

    for(unsigned y = 0; y < height; y++){
        for(unsigned x = 0; x < width; x++){
            Tile t = map[x][y];

            if(t.is_road){
                r = 0;
                g = 0;
                b = 0;
            }else if(!t.is_accessible){
                r = 0.8*luminosity;
                g = 0.8*luminosity;
                b = 0.85*luminosity;
            }else{
                r = t.height*luminosity;
                g = t.density*luminosity;
                b = 0.5*luminosity;
            }


            mapImage[4 * y * width + 4 * x + 0] = r;
            mapImage[4 * y * width + 4 * x + 1] = g;
            mapImage[4 * y * width + 4 * x + 2] = b;
            mapImage[4 * y * width + 4 * x + 3] = a;
        }
    }

    lodepng_encode32_file(outputName, mapImage, width, height);

    free(mapImage);

}

/**
 * @brief get_average_pop: Return the average population of a specified square of the map
 * @param map
 * @param left_top
 * @param width
 * @param height
 * @return
 */
pair<glm::ivec2, double> get_average_pop(Tile map[MAP_SIZE][MAP_SIZE], glm::ivec2 left_top, int width, int height)
{
    double w = width / 2;
    double h = height / 2;

    ivec2 center = left_top + ivec2(w,h);

    double total = 0;
    double nb_tile = 0;

    //Loop for all the tiles of map to find the average population in the corresponding square
    for (int x = left_top.x; x < left_top.x+width; ++x) {
        for (int y = left_top.y; y < left_top.y+height; ++y) {
            total += map[x][y].density;
            nb_tile++;
        }
    }

    return pair<ivec2, double>(center,total/nb_tile);
}

/**
 * @brief get_subdivided_map: Break the map into chunks to know where the population is situated.
 * @param map
 * @param square_size
 * @return
 */
vector<pair<glm::ivec2, double> > get_subdivided_map(Tile map[MAP_SIZE][MAP_SIZE], int square_size)
{
    vector<pair<glm::ivec2, double> > result;

    for (int x = 0; x < MAP_SIZE; x += square_size) {
        for (int y = 0; y < MAP_SIZE; y += square_size) {
            if((x+square_size) < MAP_SIZE && (y+square_size) < MAP_SIZE){
                result.push_back(get_average_pop(map,ivec2(x,y),square_size, square_size));
            }else{

                int width = square_size;
                int heigth = square_size;

                if((x+square_size) >= MAP_SIZE){
                    width = MAP_SIZE - x -1;
                }

                if((y+square_size) >= MAP_SIZE){
                    heigth = MAP_SIZE - y -1;
                }

                result.push_back(get_average_pop(map,ivec2(x,y),width, heigth));

            }
        }
    }

    sort(result.begin(),result.end(),comp_function);

    return result;
}


/**
 * @brief comp_function: Compare two pair using their value contained in the second element
 * @param a
 * @param b
 * @return true if a.value > b.value
 */
bool comp_function(pair<glm::ivec2, double> a, pair<glm::ivec2, double> b)
{
    return a.second > b.second;
}
