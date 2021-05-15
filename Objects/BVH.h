#ifndef BVH_H
#define BVH_H

#include "Object.h"
#include "../Utilities/Scene.h"
#include <algorithm>

class Scene;
class Record;

/*******************************************************************
 * The BVH acceleration Scheme
 * Each node contains the information of it's box
 * and then the left and right children contained in that box
 * 
 *******************************************************************/
class BVH : public Object {
    public:
        shared_ptr<Object> left;
        shared_ptr<Object> right;
        AABB box;
    
    public:
        BVH();

        BVH(Scene& wonderland);

        BVH( vector<shared_ptr<Object>>& objectList, size_t start, size_t end);

        virtual bool intersect(const Ray& ra, double& t, Record& recentHits) override;
        virtual bool shadowIntersect(const Ray& ra, double& t) const override;

        virtual bool getBoundingBox(AABB& output_box) const override;

    
};

inline int random_int(int min, int max) {
    // Returns a random integer in [min,max].
    int number = rand() % max + min;
    return number;
}

inline bool boxCompare(const shared_ptr<Object> a, const shared_ptr<Object> b, int axis) {
    AABB boxA;
    AABB boxB;

    if (!a->getBoundingBox(boxA) || !b->getBoundingBox(boxB))
        std::cerr << "No bounding box in bvh_node constructor.\n";

    if(axis == 0){
        return boxA.p0.xPoint < boxB.p1.xPoint;
    }
    else if(axis == 1){
        return boxA.p0.yPoint < boxB.p1.yPoint;
    }
    else{
        return boxA.p0.zPoint < boxB.p1.zPoint;
    }
}


inline bool boxXCompare (const shared_ptr<Object> a, const shared_ptr<Object> b) {
    return boxCompare(a, b, 0);
}

inline bool boxYCompare (const shared_ptr<Object> a, const shared_ptr<Object> b) {
    return boxCompare(a, b, 1);
}

inline bool boxZCompare (const shared_ptr<Object> a, const shared_ptr<Object> b) {
    return boxCompare(a, b, 2);
}

#endif