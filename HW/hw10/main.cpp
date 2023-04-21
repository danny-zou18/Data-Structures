#include <cstdlib>
#include <cmath>
#include <vector>
#include <iostream>
#include <utility>  
#include <set>

#include "image.h"
#include "priority_queue.h"

using std::cout; using std::endl; using std::vector; using std::pair; using std::set;

// ===================================================================================================

// distance field method functions
double NaiveDistanceFieldMethod(Image<Color> &input, Image<DistancePixel> &distance_image);
double ImprovedDistanceFieldMethod(Image<Color> &input, Image<DistancePixel> &distance_image);
double FastMarchingMethod(Image<Color> &input, Image<DistancePixel> &distance_image);

// visualization style helper functions
Color Rainbow(double distance, double max_distance);
Color GreyBands(double distance, double max_distance, int num_bands);

//Helper function that returns a pair based on the direction we want
pair<int,int> getDyDx(const unsigned int direction) {
    if (direction == 1){
        return std::make_pair(0,1);
    } else if (direction == 2){
        return std::make_pair(-1,1);
    } else if (direction == 3){
        return std::make_pair(-1,0);
    } else if (direction == 4){
        return std::make_pair(-1,-1);
    } else if (direction == 5){
        return std::make_pair(0,-1);
    } else if (direction == 6){
        return std::make_pair(1,-1);
    } else if (direction == 7){
        return std::make_pair(1,0);
    } else if (direction == 8){
        return std::make_pair(1,1);
    }
    return std::make_pair(0,0);
}

// ===================================================================================================

int main(int argc, char* argv[]) {
  if (argc != 5) {
    std::cerr << "Usage: " << argv[0] << " input.ppm output.ppm distance_field_method visualization_style" << std::endl;
    exit(1);
  }

  // open the input image
  Image<Color> input;
  if (!input.Load(argv[1])) {
    std::cerr << "ERROR: Cannot open input file: " << argv[1] << std::endl;
    exit(1);
  }

  // a place to write the distance values
  Image<DistancePixel> distance_image;
  distance_image.Allocate(input.Width(),input.Height());

  // calculate the distance field (each function returns the maximum distance value)
  double max_distance = 0;
  if (std::string(argv[3]) == std::string("naive_method")) {
    max_distance = NaiveDistanceFieldMethod(input,distance_image);
  } else if (std::string(argv[3]) == std::string("improved_method")) {
    max_distance = ImprovedDistanceFieldMethod(input,distance_image);
  } else if (std::string(argv[3]) == std::string("pq_with_map")) {
    max_distance = FastMarchingMethod(input,distance_image);
  } else if (std::string(argv[3]) == std::string("pq_with_hash_table")) {
    // EXTRA CREDIT: implement FastMarchingMethod with a hash table
  } else {
    std::cerr << "ERROR: Unknown distance field method: " << argv[3] << std::endl;
    exit(1);
  }

  // convert distance values to a visualization
  Image<Color> output;
  output.Allocate(input.Width(),input.Height());
  for (int i = 0; i < input.Width(); i++) {
    for (int j = 0; j < input.Height(); j++) {
      double v = distance_image.GetPixel(i,j).getValue();
      if (std::string(argv[4]) == std::string("greyscale")) {
	output.SetPixel(i,j,GreyBands(v,max_distance*1.01,1));
      } else if (std::string(argv[4]) == std::string("grey_bands")) {
	output.SetPixel(i,j,GreyBands(v,max_distance,4));
      } else if (std::string(argv[4]) == std::string("rainbow")) {
	output.SetPixel(i,j,Rainbow(v,max_distance));
      } else {
	// EXTRA CREDIT: create other visualizations 
	std::cerr << "ERROR: Unknown visualization style" << std::endl;
	exit(0);
      }
    }
  }
  // save output
  if (!output.Save(argv[2])) {
    std::cerr << "ERROR: Cannot save to output file: " << argv[2] << std::endl;
    exit(1);
  }

  return 0;
}

// ===================================================================================================

double NaiveDistanceFieldMethod(Image<Color> &input, Image<DistancePixel> &distance_image) {
  int w = input.Width();
  int h = input.Height();
  // return the maximum distance value
  double answer = 0;
  // loop over the pixels in the input image
  for (int i = 0; i < w; i++)  {
    for (int j = 0; j < h; j++) {
      double closest = -1;      
      // loop over all other pixels in the input image
      for (int i2 = 0; i2 < w; i2++)  {
	for (int j2 = 0; j2 < h; j2++) {
	  const Color& c = input.GetPixel(i2,j2);      
	  // skip all pixels that are not black
	  if (!c.isBlack()) continue;
	  // calculate the distance between the two pixels
	  double distance = sqrt((i-i2)*(i-i2) + (j-j2)*(j-j2));
	  // store the closest distance to a black pixel
	  if (closest < 0 || distance < closest) {
	    closest = distance;
	  }
	}
      }
      assert (closest >= 0);
      answer = std::max(answer,closest);
      // save the data to the distance image
      DistancePixel& p = distance_image.GetPixel(i,j);
      p.setValue(closest);
    }
  }
  return answer;
}

double ImprovedDistanceFieldMethod(Image<Color> &input, Image<DistancePixel> &distance_image) {
  int w = input.Width();
  int h = input.Height();
  double answer = 0;
  //Create a vector that contains all the black pixels in the image
  vector<DistancePixel* > cords;
  for (int i = 0; i < w; i++){
    for (int j = 0; j < h; j++){
      const Color& c = input.GetPixel(i,j);
      if (c.isBlack()){
        DistancePixel* pixel = &distance_image.GetPixel(i,j);
        pixel->setX(i); pixel->setY(j);
        pixel->setValue(0);
        cords.push_back(pixel);
      }
    }
  }
  //Loop through every single pixel and compare it with every single black pixel to find the shortest distance
  //to all of them, then set the distance value for that pixel
  for (int i = 0; i < w; i++){
    for (int j = 0; j < h; j++){
      double closest = -1;
      const Color& p = input.GetPixel(i,j);
      if (p.isBlack()){
        continue;
      }
      //Compare with every single black pixel and find the smallest distance
      for (unsigned int z = 0; z < cords.size(); z++){
        double distance = sqrt((i-cords[z]->getX()) * (i-cords[z]->getX()) + (j-cords[z]->getY()) * (j-cords[z]->getY()));
        if (closest < 0 || distance < closest) {
          closest = distance;
        }
      }
      //Find the biggest smallest distance
      assert (closest >= 0);
      answer = std::max(answer, closest);
      DistancePixel& pixel = distance_image.GetPixel(i,j);
      pixel.setValue(closest);
    }
  }
  return answer;
}

double FastMarchingMethod(Image<Color> &input, Image<DistancePixel> &distance_image) {
  int w = input.Width();
  int h = input.Height();
  //First  we want to find all the black pixels, storing all of them in a vector
  vector<DistancePixel*> b_pixels;
  for (int i = 0; i < w; i++){
    for (int j = 0; j < h; j++){
      const Color& c = input.GetPixel(i,j);
      DistancePixel* pixel = &distance_image.GetPixel(i,j);
      pixel->setX(j); pixel->setY(i);
      if (c.isBlack()){
        pixel->setValue(0);
        b_pixels.push_back(pixel);
      } else {
        //Initialize a huge number for non black pixels
        pixel->setValue(99999999999);
      }
    }
  }
  //Create a set that contains all the pixels that surrouds the black pixels
  set<DistancePixel*> pixels;
  for (unsigned int i = 0; i < b_pixels.size(); i++){
    //Get current coordinates 
    int cur_x = b_pixels[i]->getX(); 
    int cur_y = b_pixels[i]->getY();
    //Loop through all 8 eight possible directions 
    for (int d = 1; d <= 8; d++){
      pair<int,int> direction = getDyDx(d);
      //Get next coordinates
      int next_x = cur_x + direction.first;
      int next_y = cur_y + direction.second;
      if (next_x < 0 || next_y < 0 || next_x > w - 1 || next_y > h - 1){
        continue;
      }
      const Color& c = input.GetPixel(next_y,next_x);
      if (c.isBlack()){
        continue;
      }
      DistancePixel* pixel = &distance_image.GetPixel(next_y, next_x);
      pixel->setX(next_x); pixel->setY(next_y);
      //Calculate distance and set it to the pixel if the value is smaller
      double distance = sqrt((cur_x - next_x) * (cur_x - next_x) + (cur_y - next_y) * (cur_y - next_y));
      if (pixel->getValue() > distance){
        pixel->setValue(b_pixels[i]->getValue() + distance);
      }
      //If pixel is not in the set yet, insert it
      if (pixels.find(pixel) == pixels.end()){
        pixels.insert(pixel);
      } else {
        continue;
      }
    } 
  }
  set<DistancePixel*>::iterator it;
  vector<DistancePixel*> vec_pixels;
  //Push back every single pixel in the set to a vector so we can initialize a heap using its constructor
  for (it = pixels.begin(); it != pixels.end(); it++){
    vec_pixels.push_back(*it);
  }
  DistancePixel_PriorityQueue heap(vec_pixels);
  //Keep fast marching until there is only one element left in the queue, which will have our biggest value
  while (heap.size() != 1){
    const DistancePixel* top = heap.top();
    heap.pop();
    int cur_x = top->getX();
    int cur_y = top->getY();
    //Loop through all 8 directions
    for (int d = 1; d <= 8; d++){
      pair<int,int> direction = getDyDx(d);
      int next_x = cur_x + direction.first;
      int next_y = cur_y + direction.second;
      if (next_x < 0 || next_y < 0 || next_x > w - 1 || next_y > h - 1){
        continue;
      }
      DistancePixel* pixel = &distance_image.GetPixel(next_y, next_x);
      //If the pixel value is 1, then we know that its the shortest possible distance, skip
      //If the pixel value is 0, then it is a known black pixel, skip
      if (pixel->getValue() == 1 || pixel->getValue() == 0){
        continue;
      }
      //If the value of the pixel is the set huge number, we know that it has no known estimated distance,
      //Calculate the correct estimated distance, then insert to priority queue
      double distance = sqrt((cur_x - next_x) * (cur_x - next_x) + (cur_y - next_y) * (cur_y - next_y));
      double value = top->getValue() + distance;
      if (!heap.in_heap(pixel) && value < pixel->getValue()){
        pixel->setValue(value);
        heap.push(pixel);
      } else {
         if (pixel->getValue() > value){
            pixel->setValue(value);
          //Update the position if the value is changed
            heap.update_position(pixel);
          }
      }

    }
  }
  const DistancePixel* top = heap.top();
  double answer = top->getValue();
  return answer;
}

// ===================================================================================================

Color Rainbow(double distance, double max_distance) {
  Color answer;
  if (distance < 0.001) {
    // black
    answer.r = 0; answer.g = 0; answer.b = 0;
  } else if (distance < 0.2*max_distance) {
    // blue -> cyan
    double tmp = distance * 5.0 / max_distance;
    answer.r = 0;
    answer.g = tmp*255;
    answer.b = 255;
  } else if (distance < 0.4*max_distance) {
    // cyan -> green
    double tmp = (distance-0.2*max_distance) * 5.0 / max_distance;
    answer.r = 0;
    answer.g = 255;
    answer.b = (1-tmp*tmp)*255;
  } else if (distance < 0.6*max_distance) {
    // green -> yellow
    double tmp = (distance-0.4*max_distance) * 5.0 / max_distance;
    answer.r = sqrt(tmp)*255;
    answer.g = 255;
    answer.b = 0;
  } else if (distance < 0.8*max_distance) {
    // yellow -> red
    double tmp = (distance-0.6*max_distance) * 5.0 / max_distance;
    answer.r = 255;
    answer.g = (1-tmp*tmp)*255;
    answer.b = 0;
  } else if (distance < max_distance) {
    // red -> white
    double tmp = (distance-0.8*max_distance) * 5.0 / max_distance;
    answer.r = 255;
    answer.g = tmp*255;
    answer.b = tmp*255;
  } else {
    // white
    answer.r = answer.g = answer.b = 255;
  }  
  return answer;
}

Color GreyBands(double distance, double max_value, int num_bands) {
  Color answer;
  if (distance < 0.001) {
    // red
    answer.r = 255; answer.g = 0; answer.b = 0;
  } else {
    // shades of grey
    answer.r = answer.g = answer.b = int(num_bands*256*distance/double(max_value)) % 256;
  }  
  return answer;
}

// ===================================================================================================
