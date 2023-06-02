#include "Camera.h"

Camera::Camera(Vector3D position, Vector3D rotation)
{
    this->position = position;
    this->rotation = rotation;
    viewDirection = Vector3D();
}

Camera::Camera()
{
    ResetView();
}

Camera::~Camera()
{
}

void Camera::Update(Vector3D position, Vector3D rotation)
{
    this->position = position;
    this->rotation = rotation;
}

void Camera::Draw()
{

    //ortho
    if (projectionType == 0)
    {
        glRotatef(rotation.x, 1, 0, 0);
        glRotatef(rotation.y, 0, 1, 0);
    }
    //perspective
    else if (projectionType == 1)
    {
        //used code from ex9.c
        double Ex = -2 * worldDimension * Sin(rotation.y) * Cos(rotation.x);
        double Ey = +2 * worldDimension * Sin(rotation.x);
        double Ez = +2 * worldDimension * Cos(rotation.y) * Cos(rotation.x);

        //change view matrix
        gluLookAt(Ex, Ey, Ez, 0, 0, 0, 0, Cos(rotation.y), 0);
    }
    //first person
    else if (projectionType == 2)
    {
        //used information from: https://learnopengl.com/Getting-started/Camera
        viewDirection.x = Cos(rotation.y) * Cos(rotation.x);
        viewDirection.y = Sin(rotation.x);
        viewDirection.z = Sin(rotation.y) * Cos(rotation.x);

        //get the up vector
        Vector3D up = GetUp();
        //add the position vector to the front vector
        Vector3D added = position.Add(GetForward());

        //change view matrix
        gluLookAt(position.x, position.y, position.z, //camera position
                  added.x, added.y, added.z,          //position + direction
                  up.x, up.y, up.z);                  //up
    }
    else
    {
        std::cout << "ERROR: invalid projection type" << std::endl;
    }
}

void Camera::KeyPressed(int key, int scancode, int action, int  mods)
{
    if (key == GLFW_KEY_P && mods == GLFW_MOD_SHIFT)
    {
        IncreaseProjectionType();
    }
    else if (key == GLFW_KEY_P)
    {
        DecreaseProjectionType();
    }
    if (projectionType != 2)
    {
        return;
    }

    if(key == GLFW_KEY_1)
    {
        position = Vector3D(0.5, 2.5, 4.5);
        rotation = Vector3D(0, 270, 0);
    }
    else if(key == GLFW_KEY_2)
    {
        position = Vector3D(-1.5, 2.9, -4);
        rotation = Vector3D(0, 60, 0);
    }
    else if(key == GLFW_KEY_3)
    {
        position = Vector3D(-0.605, 1.978, -7.592);
        rotation = Vector3D(-5, 280, 0);
    }
    else if(key == GLFW_KEY_4)
    {
        position = Vector3D(-8.131, 2.077, 8.553);
        rotation = Vector3D(0, 145, 0);
    }
    else if(key == GLFW_KEY_5)
    {
        position = Vector3D(15.8377, 3.07098, -5.37929);
        rotation = Vector3D(-15, -10, 0);
    }

    if (key == GLFW_KEY_W)
    {
        position = position.Add(GetForward());
    }
    else if (key == GLFW_KEY_A)
    {
        position = position.Add(GetRight());
    }
    else if (key == GLFW_KEY_S)
    {
        position = position.Subtract(GetForward());
    }
    else if (key == GLFW_KEY_D)
    {
        position = position.Subtract(GetRight());
    }

    //  Right arrow key - increase angle by 5 degrees
    if (key == GLFW_KEY_RIGHT)
        rotation.y += 5;
    //  Left arrow key - decrease angle by 5 degrees
    else if (key == GLFW_KEY_LEFT)
        rotation.y -= 5;
    //  Up arrow key - increase elevation by 5 degrees
    else if (key == GLFW_KEY_UP)
        rotation.x += 5;
    //  Down arrow key - decrease elevation by 5 degrees
    else if (key == GLFW_KEY_DOWN)
        rotation.x -= 5;
    //  Keep angles to +/-360 degrees
    rotation.x = (int)rotation.x % 360;
    rotation.y = (int)rotation.y % 360;

    //fix for vector swapping when looking up side down
    if (rotation.x > 90)
    {
        rotation.x = 90;
    }
    if (rotation.x < -90)
    {
        rotation.x = -90;
    }
}

//allows the player to see themselves in the portals
void Camera::drawSelf()
{
    SimpleObject f = SimpleObject(position, Vector3D(0.3), Vector3D(0, -rotation.y, 0));
    f.Draw(nullptr);
}

//used code from ex9.c
void Camera::UpdateProjection(double worldDimension, double aspectRatio, int width, int height)
{
    this->worldDimension = worldDimension;
    this->aspectRatio = aspectRatio;
    this->width = width;
    this->height = height;

    //select projection matrix to modify
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //ortho
    if (projectionType == 0)
    {
        glOrtho(-aspectRatio * worldDimension, +aspectRatio * worldDimension,
                -worldDimension, +worldDimension, -worldDimension, +worldDimension);
    }
    //perspective and first person
    else if (projectionType == 1 || projectionType == 2)
    {

        gluPerspective(fov, aspectRatio, 0.1f, 1000);
    }
    else
    {
        std::cout << "ERROR: invalid projection type" << std::endl;
        return;
    }

    //change back to model view matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Camera::UpdateProjection()
{
    //select projection matrix to modify
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //ortho
    if (projectionType == 0)
    {
        glOrtho(-aspectRatio * worldDimension, +aspectRatio * worldDimension,
                -worldDimension, +worldDimension, -worldDimension, +worldDimension);
    }
    //perspective and first person
    else if (projectionType == 1 || projectionType == 2)
    {

        gluPerspective(fov, aspectRatio, 0.1f, 100);
    }
    else
    {
        std::cout << "ERROR: invalid projection type" << std::endl;
        return;
    }

    //change back to model view matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

std::string Camera::GetProjectionType()
{
    if (projectionType == 0)
    {
        return "orthogonal";
    }
    else if (projectionType == 1)
    {
        return "perspective";
    }
    else if (projectionType == 2)
    {
        return "first person";
    }
    else
    {
        return "ERROR: invalid projection type";
    }
}

void Camera::IncreaseProjectionType()
{
    projectionType++;
    if (projectionType > 2)
    {
        projectionType = 0;
    }
    ResetView();
}

void Camera::DecreaseProjectionType()
{
    projectionType--;
    if (projectionType < 0)
    {
        projectionType = 2;
    }
    ResetView();
}

void Camera::ResetView()
{
    if (projectionType == 0 || projectionType == 1)
    {
        position = (Vector3D){OVERHEAD_POS.x, OVERHEAD_POS.y, OVERHEAD_POS.z};
        rotation = (Vector3D){OVERHEAD_ROT.x, OVERHEAD_ROT.y, OVERHEAD_ROT.z};
    }
    else if (projectionType == 2)
    {
        position = (Vector3D){FIRST_PERSON_POS.x, FIRST_PERSON_POS.y, FIRST_PERSON_POS.z};
        rotation = (Vector3D){FIRST_PERSON_ROT.x, FIRST_PERSON_ROT.y, FIRST_PERSON_ROT.z};
    }
    else
    {
        std::cout << "ERROR: invalid projection type" << std::endl;
    }
}

Vector3D Camera::GetPosition()
{
    return position;
}
Vector3D Camera::GetRotation()
{
    return rotation;
}

Vector3D Camera::GetForward()
{
    return viewDirection.Normalize();
}
Vector3D Camera::GetRight()
{
    return viewDirection.Normalize().Cross(Vector3D(0, -1, 0));
}
Vector3D Camera::GetUp()
{
    return viewDirection.Normalize().Cross(GetRight());
}