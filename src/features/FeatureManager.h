#pragma once

#include <vector>
#include <map>
#include "Feature.h"


class FeatureManager 
{
public:
    static inline std::vector<Feature*> features;
    static inline std::map<const char*, size_t> featureIds;

    static void init();

    static void update();
    static void render(bool forceRedraw=false);

    static void setEnabled(const char* featureName, bool enabled);
    static bool isEnabled(const char* featureName);

    static void addFeature(Feature* feature);
};