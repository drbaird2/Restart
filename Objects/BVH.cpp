#include "BVH.h"

#include <algorithm>

BVH::BVH(vector<shared_ptr<Object>>& objectList, size_t start, size_t end)
{
//    std::cout << "new node"<< endl;
    auto objects = objectList;
    
    int axis = random_int(0,3);
    auto comparator = (axis == 0) ? boxXCompare:(axis == 1) ? boxYCompare : boxZCompare;

    size_t objectSpan = end - start;

    if (objectSpan == 1) {
        left = right = objects[start];
//        std::cout << "Leaf - set equal children: " << left << "\n";
    } else if (objectSpan == 2) {
        if (comparator(objects[start], objects[start+1])) {
            left = objects[start];
            right = objects[start+1];
//           std::cout << "Leaf: " << left <<" Leaf: "<< right << "\n";
        } else {
            left = objects[start+1];
            right = objects[start];
//            std::cout << "Leaf: " << left <<" Leaf: "<< right << "\n";
        }
    } else {
        /* for(int i = start; i<= end;i++){
            std::cout << "object address: " << objects[i] << "\n";
        } */
//        std::cout << objects[start]<<endl;
//        std::cout << objects[end-1]<<endl;
        sort(objects.begin() + start, objects.begin() + end); //, comparator
/*         std::cout << "After Sort\n";
        for(int i = start; i<= end;i++){
            std::cout << "object address: " << objects[i] << "\n";
        } */

        auto mid = start + objectSpan/2;
//        std::cout << "spliting" <<  "\n";
        left = make_shared<BVH>(objects, start, mid);
        right = make_shared<BVH>(objects, mid, end);

    }

    AABB boxLeft, boxRight;

    if (  !left->getBoundingBox(boxLeft) || !right->getBoundingBox(boxRight)){
        std::cerr << "No bounding box in bvh_node constructor.\n";
    }

//    std::cout << "left is address: " << typeid(left).name() << "\n";
//    std::cout << "right is address: " << typeid(right).name() << "\n";
    box = box.surroundingBox(boxLeft, boxRight);
//    std::cout<<"I am box: " << &box << " With left " << &boxLeft << " and right " << &boxRight << endl;
}   

BVH::BVH()
{}

BVH::BVH(Scene& wonderland):
    BVH(wonderland.objects, 0, wonderland.objects.size())
{}



bool BVH::intersect(const Ray& ra, double& t, Record& recentHits){
    if(!box.intersect(ra,t,recentHits)){
        return false;
    }
    bool hitLeft = left->intersect(ra,t,recentHits);
//    int leftHit = recentHits.t;
    bool hitRight = right->intersect(ra, hitLeft ? recentHits.t : t, recentHits);
    /* int rightHit = recentHits.t;
    if(!hitRight && hitLeft){
        mat = left->getMaterial();
    }   
    if(hitRight && !hitLeft){
        mat = right->getMaterial();
    }
    if(hitLeft && hitRight){
        mat = (leftHit < rightHit) ? left->getMaterial() : right->getMaterial();
    } */
    /* if(hitLeft && !hitRight){
        mat = left->getMaterial();
    }else if(hitRight && !hitLeft){
        mat = right->getMaterial();
    }else if(hitRight && hitLeft){
        mat = left->getMaterial();
    } */

    return hitLeft || hitRight;
}

bool BVH::shadowIntersect(const Ray& ra, double& tmin)const{
    if(!box.shadowIntersect(ra,tmin)){
        return false;
    }
    bool hitLeft = left->shadowIntersect(ra,tmin);
    bool hitRight = right->shadowIntersect(ra, tmin);
    if(hitRight){
        return hitRight;
    }else if(hitLeft){
        return hitLeft;
    }else{
        return false;
    }
}



bool BVH::getBoundingBox(AABB& outputBox) const{
//    std::cout << "bound a BVH" << this << "\n";
    outputBox = box;
    return true;
}

