#include <iostream>
#include <vector>
#include <string>


#include "hw4.hpp"
namespace hw = hwk4;

int main () {  

 /*   auto obj = hw::Object(1,2,3); 
    obj.center.show("Object: ", obj.center);
    auto vec3D = hw::Vec3D(1,2,3);
    auto Vec = hw::Vec3D(3,4,5);
    vec3D.show("vec3d", vec3D);
    vec3D.add(Vec);
    vec3D.show("addition", vec3D);
    vec3D.mul(3);
    vec3D.show("muliplied", vec3D);
    vec3D.div(3);
    vec3D.show("multiplied", vec3D);
    vec3D.cross(Vec);
    vec3D.show("cross product", vec3D);
    vec3D.show("dot product",vec3D.dot(vec3D));*/

    auto vec3D = hw::Vec3D(1,2,3);
    auto Vec = hw::Vec3D(3,4,5);
    auto ve = vec3D + Vec;
    ve.show("add:", ve);
    ve = ve * 3;
    ve.show("times 3: ");
    ve = ve / 3;
    ve.show("div 3: ");

    hw::Floor floor = hw::Floor(5,8,-6,0);
    auto Sphere1  = hw::Sphere(100,100,100,0.5);
    auto Sphere2 = hw::Sphere(-5,-3,-1,0.05);
    auto Spheres = std::vector<hw::Sphere> ({hw::Sphere(6, 6, -7, 100), hw::Sphere(-0.4, 0.23, -1, 0.4),hw::Sphere(0.4, 0.4, -1.2, 0.3),hw::Sphere(0.7, -0.15, -1.5, 0.2)});

    hw::VPO vpo;
    vpo.push_back(&Sphere1);
    vpo.push_back(&Sphere2);

    auto rayScanner = hw::RayScanner(vpo);
    rayScanner.scan();
    //vec3D.show("example", ray.direction);
    return 0;
}