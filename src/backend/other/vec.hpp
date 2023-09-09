#ifndef __VEC_H__
#define __VEC_H__

#include <cstdio>
#include <math.h>
#include <cstdlib>
#include "itoa.hpp"
#include "hacks.hpp"


struct ivec2 {

    pointable

    ivec2(int x, int y) {
        this->x = x;
        this->y = y;
    };

    int x;
    int y;

    ivec2 operator+(ivec2 other) {
        ivec2 vec = ivec2(0, 0);
        vec.x = this->x + other.x;
        vec.y = this->y + other.y;
        return vec;
    };

    ivec2 operator-(ivec2 other) {
        ivec2 vec = ivec2(0, 0);
        vec.x = this->x - other.x;
        vec.y = this->y - other.y;
        return vec;
    };

    ivec2 operator*(ivec2 other) {
        ivec2 vec = ivec2(0, 0);
        vec.x = this->x * other.x;
        vec.y = this->y * other.y;
        return vec;
    };

    ivec2 operator/(ivec2 other) {
        ivec2 vec = ivec2(0, 0);
        vec.x = this->x / other.x;
        vec.y = this->y / other.y;
        return vec;
    };

    ivec2 operator*(double other) {
        ivec2 vec = ivec2(0, 0);
        vec.x = this->x * other;
        vec.y = this->y * other;
        return vec;
    };

    ivec2 operator/(double other) {
        ivec2 vec = ivec2(0, 0);
        vec.x = this->x / other;
        vec.y = this->y / other;
        return vec;
    };

    double length() {
        return sqrt(pow(this->x, 2)+pow(this->y, 2));
    };

    ivec2 resize_to_length(double new_length) {
        double length = this->length();
        double k = new_length / length;
        return ivec2(this->x*k, this->y*k);
    };
    char *to_str() {
        char xstr[32];
        char ystr[32];
        itoa(this->x, xstr, 32, 10);
        itoa(this->y, ystr, 32, 10);
        char *rval = (char *)malloc(4+strlen(xstr)+strlen(ystr));
        rval[0] = '(';
        rval[strlen(xstr)+1] = ',';
        rval[strlen(xstr)+2] = ' ';
        rval[3+strlen(xstr)+strlen(ystr)] = ')';
        memcpy(rval+1, xstr, strlen(xstr));
        memcpy(rval+strlen(xstr)+3, ystr, strlen(ystr));
        return rval;
    };
};

struct ivec3 {

    pointable

    ivec3(int x, int y, int z) {
        this->x = x;
        this->y = y;
        this->z = z;
    };

    int x;
    int y;
    int z;

    ivec3 operator+(ivec3 other) {
        ivec3 vec = ivec3(0, 0, 0);
        vec.x = this->x + other.x;
        vec.y = this->y + other.y;
        vec.z = this->z + other.z;
        return vec;
    };

    ivec3 operator-(ivec3 other) {
        ivec3 vec = ivec3(0, 0, 0);
        vec.x = this->x - other.x;
        vec.y = this->y - other.y;
        return vec;
    };

    ivec3 operator*(ivec3 other) {
        ivec3 vec = ivec3(0, 0, 0);
        vec.x = this->x * other.x;
        vec.y = this->y * other.y;
        vec.z = this->z * other.z;
        return vec;
    };

    ivec3 operator/(ivec3 other) {
        ivec3 vec = ivec3(0, 0, 0);
        vec.x = this->x / other.x;
        vec.y = this->y / other.y;
        vec.z = this->z / other.z;
        return vec;
    };

    ivec3 operator*(double other) {
        ivec3 vec = ivec3(0, 0, 0);
        vec.x = this->x * other;
        vec.y = this->y * other;
        vec.z = this->z * other;
        return vec;
    };

    ivec3 operator/(double other) {
        ivec3 vec = ivec3(0, 0, 0);
        vec.x = this->x / other;
        vec.y = this->y / other;
        vec.z = this->z / other;
        return vec;
    };

    double length() {
        return sqrt(pow(this->x, 2)+pow(this->y, 2)+pow(this->z, 2));
    };

    ivec3 resize_to_length(double new_length) {
        double length = this->length();
        double k = new_length / length;
        return ivec3(this->x*k, this->y*k, this->z*k);
    };
    char *to_str() {
        char xstr[32];
        char ystr[32];
        char zstr[32];
        itoa(this->x, xstr, 32, 10);
        itoa(this->y, ystr, 32, 10);
        itoa(this->z, ystr, 32, 10);
        char *rval = (char *)malloc(4+strlen(xstr)+strlen(ystr)+strlen(zstr));
        rval[0] = '(';
        rval[strlen(xstr)+1] = ',';
        rval[strlen(xstr)+2] = ' ';
        rval[3+strlen(xstr)+strlen(ystr)] = ',';
        rval[4+strlen(xstr)+strlen(ystr)] = ' ';
        rval[4+strlen(xstr)+strlen(ystr)+strlen(zstr)] = ')';
        memcpy(rval+1, xstr, strlen(xstr));
        memcpy(rval+strlen(xstr)+3, ystr, strlen(ystr));
        memcpy(rval+strlen(xstr)+strlen(ystr)+4, zstr, strlen(zstr));
        return rval;
    };
};

struct fvec2 {

    pointable

    fvec2(double x, double y) {
        this->x = x;
        this->y = y;
    };

    double x;
    double y;

    fvec2 operator+(fvec2 other) {
        fvec2 vec = fvec2(0, 0);
        vec.x = this->x + other.x;
        vec.y = this->y + other.y;
        return vec;
    };

    fvec2 operator-(fvec2 other) {
        fvec2 vec = fvec2(0, 0);
        vec.x = this->x - other.x;
        vec.y = this->y - other.y;
        return vec;
    };

    fvec2 operator*(fvec2 other) {
        fvec2 vec = fvec2(0, 0);
        vec.x = this->x * other.x;
        vec.y = this->y * other.y;
        return vec;
    };

    fvec2 operator/(fvec2 other) {
        fvec2 vec = fvec2(0, 0);
        vec.x = this->x / other.x;
        vec.y = this->y / other.y;
        return vec;
    };

    fvec2 operator*(double other) {
        fvec2 vec = fvec2(0, 0);
        vec.x = this->x * other;
        vec.y = this->y * other;
        return vec;
    };

    fvec2 operator/(double other) {
        fvec2 vec = fvec2(0, 0);
        vec.x = this->x / other;
        vec.y = this->y / other;
        return vec;
    };

    double length() {
        return sqrt(pow(this->x, 2)+pow(this->x, 2));
    };

    fvec2 resize_to_length(double new_length) {
        double length = this->length();
        double k = new_length / length;
        return fvec2(this->x*k, this->y*k);
    };

    char *to_str() {
        char xstr[32];
        char ystr[32];
        ftoa(this->x, xstr, 32);
        ftoa(this->y, ystr, 32);
        char *rval = (char *)malloc(4+strlen(xstr)+strlen(ystr));
        rval[0] = '[';
        rval[strlen(xstr)+1] = ',';
        rval[strlen(xstr)+2] = ' ';
        rval[3+strlen(xstr)+strlen(ystr)] = ']';
        memcpy(rval+1, xstr, strlen(xstr));
        memcpy(rval+strlen(xstr)+3, ystr, strlen(ystr));
        return rval;
    };
};

#endif
