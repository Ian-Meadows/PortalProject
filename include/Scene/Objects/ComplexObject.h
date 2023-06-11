#ifndef COMPLEX_OBJECT_H
#define COMPLEX_OBJECT_H

#include "Object.h"

class ComplexObject : public Object{
public:
    ComplexObject(Vector3D pos, Vector3D scale, Vector3D rotation);
    ~ComplexObject();
    
private:
    void DrawShape() override;

    void GenerateNormals(float* array, int size, const unsigned char index[]);
    void GenerateAAndB(int i, const unsigned char index[], Vector3D& A, Vector3D& B);


    void DrawTriangle(int i);

    const int N=48;

    

    const float xyz[144] = {
//tri 1
        0, 0, 0,
        1, 0, 0,
        0.5, 0.5, 0,

//tri 2
        0, 0, -0.5,
        0.5, 0.5, 0,
        0, 0, 0,   

//tri 3
        1, 0, 0,
        0.5, -0.5, -0.5,
        0, 0, 0,

//tri 4
        0, 0, 0,
        0, 0, -0.5,
        0.5, -0.5, -0.5,
//tri 5
        1, 0, 0,
        0.5, -0.5, -0.5,
        1, -0.25, -1,
//tri 6
        1, 0, 0,
        1, -0.25, -1,
        0.5, 1, -0.75,
//tri 7
        1, 0, 0,
        0.5, 1, -0.75,
        0.5, 0.5, 0,
//tri 8
        0.5, 0.5, 0,
        0.5, 1, -0.75,
        0, 0.75, -0.5,
//tri 9
        0.5, 0.5, 0,
        0, 0.75, -0.5,
        0, 0, -0.5,
//tri 10
        0, 0, -0.5,
        0, 0.75, -0.5,
        0.25, 0.25, -1.25,
//tri 11
        0.25, 0.25, -1.25,
        0.5, 1, -0.75,
        0, 0.75, -0.5,

//tri 12
        0.25, 0.25, -1.25,
        0.5, 1, -0.75,
        1, -0.25, -1,
//tri 13
        1, -0.25, -1,
        0.25, 0.25, -1.25,
        0.35, -0.5, -1,
//tri 14
        0.35, -0.5, -1,
        1, -0.25, -1,
        0.5, -0.5, -0.5,
//tri 15
        0.35, -0.5, -1,
        0.5, -0.5, -0.5,
        0, 0, -0.5,
//tri 16
        0.35, -0.5, -1,
        0, 0, -0.5,
         0.25, 0.25, -1.25


    };

    const int index[48] = {
        0, 1, 2,//tri 1 done
        5, 4, 3,//tri 2 done
        8, 7, 6,//tri 3 current
        9, 10, 11,//tri 4
        12, 13, 14,//tri 5 cyan
        15, 16, 17,//tri 6 yellow
        18, 19, 20,//tri 7 magenta
        21, 22, 23,//tri 8 cyan
        24, 25, 26,//tri 9 yellow
        27, 28, 29,//tri 10 red
        32, 31, 30,//tri 11 green
        33, 34, 35,//tri 12 blue
        38, 37, 36,//tri 13 magenta
        39, 40, 41,//tri 14 red
        42, 43, 44,//tri 15 orange
        45, 46, 47//tri 16 purple
    };

     const float rgb[144] = {
        //tri 1
        0.75, 0, 1,
        0.75, 0, 1,
        0.75, 0, 1,
        //tri 2
        0.75, 0, 1,
        0.75, 0, 1,
        0.75, 0, 1,
        //tri 3
        1, 0, 0,
        1, 0, 0,
        1, 0, 0,
        //tri 4
        0.75, 0, 1,
        0.75, 0, 1,
        0.75, 0, 1,
        //tri 5
        0.75, 0, 1,
        0.75, 0, 1,
        0.75, 0, 1,
        //tri 6
        0.75, 0, 1,
        0.75, 0, 1,
        0.75, 0, 1,
        //tri 7
        0.75, 0, 1,
        0.75, 0, 1,
        0.75, 0, 1,
        //tri 8
        0.75, 0, 1,
        0.75, 0, 1,
        0.75, 0, 1,
        //tri 9
        0.75, 0, 1,
        0.75, 0, 1,
        0.75, 0, 1,
        //tri 10
        0.75, 0, 1,
        0.75, 0, 1,
        0.75, 0, 1,
        //tri 11
        0.75, 0, 1,
        0.75, 0, 1,
        0.75, 0, 1,
        //tri 12
        0.75, 0, 1,
        0.75, 0, 1,
        0.75, 0, 1,
        //tri 13
        0.75, 0, 1,
        0.75, 0, 1,
        0.75, 0, 1,
        //tri 14
        0.75, 0, 1,
        0.75, 0, 1,
        0.75, 0, 1,
        //tri 15
        0.75, 0, 1,
        0.75, 0, 1,
        0.75, 0, 1,
        //tri 16
        0.75, 0, 1,
        0.75, 0, 1,
        0.75, 0, 1,
    };

};

#endif