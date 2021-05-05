#pragma once
#define angleX 0
#define angleY -30
#define angleZ 0

#include "config.h"
#include "objloader.h"

/* Global variables */
static char title[] = "Lab07_Midterm_ObjParser";
static float tx = 0, ty = 0, tz = 0;
static float thetaX = angleX, thetaY = angleY, thetaZ = angleZ;
static float range = 15;
static float clickX = 0, clickY = 0, clickZ = 0;
static float radius = 0.2f;
static bool Click = false;
static Config config;
//static ObjLoader lamp;
//static ObjLoader teapot;