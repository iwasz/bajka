/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  Portions of this code are taken from the NANOSVG project which (on MIT  *
 *  license).                                                               *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Svg.h"
#include "nanosvg.h"
#include "Platform.h"
#include <common/dataSource/DataSource.h>
#include <container/inputFormat/mxml/MXmlMetaService.h>
#include <mxml.h>
#include "util/Exceptions.h"
#include "geometry/Point.h"
#include <vector>

namespace Geometry {

/**
 * Tu się wykonuje cały algorytm.
 */
struct Impl {

        Impl (Core::VariantMap *o/*, Core::IAllocator <char> *aloc*/) : output (o) {}

        // Rozkmiń co to za tag
        void onOpenElement (mxml_node_t *node);
        void onCloseElement (mxml_node_t *node);
        void onData (mxml_node_t *node) {}

        // To jest path. Rozkmiń jaki path
        void onOpenPath (mxml_node_t *node);
        void onClosePath (mxml_node_t *node);

        // To jest rect.
        void onOpenRect (mxml_node_t *node);
        void onCloseRect (mxml_node_t *node);

        typedef std::vector <Geometry::Point> PointVector;

        /**
         * Parsuje path opisany w specyfikacji SVG. W wariancie jest wskaxnik, który trzeba usunąć
         * za pomocą delete (?będzie zależeć od alokatora?).
         */
        static Core::Variant parseSvgPath (const char *path);
        static const char* getNextPathItem (const char* s, char* it);
        static int isnum (char c) { return strchr("0123456789+-.eE", c) != 0; }
        static int getArgsPerElement (char cmd);
        static void pathLineTo (PointVector* p, float* cpx, float* cpy, float* args, int rel);
        static void pathHLineTo (PointVector* p, float* cpx, float* cpy, float* args, int rel);
        static void pathVLineTo (PointVector* p, float* cpx, float* cpy, float* args, int rel);
        static void pathCubicBezTo (PointVector *p, float* cpx, float* cpy, float* cpx2, float* cpy2, float* args, int rel);
        static void pathCubicBezShortTo (PointVector *p, float* cpx, float* cpy, float* cpx2, float* cpy2, float* args, int rel);
        static void pathQuadBezTo (PointVector *p, float* cpx, float* cpy, float* cpx2, float* cpy2, float* args, int rel);
        static void pathQuadBezShortTo (PointVector *p, float* cpx, float* cpy, float* cpx2, float* cpy2, float* args, int rel);

        static void cubicBez (PointVector *p,
                              float x1, float y1, float cx1, float cy1,
                              float cx2, float cy2, float x2, float y2);

        static void cubicBezRec (PointVector *p,
                                 float x1, float y1, float x2, float y2,
                                 float x3, float y3, float x4, float y4,
                                 int level);

        static float distPtSeg(float x, float y, float px, float py, float qx, float qy);

private:

        Core::VariantMap *output;
        std::string currentId;
        Core::Variant currentObject;
        static const float P_TOL;
};

/****************************************************************************/

const float Impl::P_TOL = 1.0;
void saxHandler (mxml_node_t *node, mxml_sax_event_t event, void *data);

/****************************************************************************/

Core::VariantMap Svg::parseFile (Common::DataSource *ds, std::string const &path)
{
        Core::VariantMap ret;

//        Core::ArrayRegionAllocator <char> *memoryAllocator = container->getMemoryAllocator ();
        Impl impl (&ret/*, memoryAllocator*/);

        std::string xml;
        ds->open (path.c_str (), Common::DataSource::MODE_UNKNOWN);
        Container::MXmlMetaService::loadDataSource (ds, &xml);
        ds->close ();

        mxmlSAXLoadString (NULL, xml.c_str (), MXML_OPAQUE_CALLBACK, saxHandler, &impl);
        return ret;
}

/****************************************************************************/

Core::VariantMap Svg::parseFile (std::string const &path)
{
        Common::DataSource standardDs;
        return parseFile (&standardDs, path);
}

/****************************************************************************/

void saxHandler (mxml_node_t *node, mxml_sax_event_t event, void *data)
{
        Impl *impl = static_cast <Impl *> (data);

        mxml_type_t type = mxmlGetType (node);

        switch (event) {
        case MXML_SAX_CDATA:
        case MXML_SAX_DATA:
                impl->onData (node);
                break;

        case MXML_SAX_ELEMENT_CLOSE:

                if (type == MXML_ELEMENT) {
                        impl->onCloseElement (node);
                }
                break;

        case MXML_SAX_ELEMENT_OPEN:

                if (type == MXML_ELEMENT) {
                        impl->onOpenElement (node);
                }

                break;

        default:
                break;
        }
}

/****************************************************************************/

void Impl::onOpenElement (mxml_node_t *node)
{
        char const *name = mxmlGetElement (node);

        if (!strcmp (name, "path")) {
                onOpenPath (node);
        }
        else if (!strcmp (name, "rect")) {
                onOpenRect (node);
        }
}

/****************************************************************************/

void Impl::onCloseElement (mxml_node_t *node)
{
        char const *name = mxmlGetElement (node);

        if (!strcmp (name, "path")) {
                onClosePath (node);
        }
        else if (!strcmp (name, "rect")) {
                onCloseRect (node);
        }
}

/****************************************************************************/

void Impl::onOpenPath (mxml_node_t *node)
{
        char const *argVal = NULL;

        if ((argVal = mxmlElementGetAttr(node, "id"))) {
                currentId = argVal;
        }

        if ((argVal = mxmlElementGetAttr(node, "d"))) {
                currentObject = parseSvgPath (argVal);
        }
        else {
                throw Util::InitException("Svg::onOpenPath : path without data. <path> tag without 'd' attribute.");
        }
}

/****************************************************************************/

void Impl::onClosePath (mxml_node_t *node)
{
        output->operator[] (currentId) = currentObject;
        currentId = "";
        currentObject = Core::Variant ();
}

/****************************************************************************/

void Impl::onOpenRect (mxml_node_t *node)
{

}

/****************************************************************************/

void Impl::onCloseRect (mxml_node_t *node)
{

}

/****************************************************************************/

Core::Variant Impl::parseSvgPath (const char *s)
{
        bool closedFlag = 0;
        int nargs = 0;
        int rargs = 0;
        char item[64];
        char cmd;
        float args[10];
        float cpx, cpy, cpx2, cpy2;
        // TODO to pewnei będzie inny typ>
        PointVector tmpBuf;

        while (*s) {
                s = getNextPathItem (s, item);

                if (!*item) {
                        break;
                }

                if (isnum (item[0])) {

                        if (nargs < 10) {
                                args[nargs++] = (float)atof(item);
                        }

                        if (nargs >= rargs) {
                                switch (cmd) {
                                        case 'm':
                                        case 'M':
                                        case 'l':
                                        case 'L':
                                                pathLineTo (&tmpBuf, &cpx, &cpy, args, (cmd == 'm' || cmd == 'l') ? 1 : 0);
                                                break;
                                        case 'H':
                                        case 'h':
                                                pathHLineTo (&tmpBuf, &cpx, &cpy, args, cmd == 'h' ? 1 : 0);
                                                break;
                                        case 'V':
                                        case 'v':
                                                pathVLineTo (&tmpBuf, &cpx, &cpy, args, cmd == 'v' ? 1 : 0);
                                                break;
                                        case 'C':
                                        case 'c':
                                                pathCubicBezTo (&tmpBuf, &cpx, &cpy, &cpx2, &cpy2, args, cmd == 'c' ? 1 : 0);
                                                break;
                                        case 'S':
                                        case 's':
                                                pathCubicBezShortTo (&tmpBuf, &cpx, &cpy, &cpx2, &cpy2, args, cmd == 's' ? 1 : 0);
                                                break;
                                        case 'Q':
                                        case 'q':
                                                pathQuadBezTo (&tmpBuf, &cpx, &cpy, &cpx2, &cpy2, args, cmd == 'q' ? 1 : 0);
                                                break;
                                        case 'T':
                                        case 't':
                                                pathQuadBezShortTo (&tmpBuf, &cpx, &cpy, &cpx2, &cpy2, args, cmd == 's' ? 1 : 0);
                                                break;
                                        default:
                                                if (nargs >= 2)
                                                {
                                                        cpx = args[nargs-2];
                                                        cpy = args[nargs-1];
                                                }
                                                break;
                                }
                                nargs = 0;
                        }
                }
                else {
                        cmd = item[0];
                        rargs = getArgsPerElement (cmd);

                        if (cmd == 'M' || cmd == 'm') {

                                // Commit path. Chyba start nowego path.
                                if (p->nbuf) {
                                        svgCreatePath (p, closedFlag);
                                }

                                // Start new subpath.
                                svgResetPath(p);
                                closedFlag = 0;
                                nargs = 0;
                                cpx = 0; cpy = 0;
                        }
                        else if (cmd == 'Z' || cmd == 'z') {
                                closedFlag = 1;

                                // Commit path.Koniec całego path
                                if (p->nbuf) {
                                        svgCreatePath(p, closedFlag);
                                }

                                // Start new subpath.
                                svgResetPath(p);
                                closedFlag = 0;
                                nargs = 0;
                        }
                }
        }

        // Commit path.
        if (p->nbuf)
                svgCreatePath(p, closedFlag);

}

/****************************************************************************/

const char* Impl::getNextPathItem (const char* s, char* it)
{
        int i = 0;
        it[0] = '\0';
        // Skip white spaces and commas
        while (*s && (isspace(*s) || *s == ',')) s++;
        if (!*s) return s;
        if (*s == '-' || *s == '+' || isnum(*s))
        {
                while (*s == '-' || *s == '+')
                {
                        if (i < 63) it[i++] = *s;
                        s++;
                }
                while (*s && *s != '-' && *s != '+' && isnum(*s))
                {
                        if (i < 63) it[i++] = *s;
                        s++;
                }
                it[i] = '\0';
        }
        else
        {
                it[0] = *s++;
                it[1] = '\0';
                return s;
        }
        return s;
}

/****************************************************************************/

int Impl::getArgsPerElement (char cmd)
{
        switch (tolower (cmd)) {
        case 'v':
        case 'h':
                return 1;
        case 'm':
        case 'l':
        case 't':
                return 2;
        case 'q':
        case 's':
                return 4;
        case 'c':
                return 6;
        case 'a':
                return 7;
        }
        return 0;
}

/****************************************************************************/

void Impl::pathLineTo (PointVector* p, float* cpx, float* cpy, float* args, int rel)
{
        if (rel) {
                *cpx += args[0];
                *cpy += args[1];
        } else {
                *cpx = args[0];
                *cpy = args[1];
        }

        p->push_back (Geometry::makePoint (*cpx, *cpy));
}

/****************************************************************************/

void Impl::pathHLineTo (PointVector* p, float* cpx, float* cpy, float* args, int rel)
{
        if (rel) {
                *cpx += args[0];
        }
        else {
                *cpx = args[0];
        }

        p->push_back (Geometry::makePoint (*cpx, *cpy));
}

/****************************************************************************/

void Impl::pathVLineTo (PointVector* p, float* cpx, float* cpy, float* args, int rel)
{
        if (rel) {
                *cpy += args[0];
        }
        else {
                *cpy = args[0];
        }

        p->push_back (Geometry::makePoint (*cpx, *cpy));
}

/****************************************************************************/

void Impl::pathCubicBezTo (PointVector *p, float* cpx, float* cpy, float* cpx2, float* cpy2, float* args, int rel)
{
        float x1, y1, x2, y2, cx1, cy1, cx2, cy2;

        x1 = *cpx;
        y1 = *cpy;
        if (rel) {
                cx1 = *cpx + args[0];
                cy1 = *cpy + args[1];
                cx2 = *cpx + args[2];
                cy2 = *cpy + args[3];
                x2 = *cpx + args[4];
                y2 = *cpy + args[5];
        } else {
                cx1 = args[0];
                cy1 = args[1];
                cx2 = args[2];
                cy2 = args[3];
                x2 = args[4];
                y2 = args[5];
        }

        cubicBez(p, x1, y1, cx1, cy1, cx2, cy2, x2, y2);

        *cpx2 = cx2;
        *cpy2 = cy2;
        *cpx = x2;
        *cpy = y2;
}

/****************************************************************************/

void Impl::pathCubicBezShortTo (PointVector *p, float* cpx, float* cpy, float* cpx2, float* cpy2, float* args, int rel)
{
        float x1, y1, x2, y2, cx1, cy1, cx2, cy2;

        x1 = *cpx;
        y1 = *cpy;
        if (rel) {
                cx2 = *cpx + args[0];
                cy2 = *cpy + args[1];
                x2 = *cpx + args[2];
                y2 = *cpy + args[3];
        } else {
                cx2 = args[0];
                cy2 = args[1];
                x2 = args[2];
                y2 = args[3];
        }

        cx1 = 2 * x1 - *cpx2;
        cy1 = 2 * y1 - *cpy2;

        cubicBez(p, x1, y1, cx1, cy1, cx2, cy2, x2, y2);

        *cpx2 = cx2;
        *cpy2 = cy2;
        *cpx = x2;
        *cpy = y2;
}

/****************************************************************************/

void Impl::pathQuadBezTo (PointVector *p, float* cpx, float* cpy, float* cpx2, float* cpy2, float* args, int rel)
{
        float x1, y1, x2, y2, cx, cy;

        x1 = *cpx;
        y1 = *cpy;
        if (rel) {
                cx = *cpx + args[0];
                cy = *cpy + args[1];
                x2 = *cpx + args[2];
                y2 = *cpy + args[3];
        } else {
                cx = args[0];
                cy = args[1];
                x2 = args[2];
                y2 = args[3];
        }

        quadBez(p, x1, y1, cx, cy, x2, y2);

        *cpx2 = cx;
        *cpy2 = cy;
        *cpx = x2;
        *cpy = y2;
}

/****************************************************************************/

void Impl::pathQuadBezShortTo (PointVector *p, float* cpx, float* cpy, float* cpx2, float* cpy2, float* args, int rel)
{
        float x1, y1, x2, y2, cx, cy;

        x1 = *cpx;
        y1 = *cpy;
        if (rel) {
                x2 = *cpx + args[0];
                y2 = *cpy + args[1];
        } else {
                x2 = args[0];
                y2 = args[1];
        }

        cx = 2 * x1 - *cpx2;
        cy = 2 * y1 - *cpy2;

        quadBez(p, x1, y1, cx, cy, x2, y2);

        *cpx2 = cx;
        *cpy2 = cy;
        *cpx = x2;
        *cpy = y2;
}

/****************************************************************************/

void Impl::cubicBezRec (PointVector *p,
                        float x1, float y1, float x2, float y2,
                        float x3, float y3, float x4, float y4,
                        int level)
{
        float x12, y12, x23, y23, x34, y34, x123, y123, x234, y234, x1234, y1234;
        float d;

        if (level > 12) {
                return;
        }

        x12 = (x1 + x2) * 0.5f;
        y12 = (y1 + y2) * 0.5f;
        x23 = (x2 + x3) * 0.5f;
        y23 = (y2 + y3) * 0.5f;
        x34 = (x3 + x4) * 0.5f;
        y34 = (y3 + y4) * 0.5f;
        x123 = (x12 + x23) * 0.5f;
        y123 = (y12 + y23) * 0.5f;
        x234 = (x23 + x34) * 0.5f;
        y234 = (y23 + y34) * 0.5f;
        x1234 = (x123 + x234) * 0.5f;
        y1234 = (y123 + y234) * 0.5f;

        d = distPtSeg (x1234, y1234, x1, y1, x4, y4);

        if (level > 0 && d < P_TOL * P_TOL) {
                p->push_back (Geometry::makePoint (x1234, y1234));
                return;
        }

        cubicBezRec (p, x1, y1, x12, y12, x123, y123, x1234, y1234, level + 1);
        cubicBezRec (p, x1234, y1234, x234, y234, x34, y34, x4, y4, level + 1);
}

/****************************************************************************/

void Impl::cubicBez (PointVector *p,
                     float x1, float y1, float cx1, float cy1,
                     float cx2, float cy2, float x2, float y2)
{
        cubicBezRec (p, x1,y1, cx1,cy1, cx2,cy2, x2,y2, 0);
        p->push_back (Geometry::makePoint (x2, y2));
}

/****************************************************************************/

float Impl::distPtSeg(float x, float y, float px, float py, float qx, float qy)
{
        float pqx, pqy, dx, dy, d, t;
        pqx = qx-px;
        pqy = qy-py;
        dx = x-px;
        dy = y-py;
        d = pqx*pqx + pqy*pqy;
        t = pqx*dx + pqy*dy;
        if (d > 0) t /= d;
        if (t < 0) t = 0;
        else if (t > 1) t = 1;
        dx = px + t*pqx - x;
        dy = py + t*pqy - y;
        return dx*dx + dy*dy;
}

/****************************************************************************/

void Svg::test ()
{
        Core::VariantMap objects = parseFile ("test.svg");

        for (Core::VariantMap::const_iterator i = objects.begin (); i != objects.end (); ++i) {
                std::string const &id = i->first;
                std::cerr << "id=" << id << ", " << i->second << std::endl;
        }

#if 0
        struct SVGPath* plist;
        plist = svgParseFromFile ("test.svg");

        // Use...
        for (SVGPath* it = plist; it; it = it->next)
        {
                printlog ("path : %s", it->id);
//                glBegin(it->closed ? GL_LINE_LOOP : GL_LINE_STRIP);
                for (int i = 0; i < it->npts; ++i) {
                        printlog ("%f, %f", it->pts[i*2], it->pts[i*2+1]);
                }
//                glEnd();
        }

        // Delete
        svgDelete(plist);
#endif
}



} /* namespace Geometry */
