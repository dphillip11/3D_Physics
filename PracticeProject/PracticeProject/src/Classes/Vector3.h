#pragma once

struct Vector3 {
    float x;
    float y;
    float z;

    Vector3(float a, float b, float c) {
        x = a; y = b; z = c;
    }

    void operator+=(Vector3 a) {
        x += a.x; y += a.y; z += a.z;
    }

    Vector3 operator*(float t) {
        return Vector3{ x * t, y * t, z * t };
    }

};

