#include <float.h>
#include <assert.h>
#include "meshEdit.h"
#include "mutablePriorityQueue.h"
#include "error_dialog.h"

namespace CS248 {

VertexIter HalfedgeMesh::splitEdge(EdgeIter e0) {
  // TODO: (meshEdit)
  // This method should split the given edge and return an iterator to the
  // newly inserted vertex. The halfedge of this vertex should point along
  // the edge that was split, rather than the new edges.

  // TODO: handle edge cases https://piazza.com/class/k4xhjytl1d94tl?cid=217
  if (!e0->isBoundary()) {

    // PHASE I: Collect relevant elements

    // HALFEDGES
    HalfedgeIter h0 = e0->halfedge();
    HalfedgeIter h1 = h0->next();
    HalfedgeIter h2 = h1->next();
    HalfedgeIter h3 = h0->twin();
    HalfedgeIter h4 = h3->next();
    HalfedgeIter h5 = h4->next();
    HalfedgeIter h6 = h1->twin();
    HalfedgeIter h7 = h2->twin();
    HalfedgeIter h8 = h4->twin();
    HalfedgeIter h9 = h5->twin();

    // check to make sure they are triangles
    if (h2->next() != h0 || h5->next() != h3) {
      showError("Cannot split edges of non-triangular faces.");
      return verticesBegin();
    }

    // VERTICES
    VertexIter v0 = h0->vertex();
    VertexIter v1 = h1->vertex();
    VertexIter v2 = h2->vertex();
    VertexIter v3 = h5->vertex();

    // EDGES
    // e0 passed in
    EdgeIter e1 = h1->edge();
    EdgeIter e2 = h2->edge();
    EdgeIter e3 = h4->edge();
    EdgeIter e4 = h5->edge();

    // FACES
    FaceIter f0 = h0->face();
    FaceIter f1 = h3->face();


    // PHASE II: Allocate new elements

    // HALFEDGES
    HalfedgeIter h10 = newHalfedge();
    HalfedgeIter h11 = newHalfedge();
    HalfedgeIter h12 = newHalfedge();
    HalfedgeIter h13 = newHalfedge();
    HalfedgeIter h14 = newHalfedge();
    HalfedgeIter h15 = newHalfedge();

    // VERTICES
    VertexIter v4 = newVertex();

    // EDGES
    EdgeIter e5 = newEdge();
    EdgeIter e6 = newEdge();
    EdgeIter e7 = newEdge();

    // FACES
    FaceIter f2 = newFace();
    FaceIter f3 = newFace();


    // PHASE III: Reassign Elements

    // HALFEDGES
    #pragma region halfedge assign

    h0->next() = h10;
    h0->twin() = h3;
    h0->vertex() = v0;
    h0->edge() = e0;
    h0->face() = f0;
    h1->next() = h11;
    h1->twin() = h6;
    h1->vertex() = v1;
    h1->edge() = e1;
    h1->face() = f2;
    h2->next() = h0;
    h2->twin() = h7;
    h2->vertex() = v2;
    h2->edge() = e2;
    h2->face() = f0;
    h3->next() = h4;
    h3->twin() = h0;
    h3->vertex() = v4;
    h3->edge() = e0;
    h3->face() = f1;
    h4->next() = h12;
    h4->twin() = h8;
    h4->vertex() = v0;
    h4->edge() = e3;
    h4->face() = f1;
    h5->next() = h15;
    h5->twin() = h9;
    h5->vertex() = v3;
    h5->edge() = e4;
    h5->face() = f3;

    // outside
    h6->next() = h6->next();
    h6->twin() = h1;
    h6->vertex() = v2;
    h6->edge() = e1;
    h6->face() = h6->face();
    h7->next() = h7->next();
    h7->twin() = h2;
    h7->vertex() = v0;
    h7->edge() = e2;
    h7->face() = h7->face();
    h8->next() = h8->next();
    h8->twin() = h4;
    h8->vertex() = v3;
    h8->edge() = e3;
    h8->face() = h8->face();
    h9->next() = h9->next();
    h9->twin() = h5;
    h9->vertex() = v1;
    h9->edge() = e4;
    h9->face() = h9->face();

    // new
    h10->next() = h2;
    h10->twin() = h11;
    h10->vertex() = v4;
    h10->edge() = e6;
    h10->face() = f0;
    h11->next() = h14;
    h11->twin() = h10;
    h11->vertex() = v2;
    h11->edge() = e6;
    h11->face() = f2;
    h12->next() = h3;
    h12->twin() = h13;
    h12->vertex() = v3;
    h12->edge() = e7;
    h12->face() = f1;
    h13->next() = h5;
    h13->twin() = h12;
    h13->vertex() = v4;
    h13->edge() = e7;
    h13->face() = f3;
    h14->next() = h1;
    h14->twin() = h15;
    h14->vertex() = v4;
    h14->edge() = e5;
    h14->face() = f2;
    h15->next() = h13;
    h15->twin() = h14;
    h15->vertex() = v1;
    h15->edge() = e5;
    h15->face() = f3;

    #pragma endregion


    // VERTICES
    v0->halfedge() = h0;
    v1->halfedge() = h1;
    v2->halfedge() = h2;
    v3->halfedge() = h5;
    v4->halfedge() = h14;

    // position of new vertices
    v4->position = (v0->position + v1->position) / 2.0f;

    // EDGES
    e0->halfedge() = h0;
    e1->halfedge() = h1;
    e2->halfedge() = h2;
    e3->halfedge() = h4;
    e4->halfedge() = h5;
    e5->halfedge() = h14;
    e6->halfedge() = h11;
    e7->halfedge() = h13;

    // FACES
    f0->halfedge() = h0;
    f1->halfedge() = h4;
    f2->halfedge() = h1;
    f3->halfedge() = h5;

    // PHASE IV: Delete unused elements

    // nothing to delete!
    RunAllTestsForEntireMesh(this);

    return v4;
  }
  else {
    // e0 is a boundary edge, need to only split one triangle

    // PHASE I: Collect relevant elements
    //cout << "boundary split" << endl;
    // HALFEDGES
    HalfedgeIter h0 = e0->halfedge();
    if (h0->isBoundary()) {
      // wrong triangle, twin h0 to get the inside triangle
      //cout << "halfedge is boundary, flipping" << endl;
      h0 = h0->twin();
    }
    HalfedgeIter h1 = h0->next();
    HalfedgeIter h2 = h1->next();
    HalfedgeIter h3 = h0->twin();
    HalfedgeIter h4 = h1->twin();
    HalfedgeIter h5 = h2->twin();

    // check to make sure it's a triangle
    if (h2->next() != h0) {
      showError("Cannot split edges of non-triangular faces.");
      return verticesBegin();
    }

    // VERTICES
    VertexIter v0 = h0->vertex();
    VertexIter v1 = h1->vertex();
    VertexIter v2 = h2->vertex();

    // EDGES
    // e0 passed in
    EdgeIter e1 = h1->edge();
    EdgeIter e2 = h2->edge();

    // FACES
    FaceIter f0 = h0->face();


    // PHASE II: Allocate new elements

    // HALFEDGES
    HalfedgeIter h6 = newHalfedge();
    HalfedgeIter h7 = newHalfedge();
    HalfedgeIter h8 = newHalfedge();
    HalfedgeIter h9 = newHalfedge();

    // VERTICES
    VertexIter v3 = newVertex();

    // EDGES
    EdgeIter e3 = newEdge();
    EdgeIter e4 = newEdge();

    // FACES
    FaceIter f1 = newFace();


    // PHASE III: Reassign Elements

    // HALFEDGES
    h0->next() =   h6;
    h0->twin() =   h9;
    h0->vertex() = v0;
    h0->edge() =   e0;
    h0->face() =   f0;
    h1->next() =   h7;
    h1->twin() =   h4;
    h1->vertex() = v1;
    h1->edge() =   e1;
    h1->face() =   f1;
    h2->next() =   h0;
    h2->twin() =   h5;
    h2->vertex() = v2;
    h2->edge() =   e2;
    h2->face() =   f0;
    // outside
    h9->next() = h3->next();
    h9->twin() = h0;
    h9->vertex() = v3;
    h9->edge() = e0;
    h9->face() = h3->face();
    // do h9 before h3 to h3 sees old h3->next()
    h3->next() =   h9;
    h3->twin() =   h8;
    h3->vertex() = v1;
    h3->edge() =   e3;
    h3->face() =   h3->face();
    h4->next() =   h4->next();
    h4->twin() =   h1;
    h4->vertex() = v2;
    h4->edge() =   e1;
    h4->face() =   h4->face();
    h5->next() =   h5->next();
    h5->twin() =   h2;
    h5->vertex() = v0;
    h5->edge() =   e2;
    h5->face() =   h5->face();
    // new
    h6->next() =   h2;
    h6->twin() =   h7;
    h6->vertex() = v3;
    h6->edge() =   e4;
    h6->face() =   f0;
    h7->next() =   h8;
    h7->twin() =   h6;
    h7->vertex() = v2;
    h7->edge() =   e4;
    h7->face() =   f1;
    h8->next() =   h1;
    h8->twin() =   h3;
    h8->vertex() = v3;
    h8->edge() =   e3;
    h8->face() =   f1;


    // VERTICES
    v0->halfedge() = h0;
    v1->halfedge() = h1;
    v2->halfedge() = h2;
    v3->halfedge() = h8;

    // position of new vertices
    v3->position = (v0->position + v1->position) / 2.0f;

    // EDGES
    e0->halfedge() = h0;
    e1->halfedge() = h1;
    e2->halfedge() = h2;
    e3->halfedge() = h8;
    e4->halfedge() = h7;

    // FACES
    f0->halfedge() = h0;
    f1->halfedge() = h1;

    // PHASE IV: Delete unused elements

    // nothing to delete!

    RunAllTestsForEntireMesh(this);

    return v3;
  }
}

VertexIter HalfedgeMesh::collapseEdge(EdgeIter e) {
  // *** Extra Credit ***
  // TODO: (meshEdit)
  // This method should collapse the given edge and return an iterator to
  // the new vertex created by the collapse.

  showError("collapseEdge() not implemented.");
  return VertexIter();
}

VertexIter HalfedgeMesh::collapseFace(FaceIter f) {
  // *** Extra Credit ***
  // TODO: (meshEdit)
  // This method should collapse the given face and return an iterator to
  // the new vertex created by the collapse.
  showError("collapseFace() not implemented.");
  return VertexIter();
}

FaceIter HalfedgeMesh::eraseVertex(VertexIter v) {
  // *** Extra Credit ***
  // TODO: (meshEdit)
  // This method should replace the given vertex and all its neighboring
  // edges and faces with a single face, returning the new face.

  return FaceIter();
}

FaceIter HalfedgeMesh::eraseEdge(EdgeIter e) {
  // *** Extra Credit ***
  // TODO: (meshEdit)
  // This method should erase the given edge and return an iterator to the
  // merged face.

  showError("eraseVertex() not implemented.");
  return FaceIter();
}

EdgeIter HalfedgeMesh::flipEdge(EdgeIter e0) {
  // TODO: (meshEdit)
  // This method should flip the given edge and return an iterator to the
  // flipped edge.

  // handle edge cases
  if (e0->isBoundary()) return e0;

  // PHASE I: Collect relevant elements

  // HALFEDGES
  HalfedgeIter h0 = e0->halfedge();
  HalfedgeIter h1 = h0->next();
  HalfedgeIter h2 = h1->next();
  HalfedgeIter h3 = h2;
  while (h3->next() != h0) h3 = h3->next();

  HalfedgeIter h4 = h0->twin();
  HalfedgeIter h5 = h4->next();
  HalfedgeIter h6 = h5->next();
  HalfedgeIter h7 = h6;
  while (h7->next() != h4) h7 = h7->next();

  HalfedgeIter h8 = h1->twin();
  HalfedgeIter h9 = h3->twin();
  HalfedgeIter h10 = h5->twin();
  HalfedgeIter h11 = h7->twin();

  // VERTICES
  VertexIter v0 = h0->vertex();
  VertexIter v1 = h1->vertex();
  VertexIter v2 = h2->vertex();
  VertexIter v3 = h3->vertex();
  VertexIter v4 = h6->vertex();
  VertexIter v5 = h7->vertex();

  // EDGES
  // e0 passed in
  EdgeIter e1 = h1->edge();
  EdgeIter e2 = h3->edge();
  EdgeIter e3 = h5->edge();
  EdgeIter e4 = h7->edge();

  // FACES
  FaceIter f0 = h0->face();
  FaceIter f1 = h4->face();

  // handle edge cases
  if (f0->isBoundary() ||
    f1->isBoundary())
    return e0;


  // PHASE II: Allocate new elements

  // nothing new to allocate!


  // PHASE III: Reassign Elements

  // HALFEDGES
  h0->next() = h2;
  h0->twin() = h4;
  h0->vertex() = v4;
  h0->edge() = e0;
  h0->face() = f0;
  h1->next() = h4;
  h1->twin() = h8;
  h1->vertex() = v1;
  h1->edge() = e1;
  h1->face() = f1;
  h3->next() = h5;
  h3->twin() = h9;
  h3->vertex() = v3;
  h3->edge() = e2;
  h3->face() = f0;
  h4->next() = h6;
  h4->twin() = h0;
  h4->vertex() = v2;
  h4->edge() = e0;
  h4->face() = f1;
  h5->next() = h0;
  h5->twin() = h10;
  h5->vertex() = v0;
  h5->edge() = e3;
  h5->face() = f0;
  h7->next() = h1;
  h7->twin() = h11;
  h7->vertex() = v5;
  h7->edge() = e4;
  h7->face() = f1;
  // outside
  h8->next() = h8->next();
  h8->twin() = h1;
  h8->vertex() = v2;
  h8->edge() = e1;
  h8->face() = h8->face();
  h9->next() = h9->next();
  h9->twin() = h3;
  h9->vertex() = v0;
  h9->edge() = e2;
  h9->face() = h9->face();
  h10->next() = h10->next();
  h10->twin() = h5;
  h10->vertex() = v4;
  h10->edge() = e3;
  h10->face() = h10->face();
  h11->next() = h11->next();
  h11->twin() = h7;
  h11->vertex() = v1;
  h11->edge() = e4;
  h11->face() = h11->face();

  // VERTICES
  v0->halfedge() = h5;
  v1->halfedge() = h1;
  v2->halfedge() = h4;
  v3->halfedge() = h3;
  v4->halfedge() = h0;
  v5->halfedge() = h7;

  // EDGES
  e0->halfedge() = h0;
  e1->halfedge() = h1;
  e2->halfedge() = h3;
  e3->halfedge() = h5;
  e4->halfedge() = h7;

  // FACES
  f0->halfedge() = h0;
  f1->halfedge() = h4;

  // PHASE IV: Delete unused elements

  // nothing to delete!

  RunAllTestsForEntireMesh(this);

  return e0;
}

void HalfedgeMesh::subdivideQuad(bool useCatmullClark) {
  // Unlike the local mesh operations (like bevel or edge flip), we will perform
  // subdivision by splitting *all* faces into quads "simultaneously."  Rather
  // than operating directly on the halfedge data structure (which as you've
  // seen
  // is quite difficult to maintain!) we are going to do something a bit nicer:
  //
  //    1. Create a raw list of vertex positions and faces (rather than a full-
  //       blown halfedge mesh).
  //
  //    2. Build a new halfedge mesh from these lists, replacing the old one.
  //
  // Sometimes rebuilding a data structure from scratch is simpler (and even
  // more
  // efficient) than incrementally modifying the existing one.  These steps are
  // detailed below.

  // TODO Step I: Compute the vertex positions for the subdivided mesh.  Here
  // we're
  // going to do something a little bit strange: since we will have one vertex
  // in
  // the subdivided mesh for each vertex, edge, and face in the original mesh,
  // we
  // can nicely store the new vertex *positions* as attributes on vertices,
  // edges,
  // and faces of the original mesh.  These positions can then be conveniently
  // copied into the new, subdivided mesh.
  // [See subroutines for actual "TODO"s]
  if (useCatmullClark) {
    computeCatmullClarkPositions();
  } else {
    computeLinearSubdivisionPositions();
  }

  // TODO Step II: Assign a unique index (starting at 0) to each vertex, edge,
  // and
  // face in the original mesh.  These indices will be the indices of the
  // vertices
  // in the new (subdivided mesh).  They do not have to be assigned in any
  // particular
  // order, so long as no index is shared by more than one mesh element, and the
  // total number of indices is equal to V+E+F, i.e., the total number of
  // vertices
  // plus edges plus faces in the original mesh.  Basically we just need a
  // one-to-one
  // mapping between original mesh elements and subdivided mesh vertices.
  // [See subroutine for actual "TODO"s]
  assignSubdivisionIndices();

  // TODO Step III: Build a list of quads in the new (subdivided) mesh, as
  // tuples of
  // the element indices defined above.  In other words, each new quad should be
  // of
  // the form (i,j,k,l), where i,j,k and l are four of the indices stored on our
  // original mesh elements.  Note that it is essential to get the orientation
  // right
  // here: (i,j,k,l) is not the same as (l,k,j,i).  Indices of new faces should
  // circulate in the same direction as old faces (think about the right-hand
  // rule).
  // [See subroutines for actual "TODO"s]
  vector<vector<Index> > subDFaces;
  vector<Vector3D> subDVertices;
  buildSubdivisionFaceList(subDFaces);
  buildSubdivisionVertexList(subDVertices);

  // TODO Step IV: Pass the list of vertices and quads to a routine that clears
  // the
  // internal data for this halfedge mesh, and builds new halfedge data from
  // scratch,
  // using the two lists.
  rebuild(subDFaces, subDVertices);

  RunAllTestsForEntireMesh(this);
}

/**
 * Compute new vertex positions for a mesh that splits each polygon
 * into quads (by inserting a vertex at the face midpoint and each
 * of the edge midpoints).  The new vertex positions will be stored
 * in the members Vertex::newPosition, Edge::newPosition, and
 * Face::newPosition.  The values of the positions are based on
 * simple linear interpolation, e.g., the edge midpoints and face
 * centroids.
 */
void HalfedgeMesh::computeLinearSubdivisionPositions() {
  // TODO For each vertex, assign Vertex::newPosition to
  // its original position, Vertex::position.
  for (VertexIter v = verticesBegin(); v != verticesEnd(); v++) {
    v->newPosition = v->position;
  }

  // TODO For each edge, assign the midpoint of the two original
  // positions to Edge::newPosition.
  for (EdgeIter e = edgesBegin(); e != edgesEnd(); e++) {
    VertexCIter v0 = e->halfedge()->vertex();
    VertexCIter v1 = e->halfedge()->twin()->vertex();
    e->newPosition = (v0->position + v1->position) / 2;
  }
  // TODO For each face, assign the centroid (i.e., arithmetic mean)
  // of the original vertex positions to Face::newPosition.  Note
  // that in general, NOT all faces will be triangles!
  for (FaceIter f = facesBegin(); f != facesEnd(); f++) {
    // collect surrounding vertex positions
    vector<Vector3D> vertexPositions;
    HalfedgeCIter hStart = f->halfedge();
    HalfedgeCIter hChange = hStart;
    do
    {
      vertexPositions.push_back(hChange->vertex()->position);
      hChange = hChange->next();
    } while (hChange != hStart);
    // assign position to mean
    Vector3D sum;
    for (Vector3D position : vertexPositions) sum += position;
    f->newPosition = sum / vertexPositions.size();
  }
}

/**
 * Compute new vertex positions for a mesh that splits each polygon
 * into quads (by inserting a vertex at the face midpoint and each
 * of the edge midpoints).  The new vertex positions will be stored
 * in the members Vertex::newPosition, Edge::newPosition, and
 * Face::newPosition.  The values of the positions are based on
 * the Catmull-Clark rules for subdivision.
 */
void HalfedgeMesh::computeCatmullClarkPositions() {
  // TODO The implementation for this routine should be
  // a lot like HalfedgeMesh::computeLinearSubdivisionPositions(),
  // except that the calculation of the positions themsevles is
  // slightly more involved, using the Catmull-Clark subdivision
  // rules. (These rules are outlined in the Developer Manual.)

  // TODO faces
  for (FaceIter f = facesBegin(); f != facesEnd(); f++) {
    // collect surrounding vertex positions
    vector<Vector3D> vertexPositions;
    HalfedgeCIter hStart = f->halfedge();
    HalfedgeCIter hChange = hStart;
    do
    {
      vertexPositions.push_back(hChange->vertex()->position);
      hChange = hChange->next();
    } while (hChange != hStart);
    // assign position to mean
    Vector3D sum;
    for (Vector3D position : vertexPositions) sum += position;
    f->newPosition = sum / vertexPositions.size();
  }
  // TODO edges
  for (EdgeIter e = edgesBegin(); e != edgesEnd(); e++) {
    if (!e->isBoundary()) {
      VertexCIter v0 = e->halfedge()->vertex();  // endpoint
      VertexCIter v1 = e->halfedge()->twin()->vertex(); // endpoint
      Vector3D faceP0 = e->halfedge()->face()->newPosition; // face
      Vector3D faceP1 = e->halfedge()->twin()->face()->newPosition; // face
      e->newPosition = (v0->position + v1->position + faceP0 + faceP1) / 4;
    }
    else {
      // boundary edge, just place at midpoint
      VertexCIter v0 = e->halfedge()->vertex();
      VertexCIter v1 = e->halfedge()->twin()->vertex();
      e->newPosition = (v0->position + v1->position) / 2;
    }
  }
  // TODO vertices
  for (VertexIter v = verticesBegin(); v != verticesEnd(); v++) {
    if (!v->isBoundary()) {
      // Q is the average of all new face position for faces containing v
      vector<Vector3D> facePositions;
      HalfedgeCIter hStart = v->halfedge();
      HalfedgeCIter hChange = hStart;
      do
      {
        facePositions.push_back(hChange->face()->newPosition);
        hChange = hChange->twin()->next();
      } while (hChange != hStart);
      size_t vertexDegree = facePositions.size();
      Vector3D Q;
      for (Vector3D pos : facePositions) Q += pos;
      Q /= vertexDegree;

      // R is the average of all edge midpoints for edges containing v
      vector<Vector3D> edgeMidpointPositions;
      hStart = v->halfedge();
      hChange = hStart;
      Vector3D R;
      do
      {
        Vector3D edgeMidpoint = (v->position + hChange->next()->vertex()->position) / 2;
        R += edgeMidpoint;
        hChange = hChange->twin()->next();
      } while (hChange != hStart);
      R /= vertexDegree;

      // S is the original vertex position for vertex v
      Vector3D S = v->position;

      // weighted sum
      v->newPosition = (Q + 2 * R + (vertexDegree - 3) * S) / vertexDegree;
    }
    else {
      // boundary edge
      HalfedgeIter hStart = v->halfedge();
      HalfedgeIter hChange = hStart;
      vector<Vector3D> boundaryEdgePositions;
      do
      {
        if (hChange->edge()->isBoundary()) boundaryEdgePositions.push_back(hChange->next()->vertex()->position);
        hChange = hChange->twin()->next();
      } while (hChange != hStart);
      if (boundaryEdgePositions.size() == 2) {
        // crease
        v->newPosition = (boundaryEdgePositions[0] + 6 * v->position + boundaryEdgePositions[1]) / 8;
      }
      if (boundaryEdgePositions.size() >= 3 || boundaryEdgePositions.size() == 1) {
        // corner rule, vertex position stays the same
        // or a "dart" (1 sharp edge), and I don't care
        v->newPosition = v->position;
      }
    }
  }
}

/**
 * Assign a unique integer index to each vertex, edge, and face in
 * the mesh, starting at 0 and incrementing by 1 for each element.
 * These indices will be used as the vertex indices for a mesh
 * subdivided using Catmull-Clark (or linear) subdivision.
 */
void HalfedgeMesh::assignSubdivisionIndices() {
  // TODO Start a counter at zero; if you like, you can use the
  // "Index" type (defined in halfedgeMesh.h)
  Index index = 0;

  // TODO Iterate over vertices, assigning values to Vertex::index
  for (VertexIter v = verticesBegin(); v != verticesEnd(); v++, index++) {
    v->index = index;
  }
  // TODO Iterate over edges, assigning values to Edge::index
  for (EdgeIter e = edgesBegin(); e != edgesEnd(); e++, index++) {
    e->index = index;
  }
  // TODO Iterate over faces, assigning values to Face::index
  for (FaceIter f = facesBegin(); f != facesEnd(); f++, index++) {
    f->index = index;
  }
}

/**
 * Build a flat list containing all the vertex positions for a
 * Catmull-Clark (or linear) subdivison of this mesh.  The order of
 * vertex positions in this list must be identical to the order
 * of indices assigned to Vertex::newPosition, Edge::newPosition,
 * and Face::newPosition.
 */
void HalfedgeMesh::buildSubdivisionVertexList(vector<Vector3D>& subDVertices) {
  // TODO Resize the vertex list so that it can hold all the vertices.

  // TODO Iterate over vertices, assigning Vertex::newPosition to the
  // appropriate location in the new vertex list.
  for (VertexCIter v = verticesBegin(); v != verticesEnd(); v++) {
    subDVertices.push_back(v->newPosition);
  }
  // TODO Iterate over edges, assigning Edge::newPosition to the appropriate
  // location in the new vertex list.
  for (EdgeCIter e = edgesBegin(); e != edgesEnd(); e++) {
    subDVertices.push_back(e->newPosition);
  }
  // TODO Iterate over faces, assigning Face::newPosition to the appropriate
  // location in the new vertex list.
  for (FaceCIter f = facesBegin(); f != facesEnd(); f++) {
    subDVertices.push_back(f->newPosition);
  }
}

/**
 * Build a flat list containing all the quads in a Catmull-Clark
 * (or linear) subdivision of this mesh.  Each quad is specified
 * by a vector of four indices (i,j,k,l), which come from the
 * members Vertex::index, Edge::index, and Face::index.  Note that
 * the ordering of these indices is important because it determines
 * the orientation of the new quads; it is also important to avoid
 * "bowties."  For instance, (l,k,j,i) has the opposite orientation
 * of (i,j,k,l), and if (i,j,k,l) is a proper quad, then (i,k,j,l)
 * will look like a bowtie.
 */
void HalfedgeMesh::buildSubdivisionFaceList(vector<vector<Index> >& subDFaces) {
  // TODO This routine is perhaps the most tricky step in the construction of
  // a subdivision mesh (second, perhaps, to computing the actual Catmull-Clark
  // vertex positions).  Basically what you want to do is iterate over faces,
  // then for each for each face, append N quads to the list (where N is the
  // degree of the face).  For this routine, it may be more convenient to simply
  // append quads to the end of the list (rather than allocating it ahead of
  // time), though YMMV.  You can of course iterate around a face by starting
  // with its first halfedge and following the "next" pointer until you get
  // back to the beginning.  The tricky part is making sure you grab the right
  // indices in the right order---remember that there are indices on vertices,
  // edges, AND faces of the original mesh.  All of these should get used.  Also
  // remember that you must have FOUR indices per face, since you are making a
  // QUAD mesh!

  // iterate over faces
  for (FaceCIter f = facesBegin(); f != facesEnd(); f++) {
    // loop around face
    HalfedgeCIter hStart = f->halfedge();
    HalfedgeCIter hChange = hStart;
    do
    {
      // build lists of four indices for each sub-quad
      vector<Index> quad(4);
      quad[0] = f->index; // add face vertex
      quad[1] = hChange->edge()->index; // add edge1 vertex
      quad[2] = hChange->next()->vertex()->index; // add vertex vertex
      quad[3] = hChange->next()->edge()->index; // add edge2 vertex

      // append each list of four indices to face list
      subDFaces.push_back(quad);

      // iterate half-edge to loop around
      hChange = hChange->next();
    } while (hChange != hStart);
  }
}

FaceIter HalfedgeMesh::bevelVertex(VertexIter v) {
  // *** Extra Credit ***
  // TODO This method should replace the vertex v with a face, corresponding to
  // a bevel operation. It should return the new face.  NOTE: This method is
  // responsible for updating the *connectivity* of the mesh only---it does not
  // need to update the vertex positions.  These positions will be updated in
  // HalfedgeMesh::bevelVertexComputeNewPositions (which you also have to
  // implement!)

  showError("bevelVertex() not implemented.");
  return facesBegin();
}

FaceIter HalfedgeMesh::bevelEdge(EdgeIter e) {
  // *** Extra Credit ***
  // TODO This method should replace the edge e with a face, corresponding to a
  // bevel operation. It should return the new face.  NOTE: This method is
  // responsible for updating the *connectivity* of the mesh only---it does not
  // need to update the vertex positions.  These positions will be updated in
  // HalfedgeMesh::bevelEdgeComputeNewPositions (which you also have to
  // implement!)

  showError("bevelEdge() not implemented.");
  return facesBegin();
}

FaceIter HalfedgeMesh::bevelFace(FaceIter f) {
  // *** Extra Credit ***
  // TODO This method should replace the face f with an additional, inset face
  // (and ring of faces around it), corresponding to a bevel operation. It
  // should return the new face.  NOTE: This method is responsible for updating
  // the *connectivity* of the mesh only---it does not need to update the vertex
  // positions.  These positions will be updated in
  // HalfedgeMesh::bevelFaceComputeNewPositions (which you also have to
  // implement!)

  showError("bevelFace() not implemented.");
  return facesBegin();
}


void HalfedgeMesh::bevelFaceComputeNewPositions(
    vector<Vector3D>& originalVertexPositions,
    vector<HalfedgeIter>& newHalfedges, double normalShift,
    double tangentialInset) {
  // *** Extra Credit ***
  // TODO Compute new vertex positions for the vertices of the beveled face.
  //
  // These vertices can be accessed via newHalfedges[i]->vertex()->position for
  // i = 1, ..., newHalfedges.size()-1.
  //
  // The basic strategy here is to loop over the list of outgoing halfedges,
  // and use the preceding and next vertex position from the original mesh
  // (in the originalVertexPositions array) to compute an offset vertex
  // position.
  //
  // Note that there is a 1-to-1 correspondence between halfedges in
  // newHalfedges and vertex positions
  // in orig.  So, you can write loops of the form
  //
  // for( int i = 0; i < newHalfedges.size(); hs++ )
  // {
  //    Vector3D pi = originalVertexPositions[i]; // get the original vertex
  //    position correponding to vertex i
  // }
  //

}

void HalfedgeMesh::bevelVertexComputeNewPositions(
    Vector3D originalVertexPosition, vector<HalfedgeIter>& newHalfedges,
    double tangentialInset) {
  // *** Extra Credit ***
  // TODO Compute new vertex positions for the vertices of the beveled vertex.
  //
  // These vertices can be accessed via newHalfedges[i]->vertex()->position for
  // i = 1, ..., hs.size()-1.
  //
  // The basic strategy here is to loop over the list of outgoing halfedges,
  // and use the preceding and next vertex position from the original mesh
  // (in the orig array) to compute an offset vertex position.

}

void HalfedgeMesh::bevelEdgeComputeNewPositions(
    vector<Vector3D>& originalVertexPositions,
    vector<HalfedgeIter>& newHalfedges, double tangentialInset) {
  // *** Extra Credit ***
  // TODO Compute new vertex positions for the vertices of the beveled edge.
  //
  // These vertices can be accessed via newHalfedges[i]->vertex()->position for
  // i = 1, ..., newHalfedges.size()-1.
  //
  // The basic strategy here is to loop over the list of outgoing halfedges,
  // and use the preceding and next vertex position from the original mesh
  // (in the orig array) to compute an offset vertex position.
  //
  // Note that there is a 1-to-1 correspondence between halfedges in
  // newHalfedges and vertex positions
  // in orig.  So, you can write loops of the form
  //
  // for( int i = 0; i < newHalfedges.size(); i++ )
  // {
  //    Vector3D pi = originalVertexPositions[i]; // get the original vertex
  //    position correponding to vertex i
  // }
  //

}

void HalfedgeMesh::splitPolygons(vector<FaceIter>& fcs) {
  for (auto f : fcs) splitPolygon(f);
}

void HalfedgeMesh::splitPolygon(FaceIter f) {
  // *** Extra Credit ***
  // TODO: (meshedit) 
  // Triangulate a polygonal face
  showError("splitPolygon() not implemented.");
}

EdgeRecord::EdgeRecord(EdgeIter& _edge) : edge(_edge) {
  // *** Extra Credit ***
  // TODO: (meshEdit)
  // Compute the combined quadric from the edge endpoints.
  // -> Build the 3x3 linear system whose solution minimizes the quadric error
  //    associated with these two endpoints.
  // -> Use this system to solve for the optimal position, and store it in
  //    EdgeRecord::optimalPoint.
  // -> Also store the cost associated with collapsing this edg in
  //    EdgeRecord::Cost.
}

void MeshResampler::upsample(HalfedgeMesh& mesh)
// This routine should increase the number of triangles in the mesh using Loop
// subdivision.
{
  // disable testing for intermediate operations
  bool previous_run_tests = mesh.RUN_TESTS;
  mesh.RUN_TESTS = false;
  // TODO: (meshEdit)
  // Compute new positions for all the vertices in the input mesh, using
  // the Loop subdivision rule, and store them in Vertex::newPosition.
  for (VertexIter v = mesh.verticesBegin(); v != mesh.verticesEnd(); v++) {
    if (!v->isBoundary()) {
      Size n = v->degree();
      float u = n == 3 ? 3.0 / 16.0 : 3.0 / (8.0 * n);
      v->newPosition = (1.0f - double(n) * u) * v->position;
      auto hStart = v->halfedge();
      auto hChange = hStart;
      do
      {
        v->newPosition += u * hChange->next()->vertex()->position;
        hChange = hChange->twin()->next();
      } while (hChange != hStart);
    }
    else {
      // boundary vertex
      HalfedgeIter hStart = v->halfedge();
      HalfedgeIter hChange = hStart;
      vector<Vector3D> boundaryEdgePositions;
      do
      {
        if (hChange->edge()->isBoundary()) boundaryEdgePositions.push_back(hChange->next()->vertex()->position);
        hChange = hChange->twin()->next();
      } while (hChange != hStart);
      if (boundaryEdgePositions.size() == 2) {
        // crease
        v->newPosition = (boundaryEdgePositions[0] + 6 * v->position + boundaryEdgePositions[1]) / 8;
      }
      if (boundaryEdgePositions.size() >= 3 || boundaryEdgePositions.size() == 1) {
        // corner rule, vertex position stays the same
        // or a "dart" (1 sharp edge), and I don't care
        v->newPosition = v->position;
      }
    }
    // -> At this point, we also want to mark each vertex as being a vertex of the
    //    original mesh.
    v->isNew = false;
  }
  // -> Next, compute the updated vertex positions associated with edges, and
  //    store it in Edge::newPosition.
  for (EdgeIter e = mesh.edgesBegin(); e != mesh.edgesEnd(); e++) {
    e->isNew = false;
    // assert only triangles
    if (e->halfedge()->next()->next()->next() != e->halfedge()
      && !e->halfedge()->isBoundary()) {
      // not a triangle
      showError("Can only do loop subdivision on a mesh of all triangles; this ain't it, cheif.");
      return;
    }
    if (e->halfedge()->twin()->next()->next()->next() != e->halfedge()->twin()
      && !e->halfedge()->twin()->isBoundary()) {
      // not a triangle
      showError("Can only do loop subdivision on a mesh of all triangles; this ain't it, cheif.");
      return;
    }

    auto A = e->halfedge()->vertex()->position;
    auto B = e->halfedge()->twin()->vertex()->position;
    if (!e->isBoundary()) {
      // compute stuff
      auto C = e->halfedge()->next()->next()->vertex()->position;
      auto D = e->halfedge()->twin()->next()->next()->vertex()->position;
      e->newPosition = 3.0 / 8.0 * (A + B) + 1.0 / 8.0 * (C + D);
    }
    else {
      // boundary edge
      e->newPosition = 0.5 * (A + B);
    }
  }
  // -> Next, we're going to split every edge in the mesh, in any order.  For
  //    future reference, we're also going to store some information about which
  //    subdivided edges come from splitting an edge in the original mesh, and
  //    which edges are new, by setting the flat Edge::isNew. Note that in this
  //    loop, we only want to iterate over edges of the original mesh.
  //    Otherwise, we'll end up splitting edges that we just split (and the
  //    loop will never end!)
  // iterate over all edges in the mesh
  int n = mesh.nEdges();
  EdgeIter e = mesh.edgesBegin();
  for (int i = 0; i < n; i++) {

    // get the next edge NOW! I said NOW!!
    EdgeIter nextEdge = e;
    nextEdge++;

    // now, even if splitting the edge deletes it...
    if (!e->isNew) {
      auto newVert = mesh.splitEdge(e);
      newVert->isNew = true;
      newVert->newPosition = e->newPosition;
      auto otherOldEdge = newVert->halfedge()->edge(); // splitEdge returns vert with h.e. on new edge along original split edge
      // walk edges to mark the new ones
      HalfedgeIter hStart = newVert->halfedge();
      HalfedgeIter hChange = hStart;
      do
      {
        if (hChange->edge() != e && hChange->edge() != otherOldEdge) {
          // new edge
          hChange->edge()->isNew = true;
        }
        hChange = hChange->twin()->next();
      } while (hChange != hStart);
    }

    // ...we still have a valid reference to the next edge.
    e = nextEdge;
  }
  // -> Now flip any new edge that connects an old and new vertex.
  for (e = mesh.edgesBegin(); e != mesh.edgesEnd(); e++) {
    VertexCIter v0 = e->halfedge()->vertex();
    VertexCIter v1 = e->halfedge()->twin()->vertex();
    if (e->isNew && (v0->isNew != v1->isNew)) {
      mesh.flipEdge(e);
    }
  }
  // -> Finally, copy the new vertex positions into final Vertex::position.
  for (VertexIter v = mesh.verticesBegin(); v != mesh.verticesEnd(); v++) {
    // compute stuff
    v->position = v->newPosition;
  }

  // reset testing
  mesh.RUN_TESTS = previous_run_tests;
  mesh.RunAllTestsForEntireMesh(&mesh);
}

void MeshResampler::downsample(HalfedgeMesh& mesh) {
  // *** Extra Credit ***
  // TODO: (meshEdit)
  // Compute initial quadrics for each face by simply writing the plane equation
  // for the face in homogeneous coordinates. These quadrics should be stored
  // in Face::quadric
  // -> Compute an initial quadric for each vertex as the sum of the quadrics
  //    associated with the incident faces, storing it in Vertex::quadric
  // -> Build a priority queue of edges according to their quadric error cost,
  //    i.e., by building an EdgeRecord for each edge and sticking it in the
  //    queue.
  // -> Until we reach the target edge budget, collapse the best edge. Remember
  //    to remove from the queue any edge that touches the collapsing edge
  //    BEFORE it gets collapsed, and add back into the queue any edge touching
  //    the collapsed vertex AFTER it's been collapsed. Also remember to assign
  //    a quadric to the collapsed vertex, and to pop the collapsed edge off the
  //    top of the queue.
  showError("downsample() not implemented.");
}

void MeshResampler::resample(HalfedgeMesh& mesh) {
  // *** Extra Credit ***
  // TODO: (meshEdit)
  // Compute the mean edge length.
  // Repeat the four main steps for 5 or 6 iterations
  // -> Split edges much longer than the target length (being careful about
  //    how the loop is written!)
  // -> Collapse edges much shorter than the target length.  Here we need to
  //    be EXTRA careful about advancing the loop, because many edges may have
  //    been destroyed by a collapse (which ones?)
  // -> Now flip each edge if it improves vertex degree
  // -> Finally, apply some tangential smoothing to the vertex positions
  showError("resample() not implemented.");
}

// Local operation tests

bool VertexTest(VertexCIter v) {
  // a vertex test that goes through the ring of halfedges around it to check that all the halfedges point to that vertex
  HalfedgeCIter h0 = v->halfedge();
  HalfedgeCIter hChange = h0;
  do
  {
    if (hChange->vertex() != v) {
      cout << "Halfedge " << &hChange << " should point to vertex " << &v << " but points to " << &hChange->vertex() << endl;
      return false;
    }
    hChange = hChange->twin()->next(); // cycle around
  } while (hChange != h0);
  return true;
}
bool EdgeTest(EdgeCIter e) {
  // an edge test to checks that the pair of halfedges point to that edge
  HalfedgeCIter h0 = e->halfedge();
  if (h0->edge() != e) {
    cout << "Halfedge " << &h0 << " should point to edge " << &e << " but points to " << &h0->edge() << endl;
    return false;
  }
  if (h0->twin()->edge() != e) {
    cout << "Halfedge " << &h0->twin() << " should point to edge " << &e << " but points to " << &h0->twin()->edge() << endl;
    return false;
  }
  return true;
}
bool FaceTest(FaceCIter f) {
  // a face test that goes around the face to check that all the halfedges point to that face
  HalfedgeCIter h0 = f->halfedge();
  HalfedgeCIter hChange = h0;
  do
  {
    if (hChange->face() != f) {
      cout << "Halfedge " << &hChange << " should point to face " << &f << " but points to " << &hChange->face() << endl;
      return false;
    }
    hChange = hChange->next(); // cycle around
  } while (hChange != h0);
  return true;
}

void HalfedgeMesh::RunAllTestsForEntireMesh(HalfedgeMesh* mesh) {
  // a test that runs all previous 3 tests for every vertex, edge and face in the mesh
  if (RUN_TESTS) {
    bool vertPass = true, edgePass = true, facePass = true;
    // vertices
    for (VertexCIter v = mesh->verticesBegin(); v != mesh->verticesEnd(); v++) {
      if (!VertexTest(v)) vertPass = false;
    }
    // edges
    for (EdgeCIter e = mesh->edgesBegin(); e != mesh->edgesEnd(); e++) {
      if (!EdgeTest(e)) edgePass = false;
    }
    // faces
    for (FaceCIter f = mesh->facesBegin(); f != mesh->facesEnd(); f++) {
      if (!FaceTest(f)) facePass = false;
    }

    if(!vertPass || !edgePass || !facePass)
      cout << "vert pass: " << vertPass << " edge pass: " << edgePass << " face pass: " << facePass << endl;
  }
}

}  // namespace CS248
