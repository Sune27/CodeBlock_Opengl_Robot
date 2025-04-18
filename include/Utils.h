#include <GL/glut.h>
#include <cmath>
#include <math.h>
#include <iostream>
#include <string>

#include "Config.h"

#ifndef UTILS_H
#define UTILS_H

struct Vector
{
    GLdouble arr[3];

    Vector normalize() const {
        GLdouble x = arr[0];
        GLdouble y = arr[1];
        GLdouble z = arr[2];

        GLdouble length = sqrt(x * x + y * y + z * z);
        if (length == 0.0) {
            std::cerr << "Error: Cannot normalize zero-length vector." << std::endl;
            return Vector(0.0); // Hoặc xử lý lỗi theo cách khác
        }

        Vector result;
        result.arr[0] = x / length;
        result.arr[1] = y / length;
        result.arr[2] = z / length;
        return result;
    }
    Vector crossProduct(const Vector& other) const {
        Vector result;
        result.arr[0] = arr[1] * other.arr[2] - arr[2] * other.arr[1];
        result.arr[1] = arr[2] * other.arr[0] - arr[0] * other.arr[2];
        result.arr[2] = arr[0] * other.arr[1] - arr[1] * other.arr[0];
        return result;
    }
    void rotateAroundXAxis(const Vector& other, float angleDegrees)
    {
        // 1. Chuẩn hóa vector other
        Vector other_normalized = other.normalize();

        // 2. Tạo vector pháp tuyến của mặt phẳng chứa vector other và vuông góc với OYZ (X-axis)
        Vector xAxis(1.0, 0.0, 0.0);
        Vector normal = other_normalized.crossProduct(xAxis);
        normal = normal.normalize();

        // 3. Tạo vector vuông góc với other và nằm trong mặt phẳng đã tạo ở bước 2
        Vector orthogonal = normal.crossProduct(other_normalized);
        orthogonal = orthogonal.normalize();

        // 4. Chuyển đổi góc angle từ độ sang radian
        float angleRadians = angleDegrees * M_PI / 180.0;

        // 5. Tạo vector mới bằng cách kết hợp vector other và orthogonal với góc angle
        // Sử dụng công thức quay trực tiếp (vì mặt phẳng đã cố định)
        double newX = other_normalized.arr[0]; // Không thay đổi vì quay quanh trục X
        double newY = other_normalized.arr[1] * cos(angleRadians) - orthogonal.arr[1] * sin(angleRadians);
        double newZ = other_normalized.arr[1] * sin(angleRadians) + orthogonal.arr[1] * cos(angleRadians);

        // Gán giá trị mới cho vector hiện tại
        arr[0] = newX;
        arr[1] = newY;
        arr[2] = newZ;

        // 6. Chuẩn hóa vector kết quả (tùy chọn)
        Vector normalizedResult = this->normalize();
        arr[0] = normalizedResult.arr[0];
        arr[1] = normalizedResult.arr[1];
        arr[2] = normalizedResult.arr[2];
    }
    void rotateAroundZAxis(const Vector& other, float angleZ)
    {
        // 1. Chuẩn hóa vector other
        Vector other_normalized = other.normalize();

        // 2. Tạo vector pháp tuyến của mặt phẳng chứa vector other và vuông góc với OXY (Z-axis)
        Vector zAxis(0.0);
        zAxis.arr[2] = 1.0;
        Vector normal = other_normalized.crossProduct(zAxis);
        normal = normal.normalize();

        // 3. Tạo vector vuông góc với other và nằm trong mặt phẳng đã tạo ở bước 2
        Vector orthogonal = normal.crossProduct(other_normalized);
        orthogonal = orthogonal.normalize();

        // 4. Chuyển đổi góc angleZ từ độ sang radian (nếu cần, tùy thuộc vào đơn vị của angleZ)
        float angleRad = angleZ * M_PI / 180.0;  // Giả sử angleZ là độ

        // 5. Tạo vector mới bằng cách kết hợp vector other và orthogonal với góc angleZ.
        //    Sử dụng công thức Rodrigues' rotation formula hoặc tính toán trực tiếp dựa trên góc.
        //    Ở đây, mình sử dụng cách tính trực tiếp đơn giản hơn (vì mặt phẳng đã cố định).
        GLdouble newX = other_normalized.arr[0] * cos(angleRad) + orthogonal.arr[0] * sin(angleRad);
        GLdouble newY = other_normalized.arr[1] * cos(angleRad) + orthogonal.arr[1] * sin(angleRad);
        GLdouble newZ = other_normalized.arr[2] * cos(angleRad) + orthogonal.arr[2] * sin(angleRad);

        arr[0] = newX;
        arr[1] = newY;
        arr[2] = newZ;

        // 6. Chuẩn hóa vector kết quả (tùy chọn, để đảm bảo vector có độ dài bằng 1)
        Vector normalizedResult = this->normalize();
        arr[0] = normalizedResult.arr[0];
        arr[1] = normalizedResult.arr[1];
        arr[2] = normalizedResult.arr[2];
    }
    Vector(GLdouble x = 0, GLdouble y = 0, GLdouble z = 0)
    {
        arr[0] = x;
        arr[1] = y;
        arr[2] = z;
    }
    friend ostream& operator<<(ostream& os, Vector v)
    {
        os << "[x] :" << v.arr[0] << endl;
        os << "[y] :" << v.arr[1] << endl;
        os << "[z] :" << v.arr[2] << endl;
        return os;
    }
    void operator=(const Vector v)
    {
        this->arr[0] = v.arr[0];
        this->arr[1] = v.arr[1];
        this->arr[2] = v.arr[2];
    }
    void horizontal(const Vector& other) {
        // Vector đầu vào
        GLdouble x = other.arr[0];
        GLdouble y = other.arr[1];
        GLdouble z = other.arr[2];

        // Kiểm tra xem vector có nằm trong mặt phẳng song song với OXY không
        if (z != 0.0) {
            cerr << "Error: Input vector must be parallel to OXY plane." << std::endl;
            // Có thể xử lý lỗi theo cách khác, ví dụ: ném exception
            arr[0] = 0.0;
            arr[1] = 0.0;
            arr[2] = 0.0;
            return;
        }

        // Tính toán vector vuông góc (đổi chỗ x và y, đổi dấu một trong hai)
        arr[0] = -y;
        arr[1] = x;
        arr[2] = 0.0;

        // Chuẩn hóa vector
        GLdouble length = sqrt(arr[0] * arr[0] + arr[1] * arr[1]);
        if (length != 0.0) {
            arr[0] /= length;
            arr[1] /= length;
        } else {
            std::cerr << "Error: Input vector has zero length." << std::endl;
            // Xử lý lỗi nếu vector đầu vào có độ dài bằng 0
            arr[0] = 0.0;
            arr[1] = 0.0;
            arr[2] = 0.0;
        }
    }
    void vertical(float angleX)
    {
        // Chuyển đổi góc từ độ sang radian
        float angleRad = angleX * M_PI / 180.0f;

        // Tính toán các thành phần của vector đơn vị
        arr[0] = cos(angleRad); // Thành phần X
        arr[1] = sin(angleRad); // Thành phần Y
        arr[2] = 0.0;         // Thành phần Z (để nằm trong mặt phẳng OXY)
    }
    void setValue(GLdouble x, GLdouble y, GLdouble z)
    {
        arr[0] = x;
        arr[1] = y;
        arr[2] = z;
    }
};
struct Point
{
    //attributes
    GLdouble arr[3];

    //methods
    Point(GLdouble x = 0, GLdouble y = 0, GLdouble z = 0)
    {
        arr[0] = x;
        arr[1] = y;
        arr[2] = z;
    }
    Point(const Point& p)
    {
        this->arr[0] = p.arr[0];
        this->arr[1] = p.arr[1];
        this->arr[2] = p.arr[2];
    }
    void operator=(const Point& p)
    {
        this->arr[0] = p.arr[0];
        this->arr[1] = p.arr[1];
        this->arr[2] = p.arr[2];
    }
    friend ostream& operator<< (ostream& os, Point p)
    {
        os << "[x]: " << p.arr[0] << endl;
        os << "[y]: " << p.arr[1] << endl;
        os << "[z]: " << p.arr[2] << endl;
        return os;
    }
    void move(const Vector& direction, float move)
    {
        // Chuẩn hóa vector hướng (đảm bảo độ dài bằng 1)
        GLdouble directionX = direction.arr[0];
        GLdouble directionY = direction.arr[1];
        GLdouble directionZ = direction.arr[2];

        GLdouble length = sqrt(directionX * directionX + directionY * directionY + directionZ * directionZ);

        if (length == 0.0) {
            std::cerr << "Error: Direction vector has zero length!" << std::endl;
            // Xử lý lỗi nếu vector hướng có độ dài bằng 0
            return;
        }

        GLdouble normalizedDirectionX = directionX / length;
        GLdouble normalizedDirectionY = directionY / length;
        GLdouble normalizedDirectionZ = directionZ / length;

        // Thay đổi tọa độ của Point
        arr[0] += move * normalizedDirectionX;
        arr[1] += move * normalizedDirectionY;
        arr[2] += move * normalizedDirectionZ;
    }
    void setValue(GLdouble x, GLdouble y, GLdouble z)
    {
        arr[0] = x;
        arr[1] = y;
        arr[2] = z;
    }
};

void normalizeAngle(float& angle);
void drawFloor(double size, int divisions, Color color);
void drawButton(float x, float y, float width, float height, Color background);
void drawWireSphere(Point center, float radius, Color color);
void drawSolidSphere(Point center, float radius, Color color);
double distanceTwoPoint(Point p1, Point p2);
void drawMissingCylinderOutline(float radius, float height, Point center, Vector normal, Color color, float angleStart, float angleEnd);
void drawMissingCylinder(float radius, float height, float thickness, Point center, Vector normal, Color color, float angleStart, float angleEnd);
Vector normalize(const Vector& v);
Vector crossProduct(const Vector& v1, const Vector& v2);
GLdouble dotProduct(const Vector& v1, const Vector& v2);
void rotateVector(Vector& v, float angleZ);
void VectorRotationMethod(Vector& current, const Vector& other, float angleZ);
void drawLine(Vector direction, Point start, float length, Color color);
void drawBoxOutline(float length, float width, float height, Vector direction, Point center, Color color);
void drawBox(float length, float width, float height, Vector direction, Point center, Color color);
void drawCylinderOutline(float radius, float height, Point center, Vector normal, Color color);
void drawCylinderWithCaps(float radius, float height, float thickness, Point center, Vector normal, Color color);
void setColor(Color color);


#endif
