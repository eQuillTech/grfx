//
//  Triangulation.cpp
//  TiffTri
//
//  Created by Phil Ahrenkiel on 4/5/23.
//
#include <queue>
#include <list>
#include <stack>

#include "weiss.hpp"
#include "Topo.hpp"

// Type-defs for generating triangulations on a 2-D lattice
typedef std::pair<long, long> LattPoint; // values are point coords
typedef std::pair<long, long> LattEdge; // values are point indices
typedef std::tuple<LattEdge, long, long> LattSharedEdge; // edge and indices of sharing triangs

//-----------------------------------------------------------------------------
// Name        :  GetPointImage
// Creation    :  22-Nov-2022 SPA
// Description :  Compute point image representing pixel corners. Values are
//                interpolated from adjacent pixels
// Parameters  :  See parameter list...
// Returns     :
//-----------------------------------------------------------------------------
static void GetPointImage
(
   std::size_t width, std::size_t height, // Original dimensions of image
   std::vector<bool> &patch_img, // Provided bool patch image
   std::vector<float> &data_img, // Original data (pixel) image
   std::vector<float> &point_img // Contains (extended) interpolated point image
)
{
   int row[] = { -1, 0, -1, 0 };
   int col[] = { 0, -1, -1, 0 };

   std::size_t iPos = 0;
   for (std::size_t iY = 0; iY <= height; iY++)
   {
      for (std::size_t iX = 0; iX <= width; iX++)
      {
         float val = 0;
         short n_avg = 0;
         for (int k = 0; k < 4; ++k)
         {
            std::size_t iXp = iX + col[k], iYp = iY + row[k];
            if ((iXp >= 0) && (iXp < width) && (iYp >= 0) && (iYp < height))
            {
               if (patch_img[(iXp) + width * (iYp)])
               {
                  val += data_img[(iXp) + width * (iYp)];
                  n_avg++;
               }
            }
         }
         if (n_avg > 0)
         {
            val /= n_avg;
         }
         point_img[iPos] = val;
         iPos++;
      }
   }
}

//-----------------------------------------------------------------------------
// Name        :  IsLattPointInCircle
// Creation    :  28-Oct-2022 SPA
// Description :  Determines whether a given lattice point is within a circle
//                described by the provided vector of three lattice points. Calculation
//                is done using long double (with no division) to avoid truncation issues.
// Parameters  :
//    const std::vector<LattPoint> &tri_pts - Lattice points describing circle
//    const LattPoint &P - Lattice point to check
// Returns     :  true if point determined to be inside, false otherwise
//-----------------------------------------------------------------------------
static bool IsLattPointInCircle(const std::vector<LattPoint> &tri_pts, const LattPoint &P)
{
   if (tri_pts.size() != 3) // Need vertices of a triangle
   {
      return false;
   }
   long double X_m[3][2];
   long double Y_m[3];

   for (int i = 0; i < 3; i++)
   {
      long double iX = (long double)tri_pts[i].first;
      long double iY = (long double)tri_pts[i].second;
      X_m[i][0] = iX;
      X_m[i][1] = iY;

      Y_m[i] = iX * iX + iY * iY;
   }

   long double detM =
      X_m[0][0] * (X_m[1][1] - X_m[2][1]) -
      X_m[0][1] * (X_m[1][0] - X_m[2][0]) +
      (X_m[1][0] * X_m [2][1] - X_m[1][1] * X_m[2][0]);

   long double adjX_m[3][3];
   adjX_m[0][0] = (X_m[1][1] - X_m[2][1]);
   adjX_m[0][1] = (X_m[2][1] - X_m[0][1]);
   adjX_m[0][2] = (X_m[0][1] - X_m[1][1]);

   adjX_m[1][0] = (X_m[2][0] - X_m[1][0]);
   adjX_m[1][1] = (X_m[0][0] - X_m[2][0]);
   adjX_m[1][2] = (X_m[1][0] - X_m[0][0]);

   adjX_m[2][0] = (X_m[1][0] * X_m[2][1] - X_m[1][1] * X_m[2][0]);
   adjX_m[2][1] = (X_m[0][1] * X_m[2][0] - X_m[0][0] * X_m[2][1]);
   adjX_m[2][2] = (X_m[0][0] * X_m[1][1] - X_m[0][1] * X_m[1][0]);

   long double Z_m[3];
   for (int i = 0; i < 3; i++)
   {
      Z_m[i] = 0;
      for (int j = 0; j < 3; j++)
      {
         Z_m[i] += adjX_m[i][j] * Y_m[j];
      }
   }

   long double X = Z_m[0] * P.first + Z_m[1] * P.second + Z_m[2];
   long double Y = detM * (P.first * P.first + P.second * P.second);
   if (((X > Y) && (detM > 0.)) || ((X < Y) && (detM < 0.)))
   {
      return true;
   }
   return false;
}

//-----------------------------------------------------------------------------
// Name        :  IsLattPointInTriang
// Creation    :  28-Oct-2022 SPA
// Description :  Determines whether a given lattice point is within the interior
//                of a 2-D triangle.
// Parameters  :
//    const LattPoint &P - Lattice point to check
//    const LattPoint &A - Triangle vertex
//    const LattPoint &B - Triangle vertex
//    const LattPoint &C - Triangle vertex
// Returns     :  true if point determined to be inside, false otherwise
//-----------------------------------------------------------------------------
static bool IsLattPointInTriang(const LattPoint &P, const LattPoint &A, const LattPoint &B, const LattPoint &C)
{
   long ABx = B.first - A.first;
   long ABy = B.second - A.second;

   long ACx = C.first - A.first;
   long ACy = C.second - A.second;

   long APx = P.first - A.first;
   long APy = P.second - A.second;

   long denom = ABx * ACy - ACx * ABy;
   if (denom < 0)
   {
      std::swap(ABx, ACx);
      std::swap(ABy, ACy);
      denom = -denom;
   }

   long s = APx * ACy - ACx * APy;
   long t = ABx * APy - APx * ABy;
   
   if ((0 < s) && (s < denom) && (0 < t) && (t < denom) && (s + t < denom))
   {
      return true;
   }
   return false;
}

//-----------------------------------------------------------------------------
// Name        :  IsTopEdgeShared
// Creation    :  19-Sep-2022 SPA
// Description :  Determines whether the top edge in the current row is shared with
//                a triangle in the row above.
// Parameters  :
//    LattEdge &top_edge - Vertex indices of current top row
//    std::queue<std::pair<LattEdge, int>> &bottom_edge_triangs - Bottom edges of previous row
// Returns     :
//    bool - true if edge is shared, false otherwise
//-----------------------------------------------------------------------------
static bool IsTopEdgeShared(LattEdge &top_edge, std::queue<std::pair<LattEdge, long>> &bottom_edge_triangs)
{
   while (!bottom_edge_triangs.empty())
   {
      auto &bottom_edge_triang(bottom_edge_triangs.front());
      auto &bottom_edge(bottom_edge_triang.first);
      if (top_edge.first > bottom_edge.first)
      {
         bottom_edge_triangs.pop();
         continue;
      }
      else
      {
         if (top_edge.first < bottom_edge.first)
         {
            return false;
         }
         return true;
      }
   }
   return false;
}

// Define bit-masks for point characterization
const short bottom_left_mask     = 1 << 0;
const short bottom_right_mask    = 1 << 1;
const short top_right_mask       = 1 << 2;
const short top_left_mask        = 1 << 3;

const short vertex_mask          = 1 << 4;
const short fixed_mask           = 1 << 5;
const short border_mask          = 1 << 6;
const short apex_mask            = 1 << 7;
const short recess_mask          = 1 << 8;
const short straight_mask        = 1 << 9;
const short x_border_mask        = 1 << 10;
const short y_border_mask        = 1 << 11;

const short data_mask = 0b01111;
const short top_border_mask = 0b0011;
const short left_border_mask = 0b0110;
const short bottom_border_mask = 0b1100;
const short right_border_mask = 0b1001;

//-----------------------------------------------------------------------------
// Name        :  InitFlagImage
// Creation    :  22-Nov-2022 SPA
// Description :  Compute image of flags to retain local environment of each point,
//                particularly boundary points between data/no-data regions .
//
// Parameters  :  See parameter list...
// Returns     :
//-----------------------------------------------------------------------------
static void InitFlagImage
(  std::vector<bool> &patch_img, // Patch image: true if pixel contains valid data, false if no-date
   std::vector<short> &flag_img,  // Contains (extended) image of point flags upon return
   std::size_t width, std::size_t height // Image dimensions
)
{
   int iPos = 0;
   for (std::size_t iY = 0; iY <= height; iY++)
   {
      for (std::size_t iX = 0; iX <= width; iX++)
      {
         bool fixed = false;
         bool vertex = false;
         bool straight = false;
         bool x_border = false;
         bool y_border = false;
         bool apex = false;
         bool recess = false;
         bool patch_nn =  false;
         bool patch_n0 =  false;
         bool patch_0n =  false;
         bool patch_00 =  false;
        
         if ((iX > 0) && (iY < height))
         {
            patch_n0 = patch_img[(iX - 1) + width * (iY)];
         }
         if ((iX < width) && (iY < height))
         {
            patch_00 = patch_img[(iX) + width * (iY)];
         }
         if ((iX < width) && (iY > 0))
         {
            patch_0n = patch_img[(iX) + width * (iY - 1)];
         }
         if ((iX > 0) && (iY > 0))
         {
            patch_nn = patch_img[(iX - 1) + width * (iY - 1)];
         }

         short patch =
            ((short)patch_nn * top_left_mask) +
            ((short)patch_0n * top_right_mask) +
            ((short)patch_00 * bottom_right_mask) +
            ((short)patch_n0 * bottom_left_mask);
         bool border = (patch != data_mask) && (patch & data_mask);
         if ((patch & data_mask) && border)
         {
            vertex = true;
            x_border = (patch == left_border_mask) || (patch == right_border_mask);
            y_border = (patch == top_border_mask) || (patch == bottom_border_mask);
            straight = x_border || y_border;
            //fixed = !straight;
            apex =
               (patch == top_left_mask) ||
               (patch == top_right_mask) ||
               (patch == bottom_right_mask) ||
               (patch == bottom_left_mask);
            recess =
               (patch == ~top_left_mask) ||
               (patch == ~top_right_mask) ||
               (patch == ~bottom_right_mask) ||
               (patch == ~bottom_left_mask);
         }
         flag_img[iPos] =
            (short)x_border * x_border_mask +
            (short)y_border * y_border_mask +
            (short)straight * straight_mask +
            (short)apex * apex_mask +
            (short)recess * recess_mask +
            (short)border * border_mask +
            (short)fixed * fixed_mask +
            (short)vertex * vertex_mask +
            patch;

         iPos++;
      }
   }
}

//-----------------------------------------------------------------------------
// Name        :  FlagPoints
// Creation    :  22-Nov-2022 SPA
// Description :  Flag additional points as fixed vertices for triangulation,
//                depending on selected resolution
//
// Parameters  :  See parameter list...
// Returns     :
//-----------------------------------------------------------------------------
static bool FlagPoints
(  std::vector<float> &point_img, // (Extended) point image
   std::vector<short> &flag_img,  // (Extended) flag image - to be modified here
   std::size_t ext_width, std::size_t ext_height, // (Extended) image dimensions
   float tri_res  // User-specified resolution parameter (0 - 1)
)
{
   // Target an average vertex spacing (in pixels) of 1 / tri_res
   double inv_L_unif = sqrt(tri_res); // ~ mean inverse vertex spacing

   // Find local curvature in X for weighting
   auto distX_img = std::vector<float>(ext_width * ext_height);
   float wX_tot = 0.;
   int nX_tot_body_pts = 0;
   float abs_curvX_max = 0;
   std::size_t iPos = 0;
   for (std::size_t iY = 0; iY < ext_height; iY++)
   {
      for (std::size_t iX = 0; iX < ext_width; iX++)
      {
         float dist = 0;
         if (flag_img[iPos] & data_mask)
         {
            float d2f = 0.;
            if ((iX > 0) && (iX < ext_width - 1))
            {
               if ((flag_img[iPos - 1] & data_mask) && (flag_img[iPos + 1] & data_mask))
               {
                  d2f = point_img[iPos - 1] + point_img[iPos + 1] - 2 * point_img[iPos];
               }
            }
            float abs_curv = fabs (d2f);
            abs_curvX_max = std::max(abs_curvX_max, abs_curv);
            wX_tot += abs_curv;
            dist = abs_curv;
            nX_tot_body_pts++;
         }
         distX_img[iPos] = dist;
         iPos++;
      }
   }
   float abs_curvX_avg = wX_tot / nX_tot_body_pts;

   // Initialize a quasi-uniform distribution in X
   double aX = 0.;
   double bX = inv_L_unif;
   if ((abs_curvX_avg > 0.) && (inv_L_unif > 0.))
   {  // Find linear distribution in X with average of inv_L_unif
      double abs_curve_c = abs_curvX_avg / inv_L_unif;
      aX = 1. / abs_curve_c;
      bX = 0.;
      if (abs_curvX_max > abs_curve_c)
      {
         aX = (1 - inv_L_unif) / (abs_curvX_max - abs_curvX_avg);
         bX = inv_L_unif - aX * abs_curvX_avg;
      }
   }
   
   // Oscillate in X
   auto phaseX_img = std::vector<double>(ext_width * ext_height);
   iPos = 0;
   for (std::size_t iY = 0; iY < ext_height; iY++)
   {
      double phase = 0.;
      for (std::size_t iX = 0; iX < ext_width; iX++)
      {
         phaseX_img[iPos] = phase;
         double dphase = 0.;
         short flag = flag_img[iPos];
         if (flag & data_mask)
         {
            double d = distX_img[iPos];
            double inv_L_local = aX * d + bX;
            dphase = inv_L_local;
         }
         phase += dphase;
         iPos++;
      }
   }
   
   // Create a tic image for vertex placement
   auto tic_img = std::vector<bool>(ext_width * ext_height);

   iPos = 0;
   for (std::size_t iY = 0; iY < ext_height; iY++)
   {
     double prev_phase = 0;
     for (std::size_t iX = 0; iX < ext_width; iX++)
      {
         bool tic = false;
         double phase = phaseX_img[iPos];
         short flag = flag_img[iPos];
         if ((phase >= prev_phase + 1) || (flag & x_border_mask))
         {
            tic = true;
            prev_phase += floor(phase - prev_phase);
         }
         tic_img[iPos] = tic;
         iPos++;
      }
   }
   
   // Find local curvature in Y for weighting
   auto distY_img = std::vector<float>(ext_width * ext_height);
   float wY_tot = 0.;
   int nY_tot_body_pts = 0;
   float abs_curvY_max = 0;
   iPos = 0;
   for (std::size_t iY = 0; iY < ext_height; iY++)
   {
      for (std::size_t iX = 0; iX < ext_width; iX++)
      {
         float dist = 0;
         if (flag_img[iPos] & data_mask)
         {
            float d2f = 0.;
            if ((iY > 0) && (iY <  ext_height - 1))
            {
               if ((flag_img[iPos - ext_width] & data_mask) && (flag_img[iPos + ext_width] & data_mask))
               {
                  d2f = point_img[iPos - ext_width] + point_img[iPos + ext_width] - 2 * point_img[iPos];
               }
            }
            float abs_curv = fabs (d2f);
            abs_curvY_max = std::max(abs_curvY_max, abs_curv);
            wY_tot += abs_curv;
            dist = abs_curv;
            nY_tot_body_pts++;
         }
         distY_img[iPos] = dist;
         iPos++;
      }
   }

   // Initialize a quasi-uniform distribution in Y
   double aY = 0.;
   double bY = inv_L_unif;
   float abs_curvY_avg = wY_tot / nY_tot_body_pts;
   if ((abs_curvY_avg > 0.) && (inv_L_unif > 0.))
   {  // Find linear distribution in Y with average of inv_L_unif
      double abs_curve_c = abs_curvY_avg / inv_L_unif;
      aY = 1 / abs_curve_c;
      bY = 0;
      if (abs_curvY_max > abs_curve_c)
      {
         aY = (1 - inv_L_unif) / (abs_curvY_max - abs_curvY_avg);
         bY = inv_L_unif - aY * abs_curvY_avg;
      }
   }

   // Oscillate in Y
   auto phaseY_img = std::vector<double>(ext_width * ext_height);
   for (std::size_t iX = 0; iX < ext_width; iX++)
   {
      double phase = 0.;
      for (std::size_t iY = 0; iY < ext_height; iY++)
      {
         iPos = (iX) + ext_width * (iY);
         phaseY_img[iPos] = phase;
         double dphase = 0.;
         short flag = flag_img[iPos];
         if (flag & data_mask)
         {
            double d = distY_img[iPos];
            double inv_L_local = aY * d + bY;
            dphase = inv_L_local;
         }
         phase += dphase;
      }
   }

   // Modify tic image to indicate coincidence of x- and y-tics
   for (std::size_t iX = 0; iX < ext_width; iX++)
   {
     double prev_phase = 0;
     for (std::size_t iY = 0; iY < ext_height; iY++)
     {
         iPos = (iX) + ext_width * (iY);
         bool tic = false;
         double phase = phaseY_img[iPos];
         short flag = flag_img[iPos];
         if ((phase >= prev_phase + 1) || (flag & y_border_mask))
         {
            tic = true;
            prev_phase += floor(phase - prev_phase);
         }
         tic_img[iPos] = tic_img[iPos] && tic;
     }
   }

   // Flag additional fixed vertices
   std::size_t nCount=0;
   iPos = 0;
   for (std::size_t iY = 0; iY < ext_height; iY++)
   {
      for (std::size_t iX = 0; iX < ext_width; iX++)
      {
         if (tic_img[iPos])
         {
            flag_img[iPos] |= vertex_mask + fixed_mask;
            nCount++;
         }
         iPos++;
      }
    }
    return true;
}

//
static void IndexPoints
(  std::vector<short> &flag_img, // (Extended) image of flag bits for each point
   std::size_t ext_width, std::size_t ext_height, // (Extended) image dimensions
   std::vector<long> &index_img, // Contains (extended) point-index image upon return
   std::vector<LattPoint> &pts // Contains points (vertices) upon return
)
{
   // Fill vector and create an index look-up image
   std::size_t n_pts = 0;
   std::size_t iPos = 0;
   for (std::size_t iY = 0; iY < ext_height; iY++)
   {
      for (std::size_t iX = 0; iX < ext_width; iX++)
      {
         long index = -1;
         if (flag_img[iPos] & vertex_mask)
         {
            pts.emplace_back(iX, iY);
            index = n_pts++;
         }
         index_img[iPos] = index;
         iPos++;
      }
   }
}

//---------------------------------UpperLowerTriangle
// Creation    :  30-Nov-2022 SPA
// Description :  Builds a row triangle with a horizontal upper edge. The built
//                triangle is added to triangs. Shared edges are added to edge_triangs.
//                Point edges are added to pt_edges.
// Parameters  :  See parameter list...
// Returns     :
//-----------------------------------------------------------------------------
static void BuildRowUpperTriangle
(  long ind_00, long ind_m1, long ind_n0,
   std::queue<std::pair<LattEdge, long>> &bottom_edge_triangs, // Edge and triangle
   bool &right_edge_valid,
   std::pair<LattEdge, long> &right_edge_triang,
   std::vector<std::tuple<LattEdge, long, long>> &edge_triangs, // Contains shared edges and sharing triangles upon return
   std::vector<std::list<long>> &pt_edges, // Contains shared edges associated with each vertex upon return
   TriIndexVector &triangs // Contains triangle indices upon return
)
{
   std::size_t n_edges = (int)edge_triangs.size();
   std::size_t n_triangs = (int)triangs.size();

   LattEdge top_edge({ind_00, ind_n0});
   if (IsTopEdgeShared(top_edge, bottom_edge_triangs))
   {
      edge_triangs.emplace_back(top_edge, bottom_edge_triangs.front().second, n_triangs);
      pt_edges[ind_00].push_back(n_edges);
      pt_edges[ind_n0].push_back(n_edges);
      n_edges++;
   }

   LattEdge left_edge({ind_00, ind_m1});
   if (right_edge_valid && (right_edge_triang.first == left_edge))
   {
      edge_triangs.emplace_back(left_edge, right_edge_triang.second, n_triangs);
      pt_edges[ind_00].push_back(n_edges);
      pt_edges[ind_m1].push_back(n_edges);
      n_edges++;
   }

   LattEdge right_edge({ind_n0, ind_m1});
   right_edge_triang = {right_edge, n_triangs};
   right_edge_valid = true;

   triangs.push_back(TriIndex{ind_00, ind_m1, ind_n0});
}

//-----------------------------------------------------------------------------
// Name        :  BuildRowLowerTriangle
// Creation    :  30-Nov-2022 SPA
// Description :  Builds a row triangle with a horizontal lower edge. The built
//                triangle is added to triangs. Shared edges are added to edge_triangs.
//                Point edges are added to pt_edges.
// Parameters  :  See parameter list...
// Returns     :
//-----------------------------------------------------------------------------
static void BuildRowLowerTriangle
(  long ind_00, long ind_01, long ind_m1,
   std::queue<std::pair<LattEdge, long>> &top_edge_triangs, // Edge and triangle
   bool &right_edge_valid,
   std::pair<LattEdge, long> &right_edge_triang,
   std::vector<std::tuple<LattEdge, long, long>> &edge_triangs, // Contains shared edges and sharing triangles upon return
   std::vector<std::list<long>> &pt_edges, // Contains shared edges associated with each vertex upon return
   TriIndexVector &triangs // Contains triangle indices upon return
)
{
   std::size_t n_edges = edge_triangs.size();
   std::size_t n_triangs = triangs.size();

   LattEdge bottom_edge({ind_01, ind_m1});
   top_edge_triangs.emplace(bottom_edge, n_triangs);

   LattEdge left_edge({ind_00, ind_01});
   if (right_edge_valid && (right_edge_triang.first == left_edge))
   {
      edge_triangs.emplace_back(left_edge, right_edge_triang.second, n_triangs);
      pt_edges[ind_00].push_back(n_edges);
      pt_edges[ind_01].push_back(n_edges);
      n_edges++;
   }

   LattEdge right_edge({ind_00, ind_m1});
   right_edge_triang = {right_edge, n_triangs};
   right_edge_valid = true;

   triangs.push_back(TriIndex{ind_00, ind_01, ind_m1});
}

//-----------------------------------------------------------------------------
// Name        :  GetNextRowVertex
// Creation    :  30-Nov-2022 SPA
// Description :  Scans a row to find the next vertex point based on preset flags.
//                The point array index is returned in pos_mn
// Parameters  :
//    std::vector<short> &flag_img - Flag bits for each point
//    int ext_width - (Extended) image width
//    int dY - Row offset (typically 0 or 1)
//    int pos_00 - Reference origin index
//    int pos_mn - Contains the index of the vertex point upon return
// Returns     :  bool - true if vertex found, false otherwise
//-----------------------------------------------------------------------------
static bool GetNextRowVertex(std::vector<short> &flag_img, std::size_t ext_width, long dY, long pos_00, long &pos_mn)
{
   long dX0 = 1;
   short flag = 0;
   pos_mn = pos_00 + (0 + dX0) + ext_width * (0 + dY);
   while (((flag = flag_img[pos_mn]) & data_mask) && !(flag & vertex_mask))
   {
      dX0++;
      pos_mn = pos_00 + (0 + dX0) + ext_width * (0 + dY);
   }
   return (flag & vertex_mask);
}

//-----------------------------------------------------------------------------
// Name        :  BuildRowTriangles
// Creation    :  28-Oct-2022 SPA
// Description :  Builds a vector of triangle point indices for subsequent triangulation.
//                The triangles are assembled in rows to ensure complete filling of valid areas
//                with no extension into invalid areas. A pointer to flag image must be provided
//                that indicates point info. Concurrently, vectors of shared edges and point edges
//                are built for subsequent conversion to Delaunay triangulation.
// Parameters  :  See parameter list...
// Returns     :
//
// Diagrams for various cases shown below:
// (.) data point, vertex
// (o) data point, non-vertex
// (+) data point, either
// (*) no-data point
// (x) no-data pixel
// 1a.         1b.         1x.
// . o +       .-o-.          .
// | \          \  |           x
// |  \          \ |          .
// .-o-.       . o .

// 2.          2x.         3.          3x.
// .-o-.       .           o . +       *
//  \  |         x          / \         x
//   \ |       *           /   \       ?
// o o .                   .-o-.
//-----------------------------------------------------------------------------
static bool BuildRowTriangles
(
   std::vector<short> &flag_img, // (Extended) image of flag bits for each point
   std::vector<long> &index_img, // (Extended) image of point indices (-1 for no-data)
   std::size_t ext_width, std::size_t ext_height, // (Extended) image dimensions
   TriIndexVector &triangs, // Contains triangle indices upon return
   std::vector<std::tuple<LattEdge, long, long>> &edge_triangs, // Contains shared edges and sharing triangles upon return
   std::vector<std::list<long>> &pt_edges // Contains shared edges associated with each vertex upon return
)
{
   std::queue<std::pair<LattEdge, long>> bottom_edge_triangs; // Edge and triangle
   for (std::size_t iY = 0; iY < ext_height - 1; iY++)
   {
      TriIndexVector top_triangs;
      std::queue<std::pair<LattEdge, long>> top_edge_triangs; // Edge and triangle
      std::pair<LattEdge, long> right_edge_triang; // Edge and triangle
      bool right_edge_valid = false;
      for (std::size_t iX = 0; iX < ext_width - 1; iX++)
      {
         long pos_00 = (iX) +  ext_width * (iY);
         short flag_00 = flag_img[pos_00];
         if (flag_00 & vertex_mask)
         {
            long ind_00 = index_img[pos_00];
            long pos_01 = (iX) + ext_width * (iY + 1);
            short flag_01 = flag_img[pos_01];
            if (flag_01 & vertex_mask)
            {
               long ind_01 = index_img[pos_01];
               long pos_10 = (iX + 1) + ext_width * (iY);
               if (!(flag_img[pos_10] & bottom_left_mask))
               {  // Case 1x.
                  continue;
               }
               long pos_m1;
               if (GetNextRowVertex(flag_img, ext_width, 1, pos_00, pos_m1))
               {   // Case 1a.
                  long ind_m1 = index_img[pos_m1];
                  BuildRowLowerTriangle
                  (  ind_00, ind_01, ind_m1,
                     top_edge_triangs,
                     right_edge_valid, right_edge_triang,
                     edge_triangs, pt_edges, triangs
                  );

                  long pos_n0;
                  if (GetNextRowVertex(flag_img, ext_width, 0, pos_00, pos_n0))
                  {  // Case 1b.
                     long ind_n0 = index_img[pos_n0];
                     BuildRowUpperTriangle
                     (  ind_00, ind_m1, ind_n0,
                        bottom_edge_triangs,
                        right_edge_valid, right_edge_triang,
                        edge_triangs, pt_edges, triangs
                     );
                  }
               }
            }
            else
            {
               if (!(flag_01 & top_right_mask))
               {  // Case 2x.
                  continue;
               }
               long pos_m1;
               if (GetNextRowVertex(flag_img, ext_width, 1, pos_00, pos_m1))
               {  // Case 2.
                  long ind_m1 = index_img[pos_m1];
                  long pos_n0;
                  if (GetNextRowVertex(flag_img, ext_width, 0, pos_00, pos_n0))
                  {  // Case 2.
                     long ind_n0 = index_img[pos_n0];
                     BuildRowUpperTriangle
                     (  ind_00, ind_m1, ind_n0,
                        bottom_edge_triangs,
                        right_edge_valid, right_edge_triang,
                        edge_triangs, pt_edges, triangs
                     );
                  }
               }
            }
         }
         else
         {
            if (!(flag_00 & bottom_right_mask))
            {  // case 3x.
               continue;
            }
            long pos_01 = (iX) + ext_width * (iY + 1);
            if (flag_img[pos_01] & vertex_mask)
            {
               long ind_01 = index_img[pos_01];
               long pos_m1;
               if (GetNextRowVertex(flag_img, ext_width, 1, pos_00, pos_m1))
               {
                  long ind_m1 = index_img[pos_m1];
                  long pos_n0;
                  if (GetNextRowVertex(flag_img, ext_width, 0, pos_00, pos_n0))
                  {  // Case 3.
                     long ind_n0 = index_img[pos_n0];
                     BuildRowLowerTriangle
                     (  ind_n0, ind_01, ind_m1,
                        top_edge_triangs,
                        right_edge_valid, right_edge_triang,
                        edge_triangs, pt_edges, triangs
                     );
                  }
               }
            }
         }
      }
      bottom_edge_triangs = top_edge_triangs;
   }
   return true;
}

//-----------------------------------------------------------------------------
// Name        :  FindThirdIndex
// Creation    :  28-Oct-2022 SPA
// Description :  Given an unsorted collection of three triangle vertex indices and
//                two known vertex indices, find the third index
// Parameters  :
//    const TriIndex &triang - Triangle vertex indices
//    int jp, int jq - Two known indices from the triangle
//    int &jr - The third index
// Returns     :
//    bool - true if valid third index found, false otherwise
//-----------------------------------------------------------------------------
static bool FindThirdIndex(const TriIndex &triang, long jp, long jq, long &jr)
{
   jr = -1;
   for (std::size_t ir = 0; ir < 3; ir++)
   {
      jr = triang._p[ir];
      if ((jr != jp) && (jr != jq))
      {
         return true;
      }
   }
   return false;
}

//-----------------------------------------------------------------------------
// Name        :  FindEdge
// Creation    :  28-Oct-2022 SPA
// Description :  Given two lists of edge indices, each associated with a point,
//                find the common index.
// Parameters  :
//    const std::list<int> &pt_edgesA - Edge list for first vertex
//    const std::list<int> &pt_edgesB - Edge list for second vertex
//    int &jedge - Index of shared edge
// Returns     :
//    bool - true if shared edge-index found, false otherwise
//-----------------------------------------------------------------------------
static bool FindEdge(const std::list<long> &pt_edgesA, const std::list<long> &pt_edgesB, long &jedge)
{
   for (long jedgeA: pt_edgesA)
   {
      for (long jedgeB: pt_edgesB)
      {
         if (jedgeA == jedgeB)
         {
            jedge = jedgeA;
            return true;
         }
      }
   }
   return false;
}

//-----------------------------------------------------------------------------
// Name        :  ReassociateEdge
// Creation    :  28-Oct-2022 SPA
// Description :  Given two lists of edge indices, the index of one the two triangles
//                currently bounded by that edge, and the new index of a triangle to be
//                substituted for the current triangle, as well as the vector of all
//                edge-triangles assocation, make the substitution.
// Parameters  :  See parameter list...
// Returns     :
//    bool - true if shared edge-index found, false otherwise
//-----------------------------------------------------------------------------
static bool ReassociateEdge
(  std::list<long> &pt_edgesA, // Shared-edge list for first vertex
   std::list<long> &pt_edgesB, // Shared-dge list for second vertex
   long jtriangOld, // Previous index of a bounding triangle
   long jtriangNew, // New index of a bounding triangle
   std::vector<std::tuple<LattEdge, long, long>> &edge_triangs // Shared-edge/triangle associations
)
{
   long jedge;
   if (FindEdge(pt_edgesA, pt_edgesB, jedge))
   {
      auto &edge_triang = edge_triangs[jedge];
      auto &jtriangAp = std::get<1>(edge_triang);
      auto &jtriangBp = std::get<2>(edge_triang);
      if (jtriangAp == jtriangOld)
      {
         jtriangAp = jtriangNew;
      }
      else
      {
         jtriangBp = jtriangNew;
      }
      return true;
   }
   return false;
}

//-----------------------------------------------------------------------------
// Name        :  CleanupTriangs
// Creation    :  28-Nov-2022 SPA
// Description :  Cleanup collections of points, edges, and triangles, by reindexing
//                and removing those marked for deletion.
// Parameters  :  See parameter list...
// Returns     :
//    bool - true if successful, false otherwise
//-----------------------------------------------------------------------------
static bool CleanupTriangs
(
   const std::vector<bool> &remove_pts, // true if point is to be deleted, false otherwise
   const std::vector<bool> &remove_edges, // true if edge is to be deleted, false otherwise
   const std::vector<bool> &remove_triangs, // true if triangle is to be deleted, false otherwise
   std::vector<LattPoint> &pts, // Points (vertices)
   TriIndexVector &triangs, // Triangles
   std::vector<std::tuple<LattEdge, long, long>> &edge_triangs, // Shared edges and sharing triangles
   std::vector<std::list<long>> &pt_edges // Shared edges associated with each point
)
{
   // Reindex points
   std::size_t n_pts = pts.size();
   std::size_t n_edges = edge_triangs.size();
   std::size_t n_triangs = triangs.size();

   std::vector<long> ind_pts;
   ind_pts.resize(n_pts);
   long n_ptsp = 0;
   for (std::size_t jpt = 0; jpt < n_pts; jpt++)
   {
      long jptp = -1;
      if (!remove_pts[jpt])
      {
         jptp = n_ptsp;
         pts[jptp] = pts[jpt];
         pt_edges[jptp] = pt_edges[jpt];
         n_ptsp++;
      }
      ind_pts[jpt] = jptp;
   }
   pts.erase(pts.begin() + n_ptsp, pts.begin() + n_pts);
   pt_edges.erase(pt_edges.begin() + n_ptsp, pt_edges.begin() + n_pts);

   // Reindex edges
   std::vector<long> ind_edges;
   ind_edges.resize(n_edges);
   long n_edgesp = 0;
   for (std::size_t jedge = 0; jedge < n_edges; jedge++)
   {
      long jedgep = -1;
      if (!remove_edges[jedge])
      {
         jedgep = n_edgesp;
         edge_triangs[jedgep] = edge_triangs[jedge];
         n_edgesp++;
      }
      ind_edges[jedge] = jedgep;
   }
   edge_triangs.erase(edge_triangs.begin() + n_edgesp, edge_triangs.begin() + n_edges);
  
   // Reindex triangles
   std::vector<long> ind_triangs;
   ind_triangs.resize(n_triangs);
   long n_triangsp = 0;
   for (std::size_t jtriang = 0; jtriang < n_triangs; jtriang++ )
   {
      long jtriangp = -1;
      if (!remove_triangs[jtriang])
      {
         jtriangp = n_triangsp;
         triangs[jtriangp] = triangs[jtriang];
         n_triangsp++;
      }
      ind_triangs[jtriang] = jtriangp;
   }
   triangs.erase(triangs.begin() + n_triangsp, triangs.begin() + n_triangs);

   // Reindex point-edges
   for (auto &pt_edge: pt_edges)
   {
      for (long &jedge: pt_edge)
      {
         jedge = ind_edges[jedge];
         if (jedge == -1)
         {  // Avoid fatal indexing error
            return false;
         }
      }
   }

   // Reindex edge-triangles
   for (auto &edge_triang: edge_triangs)
   {
      auto &edge = std::get<0>(edge_triang);
      long &jtriangA = std::get<1>(edge_triang);
      long &jtriangB = std::get<2>(edge_triang);

      edge.first = ind_pts[edge.first];
      edge.second = ind_pts[edge.second];
      jtriangA = ind_triangs[jtriangA];
      jtriangB = ind_triangs[jtriangB];
   }

   // Reindex triangle-points
   for (auto &triang: triangs)
   {
      for (std::size_t ipt = 0; ipt < 3; ipt++)
      {
         long &jpt = triang._p[ipt];
         jpt = ind_pts[jpt];
         if (jpt == -1)
         {  // Avoid fatal indexing error
            return false;
         }
      }
   }
   return true;
}

//-----------------------------------------------------------------------------
// Name        :  ReduceBorderPoints
// Creation    :  22-Nov-2022 SPA
// Description :  Remove border points representing straight horizontal and vertical
//                edges that are not flagged as fixed. This improves performance on
//                Delaunayization of large, but sparse, triangulations.
// Parameters  :  See parameter list...
// Returns     :
//    bool - true if successful, false otherwise
//-----------------------------------------------------------------------------
static bool ReduceBorderPoints
(
   std::vector<short> &flag_img, // (Extended) flag image specifying point characteristics
   std::size_t width, std::size_t height, // (Extended) image dimensions
   std::vector<LattPoint> &pts, // Points (vertices)
   TriIndexVector &triangs, // Triangles
   std::vector<std::tuple<LattEdge, long, long>> &edge_triangs, // Shared edges and sharing triangles
   std::vector<std::list<long>> &pt_edges // Shared edges associated with each point
)
{
   std::size_t n_pts = pts.size();
   std::size_t n_edges = edge_triangs.size();
   std::size_t n_triangs = triangs.size();
 
   std::vector<bool> remove_pts(n_pts, false); //  Track whether to keep each point
   std::vector<bool> remove_triangs(n_triangs, false); // Track whether to keep each triangle
   std::vector<bool> remove_edges(n_edges, false); // Track whether to keep each edge
  
   std::vector<bool> pt_marks(n_pts, false);  // Mark whether each point is in the queue

   // Fill queue with points for removal and mark them
   std::queue<long> check_pts;
   for (std::size_t jp = 0; jp < n_pts; jp++)
   {
      auto &p = pts[jp];
      short flag_p = flag_img[(p.first) + width * (p.second)];
      if ((flag_p & vertex_mask) && (flag_p & straight_mask) && !(flag_p & fixed_mask))
      {
         check_pts.push(jp);
         pt_marks[jp] = true;
      }
   }
 
   // Iterate to eliminate excess shared edges in border triangles
   int n_pts_removed = 0;
   while (check_pts.size()>0)
   {
      long jp = check_pts.front();
      check_pts.pop();
      if (remove_pts[jp])
      {
         continue;
      }

      pt_marks[jp] = false;
      auto &p = pts[jp];

      // Fill queue of edges associated with this point.
      std::queue<long> check_edges;
      for (long jedge: pt_edges[jp])
      {
         check_edges.push(jedge);
      }
      
      // Prepare safeguards to avoid infinite loop
     	std::size_t n_check_edges = check_edges.size();
      const std::size_t max_iters = n_check_edges * n_check_edges;
      long i_check_edges = 0;

      while (check_edges.size()>0)
      {
         long jedge = check_edges.front();
         check_edges.pop();
         if (remove_edges[jedge])
         {
            continue;
         }

         // Safeguard to avoid infinite loop
         if (i_check_edges > max_iters)
         {  // Proceed to next point
            break;
         }
         i_check_edges++;

         auto &edge_triang = edge_triangs[jedge];
         auto &edge = std::get<0>(edge_triang);
				 long jtriangA = std::get<1>(edge_triang);
         long jtriangB = std::get<2>(edge_triang);

         auto &triangA = triangs[jtriangA];
         auto &triangB = triangs[jtriangB];

         long jq = edge.first;
         if (jq == jp)
         {
            jq = edge.second;
         }
         long jrA;
         if (!FindThirdIndex(triangA, jp, jq, jrA))
         {
            break;
         }
         long jrB;
         if (!FindThirdIndex(triangB, jp, jq, jrB))
         {
            break;
         }

         auto &q = pts[jq];
         auto &rA = pts[jrA];
         auto &rB = pts[jrB];


         long measX_q = (q.first - rA.first) * (rB.second - rA.second);
         long measY_q = (q.second - rA.second) * (rB.first - rA.first);
         bool is_rA_q_rB_linear = (measX_q == measY_q);

         if (IsLattPointInTriang(q, rA, rB, p) || is_rA_q_rB_linear)
         {
            check_edges.push(jedge);
            continue;
         }
         
         if (IsLattPointInTriang(p, rA, rB, q))
         {  // Can't remove point
            break;
         }

         bool is_rA_border = (flag_img[(rA.first) + width * (rA.second)] & border_mask);
         bool is_rB_border = (flag_img[(rB.first) + width * (rB.second)] & border_mask);

         long measX_p = (p.first - rA.first) * (rB.second - rA.second);
         long measY_p = (p.second - rA.second) * (rB.first - rA.first);
         bool is_rA_p_rB_linear = (measX_p == measY_p);

         if (is_rA_border && is_rB_border && is_rA_p_rB_linear)
         {
            if (pt_edges[jp].size() > 1)
            {  // Must remove other edges first
               check_edges.push(jedge);
               continue;
            }
            // Remove point
            pt_edges[jp].remove(jedge);
            pt_edges[jq].remove(jedge);
            remove_edges[jedge] = true;

            // Define the new triangle A
            triangA = {jrA, jq, jrB};

            // Associate edge rB-q with triangle A - no fatal consequence if failure
            if (!ReassociateEdge(pt_edges[jrB], pt_edges[jq], jtriangB, jtriangA, edge_triangs)) {}

            remove_triangs[jtriangB] = true;
            remove_pts[jp] = true;
            n_pts_removed++;
         }
         else
         {  // Flip
            pt_edges[jp].remove(jedge);
            pt_edges[jq].remove(jedge);

            pt_edges[jrA].push_back(jedge);
            pt_edges[jrB].push_back(jedge);
            
            triangA = {jrA, jq, jrB};
            triangB = {jrB, jp, jrA};

            edge = {jrA, jrB};

            // Associate edge rB-q with triangle A - no fatal consequence if failure
            if (!ReassociateEdge(pt_edges[jrB], pt_edges[jq], jtriangB, jtriangA, edge_triangs)) {}

             // Associate edge rA-p with triangle B - no fatal consequence if failure
            if (!ReassociateEdge(pt_edges[jrA], pt_edges[jp], jtriangA, jtriangB, edge_triangs)) {}
         }
      }
   }

   // Cleanup
   return CleanupTriangs(remove_pts, remove_edges, remove_triangs, pts, triangs, edge_triangs, pt_edges);
}

//-----------------------------------------------------------------------------
// Name        :  ReduceBorderPoints
// Creation    :  22-Nov-2022 SPA
// Description :  Remove border points representing straight horizontal and vertical
//                edges that are not flagged as fixed. This improves performance on
//                Delaunayization of large, but sparse, triangulations.
// Parameters  :  See parameter list...
// Returns     :
//    bool - true if successful, false otherwise
//-----------------------------------------------------------------------------
static bool SimplifyBorder
(
   std::vector<short> &flag_img, // (Extended) flag image specifying point characteristics
   std::size_t width, std::size_t height, // (Extneded) image dimensions
   std::vector<LattPoint> &pts, // Points (vertices)
   TriIndexVector &triangs, // Triangles
   std::vector<std::tuple<LattEdge, long, long>> &edge_triangs, // Shared edges and sharing triangles
   std::vector<std::list<long>> &pt_edges // Shared edges associated with each point
)
{
   std::size_t n_pts = pts.size();
   std::size_t n_edges = edge_triangs.size();
   std::size_t n_triangs = triangs.size();

   std::vector<bool> remove_pts(n_pts, false); //  Track whether to keep each point
   std::vector<bool> remove_triangs(n_triangs, false); // Track whether to keep each triangle
   std::vector<bool> remove_edges(n_edges, false); // Track whether to keep each edge
  
   std::vector<bool> pt_marks(n_pts, false);  // Mark whether each point is in the queue

   // Fill queue with points for removal and mark them
   // Frame corners are not removed.
   std::queue<long> check_pts;
   for (long jp = 0; jp < n_pts; jp++)
   {
      auto &p = pts[jp];
      short flag_p = flag_img[(p.first) + width * (p.second)];
      if ((flag_p & vertex_mask) && (flag_p & apex_mask))
      {
         long iX = p.first;
         long iY = p.second;
         bool x_corner = false;
         bool y_corner = false;
         if (p.first > 0)
         {
            x_corner |= (bool)(flag_img[(iX - 1) + width * (iY)] & y_border_mask);
         }
         if (p.first < width - 1)
         {
            x_corner |= (bool)(flag_img[(iX + 1) + width * (iY)] & y_border_mask);
         }
         if (p.second > 0)
         {
            y_corner |= (bool)(flag_img[(iX) + width * (iY - 1)] & x_border_mask);
         }
         if (p.second < height - 1)
         {
            y_corner |= (bool)(flag_img[(iX) + width * (iY + 1)] & x_border_mask);
         }
         if (x_corner && y_corner)
         {
            continue;
         }
         check_pts.push(jp);
         pt_marks[jp] = true;
      }
   }
   
   // Create a list of triangles associated with each point
   std::vector<std::list<long>> pt_triangs(n_pts);
   for (std::size_t jtriang = 0; jtriang < n_triangs; jtriang++)
   {
      auto &triang = triangs[jtriang];
      for (std::size_t ip = 0; ip < 3; ip++)
      {
         long jp = triang._p[ip];
         pt_triangs[jp].push_back(jtriang);
      }
   }

   // Iterate to eliminate excess shared edges in border triangles
   int n_pts_removed = 0;
   while (check_pts.size()>0)
   {
      auto jp = check_pts.front();
      check_pts.pop();
      if (remove_pts[jp])
      {
         continue;
      }

      pt_marks[jp] = false;
      auto &p = pts[jp];

      // Fill queue of edges associated with this point.
      std::queue<long> check_edges;
      for (long jedge: pt_edges[jp])
      {
         check_edges.push(jedge);
      }
      
      // Prepare safeguards to avoid infinite loop
      std::size_t n_check_edges = check_edges.size();
      const std::size_t max_iters = n_check_edges * n_check_edges;
      std::size_t i_check_edges = 0;

      while (check_edges.size()>0)
      {
         auto jedge = check_edges.front();
         check_edges.pop();
         if (remove_edges[jedge])
         {
            continue;
         }

         // Safeguard to avoid infinite loop
         if (i_check_edges > max_iters)
         {  // Proceed to next point
            break;
         }
         i_check_edges++;

         auto &edge_triang = edge_triangs[jedge];
         auto &edge = std::get<0>(edge_triang);
         long jtriangA = std::get<1>(edge_triang);
         long jtriangB = std::get<2>(edge_triang);

         auto &triangA = triangs[jtriangA];
         auto &triangB = triangs[jtriangB];

         long jq = edge.first;
         if (jq == jp)
         {
            jq = edge.second;
         }
         long jrA;
         if (!FindThirdIndex(triangA, jp, jq, jrA))
         {
            break;
         }
         long jrB;
         if (!FindThirdIndex(triangB, jp, jq, jrB))
         {
            break;
         }

         auto &q = pts[jq];
         auto &rA = pts[jrA];
         auto &rB = pts[jrB];

         long measX_q = (q.first - rA.first) * (rB.second - rA.second);
         long measY_q = (q.second - rA.second) * (rB.first - rA.first);
         bool is_rA_q_rB_linear = (measX_q == measY_q);

         if (IsLattPointInTriang(q, rA, rB, p) || is_rA_q_rB_linear)
         {
            check_edges.push(jedge);
            continue;
         }
         
         if (IsLattPointInTriang(p, rA, rB, q))
         {  // Can't remove point
            break;
         }

         pt_edges[jp].remove(jedge);
         pt_edges[jq].remove(jedge);

         pt_edges[jrA].push_back(jedge);
         pt_edges[jrB].push_back(jedge);
            
         triangA = {jrA, jq, jrB};
         triangB = {jrB, jp, jrA};

         edge = {jrA, jrB};

         // Associate edge rB-q with triangle A - no fatal consequence if failure
         if (!ReassociateEdge(pt_edges[jrB], pt_edges[jq], jtriangB, jtriangA, edge_triangs)) {}

         // Associate edge rA-p with triangle B - no fatal consequence if failure
         if (!ReassociateEdge(pt_edges[jrA], pt_edges[jp], jtriangA, jtriangB, edge_triangs)) {}

         pt_triangs[jp].remove(jtriangA);
         pt_triangs[jq].remove(jtriangB);

         pt_triangs[jrA].push_back(jtriangB);
         pt_triangs[jrB].push_back(jtriangA);
      }

      // Remove point
      if (pt_triangs[jp].size() == 1)
      {
         long jtriang = pt_triangs[jp].front();
         auto &triang = triangs[jtriang];

         long jrA = -1, jrB = -1;
         for (std::size_t ip = 0; ip < 3; ip++)
         {
            long jq = triang._p[ip];
            if (jq != jp)
            {
               jrB = jrA;
               jrA = jq;
            }
         }
         pt_triangs[jp].remove(jtriang);
         pt_triangs[jrA].remove(jtriang);
         pt_triangs[jrB].remove(jtriang);
         remove_triangs[jtriang] = true;

         long jedge_rA_rB = -1;
         if (FindEdge(pt_edges[jrA], pt_edges[jrB], jedge_rA_rB))
         {
            remove_edges[jedge_rA_rB] = true;
            pt_edges[jrA].remove(jedge_rA_rB);
            pt_edges[jrB].remove(jedge_rA_rB);
         }
         remove_pts[jp] = true;
         n_pts_removed++;
      }
   }

   // Clean up
   return CleanupTriangs(remove_pts, remove_edges, remove_triangs, pts, triangs, edge_triangs, pt_edges);
}

//-----------------------------------------------------------------------------
// Name        :  MakeDelaunayTriangles
// Creation    :  28-Oct-2022 SPA
// Description :  An implementation of Lawson's flip algorithm to convert an arbitrary
//                tiling of triangles Delaunay.
// Parameters  :  See parameter list...
// Returns     :
//    bool - true if successful, false otherwise
//-----------------------------------------------------------------------------
static bool MakeDelaunayTriangles
(  TriIndexVector &triangs, // Triangle indices
   const std::vector<LattPoint> &pts, // Vertex coords
   std::vector<std::tuple<LattEdge, long, long>> &edge_triangs, // Shared edges and sharing triangles
   std::vector<std::list<long>> &pt_edges // Shared edges associated with each vertex
)
{
   const std::size_t n_edges = edge_triangs.size();
   std::vector<bool> edge_marks(n_edges); // Mark whether each edge needs to be checked

   // Build stack of shared edges
   std::stack<long> check_edges;
   for (std::size_t jedge = 0; jedge < n_edges; jedge++)
   {
      check_edges.push(jedge);
      edge_marks[jedge] = true;
   }

   // Set arbitrary threshold before rejection of edge
   std::size_t max_iters = (std::size_t)(n_edges * log10((double)n_edges + 1.));
   max_iters = (max_iters < 100000)? 100000 : max_iters;
   std::size_t n_edges_prev = n_edges;
   std::size_t i_iters = 0;
   while (check_edges.size()>0)
   {
      long jedge = check_edges.top();
      check_edges.pop();
      edge_marks[jedge] = false;
         
      auto &edge_triang = edge_triangs[jedge];

      auto &edge = std::get<0>(edge_triang);
      long jtriangA = std::get<1>(edge_triang);
      long jtriangB = std::get<2>(edge_triang);

      TriIndex &triangA = triangs[jtriangA];
      TriIndex &triangB = triangs[jtriangB];

      auto jp = edge.first;
      auto jq = edge.second;
      long jrA = -1;
      if (!FindThirdIndex(triangA, jp, jq, jrA))
      {  // Indexing issue
         return false;
      }
      long jrB = -1;
      if (!FindThirdIndex(triangB, jp, jq, jrB))
      {  // Indexing issue
         return false;
      }

      auto &p = pts[jp];
      auto &q = pts[jq];
      auto &rA = pts[jrA];
      auto &rB = pts[jrB];
  
      std::vector<LattPoint> tri_ptsA = {p, q, rA};
      std::vector<LattPoint> tri_ptsB = {p, q, rB};

      bool bad_tri = false;
      if (IsLattPointInCircle(tri_ptsA, rB))
      {
         bad_tri = true;
      }
      else
      {
         if (IsLattPointInCircle(tri_ptsB, rA))
         {
            bad_tri = true;
         }
      }
      if (bad_tri)
      {
         // Flipping occurs here
         triangA = {jrB, jrA, jq};
         triangB = {jrB, jrA, jp};

         // Reassign this edge
         edge = {jrA, jrB};

         // Correct the list of indices associated with each triangle
         pt_edges[jp].remove(jedge);
         pt_edges[jq].remove(jedge);
         pt_edges[jrA].push_back(jedge);
         pt_edges[jrB].push_back(jedge);

         long jedgep;
         if (FindEdge(pt_edges[jrA], pt_edges[jp], jedgep))
         {
            auto &edge_triangp = edge_triangs[jedgep];
            long &jtriangC = std::get<1>(edge_triangp);
            long &jtriangD = std::get<2>(edge_triangp);
            if (jtriangC == jtriangA)
            {
               jtriangC = jtriangB;
            }
            else
            {
               jtriangD = jtriangB;
            }
            if (!edge_marks[jedgep])
            {
               edge_marks[jedgep] = true;
               check_edges.push(jedgep);
            }
         }

         if (FindEdge(pt_edges[jp], pt_edges[jrB], jedgep))
         {
            if (!edge_marks[jedgep])
            {
               edge_marks[jedgep] = true;
               check_edges.push(jedgep);
            }
         }

         if (FindEdge(pt_edges[jrB], pt_edges[jq], jedgep))
         {
            auto &edge_triangp = edge_triangs[jedgep];
            long &jtriangC = std::get<1>(edge_triangp);
            long &jtriangD = std::get<2>(edge_triangp);
						if (jtriangC == jtriangB)
            {
               jtriangC = jtriangA;
            }
            else
            {
               jtriangD = jtriangA;
            }
            if (!edge_marks[jedgep])
            {
               edge_marks[jedgep] = true;
               check_edges.push(jedgep);
            }
         }

         if (FindEdge(pt_edges[jq], pt_edges[jrA], jedgep))
         {
            if (!edge_marks[jedgep])
            {
               edge_marks[jedgep] = true;
               check_edges.push(jedgep);
            }
         }
         // Safeguard to avoid infinite loop
         if (check_edges.size() >= n_edges_prev)
         {
            i_iters++;
            if (i_iters > max_iters)
            {  // Unable to flip this edge - skip it
               edge_marks[jedge] = true;
               i_iters = 0;
               continue;
            }
         }
      }
      else
      {
         n_edges_prev = check_edges.size();
      }
   }
   return  true;
}

//-----------------------------------------------------------------------------
// Name        :  FlagPoints
// Creation    :  22-Nov-2022 SPA
// Description :  Flag additional points as fixed vertices for triangulation,
//                depending on selected resolution
//
// Parameters  :  See parameter list...
// Returns     :
//-----------------------------------------------------------------------------
static void GetNormals
(	std::vector<float> &point_img, // (Extended) point image
	std::vector<short> &flag_img,  // (Extended) flag image - to be modified here
	std::size_t ext_width, std::size_t ext_height, // (Extended) image dimensions
	std::vector<LattPoint> &pts, // Points to be retained
	std::vector<vtr3> &norms // Contains normals to specfied points upon return
)
{
	for(auto &pt:pts)
	{
		vtr3 nV=vtr3::Vz;
		long iX=pt.first;
		long iY=pt.second;
		double F0(0.),F1(0.),F2(0.);
		double S00(0.),S01(0.),S02(0.);
		double S10(0.),S11(0.);
		double S20(0.);
		std::size_t iPos=pt.first + (ext_width-1)*pt.second;
		for (long diY= -1; diY <= 1; diY++)
		{
			if ((iY+diY>=0) && (iY < ext_height))
			{
				for (long diX = -1; diX <= 1; diX++)
				{
					if ((iX+diX>=0) && (iX+diX < ext_width))
					{
						std::size_t iPos_p=iPos+diX+(ext_width)*diY;
						if ((flag_img[iPos_p] & data_mask))
						{
							double fxy=point_img[iPos_p];
							F0+=fxy*1;F1+=fxy*diX;F2+=fxy*diY;
				
							S00+=1.;S01+=diY;S02+=diY*diY;
							S10+=diX;S11+=diX*diY;
							S20+=diX*diX;
						}
					}
				}
			}
		}
		arr::darr1 F=arr::darr1::zero(3);
		F(0)=F0;F(1)=F1;F(2)=F2;
		
		arr::darr2 S=arr::darr2::zero(3,3);
		S(0,0)=S00;S(0,1)=S10;S(0,2)=S01;
		S(1,0)=S10;S(1,1)=S20;S(1,2)=S11;
		S(2,0)=S01;S(2,1)=S11;S(2,2)=S02;
		if(S.det()!=0.)
		{
			arr::darr1 C=S.inv()*F;
			nV=vtr3(-C(1),-C(2),1);
			nV=nV.norm();
		}
		norms.push_back(nV);
	}
}

//
static void GetRange
(	std::vector<float> &point_img, // (Extended) point image
	std::vector<short> &flag_img,  // (Extended) flag image - to be modified here
	std::size_t ext_width, std::size_t ext_height, // (Extended) image dimensions
	MeshRange &meshRange
)
{
	meshRange.init();
	std::size_t iPos(0);
	for (uint32_t iY = 0; iY < ext_height; iY++)
	{
		for (uint32_t iX = 0; iX < ext_width; iX++)
		{
			if ((flag_img[iPos] & data_mask))
			{
				pnt3 P(iX,ext_height - 1 - iY,point_img[iPos]);
				meshRange.expand(P);
			}
			iPos++;
		}
	}
}


//-----------------------------------------------------------------------------
// Name        :  CalcTriFromFloatImage
// Creation    :  28-Oct-2022 SPA
// Description :  Calculates a triangulation for a provided TIFF image with elevation values
//                (i.e., digital surface model) for subsequent image registration. Find
//                examples at https://apps.nationalmap.gov/downloader/
//                The image isloaded into an array of floats for analysis.
//                Regions containing data are densely tiled; regions without data
//                (as specified by the "no data" GDAL flag) are omitted.
//
// Parameters  :  See parameter list...
// Returns     :  bool - true if successful, false otherwise
//-----------------------------------------------------------------------------
TopoTri::TopoTri
(	std::vector<float> &data_img,  // array of image data
	std::size_t width, std::size_t height,  // Image dimensions
	bool omit_noData,
	float noDataVal,
	float tri_res, // Resolution factor (0 - 1) for triangulation
	bool simplify_border // Specifies whether to eliminate border apices
):Mesh()
{
	// Build bool patch image : true if valid pixel, false if "no data"
	auto patch_img = std::vector<bool>(width * height);
	int iPos = 0;
	for (uint32_t iY = 0; iY < height; iY++)
	{
		for (uint32_t iX = 0; iX < width; iX++)
		{
			 patch_img[iPos] = !(omit_noData && (data_img[iPos] == noDataVal));
			 iPos++;
		}
	}

	// Create point image specifying pixel corners
	std::size_t ext_width = width + 1;
	std::size_t ext_height = height + 1;
	auto point_img = std::vector<float>(ext_width * ext_height);
	GetPointImage(width, height, patch_img, data_img, point_img);
	
	// Init flag image specifying point character
	auto flag_img = std::vector<short>(ext_width * ext_height);

	InitFlagImage(patch_img, flag_img, width, height);

	// Flag additional vertices, depending on resolution
	if (!FlagPoints(point_img, flag_img, ext_width, ext_height, tri_res))
	{
		return;
	}

	// Create an image of point indices
	auto index_img = std::vector<long>(ext_width * ext_height);
	std::vector<LattPoint> pts; // Vertices
	IndexPoints(flag_img, ext_width, ext_height, index_img, pts);

	// Create row triangulation and collect elements

	_submesh.clear();
	_currentSubmesh=new SubMesh();
	_submesh["topo"]=_currentSubmesh;

	_currentSubmesh->_tris.clear();
	std::vector<std::tuple<LattEdge, long, long>> edge_triangs; // Shared edges and sharing triangles
	std::vector<std::list<long>> pt_edges(pts.size()); // Shared edges for each point
	if (!BuildRowTriangles(flag_img, index_img, ext_width, ext_height, _currentSubmesh->_tris, edge_triangs, pt_edges))
	{
		return;
	}

	// Eliminate unnecessary border points
	if (!ReduceBorderPoints(flag_img, ext_width, ext_height, pts, _currentSubmesh->_tris, edge_triangs, pt_edges))
	{
		return;
	}
	if (simplify_border)
	{
		if (!SimplifyBorder(flag_img, ext_width, ext_height, pts, _currentSubmesh->_tris, edge_triangs, pt_edges))
		{
			 return;
		}
	}
	// Convert to Delaunay triangulation
	if (!MakeDelaunayTriangles(_currentSubmesh->_tris, pts, edge_triangs, pt_edges))
	{
		return;
	}
	 
	std::vector<vtr3> norms;
	GetNormals(point_img,flag_img,ext_width,ext_height,pts,norms);

	// Convert vertices to 3-D coordinates
	_vertex.clear();
	int i_point(0);
	for (auto &pt: pts)
	{
		pnt3 P(pt.first,ext_height - 1 - pt.second,point_img[(pt.first) + ext_width * (pt.second)]);
		pnt2 Ptex(P.x()/ext_width,1.-P.y()/ext_height);
		_vertex.emplace_back(P,norms[i_point],Ptex);
		i_point++;
	}
   
	GetRange(point_img,flag_img,ext_width,ext_height,_range);
	
	// make right-handed
	for (uint32_t i_triang=0;i_triang<_currentSubmesh->numTriang();++i_triang)
	{
		auto &index=_currentSubmesh->_tris[i_triang];
		pnt3 &A=std::get<0>(_vertex[index._i]);
		pnt3 &B=std::get<0>(_vertex[index._j]);
		pnt3 &C=std::get<0>(_vertex[index._k]);

		if((B-A).cross(C-A).z()<0.)
		{
			std::swap(index._j,index._k);
		}
	}
	
 }

//-----------------------------------------------------------------------------
// Name        :  Triangulation::CalculateRes (static)
// Creation    :  01-Dec-2022 SPA
// Description :  Convert the panel slider value into a resolution factor using
//                file-size dependent, roughly log scale.
// Parameters  :
//    int sliderVal - value from panel slider (0 - 100)
//    std::size_t n_pix - image size (pixels)
// Returns     :
//    float - resolution factor (0 - 1)
//-----------------------------------------------------------------------------
float TopoTri::CalculateRes(int sliderVal, std::size_t n_pix)
{
   float ratio = (float)sliderVal / 100;
   const float res_root = (float)sqrt(n_pix);
   float tri_res = (float)(pow(res_root, ratio) - 1.)/(float)(pow(res_root, 1.) - 1.); // ~calculate slider using log scale
   return tri_res;
}
