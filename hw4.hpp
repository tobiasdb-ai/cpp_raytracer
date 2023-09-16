#include <iostream>
#include <vector>
#include <string>
namespace st = std;

namespace hwk4
{

    class Object;
    class Ray;

    typedef std::vector<Object *> VPO;

    class Vec3D
    {
        friend class Ray;

    public:
        st::string returnXYZ(Vec3D v);
        float x;
        float y;
        float z;

        Vec3D(float x, float y, float z);
        Vec3D();

        void show(st::string label, Vec3D const &self);
        void show(st::string label, float scalar);
        void show(st::string label);
        void minus(Vec3D const &self);
        Vec3D add(Vec3D const &other) const;
        Vec3D operator+(Vec3D const &other);
        Vec3D sub(Vec3D const &other) const;
        Vec3D operator-(Vec3D const &other);
        Vec3D mul(float scalar);
        Vec3D operator*(float scalar);
        Vec3D div(float scalar);
        Vec3D operator/(float scalar);
        float norm(Vec3D const &self) const;
        Vec3D unit(Vec3D const &self) const;
        float dot(Vec3D const &other) const;
        Vec3D cross(Vec3D const &other) const;

    protected:
    };

    class Object
    {
    public:
        Vec3D center;

        Object(float x, float y, float z);


        virtual bool hit(Ray const &ray) = 0;

    };

    class Ray
    {
        friend class Vec3D;

    public:
        VPO objects;
        Vec3D support;
        Vec3D direction;

        Ray(float xStart, float yStart, VPO &objects);

        bool scan();

    protected:
    };

    class Sphere : public Object
    {
        friend class Ray;
        friend class Vec3D;

    public:
        Sphere(float x, float y, float z, float radius);

        Vec3D center;
        float radius;

        bool hit(Ray const &ray);
        float distFromRay(Ray const &ray) const;
        Vec3D hitPoint(Ray const &ray) const;

    protected:
    };

    class Floor : public Object
    {
    public:
        Vec3D position;
        Vec3D normal;

        Floor(float x, float y, float z, float height);

        Vec3D center;
        float breedte;
        float lengte;

        virtual bool hit(const Ray &ray);
    };

    class RayScanner
    {
    public:
        VPO vpo;

        RayScanner(VPO vpo);

        int indextoY(int i);
        int indextoX(int j);
        void scan();
    };

}