
#include "FeatureManager.h"

#include "LogoOverlayFeature.h"
#include "DisplaySpinFeature.h"
#include "LogDisplayFeature.h"
#include "core/Logger.h"


void FeatureManager::update() {
    for (auto feature : features) {
        if (feature->enabled)
            feature->update();
    }
}
void FeatureManager::render(bool forceRedraw) {

    for (auto feature : features) {
        if (feature->enabled && (feature->needsRedraw || forceRedraw))
            feature->render();
    } 
}

void FeatureManager::setEnabled(const char* featureName, bool enabled) {
    features[featureIds[featureName]]->enabled = enabled;
    features[featureIds[featureName]]->needsRedraw = true;
}
bool FeatureManager::isEnabled(const char* featureName) {
    return features[featureIds[featureName]]->enabled;
}
void FeatureManager::addFeature(Feature* feature) {
    features.push_back(feature);
        Logger::d(feature->getName());
    featureIds[feature->getName()] = std::size(features)-1;
        Logger::d("Succes");
}
void FeatureManager::init() {
        Logger::d("Initialising features...");
    LogoOverlayFeature* logoOverlayFeature = new LogoOverlayFeature();
    DisplaySpinFeature* displaySpinFeature = new DisplaySpinFeature();
    LogDisplayFeature* logDisplayFeature = new LogDisplayFeature();
        Logger::d("Adding features...");
    addFeature(logoOverlayFeature);      
    addFeature(displaySpinFeature);      
    addFeature(logDisplayFeature);      

}