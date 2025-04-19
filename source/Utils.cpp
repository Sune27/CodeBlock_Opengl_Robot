#include "../include/Utils.h"
#include "../include/Config.h"
using namespace std;

void drawX(int x, int y, int width, int height, Color color)
{
    // Thiết lập màu đỏ
    setColor(RED);

    // Vẽ đường chéo từ góc trên bên trái đến góc dưới bên phải
    glBegin(GL_LINES);
        glVertex2i(x, y + height); // Góc trên bên trái
        glVertex2i(x + width, y);    // Góc dưới bên phải
    glEnd();

    // Vẽ đường chéo từ góc dưới bên trái đến góc trên bên phải
    glBegin(GL_LINES);
        glVertex2i(x, y);          // Góc dưới bên trái
        glVertex2i(x + width, y + height); // Góc trên bên phải
    glEnd();
}
void drawArcSegment(float centerX, float centerY, float radius, float startAngle, float endAngle, int segments)
{
    glBegin(GL_LINE_STRIP); // Sử dụng GL_LINE_STRIP để nối các đoạn thẳng
    for (int i = 0; i <= segments; ++i) {
      float angle = startAngle + (endAngle - startAngle) * i / segments;
      float x = centerX + radius * cosf(angle);
      float y = centerY + radius * sinf(angle);
      glVertex2f(x, y);
    }
    glEnd();
}

void drawOpenU(int x, int y, int width, int height, Color color)
{
    // Thiết lập màu vẽ
    setColor(color);

    // Tính toán các tham số
    float centerX = x + width / 2.0f;
    float centerY = y + height / 2.0f;
    float radius = std::min(width, height) / 2.0f * 0.8f; // Bán kính, nhỏ hơn để có khoảng trống
    int segments = 30; // Số lượng đoạn thẳng để vẽ cung

    // Độ hở giữa hai cung
    float gapAngle = 60.0; // Ví dụ: 5 độ

    // Vẽ cung bên trái
    drawArcSegment(centerX, centerY, radius, 180 + gapAngle, 270, segments); // Bắt đầu từ 180 độ (bên trái)

    // Vẽ cung bên phải
    drawArcSegment(centerX, centerY, radius, 270, 360 - gapAngle , segments);  // Đến 360 độ (bên phải)
}
void drawArrow(int x, int y, int width, int height, int direction, Color color)
{
    // Thiết lập màu đen
    setColor(color);

    // Tính toán các điểm vẽ
    float centerX = x + width / 2.0f;
    float centerY = y + height / 2.0f;
    float arrowSize = std::min(width, height) / 3.0f; // Kích thước mũi tên

    glBegin(GL_TRIANGLES);

    if (direction == 3) { // Left
        // Đầu mũi tên
        glVertex2f(x + width / 2, centerY);
        glVertex2f(x, centerY + height / 4);
        glVertex2f(x, centerY - height / 4);
    } else if (direction == 2) { // Up
        // Đầu mũi tên
        glVertex2f(centerX, y+ height/2);
        glVertex2f(centerX + width / 4, y + height);
        glVertex2f(centerX - width / 4, y + height);
    } else if (direction == 1) { // Right
        // Đầu mũi tên
        glVertex2f(x + width/2, centerY);
        glVertex2f(x + width, centerY + height / 4);
        glVertex2f(x + width, centerY - height / 4);
    } else if (direction == 4) { // Down
      // Đầu mũi tên
      glVertex2f(centerX, y+ height/2);
      glVertex2f(centerX + width / 4, y);
      glVertex2f(centerX - width / 4, y);
    }

    glEnd();
}
void drawText(int x, int y, const string& str, Color color)
{
    // Thiết lập màu chữ
    setColor(color);

    // Thiết lập vị trí raster
    glRasterPos2i(x, y); // Sử dụng glRasterPos2i cho tọa độ integer

    // Vẽ từng ký tự trong chuỗi
    for (char c : str) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c); // Hoặc một font khác
    }
}

void normalizeAngle(float& angle)
{
    angle = fmod(angle, 360.0f);
    if (angle < 0) {
        angle += 360.0f;
    }
}

void drawFloor(double size = 10.0, int divisions = 10, Color color = GRAY) {
    glBegin(GL_QUADS);

    setColor(color);
    for (int i = -divisions; i < divisions; ++i)
    {
        for (int j = -divisions; j < divisions; ++j)
        {
            double x1 = i * size / divisions;
            double y1 = j * size / divisions;
            double x2 = (i + 1) * size / divisions;
            double y2 = (j + 1) * size / divisions;

            glNormal3f(0.0f, 0.0f, 1.0f); // Normal hướng lên trên (trục Z)

            glVertex3f(x1, y1, 0.0f);
            glVertex3f(x2, y1, 0.0f);
            glVertex3f(x2, y2, 0.0f);
            glVertex3f(x1, y2, 0.0f);
        }
    }
    glEnd();
}

void drawButton(float x, float y, float width, float height, Color background)
{
    setColor(background);
    glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + width, y);
        glVertex2f(x + width, y + height);
        glVertex2f(x, y + height);
    glEnd();

    // setColor(textColor);
    // glRasterPos2f(x + width / 2 - glutBitmapLength(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)text) / 2, y + height / 2 - 6); // Căn giữa text
    // for (const char* c = text; *c != '\0'; c++)
    // {
    //     glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    // }
}

void drawWireSphere(Point center, float radius, Color color)
{
    int slices = 5, stacks = 5;
    glPushMatrix(); // Lưu lại ma trận hiện tại

    // Di chuyển đến tâm hình cầu
    glTranslated(center.arr[0], center.arr[1], center.arr[2]);

    setColor(color);
    glutWireSphere(radius, slices, stacks);

    glPopMatrix(); // Khôi phục ma trận trước đó
}

void drawSolidSphere(Point center, float radius, Color color)
{
    int slices = 30, stacks = 30;
    glPushMatrix(); // Lưu lại ma trận hiện tại

    // Di chuyển đến tâm hình cầu
    glTranslated(center.arr[0], center.arr[1], center.arr[2]);

    setColor(color);
    glutSolidSphere(radius, slices, stacks);

    glPopMatrix(); // Khôi phục ma trận trước đó
}
double distanceTwoPoint(Point p1, Point p2)
{
    double dx = p1.arr[0] - p2.arr[0];
    double dy = p1.arr[1] - p2.arr[1];
    double dz = p1.arr[2] - p2.arr[2];
    return sqrt(dx * dx + dy * dy + dz * dz);
}
void drawMissingCylinderOutline(float radius, float height, Point center, Vector normal, Color color, float angleStart, float angleEnd)
{
    // Chuẩn hóa vector pháp tuyến
    GLdouble normalX = normal.arr[0];
    GLdouble normalY = normal.arr[1];
    GLdouble normalZ = normal.arr[2];
    GLdouble length = sqrt(normalX * normalX + normalY * normalY + normalZ * normalZ);
    GLdouble normalizedNormalX = normalX / length;
    GLdouble normalizedNormalY = normalY / length;
    GLdouble normalizedNormalZ = normalZ / length;

    // Tính toán vector tiếp tuyến và bitangent
    GLdouble tangentX, tangentY, tangentZ;
    if (normalizedNormalZ != 1.0f && normalizedNormalZ != -1.0f) {
        tangentX = normalizedNormalY;
        tangentY = -normalizedNormalX;
        tangentZ = 0.0f;
    } else {
        tangentX = 1.0f;
        tangentY = 0.0f;
        tangentZ = 0.0f;
    }

    length = sqrt(tangentX * tangentX + tangentY * tangentY + tangentZ * tangentZ);
    tangentX /= length;
    tangentY /= length;
    tangentZ /= length;

    GLdouble bitangentX = normalizedNormalY * tangentZ - normalizedNormalZ * tangentY;
    GLdouble bitangentY = normalizedNormalZ * tangentX - normalizedNormalX * tangentZ;
    GLdouble bitangentZ = normalizedNormalX * tangentY - normalizedNormalY * tangentX;

    // Lấy tọa độ tâm
    GLdouble centerX = center.arr[0];
    GLdouble centerY = center.arr[1];
    GLdouble centerZ = center.arr[2];

    setColor(color); // Đặt màu cho viền
    glLineWidth(LINE_WIDTH); // Độ dày của đường viền

    // Chuyển đổi góc từ độ sang radian
    float startAngleRad = angleStart * M_PI / 180.0f;
    float endAngleRad = angleEnd * M_PI / 180.0f;
    float angleIncrement = (endAngleRad - startAngleRad) / NUM_SEGMENTS;

    // Vẽ các đường tròn ở đáy và đỉnh
    glBegin(GL_LINE_STRIP); // Sử dụng LINE_STRIP để vẽ các vòng tròn không kín
        for (int i = 0; i <= NUM_SEGMENTS; ++i) {
            float angleRad = startAngleRad + i * angleIncrement;
            float x = radius * cos(angleRad);
            float y = radius * sin(angleRad);

            // Tính toán vị trí đỉnh trên mặt phẳng hình tròn
            GLdouble pointX = centerX + x * tangentX + y * bitangentX;
            GLdouble pointY = centerY + x * tangentY + y * bitangentY;
            GLdouble pointZ = centerZ + x * tangentZ + y * bitangentZ;

            // Tính toán vị trí đỉnh trên mặt phẳng hình tròn (đỉnh dưới)
            GLdouble bottomPointX = pointX - normalizedNormalX * height / 2.0f;
            GLdouble bottomPointY = pointY - normalizedNormalY * height / 2.0f;
            GLdouble bottomPointZ = pointZ - normalizedNormalZ * height / 2.0f;

            glVertex3d(bottomPointX, bottomPointY, bottomPointZ);
        }
    glEnd();

    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= NUM_SEGMENTS; ++i) {
        float angleRad = startAngleRad + i * angleIncrement;
        float x = radius * cos(angleRad);
        float y = radius * sin(angleRad);

        // Tính toán vị trí đỉnh trên mặt phẳng hình tròn
        GLdouble pointX = centerX + x * tangentX + y * bitangentX;
        GLdouble pointY = centerY + x * tangentY + y * bitangentY;
        GLdouble pointZ = centerZ + x * tangentZ + y * bitangentZ;

        // Tính toán vị trí đỉnh trên mặt phẳng hình tròn (đỉnh trên)
        GLdouble topPointX = pointX + normalizedNormalX * height / 2.0f;
        GLdouble topPointY = pointY + normalizedNormalY * height / 2.0f;
        GLdouble topPointZ = pointZ + normalizedNormalZ * height / 2.0f;

        glVertex3d(topPointX, topPointY, topPointZ);
    }
    glEnd();

   //Vẽ 2 đường nối
   float angleRad = startAngleRad;
    float x = radius * cos(angleRad);
    float y = radius * sin(angleRad);

    GLdouble pointX = centerX + x * tangentX + y * bitangentX;
    GLdouble pointY = centerY + x * tangentY + y * bitangentY;
    GLdouble pointZ = centerZ + x * tangentZ + y * bitangentZ;

    GLdouble topPointX = pointX + normalizedNormalX * height / 2.0f;
    GLdouble topPointY = pointY + normalizedNormalY * height / 2.0f;
    GLdouble topPointZ = pointZ + normalizedNormalZ * height / 2.0f;

    GLdouble bottomPointX = pointX - normalizedNormalX * height / 2.0f;
    GLdouble bottomPointY = pointY - normalizedNormalY * height / 2.0f;
    GLdouble bottomPointZ = pointZ - normalizedNormalZ * height / 2.0f;

    glBegin(GL_LINES);
        glVertex3d(bottomPointX, bottomPointY, bottomPointZ);
        glVertex3d(topPointX, topPointY, topPointZ);
    glEnd();

    angleRad = endAngleRad;
    x = radius * cos(angleRad);
    y = radius * sin(angleRad);

    pointX = centerX + x * tangentX + y * bitangentX;
    pointY = centerY + x * tangentY + y * bitangentY;
    pointZ = centerZ + x * tangentZ + y * bitangentZ;

    topPointX = pointX + normalizedNormalX * height / 2.0f;
    topPointY = pointY + normalizedNormalY * height / 2.0f;
    topPointZ = pointZ + normalizedNormalZ * height / 2.0f;

    bottomPointX = pointX - normalizedNormalX * height / 2.0f;
    bottomPointY = pointY - normalizedNormalY * height / 2.0f;
    bottomPointZ = pointZ - normalizedNormalZ * height / 2.0f;

    glBegin(GL_LINES);
        glVertex3d(bottomPointX, bottomPointY, bottomPointZ);
        glVertex3d(topPointX, topPointY, topPointZ);
    glEnd();
}

void drawMissingCylinder(float radius, float height, float thickness, Point center, Vector normal, Color color, float angleStart, float angleEnd)
{
    setColor(color);
    // Chuẩn hóa vector pháp tuyến
    GLdouble normalX = normal.arr[0];
    GLdouble normalY = normal.arr[1];
    GLdouble normalZ = normal.arr[2];
    GLdouble length = sqrt(normalX * normalX + normalY * normalY + normalZ * normalZ);
    GLdouble normalizedNormalX = normalX / length;
    GLdouble normalizedNormalY = normalY / length;
    GLdouble normalizedNormalZ = normalZ / length;

    // Tính toán vector tiếp tuyến và bitangent
    GLdouble tangentX, tangentY, tangentZ;
    if (normalizedNormalZ != 1.0f && normalizedNormalZ != -1.0f)
    {
        tangentX = normalizedNormalY;
        tangentY = -normalizedNormalX;
        tangentZ = 0.0f;
    } else
    {
        tangentX = 1.0f;
        tangentY = 0.0f;
        tangentZ = 0.0f;
    }

    length = sqrt(tangentX * tangentX + tangentY * tangentY + tangentZ * tangentZ);
    tangentX /= length;
    tangentY /= length;
    tangentZ /= length;

    GLdouble bitangentX = normalizedNormalY * tangentZ - normalizedNormalZ * tangentY;
    GLdouble bitangentY = normalizedNormalZ * tangentX - normalizedNormalX * tangentZ;
    GLdouble bitangentZ = normalizedNormalX * tangentY - normalizedNormalY * tangentX;

    //Chuyển góc từ độ sang radian
    float startAngleRad = angleStart * M_PI / 180.0f;
    float endAngleRad = angleEnd * M_PI / 180.0f;
    float angleIncrement = (endAngleRad - startAngleRad) / NUM_SEGMENTS;

    // Lấy các giá trị tâm từ struct Point
    GLdouble centerX = center.arr[0];
    GLdouble centerY = center.arr[1];
    GLdouble centerZ = center.arr[2];

    // Vẽ thân hình trụ
    glBegin(GL_QUAD_STRIP);
        for (int i = 0; i <= NUM_SEGMENTS; ++i)
        {
            float angleRad = startAngleRad + i * angleIncrement;
            float x = radius * cos(angleRad);
            float y = radius * sin(angleRad);

            // Tính toán vị trí đỉnh trên mặt phẳng hình tròn
            GLdouble pointX = centerX + x * tangentX + y * bitangentX;
            GLdouble pointY = centerY + x * tangentY + y * bitangentY;
            GLdouble pointZ = centerZ + x * tangentZ + y * bitangentZ;

            // Tính toán vị trí đỉnh trên mặt phẳng hình tròn (đỉnh trên)
            GLdouble topPointX = pointX + normalizedNormalX * height / 2.0f;
            GLdouble topPointY = pointY + normalizedNormalY * height / 2.0f;
            GLdouble topPointZ = pointZ + normalizedNormalZ * height / 2.0f;

            // Tính toán vị trí đỉnh trên mặt phẳng hình tròn (đỉnh dưới)
            GLdouble bottomPointX = pointX - normalizedNormalX * height / 2.0f;
            GLdouble bottomPointY = pointY - normalizedNormalY * height / 2.0f;
            GLdouble bottomPointZ = pointZ - normalizedNormalZ * height / 2.0f;

            glVertex3d(bottomPointX, bottomPointY, bottomPointZ);
            glVertex3d(topPointX, topPointY, topPointZ);
        }
    glEnd();

    // Vẽ nắp trên hình trụ
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= NUM_SEGMENTS; ++i)
        {
            float angleRad = startAngleRad + i * angleIncrement;
            float x = radius * cos(angleRad);
            float y = radius * sin(angleRad);

            // Tính toán vị trí đỉnh trên mặt phẳng hình tròn
            GLdouble pointX = centerX + x * tangentX + y * bitangentX;
            GLdouble pointY = centerY + x * tangentY + y * bitangentY;
            GLdouble pointZ = centerZ + x * tangentZ + y * bitangentZ;

            // Tính toán vị trí đỉnh trên mặt phẳng hình tròn (đỉnh trên)
            GLdouble topPointX = pointX + normalizedNormalX * height / 2.0f;
            GLdouble topPointY = pointY + normalizedNormalY * height / 2.0f;
            GLdouble topPointZ = pointZ + normalizedNormalZ * height / 2.0f;

            // Tính toán vị trí đỉnh bên trong (để tạo độ dày)
            float innerX = (radius - thickness) * cos(angleRad);
            float innerY = (radius - thickness) * sin(angleRad);

            GLdouble innerPointX = centerX + innerX * tangentX + innerY * bitangentX;
            GLdouble innerPointY = centerY + innerX * tangentY + innerY * bitangentY;
            GLdouble innerPointZ = centerZ + innerX * tangentZ + innerY * bitangentZ;

            // Tính toán vị trí đỉnh bên trong (để tạo độ dày) trên nắp
            GLdouble innerTopPointX = innerPointX + normalizedNormalX * height / 2.0f;
            GLdouble innerTopPointY = innerPointY + normalizedNormalY * height / 2.0f;
            GLdouble innerTopPointZ = innerPointZ + normalizedNormalZ * height / 2.0f;

            glVertex3d(topPointX, topPointY, topPointZ);
            glVertex3d(innerTopPointX, innerTopPointY, innerTopPointZ);
        }
    glEnd();

    // Vẽ nắp dưới hình trụ
    glBegin(GL_QUAD_STRIP);
        for (int i = 0; i <= NUM_SEGMENTS; ++i)
        {
            float angleRad = startAngleRad + i * angleIncrement;
            float x = radius * cos(angleRad);
            float y = radius * sin(angleRad);

            // Tính toán vị trí đỉnh trên mặt phẳng hình tròn
            GLdouble pointX = centerX + x * tangentX + y * bitangentX;
            GLdouble pointY = centerY + x * tangentY + y * bitangentY;
            GLdouble pointZ = centerZ + x * tangentZ + y * bitangentZ;

            // Tính toán vị trí đỉnh trên mặt phẳng hình tròn (đỉnh trên)
            GLdouble bottomPointX = pointX - normalizedNormalX * height / 2.0f;
            GLdouble bottomPointY = pointY - normalizedNormalY * height / 2.0f;
            GLdouble bottomPointZ = pointZ - normalizedNormalZ * height / 2.0f;

            // Tính toán vị trí đỉnh bên trong (để tạo độ dày)
            float innerX = (radius - thickness) * cos(angleRad);
            float innerY = (radius - thickness) * sin(angleRad);

            GLdouble innerPointX = centerX + innerX * tangentX + innerY * bitangentX;
            GLdouble innerPointY = centerY + innerX * tangentY + innerY * bitangentY;
            GLdouble innerPointZ = centerZ + innerX * tangentZ + innerY * bitangentZ;

            // Tính toán vị trí đỉnh bên trong (để tạo độ dày) trên nắp
            GLdouble innerBottomPointX = innerPointX - normalizedNormalX * height / 2.0f;
            GLdouble innerBottomPointY = innerPointY - normalizedNormalY * height / 2.0f;
            GLdouble innerBottomPointZ = innerPointZ - normalizedNormalZ * height / 2.0f;

            glVertex3d(bottomPointX, bottomPointY, bottomPointZ);
            glVertex3d(innerBottomPointX, innerBottomPointY, innerBottomPointZ);
        }
    glEnd();
}


// Hàm chuẩn hóa vector
Vector normalize(const Vector& v)
{
    GLdouble magnitude = std::sqrt(v.arr[0] * v.arr[0] + v.arr[1] * v.arr[1] + v.arr[2] * v.arr[2]);
    Vector result;
    if (magnitude > 1e-9) { // Tránh chia cho 0
        result.arr[0] = v.arr[0] / magnitude;
        result.arr[1] = v.arr[1] / magnitude;
        result.arr[2] = v.arr[2] / magnitude;
    } else {
        result.arr[0] = 0.0;
        result.arr[1] = 0.0;
        result.arr[2] = 0.0;
    }
    return result;
}

// Hàm tính tích có hướng
Vector crossProduct(const Vector& v1, const Vector& v2)
{
    Vector result;
    result.arr[0] = v1.arr[1] * v2.arr[2] - v1.arr[2] * v2.arr[1];
    result.arr[1] = v1.arr[2] * v2.arr[0] - v1.arr[0] * v2.arr[2];
    result.arr[2] = v1.arr[0] * v2.arr[1] - v1.arr[1] * v2.arr[0];
    return result;
}

// Hàm tính tích vô hướng
GLdouble dotProduct(const Vector& v1, const Vector& v2)
{
    return v1.arr[0] * v2.arr[0] + v1.arr[1] * v2.arr[1] + v1.arr[2] * v2.arr[2];
}

void rotateVector(Vector& v, float angleZ)
{
    float cosAngle = cos(angleZ);
    float sinAngle = sin(angleZ);

    GLdouble x = v.arr[0];
    GLdouble y = v.arr[1];

    v.arr[0] = x * cosAngle - y * sinAngle;
    v.arr[1] = x * sinAngle + y * cosAngle;
}

void VectorRotationMethod(Vector& current, const Vector& other, float angleZ)
{
    // 1. Chuẩn hóa vector other
    Vector other_normalized = normalize(other);

    // 2. Tạo vector pháp tuyến của mặt phẳng chứa vector other và vuông góc với OXY (Z-axis)
    Vector zAxis(0,0,1);
    Vector normal = crossProduct(other_normalized, zAxis);
    normal = normalize(normal);

    // 3. Tạo vector vuông góc với other và nằm trong mặt phẳng đã tạo ở bước 2
    Vector orthogonal = crossProduct(normal, other_normalized);
    orthogonal = normalize(orthogonal);

    // 4. Chuyển đổi góc angleZ từ độ sang radian (nếu cần, tùy thuộc vào đơn vị của angleZ)
    float angleRad = angleZ * M_PI / 180.0;  // Giả sử angleZ là độ

    // 5. Tạo vector mới bằng cách kết hợp vector other và orthogonal với góc angleZ.
    //    Sử dụng công thức Rodrigues' rotation formula hoặc tính toán trực tiếp dựa trên góc.
    //    Ở đây, mình sử dụng cách tính trực tiếp đơn giản hơn (vì mặt phẳng đã cố định).
    current.arr[0] = other_normalized.arr[0] * cos(angleRad) + orthogonal.arr[0] * sin(angleRad);
    current.arr[1] = other_normalized.arr[1] * cos(angleRad) + orthogonal.arr[1] * sin(angleRad);
    current.arr[2] = other_normalized.arr[2] * cos(angleRad) + orthogonal.arr[2] * sin(angleRad);

    // 6. Chuẩn hóa vector kết quả (tùy chọn, để đảm bảo vector có độ dài bằng 1)
    current = normalize(current);

}

void drawLine(Vector direction, Point start, float length, Color color)
{
    // Chuẩn hóa vector hướng (đảm bảo độ dài bằng 1)
    GLdouble directionX = direction.arr[0];
    GLdouble directionY = direction.arr[1];
    GLdouble directionZ = direction.arr[2];

    GLdouble lengthDir = sqrt(directionX * directionX + directionY * directionY + directionZ * directionZ);

    // Kiểm tra trường hợp độ dài vector = 0
    if (lengthDir == 0.0) {
        std::cerr << "Error: Direction vector has zero length!" << std::endl;
        return; // Hoặc xử lý lỗi theo cách khác phù hợp
    }

    GLdouble normalizedDirectionX = directionX / lengthDir;
    GLdouble normalizedDirectionY = directionY / lengthDir;
    GLdouble normalizedDirectionZ = directionZ / lengthDir;

    // Tính toán điểm kết thúc
    GLdouble endX = start.arr[0] + length * normalizedDirectionX;
    GLdouble endY = start.arr[1] + length * normalizedDirectionY;
    GLdouble endZ = start.arr[2] + length * normalizedDirectionZ;

    setColor(color);
    glLineWidth(LINE_WIDTH); // Độ dày của đường thẳng

    glBegin(GL_LINES);
        glVertex3d(start.arr[0], start.arr[1], start.arr[2]);
        glVertex3d(endX, endY, endZ);
    glEnd();
}

void drawBoxOutline(float length, float width, float height, Vector direction, Point center, Color color)
{
    // Chuẩn hóa vector chỉ phương
    GLdouble directionX = direction.arr[0];
    GLdouble directionY = direction.arr[1];
    GLdouble directionZ = direction.arr[2];

    GLdouble lengthDir = sqrt(directionX * directionX + directionY * directionY + directionZ * directionZ);
    GLdouble normalizedDirectionX = directionX / lengthDir;
    GLdouble normalizedDirectionY = directionY / lengthDir;
    GLdouble normalizedDirectionZ = directionZ / lengthDir;

    // Tính toán vector tiếp tuyến và bitangent (vuông góc với vector chỉ phương)
    GLdouble tangentX, tangentY, tangentZ;
    if (normalizedDirectionZ != 1.0f && normalizedDirectionZ != -1.0f)
    {
        tangentX = normalizedDirectionY;
        tangentY = -normalizedDirectionX;
        tangentZ = 0.0f;
    } else
    {
        tangentX = 1.0f;
        tangentY = 0.0f;
        tangentZ = 0.0f;
    }

    lengthDir = sqrt(tangentX * tangentX + tangentY * tangentY + tangentZ * tangentZ);
    tangentX /= lengthDir;
    tangentY /= lengthDir;
    tangentZ /= lengthDir;

    GLdouble bitangentX = normalizedDirectionY * tangentZ - normalizedDirectionZ * tangentY;
    GLdouble bitangentY = normalizedDirectionZ * tangentX - normalizedDirectionX * tangentZ;
    GLdouble bitangentZ = normalizedDirectionX * tangentY - normalizedDirectionY * tangentX;

    // Lấy tọa độ tâm
    GLdouble centerX = center.arr[0];
    GLdouble centerY = center.arr[1];
    GLdouble centerZ = center.arr[2];

    setColor(color);
    glLineWidth(LINE_WIDTH); // Độ dày của đường viền

    // Vẽ các cạnh của hình hộp chữ nhật
    glBegin(GL_LINES);

        // Mặt trước
        glVertex3d(centerX - length / 2.0f * tangentX - width / 2.0f * bitangentX + height/2.0f * normalizedDirectionX,
        centerY - length / 2.0f * tangentY - width / 2.0f * bitangentY + height/2.0f * normalizedDirectionY,
        centerZ - length / 2.0f * tangentZ - width / 2.0f * bitangentZ + height/2.0f * normalizedDirectionZ);
        glVertex3d(centerX + length / 2.0f * tangentX - width / 2.0f * bitangentX + height/2.0f * normalizedDirectionX,
        centerY + length / 2.0f * tangentY - width / 2.0f * bitangentY + height/2.0f * normalizedDirectionY,
        centerZ + length / 2.0f * tangentZ - width / 2.0f * bitangentZ + height/2.0f * normalizedDirectionZ);

        glVertex3d(centerX + length / 2.0f * tangentX - width / 2.0f * bitangentX + height/2.0f * normalizedDirectionX,
        centerY + length / 2.0f * tangentY - width / 2.0f * bitangentY + height/2.0f * normalizedDirectionY,
        centerZ + length / 2.0f * tangentZ - width / 2.0f * bitangentZ + height/2.0f * normalizedDirectionZ);
        glVertex3d(centerX + length / 2.0f * tangentX + width / 2.0f * bitangentX + height/2.0f * normalizedDirectionX,
        centerY + length / 2.0f * tangentY + width / 2.0f * bitangentY + height/2.0f * normalizedDirectionY,
        centerZ + length / 2.0f * tangentZ + width / 2.0f * bitangentZ + height/2.0f * normalizedDirectionZ);

        glVertex3d(centerX + length / 2.0f * tangentX + width / 2.0f * bitangentX + height/2.0f * normalizedDirectionX,
        centerY + length / 2.0f * tangentY + width / 2.0f * bitangentY + height/2.0f * normalizedDirectionY,
        centerZ + length / 2.0f * tangentZ + width / 2.0f * bitangentZ + height/2.0f * normalizedDirectionZ);
        glVertex3d(centerX - length / 2.0f * tangentX + width / 2.0f * bitangentX + height/2.0f * normalizedDirectionX,
        centerY - length / 2.0f * tangentY + width / 2.0f * bitangentY + height/2.0f * normalizedDirectionY,
        centerZ - length / 2.0f * tangentZ + width / 2.0f * bitangentZ + height/2.0f * normalizedDirectionZ);

        glVertex3d(centerX - length / 2.0f * tangentX + width / 2.0f * bitangentX + height/2.0f * normalizedDirectionX,
        centerY - length / 2.0f * tangentY + width / 2.0f * bitangentY + height/2.0f * normalizedDirectionY,
        centerZ - length / 2.0f * tangentZ + width / 2.0f * bitangentZ + height/2.0f * normalizedDirectionZ);
        glVertex3d(centerX - length / 2.0f * tangentX - width / 2.0f * bitangentX + height/2.0f * normalizedDirectionX,
        centerY - length / 2.0f * tangentY - width / 2.0f * bitangentY + height/2.0f * normalizedDirectionY,
        centerZ - length / 2.0f * tangentZ - width / 2.0f * bitangentZ + height/2.0f * normalizedDirectionZ);

        // Mặt sau
        glVertex3d(centerX - length / 2.0f * tangentX - width / 2.0f * bitangentX - height/2.0f * normalizedDirectionX,
        centerY - length / 2.0f * tangentY - width / 2.0f * bitangentY - height/2.0f * normalizedDirectionY,
        centerZ - length / 2.0f * tangentZ - width / 2.0f * bitangentZ - height/2.0f * normalizedDirectionZ);
        glVertex3d(centerX + length / 2.0f * tangentX - width / 2.0f * bitangentX - height/2.0f * normalizedDirectionX,
        centerY + length / 2.0f * tangentY - width / 2.0f * bitangentY - height/2.0f * normalizedDirectionY,
        centerZ + length / 2.0f * tangentZ - width / 2.0f * bitangentZ - height/2.0f * normalizedDirectionZ);

        glVertex3d(centerX + length / 2.0f * tangentX - width / 2.0f * bitangentX - height/2.0f * normalizedDirectionX,
        centerY + length / 2.0f * tangentY - width / 2.0f * bitangentY - height/2.0f * normalizedDirectionY,
        centerZ + length / 2.0f * tangentZ - width / 2.0f * bitangentZ - height/2.0f * normalizedDirectionZ);
        glVertex3d(centerX + length / 2.0f * tangentX + width / 2.0f * bitangentX - height/2.0f * normalizedDirectionX,
        centerY + length / 2.0f * tangentY + width / 2.0f * bitangentY - height/2.0f * normalizedDirectionY,
        centerZ + length / 2.0f * tangentZ + width / 2.0f * bitangentZ - height/2.0f * normalizedDirectionZ);

        glVertex3d(centerX + length / 2.0f * tangentX + width / 2.0f * bitangentX - height/2.0f * normalizedDirectionX,
        centerY + length / 2.0f * tangentY + width / 2.0f * bitangentY - height/2.0f * normalizedDirectionY,
        centerZ + length / 2.0f * tangentZ + width / 2.0f * bitangentZ - height/2.0f * normalizedDirectionZ);
        glVertex3d(centerX - length / 2.0f * tangentX + width / 2.0f * bitangentX - height/2.0f * normalizedDirectionX,
        centerY - length / 2.0f * tangentY + width / 2.0f * bitangentY - height/2.0f * normalizedDirectionY,
        centerZ - length / 2.0f * tangentZ + width / 2.0f * bitangentZ - height/2.0f * normalizedDirectionZ);

        glVertex3d(centerX - length / 2.0f * tangentX + width / 2.0f * bitangentX - height/2.0f * normalizedDirectionX,
        centerY - length / 2.0f * tangentY + width / 2.0f * bitangentY - height/2.0f * normalizedDirectionY,
        centerZ - length / 2.0f * tangentZ + width / 2.0f * bitangentZ - height/2.0f * normalizedDirectionZ);
        glVertex3d(centerX - length / 2.0f * tangentX - width / 2.0f * bitangentX - height/2.0f * normalizedDirectionX,
        centerY - length / 2.0f * tangentY - width / 2.0f * bitangentY - height/2.0f * normalizedDirectionY,
        centerZ - length / 2.0f * tangentZ - width / 2.0f * bitangentZ - height/2.0f * normalizedDirectionZ);

        // Nối các đỉnh từ mặt trước ra mặt sau
        glVertex3d(centerX - length / 2.0f * tangentX - width / 2.0f * bitangentX + height/2.0f * normalizedDirectionX,
        centerY - length / 2.0f * tangentY - width / 2.0f * bitangentY + height/2.0f * normalizedDirectionY,
        centerZ - length / 2.0f * tangentZ - width / 2.0f * bitangentZ + height/2.0f * normalizedDirectionZ);
        glVertex3d(centerX - length / 2.0f * tangentX - width / 2.0f * bitangentX - height/2.0f * normalizedDirectionX,
        centerY - length / 2.0f * tangentY - width / 2.0f * bitangentY - height/2.0f * normalizedDirectionY,
        centerZ - length / 2.0f * tangentZ - width / 2.0f * bitangentZ - height/2.0f * normalizedDirectionZ);

        glVertex3d(centerX + length / 2.0f * tangentX - width / 2.0f * bitangentX + height/2.0f * normalizedDirectionX,
        centerY + length / 2.0f * tangentY - width / 2.0f * bitangentY + height/2.0f * normalizedDirectionY,
        centerZ + length / 2.0f * tangentZ - width / 2.0f * bitangentZ + height/2.0f * normalizedDirectionZ);
        glVertex3d(centerX + length / 2.0f * tangentX - width / 2.0f * bitangentX - height/2.0f * normalizedDirectionX,
        centerY + length / 2.0f * tangentY - width / 2.0f * bitangentY - height/2.0f * normalizedDirectionY,
        centerZ + length / 2.0f * tangentZ - width / 2.0f * bitangentZ - height/2.0f * normalizedDirectionZ);

        glVertex3d(centerX + length / 2.0f * tangentX + width / 2.0f * bitangentX + height/2.0f * normalizedDirectionX,
        centerY + length / 2.0f * tangentY + width / 2.0f * bitangentY + height/2.0f * normalizedDirectionY,
        centerZ + length / 2.0f * tangentZ + width / 2.0f * bitangentZ + height/2.0f * normalizedDirectionZ);
        glVertex3d(centerX + length / 2.0f * tangentX + width / 2.0f * bitangentX - height/2.0f * normalizedDirectionX,
        centerY + length / 2.0f * tangentY + width / 2.0f * bitangentY - height/2.0f * normalizedDirectionY,
        centerZ + length / 2.0f * tangentZ + width / 2.0f * bitangentZ - height/2.0f * normalizedDirectionZ);

        glVertex3d(centerX - length / 2.0f * tangentX + width / 2.0f * bitangentX + height/2.0f * normalizedDirectionX,
        centerY - length / 2.0f * tangentY + width / 2.0f * bitangentY + height/2.0f * normalizedDirectionY,
        centerZ - length / 2.0f * tangentZ + width / 2.0f * bitangentZ + height/2.0f * normalizedDirectionZ);
        glVertex3d(centerX - length / 2.0f * tangentX + width / 2.0f * bitangentX - height/2.0f * normalizedDirectionX,
        centerY - length / 2.0f * tangentY + width / 2.0f * bitangentY - height/2.0f * normalizedDirectionY,
        centerZ - length / 2.0f * tangentZ + width / 2.0f * bitangentZ - height/2.0f * normalizedDirectionZ);

    glEnd();
}

void drawBox(float length, float width, float height, Vector direction, Point center, Color color)
{
    // Chuẩn hóa vector chỉ phương
    GLdouble directionX = direction.arr[0];
    GLdouble directionY = direction.arr[1];
    GLdouble directionZ = direction.arr[2];

    GLdouble lengthDir = sqrt(directionX * directionX + directionY * directionY + directionZ * directionZ);
    GLdouble normalizedDirectionX = directionX / lengthDir;
    GLdouble normalizedDirectionY = directionY / lengthDir;
    GLdouble normalizedDirectionZ = directionZ / lengthDir;

    // Tính toán vector tiếp tuyến và bitangent (vuông góc với vector chỉ phương)
    GLdouble tangentX, tangentY, tangentZ;
    if (normalizedDirectionZ != 1.0f && normalizedDirectionZ != -1.0f)
    {
        tangentX = normalizedDirectionY;
        tangentY = -normalizedDirectionX;
        tangentZ = 0.0f;
    } else
    {
        tangentX = 1.0f;
        tangentY = 0.0f;
        tangentZ = 0.0f;
    }

    lengthDir = sqrt(tangentX * tangentX + tangentY * tangentY + tangentZ * tangentZ);
    tangentX /= lengthDir;
    tangentY /= lengthDir;
    tangentZ /= lengthDir;

    GLdouble bitangentX = normalizedDirectionY * tangentZ - normalizedDirectionZ * tangentY;
    GLdouble bitangentY = normalizedDirectionZ * tangentX - normalizedDirectionX * tangentZ;
    GLdouble bitangentZ = normalizedDirectionX * tangentY - normalizedDirectionY * tangentX;

    // Lấy tọa độ tâm
    GLdouble centerX = center.arr[0];
    GLdouble centerY = center.arr[1];
    GLdouble centerZ = center.arr[2];

    // Tính toán tọa độ 8 đỉnh của hình hộp chữ nhật
    GLdouble v1X = centerX - length / 2.0f * tangentX - width / 2.0f * bitangentX + height/2.0f * normalizedDirectionX;
    GLdouble v1Y = centerY - length / 2.0f * tangentY - width / 2.0f * bitangentY + height/2.0f * normalizedDirectionY;
    GLdouble v1Z = centerZ - length / 2.0f * tangentZ - width / 2.0f * bitangentZ + height/2.0f * normalizedDirectionZ;

    GLdouble v2X = centerX + length / 2.0f * tangentX - width / 2.0f * bitangentX + height/2.0f * normalizedDirectionX;
    GLdouble v2Y = centerY + length / 2.0f * tangentY - width / 2.0f * bitangentY + height/2.0f * normalizedDirectionY;
    GLdouble v2Z = centerZ + length / 2.0f * tangentZ - width / 2.0f * bitangentZ + height/2.0f * normalizedDirectionZ;

    GLdouble v3X = centerX + length / 2.0f * tangentX + width / 2.0f * bitangentX + height/2.0f * normalizedDirectionX;
    GLdouble v3Y = centerY + length / 2.0f * tangentY + width / 2.0f * bitangentY + height/2.0f * normalizedDirectionY;
    GLdouble v3Z = centerZ + length / 2.0f * tangentZ + width / 2.0f * bitangentZ + height/2.0f * normalizedDirectionZ;

    GLdouble v4X = centerX - length / 2.0f * tangentX + width / 2.0f * bitangentX + height/2.0f * normalizedDirectionX;
    GLdouble v4Y = centerY - length / 2.0f * tangentY + width / 2.0f * bitangentY + height/2.0f * normalizedDirectionY;
    GLdouble v4Z = centerZ - length / 2.0f * tangentZ + width / 2.0f * bitangentZ + height/2.0f * normalizedDirectionZ;

    GLdouble v5X = centerX - length / 2.0f * tangentX - width / 2.0f * bitangentX - height/2.0f * normalizedDirectionX;
    GLdouble v5Y = centerY - length / 2.0f * tangentY - width / 2.0f * bitangentY - height/2.0f * normalizedDirectionY;
    GLdouble v5Z = centerZ - length / 2.0f * tangentZ - width / 2.0f * bitangentZ - height/2.0f * normalizedDirectionZ;

    GLdouble v6X = centerX + length / 2.0f * tangentX - width / 2.0f * bitangentX - height/2.0f * normalizedDirectionX;
    GLdouble v6Y = centerY + length / 2.0f * tangentY - width / 2.0f * bitangentY - height/2.0f * normalizedDirectionY;
    GLdouble v6Z = centerZ + length / 2.0f * tangentZ - width / 2.0f * bitangentZ - height/2.0f * normalizedDirectionZ;

    GLdouble v7X = centerX + length / 2.0f * tangentX + width / 2.0f * bitangentX - height/2.0f * normalizedDirectionX;
    GLdouble v7Y = centerY + length / 2.0f * tangentY + width / 2.0f * bitangentY - height/2.0f * normalizedDirectionY;
    GLdouble v7Z = centerZ + length / 2.0f * tangentZ + width / 2.0f * bitangentZ - height/2.0f * normalizedDirectionZ;

    GLdouble v8X = centerX - length / 2.0f * tangentX + width / 2.0f * bitangentX - height/2.0f * normalizedDirectionX;
    GLdouble v8Y = centerY - length / 2.0f * tangentY + width / 2.0f * bitangentY - height/2.0f * normalizedDirectionY;
    GLdouble v8Z = centerZ - length / 2.0f * tangentZ + width / 2.0f * bitangentZ - height/2.0f * normalizedDirectionZ;

    // Vẽ hình hộp chữ nhật
    setColor(color);
    glBegin(GL_QUADS);
        // Mặt trước
        glNormal3d(normalizedDirectionX, normalizedDirectionY, normalizedDirectionZ);
        glVertex3d(v1X, v1Y, v1Z);
        glVertex3d(v2X, v2Y, v2Z);
        glVertex3d(v3X, v3Y, v3Z);
        glVertex3d(v4X, v4Y, v4Z);

        // Mặt sau
        glNormal3d(-normalizedDirectionX, -normalizedDirectionY, -normalizedDirectionZ);
        glVertex3d(v5X, v5Y, v5Z);
        glVertex3d(v6X, v6Y, v6Z);
        glVertex3d(v7X, v7Y, v7Z);
        glVertex3d(v8X, v8Y, v8Z);

        // Mặt trên
        glNormal3d(bitangentX, bitangentY, bitangentZ);
        glVertex3d(v4X, v4Y, v4Z);
        glVertex3d(v3X, v3Y, v3Z);
        glVertex3d(v7X, v7Y, v7Z);
        glVertex3d(v8X, v8Y, v8Z);

        // Mặt dưới
        glNormal3d(-bitangentX, -bitangentY, -bitangentZ);
        glVertex3d(v1X, v1Y, v1Z);
        glVertex3d(v2X, v2Y, v2Z);
        glVertex3d(v6X, v6Y, v6Z);
        glVertex3d(v5X, v5Y, v5Z);

        // Mặt phải
        glNormal3d(tangentX, tangentY, tangentZ);
        glVertex3d(v2X, v2Y, v2Z);
        glVertex3d(v3X, v3Y, v3Z);
        glVertex3d(v7X, v7Y, v7Z);
        glVertex3d(v6X, v6Y, v6Z);

        // Mặt trái
        glNormal3d(-tangentX, -tangentY, -tangentZ);
        glVertex3d(v1X, v1Y, v1Z);
        glVertex3d(v4X, v4Y, v4Z);
        glVertex3d(v8X, v8Y, v8Z);
        glVertex3d(v5X, v5Y, v5Z);
    glEnd();
    }

void drawCylinderOutline(float radius, float height, Point center, Vector normal, Color color)
{

    // Chuẩn hóa vector pháp tuyến
    GLdouble normalX = normal.arr[0];
    GLdouble normalY = normal.arr[1];
    GLdouble normalZ = normal.arr[2];

    GLdouble length = sqrt(normalX * normalX + normalY * normalY + normalZ * normalZ);
    GLdouble normalizedNormalX = normalX / length;
    GLdouble normalizedNormalY = normalY / length;
    GLdouble normalizedNormalZ = normalZ / length;

    // Tính toán vector tiếp tuyến và bitangent
    GLdouble tangentX, tangentY, tangentZ;
    if (normalizedNormalZ != 1.0f && normalizedNormalZ != -1.0f)
    {
        tangentX = normalizedNormalY;
        tangentY = -normalizedNormalX;
        tangentZ = 0.0f;
    } else
    {
        tangentX = 1.0f;
        tangentY = 0.0f;
        tangentZ = 0.0f;
    }

    length = sqrt(tangentX * tangentX + tangentY * tangentY + tangentZ * tangentZ);
    tangentX /= length;
    tangentY /= length;
    tangentZ /= length;

    GLdouble bitangentX = normalizedNormalY * tangentZ - normalizedNormalZ * tangentY;
    GLdouble bitangentY = normalizedNormalZ * tangentX - normalizedNormalX * tangentZ;
    GLdouble bitangentZ = normalizedNormalX * tangentY - normalizedNormalY * tangentX;

    float angleIncrement = 2.0f * M_PI / NUM_SEGMENTS;

    // Lấy tọa độ tâm
    GLdouble centerX = center.arr[0];
    GLdouble centerY = center.arr[1];
    GLdouble centerZ = center.arr[2];

    setColor(color); // Màu đen cho viền
    glLineWidth(LINE_WIDTH); // Độ dày của đường viền

    // Vẽ các đường tròn ở đáy và đỉnh
    glBegin(GL_LINE_LOOP); // Sử dụng LINE_LOOP để vẽ các vòng tròn kín
        for (int i = 0; i < NUM_SEGMENTS; ++i)
        {
            float angle = i * angleIncrement;
            float x = radius * cos(angle);
            float y = radius * sin(angle);

            // Tính toán vị trí đỉnh trên mặt phẳng hình tròn
            GLdouble pointX = centerX + x * tangentX + y * bitangentX;
            GLdouble pointY = centerY + x * tangentY + y * bitangentY;
            GLdouble pointZ = centerZ + x * tangentZ + y * bitangentZ;

            // Tính toán vị trí đỉnh trên mặt phẳng hình tròn (đỉnh dưới)
            GLdouble bottomPointX = pointX - normalizedNormalX * height / 2.0f;
            GLdouble bottomPointY = pointY - normalizedNormalY * height / 2.0f;
            GLdouble bottomPointZ = pointZ - normalizedNormalZ * height / 2.0f;

            glVertex3d(bottomPointX, bottomPointY, bottomPointZ);
            }
            glEnd();

            glBegin(GL_LINE_LOOP);
            for (int i = 0; i < NUM_SEGMENTS; ++i) {
            float angle = i * angleIncrement;
            float x = radius * cos(angle);
            float y = radius * sin(angle);

            // Tính toán vị trí đỉnh trên mặt phẳng hình tròn
            GLdouble pointX = centerX + x * tangentX + y * bitangentX;
            GLdouble pointY = centerY + x * tangentY + y * bitangentY;
            GLdouble pointZ = centerZ + x * tangentZ + y * bitangentZ;

            // Tính toán vị trí đỉnh trên mặt phẳng hình tròn (đỉnh trên)
            GLdouble topPointX = pointX + normalizedNormalX * height / 2.0f;
            GLdouble topPointY = pointY + normalizedNormalY * height / 2.0f;
            GLdouble topPointZ = pointZ + normalizedNormalZ * height / 2.0f;

            glVertex3d(topPointX, topPointY, topPointZ);
        }
    glEnd();
}

void drawCylinderWithCaps(float radius, float height, float thickness, Point center, Vector normal, Color color)
{
    setColor(color);
    // Chuẩn hóa vector pháp tuyến
    GLdouble normalX = normal.arr[0];
    GLdouble normalY = normal.arr[1];
    GLdouble normalZ = normal.arr[2];
    GLdouble length = sqrt(normalX * normalX + normalY * normalY + normalZ * normalZ);
    GLdouble normalizedNormalX = normalX / length;
    GLdouble normalizedNormalY = normalY / length;
    GLdouble normalizedNormalZ = normalZ / length;

    // Tính toán vector tiếp tuyến và bitangent
    GLdouble tangentX, tangentY, tangentZ;
    if (normalizedNormalZ != 1.0f && normalizedNormalZ != -1.0f)
    {
        tangentX = normalizedNormalY;
        tangentY = -normalizedNormalX;
        tangentZ = 0.0f;
    } else
    {
        tangentX = 1.0f;
        tangentY = 0.0f;
        tangentZ = 0.0f;
    }

    length = sqrt(tangentX * tangentX + tangentY * tangentY + tangentZ * tangentZ);
    tangentX /= length;
    tangentY /= length;
    tangentZ /= length;

    GLdouble bitangentX = normalizedNormalY * tangentZ - normalizedNormalZ * tangentY;
    GLdouble bitangentY = normalizedNormalZ * tangentX - normalizedNormalX * tangentZ;
    GLdouble bitangentZ = normalizedNormalX * tangentY - normalizedNormalY * tangentX;

    float angleIncrement = 2.0f * M_PI / NUM_SEGMENTS;

    // Lấy các giá trị tâm từ struct Point
    GLdouble centerX = center.arr[0];
    GLdouble centerY = center.arr[1];
    GLdouble centerZ = center.arr[2];

    // Vẽ thân hình trụ
    glBegin(GL_QUAD_STRIP);
        for (int i = 0; i <= NUM_SEGMENTS; ++i)
        {
            float angle = i * angleIncrement;
            float x = radius * cos(angle);
            float y = radius * sin(angle);

            // Tính toán vị trí đỉnh trên mặt phẳng hình tròn
            GLdouble pointX = centerX + x * tangentX + y * bitangentX;
            GLdouble pointY = centerY + x * tangentY + y * bitangentY;
            GLdouble pointZ = centerZ + x * tangentZ + y * bitangentZ;

            // Tính toán vị trí đỉnh trên mặt phẳng hình tròn (đỉnh trên)
            GLdouble topPointX = pointX + normalizedNormalX * height / 2.0f;
            GLdouble topPointY = pointY + normalizedNormalY * height / 2.0f;
            GLdouble topPointZ = pointZ + normalizedNormalZ * height / 2.0f;

            // Tính toán vị trí đỉnh trên mặt phẳng hình tròn (đỉnh dưới)
            GLdouble bottomPointX = pointX - normalizedNormalX * height / 2.0f;
            GLdouble bottomPointY = pointY - normalizedNormalY * height / 2.0f;
            GLdouble bottomPointZ = pointZ - normalizedNormalZ * height / 2.0f;

            glVertex3d(bottomPointX, bottomPointY, bottomPointZ);
            glVertex3d(topPointX, topPointY, topPointZ);
        }
    glEnd();

    // Vẽ nắp trên hình trụ
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= NUM_SEGMENTS; ++i)
        {
            float angle = i * angleIncrement;
            float x = radius * cos(angle);
            float y = radius * sin(angle);

            // Tính toán vị trí đỉnh trên mặt phẳng hình tròn
            GLdouble pointX = centerX + x * tangentX + y * bitangentX;
            GLdouble pointY = centerY + x * tangentY + y * bitangentY;
            GLdouble pointZ = centerZ + x * tangentZ + y * bitangentZ;

            // Tính toán vị trí đỉnh trên mặt phẳng hình tròn (đỉnh trên)
            GLdouble topPointX = pointX + normalizedNormalX * height / 2.0f;
            GLdouble topPointY = pointY + normalizedNormalY * height / 2.0f;
            GLdouble topPointZ = pointZ + normalizedNormalZ * height / 2.0f;

            // Tính toán vị trí đỉnh bên trong (để tạo độ dày)
            float innerX = (radius - thickness) * cos(angle);
            float innerY = (radius - thickness) * sin(angle);

            GLdouble innerPointX = centerX + innerX * tangentX + innerY * bitangentX;
            GLdouble innerPointY = centerY + innerX * tangentY + innerY * bitangentY;
            GLdouble innerPointZ = centerZ + innerX * tangentZ + innerY * bitangentZ;

            // Tính toán vị trí đỉnh bên trong (để tạo độ dày) trên nắp
            GLdouble innerTopPointX = innerPointX + normalizedNormalX * height / 2.0f;
            GLdouble innerTopPointY = innerPointY + normalizedNormalY * height / 2.0f;
            GLdouble innerTopPointZ = innerPointZ + normalizedNormalZ * height / 2.0f;

            glVertex3d(topPointX, topPointY, topPointZ);
            glVertex3d(innerTopPointX, innerTopPointY, innerTopPointZ);
        }
    glEnd();

    // Vẽ nắp dưới hình trụ
    glBegin(GL_QUAD_STRIP);
        for (int i = 0; i <= NUM_SEGMENTS; ++i)
        {
            float angle = i * angleIncrement;
            float x = radius * cos(angle);
            float y = radius * sin(angle);

            // Tính toán vị trí đỉnh trên mặt phẳng hình tròn
            GLdouble pointX = centerX + x * tangentX + y * bitangentX;
            GLdouble pointY = centerY + x * tangentY + y * bitangentY;
            GLdouble pointZ = centerZ + x * tangentZ + y * bitangentZ;

            // Tính toán vị trí đỉnh trên mặt phẳng hình tròn (đỉnh trên)
            GLdouble bottomPointX = pointX - normalizedNormalX * height / 2.0f;
            GLdouble bottomPointY = pointY - normalizedNormalY * height / 2.0f;
            GLdouble bottomPointZ = pointZ - normalizedNormalZ * height / 2.0f;

            // Tính toán vị trí đỉnh bên trong (để tạo độ dày)
            float innerX = (radius - thickness) * cos(angle);
            float innerY = (radius - thickness) * sin(angle);

            GLdouble innerPointX = centerX + innerX * tangentX + innerY * bitangentX;
            GLdouble innerPointY = centerY + innerX * tangentY + innerY * bitangentY;
            GLdouble innerPointZ = centerZ + innerX * tangentZ + innerY * bitangentZ;

            // Tính toán vị trí đỉnh bên trong (để tạo độ dày) trên nắp
            GLdouble innerBottomPointX = innerPointX - normalizedNormalX * height / 2.0f;
            GLdouble innerBottomPointY = innerPointY - normalizedNormalY * height / 2.0f;
            GLdouble innerBottomPointZ = innerPointZ - normalizedNormalZ * height / 2.0f;

            glVertex3d(bottomPointX, bottomPointY, bottomPointZ);
            glVertex3d(innerBottomPointX, innerBottomPointY, innerBottomPointZ);
        }
    glEnd();
}

void setColor(Color color)
{
    switch (color)
	{
        case GOLD1:
            glColor3f(255.0/255, 215.0/255, 0);
            break;
        case GOLD2:
            glColor3f(238.0/255, 201.0/255, 0);
            break;
        case GOLD3:
            glColor3f(205.0/255, 173.0/255, 0);
            break;
		case DARK_GRAY:
            glColor3f(70.0/255.0, 70.0/255.0, 70.0/255.0);
            break;
        case GRAY:
            glColor3f(90.0/255.0, 90.0/255.0, 90.0/255.0);
            break;
        case LIGHT_GRAY:
            glColor3f(190.0/255.0, 190.0/255.0, 190.0/255.0);
            break;
        case SILVER:
            glColor3f(160.0/255.0, 160.0/255.0, 160.0/255.0);
            break;
        case DIM_BLACK:
            glColor3f(30.0/255.0, 30.0/255.0, 30.0/255.0);
            break;
        case ALUMINUM:
            glColor3f(200.0/255.0, 200.0/255.0, 200.0/255.0);
            break;
        case OFF_WHILE:
            glColor3f(220.0/255.0, 220.0/255.0, 220.0/255.0);
            break;
        case ORANGE:
            glColor3f(255.0/255.0, 165.0/255.0, 0);
            break;
        case DARK_BLUE:
            glColor3f(0,0, 128.0/255);
            break;
        case LIGHT_BLUE:
            glColor3f(173.0f/255, 216.0f/255, 230.0/255);
            break;
        case DARK_GREEN:
            glColor3f(0, 128/255.0, 0);
            break;
        case PURPLE:
            glColor3f(128.0/255, 0, 128.0/255);
            break;
        case LIGHT_GREEN:
            glColor3f(143/255.0, 237/255.0, 143/255.0);
            break;
        case PINK:
            glColor3f(255/255.0, 191/255.0, 204/255.0);
            break;
    	case RED: //255 0 0
	    	glColor3f(1.0f, 0.0f, 0.0f);
	    	break;
	  	case GREEN:
	    	glColor3f(0.0f, 1.0f, 0.0f);
	    	break;
	  	case BLUE:
		    glColor3f(0.0f, 0.0f, 1.0f);
		    break;
	  	case YELLOW:
		    glColor3f(1.0f, 1.0f, 0.0f);
		    break;
	  	case WHITE:
		    glColor3f(1.0f, 1.0f, 1.0f);
		    break;
		case BLACK:
		    glColor3f(0.0f, 0.0f, 0.0f);
		    break;
        case GRAY_MATERIAL:
            glColor3f(0.5, 0.5, 0.5);
            break;
        case GRAY_LIGHT:
            glColor3f(85.0f/255.0f, 85.0f/255.0f, 75.0f/255.0f);
            break;
	  	default:
		    glColor3f(1.0f, 1.0f, 1.0f);
		    break;
    }
}
