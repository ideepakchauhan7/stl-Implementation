#include <iostream>
#include "Vector.c++"

class Vector3
{
public:
    float x = 0.0f, y = 0.0f, z = 0.0f;
    int *memory_block;

    Vector3() { memory_block = new int[5]; }
    Vector3(float scala) : x(scala), y(scala), z(scala)
    {
        memory_block = new int[5];
    }
    Vector3(float x, float y, float z) : x(x), y(y), z(z)
    {
        memory_block = new int[5];
    }
    Vector3(const Vector3 &other) : x(other.x), y(other.y), z(other.z)
    {
        memory_block = new int[5];
    }
    Vector3(Vector3 &&other) : x(other.x), y(other.y), z(other.z)
    {
        memory_block = other.memory_block;
        other.memory_block = nullptr;
    }
    ~Vector3()
    {
        delete[] memory_block;
    }

    Vector3 &operator=(const Vector3 &other) = delete;

    Vector3 &operator=(const Vector3 &&other)
    {
        x = other.x;
        y = other.y;
        z = other.z;
        return *this;
    }
};
template<typename T>
void print(const Vector<T>&vector){
    for (size_t i = 0; i < vector.Size(); i++)
    {
        std::cout<<vector[i]<<std::endl;
    }
    
}
void print(const Vector<Vector3> &vector)
{
    for (size_t i = 0; i < vector.Size(); i++)
    {
        std::cout << vector[i].x << " " << vector[i].y << " " << vector[i].z << std::endl;
    }
}

int main(int argc, char const *argv[])
{
    Vector<Vector3> vector;

    vector.EmplaceBack(1.0f);
    vector.EmplaceBack(1.0, 2.0, 3.0);
    vector.EmplaceBack(2.0f);

    print(vector);

    vector.PopBack();
    vector.PopBack();
    vector.Clear();

    Vector<int>v;
    v.Pushback(1); 
    v.Pushback(2); 
    v.Pushback(3); 
    v.Pushback(4); 

    print(v);

    return 0;
}
