#include "BVH.h"

#include <algorithm>

BVH::BVH(const vector<shared_ptr<Object>>& objectList, size_t start, size_t end)
{
    auto objects = objectList;
    
    int axis = random_int(0,2);
    auto comparator = (axis == 0) ? boxXCompare:(axis == 1) ? boxYCompare : boxZCompare;

    size_t objectSpan = end - start;

    if (objectSpan == 1) {
        left = right = objects[start];
    } else if (objectSpan == 2) {
        if (comparator(objects[start], objects[start+1])) {
            left = objects[start];
            right = objects[start+1];
        } else {
            left = objects[start+1];
            right = objects[start];
        }
    } else {
        sort(objects.begin() + start, objects.begin() + end, comparator);

        auto mid = start + objectSpan/2;
        left = make_shared<BVH>(objects, start, mid);
        right = make_shared<BVH>(objects, mid, end);
    }

    AABB boxLeft, boxRight;

    boxLeft = left->getBoundingBox();
    boxRight = right->getBoundingBox();  

    box = box.surroundingBox(boxLeft, boxRight);
}   

BVH::BVH()
{}

BVH::BVH(const Scene& wonderland):
    BVH(wonderland.objects, 0, wonderland.objects.size())
{}



bool BVH::intersect(const Ray& ra, double& t, Record& recentHits){
    if(!box.intersect(ra,t,recentHits)){
        return false;
    }
    bool hitLeft = left->intersect(ra,t,recentHits);
    int leftHit = recentHits.t;
    bool hitRight = right->intersect(ra, hitLeft ? recentHits.t : t, recentHits);
    int rightHit = recentHits.t;
    if(!hitRight && hitLeft){
        mat = left->getMaterial();
    }   
    if(hitRight && !hitLeft){
        mat = right->getMaterial();
    }
    if(hitLeft && hitRight){
        mat = (leftHit < rightHit) && (leftHit > 0) ? left->getMaterial() : right->getMaterial();
    }
    

    return hitLeft || hitRight;
}


AABB BVH::getBoundingBox() const{
    return box;
}

