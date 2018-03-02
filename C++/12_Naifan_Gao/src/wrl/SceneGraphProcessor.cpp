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
    Vec3f x0(center.x-0.5*scale*size.x, center.y-0.5*scale*size.y, center.z-0.5*scale*size.z);
    Vec3f x1(center.x+0.5*scale*size.x, center.y+0.5*scale*size.y, center.z+0.5*scale*size.z);
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
//    vector<float> fGrid;
//    fitWatertight(center, size, depth, scale, cube, fGrid);
//    fGrid.clear();

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

    // 4) if the bounding box is empty (size.x==size.y==size.z==0) or scale<=0
    // throw an StrException
    if((size.x==0 && size.y==0 && size.z==0)||scale<=0) throw new StrException("Has no bounding box");
    // 5) compute the coordinates of the 8 vertices of the scaled bounding box
//    _wrl.updateBBox(cube);
    Vec3f bbox_center = _wrl.getBBoxCenter();
    Vec3f bbox_size = _wrl.getBBoxSize();
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
                    int iV = 0;
                    // set (x,y,z) the the i=th corner coordinates
                    float x= cells[i].x;
                    float y = cells[i].y;
                    float z = cells[i].z;
                    // determine the grid vertex index iV of the corner
                    if(i==0) iV = cell_k + (N+1)*(cell_j+(N+1)*cell_i);
                    else if(i==1) iV = cell_k + (N+1)*(cell_j+(N+1)*cell_i) + 1;
                    else if(i==2) iV = cell_k + (N+1)*(cell_j+1+(N+1)*cell_i);
                    else if(i==3) iV = cell_k + (N+1)*(cell_j+1+(N+1)*cell_i) + 1;
                    else if(i==4) iV = cell_k + (N+1)*(cell_j+(N+1)*(cell_i+1));
                    else if(i==5) iV = cell_k + (N+1)*(cell_j+(N+1)*(cell_i+1)) + 1;
                    else if(i==6) iV = cell_k + (N+1)*(cell_j+1+(N+1)*(cell_i+1));
                    else if(i==7) iV = cell_k + (N+1)*(cell_j+1+(N+1)*(cell_i+1)) + 1;
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
    int i,j,k,iV,iVB[8],iE[12];
    float F[8];
    bool b[8];
    Vec3f v[8];
    
//    vector<float> coordIsosurf;
//    vector<int> coordIndexIsosurf;
    SimpleGraphMap map = SimpleGraphMap(N);
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
//
//
//                float F[8]; // function values at bbox corners
//                bool  b[8]; // function is positive or negative ?
                for(int i=0;i<8;i++) {
//                    float x = cells[i].x;
//                    float y = cells[i].y;
//                    float z = cells[i].z;
                    // determine the grid vertex index iV of the corner
//                    int coord_x = (N)*(x-min.x)/(max.x-min.x);
//                    int coord_y = (N)*(y-min.y)/(max.y-min.y);
//                    int coord_k = (N)*(z-min.z)/(max.z-min.z);
//                    iV = coord_x + (N+1)*(coord_y+(N+1)*coord_k);
                    if(i==0) iV = cell_k + (N+1)*(cell_j+(N+1)*cell_i);
                    else if(i==1) iV = cell_k + (N+1)*(cell_j+(N+1)*cell_i) + 1;
                    else if(i==2) iV = cell_k + (N+1)*(cell_j+1+(N+1)*cell_i);
                    else if(i==3) iV = cell_k + (N+1)*(cell_j+1+(N+1)*cell_i) + 1;
                    else if(i==4) iV = cell_k + (N+1)*(cell_j+(N+1)*(cell_i+1));
                    else if(i==5) iV = cell_k + (N+1)*(cell_j+(N+1)*(cell_i+1)) + 1;
                    else if(i==6) iV = cell_k + (N+1)*(cell_j+1+(N+1)*(cell_i+1));
                    else if(i==7) iV = cell_k + (N+1)*(cell_j+1+(N+1)*(cell_i+1)) + 1;
                    iVB[i] = iV;
                    F[i] = fGridVertex[iV];
                    b[i] = F[i]<0.0f;
                }
//                const int (*edge)[2] = IsoSurf::getEdgeTable();
//
//                // 5) fill the SURFACE IndexedFaceSet exactly as in the
//                // fitMultiplePlanes method
//                // 7) compute the isovertex coordinates;
//                // can you explain what is going on here?
//
                const int (*edge)[2] = IsoSurf::getEdgeTable();
                float tj,tk;
//                int   iE[12],iV, i, j, k;
                for(i=0;i<12;i++) {
                    iV   = -1;
                    j    = edge[i][0];
                    k    = edge[i][1];
                    if(b[j]!=b[k]) {
                        // isvertex index
                        iV = map.get(iVB[j], iVB[k]);
                        if(iV<0){//need to create a new vertex
                            iV = (int)((coordIfs.size())/3);
                            // isovertex coordinates
                            tk = F[j]/(F[j]-F[k]);
                            tj = F[k]/(F[k]-F[j]);
                            float x  = tj*cells[j].x+tk*cells[k].x;
                            float y  = tj*cells[j].y+tk*cells[k].y;
                            float z  = tj*cells[j].z+tk*cells[k].z;
                            coordIfs.push_back(x);
                            coordIfs.push_back(y);
                            coordIfs.push_back(z);
                            map.insert(iVB[j], iVB[k], iV);
                        }
                    }
                    iE[i] = iV;
                }
//
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

//////////////////////////////////////////////////////////////////////
void SceneGraphProcessor::fitWatertight
(const Vec3f& center, const Vec3f& size,
 const int depth, const float scale, const bool isCube,
 vector<float>& fGrid) {
    
    std::cerr << "SceneGraphProcessor::fitWatertight() {" << endl;
    
    if(size.x<=0.0f || size.y<=0.0f || size.z<=0.0f || scale<=0.0f) return;
    
    // 1) get the scene graph node named "POINTS"
    // IndexedFaceSet* points = ...
    Shape* points = (Shape*)0;
    int length = _wrl.getChildren().size();
    for(int index =0; index<length; index++){
        Node* node = _wrl.getChildren().at(index);
        if(node->isShape() && node->nameEquals("POINTS")){
            points = (Shape*)node;
            if(((IndexedFaceSet*)points->getGeometry())->getCoord().size()==0 || ((IndexedFaceSet*)points->getGeometry())->getNormal().size()==0) throw new StrException("Invalid Points");
        }
    }
    
    // 2) if there is no such node return without doing anything
    if(points==NULL) return;
    
    // 3) if the node is found but it is empty, or it does not have
    // normals per vertex, also return without doing anything
    if(points->getGeometry()==NULL||points->getAppearance()==NULL) return;
    if(((IndexedFaceSet*)points->getGeometry())->getNormalBinding()!=IndexedFaceSet::PB_PER_VERTEX) return;
    
    // 4) get the coord and normal vectors from the points node
    // vector<float>& coordPoints = ...
    // vector<float>& normalPoints = ...
    // get from the POINTS IndexedFaceSet
    vector<float>& coordPoints = ((IndexedFaceSet*)points->getGeometry())->getCoord();
    vector<float>& normalPoints = ((IndexedFaceSet*)points->getGeometry())->getNormal();
    
    // 5) from the center, size, and scale arguments, compute the min &
    // max corners of the bounding box
//    _wrl.updateBBox(isCube);
    Vec3f bbox_center = _wrl.getBBoxCenter();
    Vec3f bbox_size = _wrl.getBBoxSize();
    
    Vec3f min(bbox_center.x-0.5*scale*bbox_size.x, bbox_center.y-0.5*scale*bbox_size.y, bbox_center.z-0.5*scale*bbox_size.z);
    Vec3f max(bbox_center.x+0.5*scale*bbox_size.x, bbox_center.y+0.5*scale*bbox_size.y, bbox_center.z+0.5*scale*bbox_size.z);
    
    // 6) create a partition of the points as an array of linked lists
    _createPartition(min,max,depth,coordPoints);
    
    // 7) determine the total number of grid vertices as a function of
    // _nGrid
    // int nGridVertices = ...
    int N = _nGrid;
    int nGridVertices = (N+1)*(N+1)*(N+1);
    
    // 7) initialize fGrid with zeros
    fGrid.clear();
    fGrid.insert(fGrid.end(),nGridVertices,0.0f);
    // 8) create a temporary array of the same size to accumulate weights
    vector<float> wGrid;
    wGrid.insert(wGrid.end(),nGridVertices,0.0f);
    
    // 9) allocate arrays to do the local linear fit
    Vec4f fCell;
    Vec3f minCell,maxCell;
    vector<float> coordCell;
    vector<float> normalCell;
    
    // 10) accumulate grid vertex funtion values
    int iCell, iz, iy, ix, iPoint, nPoints;
    int nonEmptyCells = 0;
    vector<Vec3f> cells;
    Vec3f nCell;
    for(iCell=iz=0;iz<N;iz++) {
        minCell.z = (((float)(N-iz  ))*min.z+((float)(iz  ))*max.z)/((float)N);
        maxCell.z = (((float)(N-iz-1))*min.z+((float)(iz+1))*max.z)/((float)N);
        for(iy=0;iy<N;iy++) {
            minCell.y = (((float)(N-iy  ))*min.y+((float)(iy  ))*max.y)/((float)N);
            maxCell.y = (((float)(N-iy-1))*min.y+((float)(iy+1))*max.y)/((float)N);
            for(ix=0;ix<N;ix++,iCell++) {
                minCell.x = (((float)(N-ix  ))*min.x+((float)(ix  ))*max.x)/((float)N);
                maxCell.x = (((float)(N-ix-1))*min.x+((float)(ix+1))*max.x)/((float)N);
                
                if((iPoint=_first[iCell])>=0) { // cell iCell is not empty
                    nonEmptyCells++;
                    
                    // 11) copy coord and normal values of points in cell onto cell arrays
                    coordCell.clear();
                    normalCell.clear();
                    nCell.x=nCell.y=nCell.z;
                    for(nPoints=0;iPoint>=0;iPoint=_next[iPoint]) {
                        // ...
                        // count the number of points in the cell here
                        coordCell.push_back(coordPoints[iPoint*3]);
                        coordCell.push_back(coordPoints[iPoint*3+1]);
                        coordCell.push_back(coordPoints[iPoint*3+2]);
                        normalCell.push_back(normalPoints[iPoint*3]);
                        normalCell.push_back(normalPoints[iPoint*3+1]);
                        normalCell.push_back(normalPoints[iPoint*3+2]);
                    }
                    
                    // 12) fit a linear function to the points contained in the
                    // cell using the meanFit() method
                    meanFit(coordCell, normalCell, minCell, maxCell, fCell);
                    // 13) evaluate the local linear function at each of the
                    // cell's eight vertices, accumulate the values in the
                    // corresponding entries of the fGrid vector, and increment
                    // the corresponding entry of the weights vector wGrid by 1
                    int iV;
                    cells.clear();
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
                    for(int i=0;i<8;i++) {
                        // set (x,y,z) the the i=th corner coordinates
                        float x= cells[i].x;
                        float y = cells[i].y;
                        float z = cells[i].z;
                        // determine the grid vertex index iV of the corner
//                        int coord_x = (N)*(x-min.x)/(max.x-min.x);
//                        int coord_y = (N)*(y-min.y)/(max.y-min.y);
//                        int coord_k = (N)*(z-min.z)/(max.z-min.z);
//                        int iV = coord_x + (N+1)*(coord_y+(N+1)*coord_k);
                        if(i==0) iV = ix + (N+1)*(iy+(N+1)*iz);
                        if(i==1) iV = ix + (N+1)*(iy+(N+1)*iz) + 1;
                        if(i==2) iV = ix + (N+1)*(iy+1+(N+1)*iz);
                        if(i==3) iV = ix + (N+1)*(iy+1+(N+1)*iz) + 1;
                        if(i==4) iV = ix + (N+1)*(iy+(N+1)*(iz+1));
                        if(i==5) iV = ix + (N+1)*(iy+(N+1)*(iz+1)) + 1;
                        if(i==6) iV = ix + (N+1)*(iy+1+(N+1)*(iz+1));
                        if(i==7) iV = ix + (N+1)*(iy+1+(N+1)*(iz+1)) + 1;
                        fGrid[iV]= x*fCell.x+y*fCell.y+z*fCell.z+fCell.w;
                        wGrid[iV] += 1.0f;
                    }
                }
            }
        }
    }
    
    // 14) arrays needded to implement the wavefront propagation algorithm
    vector<int> src;
    vector<int> dst;
    int iV;
    // 15) normalize the fGrid values
    for(iV=0;iV<nGridVertices;iV++){
        if(wGrid[iV]>0.0f) { // only for vertices of occupied cells !
            fGrid[iV] /= wGrid[iV];
            // since the wGrid[iV] value is no longer needed, we will use it
            // to indicate which vertices have defined function values
            // (WGrid[iV]==-2), and which ones have undefined values
            // (wGrid[iV]==0)
            wGrid[iV] = -2.0f;
            // save the grid vertex indices of occupied cells in a list
            src.push_back(iV);
        }
    }
    
    // 16) extend vertex function values to all vertices by wavefront propagation
    
    int iV0,iV1;
    float fV0;
    while(src.size()>0) {
        
        // for each vertex in the wavefront
        while(src.size()>0) {
            iV0 = iV = src.back(); src.pop_back(); // wGrid[iV0]<0
            // 17) compute the x,y,z integer coordinates of the vertex
            // inverting the formula
            // iV = ix+(N+1)*(iy+(N+1)*iz);
            int iz = iV/((N+1)*(N+1));
            int iy = (iV-iz*(N+1)*(N+1))/(N+1);
            int ix = iV - iy*(N+1) - iz*(N+1)*(N+1);
            
            // 18) get the vertex function falue from fGrid
            fV0 = fGrid[iV0];
            // 19) for each of the 6 neighbors jV of vertex iV in the grid,
            // if vertex jV is inside the grid, and it does not have a
            // defined function value yet (i.e. wGrid[jV]>=0), then
            // 19.1) add the fGrid iV function value to the fGrid jV function
            // value
            // 19.2) increment the wGrid jV weight value by one
            // 19.3) if this is the first visit to this grid vertex (i.e. if
            // the wGrid jV value is equal to zero), save the jV index in
            // the output wavefront list dst
            int indexes[6];
            fill_n(indexes, 6, -1);
            if(ix>0)
                indexes[0] = ix-1+(N+1)*(iy+(N+1)*iz);
            if(ix<N)
                indexes[1] = ix+1+(N+1)*(iy+(N+1)*iz);
            if(iy>0)
                indexes[2] = ix+(N+1)*(iy-1+(N+1)*iz);
            if(iy<N)
                indexes[3] = ix+(N+1)*(iy+1+(N+1)*iz);
            if(iz>0)
                indexes[4] = ix+(N+1)*(iy+(N+1)*(iz-1));
            if(iz<N)
                indexes[5] = ix+(N+1)*(iy+(N+1)*(iz+1));
            for(int i=0; i<6; i++){
                int jV = indexes[i];
                if(jV>=0){
                    if(wGrid[jV]>=0){
                        if(wGrid[jV]==0) dst.push_back(jV);
                        fGrid[jV] += fV0;
                        wGrid[jV] += 1.0f;
                    }
                }
            }
        }
        // 20) note that at this point the src list is empty, and the dst
        // list in general is not empty
        
        // 20) normalize new function values for the grid vertices in the
        // new wavefront, and create new wavefront
        while(dst.size()>0) {
            iV1 = dst.back(); dst.pop_back();
             if(wGrid[iV1]>0.0f) {
            fGrid[iV1] /= wGrid[iV1];
            // we use -2 to indicate the vertices of the occupied cells, and
            // -1 the vertices of cells where the function has been defined
            // by the wavefront propagation algorithm
            wGrid[iV1] = -1.0f;
            src.push_back(iV1);
             }
        } // while(dst.size()>0)
        
    } // while(source.size()>0)
    
    // create output surface
    computeIsosurface(center,size,depth,scale,isCube,fGrid);
    
    // we no longer need the point partition
    _deletePartition();
    
    std::cerr << "}" << endl;
}

//////////////////////////////////////////////////////////////////////

void SceneGraphProcessor::computeIsosurface
(const Vec3f &center, const Vec3f &size, const int depth,
 const float scale, const bool cube, vector<float> &fGrid){
    cerr<< "SceneGraphProcessor::computeIsosurface() {" <<endl;
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
//        normal.clear();
//        coordIfs.clear();
//        coordIndexIfs.clear();
    
    // 4) if the bounding box is empty (size.x==size.y==size.z==0) or scale<=0
    // throw an StrException
    if((size.x==0 && size.y==0 && size.z==0)||scale<=0) throw new StrException("Has no bounding box");
    // 5) compute the coordinates of the 8 vertices of the scaled bounding box
//        _wrl.updateBBox(cube);
    Vec3f bbox_center = _wrl.getBBoxCenter();
    Vec3f bbox_size = _wrl.getBBoxSize();
    Vec3f min(bbox_center.x-0.5*scale*bbox_size.x, bbox_center.y-0.5*scale*bbox_size.y, bbox_center.z-0.5*scale*bbox_size.z);
    Vec3f max(bbox_center.x+0.5*scale*bbox_size.x, bbox_center.y+0.5*scale*bbox_size.y, bbox_center.z+0.5*scale*bbox_size.z);
    
    // 6) create a partition of the points as an array of linked lists
    Vec4f fCell;
    vector<float> coordPoints_cell;
    vector<float> normalPoints_cell;
    
    _createPartition(min,max,depth,coordPoints);
    Vec3f minCell, maxCell;
    int N = (int)pow(2, depth);
    int i,j,k,iV,iVB[8],iE[12];
    float F[8];
    bool b[8];
    Vec3f v[8];
    
    SimpleGraphMap map = SimpleGraphMap(N);
    Vec4f scalar;
//    scalar.x = 0.0f;
//    scalar.y = 0.0f;
//    scalar.z = 0.0f;
//    scalar.w = 0.0f;
    for(int cell_i=0; cell_i<N; cell_i++){
        for(int cell_j=0; cell_j<N; cell_j++){
            for(int cell_k=0; cell_k<N; cell_k++){
                
                int iCell = cell_k+N*(cell_j+N*cell_i);
//                if(_first[iCell]>=0){
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
                meanFit(coordPoints_cell, normalPoints_cell, minCell, maxCell, scalar);
//                }
                
//                eigenFit(coordPoints_cell, minCell, maxCell, scalar);
                
                
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

                for(int i=0;i<8;i++) {
                    // determine the grid vertex index iV of the corner
//                    int coord_x = (N)*(x-min.x)/(max.x-min.x);
//                    int coord_y = (N)*(y-min.y)/(max.y-min.y);
//                    int coord_k = (N)*(z-min.z)/(max.z-min.z);
//                    iV = coord_x + (N+1)*(coord_y+(N+1)*coord_k);
                    if(i==0) iV = cell_k + (N+1)*(cell_j+(N+1)*cell_i);
                    if(i==1) iV = cell_k + (N+1)*(cell_j+(N+1)*cell_i) + 1;
                    if(i==2) iV = cell_k + (N+1)*(cell_j+1+(N+1)*cell_i);
                    if(i==3) iV = cell_k + (N+1)*(cell_j+1+(N+1)*cell_i) + 1;
                    if(i==4) iV = cell_k + (N+1)*(cell_j+(N+1)*(cell_i+1));
                    if(i==5) iV = cell_k + (N+1)*(cell_j+(N+1)*(cell_i+1)) + 1;
                    if(i==6) iV = cell_k + (N+1)*(cell_j+1+(N+1)*(cell_i+1));
                    if(i==7) iV = cell_k + (N+1)*(cell_j+1+(N+1)*(cell_i+1)) + 1;
                    iVB[i] = iV;
                    F[i] = fGrid[iV];
                    b[i] = F[i]<0.0f;
                }
                //
                const int (*edge)[2] = IsoSurf::getEdgeTable();
                float tj,tk;
                for(i=0;i<12;i++) {
                    iV   = -1;
                    j    = edge[i][0];
                    k    = edge[i][1];
                    if(b[j]!=b[k]) {
                        // isvertex index
                        iV = map.get(iVB[j], iVB[k]);
                        if(iV<0){//need to create a new vertex
                            iV = (int)((coordIfs.size())/3);
                            // isovertex coordinates
                            tk = F[j]/(F[j]-F[k]);
                            tj = F[k]/(F[k]-F[j]);
                            float x  = tj*cells[j].x+tk*cells[k].x;
                            float y  = tj*cells[j].y+tk*cells[k].y;
                            float z  = tj*cells[j].z+tk*cells[k].z;
                            coordIfs.push_back(x);
                            coordIfs.push_back(y);
                            coordIfs.push_back(z);
                            map.insert(iVB[j], iVB[k], iV);
                        }
                    }
                    iE[i] = iV;
                }
                //
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
    map.clear();
    _deletePartition();
    cerr << "}" << endl;
}

//////////////////////////////////////////////////////////////////////
void SceneGraphProcessor::optimalCGHard
(const Vec3f& center, const Vec3f& size,
 const int depth, const float scale, const bool cube,
 vector<float>& fGrid /* input & output */) {
    
    cerr << "SceneGraphProcessor::optimalCGHard() {" << endl;
    
    if(size.x<=0.0f || size.y<=0.0f || size.z<=0.0f || scale<=0.0f) return;
    
    // 1) get the scene graph node named "POINTS"
    // IndexedFaceSet* points = ...
    Shape* points = (Shape*)0;
    int length = _wrl.getChildren().size();
    for(int index =0; index<length; index++){
        Node* node = _wrl.getChildren().at(index);
        if(node->isShape() && node->nameEquals("POINTS")){
            points = (Shape*)node;
            if(((IndexedFaceSet*)points->getGeometry())->getCoord().size()==0 || ((IndexedFaceSet*)points->getGeometry())->getNormal().size()==0) throw new StrException("Invalid Points");
        }
    }
    
    // 2) if there is no such node return without doing anything
    if(points==NULL) return;
    
    // 3) if the node is found but it is empty, or it does not have
    // normals per vertex, also return without doing anything
    if(points->getGeometry()==NULL||points->getAppearance()==NULL) return;
    if(((IndexedFaceSet*)points->getGeometry())->getNormalBinding()!=IndexedFaceSet::PB_PER_VERTEX) return;
    
    // 4) get the coord and normal vectors from the points node
    // vector<float>& coordPoints = ...
    // vector<float>& normalPoints = ...
    // get from the POINTS IndexedFaceSet
    vector<float>& coordPoints = ((IndexedFaceSet*)points->getGeometry())->getCoord();
    vector<float>& normalPoints = ((IndexedFaceSet*)points->getGeometry())->getNormal();
    
    // 5) from the center, size, and scale arguments, compute the min &
    // max corners of the bounding box
    Vec3f bbox_center = _wrl.getBBoxCenter();
    Vec3f bbox_size = _wrl.getBBoxSize();
    
    Vec3f min(bbox_center.x-0.5*scale*bbox_size.x, bbox_center.y-0.5*scale*bbox_size.y, bbox_center.z-0.5*scale*bbox_size.z);
    Vec3f max(bbox_center.x+0.5*scale*bbox_size.x, bbox_center.y+0.5*scale*bbox_size.y, bbox_center.z+0.5*scale*bbox_size.z);
    
    // 6) create a partition of the points as an array of linked lists
    _createPartition(min,max,depth,coordPoints);
    
    // 7) determine the total number of grid vertices as a function of
    // _nGrid
    // int nGridVertices = ...
    int N = _nGrid;
    int nGridVertices = (N+1)*(N+1)*(N+1);
    
    // 7) initialize fGrid with zeros
    fGrid.clear();
    fGrid.insert(fGrid.end(),nGridVertices,0.0f);
    // 8) create a temporary array of the same size to accumulate weights
    vector<float> wGrid;
    wGrid.insert(wGrid.end(),nGridVertices,0.0f);
    
    // 9) allocate arrays to do the local linear fit
    Vec4f fCell;
    Vec3f minCell,maxCell;
    vector<float> coordCell;
    vector<float> normalCell;
    
    // 10) accumulate grid vertex funtion values
    int iCell, iz, iy, ix, iPoint, nPoints;
    int nonEmptyCells = 0;
    vector<Vec3f> cells;
    Vec3f nCell;
    for(iCell=iz=0;iz<N;iz++) {
        minCell.z = (((float)(N-iz  ))*min.z+((float)(iz  ))*max.z)/((float)N);
        maxCell.z = (((float)(N-iz-1))*min.z+((float)(iz+1))*max.z)/((float)N);
        for(iy=0;iy<N;iy++) {
            minCell.y = (((float)(N-iy  ))*min.y+((float)(iy  ))*max.y)/((float)N);
            maxCell.y = (((float)(N-iy-1))*min.y+((float)(iy+1))*max.y)/((float)N);
            for(ix=0;ix<N;ix++,iCell++) {
                minCell.x = (((float)(N-ix  ))*min.x+((float)(ix  ))*max.x)/((float)N);
                maxCell.x = (((float)(N-ix-1))*min.x+((float)(ix+1))*max.x)/((float)N);
                
                if((iPoint=_first[iCell])>=0) { // cell iCell is not empty
                    nonEmptyCells++;
                    
                    // 11) copy coord and normal values of points in cell onto cell arrays
                    coordCell.clear();
                    normalCell.clear();
                    nCell.x=nCell.y=nCell.z;
                    for(nPoints=0;iPoint>=0;iPoint=_next[iPoint]) {
                        // ...
                        // count the number of points in the cell here
                        coordCell.push_back(coordPoints[iPoint*3]);
                        coordCell.push_back(coordPoints[iPoint*3+1]);
                        coordCell.push_back(coordPoints[iPoint*3+2]);
                        normalCell.push_back(normalPoints[iPoint*3]);
                        normalCell.push_back(normalPoints[iPoint*3+1]);
                        normalCell.push_back(normalPoints[iPoint*3+2]);
                    }
                    
                    // 12) fit a linear function to the points contained in the
                    // cell using the meanFit() method
                    meanFit(coordCell, normalCell, minCell, maxCell, fCell);
                    // 13) evaluate the local linear function at each of the
                    // cell's eight vertices, accumulate the values in the
                    // corresponding entries of the fGrid vector, and increment
                    // the corresponding entry of the weights vector wGrid by 1
                    int iV;
                    cells.clear();
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
                    for(int i=0;i<8;i++) {
                        // set (x,y,z) the the i=th corner coordinates
                        float x= cells[i].x;
                        float y = cells[i].y;
                        float z = cells[i].z;
                        // determine the grid vertex index iV of the corner
                        //                        int coord_x = (N)*(x-min.x)/(max.x-min.x);
                        //                        int coord_y = (N)*(y-min.y)/(max.y-min.y);
                        //                        int coord_k = (N)*(z-min.z)/(max.z-min.z);
                        //                        int iV = coord_x + (N+1)*(coord_y+(N+1)*coord_k);
                        if(i==0) iV = ix + (N+1)*(iy+(N+1)*iz);
                        if(i==1) iV = ix + (N+1)*(iy+(N+1)*iz) + 1;
                        if(i==2) iV = ix + (N+1)*(iy+1+(N+1)*iz);
                        if(i==3) iV = ix + (N+1)*(iy+1+(N+1)*iz) + 1;
                        if(i==4) iV = ix + (N+1)*(iy+(N+1)*(iz+1));
                        if(i==5) iV = ix + (N+1)*(iy+(N+1)*(iz+1)) + 1;
                        if(i==6) iV = ix + (N+1)*(iy+1+(N+1)*(iz+1));
                        if(i==7) iV = ix + (N+1)*(iy+1+(N+1)*(iz+1)) + 1;
                        fGrid[iV]= x*fCell.x+y*fCell.y+z*fCell.z+fCell.w;
                        wGrid[iV] += 1.0f;
                    }
                }
            }
        }
    }
    
    // 14) arrays needded to implement the wavefront propagation algorithm
    vector<int> src;
    vector<int> dst;
    int iV;
    // 15) normalize the fGrid values
    for(iV=0;iV<nGridVertices;iV++){
        if(wGrid[iV]>0.0f) { // only for vertices of occupied cells !
            fGrid[iV] /= wGrid[iV];
            // since the wGrid[iV] value is no longer needed, we will use it
            // to indicate which vertices have defined function values
            // (WGrid[iV]==-2), and which ones have undefined values
            // (wGrid[iV]==0)
            wGrid[iV] = -2.0f;
            // save the grid vertex indices of occupied cells in a list
            src.push_back(iV);
        }
    }
    
    // 16) make a list of constrained grid vertices (those which are
    // corners of occupied cells), and free grid vertices (all the
    // remaining ones).
    vector<int> iVConstrained;
    vector<int> iVFree;
    // ...
    for(iV=0; iV<nGridVertices; iV++){
        if(wGrid[iV]==-2.0f){
            iVConstrained.push_back(iV);
        }else iVFree.push_back(iV);
    }
    int n = (int)iVFree.size();
    
    // 17) iVConstrained can be regarded as a mapping which assigns a
    // grid vertex index to each constrained vertex; construct the
    // inverse of this mapping, i.e., a table that stores a constrained
    // vertex index for each grid vertex location; -1 is used to
    // indicate that the corresponding grid vertex is not (yet)
    // constrained
    vector<int> gridVertex;
    gridVertex.insert(gridVertex.end(),nGridVertices,-1);
    // ...
    for(int i=0; i<iVConstrained.size(); i++){
        gridVertex[iVConstrained[i]] = 1;
    }
    
    // 18) if all the grid vertices are constrained, return without doing anything
    if(n==0) return;
    
    // 19) Allocate data structures for the Eigen CG solver
    VectorXd X(n),B(n),D(n); // these vectors are not initialized
    B = VectorXd::Zero(n);
    SparseMatrix<double> A(n,n); // this matrix is implicitly initialized to 0's
    A.reserve(VectorXi::Constant(n,8)); // each grid vertex may have up to 8 neighbors
    // 20) fill the matrix A and the vector B
    // for each grid edge (jV,kV) {
    //   j = gridVertex[jV]
    //   k = gridVertex[jV]
    //   if(j>=0 && k>=0) {
    //     fill A(j,j), A(j,k), A(k,j), and A(k,k)
    //   } else if(j>=0) {
    //     fill A(j,j) and B(j)
    //   } else if(k>=0) {
    //     fill A(k,k) and B(k)
    //   }
    // }
    int kVs[3];
    std::vector<int>::iterator it;
    for(int iz=0; iz<=N; iz++){
//        cerr << "come to level: " << iz << endl;
        for(int iy=0; iy<=N; iy++){
            for(int ix=0; ix<=N; ix++){
                int jV = ix + (N+1)*(iy+(N+1)*iz);
                if(ix<N) kVs[0] = ix + (N+1)*(iy+(N+1)*iz) + 1;
                else kVs[0] = -1;
                if(iy<N) kVs[1] = ix + (N+1)*(iy+1+(N+1)*iz);
                else kVs[1] = -1;
                if(iz<N) kVs[2] = ix + (N+1)*(iy+(N+1)*(iz+1));
                else kVs[2] = -1;
                for(int i=0; i<3; i++){
                    if(kVs[i]>=0){
                        int kV = kVs[i];
                        if(gridVertex[jV]<0 && gridVertex[kV]<0){
                            it = find (iVFree.begin(), iVFree.end(), jV);
                            int j = distance(iVFree.begin(), it);
                            it = find(iVFree.begin(), iVFree.end(), kV);
                            int k = distance(iVFree.begin(), it);
                            A.coeffRef(j, j) += 1.0f;
                            A.coeffRef(j, k) -= 1.0f;
                            A.coeffRef(k, j) -= 1.0f;
                            A.coeffRef(k, k) += 1.0f;
                        }else if(gridVertex[jV]<0){
                            it = find (iVFree.begin(), iVFree.end(), jV);
                            int j = distance(iVFree.begin(), it);
                            A.coeffRef(j, j) += 1.0f;
                            B[j] += fGrid[kV];
                        }else if(gridVertex[kV]<0){
                            it = find(iVFree.begin(), iVFree.end(), kV);
                            int k = distance(iVFree.begin(), it);
                            A.coeffRef(k, k) += 1.0f;
                            B[k] += fGrid[jV];
                        }
                    }
                }
            }
        }
    }
    
    // 21) create an instance of the solver and decompose the matrix A
    ConjugateGradient<SparseMatrix<double> > solver;
    solver.compute(A);
    cerr << "     decompose A" << endl;
    if(solver.info()!=Success) {
        cerr << "    decomposition failed "<< endl;
    } else {

        // 22) fill x with initial guess
        cerr << "fill x with initial guess" << endl;
        for(int i=0;i<(int)iVFree.size();i++) {
            iV = iVFree[i];
            X(i) = fGrid[iV];
        }

        // 23) solve
        cerr << "solve" << endl;
        X = solver.solveWithGuess(B,X);

        // 24) transfer result back
        cerr << "transfer result" << endl;
        for(int i=0;i<(int)iVFree.size();i++) {
            iV = iVFree[i]; fGrid[iV] = (float)(X(i));
        }

        // 25) report number of iterations and estimated error
        cerr << "    " << solver.iterations() << " iterations"<< endl;
        cerr << "    " << solver.error() << " estimated error"<< endl;
    }
    
    // 26) update the output surface
    computeIsosurface(center,size,depth,scale,cube,fGrid);
    
    // 27) we no longer need the point partition
    _deletePartition();
    
    cerr << "}" << endl;
}
//////////////////////////////////////////////////////////////////////
void SceneGraphProcessor::optimalCGSoft
(const Vec3f& center, const Vec3f& size,
 const int depth, const float scale, const bool cube,
 vector<float>& fGrid /* input & output */) {
    
    cerr << "SceneGraphProcessor::optimalCGHard() {" << endl;
    
    // steps 1) to 15) same as in fitWatertight()
    if(size.x<=0.0f || size.y<=0.0f || size.z<=0.0f || scale<=0.0f) return;
    
    // 1) get the scene graph node named "POINTS"
    // IndexedFaceSet* points = ...
    Shape* points = (Shape*)0;
    int length = _wrl.getChildren().size();
    for(int index =0; index<length; index++){
        Node* node = _wrl.getChildren().at(index);
        if(node->isShape() && node->nameEquals("POINTS")){
            points = (Shape*)node;
            if(((IndexedFaceSet*)points->getGeometry())->getCoord().size()==0 || ((IndexedFaceSet*)points->getGeometry())->getNormal().size()==0) throw new StrException("Invalid Points");
        }
    }
    
    // 2) if there is no such node return without doing anything
    if(points==NULL) return;
    
    // 3) if the node is found but it is empty, or it does not have
    // normals per vertex, also return without doing anything
    if(points->getGeometry()==NULL||points->getAppearance()==NULL) return;
    if(((IndexedFaceSet*)points->getGeometry())->getNormalBinding()!=IndexedFaceSet::PB_PER_VERTEX) return;
    
    // 4) get the coord and normal vectors from the points node
    // vector<float>& coordPoints = ...
    // vector<float>& normalPoints = ...
    // get from the POINTS IndexedFaceSet
    vector<float>& coordPoints = ((IndexedFaceSet*)points->getGeometry())->getCoord();
    vector<float>& normalPoints = ((IndexedFaceSet*)points->getGeometry())->getNormal();
    
    // 5) from the center, size, and scale arguments, compute the min &
    // max corners of the bounding box
    Vec3f bbox_center = _wrl.getBBoxCenter();
    Vec3f bbox_size = _wrl.getBBoxSize();
    
    Vec3f min(bbox_center.x-0.5*scale*bbox_size.x, bbox_center.y-0.5*scale*bbox_size.y, bbox_center.z-0.5*scale*bbox_size.z);
    Vec3f max(bbox_center.x+0.5*scale*bbox_size.x, bbox_center.y+0.5*scale*bbox_size.y, bbox_center.z+0.5*scale*bbox_size.z);
    
    // 6) create a partition of the points as an array of linked lists
    _createPartition(min,max,depth,coordPoints);
    
    // 7) determine the total number of grid vertices as a function of
    // _nGrid
    // int nGridVertices = ...
    int N = _nGrid;
    int nGridVertices = (N+1)*(N+1)*(N+1);
    
    // 7) initialize fGrid with zeros
    fGrid.clear();
    fGrid.insert(fGrid.end(),nGridVertices,0.0f);
    // 8) create a temporary array of the same size to accumulate weights
    vector<float> wGrid;
    wGrid.insert(wGrid.end(),nGridVertices,0.0f);
    
    // 9) allocate arrays to do the local linear fit
    Vec4f fCell;
    Vec3f minCell,maxCell;
    vector<float> coordCell;
    vector<float> normalCell;
    
    // 10) accumulate grid vertex funtion values
    int iCell, iz, iy, ix, iPoint, nPoints;
    int nonEmptyCells = 0;
    vector<Vec3f> cells;
    Vec3f nCell;
    for(iCell=iz=0;iz<N;iz++) {
        minCell.z = (((float)(N-iz  ))*min.z+((float)(iz  ))*max.z)/((float)N);
        maxCell.z = (((float)(N-iz-1))*min.z+((float)(iz+1))*max.z)/((float)N);
        for(iy=0;iy<N;iy++) {
            minCell.y = (((float)(N-iy  ))*min.y+((float)(iy  ))*max.y)/((float)N);
            maxCell.y = (((float)(N-iy-1))*min.y+((float)(iy+1))*max.y)/((float)N);
            for(ix=0;ix<N;ix++,iCell++) {
                minCell.x = (((float)(N-ix  ))*min.x+((float)(ix  ))*max.x)/((float)N);
                maxCell.x = (((float)(N-ix-1))*min.x+((float)(ix+1))*max.x)/((float)N);
                
                if((iPoint=_first[iCell])>=0) { // cell iCell is not empty
                    nonEmptyCells++;
                    
                    // 11) copy coord and normal values of points in cell onto cell arrays
                    coordCell.clear();
                    normalCell.clear();
                    nCell.x=nCell.y=nCell.z;
                    for(nPoints=0;iPoint>=0;iPoint=_next[iPoint]) {
                        // ...
                        // count the number of points in the cell here
                        coordCell.push_back(coordPoints[iPoint*3]);
                        coordCell.push_back(coordPoints[iPoint*3+1]);
                        coordCell.push_back(coordPoints[iPoint*3+2]);
                        normalCell.push_back(normalPoints[iPoint*3]);
                        normalCell.push_back(normalPoints[iPoint*3+1]);
                        normalCell.push_back(normalPoints[iPoint*3+2]);
                    }
                    
                    // 12) fit a linear function to the points contained in the
                    // cell using the meanFit() method
                    meanFit(coordCell, normalCell, minCell, maxCell, fCell);
                    // 13) evaluate the local linear function at each of the
                    // cell's eight vertices, accumulate the values in the
                    // corresponding entries of the fGrid vector, and increment
                    // the corresponding entry of the weights vector wGrid by 1
                    int iV;
                    cells.clear();
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
                    for(int i=0;i<8;i++) {
                        // set (x,y,z) the the i=th corner coordinates
                        float x= cells[i].x;
                        float y = cells[i].y;
                        float z = cells[i].z;
                        // determine the grid vertex index iV of the corner
                        //                        int coord_x = (N)*(x-min.x)/(max.x-min.x);
                        //                        int coord_y = (N)*(y-min.y)/(max.y-min.y);
                        //                        int coord_k = (N)*(z-min.z)/(max.z-min.z);
                        //                        int iV = coord_x + (N+1)*(coord_y+(N+1)*coord_k);
                        if(i==0) iV = ix + (N+1)*(iy+(N+1)*iz);
                        if(i==1) iV = ix + (N+1)*(iy+(N+1)*iz) + 1;
                        if(i==2) iV = ix + (N+1)*(iy+1+(N+1)*iz);
                        if(i==3) iV = ix + (N+1)*(iy+1+(N+1)*iz) + 1;
                        if(i==4) iV = ix + (N+1)*(iy+(N+1)*(iz+1));
                        if(i==5) iV = ix + (N+1)*(iy+(N+1)*(iz+1)) + 1;
                        if(i==6) iV = ix + (N+1)*(iy+1+(N+1)*(iz+1));
                        if(i==7) iV = ix + (N+1)*(iy+1+(N+1)*(iz+1)) + 1;
                        fGrid[iV]= x*fCell.x+y*fCell.y+z*fCell.z+fCell.w;
                        wGrid[iV] += 1.0f;
                    }
                }
            }
        }
    }
    
    // 14) arrays needded to implement the wavefront propagation algorithm
    vector<int> src;
    vector<int> dst;
    int iV;
    // 15) normalize the fGrid values
    for(iV=0;iV<nGridVertices;iV++){
        if(wGrid[iV]>0.0f) { // only for vertices of occupied cells !
            fGrid[iV] /= wGrid[iV];
            // since the wGrid[iV] value is no longer needed, we will use it
            // to indicate which vertices have defined function values
            // (WGrid[iV]==-2), and which ones have undefined values
            // (wGrid[iV]==0)
            wGrid[iV] = -2.0f;
            // save the grid vertex indices of occupied cells in a list
            src.push_back(iV);
        }
    }
    // 16) in this case all the grid vertices are free variables
    int n = nGridVertices;
    VectorXd X(n),B(n),D(n); // these vectors are not initialized
    B = VectorXd::Zero(n);
    
    SparseMatrix<double> A(n,n); // this matrix is implicitly initialized to 0's
    A.reserve(VectorXi::Constant(n,8)); // each grid vertex may have up to 8 neighbors
    
    // Data term
    
    // 17) for each vertex iV of an occupied cell
    //   fill A(iV,iV) and B(iV)
    for(iV=0; iV<n; iV++){
        if(wGrid[iV]==-2.0f){
            A.coeffRef(iV, iV) += 1.0f;
            B[iV] = fGrid[iV];
        }else{
            B[iV] = 0.0f;
        }
    }
    // Regularization term
    
    // 18) this parameter should be exposed in the user interface, but
    // let's keep it here for now
    double lambda = 0.05;
    
    // 19) fill the matrix A
    // for each grid edge (jV,kV) {
    //   fill A(j,j), A(j,k), A(k,j), and A(k,k)
    // }
    int kVs[3];
    for(int iz=0; iz<=N; iz++){
//        cerr << "come to level: " << iz << endl;
        for(int iy=0; iy<=N; iy++){
            for(int ix=0; ix<=N; ix++){
                int jV = ix + (N+1)*(iy+(N+1)*iz);
                if(ix<N) kVs[0] = ix + (N+1)*(iy+(N+1)*iz) + 1;
                else kVs[0] = -1;
                if(iy<N) kVs[1] = ix + (N+1)*(iy+1+(N+1)*iz);
                else kVs[1] = -1;
                if(iz<N) kVs[2] = ix + (N+1)*(iy+(N+1)*(iz+1));
                else kVs[2] = -1;
                for(int i=0; i<3; i++){
                    if(kVs[i]>=0){
                        int kV = kVs[i];
                        A.coeffRef(jV, jV) += lambda;
                        A.coeffRef(jV, kV) -= lambda;
                        A.coeffRef(kV, jV) -= lambda;
                        A.coeffRef(kV, kV) += lambda;
                        
                    }
                }
            }
        }
    }
    
    // 20) create an instance of the solver and decompose the matrix A
    ConjugateGradient<SparseMatrix<double> > cg;
    cg.compute(A);
    if(cg.info()!=Success) {
        cerr << "    decomposition failed "<< endl;
    } else {

        // 21) fill x with initial guess
        for(iV=0;iV<n;iV++)
        X(iV) = fGrid[iV];

        // 22) solve
        X = cg.solveWithGuess(B,X);

        // 23) transfer result back
        for(iV=0;iV<n;iV++)
        fGrid[iV] = (float)(X(iV));

        // 24) report number of iterations and estimated error
        cerr << "    " << cg.iterations() << " iterations"<< endl;
        cerr << "    " << cg.error() << " estimated error"<< endl;
    }
    
    // 25) update the output surface
    computeIsosurface(center,size,depth,scale,cube,fGrid);
    
    // 26) we no longer need the point partition
    _deletePartition();
    
    cerr << "}" << endl;
}

//////////////////////////////////////////////////////////////////////
void SceneGraphProcessor::optimalJacobi
(const Vec3f& center, const Vec3f& size,
 const int depth, const float scale, const bool cube,
 vector<float>& fGrid /* input & output */) {
    
    cerr << "SceneGraphProcessor::optimalJacobi() {" << endl;
    
    if(size.x<=0.0f || size.y<=0.0f || size.z<=0.0f || scale<=0.0f) return;
    
    // steps 1) to 7) same as in fitWatertight()
    
    // 1) get the scene graph node named "POINTS"
    // IndexedFaceSet* points = ...
    Shape* points = (Shape*)0;
    int length = _wrl.getChildren().size();
    for(int index =0; index<length; index++){
        Node* node = _wrl.getChildren().at(index);
        if(node->isShape() && node->nameEquals("POINTS")){
            points = (Shape*)node;
            if(((IndexedFaceSet*)points->getGeometry())->getCoord().size()==0 || ((IndexedFaceSet*)points->getGeometry())->getNormal().size()==0) throw new StrException("Invalid Points");
        }
    }
    
    // 2) if there is no such node return without doing anything
    if(points==NULL) return;
    
    // 3) if the node is found but it is empty, or it does not have
    // normals per vertex, also return without doing anything
    if(points->getGeometry()==NULL||points->getAppearance()==NULL) return;
    if(((IndexedFaceSet*)points->getGeometry())->getNormalBinding()!=IndexedFaceSet::PB_PER_VERTEX) return;
    
    // 4) get the coord and normal vectors from the points node
    // vector<float>& coordPoints = ...
    // vector<float>& normalPoints = ...
    // get from the POINTS IndexedFaceSet
    vector<float>& coordPoints = ((IndexedFaceSet*)points->getGeometry())->getCoord();
    vector<float>& normalPoints = ((IndexedFaceSet*)points->getGeometry())->getNormal();
    
    // 5) from the center, size, and scale arguments, compute the min &
    // max corners of the bounding box
    Vec3f bbox_center = _wrl.getBBoxCenter();
    Vec3f bbox_size = _wrl.getBBoxSize();
//    float temp = 0.0f;
//    if(cube){
//        if(bbox_size.x>temp){
//            temp = bbox_size.x;
//        }
//        if(bbox_size.y>temp) temp = bbox_size.y;
//        if(bbox_size.z>temp) temp = bbox_size.z;
//        bbox_size.x = temp; bbox_size.y=temp; bbox_size.z=temp;
//    }
    
    Vec3f min(bbox_center.x-0.5*scale*bbox_size.x, bbox_center.y-0.5*scale*bbox_size.y, bbox_center.z-0.5*scale*bbox_size.z);
    Vec3f max(bbox_center.x+0.5*scale*bbox_size.x, bbox_center.y+0.5*scale*bbox_size.y, bbox_center.z+0.5*scale*bbox_size.z);
    
    // 6) create a partition of the points as an array of linked lists
    _createPartition(min,max,depth,coordPoints);
    
    // 7) determine the total number of grid vertices as a function of
    // _nGrid
    // int nGridVertices = ...
    int N = _nGrid;
    int nGridVertices = (N+1)*(N+1)*(N+1);
    
//    fGrid.clear();
//    fGrid.insert(fGrid.end(),nGridVertices,0.0f);
//    // 8) create a temporary array of the same size to accumulate weights
//    vector<float> wGrid;
//    wGrid.insert(wGrid.end(),nGridVertices,0.0f);

    int n = nGridVertices;
    
    // 8) these parameters should be exposed in the user interface, but
    // we will keep them here for now
    int    nIter  = 20;
    float  lambda = 0.10f;
    float  mu     = 0.5f;
    
    // 9) allocate arrays for the function values, the displacements,
    // and the weights; we need a separate array for the function
    // values, because fGrid contains the input function values which
    // are needed to compute the displacements; when we finish we
    // replace the fGrid values by the f values and return
    vector<float> f;
    vector<float> df;
    vector<float> wf;
    
    float fErr,wErr;
    
    // 10) initialize the function values using the input values
    f.insert(f.end(),fGrid.begin(),fGrid.end());
    
    // 11) iterate nIter times
    for(int iIter=0;iIter<nIter;iIter++) {
        df.clear();
        // 12) zero accumulators df and wf
        df.insert(df.end(), n, 0.0f);
        // Data term
        wf.clear();
        wf.insert(wf.end(), n, 0.0f);
        
        // 13) for each grid vertex iV of an occupied cell accumulate
        // (fGrid[iV]-f[iV]) in the corresponding displacement, and
        // increment the corresponding weight
        for(int iV=0; iV<n; iV++){
            if(fGrid[iV] != 0){
                df[iV] += (fGrid[iV]-f[iV]);
                wf[iV] += 1.0f;
            }
        }
        
        // Regularization term
        
        // 14) accumulate Laplacian
        // for each grid edge (jV,kV) {
        //   - accumulate lambda*(f[kV]-f[jV]) in df[jV] and increment the
        //     corresponding weight
        //   - accumulate lambda*(f[jV]-f[kV]) in df[kV] and increment the
        //     corresponding weight
        // }
        int kVs[3];
        for(int iz=0; iz<=N; iz++){
            for(int iy=0; iy<=N; iy++){
                for(int ix=0; ix<=N; ix++){
                    int jV = ix + (N+1)*(iy+(N+1)*iz);
                    if(ix<N) kVs[0] = ix + (N+1)*(iy+(N+1)*iz) + 1;
                    else kVs[0] = -1;
                    if(iy<N) kVs[1] = ix + (N+1)*(iy+1+(N+1)*iz);
                    else kVs[1] = -1;
                    if(iz<N) kVs[2] = ix + (N+1)*(iy+(N+1)*(iz+1));
                    else kVs[2] = -1;
                    for(int i=0; i<3; i++){
                        if(kVs[i]>=0){
                            int kV = kVs[i];
                            df[jV] += lambda*(f[kV]-f[jV]);
                            wf[jV] += lambda;
                            df[kV] += lambda*(f[jV]-f[kV]);
                            wf[kV] += lambda;
                        }
                    }
                }
            }
        }
        // 15) normalize the displacements
        for(int iV=0;iV<n;iV++)
            df[iV] /= wf[iV];
//
        // 16) update the function values
        for(int iV=0;iV<n;iV++)
            f[iV] += mu*df[iV];
        
        // 17) measure and report the error
        // ...
        cerr << "    err = " << fErr << endl;
    }
    
    // 18) save result; fGrid becomes the output
    fGrid.clear();
    fGrid.insert(fGrid.end(),f.begin(),f.end());
    
    // 19) update the output surface
    computeIsosurface(center,size,depth,scale,cube,fGrid);
    
    // 20) we no longer need the point partition
    _deletePartition();
    
    cerr << "}" << endl;
}

//////////////////////////////////////////////////////////////////////
void SceneGraphProcessor::multiGridFiner
(const Vec3f& center, const Vec3f& size,
 const int depth, const float scale, const bool cube,
 vector<float>& fGridIn /* input & output */) {
    if(depth<10) {
        
        int nGridIn         = 1<<depth;
        // int nGridInVertices = (nGridIn+1)*(nGridIn+1)*(nGridIn+1);
        int nGridOut         = 1<<(depth+1);
        int nGridOutVertices = (nGridOut+1)*(nGridOut+1)*(nGridOut+1);
        
        // 1) allocate array of output function values and initialize to 0
        vector<float> fGridOut;
        fGridOut.insert(fGridOut.end(),nGridOutVertices,0.0f);
        
        // 2) copy each input vertex value onto corresponding output vertex value
        for(int iV=0; iV<fGridIn.size(); iV++){
            int iz = iV/((nGridIn+1)*(nGridIn+1));
            int iy = (iV-iz*(nGridIn+1)*(nGridIn+1))/(nGridIn+1);
            int ix = iV-iz*(nGridIn+1)*(nGridIn+1) - iy*(nGridIn+1);
            int new_iV = ix*2 + 2*(nGridOut+1)*(iy+ (nGridOut+1)*iz);
            fGridOut[new_iV] = fGridIn[iV];
        }
        
        // 3) for each input grid edge, compute the midpoint output vertex
        // value as the average of the two ends input vertex values
        int kV, mid;
        for(int iz=0; iz<=nGridIn; iz++){
            for(int iy=0; iy<=nGridIn; iy++){
                for(int ix=0; ix<=nGridIn; ix++){
                    int jV = ix + (nGridIn+1)*(iy+(nGridIn+1)*iz);
                    if(ix<nGridIn) {
                        kV = ix + (nGridIn+1)*(iy+(nGridIn+1)*iz) + 1;
                        mid = ix*2 + (nGridOut+1)*(2*iy+2*(nGridOut+1)*iz) + 1;
                        fGridOut[mid] = (fGridIn[jV]+fGridIn[kV])/2;
                    }
                    if(iy<nGridIn) {
                        kV = ix + (nGridIn+1)*(iy+1+(nGridIn+1)*iz);
                        mid = ix*2 + (nGridOut+1)*(2*iy+1+2*(nGridOut+1)*iz);
                        fGridOut[mid] = (fGridIn[jV]+fGridIn[kV])/2;
                    }
                    if(iz<nGridIn){
                        kV = ix + (nGridIn+1)*(iy+(nGridIn+1)*(iz+1));
                        mid = ix*2 + (nGridOut+1)*(2*iy+(nGridOut+1)*(2*iz+1));
                        fGridOut[mid] = (fGridIn[jV]+fGridIn[kV])/2;
                    }
                }
            }
        }
        
        // 4) for each input grid face, compute the face center output
        // vertex value as the average of the four corner input vertex
        // values
        for(int iz=0; iz<=nGridIn; iz++){
            for(int iy=0; iy<=nGridIn; iy++){
                for(int ix=0; ix<=nGridIn; ix++){
                    int iV0 = ix + (nGridIn+1)*(iy+(nGridIn+1)*iz);
                    int iV1 = ix + (nGridIn+1)*(iy+(nGridIn+1)*iz) + 1;
                    int iV2 = ix + (nGridIn+1)*(iy+1+(nGridIn+1)*iz);
                    int iV3 = ix + (nGridIn+1)*(iy+1+(nGridIn+1)*iz) + 1;
                    int iV4 = ix + (nGridIn+1)*(iy+(nGridIn+1)*(iz+1));
                    int iV5 = ix + (nGridIn+1)*(iy+(nGridIn+1)*(iz+1)) + 1;
                    int iV6 = ix + (nGridIn+1)*(iy+1+(nGridIn+1)*(iz+1));
                    int iV7 = ix + (nGridIn+1)*(iy+1+(nGridIn+1)*(iz+1)) + 1;
                    if(ix<nGridIn && iy<nGridIn){
                        int mid_face0 = ix*2 + (nGridOut+1)*(2*iy+1+2*(nGridOut+1)*iz) + 1;
                        fGridOut[mid_face0] = (fGridIn[iV0] + fGridIn[iV1] + fGridIn[iV2] + fGridIn[iV3])/4;
                    }
                    if(ix<nGridIn && iz<nGridIn){
                        int mid_face1 = ix*2 + (nGridOut+1)*(2*iy+(nGridOut+1)*(2*iz+1)) + 1;
                        fGridOut[mid_face1] = (fGridIn[iV0] + fGridIn[iV1] + fGridIn[iV4] + fGridIn[iV5])/4;
                    }
                    if(iy<nGridIn && iz<nGridIn){
                        int mid_face2 = ix*2 + (nGridOut+1)*(2*iy+(nGridOut+1)*(2*iz+1)) + (nGridOut+1);
                        fGridOut[mid_face2] = (fGridIn[iV0] + fGridIn[iV2] + fGridIn[iV4] + fGridIn[iV6])/4;
                    }
                    if(ix<nGridIn && iy<nGridIn && iz<nGridIn){
                        int center = ix*2 + (nGridOut+1)*(2*iy+(nGridOut+1)*(2*iz+1)) + (nGridOut+1) + 1;
                        fGridOut[center] = (fGridIn[iV0] + fGridIn[iV1] + fGridIn[iV2] + fGridIn[iV3] +
                                            fGridIn[iV4] + fGridIn[iV5] + fGridIn[iV6] + fGridIn[iV7])/8;
                    }
                }
            }
        }
        
        
        // 5) for each input grid face, compute the face center output
        // vertex value as the average of the four corner input vertex
        // values
        
        // 6) create output surface
        computeIsosurface(center,size,depth+1,scale,cube,fGridOut);
        
        // 7) interchange fGrid arrays
        fGridIn.swap(fGridOut);
    }
}

//////////////////////////////////////////////////////////////////////
void SceneGraphProcessor::multiGridCoarser
(const Vec3f& center, const Vec3f& size,
 const int depth, const float scale, const bool cube,
 vector<float>& fGridIn /* input & output */) {
    if(depth>1) {
        
        int nGridIn         = 1<<depth;
        // int nGridInVertices = (nGridIn+1)*(nGridIn+1)*(nGridIn+1);
        int nGridOut         = 1<<(depth-1);
        int nGridOutVertices = (nGridOut+1)*(nGridOut+1)*(nGridOut+1);
        
        // 1) allocate array of output function values and initialize to 0
        vector<float> fGridOut;
        fGridOut.insert(fGridOut.end(),nGridOutVertices,0.0f);
        
        // 2) copy each input vertex value onto corresponding output
        // vertex value (subsampling)
        for(int iz=0; iz<=nGridIn; iz=iz+2){
            for(int iy=0; iy<=nGridIn; iy=iy+2){
                for(int ix=0; ix<=nGridIn; ix=ix+2){
                    int iV = ix +(nGridIn+1)*(iy+(nGridIn+1)*iz);
                    int new_iV = ix/2 + (nGridOut+1)*(iy/2+ (nGridOut+1)*iz/2);
                    fGridOut[new_iV] = fGridIn[iV];
                }
            }
        }
//        for(int iV=0; iV<fGridIn.size(); iV++){
//            int iz = iV/((nGridIn+1)*(nGridIn+1));
//            int iy = (iV-iz*(nGridIn+1)*(nGridIn+1))/(nGridIn+1);
//            int ix = iV-iz*(nGridIn+1)*(nGridIn+1) - iy*(nGridIn+1);
//            int new_iV = ix/2 + (nGridOut+1)*(iy/2+ (nGridOut+1)*iz/2);
//            if(fGridOut[new_iV]==0.0f)
//                fGridOut[new_iV] = fGridIn[iV];
//        }
        
        // 3) create output surface
        computeIsosurface(center,size,depth-1,scale,cube,fGridOut);
        
        // 4) interchange fGrid arrays
        fGridIn.swap(fGridOut);
    }
}

