#pragma once

#include <vector>
#include "Feature.h"


class FeatureManager 
{
public:
    static std::vector<Feature*> features;

    static void update();
    static void render();

    static void setEnabled(char* featureName, bool enabled);
    static bool isEnabled(char* featureName);
}