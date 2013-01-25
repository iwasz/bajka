/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef GEOM_PRIMITIVE_H_
#define GEOM_PRIMITIVE_H_

/**
 * \defgroup Geometry
 * \ingroup Model
 * Czysta geometria, niezależne od M/V/C.
 *
 * Boost                    | Bajka.Geometry | Bajka.Model | Opis
 * -------------------------|----------------|-------------|---------------------------------------------------------------------------------
 * model::point             | -              | -           | Basic point class, having coordinates defined in a neutral way.
 * model::d2::point_xy      | Point          | -           | 2D point in Cartesian coordinate system.
 * model::box               | Box            | Box         | Defines a box made of two describing points.
 * model::segment           | Segment        | -           | Class segment: small class containing two points.
 * model::referring_segment | -              | -           | Class segment: small class containing two (templatized) point references.
 * model::linestring        | LineString     | LineString  | A linestring (named so by OGC) is a collection (default a vector) of points.
 * model::ring              | Ring           | Ring        | A ring (aka linear ring) is a *closed* line which should not be selfintersecting.
 * model::polygon           | Polygon        | Polygon     | The polygon contains an outer ring and zero or more inner rings.
 * model::multi_point       | -              | -           | A collection of points.
 * model::multi_linestring  | -              | -           | A collection of linestrings.
 * model::multi_polygon     | -              | -           | A collection of polygons.
 * -                        | -              | Circle      | Kółko, które pa środek w punkcie p i promień r.
 *
 */

#include "AffineMatrix.h"
#include "Point.h"
#include "Box.h"
#include "Ring.h"
#include "Polygon.h"
#include "LineString.h"
#include "Segment.h"

#	endif /* PRIMITIVE_H_ */
