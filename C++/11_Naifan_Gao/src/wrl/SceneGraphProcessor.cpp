//------------------------------------------------------------------------
//  Copyright (C) Gabriel Taubin
//  Time-stamp: <2017-11-12 00:29:12 taubin>
//------------------------------------------------------------------------
//
// SceneGraphProcessor.cpp
//
// Software developed for the Fall 2017 Brown University course
// ENGN 2912B Scientific Computing in C++
// Copyright (c) 2017, Gabriel Taubin
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the Brown University nor the
//       names of its contributors may be used to endorse or promote products
//       derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL GABRIEL TAUBIN BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include <unistd.h>
#include "SceneGraphProcessor.hpp"
#include "SceneGraphTraversal.hpp"
#include "Shape.hpp"
#include "IndexedFaceSet.hpp"
#include "IndexedLineSet.hpp"
#include "Appearance.hpp"
#include "Material.hpp"
#include "IsoSurf.hpp"

using namespace Eigen;

SceneGraphProcessor::SceneGraphProcessor(SceneGraph& wrl):
  _wrl(wrl),
  _nGrid(0),
  _nPoints(0),
  _next((int*)0),
  _first((int*)0) {
}

SceneGraphProcessor::~SceneGraphProcessor() {
  _deletePartition();
}

int SceneGraphProcessor::_createPartition
(Vec3f& min, Vec3f& max, int depth, vector<float>&coord) {
  int nPointsInPartition = 0;
  _deletePartition();
  float dx = max.x-min.x;
  float dy = max.y-min.y;
  float dz = max.z-min.z;
  if(dx>0.0f && dy>0.0f && dz>0.0f) {
    _nPoints = (int)(coord.size()/3);
    if(depth<0) depth = 0;
    _nGrid = 1<<depth;
    int nCells  = _nCells();
    _next    = new int[_nPoints];
    _first   = new int[nCells];
    int iCell,iPoint,ix,iy,iz;
    float x,y,z,nG=(float)_nGrid;
    for(iCell=0;iCell<nCells;iCell++)
      _first[iCell] = -1;
    for(iPoint=0;iPoint<_nPoints;iPoint++) {  
      if((x = coord[3*iPoint  ])<min.x || x>max.x) continue;
      if((y = coord[3*iPoint+1])<min.y || y>max.y) continue;
      if((z = coord[3*iPoint+2])<min.z || z>max.z) continue;
      ix = (int)((nG*(x-min.x))/dx);
      iy = (int)((nG*(y-min.y))/dy);
      iz = (int)((nG*(z-min.z))/dz);
      iCell = ix+_nGrid*(iy+_nGrid*iz);
      _next[iPoint] = _first[iCell];
    _first[iCell] = iPoint;
    nPointsInPartition++;
    }
  }
  return nPointsInPartition;
}

void SceneGraphProcessor::_deletePartition() {
  if(_first!=(int*)0) delete [] _first;
  if(_next !=(int*)0) delete [] _next;
  _nGrid   = 0;
  _nPoints = 0;
  _next    = (int*)0;
  _first   = (int*)0;
}

void SceneGraphProcessor::normalClear() {
  _applyToIndexedFaceSet(_normalClear);
}

void SceneGraphProcessor::normalInvert() {
  _applyToIndexedFaceSet(_normalInvert);
}

void SceneGraphProcessor::computeNormalPerFace() {
  _applyToIndexedFaceSet(_computeNormalPerFace);
}

void SceneGraphProcessor::computeNormalPerVertex() {
  _applyToIndexedFaceSet(_computeNormalPerVertex);
}

void SceneGraphProcessor::computeNormalPerCorner() {
  _applyToIndexedFaceSet(_computeNormalPerCorner);
}

void SceneGraphProcessor::_applyToIndexedFaceSet(IndexedFaceSet::Operator o) {
  SceneGraphTraversal traversal(_wrl);
  traversal.start();
  Node* node;
  while((node=traversal.next())!=(Node*)0) {
    if(node->isShape()) {
      Shape* shape = (Shape*)node;
      node = shape->getGeometry();
      if(node!=(Node*)0 && node->isIndexedFaceSet()) {
        IndexedFaceSet& ifs = *((IndexedFaceSet*)node);
        o(ifs);
      }
    }
  }
}

void SceneGraphProcessor::_normalClear(IndexedFaceSet& ifs) {
  vector<float>& normal      = ifs.getNormal();
  vector<int>&   normalIndex = ifs.getNormalIndex();
  ifs.setNormalPerVertex(true);
  normal.clear();
  normalIndex.clear();
}

void SceneGraphProcessor::_normalInvert(IndexedFaceSet& ifs) {
  vector<float>& normal = ifs.getNormal();
  for(int i=0;i<(int)normal.size();i++)
    normal[i] = -normal[i];
}

void SceneGraphProcessor::_computeFaceNormal
(vector<float>& coord, vector<int>& coordIndex,
 int i0, int i1, Vector3d& n, bool normalize) {

  // TODO

  // compute normal vector to face defined by the vertex indices
  // {coordIndex[i0],...,coordIndex[i1-1]}

  // store the result in the 3D vector n

  // normalize to unit length or not, depending on the 'normalize' variable
    int iV,i;
    float x0,x1,x2;
    if(coordIndex[i1]<0) { // end of face marker found
        // face iF
        // this is how you can access all the vertex indices of this face
        vector<Vector3d> list;
        for(i=i0;i<i1;i++) {
            iV = coordIndex[i];
            x0 = coord[3*iV ];
            x1 = coord[3*iV+1];
            x2 = coord[3*iV+2];
            // you need more than one face vertex to compute the face normal ...
            list.push_back(Vector3d(x0, x1, x2));
        }
        // compute n0,n1,n2 as a function of
        // the coordinates of all the vertices of this face
        // push_back() the three values onto the normal array
        if(list.size()==3){
            Vector3d v = list.at(0)-list.at(1);
            Vector3d w= list.at(0) - list.at(2);
            n = v.cross(w);
        }else{
            Vector3d p;
            int i=0;
            while(i<list.size()){
                p.x() += list.at(i).x();
                p.y() += list.at(i).y();
                p.z() += list.at(i).z();
                i++;
            }
            p.x() /= list.size();
            p.y() /= list.size();
            p.z() /= list.size();
            for(int k=0; k<list.size(); k++){
                if(k==list.size()-1){
                    Vector3d v(list.at(k).x()-p.x(), list.at(k).y()-p.y(), list.at(k).z()-p.z());
                    Vector3d w(list.at(0).x()-p.x(), list.at(0).y()-p.y(), list.at(0).z()-p.z());
                    Vector3d temp = v.cross(w);
                    n.x() += temp.x();
                    n.y() += temp.y();
                    n.z() += temp.z();
                }else{
                    Vector3d v(list.at(k).x()-p.x(), list.at(k).y()-p.y(), list.at(k).z()-p.z());
                    Vector3d w(list.at(k+1).x()-p.x(), list.at(k+1).y()-p.y(), list.at(k+1).z()-p.z());
                    Vector3d temp = v.cross(w);
                    n.x() += temp.x();
                    n.y() += temp.y();
                    n.z() += temp.z();
                }
            }
        }
        list.clear();
        if(normalize){
            float normal = sqrt(n.x()*n.x()+n.y()*n.y()+n.z()*n.z());
            n /= normal;
        }
    }
}

void SceneGraphProcessor::_computeNormalPerFace(IndexedFaceSet& ifs) {
  if(ifs.getNormalBinding()==IndexedFaceSet::PB_PER_FACE) return;
    
  // TODO
    vector<float>& coord = ifs.getCoord();
    vector<int>& coordIndex = ifs.getCoordIndex();
    vector<float>& normal = ifs.getNormal();
    vector<int>& normalIndex = ifs.getNormalIndex();
    // clear normal & normalIndex; set normalPerVertex field of ifs to FALSE
    normal.clear();
    normalIndex.clear();
    ifs.setNormalPerVertex(false);
    int iF,iV,i,i0,i1;
    float n0,n1,n2,x0,x1,x2;
    for(iF=i0=i1=0;i1<coordIndex.size();i1++) {
        Vector3d N(0,0,0);
        if(coordIndex[i1]<0){
        _computeFaceNormal(coord, coordIndex, i0, i1, N, true);
        normal.push_back(N.x());
        normal.push_back(N.y());
        normal.push_back(N.z());
        i0 = i1+1; iF++;
        }
    }
}

void SceneGraphProcessor::_computeNormalPerVertex(IndexedFaceSet& ifs) {
  if(ifs.getNormalBinding()==IndexedFaceSet::PB_PER_VERTEX) return;

  // TODO
    vector<float>& coord = ifs.getCoord();
    vector<int>& coordIndex = ifs.getCoordIndex();
    vector<float>& normal = ifs.getNormal();
    vector<int>& normalIndex = ifs.getNormalIndex();
    int nV = coord.size()/3;
    ifs.getNormal().clear();
    normalIndex.clear(); // will not be used
    ifs.setNormalPerVertex(false);
    // compute face normals without normalization
    int iF,iV,i,i0,i1;
    for(iF=i0=i1=0;i1<coordIndex.size();i1++) {
        Vector3d N(0,0,0);
        if(coordIndex[i1]<0){
        _computeFaceNormal(coord, coordIndex, i0, i1, N, false);
        normal.push_back(N.x());
        normal.push_back(N.y());
        normal.push_back(N.z());
        i0 = i1+1; iF++;
        }
    }
    // save the computed face normal and clear the ifs normals
    vector<float> faceNormal;
    faceNormal.swap(normal);

    // at this point normal.size()==0
    // insert coord.size() zeros onto the normal array
    for(int i=0; i<coord.size(); i++){
        normal.push_back(0.0f);
    }
    // at this point coord.size()==normal.size();
    ifs.setNormalPerVertex(true);
    int iV0, iV2;
    for(iF=i0=i1=0;i1<coordIndex.size();i1++) {
        if(coordIndex[i1]<0) { // end of face marker found
            // face iF
            // retrieve this face normal coordinates from the faceNormal array
            for(i=i0;i<i1;i++) {
                iV = coordIndex[i];
                // add face normal coordinates to this vertex normal accumulator
                normal.at(iV*3) += faceNormal.at(3*iF);
                normal.at(iV*3+1) += faceNormal.at(3*iF+1);
                normal.at(iV*3+2) += faceNormal.at(3*iF+2);
                if(i==i0) iV0 = coordIndex[i1-1];
                else iV0 = coordIndex[i-1]; // [i1-1] if i==0
                if(i==i1-1) iV2 = coordIndex[i0];
                else iV2 = coordIndex[i+1]; // [i0] if i==i0-1
                Vector3d v(coord[iV*3]-coord[iV2*3], coord[iV*3+1]-coord[iV2*3+1], coord[iV*3+2]-coord[iV2*3+2]);
                Vector3d w(coord[iV*3]-coord[iV0*3], coord[iV*3+1]-coord[iV0*3+1], coord[iV*3+2]-coord[iV0*3+2]);
                Vector3d n = v.cross(w);
                normal.at(iV*3) += n.x();
                normal.at(iV*3+1) += n.y();
                normal.at(iV*3+2) += n.z();
            }
            i0 = i1+1; iF++;
        }
    }
    for(iV=0;iV<nV;iV++) {
        // normalize vertex normal to unit length
        float normalize = sqrt(normal.at(iV*3)*normal.at(iV*3)+normal.at(iV*3+1)*normal.at(iV*3+1)+normal.at(iV*3+2)*normal.at(iV*3+2));
        normal.at(iV*3) /= normalize;
        normal.at(iV*3+1) /= normalize;
        normal.at(iV*3+2) /= normalize;
    }

}

void SceneGraphProcessor::_computeNormalPerCorner(IndexedFaceSet& ifs) {
  if(ifs.getNormalBinding()==IndexedFaceSet::PB_PER_CORNER) return;
    vector<float> coord = ifs.getCoord();
    vector<int>& coordIndex = ifs.getCoordIndex();
    vector<float>& normal = ifs.getNormal();
    vector<int>& normalIndex = ifs.getNormalIndex();
  // TODO
    normal.clear();
    normalIndex.clear();
    ifs.setNormalPerVertex(true);
    int iF,iV0,iV1,iV2,i,i0,i1,iN;
    for(iF=i0=i1=0;i1<coordIndex.size();i1++) {
        if(coordIndex[i1]<0) { // end of face marker found
            // face iF
            // this is how you can access all the vertex indices of this face
            
            for(i=i0;i<i1;i++) {
                if(i==i0) iV0 = coordIndex[i1-1];
                else iV0 = coordIndex[i-1]; // [i1-1] if i==0
                iV1 = coordIndex[i ];
                if(i==i1-1) iV2 = coordIndex[i0];
                else iV2 = coordIndex[i+1]; // [i0] if i==i0-1
                // compute unit length corner normal ...
                Vector3d v(coord[iV1*3]-coord[iV2*3], coord[iV1*3+1]-coord[iV2*3+1], coord[iV1*3+2]-coord[iV2*3+2]);
                Vector3d w(coord[iV1*3]-coord[iV0*3], coord[iV1*3+1]-coord[iV0*3+1], coord[iV1*3+2]-coord[iV0*3+2]);
                Vector3d n = w.cross(v);
                float normalize = sqrt(n.x()*n.x()+n.y()*n.y()+n.z()*n.z());
                iN = normal.size()/3; // index to be assigned to this normal vector
                // push_back computed normal coordinates onto normal array
                normal.push_back(n.x()/normalize);
                normal.push_back(n.y()/normalize);
                normal.push_back(n.z()/normalize);
                // push_back iN onto normalIndex array
                normalIndex.push_back(iN);
            }
            // push_back a -1 onto the normalIndex array
            normalIndex.push_back(-1);
            i0 = i1+1; iF++;
        }
    }
}

void SceneGraphProcessor::bboxAdd(int depth, float scale, bool cube) {

  // TODO

  // 1) look for a Shape node named "BOUNDING-BOX" as a child of the
  // SceneGraph root node; if not found create a new one with that
  // name, add an Appearance node to the Shape node, and a Material
  // node to the Appearance node; assign a proper value to the
  // diffuseColor of the Material node; add the Shape node as a child
  // of the SceneGraph
  // 2) look for an IndexedFaceSet node in the geometry fields of the
  // Shape node; if an IndexedFaceSet is found, delete the
  // IndexedFaceSet and set the geometry field to (Node*)0; if the
  // geometry field is equal to (Node*)0, create a new IndexedLineSet;
  // 3) clear the IndexedLineSet
  // 4) update the SceneGraph bounding box
  // 5) create the vertices of the regular grid of side N=2^depth;
  // such grid has (N+1)*(N+1)*(N+1) vertices; store the coordinates
  // in the coord field of the IndexedLineSet
  // 6) create the edges of the regular grid; such grid has
  // 3*(N+1)*(N+1)*N edges
    Shape* node = (Shape*)_wrl.find("BOUNDING-BOX");
    if(node==(Node*)0){
        Shape* shape = new Shape();
        shape->setName("BOUNDING-BOX");
        Appearance* appearance = new Appearance();
        Material* material = new Material();
        Color color(1.0, 0.0, 0.0);
        material->setDiffuseColor(color);
        appearance->setMaterial(material);
        shape->setAppearance(appearance);
        //what value should be set for diffuseColor?
        shape->setGeometry(new IndexedLineSet());
        _wrl.addChild(shape);
        node = shape;
    }
    else if(node->hasGeometryIndexedFaceSet()){
        IndexedFaceSet* faceSet = (IndexedFaceSet*)node->getGeometry();
        delete faceSet;
        node->setGeometry(new IndexedLineSet());
    }else if(node->getGeometry()==(Node*)0){
        node->setGeometry(new IndexedLineSet());
    }
    else if(node->hasGeometryIndexedLineSet()){
        IndexedLineSet* lineSet = (IndexedLineSet*)node->getGeometry();
        lineSet->clear();
    }
    _wrl.updateBBox(cube);
    vector<float> coord;
    _wrl.appendBBoxCoord(coord);
    Vec3f center = _wrl.getBBoxCenter();
    Vec3f size = _wrl.getBBoxSize();
    if(cube){
        float temp=0;
        if(size.x>temp){
            temp = size.x;
        }
        if(size.y>temp) temp = size.y;
        if(size.z>temp) temp = size.z;
        size.x=temp; size.y=temp; size.z=temp;
        _wrl.setBBoxSize(size);
    }
    Vec3f x0(center.x-0.5*scale*size.x, center.y-0.5*scale*size.y, center.z-0.5*scale*size.z);
    Vec3f x1(center.x+0.5*scale*size.x, center.y+0.5*scale*size.y, center.z+0.5*scale*size.z);
    Vec3f newSize(size.x*scale, size.y*scale, size.z*scale);
    _wrl.setBBoxSize(newSize);
    //what is 5) and 6) means?
    IndexedLineSet* indexedLineSet = (IndexedLineSet*)node->getGeometry();
    int temp;
    int i,j,k,iV, N = (int)pow(2, depth);
    for(i=0; i<=N; i++){
        for(j=0; j<=N; j++){
            int count =0;
            for(k=0; k<=N; k++){
                count++;
                iV = k+(N+1)*(j+(N+1)*i);
                int x= iV-(N+1)*(N+1);
                int y = iV-(N+1);
                indexedLineSet->getCoord().push_back(((N-i)*x0.x+i*x1.x)/N);
                indexedLineSet->getCoord().push_back(((N-j)*x0.y+j*x1.y)/N);
                indexedLineSet->getCoord().push_back(((N-k)*x0.z+k*x1.z)/N);
                if(count==2){
                    indexedLineSet->getCoordIndex().push_back(temp);
                    indexedLineSet->getCoordIndex().push_back(iV);
                    indexedLineSet->getCoordIndex().push_back(-1);
                    temp = iV;
                    count=1;
                }else{
                    temp = iV;
                }
                if(y>=0 && j>0){
                    indexedLineSet->getCoordIndex().push_back(y);
                    indexedLineSet->getCoordIndex().push_back(iV);
                    indexedLineSet->getCoordIndex().push_back(-1);
                    
                }
                if(x>=0 && i>0){
                    indexedLineSet->getCoordIndex().push_back(x);
                    indexedLineSet->getCoordIndex().push_back(iV);
                    indexedLineSet->getCoordIndex().push_back(-1);
                }
            }
        }
    }
}

void SceneGraphProcessor::bboxRemove() {

  // TODO

  // 1) look for a child of the SceneGraph named "BOUNDING-BOX"
  // 2) if found, remove from the children array and delete
    Node* node = _wrl.find("BOUNDING-BOX");
    if(node != (Node*)0) _wrl.removeChild(node);
    delete node;
}

void SceneGraphProcessor::edgesAdd() {

  // TODO

  // 1) using a SceneGraphTraversal, look for Shape nodes

  // 2) for each Shape node containing an IndexedFaceSet as geometry

  // 3) look for another Shape node, sibiling of the previous Shape
  // node (i.e. child of the same Group node), named "EDGES"; if note
  // found create a new one, and insert it as a new child of the Group
  // node which is parent of the Shape node; if the "EDGES" Shape node
  // does not contain an IndexedLineSet as geometry, delete the
  // geometry node, and set to (Node*)0; if the geometry node is equal
  // to (Node*)0, create a new IndexedLineSet and save it in the
  // geometry field of the first Shape node

  // 4) make sure that the appearance field of the EDGES Shape node
  // contains an Appearance node, and the material field of the
  // Appearance node contains a Material node; if node create them;
  // set the diffuseColor field of the Material node to an appropriate
  // value

  // 5) clear the IndexedLineSet node

  // 6) copy the coord field from the IndexedFaceSet node to the
  // IndexedLineSet node
  // 7) for each face of the IndexedFaceSet node, determine the
  // corresponding boundary edges and store them in the coordIndex
  // array of the IndexedLineSet
    Node* child;
    SceneGraphTraversal* t = new SceneGraphTraversal(_wrl);
    t->start();
    child=t->next();
    Shape* shape_1=(Shape*)0;
    Shape* shape_2=(Shape*)0;
    while(child != NULL){
        if(child->isShape() && shape_1==(Shape*)0){
            shape_1 = (Shape*)child;
            if(!shape_1->hasGeometryIndexedFaceSet()) shape_1=(Shape*)0;
            else{
                IndexedFaceSet* faceSet = (IndexedFaceSet*)shape_1->getGeometry();
                Group* parent = (Group*)const_cast<Node*>(shape_1->getParent());
                if(parent==(Group*)0) break;
                for(int i=0; i< parent->getChildren().size(); i++){
                    if(parent->getChildren().at(i)->isShape()&& shape_1 !=parent->getChildren().at(i)){
                        if(child->nameEquals("EDGES")){
                            shape_2 = (Shape*)child;
                            IndexedLineSet* lineSet = new IndexedLineSet();
                            if(shape_2->hasGeometryNull()){
                                shape_1->setGeometry(lineSet);
                            }else if(!shape_2->hasGeometryIndexedLineSet()) {
                                delete shape_2->getGeometry();
                                shape_2->setGeometry((Node*)0);
                            }else{
                                lineSet = (IndexedLineSet*)shape_2->getGeometry();
                            }
                            lineSet->clear();
                            
                            //how to determine boundary edges?
                        }
//                        }else{
//                            shape_2 = (Shape*)0;
//                        }
                    }
                }
                if(shape_1!=(Shape*)0 && shape_2==(Shape*)0){
                    shape_2 = new Shape();
                    shape_2->setName("EDGES");
                    Appearance* appearance = new Appearance();
                    Material* material = new Material();
                    Color color(1.0,0.0,0.0);
                    material->setDiffuseColor(color);
                    appearance->setMaterial(material);
                    shape_2->setAppearance(appearance);
                    shape_2->setGeometry(new IndexedLineSet());
                    parent->addChild(shape_2);
                    shape_2->setParent(parent);
                }
                IndexedLineSet* lineSet = (IndexedLineSet*)shape_2->getGeometry();
                lineSet->clear();
                int i=0;
                vector<int> temp;
                for(int i=0; i<faceSet->getCoord().size(); i++){
                    lineSet->getCoord().push_back(faceSet->getCoord().at(i));
                }
                while(i<faceSet->getCoordIndex().size()){
                    if(faceSet->getCoordIndex().at(i)!=-1){
                        temp.push_back(faceSet->getCoordIndex().at(i));
                        i++;
                        continue;
                    }else{
                        for(int j=0; j< temp.size(); j++){
                            if(j==temp.size()-1){
                                lineSet->getCoordIndex().push_back(temp[j]);
                                lineSet->getCoordIndex().push_back(temp[0]);
                                lineSet->getCoordIndex().push_back(-1);
                            }else{
                                lineSet->getCoordIndex().push_back(temp.at(j));
                                lineSet->getCoordIndex().push_back(temp[j+1]);
                                lineSet->getCoordIndex().push_back(-1);
                            }
                        }
                        i++;
                        temp.clear();
                    }
                }
            }
        }
        child = t->next();
        shape_1=(Shape*)0;
        shape_2=(Shape*)0;
    }
}

void SceneGraphProcessor::edgesRemove() {

  // TODO

  // using a SceneGraphTraversal, look for all the shape nodes
  // named "EDGES", remove them from the scene graph and delete them
    Node* child;
    SceneGraphTraversal* t = new SceneGraphTraversal(_wrl);
    t->start();
    child=t->next();
    while(child!=NULL){
//        if(child->isGroup()){
//            Group* group = (Group*)child;
        Shape* edges = (Shape*)_wrl.find("EDGES");
        if(edges!=(Shape*)0){
            Group* parent = (Group*)edges->getParent();
            parent->removeChild(edges);
            delete edges;
            t->start();
        }
        child = t->next();
    }
}

void SceneGraphProcessor::shapeIndexedFaceSetShow() {

  // TODO

  // using a SceneGraphTraversal look for all Shape nodes containing
  // an IndexedFaceSet as geometry, and set the show variable to true
    Node* child;
    SceneGraphTraversal* t = new SceneGraphTraversal(_wrl);
    t->start();
    child=t->next();
    while(child != NULL){
        if(child->isShape()){
            Shape* shape = (Shape*)child;
            if(shape->hasGeometryIndexedFaceSet()){
                IndexedFaceSet* faceSet = (IndexedFaceSet*)shape->getGeometry();
                faceSet->setShow(true);
                shape->setShow(true);
            }
        }
        child = t->next();
    }
}

void SceneGraphProcessor::shapeIndexedFaceSetHide() {

  // TODO

  // using a SceneGraphTraversal look for all Shape nodes containing
  // an IndexedFaceSet as geometry, and set the show variable to false
    Node* child;
    SceneGraphTraversal* t = new SceneGraphTraversal(_wrl);
    t->start();
    child=t->next();
    while(child != NULL){
        if(child->isShape()){
            Shape* shape = (Shape*)child;
            if(shape->hasGeometryIndexedFaceSet()){
                IndexedFaceSet* faceSet = (IndexedFaceSet*)shape->getGeometry();
                faceSet->setShow(false);
                shape->setShow(false);
            }
        }
        child = t->next();
    }
}

void SceneGraphProcessor::shapeIndexedLineSetShow() {

  // TODO

  // using a SceneGraphTraversal look for all Shape nodes containing
  // an IndexedLineSet as geometry, and set the show variable to true
    Node* child;
    SceneGraphTraversal* t = new SceneGraphTraversal(_wrl);
    t->start();
    child=t->next();
    while(child != NULL){
        if(child->isShape()){
            Shape* shape = (Shape*)child;
            if(shape->hasGeometryIndexedLineSet()){
                IndexedLineSet* lineSet = (IndexedLineSet*)shape->getGeometry();
                lineSet->setShow(true);
                shape->setShow(true);
            }
        }
        child = t->next();
    }
}

void SceneGraphProcessor::shapeIndexedLineSetHide() {

  // TODO

  // using a SceneGraphTraversal look for all Shape nodes containing
  // an IndexedLineSet as geometry, and set the show variable to true
    Node* child;
    SceneGraphTraversal* t = new SceneGraphTraversal(_wrl);
    t->start();
    child=t->next();
    while(child != NULL){
        if(child->isShape()){
            Shape* shape = (Shape*)child;
            if(shape->hasGeometryIndexedLineSet()){
                IndexedLineSet* lineSet = (IndexedLineSet*)shape->getGeometry();
                lineSet->setShow(false);
                shape->setShow(false);
            }
        }
        child = t->next();
    }
}

bool SceneGraphProcessor::hasBBox() {
  return _wrl.getChild("BOUNDING-BOX")!=(Node*)0;
}

// a Property is define in Node.h as a function with a single Node&
// argument which returns a boolean value

bool SceneGraphProcessor::_hasShapeProperty(Shape::Property p) {
  bool value = false;

  // TODO 

  // using a SceneGraphTraversal look for Shape nodes; return true if
  // the Property p is true for at least one Shape node, and false
  // otherwise
    Node* child;
    SceneGraphTraversal* t = new SceneGraphTraversal(_wrl);
    t->start();
    child=t->next();
    while(child != NULL){
        if(child->isShape()){
            if(p(*(Shape*)child)){
                value=true;
            }
        }
        child = t->next();
    }
  return value;
}

bool SceneGraphProcessor::_hasIndexedFaceSetProperty(IndexedFaceSet::Property p) {
  bool value = false;

  // TODO 

  // using a SceneGraphTraversal look for Shape nodes containing and
  // IndexedFaceSet nodes as geometry; return true if the Property p
  // is true for at least one of these IndexedFaceSets node, and false
  // otherwise
    Node* child;
    SceneGraphTraversal* t = new SceneGraphTraversal(_wrl);
    t->start();
    child=t->next();
    while(child != NULL){
        if(child->isShape()){
            Shape* shape = (Shape*)child;
            if(shape->hasGeometryIndexedFaceSet())
                if(p(*(IndexedFaceSet*)(shape->getGeometry())))
                    value=true;
        }
        child = t->next();
    }
  return value;
}

bool SceneGraphProcessor::_hasIndexedLineSetProperty(IndexedLineSet::Property p) {
  bool value = false;

  // TODO 

  // using a SceneGraphTraversal look for Shape nodes containing and
  // IndexedFaceSet nodes as geometry; return true if the Property p
  // is true for at least one of these IndexedFaceSets node, and false
  // otherwise
    Node* child;
    SceneGraphTraversal* t = new SceneGraphTraversal(_wrl);
    t->start();
    child=t->next();
    while(child != NULL){
        if(child->isShape()){
            Shape* shape = (Shape*)child;
            if(shape->hasGeometryIndexedLineSet()){
                if(p(*(IndexedLineSet*)(shape->getGeometry()))) value = true;
            }
        }
        child = t->next();
    }
  return value;
}

// this is a Property
bool SceneGraphProcessor::_hasFaces(IndexedFaceSet& ifs) {
  bool value = false;

  // TODO
    if(ifs.getNumberOfFaces()>0) value=true;
  
  return value;
}

// this is a Property
bool SceneGraphProcessor::_hasNormalNone(IndexedFaceSet& ifs) {
  bool value = false;

  // TODO
    if(ifs.getNormalBinding()==IndexedFaceSet::PB_NONE) value = true;
  return value;
}

// this is a Property
bool SceneGraphProcessor::_hasNormalPerFace(IndexedFaceSet& ifs) {
  bool value = false;

  // TODO
    if(ifs.getNormalBinding()==IndexedFaceSet::PB_PER_FACE) value = true;
  return value;
}

// this is a Property
bool SceneGraphProcessor::_hasNormalPerVertex(IndexedFaceSet& ifs) {
  bool value = false;

  // TODO
    if(ifs.getNormalBinding()==IndexedFaceSet::PB_PER_VERTEX) value = true;
  return value;
}

// this is a IndexedFaceSet::Property
bool SceneGraphProcessor::_hasNormalPerCorner(IndexedFaceSet& ifs) {
  bool value = false;
    if(ifs.getNormalBinding()==IndexedFaceSet::PB_PER_CORNER) value = true;
  return value;
}

bool SceneGraphProcessor::hasIndexedFaceSetFaces() {
  return _hasIndexedFaceSetProperty(_hasFaces);
}

bool SceneGraphProcessor::hasIndexedFaceSetNormalNone() {
  return _hasIndexedFaceSetProperty(_hasNormalNone);
}

bool SceneGraphProcessor::hasIndexedFaceSetNormalPerFace() {
  return _hasIndexedFaceSetProperty(_hasNormalPerFace);
}

bool SceneGraphProcessor::hasIndexedFaceSetNormalPerVertex() {
  return _hasIndexedFaceSetProperty(_hasNormalPerVertex);
}

bool SceneGraphProcessor::hasIndexedFaceSetNormalPerCorner() {
  return _hasIndexedFaceSetProperty(_hasNormalPerCorner);
}

// VRML'97
//
// If the color field is not NULL, it shall contain a Color node, and
// the colours are applied to the line(s) as follows:
//
// If colorPerVertex is FALSE:
//
// If the colorIndex field is not empty, then one colour is used for
// each polyline of the IndexedLineSet. There must be at least as many
// indices in the colorIndex field as there are polylines in the
// IndexedLineSet. If the greatest index in the colorIndex field is N,
// then there must be N+1 colours in the Color node. The colorIndex
// field must not contain any negative entries.
//
// If the colorIndex field is empty, then the colours from the Color
// node are applied to each polyline of the IndexedLineSet in
// order. There must be at least as many colours in the Color node as
// there are polylines.
//
// If colorPerVertex is TRUE:
//
// If the colorIndex field is not empty, then colours are applied to
// each vertex of the IndexedLineSet in exactly the same manner that
// the coordIndex field is used to supply coordinates for each vertex
// from the Coordinate node. The colorIndex field must contain at
// least as many indices as the coordIndex field and must contain
// end-of-polyline markers (-1) in exactly the same places as the
// coordIndex field. If the greatest index in the colorIndex field is
// N, then there must be N+1 colours in the Color node.
//
// If the colorIndex field is empty, then the coordIndex field is used
// to choose colours from the Color node. If the greatest index in the
// coordIndex field is N, then there must be N+1 colours in the Color
// node.
//
// If the color field is NULL and there is a Material defined for the
// Appearance affecting this IndexedLineSet, the emissiveColor of the
// Material shall be used to draw the lines.

// this is a Property
 bool SceneGraphProcessor::_hasColorNone(IndexedLineSet& ils) {
   bool value = false;
   
   // TODO 
   if(ils.getColor().empty()) value = true;
   return value;
}

// this is a Property
bool SceneGraphProcessor::_hasColorPerVertex(IndexedLineSet& ils) {
  bool value = false;
  
  // TODO 
    if(ils.getColorPerVertex()) value = true;
  return value;
}

// this is a Property
bool SceneGraphProcessor::_hasColorPerPolyline(IndexedLineSet& ils) {
  bool value = false;
  
  // TODO
    if(ils.getColorPerVertex()==false) value=true;
  
  return value;
}

bool SceneGraphProcessor::hasIndexedLineSetColorNone() {
  return _hasIndexedLineSetProperty(_hasColorNone);
}

bool SceneGraphProcessor::hasIndexedLineSetColorPerVertex() {
  return _hasIndexedLineSetProperty(_hasColorPerVertex);
}

bool SceneGraphProcessor::hasIndexedLineSetColorPerPolyline() {
  return _hasIndexedLineSetProperty(_hasColorPerPolyline);
}

// this is a Property
bool SceneGraphProcessor::_hasEdges(Shape& shape) {
  bool value = false;
  
  // TODO
    Group* group = (Group*)shape.getParent();
    if(group==(Node*)0) return value;
    for(int i=0; i<group->getChildren().size(); i++){
        if(group->getChildren()[i]->nameEquals("EDGES")) value=true;
    }
  
  return value;
}

// this is a Property
bool SceneGraphProcessor::_hasIndexedFaceSetShown(Shape& shape) {
  bool value = false;
  
  // TODO 
    if(shape.hasGeometryIndexedFaceSet()){
        IndexedFaceSet* faceSet = (IndexedFaceSet*)shape.getGeometry();
        if(faceSet->getShow()) value=true;
    }
  return value;
}

// this is a Property
bool SceneGraphProcessor::_hasIndexedFaceSetHidden(Shape& shape) {
    bool value = false;
  
  // TODO 
    if(shape.hasGeometryIndexedFaceSet()){
        IndexedFaceSet* faceSet = (IndexedFaceSet*)shape.getGeometry();
        if(!faceSet->getShow()) value=true;
    }
  return value;
}

// this is a Property
bool SceneGraphProcessor::_hasIndexedLineSetShown(Shape& shape) {
  bool value = false;
  
  // TODO 
    if(shape.hasGeometryIndexedLineSet()){
        IndexedLineSet* lineSet = (IndexedLineSet*)shape.getGeometry();
        if(lineSet->getShow()) value=true;
    }
  return value;
}

// this is a Property
bool SceneGraphProcessor::_hasIndexedLineSetHidden(Shape& shape) {
  bool value = false;
  
  // TODO 
    if(shape.hasGeometryIndexedLineSet()){
        IndexedLineSet* lineSet = (IndexedLineSet*)shape.getGeometry();
        if(!lineSet->getShow()) value=true;
    }
  return value;
}

bool SceneGraphProcessor::hasEdges() {
  return _hasShapeProperty(_hasEdges);
}

bool SceneGraphProcessor::hasIndexedFaceSetShown() {
  return _hasShapeProperty(_hasIndexedFaceSetShown);
}

bool SceneGraphProcessor::hasIndexedFaceSetHidden() {
  return _hasShapeProperty(_hasIndexedFaceSetHidden);
}

bool SceneGraphProcessor::hasIndexedLineSetShown() {
  return _hasShapeProperty(_hasIndexedLineSetShown);
}

bool SceneGraphProcessor::hasIndexedLineSetHidden() {
  return _hasShapeProperty(_hasIndexedLineSetHidden);
}

void SceneGraphProcessor::removeSceneGraphChild(const string& name) {

  // TODO
    Node* child = _wrl.find(name);
    if(child!=NULL){
        Group* parent = (Group*)child->getParent();
        parent->removeChild(child);
    }

}

void SceneGraphProcessor::pointsRemove() {
  removeSceneGraphChild("POINTS");
}

void SceneGraphProcessor::surfaceRemove() {
  removeSceneGraphChild("SURFACE");
}

IndexedFaceSet* SceneGraphProcessor::_getNamedShapeIFS
(const string& name, bool create) {

  IndexedFaceSet* ifs = (IndexedFaceSet*)0;

  // TODO

  // 1) look for a child of the SceneGraph node with the given name

  // 2) if found, and the geometry field contains an IndexedFaceSet
  // node, return the pointer to the IndexedFaceSet node.

  // 3) otherwise, if create==true, create a new Shape node, make it a
  // child of the SceneGraph, add an Appearance node as appearance,
  // add an IndexedFaceSet as geometry, and return the pointer to the
  // IndexedFaceSet node.

  // 4) make sure tha the Appearance node has a Material node in the
  // material field with a properly defined diffuseColor field, before
  // you return
    Node* node = _wrl.find(name);
    if(node!=(Node*)0 && node->isShape()){
        Shape* shape = (Shape*)node;
        if(shape->hasGeometryIndexedFaceSet()){
            Appearance* appear = (Appearance*)shape->getAppearance();
            if(appear->getMaterial()!=(Node*)0)
            ifs = (IndexedFaceSet*)shape->getGeometry();
        }
    }else if(create==true){
        Shape* shape = new Shape();
        Appearance* appear = new Appearance();
        appear->setMaterial(new Material());
        shape->setAppearance(appear);
        shape->setGeometry(new IndexedFaceSet());
        _wrl.addChild(shape);
        ifs = (IndexedFaceSet*)shape->getGeometry();
    }
  return ifs;
}

//////////////////////////////////////////////////////////////////////
void eigenFit(const vector<float>& coordPoints,
              const Vec3f& min, const Vec3f& max, Vec4f& f) {

  char str[256];
  cerr << "eigenFit() {" <<endl;

  int nPoints = (int)((coordPoints.size())/3);
  float x0 = min.x, x1 = max.x, dx = x1-x0;
  float y0 = min.y, y1 = max.y, dy = y1-y0;
  float z0 = min.z, z1 = max.z, dz = z1-z0;
  float dMax = dx; if(dy>dMax) dMax = dy; if(dz>dMax) dMax = dz;

  // compute the mean of the points contained in the 
  double x,y,z;
  double xMean = 0.0f;
  double yMean = 0.0f;
  double zMean = 0.0f;
  int   nMean = 0;
  for(int iP=0;iP<nPoints;iP++) {
    x = (double)(coordPoints[3*iP  ]);
    y = (double)(coordPoints[3*iP+1]);
    z = (double)(coordPoints[3*iP+2]);
    if(x0<=x && x<=x1 && y0<=y && y<=y1 && z0<=z && z<=z1) {
      xMean += x;
      yMean += y;
      zMean += z;
      nMean++;
    }
  }

  cerr << "  nMean = " << nMean << endl;
  if(nMean==0) {
    // throw exception ??
    return;
  }

  xMean /= ((double)nMean);
  yMean /= ((double)nMean);
  zMean /= ((double)nMean);

  cerr << "  pMean = [" <<endl;
  sprintf(str,"    %12.6f",xMean); cerr << str << endl;
  sprintf(str,"    %12.6f",yMean); cerr << str << endl;
  sprintf(str,"    %12.6f",zMean); cerr << str << endl;
  cerr << "  ]" <<endl;

  // compute the scatter matrix
  double dxp,dyp,dzp;
  double M00=0.0,M01=0.0,M02=0.0,M11=0.0,M12=0.0,M22=0.0;
  for(int iP=0;iP<nPoints;iP++) {
    x = (double)(coordPoints[3*iP  ]);
    y = (double)(coordPoints[3*iP+1]);
    z = (double)(coordPoints[3*iP+2]);
    if(x0<=x && x<=x1 && y0<=y && y<=y1 && z0<=z && z<=z1) {
      dxp = (x-xMean)/dMax;
      dyp = (y-yMean)/dMax;
      dzp = (z-zMean)/dMax;
      M00 += dxp*dxp; M01 += dxp*dyp; M02 += dxp*dzp;
                      M11 += dyp*dyp; M12 += dyp*dzp;
                                      M22 += dzp*dzp;
    }
  }

  double dMean = (double)nMean;
  M00 /= dMean; M01 /= dMean; M02 /= dMean;
                M11 /= dMean; M12 /= dMean;
                              M22 /= dMean;
  Matrix3d M;
  M << M00,M01,M02,M01,M11,M12,M02,M12,M22;

  // double dMean = (double)nMean;
  // M(0,0) /= dMean; M(0,1) /= dMean; M(0,2) /= dMean;
  // M(1,0) /= dMean; M(1,1) /= dMean; M(1,2) /= dMean;
  // M(2,0) /= dMean; M(2,1) /= dMean; M(2,2) /= dMean;

  cerr << "  M = [" << endl;
  sprintf(str,"    %12.6f %12.6f %12.6f",M(0,0),M(0,1),M(0,2)); cerr << str << endl;
  sprintf(str,"    %12.6f %12.6f %12.6f",M(1,0),M(1,1),M(1,2)); cerr << str << endl;
  sprintf(str,"    %12.6f %12.6f %12.6f",M(2,0),M(2,1),M(2,2)); cerr << str << endl;
  cerr << "  ]" << endl;

  SelfAdjointEigenSolver<Matrix3d> eigensolver(M);

  if(eigensolver.info() != Success) {
    // trow exception ?
    // abort();
    return;
  }

  Vector3d L(eigensolver.eigenvalues());
  Matrix3d E(eigensolver.eigenvectors());

  cerr << "  eigenvalues(M)"<< endl;
  cerr << "  L = [" << endl;
  sprintf(str,"    %12.6f",L(0)); cerr << str << endl;
  sprintf(str,"    %12.6f",L(1)); cerr << str << endl;
  sprintf(str,"    %12.6f",L(2)); cerr << str << endl;
  cerr << "  ]" << endl;

  cerr << "  eigenvectors(M)"<< endl;
  cerr << "  E = [" << endl;
  sprintf(str,"    %12.6f %12.6f %12.6f",E(0,0),E(0,1),E(0,2)); cerr << str << endl;
  sprintf(str,"    %12.6f %12.6f %12.6f",E(1,0),E(1,1),E(1,2)); cerr << str << endl;
  sprintf(str,"    %12.6f %12.6f %12.6f",E(2,0),E(2,1),E(2,2)); cerr << str << endl;
  cerr << "  ]" << endl;

  // L(0)                   minimum eigenvalue
  // (E(0,0),E(1,0),E(2,0)) minimum eigenvector

  f.x =  (float)(E(0,0));
  f.y =  (float)(E(1,0));
  f.z =  (float)(E(2,0));
  f.w = -(float)(E(0,0)*xMean+E(1,0)*yMean+E(2,0)*zMean);

  cerr << "  f = [" << endl;
  sprintf(str,"    %12.6f",f.x);  cerr << str << endl;
  sprintf(str,"    %12.6f",f.y);  cerr << str << endl;
  sprintf(str,"    %12.6f",f.z);  cerr << str << endl;
  sprintf(str,"    %12.6f",f.w);  cerr << str << endl;
  cerr << "  ]" << endl;

  cerr << "}" <<endl;
}

//////////////////////////////////////////////////////////////////////
void meanFit(const vector<float>& coordPoints,
             const vector<float>& normalPoints,
             const Vec3f& min, const Vec3f& max, Vec4f& f) {

  int nPoints = (int)((coordPoints.size())/3);
  float x0 = min.x, x1 = max.x, dx = x1-x0;
  float y0 = min.y, y1 = max.y, dy = y1-y0;
  float z0 = min.z, z1 = max.z, dz = z1-z0;
  float dMax = dx; if(dy>dMax) dMax = dy; if(dz>dMax) dMax = dz;

  // compute the mean of the points contained in the 
  double x,y,z,nn;
  double xMean = 0.0f;
  double yMean = 0.0f;
  double zMean = 0.0f;
  double nxMean = 0.0f;
  double nyMean = 0.0f;
  double nzMean = 0.0f;
  int    nMean = 0;
  for(int iP=0;iP<nPoints;iP++) {
    x = (double)(coordPoints[3*iP  ]);
    y = (double)(coordPoints[3*iP+1]);
    z = (double)(coordPoints[3*iP+2]);
    if(x0<=x && x<=x1 && y0<=y && y<=y1 && z0<=z && z<=z1) {
      xMean += x;
      yMean += y;
      zMean += z;
      x = (double)(normalPoints[3*iP  ]);
      y = (double)(normalPoints[3*iP+1]);
      z = (double)(normalPoints[3*iP+2]);
      nxMean += x;
      nyMean += y;
      nzMean += z;
      nMean++;
    }
  }

  if(nMean==0) {
    // throw exception ??
    return;
  }

  // normalize the point mean
  xMean /= ((double)nMean);
  yMean /= ((double)nMean);
  zMean /= ((double)nMean);
  // normalize the normal mean to unit length
  nn = nxMean*nxMean+nyMean*nyMean+nzMean*nzMean;
  if(nn>0.0) {
    nn = sqrt(nn); nxMean/=nn; nyMean/=nn; nzMean/=nn;
  }
  // set the linear function coefficients
  f.x =  (float)(nxMean);
  f.y =  (float)(nyMean);
  f.z =  (float)(nzMean);
  f.w = -(float)(nxMean*xMean+nyMean*yMean+nzMean*zMean);
}

//////////////////////////////////////////////////////////////////////
void SceneGraphProcessor::fitSinglePlane
(const Vec3f& center, const Vec3f& size,
 const float scale, const bool cube, Vec4f& f) {

  cerr << "SceneGraphProcessor::fitSinglePlane() {" << endl;

  // 1) make sure that the bounding box is not empty; if empty throw a
  // StrExeption with a proper message
    if(_wrl.hasEmptyBBox()) throw new StrException("has no bounding box");
  // 2) find or create the input POINTS set in the scene graph; input
  // points must have coordinates and normal vector; otherwise throw
  // an StrException
    
    Shape* points = (Shape*)0;
    int length = _wrl.getChildren().size();
    for(int index =0; index<length; index++){
        Node* node = _wrl.getChildren().at(index);
        if(node->isShape() && node->nameEquals("POINTS")){
            points = (Shape*)node;
            if(((IndexedFaceSet*)points->getGeometry())->getCoord().size()==0 || ((IndexedFaceSet*)points->getGeometry())->getNormal().size()==0) throw new StrException("Invalid Points");
        }
    }
  // get from the POINTS IndexedFaceSet
    vector<float>& coordPoints = ((IndexedFaceSet*)points->getGeometry())->getCoord();
    vector<float>& normalPoints = ((IndexedFaceSet*)points->getGeometry())->getNormal();

  // 3) compute the coordinates of the SceneGraph bounding box corners
//    _wrl.updateBBox(cube);
    Vec3f bbox_center = _wrl.getBBoxCenter();
    Vec3f bbox_size = _wrl.getBBoxSize();
    float temp=0;
    if(cube){
        if(bbox_size.x>temp){
            temp = bbox_size.x;
        }
        if(bbox_size.y>temp) temp = bbox_size.y;
        if(bbox_size.z>temp) temp = bbox_size.z;
    }
    Vec3f min(bbox_center.x-0.5*scale*bbox_size.x, bbox_center.y-0.5*scale*bbox_size.y, bbox_center.z-0.5*scale*bbox_size.z);
    Vec3f max(bbox_center.x+0.5*scale*bbox_size.x, bbox_center.y+0.5*scale*bbox_size.y, bbox_center.z+0.5*scale*bbox_size.z);
    vector<Vec3f> v;
    v.push_back(min);
    Vec3f vec1(bbox_center.x+0.5*scale*bbox_size.x, bbox_center.y-0.5*scale*bbox_size.y, bbox_center.z-0.5*scale*bbox_size.z);
    v.push_back(vec1);
    Vec3f vec2(bbox_center.x-0.5*scale*bbox_size.x, bbox_center.y+0.5*scale*bbox_size.y, bbox_center.z-0.5*scale*bbox_size.z);
    v.push_back(vec2);
    Vec3f vec3(bbox_center.x+0.5*scale*bbox_size.x, bbox_center.y+0.5*scale*bbox_size.y, bbox_center.z-0.5*scale*bbox_size.z);
    v.push_back(vec3);
    Vec3f vec4(bbox_center.x-0.5*scale*bbox_size.x, bbox_center.y-0.5*scale*bbox_size.y, bbox_center.z+0.5*scale*bbox_size.z);
    v.push_back(vec4);
    Vec3f vec5(bbox_center.x+0.5*scale*bbox_size.x, bbox_center.y-0.5*scale*bbox_size.y, bbox_center.z+0.5*scale*bbox_size.z);
    v.push_back(vec5);
    Vec3f vec6(bbox_center.x-0.5*scale*bbox_size.x, bbox_center.y+0.5*scale*bbox_size.y, bbox_center.z+0.5*scale*bbox_size.z);
    v.push_back(vec6);
    v.push_back(max);
    
  // 4) fit a plane to the points contained in the bounding box
    eigenFit(coordPoints,min,max,f);
    meanFit(coordPoints,normalPoints,min,max,f);

  // 5) find or create the output SURFACE in the scene graph
    Shape* surface_points = (Shape*)0;
    for(int index =0; index<length; index++){
        Node* node = _wrl.getChildren().at(index);
        if(node->isShape() && node->nameEquals("SURFACE")){
            surface_points = (Shape*)node;
            if(((IndexedFaceSet*)surface_points->getGeometry())->getCoord().size()==0 || ((IndexedFaceSet*)surface_points->getGeometry())->getNormal().size()==0) throw new StrException("Invalid Surface");
        }
    }
    if(surface_points==(Shape*)0){
        surface_points = new Shape();
        surface_points->setName("SURFACE");
        surface_points->setGeometry(new IndexedFaceSet());
        Appearance* appearance = new Appearance();
        appearance->setMaterial(new Material());
        surface_points->setAppearance(appearance);
        _wrl.addChild(surface_points);
        surface_points->setParent(&_wrl);
    }
    IndexedFaceSet* plane = ((IndexedFaceSet*)surface_points->getGeometry());
  // get from the SURFACE IndexedFaceSet
    vector<float>&      coordIfs = plane->getCoord();
    vector<int>&   coordIndexIfs = plane->getCoordIndex();
  // 6) evaluate the linear function at bounding box corners
    float F[8]; // function values at bbox corners
    bool  b[8]; // function is positive or negative ?
    for(int i=0;i<8;i++) {
    // set (x,y,z) the the i=th corner coordinates
      float x= v[i].x;
      float y = v[i].y;
      float z = v[i].z;
    // computed in step 3) above
    b[i] = (F[i] = x*f.x+y*f.y+z*f.z+f.w)<0.0f;
  }

  cerr << "//                6 ----- 7 = (x1,y1,z1)" << endl;
  cerr << "//               /|      /|             " << endl;
  cerr << "//              4 ----- 5 |             " << endl;
  cerr << "//              | |     | |             " << endl;
  cerr << "//              | 2 ----| 3             " << endl;
  cerr << "//              |/      |/              " << endl;
  cerr << "// (x0,y0,z0) = 0 ----- 1               " << endl;

  cerr << "  b = [" << endl;
  cerr << "    " << b[0] << endl;
  cerr << "    " << b[1] << endl;
  cerr << "    " << b[2] << endl;
  cerr << "    " << b[3] << endl;
  cerr << "    " << b[4] << endl;
  cerr << "    " << b[5] << endl;
  cerr << "    " << b[6] << endl;
  cerr << "    " << b[7] << endl;
  cerr << "  ]" << endl;

  //////////////////////////////////////////////////////////////////////
  //
  //    vertices      //    edges                 //    faces
  //      6-----7     //        [6]---11---[7]    //        1
  //     /|    /|     //        /|         /|     //        | 3
  //    4-----5 |     //       6 2        7 3     //        |/
  //    | 2---|-3     //      /  |       /  |     //    4---+---5
  //    |/    |/      //    [4]---10---[5]  |     //       /|
  //    0-----1       //     |   |      |   |     //      2 |
  //                  //     |  [2]--9--|--[3]    //        0
  //                  //     0  /       1  /      //
  //                  //     | 4        | 5       //
  //                  //     |/         |/        //
  //                  //    [0]---8----[1]        //
  //
    
  const int (*edge)[2] = IsoSurf::getEdgeTable();

  // 7) compute the isovertex coordinates;
  // can you explain what is going on here?

  float tj,tk;
  int   iE[12],iV,i,j,k;
  for(i=0;i<12;i++) {
    iV   = -1;
    j    = edge[i][0];
    k    = edge[i][1];
    if(b[j]!=b[k]) {
      // isvertex index
      iV = (int)((coordIfs.size()/3));
      // isovertex coordinates
      tk = F[j]/(F[j]-F[k]);
      tj = F[k]/(F[k]-F[j]);
      float x  = tj*v[j].x+tk*v[k].x;
      float y  = tj*v[j].y+tk*v[k].y;
      float z  = tj*v[j].z+tk*v[k].z;
      coordIfs.push_back(x);
      coordIfs.push_back(y);
      coordIfs.push_back(z);
    }
    iE[i] = iV;
  }
  cerr << "  edge to isovertex table" << endl;
  cerr << "  iE = [" << endl;
   char str[256];
  for(i=0;i<12;i++) {
    sprintf(str,"    %2d (%2d, %2d) -> %3d",i,
            edge[i][0],edge[i][1],iE[i]);
    cerr << str << endl;
  }
  cerr << "  ]" << endl;

  // 8) create isosurface faces
//  vector<int>& coordIndex = surface_points->getCoordIndex(); // coordIndex.size()==0
    int nFaces = IsoSurf::makeCellFaces(b,iE,coordIndexIfs);
  cerr << "  nFaces = " << nFaces << endl;
//
//  // 9) save face normal
  ((IndexedFaceSet*)surface_points->getGeometry())->setNormalPerVertex(false);
  vector<float>& normal = plane->getNormal();
//   normal.size()==0 here
  normal.push_back(f.x);
  normal.push_back(f.y);
  normal.push_back(f.z);

  cerr << "}" << endl;
    v.clear();
}

//////////////////////////////////////////////////////////////////////
void SceneGraphProcessor::fitMultiplePlanes
(const Vec3f& center, const Vec3f& size,
 const int depth, const float scale, const bool cube,
 vector<float>& f) {

  // TODO

  // 1) find or create the POINTS Shape node; extract coordinates and normal
  // vectors from the IndexedFaceSet stored in the geometry field
  //
    Shape* points = (Shape*)0;
    int length = _wrl.getChildren().size();
    for(int index =0; index<length; index++){
        Node* node = _wrl.getChildren().at(index);
        if(node->isShape() && node->nameEquals("POINTS")){
            points = (Shape*)node;
            if(((IndexedFaceSet*)points->getGeometry())->getCoord().size()==0 || ((IndexedFaceSet*)points->getGeometry())->getNormal().size()==0) throw new StrException("Invalid Points");
        }
    }
    // get from the POINTS IndexedFaceSet
    vector<float>& coordPoints = ((IndexedFaceSet*)points->getGeometry())->getCoord();
    vector<float>& normalPoints = ((IndexedFaceSet*)points->getGeometry())->getNormal();
    
  // 2) find or create the SURFACE Shape node, and clear the
  // IndexedFaceSet stored in the geometry field
    Shape* surface_points = (Shape*)0;
    for(int index =0; index<length; index++){
        Node* node = _wrl.getChildren().at(index);
        if(node->isShape() && node->nameEquals("SURFACE")){
            surface_points = (Shape*)node;
            if(((IndexedFaceSet*)surface_points->getGeometry())->getCoord().size()==0 || ((IndexedFaceSet*)surface_points->getGeometry())->getNormal().size()==0) throw new StrException("Invalid Surface");
        }
    }
    if(surface_points==NULL){
        surface_points = new Shape();
        surface_points->setName("SURFACE");
        surface_points->setGeometry(new IndexedFaceSet());
        Appearance* appearance = new Appearance();
        appearance->setMaterial(new Material());
        surface_points->setAppearance(appearance);
        _wrl.addChild(surface_points);
        surface_points->setParent(&_wrl);
    }
    ((IndexedFaceSet*)surface_points->getGeometry())->clear();
    vector<float>&      coordIfs = ((IndexedFaceSet*)surface_points->getGeometry())->getCoord();
    vector<int>&   coordIndexIfs = ((IndexedFaceSet*)surface_points->getGeometry())->getCoordIndex();
    ((IndexedFaceSet*)surface_points->getGeometry())->setNormalPerVertex(false);
    vector<float>& normal = ((IndexedFaceSet*)surface_points->getGeometry())->getNormal();

  // 3) the argument vector<float>&f will contain one scalar values;
  // clear it here
    f.clear();
  // 4) if the bounding box is empty (size.x==size.y==size.z==0) or scale<=0
  // throw an StrException 
    if((size.x==0 && size.y==0 && size.z==0)||scale<=0) throw new StrException("Has no bounding box");
  // 5) compute the coordinates of the 8 vertices of the scaled bounding box
//    _wrl.updateBBox(cube);
    Vec3f bbox_center = _wrl.getBBoxCenter();
    Vec3f bbox_size = _wrl.getBBoxSize();
    float temp=0;
    if(cube){
        if(bbox_size.x>temp){
            temp = bbox_size.x;
        }
        if(bbox_size.y>temp) temp = bbox_size.y;
        if(bbox_size.z>temp) temp = bbox_size.z;
    }
    Vec3f min(bbox_center.x-0.5*scale*bbox_size.x, bbox_center.y-0.5*scale*bbox_size.y, bbox_center.z-0.5*scale*bbox_size.z);
    Vec3f max(bbox_center.x+0.5*scale*bbox_size.x, bbox_center.y+0.5*scale*bbox_size.y, bbox_center.z+0.5*scale*bbox_size.z);
    
  // 6) create a partition of the points as an array of linked lists

    _createPartition(min,max,depth,coordPoints);
    Vec3f minCell, maxCell;
    int N = (int)pow(2, depth);
    
  // 7) for each occupied cell, fit a plane, and compute the
  // isosurface polygon within the corresponding cube; accumulate
  // polygons as vertices faces, and face normals of the SURFACE
  // IndexedFaceSet
    vector<float> coordPoints_cell;
    vector<float> normalPoints_cell;
    for(int cell_i=0; cell_i<N; cell_i++){
        for(int cell_j=0; cell_j<N; cell_j++){
            for(int cell_k=0; cell_k<N; cell_k++){
                coordPoints_cell.clear();
                normalPoints_cell.clear();
                int iCell = cell_k+N*(cell_j+N*cell_i);
                if(_first[iCell]<0){
                    continue;
                }
                //find all points in a cell
                for(int iP=_first[iCell]; iP>=0; iP=_next[iP]){
                    coordPoints_cell.push_back(coordPoints[iP*3]);
                    coordPoints_cell.push_back(coordPoints[iP*3+1]);
                    coordPoints_cell.push_back(coordPoints[iP*3+2]);
                    normalPoints_cell.push_back(normalPoints[iP*3]);
                    normalPoints_cell.push_back(normalPoints[iP*3+1]);
                    normalPoints_cell.push_back(normalPoints[iP*3+2]);
                }
                
                minCell.x = ((N-cell_k  )*min.x+(cell_k  )*max.x)/N;
                maxCell.x = ((N-cell_k-1)*min.x+(cell_k+1)*max.x)/N;
                minCell.y = ((N-cell_j  )*min.y+(cell_j  )*max.y)/N;
                maxCell.y = ((N-cell_j-1)*min.y+(cell_j+1)*max.y)/N;
                minCell.z = ((N-cell_i  )*min.z+(cell_i  )*max.z)/N;
                maxCell.z = ((N-cell_i-1)*min.z+(cell_i+1)*max.z)/N;
            
                Vec4f scalar;
                eigenFit(coordPoints_cell, minCell, maxCell, scalar);
                meanFit(coordPoints_cell, normalPoints_cell, minCell, maxCell, scalar);
                f.push_back(scalar.x);
                f.push_back(scalar.y);
                f.push_back(scalar.z);
                f.push_back(scalar.w);
                
                //calculate eigth corners of the cell
                vector<Vec3f> cells;
                Vec3f v0(minCell.x, minCell.y, minCell.z);
                Vec3f v1(maxCell.x, minCell.y, minCell.z);
                Vec3f v2(minCell.x, maxCell.y, minCell.z);
                Vec3f v3(maxCell.x, maxCell.y, minCell.z);
                Vec3f v4(minCell.x, minCell.y, maxCell.z);
                Vec3f v5(maxCell.x, minCell.y, maxCell.z);
                Vec3f v6(minCell.x, maxCell.y, maxCell.z);
                Vec3f v7(maxCell.x, maxCell.y, maxCell.z);
                cells.push_back(v0); cells.push_back(v1); cells.push_back(v2);
                cells.push_back(v3); cells.push_back(v4); cells.push_back(v5);
                cells.push_back(v6); cells.push_back(v7);
                float F[8]; // function values at bbox corners
                bool  b[8]; // function is positive or negative ?
                for(int i=0;i<8;i++) {
                    // set (x,y,z) the the i=th corner coordinates
                    float x= cells[i].x;
                    float y = cells[i].y;
                    float z = cells[i].z;
                    // computed in step 3) above
                    b[i] = (F[i] = x*scalar.x+y*scalar.y+z*scalar.z+scalar.w)<0.0f;
                }
                const int (*edge)[2] = IsoSurf::getEdgeTable();
                
                // 7) compute the isovertex coordinates;
                // can you explain what is going on here?
                
                float tj,tk;
                int   iE[12],iV, i, j, k;
                for(i=0;i<12;i++) {
                    iV   = -1;
                    j    = edge[i][0];
                    k    = edge[i][1];
                    if(b[j]!=b[k]) {
                        // isvertex index
                        iV = (int)((coordIfs.size()/3));
                        // isovertex coordinates
                        tk = F[j]/(F[j]-F[k]);
                        tj = F[k]/(F[k]-F[j]);
                        float x  = tj*cells[j].x+tk*cells[k].x;
                        float y  = tj*cells[j].y+tk*cells[k].y;
                        float z  = tj*cells[j].z+tk*cells[k].z;
                        coordIfs.push_back(x);
                        coordIfs.push_back(y);
                        coordIfs.push_back(z);
                    }
                    iE[i] = iV;
                }
                
                int nfaces = IsoSurf::makeCellFaces(b,iE,coordIndexIfs);
                //
                //  // 9) save face normal
                //   normal.size()==0 here
                normal.push_back(scalar.x);
                normal.push_back(scalar.y);
                normal.push_back(scalar.z);
                cells.clear();
            }
        }
    }

  // 8) delete partition

  _deletePartition();
}

//////////////////////////////////////////////////////////////////////
void SceneGraphProcessor::fitContinuous
(const Vec3f& center, const Vec3f& size,
 const int depth, const float scale, const bool cube) {

  // 1) same as fitMultiplePlanes, but rather than computing the
  // isosurfaces within the hexahedral cells right away, first save
  // the linear function values at the corners of the cells
    
    Shape* points = (Shape*)0;
    int length = _wrl.getChildren().size();
    for(int index =0; index<length; index++){
        Node* node = _wrl.getChildren().at(index);
        if(node->isShape() && node->nameEquals("POINTS")){
            points = (Shape*)node;
            if(((IndexedFaceSet*)points->getGeometry())->getCoord().size()==0 || ((IndexedFaceSet*)points->getGeometry())->getNormal().size()==0) throw new StrException("Invalid Points");
        }
    }
    // get from the POINTS IndexedFaceSet
    vector<float>& coordPoints = ((IndexedFaceSet*)points->getGeometry())->getCoord();
    vector<float>& normalPoints = ((IndexedFaceSet*)points->getGeometry())->getNormal();
    
    // 2) find or create the SURFACE Shape node, and clear the
    // IndexedFaceSet stored in the geometry field
    Shape* surface_points = (Shape*)0;
    for(int index =0; index<length; index++){
        Node* node = _wrl.getChildren().at(index);
        if(node->isShape() && node->nameEquals("SURFACE")){
            surface_points = (Shape*)node;
            if(((IndexedFaceSet*)surface_points->getGeometry())->getCoord().size()==0 || ((IndexedFaceSet*)surface_points->getGeometry())->getNormal().size()==0) throw new StrException("Invalid Surface");
        }
    }
    if(surface_points==NULL){
        surface_points = new Shape();
        surface_points->setName("SURFACE");
        surface_points->setGeometry(new IndexedFaceSet());
        Appearance* appearance = new Appearance();
        appearance->setMaterial(new Material());
        surface_points->setAppearance(appearance);
        _wrl.addChild(surface_points);
        surface_points->setParent(&_wrl);
    }
    ((IndexedFaceSet*)surface_points->getGeometry())->clear();
    vector<float>&      coordIfs = ((IndexedFaceSet*)surface_points->getGeometry())->getCoord();
    vector<int>&   coordIndexIfs = ((IndexedFaceSet*)surface_points->getGeometry())->getCoordIndex();
    ((IndexedFaceSet*)surface_points->getGeometry())->setNormalPerVertex(false);
    vector<float>& normal = ((IndexedFaceSet*)surface_points->getGeometry())->getNormal();
    normal.clear();
    coordIfs.clear();
    coordIndexIfs.clear();
    
    // 4) if the bounding box is empty (size.x==size.y==size.z==0) or scale<=0
    // throw an StrException
    if((size.x==0 && size.y==0 && size.z==0)||scale<=0) throw new StrException("Has no bounding box");
    // 5) compute the coordinates of the 8 vertices of the scaled bounding box
//    _wrl.updateBBox(cube);
    Vec3f bbox_center = _wrl.getBBoxCenter();
    Vec3f bbox_size = _wrl.getBBoxSize();
    float temp=0;
    if(cube){
        if(bbox_size.x>temp){
            temp = bbox_size.x;
        }
        if(bbox_size.y>temp) temp = bbox_size.y;
        if(bbox_size.z>temp) temp = bbox_size.z;
    }
    Vec3f min(bbox_center.x-0.5*scale*bbox_size.x, bbox_center.y-0.5*scale*bbox_size.y, bbox_center.z-0.5*scale*bbox_size.z);
    Vec3f max(bbox_center.x+0.5*scale*bbox_size.x, bbox_center.y+0.5*scale*bbox_size.y, bbox_center.z+0.5*scale*bbox_size.z);
    
    // 6) create a partition of the points as an array of linked lists
    
    _createPartition(min,max,depth,coordPoints);
    Vec3f minCell, maxCell;
    int N = (int)pow(2, depth);
  // 2) note that empty cells do not have function values associated
  // with
    int nGridVertices = (N+1)*(N+1)*(N+1);
    float* fGridVertex = new float[nGridVertices];
    float* wGridVertex = new float[nGridVertices];
    for(int i=0; i< nGridVertices; i++) fGridVertex[i]=0.0f;
    for(int i=0; i< nGridVertices; i++) wGridVertex[i]=0.0f;
//    int iCell=0;
    //first loop, fit linear function to the points in each cell
    vector<float> coordPoints_cell;
    vector<float> normalPoints_cell;
    for(int cell_i=0; cell_i<N; cell_i++){
        for(int cell_j=0; cell_j<N; cell_j++){
            for(int cell_k=0; cell_k<N; cell_k++){
                
                int iCell = cell_k+N*(cell_j+N*cell_i);
                if(_first[iCell]<0){
                    iCell++;
                    continue;
                }
                //find all points in a cell
                for(int iP=_first[iCell]; iP>=0; iP=_next[iP]){
                    coordPoints_cell.push_back(coordPoints[iP*3]);
                    coordPoints_cell.push_back(coordPoints[iP*3+1]);
                    coordPoints_cell.push_back(coordPoints[iP*3+2]);
                    normalPoints_cell.push_back(normalPoints[iP*3]);
                    normalPoints_cell.push_back(normalPoints[iP*3+1]);
                    normalPoints_cell.push_back(normalPoints[iP*3+2]);
                }
            
          // 3) for each grid vertex of an occupied incident cell, compute the
          // average of the values saved on the incident cell corners; and
          // then replace the incident cell corner values by the average.
                minCell.x = ((N-cell_k  )*min.x+(cell_k  )*max.x)/N;
                maxCell.x = ((N-cell_k-1)*min.x+(cell_k+1)*max.x)/N;
                minCell.y = ((N-cell_j  )*min.y+(cell_j  )*max.y)/N;
                maxCell.y = ((N-cell_j-1)*min.y+(cell_j+1)*max.y)/N;
                minCell.z = ((N-cell_i  )*min.z+(cell_i  )*max.z)/N;
                maxCell.z = ((N-cell_i-1)*min.z+(cell_i+1)*max.z)/N;
                
                vector<Vec3f> cells;
                Vec3f v0(minCell.x, minCell.y, minCell.z);
                Vec3f v1(maxCell.x, minCell.y, minCell.z);
                Vec3f v2(minCell.x, maxCell.y, minCell.z);
                Vec3f v3(maxCell.x, maxCell.y, minCell.z);
                Vec3f v4(minCell.x, minCell.y, maxCell.z);
                Vec3f v5(maxCell.x, minCell.y, maxCell.z);
                Vec3f v6(minCell.x, maxCell.y, maxCell.z);
                Vec3f v7(maxCell.x, maxCell.y, maxCell.z);
                cells.push_back(v0); cells.push_back(v1); cells.push_back(v2);
                cells.push_back(v3); cells.push_back(v4); cells.push_back(v5);
                cells.push_back(v6); cells.push_back(v7);

                Vec4f scalar;
                eigenFit(coordPoints_cell, minCell, maxCell, scalar);
                meanFit(coordPoints_cell, normalPoints_cell, minCell, maxCell, scalar);
                
                for(int i=0;i<8;i++) {
                    // set (x,y,z) the the i=th corner coordinates
                    float x= cells[i].x;
                    float y = cells[i].y;
                    float z = cells[i].z;
                    // determine the grid vertex index iV of the corner
                    int coord_x = (N+1)*(x-min.x)/(max.x-min.x);
                    int coord_y = (N+1)*(y-min.y)/(max.y-min.y);
                    int coord_k = (N+1)*(z-min.z)/(max.z-min.z);
                    int iV = coord_x + (N+1)*(coord_y+(N+1)*coord_k);
                    fGridVertex[iV] = x*scalar.x+y*scalar.y+z*scalar.z+scalar.w;
                    wGridVertex[iV] += 1.0f;
                }
                // 9) save face normal
                // normal.size()==0 here
                
                
                coordPoints_cell.clear();
                normalPoints_cell.clear();
            }
        }
    }
    
    //normalize
    for(int iV=0; iV<nGridVertices; iV++){
        if(wGridVertex[iV]>0.0f) fGridVertex[iV] /= wGridVertex[iV];
    }
  // 4) now compute the isosurface polygon with the cells, as in the
  // fitMultiplePlanes method, but using the new values instead
    for(int cell_i=0; cell_i<N; cell_i++){
        for(int cell_j=0; cell_j<N; cell_j++){
            for(int cell_k=0; cell_k<N; cell_k++){
                
                int iCell = cell_k+N*(cell_j+N*cell_i);
                if(_first[iCell]<0){
                    continue;
                }
                coordPoints_cell.clear();
                normalPoints_cell.clear();
                
                for(int iP=_first[iCell]; iP>=0; iP=_next[iP]){
                    coordPoints_cell.push_back(coordPoints[iP*3]);
                    coordPoints_cell.push_back(coordPoints[iP*3+1]);
                    coordPoints_cell.push_back(coordPoints[iP*3+2]);
                    normalPoints_cell.push_back(normalPoints[iP*3]);
                    normalPoints_cell.push_back(normalPoints[iP*3+1]);
                    normalPoints_cell.push_back(normalPoints[iP*3+2]);
                }
                
                minCell.x = ((N-cell_k  )*min.x+(cell_k  )*max.x)/N;
                maxCell.x = ((N-cell_k-1)*min.x+(cell_k+1)*max.x)/N;
                minCell.y = ((N-cell_j  )*min.y+(cell_j  )*max.y)/N;
                maxCell.y = ((N-cell_j-1)*min.y+(cell_j+1)*max.y)/N;
                minCell.z = ((N-cell_i  )*min.z+(cell_i  )*max.z)/N;
                maxCell.z = ((N-cell_i-1)*min.z+(cell_i+1)*max.z)/N;
                
                Vec4f scalar;
                eigenFit(coordPoints_cell, minCell, maxCell, scalar);
                meanFit(coordPoints_cell, normalPoints_cell, minCell, maxCell, scalar);
                
                vector<Vec3f> cells;
                Vec3f v0(minCell.x, minCell.y, minCell.z);
                Vec3f v1(maxCell.x, minCell.y, minCell.z);
                Vec3f v2(minCell.x, maxCell.y, minCell.z);
                Vec3f v3(maxCell.x, maxCell.y, minCell.z);
                Vec3f v4(minCell.x, minCell.y, maxCell.z);
                Vec3f v5(maxCell.x, minCell.y, maxCell.z);
                Vec3f v6(minCell.x, maxCell.y, maxCell.z);
                Vec3f v7(maxCell.x, maxCell.y, maxCell.z);
                cells.push_back(v0); cells.push_back(v1); cells.push_back(v2);
                cells.push_back(v3); cells.push_back(v4); cells.push_back(v5);
                cells.push_back(v6); cells.push_back(v7);
                
                
                float F[8]; // function values at bbox corners
                bool  b[8]; // function is positive or negative ?
                for(int i=0;i<8;i++) {
                    float x = cells[i].x;
                    float y = cells[i].y;
                    float z = cells[i].z;
                    // determine the grid vertex index iV of the corner
                    int coord_x = (N+1)*(x-min.x)/(max.x-min.x);
                    int coord_y = (N+1)*(y-min.y)/(max.y-min.y);
                    int coord_k = (N+1)*(z-min.z)/(max.z-min.z);
                    int iV1 = coord_x + (N+1)*(coord_y+(N+1)*coord_k);
                    F[i] = fGridVertex[iV1];
                    b[i] = F[i]<0.0f;
                }
                const int (*edge)[2] = IsoSurf::getEdgeTable();
                
                // 5) fill the SURFACE IndexedFaceSet exactly as in the
                // fitMultiplePlanes method
                // 7) compute the isovertex coordinates;
                // can you explain what is going on here?
                
                float tj,tk;
                int   iE[12],iV, i, j, k;
                for(i=0;i<12;i++) {
                    iV   = -1;
                    j    = edge[i][0];
                    k    = edge[i][1];
                    if(b[j]!=b[k]) {
                        // isvertex index
                        iV = (int)((coordIfs.size()/3));
                        // isovertex coordinates
                        tk = F[j]/(F[j]-F[k]);
                        tj = F[k]/(F[k]-F[j]);
                        float x  = tj*cells[j].x+tk*cells[k].x;
                        float y  = tj*cells[j].y+tk*cells[k].y;
                        float z  = tj*cells[j].z+tk*cells[k].z;
                        coordIfs.push_back(x);
                        coordIfs.push_back(y);
                        coordIfs.push_back(z);
                    }
                    iE[i] = iV;
                }
                
                int nfaces = IsoSurf::makeCellFaces(b,iE,coordIndexIfs);
                for(int m=0; m<nfaces; m++){
                    normal.push_back(scalar.x);
                    normal.push_back(scalar.y);
                    normal.push_back(scalar.z);
                }
                cells.clear();
            }
        }
    }
    _deletePartition();
  
}
