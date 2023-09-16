#include <iostream>
#include <vector>
#include <string>
#include <math.h>

#define RAY_T_MIN 0.01f
#define RAY_T_MAX 10000.0f

#include "hw4.hpp"

auto const imageDist = 0.8;

namespace hwk4 {

Vec3D::Vec3D(float x, float y, float z): 
    x(x),y(y),z(z)
    {}

Vec3D::Vec3D(): 
    x(0),y(0),z(0)
    {}

st::string Vec3D::returnXYZ(Vec3D v) {
    st::string s = st::to_string(v.x) + ", " + st::to_string(v.y) + ", " + st::to_string(v.z);
    return s; 
}     
void Vec3D::show (st::string label, Vec3D const &self){
        st::cout << label << " " << returnXYZ(self) << '\n';
    };
void Vec3D::show (st::string label){
        st::cout << label << " " << returnXYZ(*this) << '\n';
    };

void Vec3D::show (st::string label, float scalar) {
        st::cout << label << " " << scalar << '\n';
}

void Vec3D::minus (Vec3D const &self) { //WORKS, flips the sign of x,y,z
    this->x = -self.x;
    this->y = -self.y;
    this->z = -self.z;
}

Vec3D Vec3D::add (Vec3D const &other) const { //WORKS, adds up two vectors
    Vec3D v;
    v.x = this->x + other.x;
    v.y = this->y + other.y;
    v.z = this->z + other.z;
    return v;
}

Vec3D Vec3D::operator+ (const Vec3D &other) { //WORKS
    Vec3D v;
    v.x = this->x + other.x;
    v.y = this->y + other.y;
    v.z = this->z + other.z;
    return v;
}
    

Vec3D Vec3D::sub (Vec3D const &other) const { //WORKS, subtraction of two vectors
    Vec3D v;
    v.x = this->x - other.x;
    v.y = this->y - other.y;
    v.z = this->z - other.z;
    return v;
}

Vec3D Vec3D::operator- (const Vec3D &other) {  //WORKS
    Vec3D v;
    v.x = this->x - other.x;
    v.y = this->y - other.y;
    v.z = this->z - other.z;
    return v;
}

Vec3D Vec3D::mul (float scalar) { //WORKS, Scalar multiplication
    Vec3D v;
    v.x = this->x * scalar;
    v.y = this->y * scalar;
    v.z = this->z * scalar;
    return v;
}

Vec3D Vec3D::operator* (float scalar) { //WORKS, multiplies the vector by a number
    Vec3D v;
    v.x = this->x * scalar;
    v.y = this->y * scalar;
    v.z = this->z * scalar;
    return v;
}


Vec3D Vec3D::div (float scalar){ //WORKS, scalar devision
    Vec3D v;
    v.x = this->x / scalar;
    v.y = this->y / scalar;
    v.z = this->z / scalar;
    return v;
}

Vec3D Vec3D::operator/ (float scalar){ //WORKS
    Vec3D v;
    v.x = this->x / scalar;
    v.y = this->y / scalar;
    v.z = this->z / scalar;
    return v;
}

float Vec3D::norm (Vec3D const &self) const {    //WORKS, gives norm of vector
   float length = pow(self.x,2) + pow(self.y,2) + pow(self.z,2);
   return sqrt(length); 
}

Vec3D Vec3D::unit (Vec3D const &self) const { //WORKS, Gives vector unit
    Vec3D unit;
    unit.x = self.x / norm(self);
    unit.y = self.y / norm(self);
    unit.z = self.z / norm(self);
    return unit;
}

float Vec3D::dot (Vec3D const &other) const { //WORKS, dot product
    float dot = this->x * other.x + this->y * other.y + this->z * other.z;
    return dot;
}

Vec3D Vec3D::cross (Vec3D const &other) const { //WORks, cross porduct
    Vec3D v;
    v.x = this->y * other.z - this->z * other.y;
    v.y = this->z * other.x - this->x * other.z;
    v.z = this->x * other.y - this->y * other.x;
    return v;
}

//OBJECT


Object::Object(float x, float y, float z): 
        center(x,y,z) {}


    bool Object::hit(Ray const &ray) {
    }        

//RAY


Ray::Ray (float xStart, float yStart, VPO &object):
    support(Vec3D (0,0,imageDist)),
    direction(Vec3D (xStart,yStart,0)),
    objects(object) {
        direction.sub(support);
        direction.unit(direction);
    }


    bool Ray::scan() {
        for(auto &o : objects) {  
            if(o->hit(*this)){
                return true;
            } 
        }  
        return false; 
    }

Floor::Floor(float x, float y, float z,float height):
    Object(x,y,z)
	{
		position = { 0,0,height };
		normal = { 0,0,1 };
	}


bool Floor::hit(const Ray& ray)
	{
		float dot = ray.direction.dot((ray.direction.cross(normal))); 
		if (dot == 0.0f)
			return false;
		return true;
	}

RayScanner::RayScanner(VPO vpo):
    vpo(vpo)    {}    

    float length = 100;
    float width = 140;

    int RayScanner::indextoY(int i){
        return 0.5*i*length;
    }

    int RayScanner::indextoX(int j){
        return 0.5*j*width;
    }

    void RayScanner::scan(){
        for(int i = 0; i < length; i++) {
            for (int j = 0; j < width; j++) {
                auto ray = Ray(0.01*indextoX(j), 0.01*indextoY(i), vpo); //--> x,y
                if(ray.scan()) {
                    std::cout << "N";
                } else {
                    std::cout << " ";
                }
            }
            std::cout << '\n';
        }
    }    

// SPHERE

Sphere::Sphere(float x, float y, float z, float radius):
    Object(x,y,z), radius(radius)
    {}

    float Sphere::distFromRay (Ray const &ray) const{
        
    return (ray.direction.norm(ray.direction.cross(ray.support.sub(center).div(ray.direction.norm(ray.direction)))));
    }

    bool Sphere::hit(Ray const &ray){
        auto a_component = pow(ray.direction.norm(ray.direction),2);
        auto b_component = (ray.direction.dot(ray.support.sub(center))) * 2;
        auto c_component = pow(ray.support.sub(center).norm(ray.support.sub(center)),2)- pow(radius,2);
        auto discriminant = pow(b_component,2)-4 * a_component * c_component;
        float t = -1.0;
        if (discriminant < 0)
			return false;
        else
        {
            return true;
        }
    
    }


    Vec3D Sphere::hitPoint (Ray const &ray) const{
        //Determines if a ray hits the sphere
        auto a = ray.support.sub(center).dot(ray.direction.unit(ray.direction));
        auto delta = a*a - (ray.support.sub(center).norm(ray.support.sub(center))*ray.support.sub(center).norm(ray.support.sub(center)) - radius * radius);
        auto distance = a*-1 - sqrt(delta);
        return ray.support.add(ray.direction.unit(ray.direction).mul(distance));

    }
}