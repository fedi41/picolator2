#pragma once

class Element {

    public:
        virtual void render() = 0;
        virtual void update() = 0;
        void renderIfDirty() {
            if (dirty) {
                render();
            }
            dirty = false;
        }
        void setDirty(bool isDirty = true) {
            dirty = isDirty;
        } 
        bool isDirty() {
            return dirty;
        }

    private:
        bool dirty = true;
        bool initialized = false;
};